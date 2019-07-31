/*
 *  大整数乘法
 *
 *
 * */
#include <iostream>
#include <string>

using namespace std;
int main()
{
    string multiplier;
    string multiplicand;
    cin >> multiplier >> multiplicand;

    unsigned int a[200] = {0};
    unsigned int b[200] = {0};
    int a_length = 0;
    int b_length = 0;

    for(size_t i = 0;i != multiplier.size();++i,++a_length)
        a[multiplier.size()-1-i] = multiplier[i] - '0';

    for(size_t i = 0;i != multiplicand.size();++i,++b_length)
        b[multiplicand.size()-1-i] = multiplicand[i] - '0';

    unsigned int sum[400] = {0};
    for(int i = 0;i < a_length;++i) {
        for(int j = 0;j < b_length;++j) {
            int num = a[i]*b[j];
            sum[i+j] += num;
        } 
    }

    size_t i = 0;
    for(i = 0;sum[i];++i) {
        if(sum[i] > 10) {
            sum[i+1] += sum[i]/10;
            sum[i] %= 10;
        }
    }
    
    for(int n = i-1;n >= 0;--n) {
        printf("%d",sum[n]);
    }
    return 0;
}

