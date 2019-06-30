#include <iostream>

int main()
{
    int wine = 456;
    int mouse[10];
    for(int i = 1,j = 0;j < 10;i *= 2,++j) {
        mouse[j] = i;
    }
    
    int n = 0;
    for(int i = 9;i >= 0;--i) {
        if((wine & mouse[i]) == mouse[i])
            n = n|(wine & mouse[i]);
    }

    std::cout << n << std::endl;
    
    return 0;
}
