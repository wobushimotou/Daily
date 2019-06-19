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

int fd;
mutex g_lock;
void handle(int sockfd)
{
    int size;
    char ch;
    while((size = recv(sockfd,&ch,1,0)) > 0) {
        send(sockfd,&ch,1,0);
    }
    close(sockfd);
}
void manage(int sig);

int main(int argc,char *argv[])
{
    
    if(argc == 1) {
        fd = socket(AF_INET,SOCK_STREAM,0);
        if(fd < 0) {
            cout << "套接字申请失败" << endl;
            exit(0);
        }
        signal(SIGTSTP,manage);

        struct sockaddr_in serv;
        memset(&serv,0,sizeof(serv));
        serv.sin_family = AF_INET;
        serv.sin_port = htons(5678);
        serv.sin_addr.s_addr = htonl(INADDR_ANY);

        int num = 1;
        int length = sizeof(num);
	    setsockopt(fd,SOL_SOCKET,SO_REUSEADDR,&num,length);

        int size;
        socklen_t len;

        getsockopt(fd,IPPROTO_TCP,TCP_MAXSEG,(void *)&size,&len);
        cout << "listen前mss大小=" << size << endl;
        size = 0;

        getsockopt(fd,SOL_SOCKET,SO_RCVBUF,(void *)&size,&len);
        cout << "listen前接收缓冲区大小=" << size << endl;
        
        if(bind(fd,(struct sockaddr *)&serv,sizeof(serv)) < 0) {
            cout << "绑定失败 " << endl;
            exit(0);
        }

        if(listen(fd,5) < 0) {
            cout << "创建监听套接字失败" << endl;
            exit(0);
        }

        getsockopt(fd,IPPROTO_TCP,TCP_MAXSEG,(void *)&size,&len);
        cout << "listen后mss大小="<< size << endl;

        size = 0;
        getsockopt(fd,SOL_SOCKET,SO_RCVBUF,(void *)&size,&len);
        cout << "listen后接收缓冲区大小=" << size << endl;


        int sockfd;
        while((sockfd = accept(fd,NULL,NULL)) > 0) {
            cout << "主线程" << endl;
            thread t(handle,sockfd);
            t.detach();
            g_lock.lock();
            g_lock.unlock();
        }
    }
    else {
        cout << "线程2开始执行" << endl;        
        int sockfd;
        
        cout << fd << endl;
        g_lock.lock();
        while((sockfd = accept(fd,NULL,NULL)) > 0) {
            cout << "线程2" << endl;
            thread t(handle,sockfd);
            t.detach();

        }
        g_lock.unlock();
    }
    return 0;

}
void manage(int sig)
{
    char **ar;
    thread t(main,2,ar);
    t.detach();
}



