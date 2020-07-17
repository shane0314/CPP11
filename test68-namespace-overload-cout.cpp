#include <iostream>
#include <sstream>
#include <iterator>
#include <vector>
#include <algorithm>
using namespace std ;

#if 0
namespace skg 
{
 template <class T>
  struct Triplet ;
}

template <class T>
ostream& operator<< (ostream& os, const skg::Triplet<T>& p_t) ;
#endif

namespace skg
{
  struct Triplet
  {
    int x, y, z ;

   Triplet (const int& p_x, const int& p_y, const int& p_z)
    : x(p_x), y(p_y), z(p_z) { }
  } ;
}
using namespace skg;

ostream& operator<< (ostream& os, const skg::Triplet& p_t)
{
 os << '(' << p_t.x << ',' << p_t.y << ',' << p_t.z << ')' ;
 return os ;
}


void printVector()
{

  vector< Triplet > vti ;
  vti.push_back (Triplet (1, 2, 3)) ;
  vti.push_back (Triplet (5, 5, 66)) ;

  copy (vti.begin(), vti.end(), ostream_iterator<Triplet> (cout, "\n")) ; // error compile
  std::cout << vti[0] << vti[1] << std::endl; // ok
}

int main (void)
{
 printVector() ;
 Triplet t(1, 2, 3);
 std::cout << t << std::endl;// ok
}
