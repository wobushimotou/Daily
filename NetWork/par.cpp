#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
using namespace std;
int main()
{
    pid_t pid;
    for(int i = 0;i < 2;++i) {
        pid = fork();
        if(pid == 0) {
            printf("执行子进程,i = %d\n",i);
        }
    }
    return 0;
}

