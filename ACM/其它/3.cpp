#include <iostream>
class ScopedPtr{
private:
    int *n_ptr;
    ScopedPtr(const ScopedPtr &);
    ScopedPtr& operator=(const ScopedPtr &);
public:
    ScopedPtr(int *ptr):n_ptr(ptr) {  }

    int& operator*() {
        return *n_ptr;
    }
    ~ScopedPtr() {
        delete n_ptr;
    }

};

void test(int n) {
    ScopedPtr ptr(new int(n));

    *ptr *= 2;
    std::cout << *ptr << std::endl;
}

int main() {
    int n = 0;
    std::cin >> n;
    test(n);
    return 0;
}
