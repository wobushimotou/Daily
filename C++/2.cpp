#include <iostream>
using namespace std;

class A{
public:
    virtual void func(){};
};

class B:public A {
public:
    void func() {} 
};
int main()
{
    A a;
    B b;

    cout << sizeof(a) << endl;
    cout << sizeof(b) << endl;
    return 0;
}

