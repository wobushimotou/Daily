/*
 *  合并排序 分治法
 *
 *
 * */
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
class MergeSort{
public:
    vector<int> ar;
    void Sort(int left,int right);  //排序ar[left:right]
    void Merge(int left,int middle,int right);//合并ar[left:middle] 与 ar[niddle+1:right];

};
void MergeSort::Sort(int left,int right) {
    if(left < right) {
        int middle = (right + left)/2;
        Sort(left,middle);
        Sort(middle+1,right);
        Merge(left,middle,right);
    }
}
void MergeSort::Merge(int left,int middle,int right) {//合并ar[left:middle] 与 ar[niddle+1:right];
    int i = left,j = middle+1;
    vector<int> b;
    while(i <= middle && j <= right) {
        if(ar[i] <= ar[j])
            b.push_back(ar[i++]);
        else
            b.push_back(ar[j++]);
    }
    if(i > middle) {
        for(int m = j;m <= right;++m)
            b.push_back(ar[m]);
    }
    else {
        for(int n = i;n <= middle;++n)
            b.push_back(ar[n]);
    }
    //将b拷贝回a
    copy(b.begin(),b.end(),ar.begin()+left);
}
int main()
{
    MergeSort ms;
    ms.ar = {2,1,3,7,5,4,6};
    ms.Sort(0,6);
    for(auto p = ms.ar.begin();p != ms.ar.end();++p)
        cout << *p << " ";

    return 0;
}

