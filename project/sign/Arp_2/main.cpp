#include <iostream>
#include "Arp.h"
#include <thread>
void Recv(int sockfd) {
    int ret_len;
    char buf_recv[ETHER_ARP_PACKET_LEN];
    Arp arp;
    while(1) {
        ret_len = recv(sockfd,buf_recv,sizeof(buf_recv),0);
        if(ret_len == sizeof(buf_recv)) {
            cout << arp.ArpAnalysis(buf_recv) << endl;
        }
 
    }
}

int main()
{
    string dst = "192.168.3.";
    int sockfd;

    sockfd = socket(PF_PACKET,SOCK_RAW,htons(ETH_P_ARP));
    if(sockfd < 0) {
        cout << "create raw socket error" << endl;
        exit(0);
    }


    thread t(Recv,sockfd);
    t.detach();
    for(int i = 1;i < 256;++i) {
        string dst_ip = dst + to_string(i);
        Arp arp = dst_ip;
        char *buf_send = arp.ArpFill();
        struct sockaddr_ll arp_addr = arp.GetAddr();
        sendto(sockfd, buf_send, ETHER_ARP_PACKET_LEN, 0, (struct sockaddr *)(&arp_addr), sizeof(struct sockaddr_ll));
    }
    sleep(1);
    return 0;
}

