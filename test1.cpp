#include "iostream"
using namespace std;

int ca_var =1;

template <typename T>
void swap(T &a, T &b)
{
    T tmp = a;
    a = b;
    b = tmp;
    a++;
    b++;
}

void TestSwap()
{
    int iA = 10;
    int iB = 20;
    double dC = 1.1;
    double dD = 2.1;

    //::swap(iA, iB);
    cout << iA << "," << iB << endl;

    std::swap(iA, iB);
    cout << iA << "," << iB << endl;

    std::swap(dC, dD);
    cout << dC << "," << dD << endl;
}

class CA {
public:	
	int ca_var;
	CA():ca_var(0) {}
	void f() {
		 cout << "::ca_var = " << ::ca_var << endl; 

	 	cout << "ca_var = " << ca_var << endl; }

};

//int ca_var=2;

int main()
{
    TestSwap();

	CA mca;
	mca.f();

    return 0;
}
