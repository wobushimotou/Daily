#include <iostream>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <thread>

using namespace std;
void f(int fd) {
    usleep(10000);
    shutdown(fd,2);
}
void f2(int fd) {
    usleep(10000);
    shutdown(fd,1);
}
int main()
{
    while(true) {
        int fd = socket(AF_INET,SOCK_STREAM,0);
        if(fd == -1)
            break;
        cout << fd << endl;
        thread t(f,fd);
        t.detach();
        thread t2(f2,fd);
        t2.detach();

    }
    return 0;
}

