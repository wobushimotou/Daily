#include <iostream>
#include <functional>

using namespace std;


void f(int a) {

}
int main()
{
    int b;
    auto fptr = std::bind(f,std::placeholders::_1);
    fptr(1);

    return 0;
}

