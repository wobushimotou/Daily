#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

using namespace std;
class String{
    private:
        size_t length;
        char *data;
    public:
        //引用类型
        typedef char& reference;
        //迭代器类型
        class iterator;

        size_t npos = -1;
        //构造函数
        String();
        String(size_t length,char ch);
        String(const char *str);
        String(const char *str,size_t length);
        String(String &str,size_t index,size_t length);
        String(iterator begin,iterator end);

        String(String const  &str);

        //运算符重载函数
        char operator[](int num);
        //运算符比较函数
        bool operator==(String &s2);        
        bool operator!=(String &s2);
        bool operator<(String &s2);
        bool operator<=(String &s2);
        bool operator>(String &s2);
        bool operator>=(String &s2);
               
        //合并函数
        String operator+(String &s2);
        String operator+(const char *str);

        //赋值操作
        String &operator=(const String &s2);
        String &operator=(const char *str);
        String operator+=(String &s2);
        String operator+=(const char *str);

        friend istream& operator>>(istream &is,String &str);
        
        //特性函数
        char *c_str() const;    //返回指向的字符串
        size_t size() const;    //返回当前字符串长度
        bool empty() const;     //返回字符串是否为空
        void resize(size_t len,char c);    //把字符串当前大小置为len，多去少补，多出的字符c填充不足的部分

        //查找函数
        size_t find(const String &str,size_t index); //从index开始寻找,返回str在字符串中第一次出现的位置 
        size_t find( const char *str, size_t index );
        size_t find(const String &str,size_t index,size_t length);
        size_t find( const char *str, size_t index,size_t length);
        size_t find( char ch, size_t index );  // 返回字符ch在字符串中第一次出现的位置
        
        size_t rfind(String &str,size_t index,size_t length);//从index开始，返回str的前length个字符串在字符串中最后一次出现的位置
        size_t rfind(String &str,size_t index);
        size_t rfind( char ch, size_t index );  // 返回字符ch在字符串中第一次出现的位置
        size_t rfind(const char *str,size_t index);

        
        size_t find_first_of(String &str,size_t index);//从index开始,查找str中任意字符第一次出现的位置
        size_t find_first_of(const char *str,size_t index);
        
        size_t find_last_of(String &str,size_t index); //从index开始,查找第一个不在str中的字符出现的位置

        //比较函数
        int compare(const String &s2);
        int compare(const String &s2,size_t pos1,size_t n1);
        int compare(const String &s2,size_t pos1,size_t n1,size_t pos2,size_t n2);
            
        //修改函数
        String substr(size_t pos,size_t n) const;   //返回pos开始的n个字符组成的字符串
        String &insert(size_t p,const String &str);    //在p的位置插入字符串str
        String &erase(size_t p,size_t n);                  //删除从p开始的n个字符,返回修改后的字符串
        String &assign(String &s2,size_t p,size_t n);   //将s中的字符串替换为s2中从p开始的n个字符
        String &replace(size_t p,size_t n,const char *s);  //删除从p开始的n个字符,然后插入串s
        void swap(String &s2);                      //减缓当前字符串与s2的值
        String &append(const char *s);              //把字符串s连接到当前字符串结尾
        void push_back(char c);                     //将字符c加入当前字符串尾部
        void pop_back(char c);                      //将字符C加入当前字符串头部


        //清除函数
        void clear();        //清楚字符串所有内容


        //析构函数
        ~String();

        //迭代器操作
        iterator begin() const{
            return iterator(this,0);
        }
        iterator end() const{
            return iterator(this,length);
        }
        //引用操作
        char &front() const{
            return (this->data)[0];
        }  
        char &back() const{
            return (this->data)[length-1];
        }


        //迭代器类
        class iterator{
            public:
                //迭代器构造函数
                iterator() {
                    it = NULL;
                }
                iterator(const iterator &its) {
                        it = its.it;
                        index = its.index;
                }
                iterator(const String *str) {
                    it = str;
                    index = 0;
                }
                iterator(const String *str,size_t num) {
                    if(num < 0) {
                        it = NULL;
                        index = 0;
                    }
                    else {
                        it = str;
                        index = num;
                    }
                }
                
                char operator*() {
                    cout << "1" << endl;
                    return *(it->data+index);
                }

