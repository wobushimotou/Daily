#include <string>
#include <iostream>
#include <deque>
using namespace std;
class Transform {
public:
    string trans(string s, int n) {
        // write code here
        deque<string> deq;
        string temp;
        
        
        int flag = 0;
        int flag2 = 0;
        for(int i = 0;i != n;++i) {
            if(s[i] == ' ')
                flag = 1;
            if(s[i] != ' ')
                flag2 = 1;
        }
        
        if(!flag2 || !flag || s.size() <= 2)
            return s;
        
        for(int j = 0;j != s.size();++j) {
            if(s[j] == ' ')
                continue;
            if(s[j] >= 'a' || s[j] <= 'z')
                s[j] -= 32;
            else
                s[j] += 32;
            
        }

        cout << s << endl;        
        
        for(int i = 0;i < n;++i) {
            
            if(s[i] == ' ') {
                deq.push_front(temp);
                temp = "";
                continue;
            }
            
            temp += s[i];
        }
        
        string ss;
        for(auto p = deq.begin();p != deq.end();++p)
            if(p != deq.end()-1)
                ss += *p+" ";
            else 
                ss += *p;
       
        return ss;
    }
};
int main() {
    Transform ts;
    string s = "hello world";
    cout << ts.trans(s,s.size()) << endl;;
}
