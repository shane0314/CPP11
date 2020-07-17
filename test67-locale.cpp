#include <iostream>
#include <regex>
#include <string>
#include <boost/locale.hpp>
#include <locale>

// Using char or wchar instead of char32_t runs without throwing though
//std::locale loc("chs");

class LocaleGuard
{
public:
    LocaleGuard( const std::locale& loc )
        : m_old( std::locale::global( loc ) )
    {
        std::cout << "set locale to " << loc.name() << std::endl;
    }

    ~LocaleGuard()
    {
        std::locale::global( m_old );
        std::cout << "recover locale to " << m_old.name() << std::endl;
    }

private:
    std::locale m_old;
};

int main()
{
    LocaleGuard guard( std::locale("") );

    const std::locale loc(std::locale(), new std::ctype<char>);
    const std::locale oldLoc = std::locale::global( std::locale("") );
    //boost::locale::generator gen; std::locale::global( gen("") );

    std::cout << "The default locale is " << std::locale().name() << '\n'
              << "The user's locale is " << std::locale("").name() << '\n'
              << "A nameless locale is " << loc.name() << '\n'
              << "old locale is " << oldLoc.name() << "\n";
    std::basic_string<char> reg = "([a-z]+)\\.txt";

    try
    {
        std::basic_regex<char> tagRegex(reg);
	std::smatch base_match;
	std::string fnames("foo.txt");
	std::cout << "matched: " << std::regex_match(fnames, base_match, tagRegex) << std::endl;
    }
    catch(std::exception &e)
    {
        std::cout << e.what() << std::endl;
    }

    std::locale::global( oldLoc );

    return 0;
}

