#include "mybuf.potato.h"

size_t package1::class1::SerializeToString(std::string& str)
{
	size_t str_len = 0;
	SerializeToCString(str_len);
	str = std::string(_c_data, str_len);

	return str_len;
}

const char* package1::class1::SerializeToCString(size_t& len)
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

int package1::class1::SerializeFromString(const std::string& str)
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

int package1::class1::SerializeFromCString(const char* c_str, size_t len)
{
	std::string str(c_str, len);
	return SerializeFromString(str);
}

ADD_MSG_ACHIEVE_HAVE_NAMESPACE(P_INT8,id1, class1, package1)

ADD_MSG_ACHIEVE_HAVE_NAMESPACE(P_INT16,id2, class1, package1)

ADD_MSG_ACHIEVE_HAVE_NAMESPACE(P_INT32,id3, class1, package1)

ADD_MSG_ACHIEVE_HAVE_NAMESPACE(P_INT64,id4, class1, package1)

ADD_MSG_ACHIEVE_HAVE_NAMESPACE(P_UINT8,id5, class1, package1)

ADD_MSG_ACHIEVE_HAVE_NAMESPACE(P_UINT16,id6, class1, package1)

ADD_MSG_ACHIEVE_HAVE_NAMESPACE(P_UINT32,id7, class1, package1)

ADD_MSG_ACHIEVE_HAVE_NAMESPACE(P_UINT64,id8, class1, package1)

ADD_MSG_ACHIEVE_HAVE_NAMESPACE(bool,is_bool, class1, package1)

ADD_MSG_ACHIEVE_HAVE_NAMESPACE(float,is_float, class1, package1)

ADD_MSG_ACHIEVE_HAVE_NAMESPACE(double,is_double, class1, package1)

ADD_MSG_ENUM_ACHIEVE_HAVE_NAMESPACE(enum1, is_enum, class1, package1)

ADD_MSG_STRING_ACHIEVE_HAVE_NAMESPACE(is_string, class1, package1)

size_t package1::class2::SerializeToString(std::string& str)
{
	size_t str_len = 0;
	SerializeToCString(str_len);
	str = std::string(_c_data, str_len);

	return str_len;
}

const char* package1::class2::SerializeToCString(size_t& len)
{
	len = OVERALL_STR_LENGTH(is_string.size(), is_string1.size());
	_c_data = new char[len];

	ADD_TO_CSTR(id1);
	ADD_TO_CSTR(id11);
	ADD_TO_CSTR(id2);
	ADD_TO_CSTR(id12);
	ADD_TO_CSTR(id3);
	ADD_TO_CSTR(id13);
	ADD_TO_CSTR(id4);
	ADD_TO_CSTR(id14);
	ADD_TO_CSTR(id5);
	ADD_TO_CSTR(id15);
	ADD_TO_CSTR(id6);
	ADD_TO_CSTR(id16);
	ADD_TO_CSTR(id7);
	ADD_TO_CSTR(id17);
	ADD_TO_CSTR(id8);
	ADD_TO_CSTR(id18);
	ADD_TO_CSTR(is_bool);
	ADD_TO_CSTR(is_bool1);
	ADD_TO_CSTR(is_float);
	ADD_TO_CSTR(is_float1);
	ADD_TO_CSTR(is_double);
	ADD_TO_CSTR(is_double1);
	STR_ADD_TO_CSTR(is_string);
	STR_ADD_TO_CSTR(is_string1);

	_add_len = 0;
	return _c_data;
}

int package1::class2::SerializeFromString(const std::string& str)
{
	POP_FROM_STR(id1);
	POP_FROM_STR(id11);
	POP_FROM_STR(id2);
	POP_FROM_STR(id12);
	POP_FROM_STR(id3);
	POP_FROM_STR(id13);
	POP_FROM_STR(id4);
	POP_FROM_STR(id14);
	POP_FROM_STR(id5);
	POP_FROM_STR(id15);
	POP_FROM_STR(id6);
	POP_FROM_STR(id16);
	POP_FROM_STR(id7);
	POP_FROM_STR(id17);
	POP_FROM_STR(id8);
	POP_FROM_STR(id18);
	POP_FROM_STR(is_bool);
	POP_FROM_STR(is_bool1);
	POP_FROM_STR(is_float);
	POP_FROM_STR(is_float1);
	POP_FROM_STR(is_double);
	POP_FROM_STR(is_double1);
	STR_POP_FROM_STR(is_string);
	STR_POP_FROM_STR(is_string1);

	IS_STR_ERR();
	return 0;
}

int package1::class2::SerializeFromCString(const char* c_str, size_t len)
{
	std::string str(c_str, len);
	return SerializeFromString(str);
}

ADD_MSG_ACHIEVE_HAVE_NAMESPACE(P_INT8,id1, class2, package1)

ADD_MSG_ACHIEVE_HAVE_NAMESPACE(P_INT8,id11, class2, package1)

ADD_MSG_ACHIEVE_HAVE_NAMESPACE(P_INT16,id2, class2, package1)

ADD_MSG_ACHIEVE_HAVE_NAMESPACE(P_INT16,id12, class2, package1)

ADD_MSG_ACHIEVE_HAVE_NAMESPACE(P_INT32,id3, class2, package1)

ADD_MSG_ACHIEVE_HAVE_NAMESPACE(P_INT32,id13, class2, package1)

ADD_MSG_ACHIEVE_HAVE_NAMESPACE(P_INT64,id4, class2, package1)

ADD_MSG_ACHIEVE_HAVE_NAMESPACE(P_INT64,id14, class2, package1)

ADD_MSG_ACHIEVE_HAVE_NAMESPACE(P_UINT8,id5, class2, package1)

ADD_MSG_ACHIEVE_HAVE_NAMESPACE(P_UINT8,id15, class2, package1)

ADD_MSG_ACHIEVE_HAVE_NAMESPACE(P_UINT16,id6, class2, package1)

ADD_MSG_ACHIEVE_HAVE_NAMESPACE(P_UINT16,id16, class2, package1)

ADD_MSG_ACHIEVE_HAVE_NAMESPACE(P_UINT32,id7, class2, package1)

ADD_MSG_ACHIEVE_HAVE_NAMESPACE(P_UINT32,id17, class2, package1)

ADD_MSG_ACHIEVE_HAVE_NAMESPACE(P_UINT64,id8, class2, package1)

ADD_MSG_ACHIEVE_HAVE_NAMESPACE(P_UINT64,id18, class2, package1)

ADD_MSG_ACHIEVE_HAVE_NAMESPACE(bool,is_bool, class2, package1)

ADD_MSG_ACHIEVE_HAVE_NAMESPACE(bool,is_bool1, class2, package1)

ADD_MSG_ACHIEVE_HAVE_NAMESPACE(float,is_float, class2, package1)

ADD_MSG_ACHIEVE_HAVE_NAMESPACE(float,is_float1, class2, package1)

ADD_MSG_ACHIEVE_HAVE_NAMESPACE(double,is_double, class2, package1)

ADD_MSG_ACHIEVE_HAVE_NAMESPACE(double,is_double1, class2, package1)

ADD_MSG_STRING_ACHIEVE_HAVE_NAMESPACE(is_string, class2, package1)

ADD_MSG_STRING_ACHIEVE_HAVE_NAMESPACE(is_string1, class2, package1)

