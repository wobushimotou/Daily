#include <iostream>
#include <vector>
using namespace std;

int main()
{
    int size;
    cin >> size;

    long ar1[size];
    long ar2[size];
    long Max1[3];
    long Max2[3];

    for(int i = 0;i < size;++i)
        cin >> ar1[i];

    for(int i = 0;i < size;++i)
        cin >> ar2[i];


    long max = 0;
    for(int i = 0;i < 3;++i) {
        for(int j = 0;j < size;++j) {
            if(max < ar1[j])
                max = j;
        }
        Max1[i] = ar1[max];
        ar1[max] = 0;
        max = 0;
    }

    for(int i = 0;i < 3;++i) {
        for(int j = 0;j < size;++j) {
            if(max < ar2[j])
                max = j;
        }
        Max2[i] = ar2[max];
        ar2[max] = 0;
        max = 0;
    }

    long sum1 = 0;
    long sum2 = 0;
    for(int i = 0;i < 3;++i) {
        sum1 += Max1[i];
        sum2 += Max2[i];
    }

    if(sum1 > sum2)
        cout << sum1;
    else
        cout << sum2;

    return 0;
}

