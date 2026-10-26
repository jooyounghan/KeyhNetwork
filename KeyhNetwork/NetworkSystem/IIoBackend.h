#pragma once
#include "NetworkTypes.h"
#include "OperationID.h"
#include "SubmitResult.h"

namespace keyh
{
	class IIoBuffer;
    class IoCompletion;
    class Socket;

    class IIoBackend 
    {
    public:
        virtual ~IIoBackend() = default;

    public:
        virtual bool registerSocket(SocketID socketId, Socket* socket) = 0;
        virtual void unregisterSocket(SocketID socketId, Socket* socket) = 0;

    public:
        virtual SubmitResult submitReceive(
            SocketID socketId,
            OperationID operationId,
            IIoBuffer* buffer
        ) = 0;

        virtual SubmitResult submitSend(
            SocketID socketId,
            OperationID operationId,
            IIoBuffer* buffer
        ) = 0;

    public:
        virtual size_t poll(
            Span<IoCompletion> completions,
            int timeoutMilliseconds
        ) = 0;
    };

}
