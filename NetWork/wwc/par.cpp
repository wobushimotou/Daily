#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <memory>
#include <map>
#include <fcntl.h>
class A{
public:
    A():a(1),b(2) {  }
    int a;
    char b;
};
using namespace std;
class foo : public enable_shared_from_this<foo>
{
public:
    shared_ptr<foo> test()
    {
        return shared_from_this();
    }
};

int main(int argc, char* argv[])
{

    map<string,string> imp;
    
    int a[10];
    int *p = &a[0];
    int *q = &a[1];

    long n = (long )(void *)p;
    long m = (long )(void *)q;
    printf("%ld\n",n);
    printf("%ld\n",m);
    printf("%p\n",p);
    return 0;
}

