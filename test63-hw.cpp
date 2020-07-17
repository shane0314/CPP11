#include <iostream>
using namespace std;

bool isN( char c )
{
    return c <='9' && c>='0';
}
bool isS( char c )
{
    return c == '+' || c == '-';
}
bool isD( char c )
{
    return c == '.';
}
//return length
//nextP: next position of finding a number
int findNum( const char* s, int& nextP )
{
    //int len = 0;
    int i = 0;
    bool haveDot = false;
    bool begin = false;
    nextP = 0;
    if( s[0]!='\0' && isS( s[0] ) && s[1]!='\0' && !isN( s[1] ) )
    {
        return 0;
    }
    if( s[0]!='\0' && isS( s[0] ) )
    {
        ++i;
    }
    while( true )
    {
        char c = s[i];
        if( c == '\0' )
        {
            nextP = -1;
            return i;
        }
        if( !isN(c) && !isD(c) )
        {
            return i;
        }
        if( isD(c) && isS(s[i-1]) )
        {
            nextP = i+1;
            return 0;
        }
        if(  isD(c) && haveDot
           || isD(c) && !isN(s[i+1])
           || isD(c) && !isN(s[i-1]) )
        {
            return i;
        }
        if( isD(c) )
        {
            nextP = i+1;
            haveDot = true;
        }
        if( c == '0' && !begin )
        {
            nextP = i+1;
            return 0;
        }
        begin = true;
        ++i;
    }
}
int main() {
    string str;
    getline(cin, str);
    const char* s = str.data();
    //cout <<　str << endl;
    int p1 = 0;
    int nextP = 0;
    int maxLen = 0;
    int maxPos = 0;
    for( int i = 0; i< str.size(); ++i )
    {
        if( isN(s[i]) || isS(s[i]) )
        {
            int len = findNum( s+i, nextP );
            if( len >= maxLen )
            {
                maxLen = len;
                maxPos = i;
            }
            if( nextP > 0 )
            {
                i += nextP;
            }
            else
            {
                i += len;
            }
        }
    }
    cout << str.substr(maxPos, maxLen) << endl;
}
