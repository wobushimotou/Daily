#include <iostream>
using namespace std;

void Way(int x,int y,int w,int &_x,int &_y) {
    if(w == 0) {
        _x = x-1;
        _y = y-1;
    }
    else if(w == 1) {
        _x = x+1;
        _y = y-1;
    }
    else if(w == 2) {
        _x = x+1;
        _y = y+1;
    }
    else {
        _x = x-1;
        _y = y+1;
    }
}
int Ret_W(int n_x,int n_y,int o_x,int o_y,int N,int M,int &C) {
    C += 2;
    if(n_x == 1 && n_y == 1)
        return 2;
    if(n_x == M-2 && n_y == 1)
        return 3;
    if(n_x == 1 && n_y == N-2)
        return 1;
    if(n_x == M-2 && n_y == N-2)
        return 0;

    C--;
    if(n_y == 1) {
        if(o_x < n_x)
            return 2;
        else 
            return 3;
    }

    if(n_y == N-2) {
        if(o_x < n_x)
            return 1;
        else 
            return 0;
    }

    if(n_x == 1) {
        if(o_y < n_y)
            return 2;
        else 
            return 1;
    }
    if(n_x == M-2) {
        if(o_y < n_y)
            return 3;
        else 
            return 0;
    }
}
int main()
{
    int n;
    cin >> n;

    int X,Y,W,T;
    int M,N;
    for(int i = 0;i != n;++i) {
        cin >> N >> M;
        cin >> X >> Y >> W >> T;

        /* int ar[N][M]; */
        /* //init */ 
        /* for(int x = 0;x != N;++x) { */
        /*     for(int y = 0;y != M;++y) */
        /*         if(x == 0 || y == 0 || x == N-1 || y == N-1) */
        /*             ar[x][y] = 1; */
        /* } */
        
        int o_x,o_y,w;
        int n_x,n_y;
        o_x = Y-1;
        o_y = X-1;
        w = W;
        int C = 0;

        for(int t = 0;t != T;++t) {
            /* cout << o_x << "," << o_y << "=" << w << " "; */ 
            Way(o_x,o_y,w,n_x,n_y);
            /* cout << n_x << "," << n_y << endl; */
            if(n_x == 1 || n_x == M-2 || n_y == 1 || n_y == N-2) {
                
                /* cout << n_x << "," << n_y << endl; */
                w = Ret_W(n_x,n_y,o_x,o_y,N,M,C);
                 
            }

            o_x = n_x;
            o_y = n_y;
        }
        printf("%d\n",C);
    }
    return 0;
}

