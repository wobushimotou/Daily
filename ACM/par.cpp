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
    cout << vec.at(1) << endl;
    vec.clear();
    vec.push_back(11);
    cout << vec.at(0) << endl;
    
}

