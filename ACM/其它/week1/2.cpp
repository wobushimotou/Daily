/*
 *  抽纸牌游戏，a,b轮流抽一堆纸牌中的一张，两人都采取最优策略，a先抽,求a抽到的数字之和减b抽到的数字之和
 *
 *
 * */
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
int main()
{
    vector<int> vec;
    int num;
    while(cin >> num)
        vec.push_back(num);
    sort(vec.begin(),vec.end());
    int a = 0;
    int b = 0;
    for(int i = vec.size()-1;i >= 0;--i) {
        if(i%2 == 0)
            a += vec.at(i);
        else
            b += vec.at(i);
    }
    cout << a - b << endl;
    return 0;
}

