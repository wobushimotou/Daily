#include "HttpDown.h"
#include "HttpOperation.h"
int main(int argc,char *argv[])
{
    HttpDown Hd(argv[1]);
    Hd.DownLoad();
    return 0;
}

