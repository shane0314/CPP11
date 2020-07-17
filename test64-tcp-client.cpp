#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <sys/epoll.h>
#include <iostream>
#include <errno.h>
#include <vector>
#include "linux/net_tstamp.h"
#include <sys/time.h>
#include <sys/ioctl.h>
 
#define MYPORT  8887
#define BUFFER_SIZE 1024
#define MAX_EVENT 255

static void printpacket(struct msghdr *msg, int res,
            char *data,
            int sock, int recvmsg_flags,
            int siocgstamp, int siocgstampns)
{
    struct sockaddr_in *from_addr = (struct sockaddr_in *)msg->msg_name;
    struct cmsghdr *cmsg;
    struct timeval tv;
    struct timespec ts;
    struct timeval now;

    gettimeofday(&now, 0);

    printf("%ld.%06ld: received %s data, %d bytes from %s, %d bytes control messages\n",
           (long)now.tv_sec, (long)now.tv_usec,
           (recvmsg_flags & MSG_ERRQUEUE) ? "error" : "regular",
           res,
           inet_ntoa(from_addr->sin_addr),
           static_cast<int>(msg->msg_controllen) );

    for (cmsg = CMSG_FIRSTHDR(msg); cmsg; cmsg = CMSG_NXTHDR(msg, cmsg)) {
        printf("   cmsg len %d: ", static_cast<int>(cmsg->cmsg_len) );

        switch (cmsg->cmsg_level) {
        case SOL_SOCKET:
            printf("SOL_SOCKET ");

            switch (cmsg->cmsg_type) {
            case SO_TIMESTAMP: {
                struct timeval *stamp =
                    (struct timeval *)CMSG_DATA(cmsg);
                printf("SO_TIMESTAMP %ld.%06ld",
                       (long)stamp->tv_sec,
                       (long)stamp->tv_usec);
                break;
            }
            case SO_TIMESTAMPNS: {
                struct timespec *stamp =
                    (struct timespec *)CMSG_DATA(cmsg);
                printf("SO_TIMESTAMPNS %ld.%09ld",
                       (long)stamp->tv_sec,
                       (long)stamp->tv_nsec);
                break;
            }
            case SO_TIMESTAMPING: {
                struct timespec *stamp =
                    (struct timespec *)CMSG_DATA(cmsg);
                printf("SO_TIMESTAMPING ");
                printf("SW %ld.%09ld ",
                       (long)stamp->tv_sec,
                       (long)stamp->tv_nsec);
                stamp++;
                printf("HW transformed %ld.%09ld ",
                       (long)stamp->tv_sec,
                       (long)stamp->tv_nsec);
                stamp++;
                printf("HW raw %ld.%09ld",
                       (long)stamp->tv_sec,
                       (long)stamp->tv_nsec);
                break;
            }
            default:
                printf("type %d", cmsg->cmsg_type);
                break;
            }
            break;
/*
        case IPPROTO_IP:
            printf("IPPROTO_IP ");
            switch (cmsg->cmsg_type) {
            case IP_RECVERR: {
                struct sock_extended_err *err =
                    (struct sock_extended_err *)CMSG_DATA(cmsg);
                printf("IP_RECVERR ee_errno '%s' ee_origin %d => %s",
                    strerror(err->ee_errno),
                    err->ee_origin,
#ifdef SO_EE_ORIGIN_TIMESTAMPING
                    err->ee_origin == SO_EE_ORIGIN_TIMESTAMPING ?
                    "bounced packet" : "unexpected origin"
#else
                    "probably SO_EE_ORIGIN_TIMESTAMPING"
#endif
                    );
                if (res < sizeof(sync))
                    printf(" => truncated data?!");
                else if (!memcmp(sync, data + res - sizeof(sync),
                            sizeof(sync)))
                    printf(" => GOT OUR DATA BACK (HURRAY!)");
                break;
            }
            case IP_PKTINFO: {
                struct in_pktinfo *pktinfo =
                    (struct in_pktinfo *)CMSG_DATA(cmsg);
                printf("IP_PKTINFO interface index %u",
                    pktinfo->ipi_ifindex);
                break;
            }
            default:
                printf("type %d", cmsg->cmsg_type);
                break;
            }
            break;
*/
        default:
            printf("level %d type %d",
                cmsg->cmsg_level,
                cmsg->cmsg_type);
            break;
        }
        printf("\n");
    }

    if (siocgstamp) {
        if (ioctl(sock, SIOCGSTAMP, &tv))
            printf("%d, %s: %s\n", sock, "SIOCGSTAMP", strerror(errno));
        else
            printf("SIOCGSTAMP %ld.%06ld\n",
                   (long)tv.tv_sec,
                   (long)tv.tv_usec);
    }
    if (siocgstampns) {
        if (ioctl(sock, SIOCGSTAMPNS, &ts))
            printf("%d, %s: %s\n", sock, "SIOCGSTAMPNS", strerror(errno));
        else
            printf("SIOCGSTAMPNS %ld.%09ld\n",
                   (long)ts.tv_sec,
                   (long)ts.tv_nsec);
    }

}

