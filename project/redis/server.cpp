#include <hiredis/hiredis.h>
#include <iostream>
#include <istream>
#include <string>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <string.h>
#include <thread>
 
using namespace std;
int Send(int fd,const char *str,int size)
{
    int l = 0;
    if((l += send(fd,&size,sizeof(size),0)) > 0)
        send(fd,str,size,0);
    return l;

}
void handle(int fd)
{    
    redisContext* c = redisConnect("127.0.0.1", 6379);
    if(c->err)
    {
        redisFree(c);
        cout << "Connect to redisServer fail" << endl;
        return;
    }

    string command;
    redisReply *r;
    
    int size = 0;
    int l = 0;
    char *buf;

    while((l = recv(fd,&size,sizeof(size),0)) == sizeof(size)) { //接收字符串大小
        
        cout << "size=" << size << endl;

        buf = new char[size+1];
        recv(fd,buf,size,0);    //接收命令字符串
        buf[size] = '\0';

        r = (redisReply*)redisCommand(c, buf);
        cout << r->type << endl;

        if(r->type == REDIS_REPLY_ERROR)    //发生错误
            Send(fd,r->str,strlen(r->str));

        if(r->type == REDIS_REPLY_STRING)   //返回值为字符串
            Send(fd,r->str,strlen(r->str));
        else if(r->type == REDIS_REPLY_NIL) {    //返回结果为空
            command = "(nil)";
            Send(fd,command.c_str(),command.length());

        }
        else if(r->type == REDIS_REPLY_STATUS) {    //返回命令的执行状态
            Send(fd,r->str,strlen(r->str));

        }
        else if(r->type == REDIS_REPLY_INTEGER) {//返回值为整数 
            command = "(integer) "+to_string(r->integer);
            Send(fd,command.c_str(),command.length());
        }

        else if(r->type == REDIS_REPLY_ARRAY) {//返回值为数组
            for(size_t i = 0;i < r->elements;++i) {
                command += to_string(i+1)+") "+(r->element)[i]->str+"\n";
            }
            Send(fd,command.c_str(),command.length());
        }
        l = 0;
        delete(buf);
        command = "";
    }

}

int main()
{
   int fd;
    fd = socket(AF_INET,SOCK_STREAM,0);
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
    while((sockfd = accept(fd,NULL,NULL)) > 0) {
        thread t(handle,sockfd);
        t.detach();
    }

     return 0;
}

