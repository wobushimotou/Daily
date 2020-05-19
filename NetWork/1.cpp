/*
 *客户端
 *
 * */
#include <iostream>
#include <vector>
#include <fstream>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netinet/tcp.h>
#include "chat.h"

using namespace std;

int main()
{
    int fd = socket(AF_INET,SOCK_STREAM,0);
    if(fd < 0) {
        exit(0);
    }

    struct sockaddr_in servaddr;
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = inet_addr("192.168.1.109");
    servaddr.sin_port = htons(9527);

    int size = 0;
    if(connect(fd,(const struct sockaddr *)&servaddr,sizeof(servaddr)) < 0) {
    }   

    vector<string> vec;
    while(true) {
        string request;
        cin >> request;
        write(fd,request.c_str(),request.size());
        write(fd,"\n",1);

        string sentence;
        while(true) {
            char ch;
            read(fd,&ch,1);
            sentence += ch;

            int flag = 0;
            if(ch == '\n') {
                for(auto p = vec.begin();p != vec.end();++p) {
                    if(*p == sentence)
                        flag = 1;
                }

                if(!flag) {
                    fstream file("2.txt",ios::app);
                    file << sentence;
                    vec.push_back(sentence);
                }
                sentence = "";
                break;
            }
        }
    }
    return 0;
}

/*
 *服务端
 *
 *
 * */
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

