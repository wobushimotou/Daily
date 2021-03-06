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
#include <fcntl.h>
#include <mutex>
#include <netinet/tcp.h>

using namespace std;

int to_num(string s) {
    int sum = 0;
    for(int i = 0;i < s.size();++i) {
        sum = sum*10+s[i]-'0';
    }
    return sum;
}


void handle_request(string s,int sockfd) {

    while(s.size() > 0) {
        int start = s.find_first_of("0123456789",0);
        int end = s.find_first_of(",",0);
        
        int num = to_num(s.substr(start,end-start));

        fstream file("1.txt");
        string buf;
        int i = 0;

        while(getline(file,buf)) {
            if(i++ == num)
                break;
        }

        cout << buf << endl;
        write(sockfd,buf.c_str(),buf.size()+1);

        int len = s.size();
        s = s.substr(end+1,len);
    }

}
int main(int argc,char *argv[])
{
    int fd;
    fd = socket(AF_INET,SOCK_STREAM,0);

    struct sockaddr_in serv;
    memset(&serv,0,sizeof(serv));
    serv.sin_family = AF_INET;
    serv.sin_port = htons(9527);
    serv.sin_addr.s_addr = htonl(INADDR_ANY);

  

    if(bind(fd,(struct sockaddr *)&serv,sizeof(serv)) < 0) {
        cout << "绑定失败 " << endl;
        exit(0);
    }

    if(listen(fd,5) < 0) {
        cout << "创建监听套接字失败" << endl;
        exit(0);
    }


    int sockfd;
    sockfd = accept(fd,NULL,NULL);
    int x;
    x=fcntl(sockfd,F_GETFL,0);
    fcntl(sockfd,F_SETFL,x | O_NONBLOCK);    

    if(sockfd != -1) {
        char ch;
        int ret;
        string request;
        while((ret = read(sockfd,&ch,1))) {
            if(ret < 0) {
                if(errno == EINTR || errno == EWOULDBLOCK || errno == EAGAIN)
                    continue;
                else
                    break;
            }            
            else if(ret > 0){
                request += ch;
                if(ch == '\n') {
                    handle_request(request,sockfd);
                    request = "";
                }
            }
            else {
                break;
            }
        }
        close(sockfd);
    } 

}

