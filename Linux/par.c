#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <unistd.h>
#include <dirent.h>
#include <signal.h>
#include <time.h>
#include <string.h>
int main()
{
          char buf[100];
          bzero(buf,100);
        time_t timep;
        struct tm *p;
        time (&timep);
        p=gmtime(&timep);
        sprintf(buf,"%d-%d-%d %d:%d:%d",1900+p->tm_year,1+p->tm_mon,p->tm_mday,8+p->tm_hour,p->tm_min,p->tm_sec);

        write(1,buf,strlen(buf)+1);


    return 0;
}

