#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <string.h>
#include <wait.h>
int main()
{
    int fds[2];
    pipe(fds);
    int ret = fork();

    if(ret == 0) {
        close(fds[0]);
        const char *buf = "hello!";
        write(fds[1],buf,strlen(buf)+1);
    }
    else if(ret > 0) {
        close(fds[1]);
        char buf[100];
        
        int i = 0;
        while(1) {
            char ch;
            read(fds[0],&ch,1);
            buf[i++] = ch;
            if(ch == '\0') {
                break;
            }
        }
        printf("%s\n",buf);
        wait(NULL);
    }
    else {

    }

    return 0;
}

