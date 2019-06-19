#ifndef PROJECT_DOWNLOAD_
#define PROJECT DOWNLOAD_
#include <iostream>
#include <fstream>
#include <string>
#include <utility>
#include <unistd.h>
#include <netdb.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <sys/types.h>
#include <vector>
#include <sys/stat.h>
#include <cstdio>
#include <iomanip>
#include <thread>


using namespace std;
//下载任务类
class Download {
public:
    Download(const string &_url) : url(_url) {  }
    Download(const string &_url,const string &_path) : url(_url),Path(_path) {  }
    Download(const string &_url,const string &_path,const string &_name) : url(_url),Path(_path),name(_name) {  }
    ~Download() = default;
private:
    //通过url解析出需下载的文件大小和类型
    void GetAttribute();
    //多线程下载文件内容
    void WriteThread();
    //合并每个线程单独写的文件
    void Mergefile(int num);

    string url;         //下载链接
    string Path = ".";    //文件保存路径
    string name;    //文件保存名
    long size;      //文件大小
    string type;    //文件类型;
};

//http操作类
class HTTP {
public:
    HTTP(const string &_url) : url(_url) { 
        Parse(); 
        Connect();
    }
    //发送http请求头
    void SendHttpHead(long start,long end);
     //读取http响应头
    void ReadHttpHead();
    //解析http响应头
    pair<int,string> ParseHead();
    
    //析构函数
    ~HTTP() {
        close(fd);
    }
private:
    //解析url链接
    void Parse();
    //与远程服务器建立连接
    int Connect();

    string url; //下载链接
    string port = "80";   //服务器端口号
    string host;//远程主机地址
    string ip_addr;//主机ip地址
    string buf; //接收缓冲区
    int fd;     //套接字

};


#endif //PROJECT_DOWNLOAD
