#include <iostream>
#include <vector>
#include <string.h>
/*
    整数变换问题　回溯法
    */

using namespace std;
class NumTransForMation{
public:
    int f(int n,int i) { 
        if(i == 0)
            return n*3; 
        else 
            return n/2;
    }
    bool BackTrack(int m,int depth);
    int i,j;
    int k;
    bool found;
    int Vec[1000];
    bool Find(int n) {
        for(int i = 0;i < 1000 && Vec[i];++i) {
            if(Vec[i] == n)
                return true;
        }
        return false;
    }
    int CurrPath[1000];
};

bool NumTransForMation::BackTrack(int m,int depth) {
    if(depth > k) {
        return false;
    }
    else {
        for(int n = 1;n < 3;++n) {
            int temp = f(m,n-1);
            if(Find(temp)) {
                found = false;
                return false;
            }
            CurrPath[depth] = n;
            Vec[depth] = temp;
            if(temp == j || BackTrack(temp,depth+1)) {
                found = true;
                return found;
            }
        }
        CurrPath[depth] = 0;
        return false;
    }     
}



int main()
{
    NumTransForMation n;
    cin >> n.i >> n.j;
    n.found = true;
    n.k = 1;
    bzero(n.CurrPath,1000*4);
    bzero(n.Vec,1000*4);

    while(!n.BackTrack(n.i,1)) {
        //出现重复值
        if(n.found == false) {
            break;
        }
        n.k++;
        bzero(n.CurrPath,1000*4);
        bzero(n.Vec,1000*4);
    }

    if(n.found) {
        for(int i = 1;i < 1000 && n.CurrPath[i];++i) {
            if(n.CurrPath[i] == 1) {
                n.i = n.i*3;
                cout << "i*3=" << n.i << endl;
            }
            if(n.CurrPath[i] == 2){ 
                n.i = n.i/2;
                cout << "i/2=" << n.i << endl;
            }
        }
    }
    else {
        cout << "not found" << endl;
    }
    return 0;
}

