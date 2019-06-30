/*
 *  子集和问题 回溯法
 *
 *
 * */
#include <iostream>
#include <vector>
#include <string.h>
using namespace std;
class SubsetSum{
public:
    SubsetSum() {
        found = 0;
        k = 0;
        bzero(x,sizeof(x));
        bzero(bestx,sizeof(bestx));
    }
    vector<int> w;
    int sum;
    int x[50];  //当前路径
    int bestx[50];//解路径
    int k;      //当前值
    void GetBest(size_t n);
    int found;
};
void SubsetSum::GetBest(size_t n) {
    if(found)
        return;
    if(k == sum) {
        found = 1;
        for(size_t i = 0;i != w.size();++i)
            bestx[i] = x[i];
    }
    if(n == w.size()) { 
        return;
    }
    else {
        if(k + w[n] <= sum) {
            k += w[n];
            x[n] = 1;
            GetBest(n+1);
            k -= w[n];
            x[n] = 0;
        }
        x[n] = 0;
        GetBest(n+1);
    }
    
}
int main()
{
    SubsetSum ss;
    ss.w = {2,2,6,5,4};
    ss.sum = 10;
    ss.GetBest(0);
    for(size_t i = 0;i != ss.w.size();++i) {
        if(ss.bestx[i])
            cout << ss.w.at(i) << " ";
    }
        
    return 0;
}

