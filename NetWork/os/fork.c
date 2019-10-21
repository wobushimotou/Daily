#include <iostream>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
using namespace std;
//子进程个数最大值
#define MAX_CHILD_NUMBER 10
//子进程睡眠时间
#define SLEEP_INTERVAL 2
int proc_number = 0;
void do_something();
int main(int argc,char *argv[])
{
    int child_proc_member = MAX_CHILD_NUMBER;
    int i,ch;
    pid_t pid;
    pid_t pids[10] = {0};
    if(argc > 1) {
        child_proc_member = atoi(argv[1]);
        child_proc_member = (child_proc_member > 10)?10:child_proc_member;
    }

    for(i = 0;i < child_proc_member;++i) {
        //父进程把子进程的id保存到pid[i]
        if((pid = fork()) > 0) 
            pids[i] = getpid();
        else if(pid == 0) {
            proc_number = i;
            do_something();
            break; 
        }
    }

    //让用户选择杀死进程，数字表示杀死该进程,q退出
    while((ch = getchar()) != 'q') {
        if(isdigit(ch)) {
            //杀死该子进程
            kill(pids[ch-'0'],SIGTERM); 
        }
    }

    //杀死本组所有进程
    for(i = 0;i < child_proc_member;++i) {
        kill(pids[i],SIGTERM);
    }
    return 0;
}

void do_something() {
    while(true) {
        printf("this is process No.%d and its pid is %d\n",proc_number,getpid());
        //阻塞两秒
        sleep(SLEEP_INTERVAL);
    }
}
