#include <iostream>

class A{
    int ab;
    double b;
    virtual void f(void) { std::cout << "a" << std::endl; }
};

class B:public A{
    char c; 
};

typedef void(*pFun)(void);

int main()
{
    A a;


    long  v_ptr = *(long *)(&a);

    void(*f_ptr)(void);
    
    f_ptr = (pFun) *(long *)v_ptr;

    long b = 1;
    f_ptr = (void)(*)(void)b;
    
    f_ptr();
    
    return 0;
}

