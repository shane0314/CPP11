#include <iostream>

class Foo
{
public:
    // public template member function must be defined in header file
    template<typename T>
    void public_print( T value ); {
        std::cout << "public_print, value: " << value << std::endl;
   }

    void bar();

private:
    template<typename T>
    void private_print( T value );

    int i;
};
