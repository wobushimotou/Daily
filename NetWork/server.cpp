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
    if(argc == 1) {
        fd = socket(AF_INET,SOCK_STREAM,0);
        if(fd < 0) {
            cout << "套接字申请失败" << endl;
            exit(0);
        }

        struct sockaddr_in serv;
        memset(&serv,0,sizeof(serv));
        serv.sin_family = AF_INET;
        serv.sin_port = htons(9527);
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


        int sockfd;
        char buf[1001];
        while((sockfd = accept(fd,NULL,NULL)) > 0) {
            cout << "主线程" << endl;
            /* thread t(handle,sockfd); */
            /* t.detach(); */
            /* g_lock.lock(); */
            /* g_lock.unlock(); */
         getsockopt(fd,IPPROTO_TCP,TCP_MAXSEG,(void *)&size,&len);
         cout << "listen后mss大小="<< size << endl;

         size = 0;
         getsockopt(fd,SOL_SOCKET,SO_RCVBUF,(void *)&size,&len);
         cout << "连接后接收缓冲区大小=" << size << endl;
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



