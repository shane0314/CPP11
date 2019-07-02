#include <stdio.h>
#include <iostream>
#include <string.h>

using namespace std;

struct SData
{
	unsigned int num;
	char str[10];
};

int main()
{
	SData data;
	data.num=65536;
	strcpy(data.str,"abc456789");
	
	cout << "size of SData: " << sizeof(SData) << "|data.num=" << data.num
		<< "|data.str=" << data.str <<endl;
	char mstr[100];
	memcpy( mstr, &data, sizeof(SData) );

	cout << "fist data is: " << *(int *) &mstr[0] <<endl;

	SData *pS = &data;
	char *pC = (char * )(void *)pS;

	cout << "fist data is: " << *(int *) pC <<endl;

}
