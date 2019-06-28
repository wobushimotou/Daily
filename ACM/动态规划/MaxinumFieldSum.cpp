/*
 *  最大字段和　动态规划
 *
 *
 * */

#include <iostream>
#include <vector>
#include <string.h>
using namespace std;
class MaxinumFieldSum{
public:
    vector<int> vec;    //存储序列
    int Max(int a,int b) {
        return (a>b)?a:b;
    }
    int ar[50];         //ar[n]为子序[0:n]的最大字段和
    int GetMax(int n);
};
int MaxinumFieldSum::GetMax(int n) {
    int Sum = 0;  
    int M = 0;
    for(size_t i = 0;i != vec.size();++i) {
        Sum = (Sum + vec[i] > vec[i])?(Sum + vec[i]):vec[i];
        if(Sum > M)
            M = Sum;
    }
    return M;
}

int main()
{
    MaxinumFieldSum mf;
    int num;
    bzero(mf.ar,sizeof(mf.ar));

    for(int i = 0;i < 8;++i) {
        cin >> num;
        mf.vec.push_back(num);
    }
    
    cout << mf.GetMax(mf.vec.size()-1) << endl;
    return 0;
}

