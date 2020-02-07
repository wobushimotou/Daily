#include <stdio.h>

int main()
{
    int n;
    unsigned int mask;
    mask = 1u << 31; 
    scanf("%d",&n);
    while(mask) {
        printf("%d",(n & mask)?1:0);
        mask >>= 1;
    }
    return 0;
}

