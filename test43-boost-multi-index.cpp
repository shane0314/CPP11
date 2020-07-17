#include <string>
#include <iostream>
#include <boost/multi_index_container.hpp>
#include <boost/multi_index/member.hpp>
#include <boost/multi_index/ordered_index.hpp>

using namespace boost;
using namespace boost::multi_index;
using namespace std;
struct Employee{
    int id;
    string name;
    int age;
    mutable int salary=0;

    Employee(int id_,string name_,int age_):id(id_),name(name_),age(age_){}

    friend ostream& operator<<(ostream& os,const Employee& e)
    {
        os<<e.id<<" "<<e.name<<" "<<e.age <<" " <<  e.salary;
        return os;
    }
};

typedef multi_index_container<
    Employee,
    indexed_by<
        ordered_unique<member<Employee, int, &Employee::id> >,
        ordered_non_unique<member<Employee, string, &Employee::name> >,
        ordered_non_unique<member<Employee, int, &Employee::age> >
    >
> EmployeeContainer;

typedef multi_index_container<
    Employee,
    indexed_by<
        ordered_non_unique<member<Employee, int, &Employee::id> >,
        ordered_non_unique<member<Employee, string, &Employee::name> >
    >
> EmployeeContainer2;

typedef EmployeeContainer::nth_index<0>::type IdIndex;
typedef EmployeeContainer::nth_index<1>::type NameIndex;
typedef EmployeeContainer::nth_index<2>::type AgeIndex;

template<class BeginIterator, class EndIterator>
double calcMedian( BeginIterator beginIter, EndIterator endIter, int size )
{
    int64_t tmp = 0;
    int count = 0;
    for( auto iter = beginIter; iter != endIter; ++iter )
    {
        if( count == size/2 )
        {
            if( size%2 != 0 ) // odd
            {
                return (*iter).age;
            }
            else // even
            {
                return ((*iter).age + tmp)/2.0;
            }
        }
        else if( count == size/2 - 1 && size%2 ==0 ) //even
        {
            tmp = (*iter).age;
        }
        ++count;
    }
}

int main(){
    EmployeeContainer con;
    con.insert(Employee(0,"Alex",31));
    con.insert(Employee(1,"Robert",27));
    con.insert(Employee(2,"John",41));
    con.insert(Employee(3,"John",42));
    con.insert(Employee(4,"Joe",40));
    con.insert(Employee(5,"John",43));
    con.insert(Employee(6,"John",44));

    ostream_iterator<Employee> cout_iter(cout, "\n");

    IdIndex& ids = con.get<0>();
    copy(ids.begin(),ids.end(), cout_iter);
    cout << endl;

    NameIndex& names = con.get<1>();
    copy(names.begin(), names.end(), cout_iter);
    cout << endl;

    //  names.erase(names.begin());

    AgeIndex& ages = con.get<2>();
    copy(ages.begin(), ages.end(), cout_iter);
    cout << endl;

    cout << "===test equal_range, find, lower_bound===" << endl;
    cout << "number of name John : " << names.count("John") << endl;

    auto iters = names.equal_range("John");
    cout << "---" << endl;
    for( auto it = iters.first; it != iters.second; ++it )
        cout << *it << endl;
    cout << "median age of people named John = " << calcMedian( iters.first, iters.second, names.count("John") ) << endl;; 
    cout << "---" << endl;

    auto iter = names.find("John");
    cout << *iter << endl;
    iter->salary = 3000;
    cout << "after : " << *iter << endl;
    cout << "---" << endl;

    auto begin = ages.lower_bound(20);
    auto end = ages.upper_bound(40);
    copy( begin, end, cout_iter );
    cout << "============================================" << endl;

    EmployeeContainer2 con2;
    con2.insert(Employee(0,"Alex",31));
    con2.insert(Employee(1,"Robert",27));
    con2.insert(Employee(2,"John",41));
    
    cout << "---con2.find()---" << endl;
    auto it2 = con2.find(31); // only can find directly for first index 
    if( it2 != con2.end() )
        cout << *it2 << endl;
    else
        cout << "not found" << endl;

    return 0;
}
