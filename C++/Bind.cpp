#include <iostream>
#include <vector>
#include <functional>
using namespace std;
void f(int &a,double &b) {
    a = 18;
    b = 19;
    cout << a << " " << b << endl;
}
int main()
{
    int a = 10;
    double b = 11;
    auto p = std::bind(f,ref(a),ref(b));
    
    p();
    cout << a << " " << b << endl;
    return 0;
}

