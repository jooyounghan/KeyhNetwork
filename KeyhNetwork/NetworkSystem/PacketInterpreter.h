#pragma once
#include "PacketEnum.h"

namespace keyh
{
	class REFLECTIVE(PacketInterpreter)
	{
		KEYH_REFLECT_DECLARE_BODY(PacketInterpreter);

	private:
		StaticArray<int, kFieldTypeCount> _fieldInterpreters;
	};
}
#include "generated/PacketInterpreter.reflect_generated.inl"
