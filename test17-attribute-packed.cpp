#include <iostream>
#include </usr/include/stdint.h>
#include </usr/include/x86_64-linux-gnu/sys/cdefs.h>

using namespace std;

struct  __attribute__((__packed__)) A
{
    int i;
    char ident[1];
    char name[2];
    uint64_t : 16 __attribute__((__packed__));
    int c;
};
struct B
{
    int i;
    char ident[1];
    char name[2];
    uint64_t : 16;// __attribute__((__packed__));
    int c;
    uint64_t : 16;// __attribute__((__packed__));
};

int main(void)
{
    cout << "sizeof(A)：" << sizeof(A) << endl;
    cout << "sizeof(B)：" << sizeof(B) << endl;
}
