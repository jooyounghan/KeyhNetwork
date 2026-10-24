#include "NetworkSystemPch.h"
#include "OperationContext.h"

namespace keyh
{
	OperationID::OperationID(uint64 id)
		: _id(id) 
	{}

	OperationID OperationIdGenerator::generate()
	{
		_generatedId++;
		return OperationID(_generatedId);
	}
}
