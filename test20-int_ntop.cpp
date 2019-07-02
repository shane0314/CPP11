#include <stdio.h>   
#include <sys/socket.h>   
#include <netinet/in.h>   
#include <arpa/inet.h>   
#include <string.h>   
#include <sstream>
#include <boost/array.hpp>


int main()   
{ 
    struct in_addr addr1,addr2; 
    //struct in_addr in_addr3(3162834149);
    unsigned long l1,l2; 
    l1= inet_addr("192.168.0.74"); 
    l2 = inet_addr("211.100.21.179"); 
    memcpy(&addr1, &l1, 4); 
    memcpy(&addr2, &l2, 4); 

    printf("%s : %s\n", inet_ntoa(addr1), inet_ntoa(addr2)); //注意这一句的运行结果   

    //printf("%s : %s\n", addr1.toString(), addr2.toStringi()); //注意这一句的运行结果   
    printf("%ud : %ud\n", addr1, addr2); //注意这一句的运行结果   
    
    addr1.s_addr = 3162834149u;

    char ip1[20];
    const char * tmp = inet_ntop(AF_INET, &addr1, ip1, 16);
    const std::string str = ip1;
    printf("str:%s\n", str.c_str()); 
    std::stringstream ss;
    
    ss << "IIP:" << str;

    printf("%s = %s\n", tmp, ss.str().c_str());     
    
    boost::array<char, 20> ovs;
    ::strncpy(ovs.data(), "4.4.0-141-generic" , 20);

    std::string ovs_str = ovs.data();
    printf("ovs_str:%s\n", ovs_str.c_str());
//    printf("%s\n", inet_ntop(addr1)); 
  //  printf("%s\n", inet_ntop(addr2)); 
    return 0; 

}

