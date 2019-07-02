#include <iostream>

using namespace std;

class B
{
public:
    void printA()
    {
        cout<<"B::printA"<<endl;
    }
};

class D : public B  
{  
public:  
    void printA()  
    {  
        cout<<"D::printA"<<endl;  
    }  
    
    virtual void printB()  
    {  
        cout<<"printB"<<endl;  
    }  
    
    static void printC()
    {
        cout<<"printC"<<endl;
    }
};  
int main(void)
{

    D dd;
    dd.B::printA();
    dd.printA();

    D *d=NULL;
    d->printC();
    d->B::printA();
    d->printA();
    d->printB();
    
}
