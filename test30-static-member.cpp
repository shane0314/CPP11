#include "test30-static-member.h"

void A::testB() {
		B b[2];
		b[0].addStatic();
		std::cout << b[0].getStatic() << std::endl;
		b[1].addStatic();
		std::cout << b[1].getStatic() << std::endl;
	}
	
int A::B::getStatic() { return seq; }
void A::B::addStatic() { seq++; }
	
//int A::B::seq = 0;
