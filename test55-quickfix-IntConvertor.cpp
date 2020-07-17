#include <iostream>
#include <quickfix/FieldMap.h>
#include <chrono>

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


using namespace std;
using namespace std::chrono;

template<typename type>
    static inline char* integer_to_string( char* buf, const size_t len, type num )
    {
      const bool isNegative = num < 0;
      char* p = buf + len;
      *--p = '\0';

      // get unsigned value of number
      num = num < 0 ? -num : num;

      while( num > 0 )
      {
        *--p = num%10 + '0';
        num /= 10;
      }

      if( isNegative )
        *--p = '-';

      return p;
    }

/*
    inline std::string to_string( int32_t value )
    {
      return integer_to_string( std::numeric_limits<int32_t>::digits10 + 3, value );
    }

    inline std::string to_string( uint32_t value )
    {
      return integer_to_string( std::numeric_limits<uint32_t>::digits10 + 3, value );
    }
/
    inline std::string to_string( int64_t value )
    {
      // buffer is big enough for significant digits and extra digit,
      // minus and null
      char buffer[std::numeric_limits<int64_t>::digits10 + 3];
      const char* const start = integer_to_string( buffer, sizeof (buffer), value );
      return std::string( start, buffer + sizeof (buffer) - start - 1 );
    }
    inline std::string to_string( uint64_t value )
    {
      // buffer is big enough for significant digits and extra digit,
      // minus and null
      char buffer[std::numeric_limits<uint64_t>::digits10 + 3];
      const char* const start = integer_to_string( buffer, sizeof (buffer), value );
      return std::string( start, buffer + sizeof (buffer) - start - 1 );
    }
    inline std::string to_string( int32_t value )
    {
      // buffer is big enough for significant digits and extra digit,
      // minus and null
      char buffer[std::numeric_limits<int32_t>::digits10 + 3];
      const char* const start = integer_to_string( buffer, sizeof (buffer), value );
      return std::string( start, buffer + sizeof (buffer) - start - 1 );
    }
    inline std::string to_string( uint32_t value )
    {
      // buffer is big enough for significant digits and extra digit,
      // minus and null
      char buffer[std::numeric_limits<uint32_t>::digits10 + 3];
      const char* const start = integer_to_string( buffer, sizeof (buffer), value );
      return std::string( start, buffer + sizeof (buffer) - start - 1 );
    }
*/
    template<typename type>
    inline
    typename std::enable_if<std::is_integral<type>::value, std::string>::type
    convertIntString( type value )
    {
      // buffer is big enough for significant digits and extra digit,
      // minus and null
      char buffer[std::numeric_limits<type>::digits10 + 3];
      const char* const start = integer_to_string( buffer, sizeof (buffer), value );
      return std::string( start, buffer + sizeof (buffer) - start - 1 );
    }

int main()
{
    int64_t m_int64 = 929949600001;
    int32_t m_int32 = (int32_t)m_int64;
    long m_long = (long)m_int64;
    int m_int = (int)m_int64;
    uint64_t m_uint64 = (uint64_t)m_int64;
    uint64_t m_uint32 = (uint32_t)m_int64;

    double  m_double = 12345.6789;

    std::cout << m_int64 << std::endl;
    std::cout << m_int32 << std::endl;
    std::cout << m_long << std::endl;
    std::cout << m_int << std::endl;

    std::cout << "to_string( m_int32 ) = "
            << convertIntString( m_int32 ) << std::endl;
    std::cout << "to_string( m_int64 ) = "
            << convertIntString( m_int64 ) << std::endl;

    std::cout << "to_string( m_long ) = "
            << convertIntString( m_long ) << std::endl;

    std::cout << "to_string( m_uint ) = "
            << convertIntString( (uint32_t)4294967290 ) << std::endl;
    std::cout << "to_string( m_int ) = "
            << convertIntString( (int32_t)2147483647 ) << std::endl;
    std::cout << "to_string( a num ) = "
            << convertIntString( 2147483647 ) << std::endl;

    std::cout << "to_string( m_uint64 ) = "
            << convertIntString( m_uint64 ) << std::endl;
    std::cout << "to_string( m_uint32 ) = "
            << convertIntString( m_uint32 ) << std::endl;
//    std::cout << "to_string( m_double ) = "
//            << convertIntString( m_double ) << std::endl;
    
    int32_t m_minInt32 = (std::numeric_limits<int32_t>::min)();
    int32_t m_a = -m_minInt32;
    int32_t m_b = 1+m_minInt32;

    std::cout << "m_minInt32 = " << m_minInt32  << std::endl;
    std::cout << "-m_minInt32 = " << m_a << std::endl;
    std::cout << "1+m_minInt32 = " << m_b << std::endl;

    std::cout << "std::to_string((std::numeric_limits<int32_t>::min)()) = " << std::to_string((std::numeric_limits<int32_t>::min)()) << std::endl;

    char m_char = '1';
    std::cout << "::to_stirng(m_char) = " << ::to_string(m_char) << std::endl;
    std::cout << "std::to_stirng(m_char) = " << std::to_string(m_char) << std::endl;
    bool m_bool = true;
    std::cout << "::to_stirng(m_bool) = " << ::to_string(m_bool) << std::endl;
    std::cout << "std::to_stirng(m_bool) = " << std::to_string(m_bool) << std::endl;

    std::cout << "=======test std::to_string, self-defined on, which is faster==========" << std::endl;
    int times = 10000;

    auto start = high_resolution_clock::now();
    for( int i=0; i<times; ++i )
    {
        std::string strtmp = std::to_string(m_int64+i);
    } 
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start); 
    cout << "Time taken by function std::to_string: " << duration.count() << " microseconds" << endl; 
/*
    auto start2 = high_resolution_clock::now();
    for( int i=0; i<times; ++i )
    {
        std::string strtmp = to_string(m_int64+i);
    } 
    auto stop2 = high_resolution_clock::now();
    auto duration2 = duration_cast<microseconds>(stop2 - start2); 
    cout << "Time taken by function to_string: " << duration2.count() << " microseconds" << endl; 
*/

    auto start4 = high_resolution_clock::now();
    for( int i=0; i<times; ++i )
    {
        std::string strtmp = FIX::IntConvertor::convert(m_int64+i);
    } 
    auto stop4 = high_resolution_clock::now();
    auto duration4 = duration_cast<microseconds>(stop4 - start4); 
    cout << "Time taken by function FIX::IntConvertor::convert: " << duration4.count() << " microseconds" << endl; 

    auto start3 = high_resolution_clock::now();
    for( int i=0; i<times; ++i )
    {
        std::string strtmp = convertIntString(m_int64+i);
    } 
    auto stop3 = high_resolution_clock::now();
    auto duration3 = duration_cast<microseconds>(stop3 - start3); 
    cout << "Time taken by function UtilsconvertIntString: " << duration3.count() << " microseconds" << endl; 
}

