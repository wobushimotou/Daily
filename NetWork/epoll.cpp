#include <iostream>
#include <unistd.h>
#include <sys/epoll.h>
int main()
{
    int epfd = epoll_create(10);

    struct epoll_event event;
    event.data.fd = 1;
    event.events = EPOLLET | EPOLLOUT;

    epoll_ctl(epfd,EPOLL_CTL_ADD,1,&event);

    struct epoll_event ev[2];
    while(1) {
        int n = epoll_wait(epfd,ev,2,-1);
        if(n > 0) {
            for(int i = 0;i < n;++i) {
                if(ev[i].events & EPOLLOUT) {
                    write(1,"writeable\n",10);
                }
            }
        }
    }
    return 0;
}

