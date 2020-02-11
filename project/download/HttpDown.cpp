#include "HttpDown.h"

long HttpDown::Position() {
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
    //下载的字节数
    int size = end-start;

    Ho.Connect();
    Ho.SendHttpHead(start,end);
    Ho.ReadHttpHead();

    char buf[size];     //缓冲区
    long s = 0;
    while(s < size) {
        s += Ho.HttpRead(buf+s,size-s);
    }

    Ho.Close();
    fstream out(Hd->filename);

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
    //获取文件大小，类型等数据
    Hp.Parse();    
    Hp.GetIpAddr();
    Hp.Connect();
    Hp.SendHttpHead(0,-1);
    Hp.ReadHttpHead();
    Hp.ParseHead();    
    Hp.Close();

    //显示文件信息
    cout << "文件:"+Hp.filename << endl;    
    cout << "来自:"+Hp.host << endl;
    cout << "大小:"+((Hp.size > 1024)?(to_string(Hp.size/1024)+"K"):(to_string(Hp.size))) << endl;
    cout << "类型:"+Hp.type << endl;
    cout << "路径:" << "." << endl;

    if(Hp.filename == "")
        Hp.filename = "1."+Hp.type;
    filesize = Hp.size;

    filename = Hp.filename;
    filepath = ".";
    int Content = 10240;

        
    long Part = filesize/Content+(((filesize-(filesize/Content)*Content)>0)?1:0);

    //网页不支持分段下载
    if(Hp.type == "html")
        Part = 1;


    current = new char[Part];
    bzero(current,Part);

    //获取文件信息
    Position();


    //开始多线程下载文件
    //每个线程下载Content字节
    for(long i = 0;i < Part;++i) {
        if(*(current + i) == 1)
            continue;
        thread t(ThreadDownLoad,i*Content,(i+1)*Content,Hp,this);        
        t.detach();
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
      printf("[");

    for(int i = 0;i < Current;++i)
        putchar('#');

    for(int i = 0;i < Final-Current;++i)
        putchar('-');

    printf("]");
    fflush(stdout);
    sleep(1);
    for(int i = 0;i < Final+2;++i)
        putchar('\b');
}

HttpDown::~HttpDown() {
    delete current;
}
