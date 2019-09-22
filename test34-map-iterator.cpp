#include <iostream>
#include <string>
#include <map>
#include <vector>

class CA
{
public:
	CA();
	void printMap1();
	void insertMap1( std::string, int, char* );
private:
	int vint;
	char vstr[10];
	std::map<std::string, int> m_map1; //name,age
	std::map<std::string, char*> m_map2; //name,address
	std::vector<int> m_vec; //seqnum
};

class CB
{
	int vint;
	char vstr[10];
};

class CC
{
	char vstr[10];
};

CA::CA()
{
	vint = 0;
	vstr[0] = '\0';
	m_map1["nobody"] = 0;
	m_map2["nobody"] = NULL;
	m_vec.push_back(0);
}

void CA::printMap1()
{
	std::cout << "printMap1:" << std::endl;
	for( auto it = m_map1.begin(); it != m_map1.end(); ++it )
	{
		std::cout << "name:" << it->first
				<< " age:"	<< it->second
				<< " addr:" << ( m_map2[it->first] ? m_map2[it->first] : "" )
				<< ( std::next(it,1) == m_map1.end() ? "" : " | ");
	}
	std::cout << std::endl;
	std::cout << "max seqnum: " << m_vec.size() << std::endl;
}

void CA::insertMap1(std::string str, int n, char* addr = NULL)
{
	m_map1[str] = n;
	m_map2[str] = addr;
	m_vec.push_back(m_vec.size());
}

int main()
{
	CA ca;
	ca.insertMap1("Jack",21, new char[10]);
	ca.insertMap1("David",30, new char[10]);
	ca.insertMap1("Luis",16, new char[10]);
	ca.printMap1();
	
	std::vector<int> test;
	test.push_back(1);
	test.push_back(2);
	auto it = test.begin(); 	
	auto it2 = it+1;
	std::cout << "Print:" << *it2 << std::endl; 
	
	std::cout << "size of CA : " << sizeof(CA) << std::endl;
	std::cout << "size of ca : " << sizeof(ca) << std::endl;
	std::cout << "size of int : " << sizeof(int) << std::endl;
	std::cout << "size of std::map<string,int> : " << sizeof(std::map<std::string,int>) << std::endl;
	std::cout << "size of std::map<string, char *> : " << sizeof(std::map<std::string,char*>) << std::endl;
	std::cout << "size of std::vector<int> : " << sizeof(std::vector<int>) << std::endl;
	
	std::cout << "size of CB : " << sizeof(CB) << std::endl;
	std::cout << "size of CC : " << sizeof(CC) << std::endl;
	return 0;
}
