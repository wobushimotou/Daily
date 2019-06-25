#include <iostream>
#include <vector>

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
    vector<int> Vec;
    bool Find(int n) {
        for(auto p = Vec.begin();p != Vec.end();++p) {
            if(*p == n)
                return true;
        }
        return false;
    }
    vector<int> CurrPath;
    vector<int> BestPath;
};

bool NumTransForMation::BackTrack(int m,int depth) {
    if(depth > k) {
        return false;
    }
    else {
        for(int i = 0;i < 2;++i) {
            int temp = f(m,i);
            if(Find(temp)) {
                found = false;
                return false;
            }
            CurrPath.push_back(i);
            Vec.push_back(temp);
            if(temp == j || BackTrack(temp,depth+1)) {
                BestPath = CurrPath;
                return true;
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

    while(!n.BackTrack(n.i,1)) {
        //出现重复值
        if(n.found == false) {
            break;
        }
        n.k++;
        n.CurrPath.clear();
        n.BestPath.clear();
    }

    if(n.found) {
        for(auto p = n.BestPath.begin();p != n.BestPath.end();++p) {
            if(*p == 0) {
                n.i = n.i*3;
                cout << "i*3=" << n.i << endl;
            }
            else { 
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

