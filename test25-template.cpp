#include <iostream>
#include <utility>
 
void tprintf(const char* format) // base function
{
    std::cout << format;
}
 
template<typename T, typename... Targs>
void tprintf(const char* format, T value, Targs... Fargs) // recursive variadic function
{
	//std::cout << std::endl;
    //std::cout << "|format:" << format << "...|value:" << value << "|size of Fargs:" << sizeof...(Fargs) << std::endl;
    
    for ( ; *format != '\0'; format++ ) {
        if ( *format == '%' ) {
           std::cout << value;
           tprintf(format+1, Fargs...); // recursive call
           return;
        }
        std::cout << *format;
    }
}

class A
{
public:
	A() {}
	A(int i) {  std::cout << "A(int)" << i << std::endl; }
	A(double i) {  std::cout << "A(double)" << i << std::endl; }
	void print() { std::cout << "A::print()" << std::endl; }
	std::pair<int,int> getSome(int i) { std::cout << "std::pair<int,int> getSome(int) of A" << std::endl; return std::make_pair(1,1); }
	std::pair<int,int> getSome(double i) { std::cout << "std::pair<int,int> getSome(double of A" << std::endl; return std::make_pair(2,2); }
};
class B
{
public:
	B() {}
	B(int i) {  std::cout << "B(int)" << i << std::endl; }
	B(double i) {  std::cout << "B(double)" << i << std::endl; }
	void print() { std::cout << "B::print()" << std::endl; }
	int getSome(int i) { std::cout << "int getSome(int) of A" << std::endl; return 3; }
	int getSome(double i) { std::cout << "int getSome(double of A" << std::endl; return 4; }
};


template<typename ClassT>
class Parser
{
public:
	Parser() {}
	
	ClassT ins;

	template<typename returnT, typename argT>
	returnT getMsg(argT arg)
	{
		return ins.getSome( arg );
	}
	void print() { std::cout << "Parser::print()" << std::endl; }
};


int main()
{
    tprintf("% world% %! fuck,%!\n","Hello",'!',123,"get it");
	
	int i = 1.1;
	double d =2.2;

	Parser<A> pA;
	pA.print();
	auto res1 = pA.getMsg<std::pair<int, int> >( d );
	std::cout << "res1:<" << res1.first << "," << res1.second << ">" << std::endl;
	Parser<B> pB;
	pB.print();
	auto res2 = pB.getMsg <int> ( d );

    return 0;
}
