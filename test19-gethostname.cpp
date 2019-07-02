#include <stdio.h>
#include <unistd.h>
#include <sys/utsname.h>
#include <iostream>

int main()
{
    char name[65];
    char name2[100];
    gethostname(name, sizeof(name));
    getdomainname(name2, sizeof(name2));

    printf("hostname = %s\n", name);
    printf("domainname = %s\n", name2);

    struct utsname u;
    uname( &u );
    printf("uname = %s;%s \n", std::string(u.release).c_str(), std::string(u.version).c_str() );

    return 0;
}
