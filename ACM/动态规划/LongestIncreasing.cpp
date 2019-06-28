/*
 *  求最长单调递增子序列    动态规划
 *
 *
 * */
#include <iostream>
#include <string>
#include <string.h>
using namespace std;
class LongestIncreasing{
public:
    string str;
    int Max(int a,int b) {
        return( a>b)?a:b;
    }
    int d[50];      //d[n]表示str[0:n]的最长单调递增子序列长度
    string GetLong();
};

string LongestIncreasing::GetLong() {
    //求出最长递增子序列长度
    d[0] = 1;
    for(size_t i = 1;i != str.size();++i) {
        d[i] = 1;
        for(size_t j = 0;j < i;++j) {
            if(str[j] < str[i]) {
                if(d[j]+1 > d[i])
                    d[i] = d[j]+1;
            }
            else 
                d[i] = d[j];
        }
    }

    int n = d[str.size()-1];
    string sum;
    for(size_t i = 0;i != str.size();++i) {
        for(size_t j = i;j != str.size();++j) {
            if(str[i] > sum[sum.size()-1]) 
                sum += str[i];
            if(sum.size() == n)
                return sum;
        }

    }
}

int main()
{
    LongestIncreasing li;
    li.str = "215364897";
    bzero(li.d,sizeof(li.d));
    cout << li.GetLong() << endl;
    
    return 0;
}

