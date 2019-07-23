/*
 *  n=0到n=k,可以n++,n--,n*=2,求到达k点的最短走法步数
 *
 *
 * */
#include <iostream>
#include <vector>
using namespace std;

int f(int n,int i) {
    if(i == 0)
        return n*2;
    else if(i == 1)
        return ++n;
    else
        return --n;
}
bool found;
int k;
int j;
bool BackTrack(int m,int depth) {
    if(depth > k) {
        return false;
    }
    else {
        for(int n = 0;n < 3;++n) {
            int temp = f(m,n);
            if(temp == j || BackTrack(temp,depth+1)) {
                found = true;
                return found;
            }
        }
        return false;
    }     
}



int main()
{
   found = false;
   cin >> j;
   k = 1;
    while(!BackTrack(0,1)) {
        if(found)
            break;
        k++;
    }
    cout << k << endl;
 
    return 0;
}

