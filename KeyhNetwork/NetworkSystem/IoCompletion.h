#pragma once
#include "NetworkTypes.h"
#include "OperationID.h"

namespace keyh
{
	enum class IoStatus : uint8
	{
		None,
		Success,
		Closed,
		Cancelled,
		Error
	};

	class IIoBuffer;

	struct IoCompletion
	{
		SocketID		_socketId;
		OperationID		_operationId;

		OperationType	_operationType = OperationType::None;
		IoStatus		_status = IoStatus::None;

		size_t			_byteTransferred = 0;

		IoErrorGroup	_errorGroup;
		IIoBuffer*		_ioBuffer = nullptr;
	};
}

