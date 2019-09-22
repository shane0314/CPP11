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

	memset( &group_addr, 0, sizeof(struct sockaddr_in) );
	group_addr.sin_family = AF_INET;
	group_addr.sin_port = htons( group_port );
	group_addr.sin_addr.s_addr = inet_addr( group_ip );
	
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
} 
