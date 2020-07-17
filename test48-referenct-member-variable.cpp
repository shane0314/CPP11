#include <iostream>
#pragma  pack ( 1 )

class A
{
    int a;
    int b;
    int c;
};

class B
{
    A a;
};

class C
{
public:
    C(A&& ra_) =delete;
    C(A& a_) : a(a_) {}
private:
    A& a;
};

int main()
{
    int i;
    int & ri=i;
    double d;
    double & rd=d;
    A a=A();
    A & ra=a;
    C c(a);
//    C c1(std::move(a));
    std::cout << "sizeof A = " << sizeof(A) << std::endl;
    std::cout << "sizeof B = " << sizeof(B) << std::endl;
    std::cout << "sizeof C = " << sizeof(C) << std::endl;
    std::cout << "sizeof c = " << sizeof(c) << std::endl;
    
    std::cout << "size of pointer = " << sizeof(void*) << std::endl;
    std::cout << "size of int& = " << sizeof(int&) << std::endl;
    std::cout << "size of A& = " << sizeof(A&) << std::endl;
    return 0;
}

