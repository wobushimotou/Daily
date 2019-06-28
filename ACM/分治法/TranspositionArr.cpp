#include <iostream>
#include <vector>
/*
 *  将数组ar中[0:k-1]的元素与[k:n-1]的元素位置互换
 *  要求时间复杂度为O(n),空间复杂度为O(1)
 * 
 * */
using namespace std;
void swap(vector<int> &a,int low1,int high1,int low2,int high2){  

    int temp;  
    while(low1<=high1){  
        temp=a[low1];  
        a[low1]=a[low2];  
        a[low2]=temp;  
        low1++;  
        low2++;  
    }  
}  
void TranspositionArr(vector<int> &a,size_t low,size_t k,size_t high) {
        if(low<high){  
            if((k-low+1)==(high-k))  
                swap(a,low,k,k+1,high);  
            else if((k-low+1)<(high-k)){  
                swap(a,low,k,low+high-k,high);  
                TranspositionArr(a,low,k,low+high-k-1);  
            }  
            else{  
                swap(a,low,high+low-k-1,k+1,high);  
                TranspositionArr(a,high+low-k,k,high);  
            }  
        }  

}  
int main()
{
    vector<int> vec;
    for(int i = 1;i < 10;++i)
        vec.push_back(i);
    TranspositionArr(vec,0,3,vec.size());

    for(auto e:vec)
        cout << e << " ";
    return 0;
}

