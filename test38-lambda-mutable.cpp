#include <iostream>

using namespace std;

int w = 5;

void foo(int);


int main()
{
    int xx = 1;
    auto f = [xx]() mutable { cout << ++xx << endl; };
    cout << "after lambda create, before call, x =" << xx << endl;    
    xx = 0;
    f();
    cout << "after call, x =" << xx << endl;    

    foo(2);

    cout << "===test lambda as return value===" << endl;
    cout << [&](){ return xx+10; }() << endl;

    return 0;
}

void foo( int x )
{
    int y = 3;
    static int z = 4;
    auto f = [x,y]() { cout << x << "," << y << "," << z << "," << w << endl; };
    f();
}
