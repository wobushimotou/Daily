#include <iostream>
#include <vector>
using namespace  std;
int main()
{
    string ss = "P->Pa|b";
    string tt;
    int t = ss.find_first_of("|");
    string x = ss.substr(4,t-4);
    string y = ss.substr(t+1,ss.size());
    char A = 'p';
    ss = ss.substr(0,3);
    ss += y+A;
    tt += A;
    tt += "->"+x+A+"|@";
    cout << x << endl;
    cout << y << endl;
    cout << ss << endl;
    cout << tt << endl;
}
