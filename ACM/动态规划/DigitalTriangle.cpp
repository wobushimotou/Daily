/*
 *  数字三角形问题 动态规划
 *
 * */
#include <iostream>
#include <string.h>
using namespace std;
class DigitalTriangle{
public:
    int ar[50][50]; //存储数字三角形的数组
    DigitalTriangle() {
        bzero(ar,sizeof(ar));
        bzero(edit,sizeof(edit));
    }
    int edit[50][50];//edit[m][n]标识第m行第n列的从顶至下最大和
    int Max(int a,int b) {
        return a>b?a:b;
    }
    int GetMax(int m,int n);
    int Get();
};
int DigitalTriangle::GetMax(int m,int n) {
    if(m < 0 || n < 0)
        return 0;
    if(m == 0 && n == 0) {
        edit[m][n] = ar[m][n];
        return edit[m][n];
    }
    edit[m][n] = ar[m][n] + Max(GetMax(m-1,n-1),GetMax(m-1,n));
    return edit[m][n];
}
int DigitalTriangle::Get() {
    int M = -1;
    int num;
    for(int i = 0;i < 5;++i) {
        num = GetMax(4,i);
        if(num > M)
            M = num;
    }
    return M;
}
int main()
{
    DigitalTriangle dt;
    for(int i = 0;i < 5;++i)
        for(int j = 0;j <= i;++j)
            cin >> dt.ar[i][j];
    cout << dt.Get() << endl;
    return 0;
}

