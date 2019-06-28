/*
 *  最小m段和问题　动态规划
 *
 *
 *
 * */
#include <iostream>
#include <vector>
#include <string.h>
using namespace std;


class Minsum{
public:
    vector<int> vec;
    int GetMax(int m,int n);
    int Max(int a,int b) {
        return a>b?a:b;
    }
    int d[50][50];
    Minsum() {
        bzero(d,sizeof(d));
    }
};
int Minsum::GetMax(int n,int m) {
    for(int i = 1;i <= n;++i)
        d[i][1] = d[i-1][1]+vec[i]; 

    for(int i = 1;i <= n;++i) {
        for(int j = 2;j <= m;++j) {
            int minvalue = 9999;
            for(int k = 1;k < i;++k) {
                int temp = Max(d[k][j-1],d[i][1]-d[k][1]);
                if(temp < minvalue)
                    minvalue = temp;
            }
            d[i][j] = minvalue;
        }
    }
    return d[n][m];
}

int main()
{
    Minsum ms;
    ms.vec = {0,9,8,7,6,5,4,3,2,1};
    cout << ms.GetMax(9,3) << endl;
    return 0;
}

