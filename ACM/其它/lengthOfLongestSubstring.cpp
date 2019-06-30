#include <iostream>
#include <string>
#include <algorithm>
#include <numeric>
using namespace std;
class Solution{
public:
    //求字符串最大不重复子串长度
    static size_t lengthOfLongestSubstring(string s) {
        int left = 0;
        size_t num = 0;
        int m[256] = {0};
        for(size_t i = 0;i < s.length();++i) {
            if(m[s[i]] == 0 || m[s[i]] < left)
                num = (num>(i-left+1))?num:(i-left+1);
            else
                left = m[s[i]];
            m[s[i]] = i+1;
        }
        return num;
    }
};


int main()
{
    Solution s;
    cout << s.lengthOfLongestSubstring("123123412345") << endl;
    return 0;
}