                //迭代器加法
                iterator operator+(int num) {
                    if(!it)
                        return iterator();
                    return iterator(it,index+num);
                }
                //迭代器减法
                iterator operator-(int num) {
                    if(!it)
                        return iterator();
                    return iterator(it,index-num);
                }
                //迭代器与迭代器减法
                int operator-(iterator &end) {
                    //判断是否指向同一对象
                    if(this->it != end.it)
                        return -1; 
                    else {
                        return this->index - end.index;
                    }
                }

                iterator &operator=(iterator &its) {
                    it = its.it;
                    index = its.index;
                    return *this;
                } 
                //迭代器相等操作
                bool operator==(iterator &its) {
                    return this->it == its.it && this->index == its.index;
                }
                bool operator!=(iterator &its) {
                    return !(*this == its);
                }
                //前置递增
                iterator &operator++() {
                    if(index+1 > it->size()) {
                        cout << "无法递增,无效的迭代器" << endl;
                        exit(0);
                    }
                    else {
                        index += 1;
                    }
                    return *this;
                }
                //前置递减
                iterator &operator--() {
                    if(index-1 < 0) {
                        cout << "无法递减,无效的迭代器" << endl;
                        exit(0);
                    }
                    else {
                        index -= 1;
                    }
                    return *this;
                }
                //后置递增
                iterator operator++(int num) {
                    //保存当前迭代器状态
                    iterator its = *this;
                    ++(*this);
                    return its;
                }
                //后置递减
                iterator operator--(int num) {
                    //保存当前迭代器状态
                    iterator its = *this;
                    --(*this);
                    return its;
                }
                
                //小于大于
                bool operator<(iterator &its) {
                    //判断是否指向同一String对象
                    if(this->it != its.it) {
                        cout << "指向不同对象的迭代器不能互相比较" << endl;
                        exit(0);
                    }
                    return this->index < its.index;
                }
                bool operator<=(iterator &its) {
                    //判断是否指向同一String对象
                     if(this->it != its.it) {
                        cout << "指向不同对象的迭代器不能互相比较" << endl;
                        exit(0);
                    }
                    return this->index <= its.index;
                }
                bool operator>(iterator &its) {
                    return !(*this < its);
                }
                bool operator>=(iterator &its) {
                    return !(*this <= its);
                }

                //累加累减
                iterator &operator+=(int num) {
                    if(this->index+num > this->it->size()) {
                        cout << "无法增长，无效的迭代器" << endl;
                        exit(0);
                    }
                    this->index += num;
                    return *this;
                }  
                iterator &operator-=(int num) {
                    if(this->index-num < 0) {
                        cout << "无法减少，无效的迭代器" << endl;
                        exit(0);
                    }
                    this->index -= num;
                    return *this;
                }
                
                //迭代器析构函数
                ~iterator() {
                    it = NULL;
                }
            private:
                const String *it;
                size_t index;
        };
        
              

};

void String::clear()
{
    this->length = 0;
    delete(this->data);
}

String::~String()
{
    clear();
}

String::String() 
{
    data = NULL;
    length = 0;
}
String::String(size_t length,char ch)
{
    if(length <= 0) {
        data = NULL;
        length = 0;
        return;
    }
    this->length = length;
    data = new char[length+1];
    for(size_t i = 0;i < length;++i)
        data[i] = ch;
    data[length] = '\0';
}
String::String(const char *str)
{
    if(!str) {
        data = NULL;
        length = 0;
        return;
    }
    else {
        this->length = strlen(str);
        data = new char[this->length+1];
        strcpy(data,str);
        data[length] = '\0';
    }
}
String::String(const char *str,size_t length)
{
    if(!str) {
        data = NULL;
        this->length = 0;
        return;
    }

    if(length > strlen(str)) {
        this->length = strlen(str);
        data = new char[this->length+1];
        strcpy(data,str);
        data[length] = '\0';
  
    }
    else{
        this->length = length;
        data = new char[length+1]; 
        for(size_t i = 0;i < length;++i)
            data[i] = str[i];
        data[length] = '\0';
    }
    
}

String::String(String const &str)
{
    if(str.size() == 0) {
        data = NULL;
        this->length = 0;
        return;
    }
    else {
        this->length = str.size();
        data = new char[str.size()+1];
        strcpy(data,str.c_str());
        data[str.size()] = '\0';
    }
}

