/*
 *  最优分解问题 贪心
 *
 *
 *
 * */
#include <iostream>
#include <string.h>
using namespace std;
class OptimalDecomposition{
public:
    OptimalDecomposition() {
        bzero(ar,sizeof(ar));
    }
    int I;
    int ar[50]; //存储每一步分解的数
    int GetMax();
};
int OptimalDecomposition::GetMax() {
    int k = 0;
    
    for(int i = 2;I > 0;++i) {
        if(I > i) {
            ar[k++] = i;
            I -= i;
        }
        else
            break;
    }
    for(int i = 0;i < I;++i)
        ar[--k]++;

    int sum = 1;
    for(int i = 0;ar[i];++i)
        sum *= ar[i];
    return sum;
}

int main()
{
    OptimalDecomposition od;
    od.I = 11;
    cout << od.GetMax() << endl;
    return 0;
}

