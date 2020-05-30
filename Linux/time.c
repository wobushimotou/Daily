#include <stdio.h>
#include <time.h>
#include <signal.h>
#include <unistd.h>

void handle(int signum) {
    time_t t;
    time(&t);
    char buf[1042];
    ctime_r(&t,buf);
    for(int i = 0;i != 3;++i)
        printf("%s\n",buf);
    return;

}
int main()
{
    signal(SIGALRM,handle);

    pause();
    return 0;
}

