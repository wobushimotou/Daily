#include <iostream>
#include "Thread_Recv_Send.h"
void Thread_Send(long lhs,long rhs,const Thread_Recv_Send &t) {
    printf("l=%ld,r=%ld\n",lhs,rhs);
    //初始化发送结构体
    AttriBute ab(lhs,rhs);
    strcpy(ab.pathname,t.filename.c_str());

    //打开文件,读取响应内容
    std::fstream f(t.filename);
    if(!f.is_open()) {
        std::cout << "打开文件失败" << std::endl;
    }
    
    //文件流移动到要读取的内容处
    f.seekg(lhs,std::ios::beg);

    //读取文件对应范围内容并发送
    for(long i = lhs,j = 0;i != rhs;i++,++j) {
        f.read(&ab.buf[j],1);
    }
    ab.size = t.size;
    //关闭文件流
    f.close();
    //发送结构体        
    write(t.fd,&ab,sizeof(ab));
}

void Thread_Recv(const AttriBute ab) {
    //打开文件,写入响应内容
    std::fstream f(ab.pathname);
    if(!f.is_open()) {
        std::cout << "打开文件失败" << std::endl;
    }

    //文件流移动到要写入的地方
    f.seekp(ab.l_range,std::ios::beg);
    //写入文件对应范围内容
    for(long i = ab.l_range,j = 0;i != ab.r_range;++i,++j) {
        f.write(&ab.buf[j],1);
    }
    //关闭文件流
    f.close();
}

int Thread_Recv_Send::Send_File(const std::string &pathname)
{
    std::cout << "开始发送文件" << std::endl;
    this->filename = pathname;
    //获取文件大小
    struct stat info;
    stat(filename.c_str(),&info);
    size = info.st_size;

    for(long i = 0;i <= size;i += 1000) {
        if(size - i < 1000)
            std::thread t(Thread_Send,i,size,*this);
        else
            std::thread t(Thread_Send,i,i+1000,*this);
    }
    //返回文件发送的大小
    return size;
}
int Thread_Recv_Send::Recv_File(void) {
    std::cout << "开始接收文件" << std::endl;
    //初始化接收结构体
    
    AttriBute ab;
    int len;
    while(true) {
        len = 0;
        if((len += read(fd,&ab,sizeof(ab))) == sizeof(ab)) {
            printf("l_range=%ld r_range=%ld\n",ab.l_range,ab.r_range);
        }
        std::thread t(Thread_Recv,ab);
        t.detach();
    }
    return 1;
}

