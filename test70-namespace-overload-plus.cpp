#include <iostream>
#include <numeric>
#include "test70.h"

using namespace N;
int operator+(int i, N::C) {  return i+1; }

void foo(){
  C a[10];
  std::accumulate(a, a+10, 0);
}

// a mainline to exercise it
int main() {
    foo();
}
