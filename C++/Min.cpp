#include <iostream>
#include <string>
#include <fstream>
#include <map>
using  namespace std;
int Min(string s1,string s2) {

    int dp[s1.size()+1][s2.size()+1];

    for(size_t i = 0;i != s1.size()+1;++i)
        dp[i][0] = i;

    for(size_t j = 0;j != s2.size()+1;++j)
        dp[0][j] = j;

    for(size_t i = 1;i != s1.size()+1;++i) {
        for(size_t j = 1;j != s2.size()+1;++j) {
            if(s1[i-1] == s2[j-1])
                dp[i][j] = dp[i-1][j-1];
            else {
                dp[i][j] = min(dp[i-1][j-1],dp[i-1][j],dp[i][j-1])+1;
            }
        }
    }
    return dp[s1.size()][s2.size()]; 
}
int main()
{
    string s;
    cin >> s;
    
    //打开词库
    fstream file("1.txt");
    
    string t;

    map<int,string> imap;

    while(file >> t) {
        if(t.size() > s.size()) {
            imap[Min(t,s)] = t;
        }
    }

    cout << imap.begin()->second << endl;
    return 0;
}

