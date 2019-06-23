#include <iostream>
#include "Arp2.h"
int main()
{
    string dst = "192.168.3.1";
    int sockfd,ret_len;

    sockfd = socket(PF_PACKET,SOCK_RAW,htons(ETH_P_ARP));
    if(sockfd < 0) {
        cout << "create raw socket error" << endl;
        exit(0);
    }
    
    Arp arp(dst);
    char *buf_send = arp.ArpFill();
    struct sockaddr_ll arp_addr = arp.GetAddr();

    ret_len = sendto(sockfd, buf_send, ETHER_ARP_PACKET_LEN, 0, (struct sockaddr *)(&arp_addr), sizeof(struct sockaddr_ll));
    
    char buf_recv[ETHER_ARP_PACKET_LEN];
    bzero(buf_recv,sizeof(buf_recv));
    ret_len = recv(sockfd,buf_recv,sizeof(buf_recv),0);
    if(ret_len == sizeof(buf_recv)) {
        cout << arp.ArpAnalysis(buf_recv) << endl;
    }
    return 0;
}

