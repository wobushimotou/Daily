#include <iostream>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <vector>
#include <thread>
#include "Arp.h"

#define SERVER_PORT 8888
vector<string> vec;
void Recv(int sawfd) {
    int ret_len;
    char buf_recv[ETHER_ARP_PACKET_LEN];
    Arp arp;
    while(1) {
        ret_len = recv(sawfd,buf_recv,sizeof(buf_recv),0);
        if(ret_len == sizeof(buf_recv)) {
            string s = arp.ArpAnalysis(buf_recv);
            if(s.size() > 0)
                cout << s << endl;
        }
    }
}
int main()
{
    Arp RecvArp;
    char buf[ETHER_ARP_PACKET_LEN];
    //申请套接字
    int socketfd = socket(AF_INET,SOCK_STREAM,0);
    int sawfd = socket(PF_PACKET,SOCK_RAW,htons(ETH_P_ARP));
    //开启线程去接收
    thread t(Recv,sawfd);
    t.detach();

    sockaddr_in sockaddr;
    sockaddr.sin_family = AF_INET;
    sockaddr.sin_port = htons(SERVER_PORT);
    sockaddr.sin_addr.s_addr = inet_addr("127.0.0.1"); 

    vector<string> vec;
    
   if(connect(socketfd,(struct sockaddr*)&sockaddr,sizeof(sockaddr)) == 0) {
        //连接服务器成功
        cout << "connected" << endl;
        char ch = 'c';
        bzero(buf,sizeof(buf));
        
       send(socketfd,&ch,1,0);

        while(true) {
            int len = recv(socketfd,&ch,1,0);
            if(len == 0) {
                //连接关闭
                break;
            }
            else if(len < 0) {
                if(errno != EWOULDBLOCK && errno != EINTR) {
                    break;
                }
            }
            else {
                //服务器端Arp请求发送完毕,退出程序
                cout << "服务端Arp请求发送完毕,退出程序" << endl;
                break;
            }
        }
    }
    cout << vec.size() << endl;
    return 0;
}

