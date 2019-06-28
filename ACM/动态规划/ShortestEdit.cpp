/*
 *  最短编辑距离问题　动态规划
 *
 *
 * */
#include <iostream>
#include <string>
#include <string.h>

using namespace std;
class ShortestEdit{
public:
    string a;
    string b;
    int edit[50][50];
    int Min(int i,int j,int k) {
        return Min(Min(i,j),k);
    }
    int Min(int i,int j) {
        return i>j?j:i;
    }
    int GetShort(int m,int n);
};
int ShortestEdit::GetShort(int m,int n) {
    if(m < 0 || n < 0)
        return 1;
    if(edit[m][n])
        return edit[m][n];
    if(a[m] == b[n]) {
        edit[m][n] = GetShort(m-1,n-1);
        return edit[m][n];
    }
    else {
        edit[m][n] = Min(GetShort(m-1,n)+1,GetShort(m,n-1)+1,GetShort(m-1,n-1)+1);
        return edit[m][n];
    }
}
int main()
{
    ShortestEdit se;
    bzero(se.edit,sizeof(se.edit));
    se.a = "abcd";
    se.b = "abcdef";
    cout << se.GetShort(se.a.size()-1,se.b.size()-1) << endl;

    return 0;
}

