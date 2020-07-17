#include <string>

struct B {
  int f( int );
  int f( double );
  int g( int );
};
int B::f( int i ) { return i+1; }
int B::f( double d ) { return d+0.1; }
int B::g( int i ) { return i+2; }

struct D : public B {
  using B::g;
  int g( std::string, bool );
};
int D::g( std::string s, bool flag ) { return flag ? s.size() : 0; }

int main(){
D   d;
int i;
d.f(i);    // ok, means B::f(int)
d.g(i);    // error: g takes 2 args
d.B::g(i);    // error: g takes 2 args

return 0;
}
