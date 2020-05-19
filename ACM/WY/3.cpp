#include <iostream>
using namespace std;

int main()
{
    int n;
    cin >> n;

    for(int i = 0;i != n;++i) {
        int N,M;
        cin >> N >> M;
        int ar[N][M];
        for(int n = 0;n != N;++n)
            for(int m = 0;m != M;++m)
                cin >> ar[n][m];

        int t;
        t = min(N,M)/3*3;
        
        int a,b,c,d;
        a = 0;
        b = 0;
        c = a+t-1;
        d = b+t-1;

        while(true) {
            if(Is(a,b,c,d,ar)) {
                break;
            }

            if(c != N) {
                a++;
                c = a+t-1;
            }
            if(d != M) {
                b++;
                d = b+t-1;
            }
            
            if(c == N-1 && d == M-1) {
                t--;
                t = t/3*3;
            }
            
        }
    }
    return 0;
}

