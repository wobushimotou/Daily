#include <iostream>
#include <netdb.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <fstream>
#include <pthread.h>
#include <vector>
#include <sys/stat.h>
#include <cstdio>
#include <iomanip>
#include <thread>

using namespace std;

long file_size;

class HTTPDOWN{
public:
    string url;     //下载链接
    string downfile; //保存文件名
    string port;       //端口号
    string host;    //远程主机地址
    string filename;    //下载的文件名
    string ip_addr; //主机ip地址
    string head;    //http头
    int fd;         //套接字
    string buf;     //缓冲区
    int size;       //下载的文件大小
    string type;    //下载文件的类型

    HTTPDOWN(string _url) : url(_url) {  }
    void Parse() {   //解析URL链接
        //解析域名
        string::size_type i = 0;
        string::size_type start;
        for(i = 0;i < url.length();++i) {
            if(url.at(i) == '/' && url.at(i+1) == '/') 
                break;
        }
        start = i+2;
        for(int j = start;url.at(j) != '/';++j)
            host.push_back(url.at(j));

        //解析端口号
        for(i = start;i < url.length();++i)
            if(url.at(i) == ':') {
                i++;
                while(url.at(i) < '0' || url.at(i) > '9')
                    port.push_back(url.at(i++));         

            }
        if(port == "")
            port = "80";
        else {
            //删除域名里面的端口号
            int temp = host.find_first_of(':',0);
            host = host.substr(0,temp);
        } 

        //解析文件名
        auto p = url.begin();
        auto q = p;
        for(;p != url.end();++p) 
            if(*p == '/')
                q = p;

        filename = {q+1,url.end()};

    }
    void GetIpAddr() {//通过域名得到对应的ip地址
        struct hostent *h = gethostbyname(host.c_str());
        char ip[16];
        for(int i = 0;h->h_addr_list[i];i++) {
            strcpy(ip,inet_ntoa(*(struct in_addr*)h->h_addr_list[i]));
            break;
        }
        ip_addr = ip;
    }
    int Connect() {//建立连接
        fd = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);

        if(fd < 0) {
            cout << "套接字创建失败" << endl;
            return 0;
        }

        struct sockaddr_in addr;
        memset(&addr,0,sizeof(addr));
        addr.sin_family = AF_INET;
        addr.sin_addr.s_addr = inet_addr(ip_addr.c_str());
        addr.sin_port = htons(atoi(port.c_str()));


        int res = connect(fd,(struct sockaddr *)&addr,sizeof(addr));
        if(res == -1) {
            cout << "连接失败" << endl;
            return 0;
        }
        return 1;
    }

    void SendHttpHead(long start,long end) {//发送http请求头
        
    //设置http请求头
        head = "GET "+url+" HTTP/1.1\r\n"+
            "Accept: */*\r\n"+
            "Host: "+host+"\r\n"+
            "Connection: keep-alive\r\n"+
            "Range: bytes="+to_string(start)+"-"+((end>0)?to_string(end):"")+"\r\n"+
            "\r\n";
            //发送
        send(fd,head.c_str(),head.length(),0); 
    }

    void ReadHttpHead() {//读取http响应头
        unsigned char temp;
        while(true) {
            read(fd,&temp,1);
            buf.push_back(temp);
            int flag = 0;
            for(auto p = buf.rbegin();*p == '\r' || *p == '\n';++p,++flag);

            if(flag == 4)
                break;
        }
    }

    void ParseHead() {//解析响应头
        //得到文件大小
        int i = buf.find("Content-Length:",0);
        

        size = 0;
        for(int j = i+16;buf.at(j) > '0' && buf.at(j) < '9';++j)
            size = size*10 + buf.at(j) - '0';

            
        //得到文件类型
        i = buf.find("Content-Type:",0);
        i += 13;
        for(;buf.at(i) != '\r';++i) {
            type.push_back(buf.at(i));
            if(buf.at(i) == '/')
                type = "";
        
        }
        //解析完毕释放缓冲区
        buf = "";
    }
    //合并每个线程单独写的文件
    void Merge(int num) {
        fstream file;
        file.open(downfile,ios::out);
        if(!file.is_open()) {
            cout << "合并文件打开失败" << endl;
            return;
        }
        for(int i = 0;i < num+1;++i) {
            fstream f;
            f.open(downfile+"_"+to_string(i),ios::in);
            if(!f.is_open())
                break;
            char temp;
            int j = 0;

            while(f.read(&temp,1)) {
                file << temp;
                j++;
                if(j == (size/num))
                    break;
            }
            string path = downfile+"_"+to_string(i);
            if(remove(path.c_str()) == -1) {
                cout << "删除失败" << endl;
            }
        }
        

    }
    
    void Close() {//关闭连接
        close(fd); 
    }
    
    long Is_Exist() {  //检测文件是否存在并返回大小
        fstream file(downfile);
        if(!file.is_open()) {
            return 0;
        }

        long length = 0;
        char temp;
        while(file.read(&temp,1))
            ++length;
        file.close();
        return length;

    }
    long Contrast(long end) {   //对比已存在文件内容与下载下来的是否相同并返回最后相同字节位置
        Connect();
        SendHttpHead(0,end);
        ReadHttpHead();
       
        //打开文件
        fstream file(downfile);
        char c_file,c_http;
        for(int i = 0;i < end;++i) {
            file.read(&c_file,1);
            read(fd,&c_http,1);
            if(c_file != c_http)
                return i;
        }

        Close();
        file.close();

        return size;
        
    }
};
struct info{
    long start; 
    long end;
    string downfile;    //保存文件名
    int fd;             //此线程所用套接字
    info(long s1,long s2,string name,int res) : start(s1),end(s2),downfile(name),fd(res) {  }
};
vector<struct info> inf;

