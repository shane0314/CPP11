#include <iostream>
#include <stdlib.h>

using namespace std;

int main()
{
    #ifdef _MYDEF
        cout << "#defined _MYDEF" << endl;
    #else
        cout << "not #defined _MYDEF" << endl;
    #endif

    return EXIT_SUCCESS;
}
