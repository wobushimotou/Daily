#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <time.h>

int main(void)
{
    pid_t pid;
    int fd[2], i;
    pipe(fd);
    for (i = 0; i < 2; i++) {
        if((pid = fork()) == 0) {
            break;
        }
    }
    if (i == 0) { //兄
        close(fd[0]);
        char buf[100];
        time_t timep;
        struct tm *p;
        time (&timep);
        p=gmtime(&timep);
        sprintf(buf,"%d-%d-%d %d:%d:%d",1900+p->tm_year,1+p->tm_mon,p->tm_mday,8+p->tm_hour,p->tm_min,p->tm_sec);

        write(fd[1],buf,strlen(buf)+1);

    } else if (i == 1) { //弟
        close(fd[1]);
        char buf[100];
        
        int i = 0;
        while(1) {
            char ch;
            read(fd[0],&ch,1);
            buf[i++] = ch;
            if(ch == '\0') {
                break;
            }
        }
        printf("%s\n",buf);
 
    } else {
        close(fd[0]);
        close(fd[1]);
        for(i = 0; i < 2; i++) //两个儿子wait两次
            wait(NULL);
    }


    return 0;

}

