#include <iostream>
#include <fstream>
#include "mythreadpool.h"
#include "InitVec.cpp"

int ar[10];
void ArSum(vector<int> &vec,int l,int r,int n) {
    for(int i = l;i < r;++i) {
        ar[n] += vec[i];
    }
}

int main()
{
    vector<int> vec;
    int arSize = 100;
    GetRandVec(vec,arSize,0,100);
    mythreadpool tpool(10);
    for(int i = 0;i < arSize;++i) {
        tpool.Append(ArSum,vec,i*10,(i+1)*10,i);
    }

    int sum = 0;
    for(int i = 0;i < 10;++i) {
        sum += ar[i];
    }
    cout << sum << endl;

    
    return 0;
}

