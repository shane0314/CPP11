#include <string>
#include <iostream>
#include <sstream>

using namespace std;

class Person {
public:
	Person() = default;
	Person(const string &name, const int age) : m_name(name), m_age(age) {}
	Person(const string &name) : m_name(name),m_age(0) {}
	explicit Person(const int age) : m_name("anonym"), m_age(age) {}
	explicit Person(const char *name, const int age) : m_name(string(name)), m_age(age) {} // non-sense
	friend ostream &operator<<( ostream &os, const Person &per);
	operator string() { 
		stringstream sstr;
		sstr << "Name:" << m_name << " Age:" << m_age;
		return sstr.str();
	}
		
private:
	string m_name;
	int m_age;
};
ostream &operator<<( ostream &os, const Person &per){
	os << "Name:" << per.m_name << " Age:" << per.m_age;
	return os;
}

int main()
{
	Person p1("Jack");
	cout << p1 << endl;
	// Person p2 = "Tom"; // error: conversion from ‘const char [4]’ to non-scalar type ‘Person’ requested
	Person p2 = string("Tom");
	cout << p2 << endl;
	Person pp2 = static_cast<string>("Tom");
	cout << pp2 << endl;
	Person p3("Suke", 18);
	cout << p3 << endl;
	// Person p4 = 19; // error: conversion from ‘int’ to non-scalar type ‘Person’ requested
	Person p4(19);
	cout << p4 << endl;
	Person p5("Alex", 20);
	cout << p5 << endl;

	string pp_string(p5);
	cout << p5 << endl;
}
