//g++ test30-main.cpp test30-static-member.cpp -o t30
#include "test30-static-member.h"
	
int A::B::seq = 0;

int main()
{
/*
	A a;
	std::cout << a.getStatic() << std::endl;
	a.addStatic();
	std::cout << a.getStatic() << std::endl;
*/
	A a2;
	a2.testB();

	return 0;
}
