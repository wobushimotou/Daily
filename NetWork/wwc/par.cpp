#include <iostream>
#include <memory>
class A{
public:
    A():a(1),b(2) {  }
    int a;
    char b;
};
int main()
{
    std::shared_ptr<A> p = std::make_shared<A>();
    std::cout << p->a << std::endl;
    return 0;
}

