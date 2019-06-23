/*
 构造arp请求报,解析应答报
  */

#pragma once
#include <iostream>
#include <string>
#include <netinet/if_ether.h>       
#include <net/if_arp.h>             
#include <net/ethernet.h>           
#include <netpacket/packet.h>       
#include <net/if.h>                 
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <netinet/in.h>
#include <net/ethernet.h>

/* 以太网帧首部长度 */
#define ETHER_HEADER_LEN sizeof(struct ether_header)
/* 整个arp结构长度 */
#define ETHER_ARP_LEN sizeof(struct ether_arp)
/* 以太网 + 整个arp结构长度 */
#define ETHER_ARP_PACKET_LEN ETHER_HEADER_LEN + ETHER_ARP_LEN
/* IP地址长度 */
#define IP_ADDR_LEN 4
/* 广播地址 */
#define BROADCAST_ADDR {0xff, 0xff, 0xff, 0xff, 0xff, 0xff}



using namespace std;
class Arp
{
public:
    Arp(string &dst) : dst_ip(dst){  
        if ((sock_raw_fd = socket(PF_PACKET, SOCK_RAW, htons(ETH_P_ARP))) == -1)
            cout << "套接字申请失败" << endl;
    }
    Arp() {  
        if ((sock_raw_fd = socket(PF_PACKET, SOCK_RAW, htons(ETH_P_ARP))) == -1)
            cout << "套接字申请失败" << endl;
    }
    ~Arp() {
        close(sock_raw_fd);
   }
    Arp &operator=(string &dst) {
        this->dst_ip = dst;
        return *this;
    }

    int arpSend();   //发送arp帧
    string arpRecv();  //接收arp帧
    int arpFill();  //填充arp帧
    struct ether_arp *arp_data; //arp分组

private:
    int sock_raw_fd;    //原始套接字
    string src_ip;      //源ip地址
    string dst_ip;      //目的ip地址
    string src_mac_addr;  //源mac地址
    string dst_mac_addr;    //目的mac地址
    struct ether_header *arp_head;    //arp帧首部
    struct sockaddr_ll arp_addr;//物理地址结构
    char buf[ETHER_ARP_PACKET_LEN];//缓冲区
};

