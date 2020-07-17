#include <iostream>

using namespace std;

#define RESET   "\033[0m"
#define BLACK   "\033[30m"      /* Black */
#define RED     "\033[31m"      /* Red */
#define GREEN   "\033[32m"      /* Green */
#define YELLOW  "\033[33m"      /* Yellow */
#define BLUE    "\033[34m"      /* Blue */
#define MAGENTA "\033[35m"      /* Magenta */
#define CYAN    "\033[36m"      /* Cyan */
#define WHITE   "\033[37m"      /* White */
#define BOLDBLACK   "\033[1m\033[30m"      /* Bold Black */
#define BOLDRED     "\033[1m\033[31m"      /* Bold Red */
#define BOLDGREEN   "\033[1m\033[32m"      /* Bold Green */
#define BOLDYELLOW  "\033[1m\033[33m"      /* Bold Yellow */
#define BOLDBLUE    "\033[1m\033[34m"      /* Bold Blue */
#define BOLDMAGENTA "\033[1m\033[35m"      /* Bold Magenta */
#define BOLDCYAN    "\033[1m\033[36m"      /* Bold Cyan */
#define BOLDWHITE   "\033[1m\033[37m"      /* Bold White */

int main()
{
    int n =10;
    int count=0;
    std::cout << "--start---" << std::endl;
    {
    std::cout << YELLOW << "[WARN] waring waring " << count++ << RESET << std::endl;
    std::cout << RED << "[WARN] waring waring " << count++ << RESET << std::endl;
    std::cout << BLUE << "[WARN] waring waring " << count++ << RESET << std::endl;
    std::cout << GREEN << "[WARN] waring waring " << count++ << RESET << std::endl;
    std::cout << MAGENTA << "[WARN] waring waring " << count++ << RESET << std::endl;
    std::cout << CYAN << "[WARN] waring waring " << count++ << RESET << std::endl;
    std::cout << WHITE << "[WARN] waring waring " << count++ << RESET << std::endl;
    std::cout << BLACK << "[WARN] waring waring " << count++ << RESET << std::endl;
    }
    cout << "\033[1;31mbold red text\033[0m\n";
    cout << "\033[7;31mbold red text\033[0m\n";
    std::cout << "---end---" << std::endl;
}
