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
    char word1[5] = {'w','o','r','l','d'};
    char word2[6] = "hello";
    //std::cout << word1 << word2 << std::endl;
    std::cout << makestring(word1,5) << std::endl;
}
