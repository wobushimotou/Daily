#include <iostream>
#include "Arp2.h"
char *Arp::ArpFill() {
    //存储arp应答数据报的缓冲区
    buf = new char[ETHER_ARP_PACKET_LEN];
    string src_ip;
    unsigned char src_mac_addr[6];
    unsigned char dst_mac_addr[6] = BROADCAST_ADDR;
    

    int sockfd = socket(AF_INET,SOCK_STREAM,0);
    struct ifreq ifr;
    bzero(&ifr,sizeof(ifr));
    memcpy(ifr.ifr_name,"wlp4s0",strlen("wlp4s0"));
    
    /* 获取网卡接口IP地址 */
    if(ioctl(sockfd,SIOCGIFADDR,&ifr) == -1) {
        cout << "获取网卡接口ip失败" << endl;
        exit(0);
    }
    src_ip = inet_ntoa(((struct sockaddr_in *)&ifr.ifr_ifru.ifru_addr)->sin_addr);

    /* 获取网卡接口MAC地址 */
    if (ioctl(sockfd, SIOCGIFHWADDR, &ifr))
        cout << "获取网卡接口mac地址失败" << endl;
    memcpy(src_mac_addr, ifr.ifr_hwaddr.sa_data, ETH_ALEN);

    //获取网卡接口索引
    bzero(&arp_addr,sizeof(arp_addr));
    if (ioctl(sockfd, SIOCGIFINDEX, &ifr) == -1)
        cout << "获取接口索引失败" << endl;
    arp_addr.sll_ifindex = ifr.ifr_ifindex;
    arp_addr.sll_family = PF_PACKET;

    //填充以太帧首部
    struct ether_header *arp_head;
    bzero(&arp_head,sizeof(arp_head));
    
    arp_head = (struct ether_header *)buf;
    memcpy(arp_head->ether_shost,src_mac_addr,ETH_ALEN);
    memcpy(arp_head->ether_dhost,dst_mac_addr,ETH_ALEN);
    arp_head->ether_type = htons(ETHERTYPE_ARP);

    //填充arp数据报内容
    struct ether_arp *arp_data = (struct ether_arp *)(buf+ETHER_HEADER_LEN);
    arp_data->arp_hrd = htons(ARPHRD_ETHER);
    arp_data->arp_pro = htons(ETHERTYPE_IP);
    arp_data->arp_hln = ETH_ALEN;
    arp_data->arp_pln = IP_ADDR_LEN;
    arp_data->arp_op = htons(ARPOP_REQUEST);

    struct in_addr src_ip_addr,dst_ip_addr;
      /* IP地址转换 */
    inet_pton(AF_INET, src_ip.c_str(), &src_ip_addr);
    inet_pton(AF_INET, dst_ip.c_str(), &dst_ip_addr);

    memcpy(arp_data->arp_sha,src_mac_addr,ETH_ALEN);
    memcpy(arp_data->arp_tha,dst_mac_addr,ETH_ALEN);
    memcpy(arp_data->arp_spa,&src_ip_addr,IP_ADDR_LEN);
    memcpy(arp_data->arp_tpa,&dst_ip_addr,IP_ADDR_LEN);

    return buf;
}

string Arp::ArpAnalysis(char *arp) {
    stringstream istr;
    struct ether_arp *arp_data = (struct ether_arp *)(arp+ETHER_HEADER_LEN);

    if(ntohs(arp_data->arp_op) == 2) {
        for (int i = 0; i < ETH_ALEN; i++) {
            int m = arp_data->arp_sha[i];
            if(i == ETH_ALEN-1) {
                istr << hex << m;
                continue;
            }
            istr << hex << m << ":";
        }
        return istr.str();
    }
    return "";
}
