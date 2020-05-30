#include <iostream>
#include <vector>
#include <map>
#include <math.h>
using namespace std;
int main()
{
    int N,M;
    cin >> N >> M;

    int x = 0,y = 0;
    int ar[N][M];
    for(int i = 0;i != N;++i)
        for(int j = 0;j != M;++j) {
            cin >> ar[i][j];
            if(ar[i][j] == 1)
                x++;
        }

    
    for(int i = 0;i != N;++i)
        for(int j = 0;j != M;++j) {
            if(ar[i][j] == 1) {
                if(i+1 != N && ar[i+1][j] == 1)
                    y++;
                if(j+1 != M && ar[i][j+1] == 1)
                    y++;
            }
        }

    long q = pow(2,x) - y*pow(2,x-2) + pow(y-1,2);

    cout << q%100000000 << endl;
    return 0;
}

