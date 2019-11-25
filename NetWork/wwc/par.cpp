#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <memory>
class A{
public:
    A():a(1),b(2) {  }
    int a;
    char b;
};
void fun(A *p) {
    std::cout << p->a << std::endl;
    
}

void test() {

    auto p = std::make_shared<A>();
    
    A *a = p.get();

    std::cout << p.use_count() << std::endl;
}
int main()
{
    std::shared_ptr<A> a(new A());
    return 0;
}

