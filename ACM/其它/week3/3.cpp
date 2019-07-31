/*
 *  分巧克力问题
 *  m个人分n块巧克力
 *  h[i]为第i个人想得到的巧克力重量
 *  w[j]为第j块巧克力的重量
 *  求最多多少人可以满足愿望
 * */
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
int main()
{
    vector<int> w;
    vector<int> h;
    int num;
    int w_l;
    int h_l;

    cin >> h_l;
    for(int i = 0;i < h_l;++i) {
        cin >> num;
        h.push_back(num);
    }
    cin >> w_l;
    for(int i = 0;i < w_l;++i) {
        cin >> num;
        w.push_back(num);
    }
 
    sort(h.begin(),h.end(),[](int a,int b){ return a>b; });
    
    int n = 0;
    for(int i = 0;i != w_l;++i) {
        //在h中找到第一个小于等于w[i]的数
        for(int j = 0;j != h.size();++j) {
            if(h[j] <= w[i]) {
                ++n;
                h.erase(h.begin()+j);
                break;
            }
        } 
    }

    cout << "n = " << n << endl;
    return 0;
}

