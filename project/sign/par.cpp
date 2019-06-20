#include <iostream>
#include <netdb.h>
#include <arpa/inet.h>
#include <netinet/if_ether.h>
#include <string.h>
using namespace std;
int main()
{
    struct addrinfo *result;
    if(getaddrinfo("192.168.3.1",NULL,NULL,&result) == 0) {
        cout << "成功" << endl;
        if(result) {
            cout << inet_ntoa(((struct sockaddr_in *)result->ai_addr)->sin_addr) << endl;
        }
    }
    
    cout << 0x0806 << endl;
    cout << ETHERTYPE_ARP << endl; 
    unsigned char i = 15;
    int m = i;
    cout.width(2);
    cout.fill('0');
    cout  << hex <<  m;

    return 0;
}

