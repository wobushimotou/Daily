/*
 *  n后问题 回溯法
 *
 *
 *
 * */

#include <iostream>
#include <vector>


std::vector<int> x;
int n;
int sum = 0;

bool IsPlace(int k) {
    for(int j = 1;j < k;++j)
        if((abs(k - j) == abs(x[j] - x[k])) || (x[j] == x[k]))
           return false;
    return true;
}

void NQueen(int k) {
    if(k > n)
        sum++;
    else
        for(int i = 1;i <= n;++i) {
            x[k] = i;
            if(IsPlace(k))
                NQueen(k+1);
        }
}
int main()
{   
    std::cin >> n;
    for(int i = 0;i <= n;++i)
        x.push_back(0);
    sum = 0;

    NQueen(1);
    //初始化x

    std::cout << sum << std::endl;
    return 0;
}

