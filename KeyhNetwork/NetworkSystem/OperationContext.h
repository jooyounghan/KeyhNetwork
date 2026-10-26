#pragma once
#include "NetworkTypes.h"
#include "OperationID.h"

namespace keyh
{
	struct OperationContext
	{
		OperationID		_operaionId;
		OperationType	_operaionType;
		SocketID		_socketId;

		IIoBuffer*		_ioBuffer = nullptr;
		size_t			_byteTransferred = 0;
	};

#if defined(KEYH_PLATFORM_WINDOWS)
	struct IocpOperation 
	{
		OVERLAPPED			_overlapped;
		WSABUF				_wsaBuf;
		OperationContext	_context;
	};
#elif defined(KEYH_PLATFORM_POSIX)
	struct EpollOperation 
	{
		OperationContext	_context;
		size_t				_totalSendBytes = 0;
	};

	struct UringOperation 
	{
		OperationContext	_context;
	};
#endif
}

