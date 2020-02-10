#pragma once
#include <iostream>
#include <netdb.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <fstream>
#include <pthread.h>
#include <vector>
#include <sys/stat.h>
#include <cstdio>
#include <iomanip>
#include <thread>
#include <openssl/ssl.h>
#include <openssl/bio.h>


using namespace std;
class HttpOperation{
public:
    string url;     
    string downfile; //保存文件名
    string port;       //端口号
    string host;    //远程主机地址
    string filename;    //下载的文件名
    string datapath;    //资源路径
    string ip_addr; //主机ip地址
    string head;    //http头
    int fd;         //套接字
    string buf;     //缓冲区
    int size;       //下载的文件大小
    string type;    //下载文件的类型
    int protocol;
    SSL_CTX *ssl_ct;//SSL会话环境
    SSL *ssl;       //SSL套接字

    HttpOperation(string _url) : url(_url) {  }

    void Parse();   //解析URL链接,返回０为http协议,返回１为https

    void GetIpAddr();//通过域名得到对应的ip地址

    int Connect();//建立连接

    void SendHttpHead(long start,long end);//发送http请求头

    int ConnectSSL();//建立SSL连接
    
    void ReadHttpHead();//读取http响应头

    int HttpRead(char *buf,size_t len);

    int HttpWrite(char *buf,size_t len);

    void ParseHead();//解析响应头

    void Close();//关闭TCP连接

    void CloseSSL();//关闭SSL连接
};

