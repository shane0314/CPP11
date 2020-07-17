#include <memory>
#include <vector>
#include <iostream>

using namespace std;

template<typename T>
class smart_ptr{
public:
	smart_ptr(T*);
	smart_ptr(smart_ptr&);

	T* operator->();
	T& operator*();
	smart_ptr& operator=(smart_ptr&);
	
	~smart_ptr();

private:
	int *count;
	T *p;
};

template<typename T>
smart_ptr<T>::smart_ptr(T* p)
	: count( new int(1) )
	, p(p)
{}

template<typename T>
smart_ptr<T>::smart_ptr(smart_ptr& sp)
	: count( &( ++*sp.count) ) //can get private value ?
	, p(sp.p)
{
	cout << "ref copy constructor, count=" << count << endl;
}

template<typename T>
T* smart_ptr<T>::operator->()
{
	return p;
}

template<typename T>
T& smart_ptr<T>::operator*()
{
	return *this->operator->();
}

template<typename T>
smart_ptr<T>& smart_ptr<T>::operator=(smart_ptr& sp)
{
	++*sp.count;
	if(--*count == 0)
	{
		delete count;
		delete p;
	}
	this->p = sp.p;
	this->count = sp.count;
	return *this;
}


template<typename T>
smart_ptr<T>::~smart_ptr()
{
	if( --*count == 0 )
	{
		delete count;
		delete p;
	}
}


int main()
{
    struct IntS
    {
        IntS( int a, int b ) : a(a), b(b) { cout << "IntS construct(int, int) ... " << endl; } 
        IntS() { cout << "IntS default construct ... " << endl; }
        int a;
        int b;
    };

    typedef shared_ptr<IntS> IntSPtr;

    auto isp = std::make_shared<IntS>(10,20);
    cout << "isp: " << isp->a << "," << isp->b << endl;

    typedef shared_ptr<int> IntPtr;

    IntPtr ip = std::make_shared<int>(1);
    cout << "ip = " << *ip << endl;
    IntPtr& ipref = ip;
    *ipref = 2; 
    cout << "ipref = " << *ipref << endl;
    cout << "ip = " << *ip << endl;
    IntPtr iptmp = ip;
    *iptmp = 3;
    cout << "iptmp = " << *iptmp << endl;
    cout << "ip = " << *ip << endl;
    cout << "sizeof(ip)=" << sizeof(ip) <<", sizeof(IntPtr)=" << sizeof(IntPtr) << endl; 

    cout << "--------begin------------" << endl;
    std::vector<IntS> isv;
    IntS tmp_is(11,11);
    IntS tmp_is2(21,21);
    cout << "-------push_back()-------" << endl;
    isv.push_back(tmp_is);
    cout << "-------push_back(std::move())------" << endl;
    isv.push_back( std::move(tmp_is2) );
    tmp_is.a = 31; tmp_is.b = 31;
    tmp_is2.a = 32; tmp_is2.b = 32;
    cout << "isv[0]=" << isv[0].a << "," << isv[0].b << "|" 
        << "isv[1]=" << isv[1].a << "," << isv[1].b << endl; 
    isv.at(1).a = 55;
    cout << "isv[0]=" << isv[0].a << "," << isv[0].b << "|" 
        << "isv[1]=" << isv[1].a << "," << isv[1].b << endl; 
    cout << "--------end------------" << endl;
    

    typedef std::vector<std::pair<double, double> > TestVec;
    typedef shared_ptr<TestVec> TestPtr;
    cout << "sizeof(TestPtr)=" << sizeof(TestPtr) << ", sizeof(TestVec)=" << sizeof(TestVec) << endl;
	int* p = new int(4);
	int i=6;

    // test to generate a empty/null shared_ptr
    IntPtr ip5;
    if(ip5) cout << "ip5 is not null" << endl; else cout << "ip5 is null" << endl;
    IntPtr ip6 = make_shared<int>();
    if(ip6) cout << "ip6 is not null" << endl; else cout << "ip6 is null" << endl;
    IntPtr ip7=nullptr;
    if(ip7) cout << "ip7 is not null" << endl; else cout << "ip7 is null" << endl;

	smart_ptr<int> p1(p);

	smart_ptr<int> p2{p}; 

	//auto p3 = make_smart<int>(int(6));

	smart_ptr<int> p4(new int(7));

	auto p5 = shared_ptr<int>(p); // right
	//auto p6 = smart_ptr<int>(p); // error
	
	cout << "p1:" << *p1 << endl;
	cout << "p2:" << *p2 << endl;
	//cout << "p3:" << *p3 << endl;
	cout << "p4:" << *p4 << endl;

    //[[
    // uinque_ptr
    unique_ptr<int> upi1( new int );
    cout << "*upi1 = " << *upi1 << endl;
    // unique_ptr<int> upi2 = upi1; // error
    // unique_ptr<int> upi2( upi1 ); // error
    unique_ptr<int> upi2( move( upi1 ) );
    // cout << "*upi1 = " << *upi1 << endl; // core dumped
    cout << "*upi2= " << *upi2 << endl;
    //]]

    //shared_ptr
    shared_ptr<int> spi1 = nullptr;
    int *i1 = new int;
    *i1 = 1;
    spi1.reset(i1);
    cout << "*spi 1= " << *spi1 << endl;
    *i1 = 2;
    cout << "*spi 1= " << *spi1 << endl;


	return 0;
}