String::String(String &str,size_t index,size_t length)
{
    if(str.size() == 0 || index < 0) {
        data = NULL;
        this->length = 0;
        return;
    }

    if(length + index > str.size()) {
        this->length = length;
        data = new char[str.size()+1];
        strcpy(data,str.c_str());
        data[str.size()] = '\0';
    }
    else {
        this->length = length;
        data = new char[length+1];
        for(size_t i = index,j = 0;j < length;++i,++j)
            data[j] = str.c_str()[i];
        data[length] = '\0';
    }
}

String::String(iterator begin,iterator end)
{
    //判断是否指向同一对象并且迭代器范围是否有误
    if(end - begin < 0) {
        cout << "length=" << end - begin << endl;
        cout << "无效的迭代器" << endl;
        exit(0);
    } 
    else {
        data = new char[end - begin+1];
        size_t i = 0;
        while(begin != end) {
            data[i++] = *begin++;
        }
        data[i] = '\0';
    }
}
char String::operator[](int num)
{
    return c_str()[num];
}

bool String::operator==(String &s2)
{
    if(this->length != s2.size())
    return false;
    for(size_t i = 0;i < this->length;++i) {
        if(data[i] != s2.c_str()[i])
            return false;
    }
    return true;
}  

bool String::operator<(String &s2) 
{
    size_t n = 0;
    while(n < this->length && n < s2.size()) {
        if(this->c_str()[n] != s2.c_str()[n])
            return this->c_str()[n] < s2.c_str()[n];
        n++;
    }
    if(n == this->length && n == s2.size())
        return false;
    else if(n == s2.size())
        return false;
    else
        return true;
}

bool String::operator<=(String &s2) 
{
    size_t n = 0;
    while(n < this->length && n < s2.size()) {
        if(this->c_str()[n] != s2.c_str()[n])
            return this->c_str()[n] < s2.c_str()[n];
        n++;
    }
    if(n == this->length && n == s2.size())
        return true;
    else if(n == s2.size())
        return false;
    else
        return true;
}
bool String::operator>(String &s2) 
{
    return !(*this < s2); 
}
bool String::operator>=(String &s2) 
{
    return !(*this <= s2);
}

bool String::operator!=(String &s2) 
{
    return !(*this == s2);
}

String String::operator+(String &s2)
{
    
    long l = this->length + s2.size();
    char ar[l];

    strcpy(ar,this->c_str());
    strcat(ar,s2.c_str());

    String temp2(ar);
    return temp2;
    
}
String String::operator+(const char *str) 
{
    String s2(str);
    long l = this->length + s2.size();
    char ar[l];

    strcpy(ar,this->c_str());
    strcat(ar,s2.c_str());

    String temp2(ar);
    return temp2;

} 

String &String::operator=(const char *str) 
{
    //检查字符串是否有效
    if(!str) {
        String(); 
    }
    //检查当前String类是否有数据
    if(this->length > 0) {
        delete(this->data);
    }
    this->length = strlen(str);
    data = new char[strlen(str)+1];
    strcpy(data,str);;
    data[this->length] = '\0';
    return *this;
}

String &String::operator=(const String &s2)
{
    return *this = s2.c_str();
}

   
char * String::c_str() const
{
    return this->data;
}
size_t String::size() const
{
    return this->length;
}   

ostream& operator<<(ostream &os,const String &str)
{
    if(str.size() == 0) {
        
    }
    else {
        os << str.c_str();
    }
    return os;
}
istream& operator>>(istream &is,String &str)
{
    if(str.size()) {
        //删除原有内存空间
        delete(str.data);        
    }
    char buf[100];
    cin >> buf;
    str.data = new char[strlen(buf)+1];
    strcpy(str.data,buf);
    str.length = strlen(buf);
    str.data[str.length] = strlen(buf);
    return is;
}
bool String::empty() const
{
    return this->length == 0;
}

void String::resize(size_t len,char c)
{
    if(this->length < len) {
        char buf[len];
        strcpy(buf,this->data);
        delete(this->data);
        data = new char[len+1];
        strcpy(this->data,buf);
        for(size_t i = this->length;i < len;++i)
            data[i] = c;
        this->length = len;
        this->data[len] = '\0';
    }
    else {
        char buf[len];
        for(size_t i = 0;i < len;++i)
            buf[i] = this->data[i];
        delete(this->data);
        this->data = new char[len+1];
        strcpy(this->data,buf);
        this->data[len] = '\0';
    }
}

size_t String::find( const char *str, size_t index,size_t length)
{
    size_t l = length;
    String cmp(str);

    for(size_t i = index;i < this->length - l;++i) {
        String temp(*this,i,l);
        if(temp == cmp)
            return i;
    }
    return npos;
}

