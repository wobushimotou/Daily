/*
 *  最大k乘积问题 动态规划
 *
 * */
#include <iostream>
#include <vector>
#include <math.h>
#include <string.h>
#include <sstream>
#include <string>
using namespace std;
class MaxProduct{
public:
    long I;  //数字
    int d[50][50];  //d[i][j]代表前i位数字分隔成j段的最大乘积
    
    MaxProduct() {
        bzero(d,sizeof(d));
    }
    int GetNum(int k,int m,int n) {//得到I的[m:n]范围内的后k位数字
        string num;
        stringstream os;
        os << I;
        os >> num;
        int value = 0;
        m--,n--;
        for(int i = n+1-k;i <= n;++i)
            value = value*10 + num[i]-'0';

        return value;
    }
    int GetMax(int,int);
};
int MaxProduct::GetMax(int n,int m) {
    for(int i = 1;i <= n;++i) {
        d[i][1] = (int)(I/pow(10,n-i));
    }

    for(int i = 2;i <= n;++i) {
        for(int j = 2;j <= m;++j) {
            int maxvalue = 0;
            for(int k = 1;k < i;++k) {
                int temp = d[k][j-1]*GetNum(i-k,1,i);
                //找到最大值
                if(temp > maxvalue)
                    maxvalue = temp;
            }
            //将最大值保存起来
            d[i][j] = maxvalue;
        }
    }
    return d[n][m];
}
int main()
{
    MaxProduct mp;
    mp.I = 12345;
    cout << mp.GetMax(5,2) << endl;
    return 0;
}

