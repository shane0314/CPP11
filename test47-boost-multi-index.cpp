#include <string>
#include <iostream>
#include <boost/multi_index_container.hpp>
#include <boost/multi_index/member.hpp>
#include <boost/multi_index/ordered_index.hpp>

using namespace boost;
using namespace boost::multi_index;
using namespace std;

struct Sname
{
    Sname(string& name1, string& name2)
        :first_name(name1)
        ,last_name(name2)
        {}
    friend bool operator< (const Sname& name1, const Sname& name2)
    {
        return name1.first_name < name2.first_name ? true : name1.last_name < name2.last_name;
    }
    friend ostream& operator<< (ostream&os, const Sname& name )
    {
        os << name.first_name << " " << name.last_name;
        return os;
    }
    string first_name;
    string last_name;
};

struct Employee{
    int id;
    Sname name;
    int age;

    Employee(int id_, string name1_, string name2_, int age_)
        :id(id_)
        ,name(name1_, name2_)
        ,age(age_)
        {}

    friend ostream& operator<<(ostream& os,const Employee& e)
    {
        os<<e.id<<" "<<e.name<<" "<<e.age;
        return os;
    }
};

typedef multi_index_container<
    Employee,
    indexed_by<
        ordered_unique<member<Employee, int, &Employee::id> >,
        ordered_non_unique<member<Employee, Sname, &Employee::name> >,
        ordered_non_unique<member<Employee, int, &Employee::age> >
    >
> EmployeeContainer;

typedef EmployeeContainer::nth_index<0>::type IdIndex;
typedef EmployeeContainer::nth_index<1>::type NameIndex;
typedef EmployeeContainer::nth_index<2>::type AgeIndex;

int main(){
    EmployeeContainer con;
    con.insert(Employee(0,"Joe","Green",31));
    con.insert(Employee(1,"Robert","Lee",27));
    con.insert(Employee(2,"John","Cheng",40));

    ostream_iterator<Employee> cout_iter(cout, "\n");

    IdIndex& ids = con.get<0>();
    copy(ids.begin(),ids.end(), cout_iter);
    cout << endl;

    ids.erase(ids.begin());

    NameIndex& names = con.get<1>();
    copy(names.begin(), names.end(), cout_iter);
    cout << endl;

    con.clear();
    AgeIndex& ages = con.get<2>();
    //ages.clear();
    copy(ages.begin(), ages.end(), cout_iter);
    cout << endl;

    return 0;
}
