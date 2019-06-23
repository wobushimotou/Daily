#pragma once
#include <string>
#include <sstream>
#include <stdio.h>
#include <netinet/if_ether.h>
#include <net/if_arp.h>             
#include <net/ethernet.h>           
#include <netpacket/packet.h>       
#include <net/if.h>                 
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <netinet/in.h>
#include <net/ethernet.h>
#include <string.h>

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
    Arp(string &dst):dst_ip(dst),buf(NULL) {  }
    Arp(void):buf(NULL){  }
    ~Arp() {
        if(buf)
            delete buf;
    }

    //根据dst_ip构造arp请求报,返回数据报首地址
    char *ArpFill();  
    //解析arp应答报，返回应答中的目标mac地址的字符串
    string ArpAnalysis(char *arp);
    struct sockaddr_ll GetAddr() {
        return arp_addr;
    }
private:
    //目标ip
    string dst_ip;
    //arp数据报缓冲区
    char *buf;
    //网卡信息
    struct sockaddr_ll arp_addr; 
};

