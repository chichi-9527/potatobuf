
#include "mybuf.h"
#include "mybuf.potato.h"

#include <iostream>

int main()
{
	package1::class1* a = new package1::class1();
	a->set_id1(1);
	a->set_is_string("wodetianÎÒµÄÌì");
	a->set_id2(2);
	a->set_id3(3);
	a->set_id4(4);
	a->set_id5(5);
	a->set_id6(6);
	a->set_id7(7);
	a->set_id8(8);
	a->set_is_bool(true);
	a->set_is_double(5.12);
	a->set_is_float(4.32f);
	a->set_is_enum(package1::class1::ENUM_2);

	//std::string result;
	//size_t size = a->SerializeToString(result);
	size_t size = 0;
	char* c_result = a->SerializeToCString(size);
	std::string result(c_result, size);

	std::string result_error("asdwad");

	package1::class1* b = new package1::class1();
	if (-1 == b->SerializeFromString(result))
	{
		std::cout << b->get_error();
	}

	std::cout << (int)b->get_id1() << "\n";
	std::cout << b->get_id2() << "\n";
	std::cout << b->get_id3() << "\n";
	std::cout << b->get_id4() << "\n";
	std::cout << (unsigned int)b->get_id5() << "\n";
	std::cout << b->get_id6() << "\n";
	std::cout << b->get_id7() << "\n";
	std::cout << b->get_id8() << "\n";
	std::cout << b->get_is_enum() << "\n";

	std::cout << b->get_is_bool() << "\n";
	std::cout << b->get_is_float() << "\n";
	std::cout << b->get_is_double() << "\n";
	std::cout << b->get_is_string() << "\n";


	return 0;
}

