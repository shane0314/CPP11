#include <iostream>
#include <string.h>

using namespace std;

class A
{
public:
    static void setA( int i );
    static int getA();
private:
    static int a;
};

int A::a = 0;
void A::setA( int i )
{
    a = i;
}
int A::getA()
{
    return a;
}

int main()
{
    A::setA( 1 );
    cout << "A::a = " << A::getA() << endl;
}
