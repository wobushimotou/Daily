#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

struct A{
    int a:12;
    int b:12;
};

int main()
{
    int i = 0;
    /* int i = 0; */

    /* int n = 0; */
    /* n = i++; */
    /* n = ++i; */


    char *p = (char *)malloc(1);

    int n = 0;
    scanf("%d",&n);

    *(p+n) = 'a';
    *(p+n/2) = 'b';
    *(p+n/3) = 'c';

    printf("%c\n",*(p+n));
    printf("%c\n",*(p+n/2));
    printf("%c\n",*(p+n/3));

    sleep(20);
    return 0;
}

