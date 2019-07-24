#include <iostream>
#include <vector>
#include <memory>
#include <thread>
#include <mutex>
#include <sys/uio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

using namespace std;
std::mutex mtx;
class Foo *X;
class Foo{
public:
    void f() { std::cout << "1" << std::endl; }
};

void fun()
{
    mtx.lock();
    delete X;
    mtx.unlock();
}
void fun2()
{
    mtx.lock();
    X->f();
    mtx.unlock();
}
class A{
public:
    A() { f();}
    virtual void f() { cout << "f" << endl; }
};
class B : public A{
public:
    B() { f(); }
    virtual void f2() { cout << "f2" << endl; }
};
void f(void)
{
    std::cout << "f" << std::endl;
}

class C{
public:
    C() = default;
    //C(const C& c);

};

class a{
    int a;
    int b;
};
class aa : public a{

};
using namespace std;
int main()
{
    int fd = open("1.txt",O_RDWR);

}

