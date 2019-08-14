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

    int8_t a = 127;
    printf("%d",a);
    return 0;
}

