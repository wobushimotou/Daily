#include <iostream>
using namespace std;
int main()
{
    long size;
    cin >> size;
    long nums[size];
    for(long i = 0;i < size;++i)
        cin >> nums[i];

    long left,right;
    long Max = 0;

    left = 0;
    right = 0;

    for(long n = 0;n < size;++n) {
        for(long i = 1;i < size;++i) {
            if(i == n)
                continue;
            if(nums[i] > nums[i-1]) {
                right++;
                if(right-left > Max)
                    Max = right-left;
            }
            else {
                left = i;
                right = i;
            }
        }
        left = 0;
        right = 0;
    }

    cout << Max+1 << endl;
    return 0;
}

