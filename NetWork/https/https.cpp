#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <openssl/ssl.h>
#include <openssl/bio.h>
 
using namespace std;
int main()
{
    int sockfd;
    SSL_CTX *ssl_ct;
    SSL *ssl;

    string ip;
    int port = 443;
    sockfd = socket(AF_INET,SOCK_STREAM,0); 

    sockaddr_in addr;
    
    addr.sin_addr.s_addr = inet_addr("118.31.180.41");
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);

    //建立TCP连接
    if(connect(sockfd,(sockaddr *)&addr,sizeof(addr)) < 0) {
        cout << "连接失败" << endl;
    }

    SSL_library_init();
    //申请会话环境
    ssl_ct = SSL_CTX_new(SSLv23_client_method());
    
    //创建SSL套接字
    ssl = SSL_new(ssl_ct);

    //绑定流套接字
    SSL_set_fd(ssl,sockfd);

    //发起握手
    SSL_connect(ssl);

// http 请求头信息
    char https_header[] =
        "GET https://www.cnblogs.com/bwar/p/9879893.html HTTP/1.1\r\n"
        "Host: www.cnblogs.com\r\n"
        "User-Agent: curl/7.16.3 libcurl/7.16.3 OpenSSL/0.9.7l zlib/1.2.3\r\n"
        "Connection: keep-alive\r\n"
        "Accept: */*\r\n"
        "Range: bytes=0-1024\r\n"
        "\r\n";

    cout << https_header << endl;
    char https_res[40240] = {0};
    int ret = SSL_write(ssl,https_header,sizeof(https_header));

    int len = 0;
    while(true) {
        int n = SSL_read(ssl,https_res+len,1);
        if(n < 1)
            break;
        len++;
    }
    
    cout << https_res << endl;
    //关闭SSL套接字
    SSL_shutdown(ssl);

    //释放SSL套接字
    SSL_free(ssl);

    //释放SSL会话环境
    SSL_CTX_free(ssl_ct);
    return 0;
}

