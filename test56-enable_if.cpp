// enable_if example: two ways of using enable_if
#include <iostream>
#include <type_traits>

// 1. the return type (bool) is only valid if T is an integral type:
template <typename T>
typename std::enable_if<std::is_integral<T>::value,bool>::type
gt_zero (T i) { return i>0;  }
template <typename T>
typename std::enable_if<!std::is_integral<T>::value,bool>::type
gt_zero (T i) { return i>0; }

// 2. send parameter is unuseful, just for checking if T is an integral type
template < typename T>
bool
ltq_zero( T i, typename std::enable_if<std::is_integral<T>::value, T>::type foo=0 ) { return !gt_zero(i); }
template < typename T>
bool
ltq_zero( T i, typename std::enable_if<!std::is_integral<T>::value, T>::type foo=0 ) { return !gt_zero(i); }


// 3. the second template argument is only valid if T is an integral type:
template <typename T,
        typename std::enable_if<std::is_integral<T>::value>::type* = nullptr >
bool
is_even (T i) { return !bool(i%2); }
template <typename T,
        typename std::enable_if<!std::is_integral<T>::value>::type* = nullptr >
bool
is_even (T i) { return !bool( ((int)i)%2); }

// 4. only valid from c++14
/**
template < typename T,
           std::enable_if_t<std::is_integral<T>::value> = 0 >
bool
is_odd (T i) {return bool(i%2);}

template < typename T,
           std::enable_if_t<!std::is_integral<T>::value> = 0 >
bool
is_odd (T i) {return bool( ((int)i) % 2);}
**/


int main() {

  short int i = 1;    // code does not compile if type of i is not integral
  float f = 3.1;

  std::cout << std::boolalpha;
  std::cout << i << " greater than zero : " << gt_zero(i) << std::endl;
  std::cout << f << " greater than zero : " << gt_zero(f) << std::endl;
  std::cout << i << " less or equal zero : " << ltq_zero(i) << std::endl;
  std::cout << f << " less or equal zero : " << ltq_zero(f) << std::endl;
  std::cout << i << " is even: " << is_even(i) << std::endl;
  std::cout << f << " is even: " << is_even(f) << std::endl;
  //std::cout << i << " is odd: " << is_odd(i) << std::endl;
  //std::cout << f << " is odd: " << is_odd(f) << std::endl;

  std::cout << std::is_signed<int>::value << '\n';
  std::cout << std::is_signed<char>::value << '\n';
  std::cout << std::is_signed<bool>::value << '\n';

    bool m_bool=true;
    m_bool /= 10;

  return 0;
}
