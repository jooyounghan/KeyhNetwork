#pragma once
#include "IIoBackend.h"

namespace keyh
{
    class IocpOperation;

	class IocpBackend : public IIoBackend
	{
	public:
		IocpBackend();
		~IocpBackend() override;

	public:
        virtual bool registerSocket(SocketID socketId, Socket* socket) override;
        virtual void unregisterSocket(SocketID socketId, Socket* socket) override;

    public:
        virtual SubmitResult submitReceive(
            SocketID socketId,
            OperationID operationId,
            IIoBuffer* buffer
        ) override;

        virtual SubmitResult submitSend(
            SocketID socketId,
            OperationID operationId,
            IIoBuffer* buffer
        ) override;

    public:
        virtual size_t poll(
            Span<IoCompletion> completions,
            int timeoutMilliseconds
        ) override;

    private:
        WSADATA _wsaData;
        HANDLE  _iocp = nullptr;

    private:
        using SocketMap = HashMap<uint64, Socket*>;
        using OperationMap = HashMap<uint64, Ptr<IocpOperation>>;

        // Need to optimize with locality(improve Cache Efficiency with locality / Pooling)
        SocketMap       _registeredSockets;
        OperationMap    _pendingOperations;
	};
}

