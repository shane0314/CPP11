#include <iostream>

using namespace std;

int main()
try
{
    cout << "main body" << endl;
    throw 0;
}
catch（ int e )
{
    cout << "error:" << e << endl;
}
catch(exception &ex)
{
    cout << "stderror:" << ex.what() << endl;
}
