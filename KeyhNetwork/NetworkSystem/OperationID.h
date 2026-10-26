#pragma once

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

	public:
		static uint64 encode(OperationID operationId) { return operationId._id; }

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
}