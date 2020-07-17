#include <vector>
#include <iostream>

using namespace std;

template<typename T>
void swap(T a, T b)
{
    cout << "self defined swap!!" << endl;
    T tmp = a;
    a = b;
    b = tmp;
}

int main()
{
    vector<double> v1{1,2,3,4,5};
    vector<double> v2{6,7,8,9};
    double *p = &v1[0];
    cout << "*p = " << *p << ", &v1[0] = " << &v1[0] << endl;

    cout << "swap two containers" << endl;
    swap(v1,v2);

    cout << "v1 : ";
    for( auto iter = v1.cbegin(); iter != v1.cend(); iter++ )
    {
        cout << *iter << ", ";
    }
    cout << endl;

    cout << "v2 : ";
    for( auto iter = v2.cbegin(); iter != v2.cend(); iter++ )
    {
        cout << *iter << ", ";
    }
    cout << endl;

    cout << "*p = " << *p << ", &v1[0] = " << &v1[0] << endl;

    cout << "swap two first elements" << endl;
    ::swap(v1[0], v2[0]);
    cout << "v1[0] = " << v1[0] << ", " << "v2[0] = " << v2[0] << endl;

    ::swap( *(v1.begin()+1), *(v2.begin()+1) );
    cout << "v1[1] = " << v1[1] << ", " << "v2[1] = " << v2[1] << endl;
    
    cout << "stand swap" << endl;
    std::swap(v1[0], v2[0]);
    cout << "v1[0] = " << v1[0] << ", " << "v2[0] = " << v2[0] << endl;

    std::swap( *(v1.begin()+1), *(v2.begin()+1) );
    cout << "v1[1] = " << v1[1] << ", " << "v2[1] = " << v2[1] << endl;


      std::vector<int>::size_type sz;

  std::vector<int> foo(0);
  sz = foo.size();
  std::cout << "making foo grow:\n";
  for (int i=0; i<21; ++i) {
    foo.push_back(i);
    if (sz!=foo.size()) {
      sz = foo.size();
      std::cout << "capacity changed: " << sz << '\n';
    }
  }

  std::vector<int> bar;
  sz = bar.capacity();
  bar.reserve(100);   // this is the only difference with foo above
  std::cout << "making bar grow:\n";
  for (int i=0; i<100; ++i) {
    bar.push_back(i);
    if (sz!=bar.capacity()) {
      sz = bar.capacity();
      std::cout << "capacity changed: " << sz << '\n';
    }
  }

    return 0;
}

