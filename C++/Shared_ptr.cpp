#include <iostream>
#include <memory>
#include <utility>
#include <functional>

template<typename T> class Shared_ptr{
public:

    //构造函数
    Shared_ptr() : ptr(NULL),use(NULL) {   }
    explicit Shared_ptr(T *p) : ptr(p),use(new size_t(1))  {  }

    //拷贝构造函数
    Shared_ptr(Shared_ptr<T> const &p);
    //移动构造函数

    //运算符重载
    //拷贝赋值运算符
    Shared_ptr<T> &operator=(const Shared_ptr<T> q);
    //解引用运算符
    T &operator*();
    //指针运算符
    T *operator->();
    //比较运算符
    bool operator==(const Shared_ptr<T> &q) { return this->ptr == q.ptr; };
    bool operator!=(const Shared_ptr<T> &q) { return !(*this == q); }

    //返回指向对象的指针
    T *get() { return ptr; }
    
    //释放该对象
    void reset() { Delete(); }
    //重新设置指向的对象
    void reset(Shared_ptr<T> &q) { this = q; }
    void reset(Shared_ptr<T> &q,void (*fun)(Shared_ptr<T> &ptr)) { *this = q;f = fun; }
    
    //返回该对象的引用计数
    size_t use_count() { return *use; }

    bool unique() { return (*use) == 1; }
    
    void swap(Shared_ptr<T> &q);
    //析构函数
    ~Shared_ptr() { if(f) f(*this); else Delete(); };

    void Delete() {
        if(ptr && --*use == 0) {
            delete ptr;
            delete use;
        }
    }

private:    
    size_t *use;
    T *ptr;
    void (*f)(Shared_ptr<T> &) = NULL;
};
template <typename T>
T *Shared_ptr<T>::operator->()
{
    return ptr;
}
template <typename T>
T &Shared_ptr<T>::operator*()
{
        return *ptr;
}
    
template<typename T>    
Shared_ptr<T>::Shared_ptr(Shared_ptr<T> const &p)
{
    this->ptr = p.ptr;
    //拷贝构造时引用计数加一
    (*p.use)++;
    this->use = p.use;
}
template <typename T>
Shared_ptr<T> &Shared_ptr<T>::operator=(const Shared_ptr<T> q)
{
    if(*this == q)
        return *this;
    //拷贝赋值时被赋值方原有对象引用计数减一
    if(this->ptr)
        this->~Shared_ptr<T>();
    //赋值方对象引用计数加一
    (*q.use)++;
    this->ptr = q.ptr;
    this->use = q.use;
    return *this;
}

template <typename T>
void Shared_ptr<T>::swap(Shared_ptr<T> &q)
{
    Shared_ptr<T> temp;
    temp = q;
    q = *this;
    *this = temp;
}

void f(Shared_ptr<int> &ptr)
{
    std::cout << "f" << std::endl;
    delete ptr.get();
}

template <typename T,typename ... Args>
auto  Make_shared(Args && ...arg) ->Shared_ptr<T>
//Shared_ptr<T> &Make_shared(Args && ...arg)
{
    return Shared_ptr<T>(new T(std::forward<Args>(arg)...));
}

int main()
{
    int i = 99;
    auto p = Make_shared<int>(i);
    
    return 0;
}

