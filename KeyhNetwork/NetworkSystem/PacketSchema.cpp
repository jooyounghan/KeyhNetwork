#include "NetworkSystemPch.h"
#include "PacketSchema.h"

namespace keyh
{
	KEYH_REFLECT_DEFINE_BODY(PacketField)

	bool PacketField::validatePacketField() const
	{
		if (_fieldType == FieldType::Group)
		{
			if (_childFields.empty())
				return false;

			for (const auto& childField : _childFields)
			{
				if (childField.validatePacketField() == false)
					return false;
			}
		}
		else if (_byteSize == 0 || !_childFields.empty())
		{
			return false;
		}
		return true;
	}

	KEYH_REFLECT_DEFINE_BODY(PacketSchema)
}
#include "generated/PacketSchema.reflect_generated.cpp.inl"
