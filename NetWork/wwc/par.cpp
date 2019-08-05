#include <iostream>
#include <map>
using namespace std;
int main()
{
    map<int,string> imap;
    imap[0] = "wh";
    imap[1] = "gl";
    size_t n = imap.erase(1);
    cout << n << endl;
    return 0;
}

