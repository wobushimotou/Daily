/*
 *  寻找无序大数组中的距离中位数最近的一千个数
 *  给定数组范围为0~k
 *
 * */
#include <iostream>
#include <vector>
#include <stdlib.h>
#include <strings.h>
using namespace std;

void getRandVec(vector<int> &vec,int size,int k) {
    for(int i = 0;i < size;++i) {
        unsigned int num = clock();
        vec.push_back((rand_r(&num)%k));
    }
}
int main()
{
    int size = 20;
    int k = 100;
    vector<int> vec;
    getRandVec(vec,size,k);

    //桶排
    int ar[k];
    bzero(ar,k*sizeof(int));

    for(auto &e:vec) {
        ar[e]++;
    }

    int down = size/2 - 1;
    int up = size/2 + 1;

    cout << down << " " << up << endl;
    vector<int> result;
    int len = 0;
    for(int i = 0;i != k;++i) {
        if(ar[i] && (len >= down && len <= up)) {
            result.push_back(i);
        }
        if(ar[i]) {
            ar[i]--;
            i--;
            len++;
        }
    }

    cout << result.size() << endl;
    for(auto &e:result) {
        cout << e << " ";
    }
    return 0;
}

