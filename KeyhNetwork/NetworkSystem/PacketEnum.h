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
}