static void recvpacket(int sock, int recvmsg_flags, int siocgstamp, int siocgstampns)
{
    char data[256];
    struct msghdr msg;
    struct iovec entry;
    struct sockaddr_in from_addr;
    struct {
        struct cmsghdr cm;
        char control[512];
    } control;
    int res;

    memset(&msg, 0, sizeof(msg));
    msg.msg_iov = &entry;
    msg.msg_iovlen = 1;
    entry.iov_base = data;
    entry.iov_len = sizeof(data);
    msg.msg_name = (caddr_t)&from_addr;
    msg.msg_namelen = sizeof(from_addr);
    msg.msg_control = &control;
    msg.msg_controllen = sizeof(control);

    res = recvmsg(sock, &msg, recvmsg_flags|MSG_DONTWAIT);
    if (res < 0) {
        printf("%s %s: %s\n",
               "recvmsg",
               (recvmsg_flags & MSG_ERRQUEUE) ? "error" : "regular",
               strerror(errno));
    } else {
        printpacket(&msg, res, data,
                sock, recvmsg_flags,
                siocgstamp, siocgstampns);
    }
}
 
int main( int argc, const char** argv )
{
    ///定义sockfd
    //close(0);
    int sock_cli = socket(AF_INET,SOCK_STREAM, 0);
    printf("socket success, sockfd = %d\n", sock_cli);
 
    ///定义sockaddr_in
    struct sockaddr_in servaddr;
    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(MYPORT);  ///服务器端口
    //servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");  ///服务器ip
    servaddr.sin_addr.s_addr = inet_addr( argv[1] );  ///服务器ip
 
    ///连接服务器，成功返回0，错误返回-1
    if (connect(sock_cli, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0)
    {
        perror("connect");
        exit(1);
    }
    //puts("connect success");

    //TIMESTAMP
    static const int SOF_TIMESTAMPING_RX_ANY = SOF_TIMESTAMPING_RX_HARDWARE | SOF_TIMESTAMPING_RAW_HARDWARE | SOF_TIMESTAMPING_SYS_HARDWARE;
    static const int RX_HW_TIMESTAMPING = SOF_TIMESTAMPING_RX_ANY | SOF_TIMESTAMPING_RX_SOFTWARE | SOF_TIMESTAMPING_SOFTWARE | SOF_TIMESTAMPING_RX_SOFTWARE; 
    int value = RX_HW_TIMESTAMPING;

    int ret = setsockopt(sock_cli, SOL_SOCKET, SO_TIMESTAMPING, &value, sizeof(value) );
    if( ret < 0 )
    {
        std::cerr << "set timestamping failed: " << ret << ":" << strerror(errno) << std::endl;
    }
    int new_value;
    socklen_t sz = sizeof(new_value);
    if( getsockopt(sock_cli, SOL_SOCKET, SO_TIMESTAMPING, &new_value, &sz ) == 0 )
    {
        std::cout << "timestamping, value:" << value << ", new value:" << new_value << std::endl;
    }


    //epoll to recv data from server
    int epollfd = epoll_create1( EPOLL_CLOEXEC );
    if( epollfd == -1 )
    {
        std::cerr << "epoll_create failed: " << epollfd << std::endl;
        return EXIT_FAILURE;
    }
    struct epoll_event ev;
    ev.events = EPOLLIN;
    ev.data.fd = sock_cli;
    if( epoll_ctl( epollfd, EPOLL_CTL_ADD, ev.data.fd, &ev )  )
    {
        std::cout << "epoll_ctl add td server fd failed: " << strerror(errno) << std::endl;
        return EXIT_FAILURE;
    }
    else
    {
        std::cout << "epoll_ctl success: " << strerror(errno) << std::endl;
    }

    std::vector<struct epoll_event>  events(MAX_EVENT);
 
    while (1)
    {
        int nfds = epoll_wait( epollfd, &*events.begin(), static_cast<int>(events.size()), -1 );
        if( nfds == -1 )
        {
            if( errno == EINTR )
                continue;
            std::cerr << "epoll_wait failed. errno = " << errno << std::endl;
            return EXIT_FAILURE;
        }
        if( nfds == 0 )
            continue;
        if( (size_t)nfds == events.size() )
        {
            events.resize( events.size() * 2 );
        }

        for( int i = 0; i < nfds; ++i )
        {
            if( events[i].data.fd == sock_cli )
            {
//                self_recv( sock_cli  );
                recvpacket( sock_cli, 0, 1, 1 );
                recvpacket( sock_cli, MSG_ERRQUEUE, 1, 1 );
            }
        }
    }
 
    close(sock_cli);
    return 0;
}
