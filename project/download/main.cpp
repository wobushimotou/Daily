#include "HttpDown.h"
#include "myhttp_down.h"
int main(int argc,char *argv[])
{
    HttpDown Hd(argv[1]);
    Hd.DownLoad();
    return 0;
}

