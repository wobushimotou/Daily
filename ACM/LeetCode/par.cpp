#include <iostream>
#include <set>

using namespace std;
struct A{
    A(int _a,int _b): a(_a),b(_b){  }
    int a;
    int b;
    bool operator<(const A &_a)const {
        return a < _a.a;        
    }
    bool operator==(const A &_a)const {
        return a == _a.a && b == _a.b;        
    }
};
int main()
{
    set<A> iset;

    A a(11,12);
    iset.insert(a);

    a.b = 13;
    if(iset.find(a) == iset.end())
        cout << "true" << endl;
    
    return 0;
}

