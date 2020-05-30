#include <iostream>
#include <functional>
using namespace std;

class A{
public:

    A() { cout << "A()" << endl; }
    ~A() { cout << "~A()" << endl; }
    A(const A&) { cout << "A(const A&)" << endl;}
    A& operator=(const A&)  { cout << "=A&" << endl; return *this;}
    A* operator&() { cout << "AAAA" << endl; return this; } 
    const A* operator&()const { cout << "AAAA" << endl; return this; } 
    A(A &&){ cout << "A&&" << endl; }
    A& operator=(A &&) { cout << "=A&&" << endl; return *this;}

    virtual void func()const { cout << "func" << endl;}
};


class B{
public:
    B():b(1){  }
    long b;
    void f(){ cout << ">>>" << endl; }
};

class C:public B{
public:
    C():c(2){  }
    long c;
    void f(int i){ cout << "<<<" << endl; }
    void fc2(){ cout << "<<<" << endl; }
};

struct D{
    char a;
    int b;
};
int main()
{
    return 0;
}