void *Write_Thread(void *num)
{
    int start = (inf.begin() + *(int *)num)->start;
    int end = (inf.begin() + *(int *)num)->end;

   // if(*(int *)num == 1)
   //     pthread_exit(NULL);

    long i = end-start;
    long j = 0;
    
    fstream file;
    
    file.open((inf.begin() + *(int *)num)->downfile+"_"+to_string(*(int *)num),ios::out);
    if(!file.is_open()) {
        cout << "下载文件打开失败" << endl;
    }
   // file.open((inf.begin() + *(int *)num)->downfile,ios::out);
   // file.seekg(start,ios::beg);

    unsigned char temp;
    while(true) {
        read((inf.begin() + *(int *)num)->fd,&temp,1);
        
        file << temp;
        j++;
        file_size++;
        if(j == i) {
            break;
        }
    }
    file.close();
    pthread_exit(NULL);
}

void *Schedule(void *name)
{
    double num;
    cout << (char *)name << endl;
    while(true) {

        struct stat info;
        if((stat((char *)name,&info)) == -1)
            continue;
        num = (double)info.st_size/(double)file_size;
        cout << setprecision(3) << num*100 << "%";
        //printf("%.2f%%",num);
        fflush(stdout);
        if(num*100 < 10)
            cout << "\b\b\b\b";
        else
            cout << "\b\b\b\b\b";
    }
}



int main()
{
    
    //输入下载地址
    string _url("http://img.ljia.net/upload2016/2016-03/22931/2016032316433620132.jpg");
    int t_num = 10;
    
    //第一次发送http请求头得到文件大小以及文件类型数据
    HTTPDOWN http(_url);
    http.Parse();
    http.GetIpAddr();
    http.Connect();
    http.SendHttpHead(0,-1);
    http.ReadHttpHead();
    http.ParseHead();   //解析响应头,得到文件大小,类型等信息
    http.Close();   //关闭连接
    
    //询问是否要下载此文件
    cout << "文件:"+http.filename << endl;    
    cout << "来自:"+http.host << endl;
    cout << "大小:"+((http.size > 1024)?(to_string(http.size/1024)+"K"):(to_string(http.size))) << endl;
    cout << "类型:"+http.type << endl;

    http.downfile = http.filename;    
    
    file_size = 0;
    
    //检测文件是否存在
    long end;
    if((end = http.Is_Exist()) > 0) {
        //获取文件内容的下载起点
        end = http.Contrast(end);
    }    
    

    //设置线程显示下载进度
    thread t(Schedule,(void *)http.filename.c_str());
    t.detach();

    //pthread_create(&tid,NULL,Schedule,(void *)(http.filename.c_str()));

    pthread_t tids[t_num];
    int ar[t_num+1];
    for(int i = 0;i < t_num+1;++i)
        ar[i] = i;

    int i,j;
    for(i = 0,j = 0;j < t_num;i += http.size/t_num,j++) {
        //重新建立与服务器的连接
        http.Connect();
        http.SendHttpHead(i,i + http.size/t_num);   //发送此线程所需下载文件的范围区间
        http.ReadHttpHead();

        //存储下载文件所需的一系列信息
        struct info temp(i,i + http.size/t_num,http.downfile,http.fd);
        inf.push_back(temp);
    
        pthread_create(&tids[j],NULL,Write_Thread,(void *)&ar[j]);
    }
    
    if(i < http.size) {
        http.Connect();
        http.SendHttpHead(i,http.size);   //发送此线程所需下载文件的范围区间
        http.ReadHttpHead();

        //存储下载文件所需的一系列信息
        struct info temp(i,http.size,http.downfile,http.fd);
        inf.push_back(temp);
    
        pthread_create(&tids[j],NULL,Write_Thread,(void *)&ar[j]);
    }
    
    
    while(true) {
        if(file_size == http.size)
            break;
    }
    
    /*
    while(true) {
        struct stat info;
        stat(http.downfile.c_str(),&info);
        if(info.st_size == http.size)
            break;
    }
    */
    //将所有线程单独下载的文件合并起来
    http.Merge(t_num);
    
    http.Close(); 
    
    
    return 0;
}

