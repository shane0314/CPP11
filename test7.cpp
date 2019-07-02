#include "myHfile.h"
using namespace std;


typedef struct type1 { char x[3]; } type1;
typedef char type2[3];

int main()
{
	type1 a1;
	type2 a2;
	cout << "size of type1: " << sizeof(type1) <<endl;
	cout << "size of type2: " << sizeof(type2) <<endl;

	strcpy(a2,"he");
	cout << "a2=" << a2 <<endl;
	a2[0] = 'H';
	a2[1] = 'E';
	cout << "a2=" <<a2 <<endl;
}
