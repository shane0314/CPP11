#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netdb.h>
#include <errno.h>
#include <iostream>
#include <unistd.h>
#include <net/if.h>

using namespace std;

int main( int argc, const char** argv )
{
    if( argc < 3 ) {
        std::cout << "usage : a.out mcast_ip port" << std::endl;
        return -1;
    }
    //std::string mcast_ip = argv[1];
    //std::string mcast_port = argv[2]
	const char* group_ip = argv[1];
	const int group_port = atoi(argv[2]);
	//strcpy(group_ip, "231.1.1.1");
    std::cout << "multicast addr " << group_ip << ":" << group_port << std::endl;

	const char sendmsgbase[]="test multicast, seq:";
	char sendmsg[256];
	strcpy( sendmsg, sendmsgbase );

	struct sockaddr_in group_addr; //group address
	struct sockaddr_in local_addr; //local address
	struct ip_mreq mreq;
	socklen_t addr_len = sizeof(group_addr);

	int socket_fd;
	socket_fd = socket(AF_INET, SOCK_DGRAM, 0);
	if( socket_fd < 0 )
	{
		perror("socket multicast failed");
		exit(1);
	}
	std::cout << "socket success!" <<  std::endl;

	//allow multiple sockets to use the same PORT number 
	u_int yes;
	if( setsockopt(socket_fd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(yes)) < 0 ) 
	{
		perror("Reusing ADDR failed");
		exit(1);
	}
	std::cout << "setsockopt SO_REUSEADDR success!" << std::endl;

	memset( &group_addr, 0, sizeof(struct sockaddr_in) );
	group_addr.sin_family = AF_INET;
	group_addr.sin_port = htons( group_port );
	group_addr.sin_addr.s_addr = inet_addr( group_ip );
	//group_addr.sin_addr.s_addr = INADDR_ANY;
	

    //send to specify interface
	struct in_addr localInterface;
	localInterface.s_addr = inet_addr("192.168.0.29");
	//localInterface.s_addr = inet_addr("127.0.0.1");
	if( setsockopt(socket_fd, IPPROTO_IP, IP_MULTICAST_IF, (char *) &localInterface, sizeof(localInterface)) <0)
	{
    	perror("setsockopt():IP_MULTICAST_IF ");
    	exit(1);
	}

	#if 0
	memset(&local_addr, 0, sizeof(local_addr) );
	local_addr.sin_family = AF_INET;
	//local_addr.sin_addr.s_addr = htonl(INADDR_ANY );
	local_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	//local_addr.sin_port = htons(group_port);

	if( bind( socket_fd, (struct sockaddr*)&local_addr, sizeof(local_addr)) < 0 )
	{
		perror( "bind multicast failed" );
		exit(1);
	}
	std::cout << "bind multicast success!" << std::endl;

    /* 指定接口 */
    struct ifreq nif;
    char *inface = "eth0";
    //strcpy(nif.ifr_name, inface);
    strncpy(nif.ifr_name, inface, IFNAMSIZ);

	/* 绑定接口 */
    if (setsockopt(socket_fd, SOL_SOCKET, SO_BINDTODEVICE, (char * )&nif, sizeof(nif) ) < 0)
    {
        printf("bind interface fail, errno: %d \r\n", errno);
		exit(1);
    }
    else
    {
        printf("bind interface success \r\n");
    }
	#endif


	int msgcount = 0;
	while(1)
	{
		/*send*/
		msgcount++;
		strcpy( sendmsg+sizeof(sendmsgbase)-1, to_string(msgcount).c_str() );	
		if( sendto( socket_fd, sendmsg, strlen(sendmsg), 0, (struct sockaddr*)&group_addr, sizeof(group_addr) ) < 0 )
		{
			std::cerr << "sendto failed!" << std::endl;
			exit(1);
		}
		std::cout << "sendto ok! msg:" << sendmsg << std::endl;
		sleep(1);
	}

    return 0;
} 
