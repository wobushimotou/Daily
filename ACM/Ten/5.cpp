#include <iostream>
#include <vector>
#include <deque>
#include <math.h>
using namespace std;

int height(int x) {
    int n = 0;
    int h = 0;

    while(true) {
        x -= pow(2,n);
        n++;
        h++;
        if(x <= 0)
            break;
    }

    return h;
}

int father(int x) {
    return x/2;
}
int main()
{
    int q;
    cin >> q;

    int x,h;
    for(int i = 0;i != q;++i) {
        cin >> x;
        cin >> h;

        int h_x = height(x);
        if(h >= h_x) {
            cout << "-1" << endl;
            continue;
        }
        for(int j = 0;j != h_x-h;++j) {
            x = father(x);
        }
        cout << x << endl;
    }
    return 0;
}

