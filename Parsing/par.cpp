#include <iostream>
#include <vector>
#include <algorithm>
using namespace  std;
class A{
public:
    A() = default;
};
int main()
{
    string ss;
    vector<char> vv = {'1','2','3','4'};
    copy(vv.begin(),vv.end(),back_inserter(ss));

    
    string sd = "wang1heng2";

    size_t n = 0;
    do{
        n = sd.find_first_of(ss,0);
        sd[n] = 'w';
        cout << n << endl;
        
    }while(n != string::npos);

    return 0;
}
