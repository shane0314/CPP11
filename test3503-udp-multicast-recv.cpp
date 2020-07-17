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

using namespace std;

int main( int argc, char* args[] )
{
	char mcast_ip[20];
    char source_ip[20];
    char local_ip[20];
	if( argc < 5 )
	{
		std::cout << "Usage : ./t3503 <mcast-ip> <mcast-port> <source-ip> <local-ip>" << std::endl;
		exit(1);
	}
	strcpy( mcast_ip, args[1] );
	int mcast_port = atoi( args[2] );
	strcpy( source_ip, args[3] );
	strcpy( local_ip, args[4] );
    
	//int mcast_port = 11111;
	//strcpy(mcast_ip, "231.1.1.1");

	char recvmsg[256];

	struct sockaddr_in mcast_addr; //group address
	//struct sockaddr_in local_addr; //local address
	struct ip_mreq_source mreq;
	socklen_t addr_len = sizeof(mcast_addr);

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
	
	memset( &mcast_addr, 0, sizeof(struct sockaddr_in) );
	mcast_addr.sin_family = AF_INET;
	mcast_addr.sin_port = htons( mcast_port );
	mcast_addr.sin_addr.s_addr = inet_addr( mcast_ip );
/*
	memset( &local_addr, 0, sizeof(local_addr) );
	local_addr.sin_family = AF_INET;
	local_addr.sin_port = htons( mcast_port );
	local_addr.sin_addr.s_addr = mcast_ip;
*/
	if( bind(socket_fd, (struct sockaddr*)&mcast_addr, sizeof(mcast_addr)) < 0 )
	{
		perror("bind mulitcast failed!");
		exit(1);	
	}
	std::cout << "bind multicast success!" << std::endl;
	
	mreq.imr_multiaddr.s_addr = inet_addr(mcast_ip);
	mreq.imr_interface.s_addr = inet_addr(local_ip);
	mreq.imr_sourceaddr.s_addr = inet_addr(source_ip);
	if( setsockopt( socket_fd, IPPROTO_IP, IP_ADD_SOURCE_MEMBERSHIP, &mreq, sizeof(mreq) ) < 0 )
	{
		std:cerr << ( "setsockopt multicast failed!") << std::endl;
		exit(1);
	}
	std::cout << "setsockopt multicast successed!" << std::endl;

	while(1)
	{
		/*recv*/
		memset(recvmsg, 0, sizeof(recvmsg) );
		auto n = recvfrom( socket_fd, recvmsg, sizeof(recvmsg)-1, 0, 
						(struct sockaddr*)&mcast_addr, &addr_len );
		if( n < 0 )
		{
			std::cerr << "recvfrom failed!" << std::endl;
			exit(4);
		}
		else
		{
			recvmsg[n] = 0;
			std::cout << "received msg:" << recvmsg << std::endl;
		}
	}
} 
