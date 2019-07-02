
#pragma pack(1)

#include "myHfile.h"

#define int32_t int
#define uint32_t unsigned int
#define LOG_ERROR cout

void test6(const char *str)
{
	cout << "the len of string is: " << strlen(str) <<endl;
	cout << "the string is: " << str <<endl;
}

struct MsgHeader
{
    uint32_t msgType;
    uint32_t bodyLength;
};

struct MsgTail
{
    uint32_t checkSum;
};

struct MsgLogon
{
    MsgHeader   standardHeader;

    char        senderCompID[20]; //[20+1];
    char        targetCompID[20];
    int32_t    heartBtInt;
    char        password[16];
    char        defaultApplVerID[32];

    MsgTail     standardTail;
};

struct MsgLogout
{
    MsgHeader   standarHeader;

    int32_t    sessionStatus;
    char       text[200];

    MsgTail     standarTail;
};

void msgAssign(char *buf, uint32_t buflen, const char *src)
{
    if( !buf || buflen == 0 )
    {
        LOG_ERROR << "Buffer is not big enough to process a single message, increase buffer size! Unrecoverable error, exiting..." << endl;
        return;
    }
    size_t idx=0;
    for( ; idx < strlen(src) && idx < buflen; idx++)
	{
		cout << "[Debug]" <<"src[" << idx <<"]=" << src[idx]<<endl;		
		buf[idx] = src[idx];
    }
    if( idx < buflen)
        for(; idx < buflen; buf[idx++] = '*');
}

void msgAssign(char *buf, uint32_t buflen, const string &src)
{
    if( !buf || buflen == 0 )
    {
        LOG_ERROR << "Buffer is not big enough to process a single message, increase buffer size! Unrecoverable error, exiting..." << endl;
        return;
    }
    size_t idx=0;
    for( ; idx < src.length() && idx < buflen; buf[idx] = src[idx], idx++)
        
    if( idx < buflen)
        for(; idx < buflen; buf[idx++] = ' ');
}

void show(char * buff, int size)
{	
	if( !buff || size==0 )
		return;
	cout << "BUFFER" <<"[" <<size <<"]:";
	for( int i=0; i<size; i++ )
		cout<<buff[i];
	cout << endl;
}

int main()
{
	cout << "sizeof(MsgHeader)=" << sizeof( MsgHeader) << endl;
	cout << "sizeof(MsgTail)=" << sizeof( MsgTail) <<endl;
	cout << "sizeof(MsgLogon)=" << sizeof( MsgLogon) <<endl;
	cout << "sizeof(MsgLogout)=" << sizeof( MsgLogout) <<endl;
/*
	char buff[20];
	char cstr[]="hello world";
	msgAssign( buff, 20, cstr );
	show( buff, 20);
	
	msgAssign( buff, 20, "Hello world2");
	show( buff, 20 );
*/
	return 0;
}
