// use nohup to start this program :
// nohup ./t41 > t41.log 2>&1

#include <sys/epoll.h>
#include <string.h>
#include <errno.h>
#include <iostream>
#include <unistd.h>
//#include <sys/types.h>
//#include <sys/stat.h>
//#include <fcntl.h>
 
int main()
{
    //close(0);

    int epollfd = epoll_create1( EPOLL_CLOEXEC );
    if( epollfd == -1 )
    {
        std::cerr << "epoll_create failed, " << epollfd << "errno: " << errno << " " << strerror(errno) << std::endl;
    }
    struct epoll_event ev;
    ev.events = EPOLLIN;

    //ev.data.fd = 0;
    ev.data.fd = 12345;
    if( epoll_ctl( epollfd, EPOLL_CTL_ADD, ev.data.fd, &ev )  )
    {
        std::cerr << "epoll_ctl add td server fd failedi, " << "errno: " << errno << " " << strerror(errno) << std::endl;
    }
    else
    {
        std::cout << "epoll_ctl success." << std::endl;
    }

    return 0;
}
