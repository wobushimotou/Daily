/*
 *  寻找合法字符问题,输入一个表格和一个单词，查找单词在表格上的合法序列的数量
 *  
 *
 * */
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

int main()
{
    string s;
    int m,n;
    cin >> m >> n;
    char form[m][n];
    for(int i = 0;i < m;++i)
        for(int j = 0;j < n;++j) {
            cin >> form[i][j];
        }
    cin >> s;

    for(int i = 0;i < m;++i)
        for(int j = 0;j < n;++j)
        if(find(s.begin(),s.end(),form[i][j]) == s.end()) {
            form[i][j] = 'x';
        }

    int sum = 0;
    for(int i = 0;i < m;++i) {
        for(int j = 0;j < n;++j) {
            if(form[i][j] == 'x')
                continue;
            bool l1 = false,l2 = false,l3 = false;
            sum += 3;
            for(int k = 0;k < s.size();++k) {
                if(form[i][j+k] != s[k] || j+k >= n)
                    l1 = true;
                if(form[i+k][j] != s[k] || i+k >= m)
                    l2 = true;
                if(form[i+k][j+k] != s[k] || i+k >= m || j+k >= n)
                    l3 = true;
            }
            if(l1)
                sum--;
            if(l2)
                sum--;
            if(l3)
                sum--;
        }
    }
    cout << sum << endl;


    return 0;
}

