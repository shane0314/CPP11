#include <iostream>
using namespace std;

class Base 
{
public:
	Base() { cout << "Base()" << endl; }
	Base(const Base&) { cout << "Base(const Base&)" << endl; }
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
	Derived() { cout << "Derived()" << endl; }
	Derived(const Derived&) { cout << "Derived(const Derived&)" << endl; }
	Derived(const Base&) { cout << "Derived(const Base&)" << endl; }
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
	DDerived() { cout << "DDrived()" << endl; }
	void vf()
	{
		cout<<"vf() of DD"<<endl;
	}
};

int main()
{
	Derived d;
	cout << "Object: ";
	Base b = (Base)d;
	cout << "Reference: ";
	Base *pb = &d;
	cout << "Pointer: ";
	Base &bb = d;
	cout << "convert from Base to Derived:";
	Derived db = (Derived)b;
	cout << "=============" << endl;
	b.vf();
	pb->vf();
	bb.vf();
	cout << "=============" << endl;
	DDerived dd;
	Derived *pd = &dd;
	pd->vf();
	pd->f();
	
	return 0;
}
