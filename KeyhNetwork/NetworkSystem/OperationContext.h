#pragma once
#include "NetworkTypes.h"

namespace keyh
{
	class OperationID
	{
		static constexpr uint64 kInvalidOperation = 0;

	public:
		OperationID() = default;

	private:
		friend class OperationIdGenerator;
		OperationID(uint64 id);

	private:
		uint64 _id = kInvalidOperation;

	public:
		inline bool isValid() const { return _id != kInvalidOperation; }
	};

	class OperationIdGenerator
	{
	public:
		OperationIdGenerator() = default;

	private:
		uint64 _generatedId = OperationID::kInvalidOperation;

	public:
		OperationID generate();
	};

	struct OperationContext
	{
		OperationID		_operaionId;
		OperationType	_operaionType;
		SocketID		_socketId;

		size_t			_trasferred = 0;
	};

#if defined(KEYH_PLATFORM_WINDOWS)
	struct IocpOperation 
	{
		OVERLAPPED			_overlapped;
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

