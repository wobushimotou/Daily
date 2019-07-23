/*
 *  找出1到n中n个数的最大公倍数
 *
 *
 * */
#include <iostream>
#include <vector>
using namespace std;
int main()
{
    vector<int> ar;
    int n;
    cin >> n;
    long m = 1;

    for(int i = 1;i <= n;++i) {
        ar.push_back(i);
    }
   
    for(size_t i = 0;i < ar.size();++i) {
        m *= ar[i];
    }
    for(size_t i = 0;i < ar.size();++i) {
        ar[i] = m/ar[i];
    }

    bool flag = true;
    long Min = 99999999;
    while(flag) {
        //找到最小非零项
        flag = false;
        for(auto e:ar)
            if(Min > e && e > 0) {
                Min = e;
                flag = true;
            }
        for(int &e:ar)
            if(e != Min) 
                e = e%Min;
    }
    cout << "最小公倍数为:" << m/Min << endl;

    return 0;
}

