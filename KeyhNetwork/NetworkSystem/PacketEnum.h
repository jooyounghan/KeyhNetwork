#pragma once

namespace keyh
{
	KEYH_REFLECT_ENUM
	enum class FieldType : uint8
	{
		Int,
		Uint,
		Float,
		Double,
		ManualFloat,
		Group,
		Count,
	};
	constexpr size_t kFieldTypeCount = static_cast<size_t>(FieldType::Count);
	static_assert(kFieldTypeCount == 6, "FieldType count mismatch");

}
#include "generated/PacketEnum.reflect_generated.inl"
