#pragma once




#include "stink_potatobuf/stink_potatobuf.h"


namespace package2
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
		is_enum(_enum1(0))
	{
		INIT_MSG_NUM(1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1);
	}

	~class1()
	{

	}

	size_t SerializeToString(std::string& str) override;
	const char* SerializeToCString(size_t& len) override;
	int SerializeFromString(const std::string& str) override;
	int SerializeFromCString(const char* c_str, size_t len) override;

	//enum1
	enum _enum1 : P_INT64 {
		ENUM_1 = 0,
		ENUM_2 = 2,
		ENUM_3
	};


	//id1
	/*P_INT8 get_id1();
	void set_id1(P_INT8 value);
	void clear_id1();*/
	ADD_MSG(P_INT8 , id1)

	//id2
	P_INT16 get_id2();
	void set_id2(P_INT16 value);
	void clear_id2();

	//id3
	P_INT32 get_id3();
	void set_id3(P_INT32 value);
	void clear_id3();

	//id4
	P_INT64 get_id4();
	void set_id4(P_INT64 value);
	void clear_id4();

	//id5
	P_UINT8 get_id5();
	void set_id5(P_UINT8 value);
	void clear_id5();

	//id6
	P_UINT16 get_id6();
	void set_id6(P_UINT16 value);
	void clear_id6();

	//id7
	P_UINT32 get_id7();
	void set_id7(P_UINT32 value);
	void clear_id7();

	//id8
	P_UINT64 get_id8();
	void set_id8(P_UINT64 value);
	void clear_id8();

	//is_bool
	//bool get_is_bool();
	//void set_is_bool(bool value);
	//void clear_is_bool();
	ADD_MSG(bool, is_bool)

	//is_float
	float get_is_float();
	void set_is_float(float value);
	void clear_is_float();

	//is_double
	double get_is_double();
	void set_is_double(double value);
	void clear_is_double();

	//is_string
	/*const std::string& get_is_string();
	void set_is_string(const std::string& value);
	void set_is_string(const char* value);
	void set_is_string(const char* value, size_t size);
	void clear_is_string();*/
	ADD_MSG_STRING(is_string)

	//is_enum
	/*_enum1 get_is_enum();
	void set_is_enum(_enum1 value);
	void clear_is_enum();*/
	ADD_MSG_ENUM(_enum1, is_enum)


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
	std::string is_string;

	_enum1 is_enum;
};

} // namespace package1