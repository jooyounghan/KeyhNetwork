#pragma once
#include "PacketEnum.h"

namespace keyh
{
	class REFLECTIVE(PacketInterpreter)
	{
		KEYH_REFLECT_DECLARE_BODY(PacketInterpreter);

	private:
		StaticArray<int, static_cast<size_t>(FieldType::Count)> _fieldInterpreters;
	};
}
