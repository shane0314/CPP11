#include <iostream>
#include <sstream>
#include <chrono>

using namespace std;
using namespace std::chrono;


std::string m_to_string( int num )
{
    //buffer is big enough for significant digits and extra digit, minus and null
    char buf[std::numeric_limits<long>::digits10 + 3];

    const bool isNegative = num < 0;
    char* p = buf + sizeof(buf);
    *--p = '\0';
    num = num < 0 ? -num : num;

    do {
        *--p = num%10 + '0';
        num /= 10; 
    } while( num > 0 );  

    if( isNegative )
        *--p = '-';

    return std::string( p );
}

static const char digit_pairs[201] = {
  "00010203040506070809"
  "10111213141516171819"
  "20212223242526272829"
  "30313233343536373839"
  "40414243444546474849"
  "50515253545556575859"
  "60616263646566676869"
  "70717273747576777879"
  "80818283848586878889"
  "90919293949596979899"
};

std::string m_to_string2( int num )
{
    //buffer is big enough for significant digits and extra digit, minus and null
    char buf[std::numeric_limits<long>::digits10 + 3];

    const bool isNegative = num < 0;
    char* p = buf + sizeof(buf);
    *--p = '\0';
    num = num < 0 ? -num : num;

    while( num > 99 )
    {
      unsigned pos = num % 100;
      num /= 100;
      p -= 2;
      *(short*)(p) = *(short*)(digit_pairs + 2 * pos);
    }
    if( num > 9 )
    {
      p -= 2;
      *(short*)(p) = *(short*)(digit_pairs + 2 * num);
    }
    else
    {
      *--p = '0' + char(num);
    }

    if( isNegative )
    *--p = '-';

    return std::string( p );
}


int main()
{
    //check
    std::cout << "m_to_string(0)=" << m_to_string(0) << std::endl;
    std::cout << "m_to_string(-1)=" << m_to_string(-1) << std::endl;
    std::cout << "m_to_string(429900)=" << m_to_string(429900) << std::endl;
    std::cout << "m_to_string2(0)=" << m_to_string2(0) << std::endl;
    std::cout << "m_to_string2(-1)=" << m_to_string2(-1) << std::endl;
    std::cout << "m_to_string2(429900)=" << m_to_string2(429900) << std::endl;

    std::cout << "=======test which is faster==========" << std::endl;
    int times = 10000;
    int initValue = 12345;
    std::string strRet;

    auto start = high_resolution_clock::now();
    for( int i=0; i<times; ++i )
    {
        strRet == [](int value)->std::string{ std::stringstream ss; ss << value; return ss.str(); }( initValue+i );
    } 
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start); 
    cout << "Time taken by using std::stringstream: " << duration.count() << " microseconds" << endl; 

    start = high_resolution_clock::now();
    for( int i=0; i<times; ++i )
    {
        strRet == [](int value)->std::string{ char buf[std::numeric_limits<long long>::digits10 + 3]={0}; sprintf(buf, "%d", value); return std::string(buf); }( initValue+i );
    } 
    stop = high_resolution_clock::now();
    duration = duration_cast<microseconds>(stop - start); 
    cout << "Time taken by using sprintf sprintf:   " << duration.count() << " microseconds" << endl; 

    start = high_resolution_clock::now();
    for( int i=0; i<times; ++i )
    {
        strRet = std::to_string(initValue+i);
    } 
    stop = high_resolution_clock::now();
    duration = duration_cast<microseconds>(stop - start); 
    cout << "Time taken by function std::to_string: " << duration.count() << " microseconds" << endl; 

    start = high_resolution_clock::now();
    for( int i=0; i<times; ++i )
    {
        std::string strtmp = m_to_string(initValue+i);
    } 
    stop = high_resolution_clock::now();
    duration = duration_cast<microseconds>(stop - start); 
    cout << "Time taken by function m_to_string:    " << duration.count() << " microseconds" << endl; 

    start = high_resolution_clock::now();
    for( int i=0; i<times; ++i )
    {
        std::string strtmp = m_to_string2(initValue+i);
    } 
    stop = high_resolution_clock::now();
    duration = duration_cast<microseconds>(stop - start); 
    cout << "Time taken by function m_to_string2:   " << duration.count() << " microseconds" << endl; 

    return 0;
}

