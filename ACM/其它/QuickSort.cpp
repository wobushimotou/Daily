/*
 *  快排
 * */
#include <iostream>
#include <vector>
#include <ctime>
#include <thread>
using namespace std;

void GetRandVec(vector<int> &vec,int size,int k) {
    unsigned int c = clock();
    vec.resize(size);
    for(int i = 0;i < size;++i) {
        vec[i] = rand_r(&c)%k;
    }
}

void swap(int &a,int &b) {
    int temp = a;
    a = b;
    b = temp;
}
void Sort(vector<int> &vec,int l,int r) {
    if(l >= r)
        return ;

    int temp = vec[l];
    int left = l;
    int right = r;

    while(left < right) {
        while(left < right && vec[right] > temp)
            right--;
        if(left < right) {
            vec[left] = vec[right];            
            left++;
        }

        while(left < right && vec[left] < temp)
            left++;
        if(left < right) {
            vec[right] = vec[left];
            right--;
        }
    }
    vec[left] = temp;
    
    /* cout << l << " " << left-1 << endl; */
    /* cout << left+1 << " " << r << endl; */

    Sort(vec,l,left-1);
    Sort(vec,left+1,r);
}

//多线程快排
void threadQuickSort(vector<int> &vec,int l,int r) {
    if(l >= r)
        return ;

    int temp = vec[l];
    int left = l;
    int right = r;

    while(left < right) {
        while(left < right && vec[right] > temp)
            right--;
        if(left < right) {
            vec[left] = vec[right];            
            left++;
        }

        while(left < right && vec[left] < temp)
            left++;
        if(left < right) {
            vec[right] = vec[left];
            right--;
        }
    }
    vec[left] = temp;
    
    thread tl(Sort,std::ref(vec),l,left-1);
    thread tr(Sort,std::ref(vec),left+1,r);
    
    tl.join();
    tr.join();
}

int main()
{
    vector<int> vec;
    GetRandVec(vec,100,1000);
    for(auto &e:vec) 
        cout << e << " ";

    cout << endl;
    threadQuickSort(std::ref(vec),0,vec.size());
    /* Sort(vec,0,vec.size()); */

    for(auto &e:vec) 
        cout << e << " ";

    return 0;
}

