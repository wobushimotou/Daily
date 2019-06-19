#include "Thread_Download.h"
#include <iostream>

//解析url链接
void HTTP::Parse() {
    string::size_type pos; 
    //解析域名
    pos = url.find("//");
    url = url.substr(pos+2,url.length()-pos-2);
    pos = url.find("/");
    host = url.substr(0,pos);

    //解析端口号
    pos = url.find(":");
    if(pos != string::npos) {
        port = url.substr(pos+1,url.find_first_not_of("0123456789",pos+1));
        //删除域名内的端口号
        pos = host.find_first_of(":",0);
        host = host.substr(0,pos);
    }
   //解析ip地址
    auto h = gethostbyname(host.c_str()); 
    if(h->h_addr_list[0])
        ip_addr = inet_ntoa(*((struct in_addr *)h->h_addr_list[0]));

    /*
    struct addrinfo hints,*res;
    bzero(&hints,sizeof(struct addrinfo));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = 0;
    int n;
    
    
    if( (n = (getaddrinfo(host.c_str(),NULL,&hints,&res))) != 0 ) {
        std::cout << "getaddrinfo error" << std::endl;
    }
    for(auto p = res;p;p = p->ai_next) {
        std::cout << inet_ntoa(((struct sockaddr_in *)p->ai_addr)->sin_addr) << std::endl;
        std::cout << ntohs(((struct sockaddr_in *)p->ai_addr)->sin_port) << std::endl;
    }

    char host[20];
    char serv[20];
    bzero(host,20);
    bzero(serv,20);
    getnameinfo(res->ai_addr,sizeof(struct sockaddr),host,20,serv,20,NI_NUMERICHOST);
    std::cout << "主机名=" << host << std::endl;
    std::cout << "服务名=" << serv << std::endl;
    freeaddrinfo(res);
    */

    std::cout << url << std::endl;
    std::cout << port << std::endl;
    std::cout << host << std::endl;
    std::cout << ip_addr << std::endl;
    std::cout << h->h_name << std::endl;

}

//设置http请求头并发送
void HTTP::SendHttpHead(long start,long end) {
    string head = "GET "+url+" HTTP/1.1\r\n"+
            "Accept: */*\r\n"+
            "Host: "+host+"\r\n"+
            "Connection: keep-alive\r\n"+
            "Range: bytes="+to_string(start)+"-"+((end>0)?to_string(end):"")+"\r\n"+
            "\r\n";
        
}

//接收http响应头
void HTTP::ReadHttpHead() {
    unsigned char ch;
    while(1) {
        read(fd,&ch,1);
        buf.push_back(ch);
        int flag = 0;
        for(auto p = buf.rbegin();*p == '\r' || *p == '\n';++p,++flag);

        if(flag == 4)
            break;
    }
}
//解析http响应头
pair<int,string> HTTP::ParseHead() {
    int size;
    string type;
    //得到文件大小
    int i = buf.find("Content-Length:",0);

    size = 0;
    for(int j = i+16;buf.at(j) > '0' && buf.at(j) < '9';++j)
        size = size*10 + buf.at(j) - '0';

    //得到文件类型
    i = buf.find("Content-Type:",0);
    i += 13;
    for(;buf.at(i) != '\r';++i) {
        type.push_back(buf.at(i));
        if(buf.at(i) == '/')
            type = "";
    }

    //解析完释放缓冲区
    buf = "";
    return make_pair(size,type);
}


//与远程服务器建立连接
int HTTP::Connect() {
    fd = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
    if(fd < 0) {
        std::cout << "套接字创建失败" << std::endl;
        exit(0);
    }

    struct sockaddr_in addr;
    memset(&addr,0,sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr(ip_addr.c_str());
    addr.sin_port = htons(atoi(port.c_str()));

    int res = connect(fd,(struct sockaddr *)&addr,sizeof(addr));
        if(res == -1) {
            cout << "连接失败" << endl;
            return 0;
        }
        return 1;
}


