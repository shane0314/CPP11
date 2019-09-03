#include <vector>
#include <string>
#include <iostream>

int main()
{
	std::vector<std::string> vs;
	// vs.push_back("Hello");
	auto p = vs.begin();
	if( p == vs.end() )
		std::cout << "empty" << std::endl;
	else
		std::cout << "not empty" << std::endl;
	std::cout << "the size of string : " << p->size() << std::endl;

	return 0;
}