size_t String::find(const String &str,size_t index,size_t length)
{
    return find(str.c_str(),index,length);
}

size_t String::find( const char *str, size_t index)
{
    return find(str,index,strlen(str));
}

size_t String::find(const String &str,size_t index)
{
    return find(str.c_str(),index,str.size());
}

size_t String::find( char ch, size_t index )
{
    for(size_t i = index;i < this->length;++i)
        if(ch == (*this)[i])
            return i;
    return npos;
}

size_t String::find_first_of(String &str,size_t index)
{
     
    for(size_t i = index;i < this->length;++i)
        if(str.find((*this)[i],0) != npos)
            return i;
    return npos;
}

size_t String::find_first_of(const char *str,size_t index)
{
    String s(str);
    return find_first_of(s,index);
}

size_t String::rfind(String &str,size_t index,size_t length)
{
    size_t temp = npos;
    size_t num;
    while(index < this->length) {
        if((num = find(str,index,length)) != npos)
            temp = num;
        index++;
    }
    return temp;
}

size_t String::rfind(String &str,size_t index)
{
    return rfind(str,index,str.size());
}

size_t String::rfind( char ch, size_t index )
{
    size_t temp = npos;
    size_t num;
    while(index < this->length) {
        if((num = find(ch,index)) != npos)
            temp = num;
        index++;
    }
    return temp;
}

size_t String::rfind(const char *str,size_t index)
{
    String temp(str);
    return rfind(temp,index);
}

size_t String::find_last_of(String &str,size_t index)
{
    for(size_t i = index;i < this->length;++i) 
        if(str.find((*this)[i],0) == npos)
            return i;
    return npos;
}

int String::compare(const String &s2)
{
    return strcmp(this->data,s2.c_str());
}

int String::compare(const String &s2,size_t pos1,size_t n1,size_t pos2,size_t n2)
{
    String t1 = this->substr(pos1,n1);
    String t2 = s2.substr(pos2,n2);
    return strcmp(t1.c_str(),t2.c_str());
}

String String::substr(size_t pos,size_t n) const
{
    if(pos + n > this->length) {
        cout << "无效的长度" << endl;
        exit(0);
    } 
    char buf[n];
    char *temp = this->data+pos;
    strncpy(buf,temp,n);
    return String(buf,n);
}

String &String::insert(size_t p,const String &str)
{

    String s1 = str;
    String s2 = this->substr(p,this->length-p);
    
    String s3 = this->substr(0,p);

    *this = s3 + s1 + s2;
    return *this;
}

String &String::erase(size_t p,size_t n)
{
    if(p + n > this->length) {
        cout << "无效的范围" << endl;
        exit(0);
    } 
    String s1 = this->substr(0,p);
    String s2 = this->substr(p,n);
    String s3 = this->substr(p+n,this->length-p-n);

    *this = s1 + s3;
    return *this;
}

String &String::assign(String &s2,size_t p,size_t n)
{
    String temp = s2.substr(p,n); 
    *this = temp;
    return *this;
}
String &String::replace(size_t p,size_t n,const char *s)
{
    this->erase(p,n);
    this->insert(p,s);
    return *this;
}


void String::swap(String &s2)
{
    char *temp = this->c_str();
    this->data = s2.c_str();
    s2.data = temp;
}


String &String::append(const char *s)
{
    return this->insert(this->length,s);
}

void String::push_back(char c)
{
    char buf[this->length];
    strcpy(buf,this->data);
    delete(this->data);
    this->length++;
    this->data = new char[this->length+1];
    strcpy(this->data,buf);
    this->data[this->length-1] = c;
    this->data[this->length] = '\0';
}

void String::pop_back(char c)
{
    char buf[this->length];
    strcpy(buf,this->data);
    delete(this->data);
    this->length++;
    this->data = new char[this->length+1];
    this->data[0] = c;
    strcat(this->data,buf);
    this->data[this->length] = '\0';

}
String To_string(int n)
{
    char ar[5]; 
    sprintf(ar,"%d",n);
    return String(ar);
}
String To_string(double f)
{
    char ar[20];
    sprintf(ar,"%lf",f);
    return String(ar);
}
int main()
{
        

    String s1 = "123456";
    String s2 = "789";
    
    String *p = &s1;
    cout << *p << endl;

    return 0;
}

