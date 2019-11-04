#include <iostream>
#include <memory>
#include <vector>
using namespace std;
struct A{
    int a;
    long b;
};
int main()
{
    allocator<A> alloc;
    A *data = alloc.allocate(1);
    alloc.construct(data,A());
    return 0;
}

