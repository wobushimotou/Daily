#include <iostream>
#include <list>
#include <vector>

using namespace std;
int main()
{
    vector<int> vec;
    for(int i = 0;i < 10;++i) {
        vec.push_back(i);
    }
    auto p = vec.begin();
    auto q = p+1;
    int temp = *q;
    temp = *q;
    *q = *p;
    *p = temp;

    cout << *vec.begin() << endl;
    cout << *(vec.begin()+1) << endl;
   
}

