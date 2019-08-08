/*
 *  给出矩阵ａ
 *  定义x[i][j]为矩阵ａ中第i行第j列除a[i][j]之外的剩余元素的乘积
 *  求最大的乘积
 *
 * */
#include <iostream>
#include <vector>
using namespace std;
int main()
{
    int m,n;
    cin >> m >> n;
    int vec[m][n];
    int vec1[m][n];
    int vec2[m][n];
    
    for(int i = 0;i < m;++i)
        for(int j = 0;j < n;++j) {
            cin >> vec[i][j];
            vec2[i][j] = vec[i][j];
            vec1[i][j] = vec[i][j];
        }

    int temp1,temp2;
    //计算所有行乘积
    for(int i = 0;i < m;++i) {
        temp1 = 1;
        for(int j = 0;j < n;++j) {
            vec[i][j] = temp1;
            temp1 *= vec2[i][j];
        }
        temp2 = 1;
        for(int j = n-1;j >= 0;--j) {
            vec[i][j] *= temp2;
            temp2 *= vec2[i][j];
        }
    }
    
    //计算所有列乘积
    for(int i = 0;i < n;++i) {
        int temp = 1;
        for(int j = 0;j < m;++j) {
            vec1[j][i] = temp;
            temp *= vec2[j][i];
        }
        temp = 1;
        for(int j = m-1;j >= 0;--j) {
            vec1[j][i] *= temp;
            temp *= vec2[j][i];
        }
    }

    int Max = 0;
    for(int i = 0;i < m;++i) {
        for(int j = 0;j < n;++j) {
            vec[i][j] *= vec1[i][j];
            if(vec[i][j] > Max)
                Max = vec[i][j];
        }
    }
    cout << Max << endl;
 
        return 0;
}

