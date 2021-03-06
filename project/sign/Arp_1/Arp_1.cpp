#include "Arp_1.h"
#include <iostream>
int Arp::arpFill() {
    struct in_addr src_in_addr, dst_in_addr;
    unsigned char dst_mac_addr[ETH_ALEN] = BROADCAST_ADDR;

    /* IP地址转换 */
    inet_pton(AF_INET, src_ip.c_str(), &src_in_addr);
    inet_pton(AF_INET, dst_ip.c_str(), &dst_in_addr);


    /* 整个arp包 */
    arp_data->arp_hrd = htons(ARPHRD_ETHER);
    arp_data->arp_pro = htons(ETHERTYPE_IP);
    arp_data->arp_hln = ETH_ALEN;
    arp_data->arp_pln = IP_ADDR_LEN;
    arp_data->arp_op = htons(ARPOP_REQUEST);

    memcpy(arp_data->arp_sha, src_mac_addr.c_str(), ETH_ALEN);
    memcpy(arp_data->arp_tha, dst_mac_addr, ETH_ALEN);
    memcpy(arp_data->arp_spa, &src_in_addr, IP_ADDR_LEN);
    memcpy(arp_data->arp_tpa, &dst_in_addr, IP_ADDR_LEN);
    return 1;
}

int Arp::arpSend() {
    

    struct ifreq ifr;
    unsigned char src_mac_addr[ETH_ALEN];
    unsigned char dst_mac_addr[ETH_ALEN] = BROADCAST_ADDR;
    int ret_len, i;



    bzero(&arp_addr, sizeof(struct sockaddr_ll));
    bzero(&ifr, sizeof(struct ifreq));
    /* 网卡接口名 */
    memcpy(ifr.ifr_name, "wlp4s0", strlen("wlp4s0"));


    /* 获取网卡接口索引 */
    if (ioctl(sock_raw_fd, SIOCGIFINDEX, &ifr) == -1)
        cout << "获取接口索引失败" << endl;
    arp_addr.sll_ifindex = ifr.ifr_ifindex;
    arp_addr.sll_family = PF_PACKET;


    /* 获取网卡接口IP */
    if (ioctl(sock_raw_fd, SIOCGIFADDR, &ifr) == -1)
        cout << "获取网卡接口ip失败" << endl;
    src_ip = inet_ntoa(((struct sockaddr_in *)&(ifr.ifr_addr))->sin_addr);


    /* 获取网卡接口MAC地址 */
    if (ioctl(sock_raw_fd, SIOCGIFHWADDR, &ifr))
        cout << "获取网卡接口mac地址失败" << endl;
    memcpy(src_mac_addr, ifr.ifr_hwaddr.sa_data, ETH_ALEN);

    for (i = 0; i < ETH_ALEN; i++) {
        this->src_mac_addr.push_back(src_mac_addr[i]);
    }

    bzero(buf, ETHER_ARP_PACKET_LEN);
    /* 填充以太首部 */
    arp_head = (struct ether_header *)buf;
    memcpy(arp_head->ether_shost, src_mac_addr, ETH_ALEN);    //源以太网地址
    memcpy(arp_head->ether_dhost, dst_mac_addr, ETH_ALEN);    //目的以太网地址

    arp_head->ether_type = htons(ETHERTYPE_ARP);              //0x0806

    arp_data = (struct ether_arp *)(buf+ETHER_HEADER_LEN);
    /* arp包 */
    arpFill();
    //memcpy(buf + ETHER_HEADER_LEN, arp_data, ETHER_ARP_LEN);


    /* 发送请求 */
    ret_len = sendto(sock_raw_fd, buf, ETHER_ARP_PACKET_LEN, 0, (struct sockaddr *)&arp_addr, sizeof(struct sockaddr_ll));
    return 1;
}

string Arp::arpRecv() {

    string dst_mac_addr;    
    bzero(buf, ETHER_ARP_PACKET_LEN);
    int i = 0;
    unsigned long ret_len = 0;
    while(ret_len < ETHER_ARP_PACKET_LEN) {
        ret_len += recv(sock_raw_fd, buf, ETHER_ARP_PACKET_LEN, 0);
    }
    /* 剥去以太头部 */
    arp_data = (struct ether_arp *)(buf + ETHER_HEADER_LEN);
    /* arp操作码为2代表arp应答 */
    if (ntohs(arp_data->arp_op) == 2)
    {
        for (i = 0; i < ETH_ALEN; i++) {
            dst_mac_addr.push_back(arp_data->arp_sha[i]);
        }
        return dst_mac_addr;
    }
    return "wh";
}
