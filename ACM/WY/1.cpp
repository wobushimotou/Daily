#include <iostream>
using namespace std;

int Length(int ns,int t,int (*ar)[101][2]) {
    int s,e,w;
    int i = 0;
    s = ar[ns][i][0];
    e = ar[ns][i+1][0];
    w = ar[ns][i][1];

    int ts,te;
    ts = 0;
    te = t;
    int sum = 0;

    while(s != -1 && e != -1) {
        if(e <= te) {
            sum += (e-s)*w;
            ts = e;
            if(ts == te)
                return sum;
        }
        else {
            sum += (te-ts)*w;
            return sum;
        }

        i++;
        s = ar[ns][i][0];
        e = ar[ns][i+1][0];
        w = ar[ns][i][1];
    }
    
}
int main()
{
    int n;
    cin >> n;
    int ar[n][101][2];

    for(int i = 0;i != n;++i)
        for(int j = 0;j != 100;++j)
            ar[i][j][0] = ar[i][j][1] = -1;

    for(int i = 0;i != n;++i) {
        int mi;
        cin >> mi;
        for(int m = 0;m != mi;++m) {
            cin >> ar[i][m][0] >> ar[i][m][1];
        }

        ar[i][mi][0] = 10001;
        ar[i][mi][1] = ar[i][mi-1][1];
    }

    int Q;
    cin >> Q;

    int sums[n];
   
    for(int i = 0;i != Q;++i) {
        //init sums
        for(int i = 0;i != n;++i)
            sums[i] = 0;

        int qi;
        cin >> qi;
        for(int ns = 0;ns != n;++ns) {
            sums[ns] = Length(ns,qi,ar); 
        }

        int Max = 0;
        int num;
        for(int ns = 0;ns != n;++ns)
            if(Max < sums[ns]) {
                Max = sums[ns];
                num = ns;
            }
        printf("%d\n",num+1);

    }
    return 0;
}

