
#include "mybuf.h"
#include "potatobuf_c/test/mybuf.potato.h"

#define INVENT_ITEXT_USE_WSTRING
#include "IneventText/IText.h"

#include <iostream>

#ifdef _WIN32
#include <Windows.h>
#endif

int main()
{
#ifdef _WIN32
	SetConsoleOutputCP(CP_UTF8);
#endif

	package1::class2* a = new package1::class2();
	a->set_id1(1);
	a->set_is_string(u8"wodetian我的天");
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
	//a->set_is_enum(package1::class1::enum1::ENUM_2);

	//std::string result;
	//size_t size = a->SerializeToString(result);
	size_t size = 0;
	const char* c_result = a->SerializeToCString(size);
	std::string result(c_result, size);

	std::string result_error("asdwad");

	package1::class2* b = new package1::class2();
	if (-1 == b->SerializeFromCString(result.c_str(), result.size()))
	{
		std::cout << b->get_error();
		return -1;
	}

	std::cout << (int)b->get_id1() << "\n";
	std::cout << b->get_id2() << "\n";
	std::cout << b->get_id3() << "\n";
	std::cout << b->get_id4() << "\n";
	std::cout << (unsigned int)b->get_id5() << "\n";
	std::cout << b->get_id6() << "\n";
	std::cout << b->get_id7() << "\n";
	std::cout << b->get_id8() << "\n";
	//std::cout << b->get_is_enum() << "\n";

	std::cout << b->get_is_bool() << "\n";
	std::cout << b->get_is_float() << "\n";
	std::cout << b->get_is_double() << "\n";
	std::cout << b->get_is_string() << "\n";


	/////////////////////////////////////////////////

	std::string str(u8"1234567,qbcdefg,我的天，是中文！");
	std::wstring wstr(L"1234567,qbcdefg,我的天，是中文！");
	std::cout << str << "\n";
	INVENT::IText text(wstr);
	INVENT::IText text2 = std::move(text);

	std::string utf8_str;
	text.ToUtf8(utf8_str);

	std::cout << utf8_str << "\n";
	text2.ToUtf8(utf8_str);

	std::cout << utf8_str << "\n";


	return 0;
}

