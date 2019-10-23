#include <stdio.h>
int fun(int *x,int *y) {
    *x = 10;
    *y = 20;
    return *x;
}

int main()
{
    return 0;
}

