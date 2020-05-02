#include <iostream>
#include <vector>
#include <deque>
#include <unistd.h>
#include <stdio.h>

using namespace std;

long to_num(string s) {
    long sum = 0;
    for(int i = 0;i != s.size();++i) {
        sum += sum*10+ s[i]-'0';
    }
    return sum;
}
int main()
{
    int n;
    int m;
    

    cin >> n;
    string way;
    for(int i = 0;i != n;++i) {
            m = 0;            
            cin >> m;
            deque<int> deq;
                getline(cin,way);

            for(int j = 0;j != m;++j) {
                way = "";
                getline(cin,way);
                if(way == "TOP") {
                    if(deq.size() > 0) 
                        cout << deq.front() << endl;
                    else
                        cout << "-1" << endl;
                }
                else if(way == "POP") {
                    if(deq.size() > 0)
                        deq.pop_front();
                    else
                        cout << "-1" << endl;
                }
                else if(way == "SIZE") {
                    cout << deq.size() << endl;
                }
                else if(way == "CLEAR") {
                    deq.clear();
                }
                else if(way.size() > 0){
                    cout << way.substr(5,way.size()) << endl;;
                    long num = to_num(way.substr(5,way.size()));
                    cout << num << endl;
                    deq.push_back(num);
                }
                way = ""; 
            }
            
    }

    return 0;

}

