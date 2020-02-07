#include <stdio.h>

int i;
int main()
{
    i--;
    if(i > sizeof(i))
        printf(">\n");
    else
        printf("<\n");
    return 0;
}

