#include <iostream>
#include <netdb.h>
#include <arpa/inet.h>
#include <netinet/if_ether.h>
#include <string.h>
#include <sstream>
using namespace std;
int main()
{
    unsigned char m = 156;
    string buf;
    stringstream istr;
    istr << hex << (int)m;
    
    buf = istr.str(); 
    cout << buf << endl;
    return 0;
}

