#include <iostream>
#include <list>
#include <vector>

using namespace std;
void f(vector<int> &ar,int left,int right,size_t k) {
    if(k < 1)
        return;
    if(k == ar.size()/2) {  //两边数组大小相等,直接交换
        for(size_t i = left;i < k;++i)
            swap(ar[i],ar[k]);
    }
    else if(k < ar.size()/2) {
        for(size_t i = 0;i < k;++i)
            swap(ar[i],ar[k+i]);
        f(ar,k,right,k*2);
    }
    else {
        for(size_t i = 0;i < ar.size()-k;++i)
            swap(ar[i],ar[k+i-1]);
        f(ar,ar.size()-k,right,k);

    }
}
int main()
{
    vector<int> vec;
    for(int i = 0;i < 10;++i) {
        vec.push_back(i);
    }
    f(vec,1,vec.size(),3);
    for(auto e:vec)
        cout << e << " ";
   
}

