#include <iostream>
#include <typeinfo>

template<typename T1, typename T2>
T1 foo(T2 var)
{
	
	return var+1;
}

int main()
{
	//std::cout << foo<int, int>(1) << std::endl;
	//std::cout << foo<double, int>(1) << std::endl;
	
	auto a = foo<int>(1);
	auto b = foo<double>(2);
	std::cout << "type:" << typeid(a).name() << " value:" << a << std::endl;
	std::cout << "type:" << typeid(b).name() << " value:" << b << std::endl;
}
