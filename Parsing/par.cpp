#include <iostream>
#include <vector>
using namespace  std;
int main()
{
    vector<string> vv;
    vv.push_back("123");
    vv.push_back("456");
    vv.push_back("789");
    vv.push_back("");

    for(size_t m = 0;m != vv.size()-1;++m)
        if(vv[m].size()) {
            vv[m] = vv[m].substr(0,vv[m].size()-1);
        }
        else {
            vv.erase(vv.begin()+m);
        }

    if(!(vv.end()-1)->size())
        vv.erase(vv.end()-1);
    for(auto &e:vv)
        cout <<e << endl;
}
