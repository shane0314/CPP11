#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>

using namespace std;

struct Message{
    string macaddr;
    string diskuuid;
    string getmacaddr() const { return macaddr; }
    string getdiskuuid() const { return diskuuid; }
    void setmacaddr(string str) { macaddr = str; }
    void setdiskuuid(string str) { diskuuid = str; }
};

int main()
{
    Message msg;
    msg.setmacaddr( string("00:50:56:a3:4b:41") );
    msg.setdiskuuid( string("92D7FC20-6FAD-4367-B018-887E8307682E") );

    string m_macaddr = msg.getmacaddr();
    string m_diskuuid = msg.getdiskuuid();

    m_macaddr.erase( std::remove(m_macaddr.begin(), m_macaddr.end(), ':' ), m_macaddr.end() );

    stringstream ss;
    ss << "MAC:" << m_macaddr 
       << ";HD:" << m_diskuuid;
    
    cout << "mac and disk uuid = " << ss.str() << std::endl;

    return 0;
}
