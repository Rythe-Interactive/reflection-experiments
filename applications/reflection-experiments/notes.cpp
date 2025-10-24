
#include <rsl/containers>

struct reflection_member;

struct reflection_type
{
	array_view<reflection_member> members;
};

struct reflection_member
{
	reflection_type type;
	rsl::string_view name;
	...
};

class serializer
{
	virtual serializer& start_object(rsl::string_view name, rsl::id_type typeId);

	template<typename T>
	serializer& add_member(rsl::string_view name, const T& data);

	virtual serializer& add_member_enum(rsl::string_view name, rsl::int64 data, array_view<enum_values> enumDefinition);

protected:
	virtual serializer& add_member_integer(rsl::string_view name, rsl::int64 data);
	virtual serializer& add_member_unsigned_integer(rsl::string_view name, rsl::uint64 data);
	virtual serializer& add_member_float(rsl::string_view name, rsl::float64 data);
	virtual serializer& add_member_string(rsl::string_view name, rsl::string_view data);
};

struct memory_block
{
	rsl::byte* data;
	rsl::size_type size;
};

enum struct MyEnum
{
	a,b,c
};

struct MyStruct
{
	int value;
	MyEnum enumVal;
	bool Foo();
};

class editor_ui_serializer : public serializer {};

bool serialize_object(serializer& serial, memory_block src, rsl::id_type typeId);

// generated:

void serialize_MyEnum(serializer& serial, memory_block src)
{
	MyEnum* srcObject = reinterpret_cast<MyEnum*>(src.data);

	array<enum_values> enumDef = {
		{ "a", static_cast<rsl::int64>(MyEnum::a) },
		{ "b", static_cast<rsl::int64>(MyEnum::b) },
		{ "c", static_cast<rsl::int64>(MyEnum::c) }
	}

	serial.add_member_enum("MyEnum", *srcObject, enumDef);
}

void serialize_MyStruct(serializer& serial, memory_block src)
{
	if (editor_ui_serializer* editorUI = dynamic_cast<editor_ui_serializer*>(&serial); editorUI)
	{
		// this is editor ui
		editorUi->add_button();
	}
	else
	{
		// this is file serialization or anything else
		MyStruct* srcObject = reinterpret_cast<MyStruct*>(src.data);

		serial.start_object("MyStruct", 14736435468364554ull)
			.add_member("value", srcObject->value)
			.add_member("enumVal", srcObject->enumVal)
			.add_function("Foo", srcObject, &MyStruct::Foo);
	}
}

int main()
{
	editor_ui_serializer editorUISerializer;
	MyStruct value;
	serialize_object(editorUISerializer, memory_block{ &value, sizeof(MyStruct) }, 14736435468364554ull);

	return 0;
}

void serialize(reflector refl)
{
	serializer serial;
	for (auto member : refl.member_variables())
	{
		if (member.is_integer() && member.name == "noPleaseDont")
		{
			continue;
		}

		serial.add_member(member);
	}
}

reflector.serialize(serializer);