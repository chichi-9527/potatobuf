#include "mybuf.h"

size_t package2::class1::SerializeToString(std::string& str)
{
	size_t str_len = 0;
	SerializeToCString(str_len);
	str = std::string(_c_data, str_len);

	return str_len;
}

const char* package2::class1::SerializeToCString(size_t& len)
{
	len = OVERALL_STR_LENGTH(is_string.size());
	_c_data = new char[len];

	ADD_TO_CSTR(id1);
	ADD_TO_CSTR(id2);
	ADD_TO_CSTR(id3);
	ADD_TO_CSTR(id4);
	ADD_TO_CSTR(id5);
	ADD_TO_CSTR(id6);
	ADD_TO_CSTR(id7);
	ADD_TO_CSTR(id8);
	ADD_TO_CSTR(is_bool);
	ADD_TO_CSTR(is_float);
	ADD_TO_CSTR(is_double);
	ADD_TO_CSTR(is_enum);

	STR_ADD_TO_CSTR(is_string);

	_add_len = 0;
	return _c_data;
}

int package2::class1::SerializeFromString(const std::string& str)
{
	POP_FROM_STR(id1);
	POP_FROM_STR(id2);
	POP_FROM_STR(id3);
	POP_FROM_STR(id4);
	POP_FROM_STR(id5);
	POP_FROM_STR(id6);
	POP_FROM_STR(id7);
	POP_FROM_STR(id8);
	POP_FROM_STR(is_bool);
	POP_FROM_STR(is_float);
	POP_FROM_STR(is_double);
	POP_FROM_STR(is_enum);

	STR_POP_FROM_STR(is_string);
	
	IS_STR_ERR();
	return 0;
}

int package2::class1::SerializeFromCString(const char* c_str, size_t len)
{
	std::string str(c_str, len);
	return SerializeFromString(str);
}

//P_INT8 package1::class1::get_id1()
//{
//	return id1;
//}
//
//void package1::class1::set_id1(P_INT8 value)
//{
//	id1 = value;
//}
//
//void package1::class1::clear_id1()
//{
//	id1 = 0;
//}

ADD_MSG_ACHIEVE_HAVE_NAMESPACE(P_INT8, id1, class1, package2)

P_INT16 package2::class1::get_id2()
{
	return id2;
}

void package2::class1::set_id2(P_INT16 value)
{
	id2 = value;
}

void package2::class1::clear_id2()
{
	id1 = 0;
}

P_INT32 package2::class1::get_id3()
{
	return id3;
}

void package2::class1::set_id3(P_INT32 value)
{
	id3 = value;
}

void package2::class1::clear_id3()
{
	id3 = 0;
}

P_INT64 package2::class1::get_id4()
{
	return id4;
}

void package2::class1::set_id4(P_INT64 value)
{
	id4 = value;
}

void package2::class1::clear_id4()
{
	id4 = 0;
}

P_UINT8 package2::class1::get_id5()
{
	return id5;
}

void package2::class1::set_id5(P_UINT8 value)
{
	id5 = value;
}

void package2::class1::clear_id5()
{
	id5 = 0;
}

P_UINT16 package2::class1::get_id6()
{
	return id6;
}

void package2::class1::set_id6(P_UINT16 value)
{
	id6 = value;
}

void package2::class1::clear_id6()
{
	id6 = 0;
}

P_UINT32 package2::class1::get_id7()
{
	return id7;
}

void package2::class1::set_id7(P_UINT32 value)
{
	id7 = value;
}

void package2::class1::clear_id7()
{
	id7 = 0;
}

P_UINT64 package2::class1::get_id8()
{
	return id8;
}

void package2::class1::set_id8(P_UINT64 value)
{
	id8 = value;
}

void package2::class1::clear_id8()
{
	id8 = 0;
}

//bool package1::class1::get_is_bool()
//{
//	return is_bool;
//}
//
//void package1::class1::set_is_bool(bool value)
//{
//	is_bool = value;
//}
//
//void package1::class1::clear_is_bool()
//{
//	is_bool = false;
//}
ADD_MSG_ACHIEVE_HAVE_NAMESPACE(bool, is_bool, class1, package2)

float package2::class1::get_is_float()
{
	return is_float;
}

void package2::class1::set_is_float(float value)
{
	is_float = value;
}

void package2::class1::clear_is_float()
{
	is_float = 0.0f;
}

double package2::class1::get_is_double()
{
	return is_double;
}

void package2::class1::set_is_double(double value)
{
	is_double = value;
}

void package2::class1::clear_is_double()
{
	is_double = 0.0;
}

//const std::string& package1::class1::get_is_string()
//{
//	return is_string;
//}
//
//void package1::class1::set_is_string(const std::string& value)
//{
//	is_string = value;
//}
//
//void package1::class1::set_is_string(const char* value)
//{
//	is_string = value;
//}
//
//void package1::class1::set_is_string(const char* value, size_t size)
//{
//	is_string.resize(size);
//	for (size_t i = 0; i < size; ++i)
//	{
//		is_string[i] = value[i];
//	}
//}
//
//void package1::class1::clear_is_string()
//{
//	is_string.clear();
//}

ADD_MSG_STRING_ACHIEVE_HAVE_NAMESPACE(is_string, class1, package2)

//package1::class1::_enum1 package1::class1::get_is_enum()
//{
//	return is_enum;
//}
//
//void package1::class1::set_is_enum(_enum1 value)
//{
//	is_enum = value;
//}
//
//void package1::class1::clear_is_enum()
//{
//	is_enum = package1::class1::_enum1(0);
//}

ADD_MSG_ENUM_ACHIEVE_HAVE_NAMESPACE(_enum1, is_enum, class1, package2)
