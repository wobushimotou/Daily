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

