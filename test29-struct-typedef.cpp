#include <iostream>
#include <type_traits>
#include <typeinfo>

namespace bb
{
struct test_struct
{
	char a;
	int i;
};
struct test_struct_2
{
	char a;
	int i;
	double d;
};
}

int main()
{
	const bool flag = true;

	using  AAA = typename std::conditional<
		flag == true,
		bb::test_struct,
		bb::test_struct_2 >::type;
	
	typedef std::conditional<
		!flag,
		bb::test_struct,
		bb::test_struct_2 >::type  BBB;
		
	AAA sa;
	sa.a = 'a';
	BBB sb;
	sb.a = 'b';
	
	std::cout << typeid(sa).name() << std::endl;
	std::cout << typeid(sb).name() << std::endl;

	typedef const char constchar_t;
	constchar_t cc = 'c';

	typedef int int_t;
	const int_t i=0;
	//i = 1;

	return 0;
}
