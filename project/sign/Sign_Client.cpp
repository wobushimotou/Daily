#include <iostream>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "Arp.h"

#define SERVER_PORT 8888
int main()
{
    Arp RecvArp;
    char buf[ETHER_ARP_PACKET_LEN];
    //申请套接字
    int socketfd = socket(AF_INET,SOCK_STREAM,0);
    int sawfd = socket(PF_PACKET,SOCK_RAW,htons(ETH_P_ARP));

    sockaddr_in sockaddr;
    sockaddr.sin_family = AF_INET;
    sockaddr.sin_port = htons(SERVER_PORT);
    sockaddr.sin_addr.s_addr = inet_addr("127.0.0.1"); 
    

    if(connect(socketfd,(struct sockaddr*)&sockaddr,sizeof(sockaddr)) == 0) {
        //连接服务器成功
        cout << "connected" << endl;
        char ch = 'c';
        bzero(buf,sizeof(buf));
        send(socketfd,&ch,1,0);
        int len = 1;
        while(len) {
            len = recv(sawfd,buf,sizeof(buf),0);
            cout << len << endl;
            if(len == sizeof(buf)) {
                cout << RecvArp.ArpAnalysis(buf) << endl;
            }
        
        }
    }
    return 0;
}

