#include <iostream>
using namespace std;

class Base 
{
public:
	void f()
	{
		cout<<"f() of B"<<endl;
	}
	virtual void vf()
	{
		cout<<"vf() of B"<<endl;
	}
};

class Derived: public Base
{
public:
	void f()
	{
		cout<<"f() of D"<<endl;
	}
	void vf()
	{
		cout<<"vf() of D"<<endl;
	}
};

class DDerived: public Derived
{
public:
	void vf()
	{
		cout<<"vf() of DD"<<endl;
	}
};

int main()
{
	Derived d;
	Base b = (Base)d;
	Base *pb = &d;
	Base &bb = d;
	
	b.vf();
	pb->vf();
	bb.vf();
	
	DDerived dd;
	Derived *pd = &dd;
	pd->vf();
	pd->f();
	
	return 0;
}
