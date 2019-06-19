#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <memory>
#include <utility>

template <typename T> 
int compare(const T &v1,const T &v2)
{
    if(v1 > v2)
        return 1;
    else
        return -1;
    return 0;
}

template <typename T,typename U> 
bool Find(const T &it1,const T &it2,const U &val)
{
    T it3 = it1;
    for(;it3 != it2;it3++)
        if(*it3 == val)
            return true;
    return false;
}

template <typename T>
void print(const T &ar)
{
    for(auto n : ar)
        std::cout << n << " ";
}
template <typename T,unsigned N>
const T *begin(const T (&arr)[N])
{
    return arr;
}

template <typename T,unsigned N>
const T *end(const T (&arr)[N])
{
    return arr+N;
}

template <typename T,unsigned N>
constexpr size_t Size(const T (&arr)[N])
{
    return N;
}

template <typename T> class Blob;
template <typename T> class BlobPtr;

template <typename T>
bool operator==(const Blob<T> &b1,const Blob<T> &b2)
{
    return b1.data == b2.data;
}

template <typename T> class Blob{
    template <typename X> friend class BlobPtr;
    friend bool operator== <T>(const Blob<T> &,const Blob<T> &);
public:
    typedef T value_type;
    typedef typename std::vector<T>::size_type size_type;
    //构造函数
    Blob() : data(std::make_shared<std::vector<T>>()) {  };
    Blob(std::initializer_list<T> i1) : data(std::make_shared<std::vector<T>>(i1)) {  };
    //Blob中的元素数目
    size_type size() const {return data->size();}
    bool empty()const { return data->empty(); }
    //添加和删除元素
    void push_back(const T &t) {data->push_back(t);}
    void pop_back() { check(0,"pop_back on empty Blob"); data->pop_back(); }
    
    //元素访问
    T &back() { check(0,"back on empty Blob"); return data->back(); };
    T &operator[](size_type i) {  check(i,"subscript out of range"); return (*data)[i]; };
private:
    std::shared_ptr<std::vector<T>> data;
    void check(size_type i,const std::string &msg) const;
};

template <typename T>
void Blob<T>::check(size_type i,const std::string &msg) const
{
    if(i >= data->size())
        throw std::out_of_range(msg);
}

template <typename T> class BlobPtr{
public:
    typedef typename std::vector<T>::size_type size_type;
    //构造函数
    BlobPtr();
    BlobPtr(Blob<T> &a,size_t sz = 0) : wptr(a.data),curr(sz) {  }
    //解引用运算符
    T& operator*()const {auto p = check(curr,"dereference past end"); return (*p)[curr];}
    //递增递减运算符
    BlobPtr operator++();
    BlobPtr operator--();
    //关系运算符
private:
    std::shared_ptr<std::vector<T>> check(size_type,const std::string&) const;
    std::weak_ptr<std::vector<T>> wptr;
    std::size_t curr;
};
template <typename T>
bool operator!=(const Blob<T> &b1,const Blob<T> &b2)
{
    return !(b1 == b2);
}

template <typename T>
std::shared_ptr<std::vector<T>> BlobPtr<T>::check(size_type i,const std::string& msg) const
{
    auto p = wptr.lock();
    if(i >= p->size())
        throw std::out_of_range(msg);
    return p;
}

template <typename T>
BlobPtr<T> BlobPtr<T>::operator++()
{
    BlobPtr ret = *this;
    ++*this;
    return ret;
}

template <typename T>
BlobPtr<T> BlobPtr<T>::operator--()
{
    BlobPtr ret = *this;
    --*this;
    return ret;
}

template <typename T>
void ForEach(T &t)
{
    for(auto e : t)
        std::cout << e << std::endl;
    for(auto q = t.begin();q != t.end();++q)
        std::cout << *q << std::endl;
}

template <typename T> class DebugDelete{
public:
    DebugDelete(std::ostream &s) : os(s) {  }
    
    void operator()(T *p)const {
        os << "deleting unique_ptr" << std::endl;
        delete p;
    }
private:
    std::ostream &os;
};

template <typename T>
bool Compare(const T &lhs,const T &rhs)
{
    return lhs < rhs;
}

template <typename T>
auto Sum(const T& lhs,const T& rhs) ->decltype(lhs + rhs)
{
    return lhs+rhs;
}
template <typename F,typename T1,typename T2>
void fun(F f,T1 &&lhs,T2 &&rhs)
{
    f(std::forward<T2>(rhs),std::forward<T1>(lhs));
}
void f(int &&a,int &b)
{
    std::cout << a << " " << ++b << std::endl;
}
template <typename T,typename ... Args>
void foo(const T &t,const Args& ... rest)
{

}
template <typename ... Args> void g(Args ... args)
{
    std::cout << sizeof...(Args) << std::endl;
    std::cout << sizeof...(args) << std::endl;
}

template <typename T> std::ostream &print(std::ostream &os,const T &t)
{
    return os << t << std::endl;;
}

template <typename T,typename ... Args> std::ostream &print(std::ostream &os,const T &t,Args ... rest)
{
    os << t << ",";
    return print(os,rest...);
}

template <typename T,typename U>
size_t Count(const std::vector<T> &vec,const U e)
{
    size_t timecount = 0;
    for(auto n : vec)
        if(n == e)
            timecount++;
    return timecount;
}

template<> 
size_t Count(const std::vector<const char *> &vec,const char *val)
{
    size_t timecount = 0;
    for(auto n : vec)
        if(*n == *val)
            timecount++;
    return timecount;
}
template <typename T,typename U>
void f(T t,U u)
{

}
template<>
void f(int a,double b)
{

}

int main()
{
    std::vector<const char *> v= {"wh","gl","wh"};
    std::cout << Count(v,"wh") << std::endl;
    return 0;

}

