#include <iostream>
#include <regex>
#include <string>
 
int main()
{
    std::string tmp,html;
    while(getline(std::cin,tmp))
    {
        tmp += '\n';
        html += tmp;
    }
    std::string pattern("http(s)?://([\\w-]+\\.)+[\\w-]+(/[\\w- ./?%&=]*)?");
    pattern = "[[:alpha:]]*" + pattern + "[[:alpha:]]*";
    std::regex r(pattern);
    for (std::sregex_iterator it(html.begin(), html.end(), r), end;     //end是尾后迭代器，regex_iterator是regex_iterator的string类型的版本
        it != end;
        ++it)
    {
        std::cout << it->str() << std::endl;
    }
}
