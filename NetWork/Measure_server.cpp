#include <iostream>
#include <vector>
#include <sys/socket.h>
#include <sys/un.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <wait.h>
#include <thread>
#include <csignal>
#include <fstream>
#include <mutex>
#include <netinet/tcp.h>

using namespace std;


int main(int argc,char *argv[])
{
    int fd;
    fd = socket(AF_INET,SOCK_STREAM,0);

    struct sockaddr_in serv;
    memset(&serv,0,sizeof(serv));
    serv.sin_family = AF_INET;
    serv.sin_port = htons(9527);
    serv.sin_addr.s_addr = htonl(INADDR_ANY);

    int num = 1;
    int length = sizeof(num);

    setsockopt(fd,SOL_SOCKET,SO_REUSEADDR,&num,length);

    int size = 0;
    socklen_t len;

    getsockopt(fd,IPPROTO_TCP,TCP_MAXSEG,(void *)&size,&len);
    cout << "listen前mss大小=" << size << endl;
    size = 0;

    size = 0;
    setsockopt(fd,IPPROTO_TCP,SO_RCVBUF,(void *)&size,len);



    if(bind(fd,(struct sockaddr *)&serv,sizeof(serv)) < 0) {
        cout << "绑定失败 " << endl;
        exit(0);
    }

    if(listen(fd,5) < 0) {
        cout << "创建监听套接字失败" << endl;
        exit(0);
    }


    int sockfd;
    char buf[1001];
    while((sockfd = accept(fd,NULL,NULL)) > 0) {
        cout << "主线程" << endl;
        size = 0;
        cout << "将接收缓冲区设置为0" << endl;
        size = 0;
        setsockopt(sockfd,IPPROTO_TCP,SO_RCVBUF,(void *)&size,len);

        getsockopt(sockfd,SOL_SOCKET,SO_RCVBUF,(void *)&size,&len);
        cout << "接收缓冲区大小=" << size << endl;


        sleep(1);
    }

}
