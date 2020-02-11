#include "HttpOperation.h"

void HttpOperation::Parse() {   //解析URL链接
        //解析协议
        size_t ret = url.find("https",0);
        if(ret != string::npos)
            protocol = 1;
        else
            protocol = 0;

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

        if(port == "") {
            if(protocol == 0)
                port = "80";
            else
                port = "443";
        }

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


        auto n = url.find("/",start);
        for(;n < url.size() && url.at(n) != '?';++n)
            datapath.push_back(url.at(n));

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

        if(protocol == 1)
            ConnectSSL();
        return fd;
    }

int HttpOperation::ConnectSSL() {//建立SSL连接

    //初始化SSL算法库
    SSL_library_init();
    //申请会话环境
    ssl_ct = SSL_CTX_new(SSLv23_client_method());
    
    //创建SSL套接字
    ssl = SSL_new(ssl_ct);

    //绑定流套接字
    SSL_set_fd(ssl,fd);

    //发起握手
    int ret = SSL_connect(ssl);
    
    return ret;
}

void HttpOperation::SendHttpHead(long start,long end) {//发送http请求头
        
        //设置http请求头
        head = "GET "+url+" HTTP/1.1\r\n"+
            "Host: "+host+"\r\n"+
            "Connection: Close\r\n"+
            "Accept: */*\r\n"+
            "Range: bytes="+to_string(start)+"-"+((end>0)?to_string(end):"")+"\r\n"+
            "\r\n";
        //发送
            

        if(protocol == 0)
            send(fd,head.c_str(),head.length(),0); 
        else
            SSL_write(ssl,head.c_str(),head.length());

    }

void HttpOperation::ReadHttpHead() {//读取http响应头
        unsigned char temp;
        while(true) {


            if(protocol == 0)
                read(fd,&temp,1);
            else
                SSL_read(ssl,&temp,1);

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
    if(protocol == 1)
        CloseSSL();
}

void HttpOperation::CloseSSL() {//关闭SSL连接
    //关闭SSL套接字
    SSL_shutdown(ssl);

    //释放SSL套接字
    SSL_free(ssl);

    //释放SSL会话环境
    SSL_CTX_free(ssl_ct);

}

int HttpOperation::HttpRead(char *buf,size_t len) {
    if(protocol == 0)
        return read(fd,buf,len);
    else
        return SSL_read(ssl,buf,len);

}

int HttpOperation::HttpWrite(char *buf,size_t len) {
    if(protocol == 0)
        return read(fd,buf,len);
    else
        return SSL_read(ssl,buf,len);
}
