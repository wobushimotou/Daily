#include <iostream>
#include <vector>
#include <map>
using namespace std;
int main()
{
    vector<int> vec;
    int n;
    while(cin >> n) {
        vec.push_back(n);
    }



    map<int,int> imap;

    
    size_t Size = vec.size();

    for(size_t i = 0;i < Size;++i) {
        if(imap.find(vec[i]) != imap.end()) {
            vec.erase(vec.begin()+i);
            Size--;
            i--;
        }
        else
            imap[vec[i]]++;
    }

    for(auto &e:vec)
        cout << e << " ";
    cout << endl;

    return 0;
}

