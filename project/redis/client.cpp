#include <iostream>
#include <string>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netinet/tcp.h>

using namespace std;
int Recv(int fd,string &s)
{
    int l = 0;
    int size = 0;
    char *str = NULL;
    if((l += recv(fd,&size,sizeof(size),0)) > 0) {
        str = new char[size];
        recv(fd,str,size,0);
    }
    s = str;
    delete(str);
    return l;
}
int main()
{   
    int fd = socket(AF_INET,SOCK_STREAM,0);
    if(fd < 0) {
        cout << "套接字创建失败" << endl;
        exit(0);
    }

    struct sockaddr_in servaddr;
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    servaddr.sin_port = htons(5678);

    if(connect(fd,(const struct sockaddr *)&servaddr,sizeof(servaddr)) < 0) {
        cout << "连接失败" << endl;
        exit(0);
    }
    
    //连接成功
    cout << "127.0.0.1:6379> ";
    string command;
    int size;
    string s;
    while(getline(cin,command)) {
        size = command.size();
        //发送命令
        if((send(fd,&size,sizeof(size),0)) > 0)
            send(fd,command.c_str(),size,0);
        
        //接收信息
        if(Recv(fd,s) > 0)
            cout << s << endl;
        command = "";
        cout << "127.0.0.1:6379> ";
    }


 
    return 0;
}

