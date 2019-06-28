/*
 *  大整数乘积 分治法
 *
 *
 * */
#include <iostream>
#include <string>
#include <math.h>
using namespace std;

int BigNumberMult(long X,long Y,int n) {
    if(X == 0 || Y == 0)
        return 0;
    if(n == 1)
        return X*Y;
    int A = (int) X / pow(10, (int)(n / 2));
    int B = X - A * pow(10, n / 2);
    int C = (int) Y / pow(10, (int)(n / 2));
    int D = Y - C * pow(10, n / 2);
    int AC = BigNumberMult(A, C, n / 2);
    int BD = BigNumberMult(B, D, n / 2);
    int ABDC = BigNumberMult((A - B), (D - C), n / 2) + AC + BD;
    return (AC * pow(10 , n) + ABDC * pow(10, (int)(n / 2)) + BD);  
}
int main()
{
    cout << BigNumberMult(1234,5678,4) << endl;
    return 0;
}

