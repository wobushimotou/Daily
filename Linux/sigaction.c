#include <stdio.h>
#include <signal.h>
#include <unistd.h>

void handle(int sig)
{
    if(sig==SIGINT||sig==SIGRTMIN)
        printf("receive a sig=%d\n",sig);//接收到三个SIGRTMIN,只接收到一个SIGINT
    else if(sig==SIGUSR1)
    {
        sigset_t s;
        sigemptyset(&s);
        sigaddset(&s,SIGINT);
        sigaddset(&s,SIGRTMIN);
        sigprocmask(SIG_UNBLOCK,&s,NULL);
    }

}
int main()
{
    struct sigaction act;
    act.sa_handler = handle;
    sigemptyset(&act.sa_mask);
    act.sa_flags = 0;

        sigset_t s;
    sigaddset(&s,SIGINT);
    sigaddset(&s,SIGRTMIN);
    sigprocmask(SIG_BLOCK,&s,NULL);//针对进程对信号阻塞。
    
    sigaction(SIGINT,&act,NULL);
    sigaction(SIGRTMIN,&act,NULL);
    sigaction(SIGUSR1,&act,NULL);
    for(;;)
        pause();
    return 0;
}

