#include <iostream>
#include <string.h>
#include <stdlib.h>

using namespace std;

bool branchid2ReffPrefix(char *branchid, char *reff) 

{

int x,m,n,p,q;

	char temp[2];



       x = atoi(branchid);



if ( x<1000 || x>4843 ) return false;



m = ( x - 1000 ) / 62;

n = ( x - 1000 ) % 62;



if ( m>=0 && m<=9 ) p = m+48;

else if ( m >=10 && m<=35) p = m+55;

else if ( m >=36 && m<=61) p = m+61;



if ( n>=0 && n<=9 ) q = n+48;

else if ( n >=10 && n<=35) q = n+55;

else if ( n >=36 && n<=61) q = n+61;



	temp[0] = p;

	temp[1] = q;



	memcpy(reff,temp,2);



return true;

}

int main()
{
	char mbid[]="03999";
	char mreff[2];
	if( branchid2ReffPrefix(mbid,mreff) )
		cout<<mbid<<"to"<<mreff<<endl;
	else
		cout << "fail!" <<endl;
	
}

