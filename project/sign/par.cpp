#include <iostream>
#include <netdb.h>
#include <arpa/inet.h>
#include <netinet/if_ether.h>
#include <string.h>
#include <sstream>
using namespace std;
int main()
{
    string dst = "192.168.3.1";
    cout << dst.substr(0,dst.rfind(".",dst.length() - 1)+1) << endl;
    return 0;
}

