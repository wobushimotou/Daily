#include <iostream>
#include <string>
#include <memory>
#include <utility>
#include <initializer_list>
#include <algorithm>

int num = 10;
template <typename T> class Vector{
public:
    
    //构造函数
    Vector() : elements(NULL),first_free(NULL),cap(NULL){ };
    Vector(std::initializer_list<T>);
    Vector(const Vector<T> &);  //拷贝构造函数
    Vector &operator=(const Vector<T> &);   //拷贝赋值运算符
    Vector(const Vector &&v) : elements(v.elements),cap(v.cap),first_free(v.first_free) { };              //移动构造函数

    ~Vector() { this->free(); };                  //析构函数

    //插入元素
    void push_back(const T &);
    template <typename ... Args> void emplace_back(Args ... args);
    size_t size() { return first_free - elements; }
    size_t capacity() { return cap - elements; }

    //迭代器操作
    T *begin() { return elements; };
    T *end() { return first_free; }; 
    
private:
    static std::allocator<T> alloc; //用于分配内存空间的分配器
    //检查已有空间大小,若溢出则分配另外的空间
    void check_n_alloc() { if(size() == capacity()) reallocate(); }
    void free();//销毁元素并且释放内存
    void reallocate();//获取更多内存并拷贝已有元素
    
    std::pair<T*,T*> alloc_n_copy(const T*,const T*);
    T *elements;//指向首元素
    T *first_free;//指向已分配空间的未构造位置
    T *cap;     //指向尾元素
};
//列表初始化
template <typename T>
Vector<T>::Vector(std::initializer_list<T> l)
{
    auto newdata = alloc_n_copy(l.begin(),l.end());
    elements = newdata.first;
    first_free = cap = newdata.second;
}
//初始化类模板静态成员
template <typename T>
std::allocator<T> Vector<T>::alloc;

template <typename T>
void Vector<T>::push_back(const T &t)
{
    //检查空间是否足够
    check_n_alloc();
    //在first_free指向的空间中构造元素
    alloc.construct(first_free++,t);
}

template<typename T>
std::pair<T*,T*> Vector<T>::alloc_n_copy(const T *b,const T *e)
{
    //分配新的空间
    auto data = Vector<T>::alloc.allocate(e-b);
    //将b,e范围内的元素拷贝到以data为起始位置的已分配空间上并返回起始地址和尾部地址
    return {data,std::uninitialized_copy(b,e,data)};
}
template <typename T>
void Vector<T>::free() 
{
    if(elements) {
        //对所有已构造的空间执行析构函数
        for(auto p = first_free;p != elements;) {
            Vector<T>::alloc.destroy(--p);
        }
        //回收空间
        Vector<T>::alloc.deallocate(elements,cap-elements);
    }
}
template <typename T>    
void Vector<T>::reallocate()
{
    //计算需要申请多少空间
    auto newcapacity = size()?2*size():1;
    //申请空间
    auto newdata = Vector<T>::alloc.allocate(newcapacity);
    //将数据从旧内存移动到新内存
    auto dest = newdata;
    auto elem = elements;
    for(size_t i = 0;i != size();++i)
        Vector<T>::alloc.construct(dest++,std::move(*elem++));
    //释放旧空间
    this->free();
    //更新指针指向
    elements = newdata;
    first_free = dest;
    cap = elements + newcapacity;
}
template <typename T>
Vector<T>::Vector(const Vector<T> &V)
{
    auto newdata = alloc_n_copy(V.elements,V.first_free);
    elements = newdata.first;
    cap = first_free = newdata.second;
}

template <typename T>
Vector<T>&  Vector<T>::operator=(const Vector<T> &V)
{
    
    auto data = alloc_n_copy(V.elements,V.first_free);
    this->free();
    elements = data.first;
    first_free = cap = data.second;
    return *this;
}

template <typename T>
template <typename ... Args> 
void Vector<T>::emplace_back(Args ... args)
{
    check_n_alloc();
    alloc.construct(first_free++,std::forward<Args>(args)...); 
}

int main()
{
    Vector<std::string> v({"12","34","56"});
    
    
    

    for(auto e : v)
        std::cout << e << std::endl;
    return 0;
}

