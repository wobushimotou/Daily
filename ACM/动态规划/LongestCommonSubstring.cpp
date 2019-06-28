#include <iostream>
#include <string>
#include <vector>
/*
 *  最长公共子序列问题　动态规划
 * 
 * */
using namespace std;
class LongestCommonSubstring{
public:
    string a;
    string b;
    string c[50][50];
    string GetLongest(int,int);
    string Max(string a,string b) {
        if(a.size() > b.size())
            return a;
        return b;
    }
};
string LongestCommonSubstring::GetLongest(int x,int y) {
    if(x < 0 || y < 0)
        return "";
    if(c[x][y].size() )
        return c[x][y];
    if(a[x] == b[y]) {
        c[x][y] = GetLongest(x-1,y-1) + a[x];
        return c[x][y];
    }
    else{
        c[x][y] = Max(GetLongest(x,y-1),GetLongest(x-1,y));    
        return c[x][y];
    }
    
}

int main()
{
    LongestCommonSubstring lc;
    lc.a = "13456778";
    lc.b = "357486782";
    cout << lc.GetLongest(lc.a.size()-1,lc.b.size()-1) << endl; 
    return 0;
}

