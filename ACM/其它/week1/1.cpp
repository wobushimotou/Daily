/*
 *  分巧克力问题
 *  M个巧克力分n天吃，要求每一天吃的数量不少于前一天吃的一半，并且每天都有巧克力吃，求第一天可以吃的最大值
 *
 * */
#include <iostream>
#include <math.h>
using namespace std;
int n,m;

int getsum(int a){//第一天是a 
	int sum = 0;
	for(int i=0;i<n;i++){
		sum += a;
		a = (a+1)/2;//向上取整 
	} 
	return sum;
}

//使用二分查找寻找结果
int BinarySearch(void) {
	int low = 1,high = m,mid;//因为第一天的在1-m之间，所以采用二分查找，时间复杂度到O(logn) 
	while(low <= high) {
		mid = (low+high)/2;
		if(getsum(mid) == m) {
			return mid;
		}	
		else if(getsum(mid) > m)
			high = mid - 1;
		else
			low = mid + 1;
	}
	return high;	
} 

//使用逐行递加的方法查找
int AddSearch(void) {
    //存储每天所吃的巧克力的个数
    int ar[n];
    for(int i = 0;i < n;++i)
        ar[i] = 1;
    int carry = n-1;  //标识进位
    int lave = m-n;           //剩余的巧克力数量
    while(lave > 0) {
        ar[carry]++;    //进位上的巧克力加一
        lave--;         //剩余巧克力数量减一

        //寻找下一个进位
        int i;
        for(i = n-1;i > 0;--i) {
            if(ar[i] < 2*ar[i-1]) {
                carry = i;
                break;
            }
        }
        if(i == 0)
            carry = 0;
            
    }
    return ar[n-1];
}
int main() {
    while(true) {
    cin >> m >> n;
    cout << AddSearch() << endl;
    cout << BinarySearch() << endl;
    }
}




