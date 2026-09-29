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
	};

	struct REFLECTIVE(PacketField)
	{
		KEYH_REFLECT_DECLARE_BODY(PacketField);
		
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
	};

	class REFLECTIVE(PacketSchema)
	{
		KEYH_REFLECT_DECLARE_BODY(PacketSchema);

	private:
		KEYH_REFLECT_PROPERTY(PropertyName = "SchemaName")
		FlyweightStringA _schemaName;

		KEYH_REFLECT_PROPERTY(PropertyName = "Fields")
		Vector<PacketField> _fields;
	};
}

#include "generated/PacketSchema.reflect_generated.inl"
