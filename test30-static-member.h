#include <iostream>

class A
{
public:
	int getStatic() { return B::seq; }
	void addStatic() { B::seq++; }
	void testB();
	
private:
	struct B
	{
		int getStatic();
		void addStatic();
		static int seq;
		int num;
	};		
	
	B bb[10];
};

//must be defined in cpp file
//int A::B::seq = 0;
