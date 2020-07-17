#include <iostream>
#include <string>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

using namespace std;

class A
{
public:
    inline virtual void init()
    {
        cout << "A::init()" << endl;
    }
    inline virtual void func()
    {
        cout << "A::func()" << endl;
    }
};

class Base : public A
{
public:
    void init() override
    {
        cout << "Base::init()" << endl;
    }
    void func() override
    {
        cout << "Base::func()" << endl;
        //Base::init();
        init();
    }
};

class Derived
    : public Base
{
public:
    inline void init() override
    {
        cout << "Derived::init() {" << endl;
        Base::init();
        cout << "} Derived::init()" << endl;
    }
    inline void func() override
    {
        cout << "inline Derived::func() {" << endl;
        A::func();
        cout << "} Derived::func()" << endl;
    }

};

int main()
{
    Derived obj;
    obj.func();

    A *pA = &obj;
    pA->func();
}
