#include <memory>
#include <iostream>

using namespace std;

int main()
{
	int* p = new int(4);

	shared_ptr<int> p1(p);

	shared_ptr<int> p2{p}; 

	auto p3 = make_shared<int>(6);

	auto p4 = shared_ptr<int>(new int(7) );
	
	cout << "p1:" << *p1 << p1 << endl;
	cout << "p2:" << *p2 << p2 << endl;
	cout << "p3:" << *p3 << p3 << endl;
	cout << "p4:" << *p4 << p4 << endl;

	return 0;
}
