#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include <boost/algorithm/string.hpp>
#include <time.h>
#include <stdio.h>

using namespace std;

#define ABC(a,b,c,d)  printf("%d\n",a); printf("%d\n",b); printf("%d\n",c); printf("%d\n",d); 

int main()
{
    int va=1,vb=2,vc=3;
    ABC(va,vb,vc,vc);    

    return 0;
}
