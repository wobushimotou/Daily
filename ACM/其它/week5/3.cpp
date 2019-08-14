/*
 *  给出两个整数m,n,化为二进制，求多少位不同
 *
 *
 * */
#include <iostream>
using namespace std;
int main()
{
    int m,n;
    cin >> m >> n;
    int result = m^n;
    int sum = 0;
    for(int i = 0;i < 32;++i) {
        int flag = 1 << i;
        sum += (result&flag)?(1):(0);
    }
    cout << sum << endl;
    return 0;
}

