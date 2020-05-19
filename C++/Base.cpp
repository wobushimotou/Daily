#include <iostream>
using namespace std;

class A{
public:
    virtual void f() { cout << "A" << endl; }
};

class B{
public:
    virtual void f() { cout << "B" << endl; }
};


class C:public A,public B{
public:
    /* virtual void f() { cout << "C" << endl; } */
};

typedef void(*Fun)(void);
int main()
{
    C c;
    //虚表地址
    cout << *(long *)&c << endl;

    //虚表第一个函数地址
    cout << (long *)*(long *)(&c) << endl;

    cout << sizeof(C) << endl;
    A *a = &c;
    a->f();

    return 0;
}

