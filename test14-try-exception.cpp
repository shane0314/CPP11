#include <iostream>
#include <stdexcept>

using namespace std;

int main()
{
try
{
    cout << "input zero : ";
	double d = 1;
	//cin >> d;
	cout << "the result is : " << 4.0/d << std::endl;
	throw 0.1;
    throw -1;
}

// we mustn't cath what try codes throw, but suggest to do that
catch( int e )
{
    cout << "error:" << e << endl;
}
catch( double e )
{
    cout << "error:" << e << endl;
}

// runtime_error must be catched before exception, becase runtime_error is derived class of exception
catch( std::runtime_error err)
{
	cout << "runtime_error:" << err.what() << endl;
}
catch( std::exception e)
{
	cout << "error:" << e.what() << endl;
}

}
