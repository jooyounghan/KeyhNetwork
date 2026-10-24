#pragma once
#include "PacketEnum.h"

namespace keyh
{
	struct REFLECTIVE(PacketField)
	{
		KEYH_REFLECT_DECLARE_BODY(PacketField);

	REFLECT_PRIVATE:
		KEYH_REFLECT_PROPERTY(PropertyName = "FieldName")
		FlyweightStringA _name = 0;

		KEYH_REFLECT_PROPERTY(PropertyName = "LocalOffset", Default = 0)
		uint8 _localOffset = 0;

		KEYH_REFLECT_PROPERTY(PropertyName = "FieldType", Default = FieldType::Group)
		FieldType _fieldType = FieldType::Group;

		KEYH_REFLECT_PROPERTY(PropertyName = "ByteSize", Default = 0)
		uint16 _byteSize = 0;

		KEYH_REFLECT_PROPERTY(PropertyName = "ChildFields")
		Vector<PacketField> _childFields;

	public:
		bool validatePacketField() const;
	};

	class REFLECTIVE(PacketSchema)
	{
		KEYH_REFLECT_DECLARE_BODY(PacketSchema);

	REFLECT_PRIVATE:
		KEYH_REFLECT_PROPERTY(PropertyName = "SchemaName")
		FlyweightStringA _schemaName;

		KEYH_REFLECT_PROPERTY(PropertyName = "Fields")
		Vector<PacketField> _fields;
	};
}

#include "generated/PacketSchema.reflect_generated.inl"
