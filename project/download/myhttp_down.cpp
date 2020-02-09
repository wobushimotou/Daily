#include "myhttp_down.h"

void HttpOperation::Parse() {   //解析URL链接
        //解析域名
        string::size_type i = 0;
        string::size_type start;
        for(i = 0;i < url.length();++i) {
            if(url.at(i) == '/' && url.at(i+1) == '/') 
                break;
        }
        start = i+2;
        for(int j = start;url.at(j) != '/';++j)
            host.push_back(url.at(j));

        //解析端口号
        for(i = start;i < url.length();++i)
            if(url.at(i) == ':') {
                i++;
                while(url.at(i) < '0' || url.at(i) > '9')
                    port.push_back(url.at(i++));         

            }
        if(port == "")
            port = "80";
        else {
            //删除域名里面的端口号
            int temp = host.find_first_of(':',0);
            host = host.substr(0,temp);
        } 

        //解析文件名
        auto p = url.begin();
        auto q = p;
        for(;p != url.end();++p) 
            if(*p == '/')
                q = p;

        filename = {q+1,url.end()};

    }
void HttpOperation::GetIpAddr() {//通过域名得到对应的ip地址
        struct hostent *h = gethostbyname(host.c_str());
        char ip[16];
        for(int i = 0;h->h_addr_list[i];i++) {
            strcpy(ip,inet_ntoa(*(struct in_addr*)h->h_addr_list[i]));
            break;
        }
        ip_addr = ip;
    }
int HttpOperation::Connect() {//建立连接
        fd = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);

        if(fd < 0) {
            cout << "套接字创建失败" << endl;
            return 0;
        }

        struct sockaddr_in addr;
        memset(&addr,0,sizeof(addr));
        addr.sin_family = AF_INET;
        addr.sin_addr.s_addr = inet_addr(ip_addr.c_str());
        addr.sin_port = htons(atoi(port.c_str()));


        int res = connect(fd,(struct sockaddr *)&addr,sizeof(addr));
        if(res == -1) {
            cout << "连接失败" << endl;
            return -1;
        }
        return fd;
    }

void HttpOperation::SendHttpHead(long start,long end) {//发送http请求头
        
    //设置http请求头
        head = "GET "+url+" HTTP/1.1\r\n"+
            "Accept: */*\r\n"+
            "Host: "+host+"\r\n"+
            "Connection: keep-alive\r\n"+
            "Range: bytes="+to_string(start)+"-"+((end>0)?to_string(end):"")+"\r\n"+
            "\r\n";
            //发送
        send(fd,head.c_str(),head.length(),0); 
    }

void HttpOperation::ReadHttpHead() {//读取http响应头
        unsigned char temp;
        while(true) {
            read(fd,&temp,1);
            buf.push_back(temp);
            int flag = 0;
            for(auto p = buf.rbegin();*p == '\r' || *p == '\n';++p,++flag);

            if(flag == 4)
                break;
        }
    }

void HttpOperation::ParseHead() {//解析响应头
        //得到文件大小
        int i = buf.find("Content-Length:",0);
        

        size = 0;
        for(int j = i+16;buf.at(j) >= '0' && buf.at(j) <= '9';++j)
            size = size*10 + buf.at(j) - '0';

            
        //得到文件类型
        i = buf.find("Content-Type:",0);
        i += 13;
        for(;buf.at(i) != '\r';++i) {
            type.push_back(buf.at(i));
            if(buf.at(i) == '/')
                type = "";
        
        }
        //解析完毕释放缓冲区
        buf = "";
    }

void HttpOperation::Close() {
    close(fd);
}

