#pragma once
#include <iostream>
#include <memory>
#include <thread>
#include <vector>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include "HttpOperation.h"
using namespace std;
class HttpDown
{
public:
    HttpDown(string _url):Hp(_url) {  } ;
    int DownLoad();
    string filename; //文件保存名
    string filepath; //保存的路径
    char *current;   //文件校验码
    long filesize;       //文件大小

    ~HttpDown();
private:
    long Position(); //计算文件起始位置
    void Print(int,int);   //显示下载进度
    HttpOperation Hp;
};
