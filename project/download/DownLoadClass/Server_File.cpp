#include <iostream>
#include <sys/socket.h>
#include <sys/un.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
#include <thread>
#include <fstream>
#include "Thread_Recv_Send.h"

using namespace std;
int main()
{
    int fd = socket(AF_INET,SOCK_STREAM,0);
    if(fd < 0) {
        cout << "套接字申请失败" << endl;
        exit(0);
    }

    struct sockaddr_in serv;
    memset(&serv,0,sizeof(serv));
    serv.sin_family = AF_INET;
    serv.sin_port = htons(5678);
    serv.sin_addr.s_addr = htonl(INADDR_ANY);

    int num = 1;
    int length = sizeof(num);
    setsockopt(fd,SOL_SOCKET,SO_REUSEADDR,&num,length);

    if(bind(fd,(struct sockaddr *)&serv,sizeof(serv)) < 0) {
        cout << "绑定失败 " << endl;
        exit(0);
    }

    if(listen(fd,5) < 0) {
        cout << "创建监听套接字失败" << endl;
        exit(0);
    }

    int sockfd;
    char ch;
    while((sockfd = accept(fd,NULL,NULL)) > 0) {
        read(sockfd,&ch,1);
        std::cout << ch << std::endl;
    }


    close(sockfd);
    close(fd);


    return 0;
}

