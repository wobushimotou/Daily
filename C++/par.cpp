#include <iostream>
using namespace std;

class A{
public:
    A() = default;
    A(int _a):a(_a) {  cout << "4\n";}
    A(const A &a);
    ~A() {
        a = 0;
    }
    A operator=(const A &a) {
        cout << "3\n";
        this->a = a.a;
        return *this;
    }

    int a;
};

A::A(const A &a) {
    cout << "2" << endl;
}


A fun() {
    A t(9);
    return t;
}

int main()
{
    A b = fun();
    /* cout << b.a << endl; */
    return 0;
}

