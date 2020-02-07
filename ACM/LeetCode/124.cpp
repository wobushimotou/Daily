#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
using namespace std;

string shortestPalindrome(string s) {
        string r=s;
        reverse(r.begin(),r.end());
        string t=s+"#"+r;
        int n=t.size();
        vector<int> idx(n,-1);
        for(int i=1;i<n;i++){
            int p=idx[i-1];
            while(p!=-1&&t[i]!=t[p+1])
                p=idx[p];
            if(p==-1) idx[i]=t[i]==t[0]?0:-1;
            else idx[i]=p+1;
        }

        string tmp=s.substr(idx[n-1]+1,s.size()-idx[n-1]-1);
        reverse(tmp.begin(),tmp.end());
        return tmp+s;
}

bool IsRepeat(string s,int r,int l) {
    for(int i = r;i < l/2;++i)
        if(s[i] != s[l-i-1])
            return false;
    return true;
}
string shortestPalindrome2(string s) {
    size_t i = s.size();
    string r;
    for(;i >= 1;--i) {
        if(IsRepeat(s,0,i)) {
            r = s.substr(i,s.size()-i);
            break;
        }
    }
    cout << r << endl;
    reverse(r.begin(),r.end());
    return r+s;
}


int main()
{

    string s;
    cin >> s;
    s.substr(1,s.size()-2);

    cout << shortestPalindrome2(s) << endl;    
    return 0;
}

