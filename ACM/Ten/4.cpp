#include <iostream>
#include <vector>
#include <stack>
using namespace std;

long to_num(string s) {
    long sum = 0;
    for(int i = 0;i != s.size();++i) {
        sum = sum*10+s[i]-'0';
    }
    return sum;
}

void fun(stack<int> &s_front,stack<int> &s_back,int w) {
    if(w == 0) {
        for(int i = 0;i < s_front.size();++i) {
            s_front.pop();        
        }

        stack<int> s_temp = s_back;

        for(int i = 0;i < s_temp.size();++i) {
            int num = s_back.top();
            s_front.push(num);
            s_back.pop();
        }
        
        s_back = s_temp;
        
    }
    else {
        for(int i = 0;i < s_back.size();++i) {
            s_back.pop();        
        }

        stack<int> s_temp = s_front;

        for(int i = 0;i < s_temp.size();++i) {
            int num = s_front.top();
            s_back.push(num);
            s_front.pop();
        }
        
        s_front = s_temp;
        
 
    }
}
int main()
{
    stack<int> s_front;
    stack<int> s_back;

    int n;
    cin >> n;

    string way;
                getline(cin,way);

            for(int j = 0;j != n;++j) {
                way = "";
                getline(cin,way);
                if(way == "peek") {
                    cout << s_front.top() << endl;
                }
                else if(way == "poll") {
                    s_front.pop();
                    fun(s_front,s_back,1);
                }
                else {
                    long num = to_num(way.substr(4,way.size()));
                    s_back.push(num);
                    fun(s_front,s_back,0);
                }
                way = ""; 
            }
 
    return 0;
}

