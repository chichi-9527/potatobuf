#ifndef _mybuf_potato_h
#define _mybuf_potato_h


#include "stink_potatobuf/stink_potatobuf.h"


namespace package1
{

class class1 final : public PotatoBuffer::_potatobuf
{
public:
	class1() :
		id1(0),
		id2(0),
		id3(0),
		id4(0),
		id5(0),
		id6(0),
		id7(0),
		id8(0),
		is_bool(false),
		is_float(0.0f),
		is_double(0.0),
		is_enum(enum1(0))
	{
		INIT_MSG_NUM(1,1,1,1,1,1,1,1,1,1,1,1,1);
	}

	~class1(){}

	size_t SerializeToString(std::string& str) override;
	char* SerializeToCString(size_t& len) override;
	int SerializeFromString(std::string& str) override;
	int SerializeFromCString(char* c_str, size_t len) override;

	//enum1
	enum enum1 : int {
		ENUM_1 = 0,
		ENUM_2 = 2,
		ENUM_3
	};


	//enum2
	enum enum2 : int {
		ENUM_4 = 0,
		ENUM_5 = 2,
		ENUM_6
	};

	//id1
	//None
	ADD_MSG(P_INT8 ,id1)

	//id2
	//None
	ADD_MSG(P_INT16 ,id2)

	//id3
	//None
	ADD_MSG(P_INT32 ,id3)

	//id4
	//None
	ADD_MSG(P_INT64 ,id4)

	//id5
	//None
	ADD_MSG(P_UINT8 ,id5)

	//id6
	//None
	ADD_MSG(P_UINT16 ,id6)

	//id7
	//None
	ADD_MSG(P_UINT32 ,id7)

	//id8
	//None
	ADD_MSG(P_UINT64 ,id8)

	//is_bool
	//None
	ADD_MSG(bool ,is_bool)

	//is_float
	//None
	ADD_MSG(float ,is_float)

	//is_double
	//None
	ADD_MSG(double ,is_double)

	//is_enum
	//None
	ADD_MSG_ENUM(enum1, is_enum)

	//is_string
	//None
	ADD_MSG_STRING(is_string)

	private:
		P_INT8 id1;
		P_INT16 id2;
		P_INT32 id3;
		P_INT64 id4;
		P_UINT8 id5;
		P_UINT16 id6;
		P_UINT32 id7;
		P_UINT64 id8;
		bool is_bool;
		float is_float;
		double is_double;
		enum1 is_enum;
		std::string is_string;
}; // class class1

class class2 final : public PotatoBuffer::_potatobuf
{
public:
	class2() :
		id1(0),
		id11(0),
		id2(0),
		id12(0),
		id3(0),
		id13(0),
		id4(0),
		id14(0),
		id5(0),
		id15(0),
		id6(0),
		id16(0),
		id7(0),
		id17(0),
		id8(0),
		id18(0),
		is_bool(false),
		is_bool1(false),
		is_float(0.0f),
		is_float1(0.0f),
		is_double(0.0),
		is_double1(0.0)
	{
		INIT_MSG_NUM(2,2,2,2,2,2,2,2,2,2,2,0,2);
	}

	~class2(){}

	size_t SerializeToString(std::string& str) override;
	char* SerializeToCString(size_t& len) override;
	int SerializeFromString(std::string& str) override;
	int SerializeFromCString(char* c_str, size_t len) override;
	//id1
	//None
	ADD_MSG(P_INT8 ,id1)

	//id11
	//None
	ADD_MSG(P_INT8 ,id11)

	//id2
	//None
	ADD_MSG(P_INT16 ,id2)

	//id12
	//None
	ADD_MSG(P_INT16 ,id12)

	//id3
	//None
	ADD_MSG(P_INT32 ,id3)

	//id13
	//None
	ADD_MSG(P_INT32 ,id13)

	//id4
	//None
	ADD_MSG(P_INT64 ,id4)

	//id14
	//None
	ADD_MSG(P_INT64 ,id14)

	//id5
	//None
	ADD_MSG(P_UINT8 ,id5)

	//id15
	//None
	ADD_MSG(P_UINT8 ,id15)

	//id6
	//None
	ADD_MSG(P_UINT16 ,id6)

	//id16
	//None
	ADD_MSG(P_UINT16 ,id16)

	//id7
	//None
	ADD_MSG(P_UINT32 ,id7)

	//id17
	//None
	ADD_MSG(P_UINT32 ,id17)

	//id8
	//None
	ADD_MSG(P_UINT64 ,id8)

	//id18
	//None
	ADD_MSG(P_UINT64 ,id18)

	//is_bool
	//None
	ADD_MSG(bool ,is_bool)

	//is_bool1
	//None
	ADD_MSG(bool ,is_bool1)

	//is_float
	//None
	ADD_MSG(float ,is_float)

	//is_float1
	//None
	ADD_MSG(float ,is_float1)

	//is_double
	//None
	ADD_MSG(double ,is_double)

	//is_double1
	//None
	ADD_MSG(double ,is_double1)

	//is_string
	//None
	ADD_MSG_STRING(is_string)

	//is_string1
	//None
	ADD_MSG_STRING(is_string1)

	private:
		P_INT8 id1;
		P_INT8 id11;
		P_INT16 id2;
		P_INT16 id12;
		P_INT32 id3;
		P_INT32 id13;
		P_INT64 id4;
		P_INT64 id14;
		P_UINT8 id5;
		P_UINT8 id15;
		P_UINT16 id6;
		P_UINT16 id16;
		P_UINT32 id7;
		P_UINT32 id17;
		P_UINT64 id8;
		P_UINT64 id18;
		bool is_bool;
		bool is_bool1;
		float is_float;
		float is_float1;
		double is_double;
		double is_double1;
		std::string is_string;
		std::string is_string1;
}; // class class2

} // namespace package1

#endif //mybuf_potato_h
