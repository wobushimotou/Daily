#include "Buffer.h"

Buffer::Buffer():data(new char[DEFAULTSIZE]),ndata(new char[DEFAULTSIZE]),readable(0),writeable(DEFAULTSIZE){

}

Buffer::~Buffer() {
    if(readable+writeable > 0)
        delete[] data;
    delete[] ndata;
}

void Buffer::handleRead() {
    unsigned int nread;
    while(true) {
        if((nread = read(fd,ndata,size)) < 0) {
            if(errno == EWOULDBLOCK || errno == EAGAIN) {
                continue;
            }
            else if(errno == EINTR) {
                break;
            }
            else {
                std::cout << "读取失败" << std::endl;
                exit(0);
            }

        }
        else if(nread == 0) {//连接关闭
            break;   
        }
        else {
            if(nread > writeable) {
                extendSpace();
            }
            //将数据移动到data中
            memcpy(data+readable,ndata,nread);
            readable += nread;
            writeable -= nread;
        }

    }
}

//将缓冲区数据写入fd对应的文件对应的位置中
size_t Buffer::WriteFile(int fd,int seek) {
    lseek(fd,SEEK_SET,seek);
    unsigned int nwrite;
    nwrite = write(fd,data,readable);
    return nwrite;
}

void Buffer::extendSpace() {
    char *odata = data;
    data = new char[size*EXTENDRATIO];
    //旧数据移动到新空间
    memcpy(data,odata,readable);
    delete[] odata;
    
    char *ondata = ndata;
    ndata = new char[size*EXTENDRATIO];
    delete[] ondata;

    writeable += size;
    size *= 2;
}

