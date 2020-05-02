/*
 *  无重复字符最长子串
 * */
#include <iostream>
#include <map>
using namespace std;
string function(string s) {
    map<char,int> imap;
    int left = 0;
    int right = 0;
    int tleft = 0;
    int tright = 0;
    for(size_t i = 0;i < s.size();++i) {
        auto p = imap.find(s[i]);
        if(p == imap.end()) {
            if(right-left < tright - tleft) {
                right = tright;
                left = tleft;
            }
        }
        else {
            tleft = p->second+1; 
        }
        tright++;
        imap[s[i]] = i;
    }
    return s.substr(left,right-left+1);
}

int main()
{
    string s;
    cin >> s;
    cout << function(s) << endl;
    return 0;
}

