#include <iostream>
 
void tprintf(const char* format) // base function
{
    std::cout << format;
}
 
template<typename T, typename... Targs>
void tprintf(const char* format, T value, Targs... Fargs) // recursive variadic function
{
	//std::cout << std::endl;
    //std::cout << "|format:" << format << "...|value:" << value << "|size of Fargs:" << sizeof...(Fargs) << std::endl;
    
    for ( ; *format != '\0'; format++ ) {
        if ( *format == '%' ) {
           std::cout << value;
           tprintf(format+1, Fargs...); // recursive call
           return;
        }
        std::cout << *format;
    }
}
 
int main()
{
    tprintf("% world% %! fuck,%!\n","Hello",'!',123,"get it");
    return 0;
}
