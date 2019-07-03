#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
int main()
{
    vector<int> ar = {1,2,3,4,6,7,8,9,10,11};
    vector<int> b  ={11,12,13,14,15,16};
    copy(b.begin(),b.end(),ar.begin()+1);
    for(auto p = ar.begin();p != ar.end();++p)
        cout << *p << " ";
    return 0;
}

