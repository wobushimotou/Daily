/*
 *  01背包问题　动态规划
 *
 * */
#include <iostream>
#include <vector>
#include <string.h>
using namespace std;
class Packet{
public:
    vector<int> v;  //存储物品价值
    vector<int> w;  //存储物品重量
    int f[50];  
    int Max(int a,int b) {
        return a>b?a:b;
    }
    int GetMaxV(int,int);
};
int Packet::GetMaxV(int n,int c) {
    if(n < 0)
        return 0;
    if(f[n])
        return f[n];
    if(w[n] > c) {   //剩余重量小于物品重量
        f[n] = GetMaxV(n-1,c);
        return f[n];
    }
    else {
        f[n] = Max(GetMaxV(n-1,c),GetMaxV(n-1,c-w[n])+v[n]);
        return f[n];
    }
}

int main()
{
    Packet pk;
    bzero(pk.f,sizeof(pk.f));    
    pk.w = {2,2,6,5,4};
    pk.v = {6,3,5,4,6};
        
    cout << pk.GetMaxV(5,10) << endl;
    return 0;
}

