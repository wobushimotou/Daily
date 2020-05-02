#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
using namespace std;

map<char,vector<size_t>> imap;
struct Info{
    size_t start;
    size_t end;
    size_t size;
};
vector<struct Info> vec;
string Function(string &s) {
    for(size_t i = 0;i != s.size();++i) {
        imap[s[i]].push_back(i);
    }

    bool flag;
    for(size_t i = 0;i != s.size();++i) {
        auto p = find(imap[s[i]].begin(),imap[s[i]].end(),i);
        ++p;
        flag = true;
        if(p != imap[s[i]].end() && s.size()-*p >= *p - i) {
            for(size_t m = i,n = *p;m != *p;++m,++n) {
                if(s[m] != s[n]) {
                    flag = false;
                    break;
                }
            }
        }

        if(flag) {
            bool f = true;
            for(auto m = vec.begin();m != vec.end();++m) {
                if(i == m->end) {
                    m->end = *p;
                    f = false;
                }
            }
            if(f) {
                vec.push_back({i,*p+*p-i,*p-i});
            }

        }
    }

}
int main()
{
    

    return 0;
}

