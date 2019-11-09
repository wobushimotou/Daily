#include <stdio.h>

int main()
{
    char *str = "hello";
    str[4] = '\0';
    printf("%s\n",str);
    return 0;
}

