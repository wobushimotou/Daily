#include <iostream>
using namespace std;
int consecutiveNumbersSum(int N) {
    if(N <= 2)
        return 1;
    int cnt = 0;
    int t = 0;
    for(int i = 1;i < N;++i) {
        t = (i*(i+1))/2;
        if(t < N) {
            if((N-t)%i == 0)
                cnt++;
        }
        else if(t == N) {
            cnt++;
            break;
        }
        else
            break;
    }
    return cnt;
}
int main()
{
    int n;
    cin >> n;
    cout << consecutiveNumbersSum(n) << endl;
    return 0;
}

