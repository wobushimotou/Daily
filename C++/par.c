#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
struct A
{
    int b;
    int c;
};
int main()
{
    int fd = open("1.txt",O_CREAT | O_APPEND ,S_IRUSR|S_IWUSR);
    getchar();
    struct A data = {1,2};
    
    write(fd,&data,sizeof(data));
    close(fd);

    return 0;
}

