#include <iostream>
#include <map>
#include <vector>
#include <algorithm>
using namespace std;

int main()
{
    int n;
    vector<int> vec;
    while(cin >> n) {
        vec.push_back(n);
    }

    map<int,int> imap;

    for(auto &e:vec)
        imap[e]++;

    
    int Max = 0;
    for(auto &e : imap)
        if(Max < e.second)
            Max = e.second;

    
    vector<int> Vec;

    for(auto &e:vec) {
        if(imap[e] == Max)
            Vec.push_back(e);
    }


    sort(Vec.begin(),Vec.end());

    cout << *(Vec.end()-1) << endl;
    return 0;
}

