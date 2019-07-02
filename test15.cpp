#include <iostream>

using namespace std;

class A {
public:
    virtual void fun() = 0;
    A():i(1) {}
    int i;
};

class B:public A {
public:
//    B():i(0) {}
//    int i;
    void fun() { cout << "class B: " << i << endl; }
}; 

int main()
{
    B b;
    b.fun();
    
    return 0;
}
