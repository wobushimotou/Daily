/*
 *  一个无序数组，包含正数,负数,0从中找出三个数的乘积最大，要求时间复杂度O(n),空间复杂度O(1)
 *
 * */
#include <iostream>
#include <vector>
using namespace std;

int arMax[3];
int arMin[2];

// arMax[0] > arMax[1] > arMax[2]
void AddMax(int num) {
    for(int i = 0;i != 3;++i) {
        if(num > arMax[i]) {
            if(i == 2)
                arMax[i] = num;
            else  {
                int temp = arMax[i];
                arMax[i] = num;
                arMax[i+1] = temp;
            }
            break;
        }
    }
}
// arMin[0] < arMin[1]
void AddMin(int num) {
    for(int i = 0;i != 2;++i)
        if(num < arMin[i]) {
            arMin[i] = num;
            break;
        }
}
int main()
{
    for(int i = 0;i != 3;++i)
        arMax[i] = -9999;
    for(int i = 0;i != 2;++i)
        arMin[i] = 9999;

    vector<int> ar;
    int num;
    while(cin >> num) {
        ar.push_back(num);
    }

    for(size_t i = 0;i != ar.size();++i) {
        AddMax(ar[i]);
        AddMin(ar[i]);
    }

    long long sum = 1;
    sum *= arMax[0];
    if(arMax[1]*arMax[2] > arMin[0]*arMin[1])
        sum *= arMax[1]*arMax[2];
    else
        sum *= arMin[0]*arMin[1];

    std::cout << "sum = " << sum << std::endl;
    
    return 0;
}

