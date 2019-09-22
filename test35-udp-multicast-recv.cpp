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

int main(void)
{
	char group_ip[20];
	int group_port = 11111;
	strcpy(group_ip, "231.1.1.1");

	char recvmsg[256];

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
	
	memset( &group_addr, 0, sizeof(struct sockaddr_in) );
	group_addr.sin_family = AF_INET;
	group_addr.sin_port = htons( group_port );
	group_addr.sin_addr.s_addr = inet_addr( group_ip );

	memset( &local_addr, 0, sizeof(local_addr) );
	local_addr.sin_family = AF_INET;
	local_addr.sin_port = htons( group_port );
	local_addr.sin_addr.s_addr = INADDR_ANY;

	if( bind(socket_fd, (struct sockaddr*)&group_addr, sizeof(local_addr)) < 0 )
	{
		perror("bind mulitcast failed!");
		exit(1);	
	}
	std::cout << "bind multicast success!" << std::endl;
	
	mreq.imr_multiaddr.s_addr = inet_addr(group_ip);
	mreq.imr_interface.s_addr = INADDR_ANY;
	if( setsockopt( socket_fd, IPPROTO_IP, IP_ADD_MEMBERSHIP, &mreq, sizeof(mreq) ) < 0 )
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
						(struct sockaddr*)&group_addr, &addr_len );
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
