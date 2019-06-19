#include <iostream>
#include <sstream>
using namespace std;
int main()
{
    string buf;
    stringstream s;
    s << "wang";
    s << " heng";

    s >> buf;
    cout << buf << endl;
    return 0;
}

