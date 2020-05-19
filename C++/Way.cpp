#include <string>
using namespace std;
int Way(string s) {
    int sum = 0;
    for(int i = 0;i != s.size();++i) {
        int num = s[i]-'0';
        int t;
        if(num >= 0 && num <= 9) {
            t = num;
        }
        else {
            t = s[i]-'A'+10;
        }
        sum = sum*10+t;
    }
    return sum;
}
