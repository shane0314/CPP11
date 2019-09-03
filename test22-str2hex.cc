#include <string>
#include <iostream>
//#include <math.h>
#include <sstream>

using namespace std;

int main()
{
	string str("0123456789ab");
	for( size_t i=0; i<str.length()/2; i++ )
	{
		string substr = str.substr(2*i, 2);
		cout << "substr_" << i << ":" << substr;
		int value;
		// value = dec2hex( stoi(substr, 0, 16) );
		stringstream ss( substr );
		ss >> hex >> value;
		cout << ", value:" << hex << value << endl;
	}
	return 0;
}
