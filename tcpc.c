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
 
#define MYPORT  8888
#define BUFFER_SIZE 1024
 
int main()
{
    int max_clients = 5;
    while( max_clients-- ) {

    ///定义sockfd
    //close(0);
    int sock_cli = socket(AF_INET,SOCK_STREAM, 0);
    printf("socket success, sockfd = %d\n", sock_cli);
 
    ///定义sockaddr_in
    struct sockaddr_in servaddr;
    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(MYPORT);  ///服务器端口
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");  ///服务器ip

 
    ///连接服务器，成功返回0，错误返回-1
    if (connect(sock_cli, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0)
    {
        perror("connect");
        exit(1);
    }
    //puts("connect success");

    //openat( server_sockfd, "foo.log", O_RDONLY );
    int epollfd = epoll_create1( EPOLL_CLOEXEC );
    if( epollfd == -1 )
    {
        std::cerr << "epoll_create failed: " << epollfd << std::endl;
    }
    struct epoll_event ev;
    ev.events = EPOLLIN;
    ev.data.fd = 0; //
    if( epoll_ctl( epollfd, EPOLL_CTL_ADD, ev.data.fd, &ev )  )
    {
        std::cout << "epoll_ctl add td server fd failed: " << strerror(errno) << std::endl;
    }
    else
    {
        std::cout << "epoll_ctl success: " << strerror(errno) << std::endl;
    }
 
    char sendbuf[BUFFER_SIZE]="abcdefg12345";
    char recvbuf[BUFFER_SIZE]={0};
    //while (fgets(sendbuf, sizeof(sendbuf), stdin) != NULL)
    int times = 5;
    while (times--)
    {
        send(sock_cli, sendbuf, strlen(sendbuf),0); ///发送
        sleep(1);
        if(strcmp(sendbuf,"exit\n")==0)
            break;
        int len = recv(sock_cli, recvbuf, sizeof(recvbuf),0); ///接收
        printf("\nrecv data length %d :", len);
        fputs(recvbuf, stdout);
 
        //memset(sendbuf, 0, sizeof(sendbuf));
        memset(recvbuf, 0, sizeof(recvbuf));
    }
    printf( "close socket: %d\n", sock_cli ); 
    close( sock_cli );

    }
 
//    close(sock_cli);
    return 0;
}
