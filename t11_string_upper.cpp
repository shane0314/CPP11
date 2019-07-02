#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include <boost/algorithm/string.hpp>
#include <time.h>
#include <stdio.h>

using namespace std;

int main()
{
    string str1 = "Hello World";
    string str2 = "Hello World";

    clock_t tStart;    

    tStart = clock();
    boost::to_upper( str1 );
    cout << "str1:" << str1 << endl;
    printf("Time taken: %.2fs\n", (double)(clock() - tStart)/CLOCKS_PER_SEC);    


    tStart = clock();
    std::transform( str2.begin(), str2.end(), str2.begin(), ::toupper );
    cout << "str2:" << str2 << endl;
    printf("Time taken: %.2fs\n", (double)(clock() - tStart)/CLOCKS_PER_SEC);    
    
    return 0;
}
