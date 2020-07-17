#include <algorithm>
#include <list>
#include <iostream>
#include <iterator>

using namespace std;

int main()
{
    list<int> lst = {1,2,3,4,5};
    list<int> lst2, lst3, lst4;
    list<int> lst5(5), lst6;

    cout << "\nlist4: ";
    copy( lst.cbegin(), lst.cend(), ostream_iterator<int>(cout, " ") );

    copy( lst.cbegin(), lst.cend(), front_inserter(lst2) );
    cout << "\nlist2: ";
    copy( lst2.cbegin(), lst2.cend(), ostream_iterator<int>(cout, " ") );
    
    copy( lst.cbegin(), lst.cend(), inserter( lst3, lst3.begin() ) );
    cout << "\nlist3: ";
    copy( lst3.cbegin(), lst3.cend(), ostream_iterator<int>(cout, " ") );
    
    copy( lst.cbegin(), lst.cend(), back_inserter(lst4) );
    cout << "\nlist4: ";
    copy( lst4.cbegin(), lst4.cend(), ostream_iterator<int>(cout, " ") );

    copy( lst.cbegin(), lst.cend(), lst5.begin() );
    cout << "\nlist5: ";
    copy( lst5.cbegin(), lst5.cend(), ostream_iterator<int>(cout, " ") );

    copy( lst.cbegin(), lst.cend(), lst6.begin() );
    cout << "\nlist6: ";
    copy( lst6.cbegin(), lst6.cend(), ostream_iterator<int>(cout, " ") );
    

    return 0;
}

