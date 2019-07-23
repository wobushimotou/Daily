/*
 *  重新排列数列A，求A中的所有相邻元素乘积都为4的倍数,输出A是否可以
 *
 *
 * */
#include <iostream>
#include <vector>

using namespace std;
int main()
{
    vector<int> a;
    int n;
    int flag = false;
    while(cin >> n) {
        a.push_back(n);
    }
    //求出A中的2的倍数的元素的个数,4的倍数的元素个数
    int Count4 = 0;
    int Count2 = 0;
    for(auto e:a) {
        if(e%4 == 0) {
            Count4++;
            continue;
        }
        if(e%2 == 0)
            Count2++;
    }
    //求出剩余数字
    int Count = a.size() - Count2 - Count4;

    if(Count2 > 0) {
        if(Count4 >= Count)
            flag = true;
    }
    else {
        if(Count4 >= Count - 1)
            flag = true;
    }
    if(flag)
        cout << "yes" << endl;
    else
        cout << "no" << endl;
    return 0;
}

