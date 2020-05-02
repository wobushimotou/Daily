#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdlib.h>
#include <time.h>
#include <strings.h>
int main()
{
    unsigned int a = clock();
    double num = (double)rand_r(&a)/rand();

    while(num > 1)
        num -= 1;

    num -= 0.5;
    printf("%lf\n",num);
    return 0;
}

