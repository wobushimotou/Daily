#include <iostream>
#include <vector>
/*
 *　二分搜索的一系列算法
 *  假定数组已排好序
 * 
 * */

using namespace std;

//标准的二分搜索
template<typename T>
size_t BinarySearch(vector<T> &vec,T value) {
    int left = 0,right = vec.size()-1;
    while(left < right) {
        int middle = left + (right - left + 1)/2;
        if(vec.at(middle) == value)
            return middle;
        else if(vec.at(middle) < value)
            left = middle+1;
        else
            right = middle-1;
    }
    return -1;
}

//当value不在数组时,返回小于value的最大元素和大于value的最小元素位置
template<typename T>
pair<size_t,size_t> BinarySearch_2(vector<T> &vec,T value) {
    int left = 0,right = vec.size()-1;
    while(left <= right) {
        int middle = left + (right -left + 1)/2;
        if(vec.at(middle) == value)
            return {middle,middle};

        if(vec.at(middle) < value)
            left = middle+1;
        else
            right = middle-1;
        if(left+1 == right && vec.at(left) != value  && vec.at(right) != value)
            return {left,right};
    }
}



int main()
{
    vector<int> vec;
    for(int i = 1;i < 8;++i)
        if(i != 2)
            vec.push_back(i);
    cout << BinarySearch_2(vec,2).first << endl;
    return 0;
}

