#include "HttpDown.h"
#include <ctime>
#include <time.h>
int main(int argc,char *argv[])
{
    clock_t start = clock();

    /*
    //获取参数
    string Path;
    string Name;
    for(int i = 1;i < argc;++i) {
        if(!strcmp(argv[i],"-o"))
            Name = argv[i+1];
        if(!strcmp(argv[i],"-p"))
            Path = argv[i+1];
    }

    shared_ptr<HttpDown> Hd;
    if(Path.size() && Name.size())
        Hd = make_shared<HttpDown>(argv[1],Name,Path);
    else
        Hd = make_shared<HttpDown>(argv[1]);

    Hd->DownLoad();
*/
    HttpDown Hd("http://releases.ubuntu.com/18.04.4/ubuntu-18.04.4-desktop-amd64.iso?_ga=2.250982342.1328127375.1582905067-392630687.1582905067");
    Hd.DownLoad();

    clock_t end = clock();
    
    cout << endl << "所用时间为:"<< (double)(end - start)/CLOCKS_PER_SEC*100 << "秒" << endl;
    return 0;
}

