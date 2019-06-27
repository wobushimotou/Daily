#include <iostream>
#include <map>

using namespace std;
int main()
{
    map<int,int> imap;
    int num;
    for(int i = 0;i < 6;++i) {
        cin >> num;
        imap[num]++;
    }

    int max = 0;
    auto p = imap.begin();
    auto q = p;
    for(;p != imap.end();++p) {
        if(p->second > max) {
            max = p->second;
            q = p;
        }
    }
    cout << q->first << " " << q->second << endl;
    return 0;
}

