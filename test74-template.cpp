#include "test74-template.h"

void Foo::bar() {
    private_print( 3.5 );
}

// private template member function can be defined in source file
template<typename T>
void Foo::private_print( T value ) {
    std::cout << "private_print, value: " << value << std::endl;
}
