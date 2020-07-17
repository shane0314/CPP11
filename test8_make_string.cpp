#include "myHfile.h"
using namespace std;


std::string makestring(char * cstr, int size)
{
    std::string str;
    str.append(cstr,size);
    return str;
}


int main()
{
    char word1[7] = {'w','o','r','l','d', ' ', ' '};
    std::string word2 = "hello67";
    //std::cout << word1 << word2 << std::endl;
    std::cout << makestring(word1,5) << std::endl;
	std::string str(word1,7);
	std::cout << "str(word1,7) : " << str << "END" << std::endl;
	std::string str2(word2.c_str(),7);
	std::cout << "str2(word2,7) : " << str2 << "END" << std::endl;
}
