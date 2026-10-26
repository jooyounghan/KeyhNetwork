#include "NetworkSystemPch.h"
#include "IocpBackend.h"

#include "Socket.h"
#include "IoBuffer.h"
#include "OperationContext.h"

namespace keyh
{

#define WSA_VERSION_LO_BYTE 2
#define WSA_VERSION_HI_BYTE 2

	IocpBackend::IocpBackend()
	{
		WORD wVersionRequested = MAKEWORD(WSA_VERSION_LO_BYTE, WSA_VERSION_HI_BYTE);
		int error = WSAStartup(wVersionRequested, &_wsaData);
		if (error != 0)
		{
			KEYH_ASSERT_DEV_ARGS(false, "WSAStartup failed with error: %d", error);
			return;
		}

		if (LOBYTE(_wsaData.wVersion) != WSA_VERSION_LO_BYTE 
			|| HIBYTE(_wsaData.wVersion) != WSA_VERSION_HI_BYTE) 
		{
			KEYH_ASSERT_DEV(false, "Could not find a usable version of Winsock.dll");
			WSACleanup();
			return;
		}

		_iocp = CreateIoCompletionPort(
			INVALID_HANDLE_VALUE
			, nullptr
			, 0
			, 0
		);

		if (_iocp == nullptr)
		{
			KEYH_ASSERT_DEV("false", "CreateIoCompletionPort failed");
			return;
		}
	}

	IocpBackend::~IocpBackend()
	{
		//FlushPendingIO();

		if (_iocp != nullptr)
		{
			CloseHandle(_iocp);
			_iocp = nullptr;
		}

		WSACleanup();
	}

#define IOCP_ARGS(encodedSocketId, socket, iocp, numThread)	\
reinterpret_cast<HANDLE>(socket->getNativeSocket())			\
, iocp														\
, static_cast<ULONG_PTR>(encodedSocketId)					\
, numThread

	bool IocpBackend::registerSocket(SocketID socketId, Socket* socket)
	{
		if (socket == nullptr || socketId.isValid() == false )
		{
			KEYH_ASSERT_DEV(false, "Invalid Socket");
			return false;
		}

		uint64 encodedSocketId = SocketID::encode(socketId);
		HANDLE result = CreateIoCompletionPort(IOCP_ARGS(encodedSocketId, socket, _iocp, 0));
		if (result == nullptr)
		{
			KEYH_ASSERT_DEV(false, "Socket Register for IOCP Failed");
			return false;
		}

		_registeredSockets.insert(encodedSocketId, socket);
		return true;
	}

#undef IOCP_ARGS

	void IocpBackend::unregisterSocket(SocketID socketId, Socket* socket)
	{

	}

	SubmitResult IocpBackend::submitReceive(SocketID socketId, OperationID operationId, IIoBuffer * buffer)
	{
		if (socketId.isValid() == false)
			return SubmitResult::reject(IoErrorCode::InvalidSocket);

		if (operationId.isValid() == false)
			return SubmitResult::reject(IoErrorCode::InvalidOperation);

		if (buffer == nullptr)
			return SubmitResult::reject(IoErrorCode::InvalidBuffer);

		uint64 encodedSocketId = SocketID::encode(socketId);
		SocketMap::FindResult socketFindResult = _registeredSockets.find(encodedSocketId);

		if (socketFindResult.isFound() == false)
			return SubmitResult::reject(IoErrorCode::InvalidSocket);
		
		Socket* targetSocket = *socketFindResult.value();

		uint64 encodedOpearionId = OperationID::encode(operationId);
		OperationMap::FindResult operationFindResult = _pendingOperations.find(encodedOpearionId);

		if (operationFindResult.isFound())
			return SubmitResult::reject(IoErrorCode::ResourceExhausted);

		Ptr<IocpOperation> operation = makePtr<IocpOperation>();

		operation->_context._socketId = socketId;
		operation->_context._operaionId = operationId;
		operation->_context._operaionType = OperationType::Receive;
		operation->_context._ioBuffer = buffer;

		IBuffer* storage = buffer->getBuffer();

		operation->_wsaBuf.buf = reinterpret_cast<char*>(storage->getRawBuffer());
		operation->_wsaBuf.len = static_cast<ULONG>(storage->capacity());

		_pendingOperations.insert(encodedOpearionId, keyh::move(operation));

		DWORD flags = 0;
		DWORD bytesReceived = 0;

		const int result = WSARecv
		(
			targetSocket->getNativeSocket()
			, &operation->_wsaBuf
			, 1
			, &bytesReceived
			, &flags
			, &operation->_overlapped
			, nullptr
		);

		if (result == SOCKET_ERROR)
		{
			const int error = ::WSAGetLastError();
			if (error != WSA_IO_PENDING)
			{
				_pendingOperations.remove(encodedOpearionId);
				return SubmitResult::reject(IoErrorCode::SystemError, error);
			}
		}


		return SubmitResult::sucess();
	}

	SubmitResult IocpBackend::submitSend(SocketID socketId, OperationID operationId, IIoBuffer* buffer)
	{
		return SubmitResult();
	}

	size_t IocpBackend::poll(Span<IoCompletion> completions, int timeoutMilliseconds)
	{
		return size_t();
	}
}
