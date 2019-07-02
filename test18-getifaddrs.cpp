#include <stdio.h>      
#include <sys/types.h>
#include <ifaddrs.h>
#include <netinet/in.h> 
#include <string.h> 
#include <arpa/inet.h>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <algorithm>
#include <vector>

#include <ifaddrs.h>
#include <net/if.h>
#include <netpacket/packet.h>
#include <sys/utsname.h>
#include <cpuid.h>
#include <linux/hdreg.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <scsi/sg.h>

using namespace std;

int main (int argc, const char * argv[]) {
    struct ifaddrs * ifAddrStruct=NULL;
    void * tmpAddrPtr=NULL;

    getifaddrs(&ifAddrStruct);

    while (ifAddrStruct!=NULL) {
        if (ifAddrStruct->ifa_addr->sa_family==AF_INET) { // check it is IP4

            // is a valid IP4 Address
            tmpAddrPtr=&((struct sockaddr_in *)ifAddrStruct->ifa_addr)->sin_addr;
            char addressBuffer[INET_ADDRSTRLEN];
            inet_ntop(AF_INET, tmpAddrPtr, addressBuffer, INET_ADDRSTRLEN);
			cout << "[test inet_ntoa]" << inet_ntoa( ((struct sockaddr_in *)ifAddrStruct->ifa_addr)->sin_addr ) << endl;

            // get mac addr
            struct sockaddr_ll* s = (struct sockaddr_ll*)ifAddrStruct->ifa_addr;
            stringstream   stream;
            for( int i = 0; i < (int)s->sll_halen; i++ )
            {
                stream << setfill( '0' ) << setw( 2 ) << hex
                       << (int)s->sll_addr[i];
                cout << stream.str() << endl;
            }
            
            //print
            printf("[%s] IP4 Address: %s| MAC: %s\n", ifAddrStruct->ifa_name, addressBuffer, stream.str().c_str()); 
        } else if (ifAddrStruct->ifa_addr->sa_family==AF_INET6) { // check it is IP6
            // is a valid IP6 Address
            tmpAddrPtr=&((struct sockaddr_in *)ifAddrStruct->ifa_addr)->sin_addr;
            char addressBuffer[INET6_ADDRSTRLEN];
            inet_ntop(AF_INET6, tmpAddrPtr, addressBuffer, INET6_ADDRSTRLEN);
            printf("[%s] IP6 Address: %s\n", ifAddrStruct->ifa_name, addressBuffer); 
        } 
        ifAddrStruct=ifAddrStruct->ifa_next;
    }
	
	cout << "Test MAC address" << endl;
	std::string mac( "12:34:56:78:9A:bc" );
	cout << "Origianl MAC address: " << mac <<endl;
    mac.erase( std::remove( mac.begin(), mac.end(), ':'), mac.end() );
    std::transform( mac.begin(), mac.end(), mac.begin(), ::toupper );
	cout << "Processed MAC address: " << mac << endl;
	
	unsigned char mac_arr[6];
	//memcpy(mac_arr, mac.c_str(), 6);
	stringstream stream(mac);
	for( int i=0; i<6; i++)
		stream >> setw(2) >> hex  >> mac_arr[i];
	cout << "char array of MAC: ";
	for( int i=0; i<6; i++)
		cout << mac_arr[i] << ":";
	cout << "\nFailed !" << endl;

	//每隔两位插入一个':'
	for( int i = mac.length()-2; i>1; i = i -2 )
		mac.insert(i, 1, ':');
	cout << "second processed MAC address: " << mac << endl;

	//test lookthrough info
	string infostr("terminal type@timestamp@local IP1@local IP2@MACaddr1@MAC addr2@hostname@os version@harddisk serial@cpu@@test@");
	cout << infostr << endl;
	vector<std::string> vec_str;
    char token = '@';
    size_t pos = infostr.find( token );
    size_t size = infostr.size();

    while( pos != std::string::npos )
    {
        vec_str.push_back( infostr.substr(0, pos));
        infostr = infostr.substr(pos+1, size);
        pos = infostr.find( token );
    }
	vec_str.push_back( infostr );

	for( int i=0; i< vec_str.size(); i++)
	{
		cout << vec_str[i] << endl;
	}

	cout << "TEST how print mac_add:";
	for( int i =0; i<6; i++)
	{
		cout << i << (i<5?':':' ');
	}
	cout << endl;

	char tmp[10] ={'1','2','3'};
	cout << tmp << "<<<" << endl;;
	cout << string(tmp,10) << "<<<" << endl;	
	
	cout << "test conver mac_add:" << endl;
	unsigned char mac_addr[6];
	int values[6];
    sscanf ( "40:f2:e9:cb:bb:6a", "%02x:%02x:%02x:%02x:%02x:%02x",
                &values[0], &values[1], &values[2],
                &values[3], &values[4], &values[5]);
    for(size_t i = 0 ; i<6; i++)
    {
        mac_addr[i] = values[i];
		cout << "mac_addr[" << i <<"]:" << (unsigned int)mac_addr[i] << endl;
    }



    return 0;
}	
