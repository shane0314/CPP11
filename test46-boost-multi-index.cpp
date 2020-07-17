#include <string>
#include <iostream>
#include <memory>
#include <boost/multi_index_container.hpp>
#include <boost/multi_index/member.hpp>
#include <boost/multi_index/ordered_index.hpp>
#include <boost/shared_ptr.hpp>

using namespace boost;
using namespace boost::multi_index;
using namespace std;
struct Employee{
    int id;
    string name;
    int age;

    Employee(int id_,string name_,int age_):id(id_),name(name_),age(age_){}

    friend ostream& operator<<(ostream& os,const Employee& e)
    {
        os<< e.id <<" "<< e.name <<" "<< e.age;
        return os;
    }
    friend ostream& operator<<(ostream& os,const Employee* e)
    {
        os<< e->id <<" "<< e->name <<" "<< e->age;
        return os;
    }
};
typedef std::shared_ptr<Employee> EmployeePtr;

typedef multi_index_container<
    EmployeePtr,
    indexed_by<
        ordered_unique<member<Employee, int, &Employee::id> >,
        ordered_non_unique<member<Employee, string, &Employee::name> >,
        ordered_non_unique<member<Employee, int, &Employee::age> >
    >
> EmployeeContainer;

typedef EmployeeContainer::nth_index<0>::type IdIndex;
typedef EmployeeContainer::nth_index<1>::type NameIndex;
typedef EmployeeContainer::nth_index<2>::type AgeIndex;

int main(){
    EmployeeContainer con;
    con.insert( EmployeePtr(new Employee(0,"Joe",31)) );
    con.insert( EmployeePtr(new Employee(1,"Robert",27)) );
    con.insert( EmployeePtr(new Employee(2,"John",40)) );

    ostream_iterator<Employee> cout_iter(cout, "\n");
    ostream_iterator<EmployeePtr> cout_iter2(cout, "\n");

    IdIndex& ids = con.get<0>();
    std::transform(ids.begin(),ids.end(), cout_iter, [](EmployeePtr e){ return *e; } );
    cout << endl;

    NameIndex& names = con.get<1>();
    //std::transform(names.begin(),names.end(), cout_iter, [](EmployeePtr e){ return *e; } );
    copy(names.begin(), names.end(), cout_iter2);
    cout << endl;

    //  names.erase(names.begin());

    AgeIndex& ages = con.get<2>();
    //std::transform(ages.begin(),ages.end(), cout_iter, [](EmployeePtr e){ return *e; } );
    copy(ages.begin(), ages.end(), cout_iter2);
    cout << endl;

    return 0;
}
