#include "HttpDown.h"

HttpDown::HttpDown(string _url,string _name,string _path):
    filename(_name),
    filepath(_path),
    Hp(_url)
{

}

HttpDown::HttpDown(string _url):
    HttpDown(_url,"1","./") {
}

long HttpDown::Position(int k) {
    //获取文件大小
    struct stat info;
    stat(filename.c_str(),&info);
    long size = info.st_size;

    fstream in(filename,ios::in);
    if(!in.is_open() || size < filesize) {
        //创建文件
        in.open(filename,ios::out); 
        in.close();
        return 0;
    }
    
    //判断文件是否存在且已下载完
    if(size == filesize) {
        for(int i = 0;i < k;++i)
            *(current + i) = 1;
        return 0;
    }
    char ch;
    //检查文件末尾校验和
    in.seekg(filesize+1,ios::beg); 
    
    int Written = 0;
    while(in.read(&ch,1)) {
        *(current + Written) = ch;
        Written++;
    }
    
    in.close();
    return Written;
}


void ThreadDownLoad(long start,long end,HttpOperation Ho,HttpDown *Hd) {
    long EndSize = 0;
    if(end > Hd->filesize) {
        EndSize = end-start;
        end = Hd->filesize;
    }
    //需下载的字节数
    long size = end-start;
    

    Ho.Connect();
    Ho.SendHttpHead(start,end);
    Ho.ReadHttpHead();


    char buf[size];     //缓冲区
    long s = 0;
    
    while(s < size) {
        s += Ho.HttpRead(buf+s,size-s);
    }
    
    Ho.Close();

    fstream out(Hd->filepath+Hd->filename);
    //将缓冲区数据写入文件
    out.seekp(start,ios::beg);
    out.write(buf,size);

    //计算校验码写入位置
    long Check = 0;
    
    if(EndSize > 0)
        size = EndSize;

    Check = (Hd->filesize)+(start+1)/size+1;
    //写入校验码
    char ch = 1;
    out.seekp(Check,ios::beg);
    out.write(&ch,1);

    //更新已下载大小

    *(Hd->current+(start+1)/size) = 1;
 
    out.close();
}

int HttpDown::DownLoad() {

    printf("开始下载\n");
    //获取资源信息
    if(GetAttribute() < 0) {
        //重定向URL
        GetAttribute();
    }

    //显示文件信息
    cout << "文件:"+Hp.filename << endl;    
    cout << "来自:"+Hp.host << endl;
    cout << "大小:"+((Hp.size > 1024)?(to_string(Hp.size/1024)+"K"):(to_string(Hp.size))) << endl;
    cout << "类型:"+Hp.type << endl;


    cout << "保存路径:" << filepath+filename+"."+Hp.type << endl;

    filename += "."+Hp.type; 
    if(Hp.filename.size() > 0)
        filename = Hp.filename;

    /* filename += "."+Hp.type; */

    /* Hp.filename = filename; */
    
    /* filename = filepath + filename; */

    

    filesize = Hp.size;
    int Content = 1024000;
        
    long Part = ((filesize + Content -1 )/Content);
       
    current = new char[Part];
    bzero(current,Part);

    //获取文件信息
    Position(Part);
    
    if(Part > 100) {
        //根据文件大小初始化线程池
        threadpool = make_shared<mythreadpool>(500);
    }


    //开始多线程下载文件
    //每个线程下载Content字节
    for(long i = 0;i < Part;++i) {
        if(*(current + i) == 1)
            continue;

        if(Part > 100) {
            threadpool->Append(ThreadDownLoad,i*Content,(i+1)*Content,Hp,this);
        }
        else {
            thread t(ThreadDownLoad,i*Content,(i+1)*Content,Hp,this);        
            t.detach();
        }
    }

    while(true) {
        int f = 0;
        int s = 1;
        for(int i = 0;i < Part;++i) {
            if(*(current+i) == 0) {
                s = 0;
                f++;
            }
        }
        Print(Part-f,Part);
        if(s)
            break;
    }

    //下载完毕去除文件校验码
    truncate(Hp.filename.c_str(),filesize);    

    return 1;
}

void HttpDown::Print(int Current,int Final) {

    //转化为百分比
    Current = 100*((double)Current/Final);
    Final = 100;

    printf("[");

    for(int i = 0;i < Current;++i)
        printf("#");

    for(int i = 0;i < Final-Current;++i)
        printf("-");

    printf("]");
    fflush(stdout);
    sleep(1);
    for(int i = 0;i < Final+2;++i)
        printf("\b");
}

int HttpDown::GetAttribute() {
    //获取文件大小，类型等数据
    Hp.Parse();    
    Hp.GetIpAddr();
    Hp.Connect();
    Hp.SendHttpHead(0,-1);
    Hp.ReadHttpHead();
    Hp.Close();

    return Hp.ParseHead();
}

HttpDown::~HttpDown() {
    delete current;
}
