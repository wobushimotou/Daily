#include "Buddy.h"
Buddy::Buddy(int _size):size(_size),area(new Space[size])
{
    mm.resize(12);
}

Buddy::Buddy()
{
    Buddy(1024);
}

void Buddy::Init()
{
    Alloc(0,size);
}
void Buddy::Alloc(int address,int size) {
    int t = size;
    while(t) {
        int n = GetMaxBit(t);
        mm.at(NumToBitNum(n)).push_back(address);
        t -= n;
        address += n;
    }
}

Buddy::~Buddy()
{
    delete[] area.get();
}

int Buddy::GetMaxBit(int n)
{
    int t;
    int i = 1;
    while(i <= 1024) {
        if(n & i) {
            t = i;
        }
        i *= 2;
    }
    return t;
}

int Buddy::NumToBitNum(int t)
{
    int p = 0;
    while(t) {
        t /= 2;
        p++;
    }
    return p-1;
}

void Buddy::Display()
{
    int i,j,k;
    i = 0;
    j = 0;
    k = 1;
    for(auto p = mm.begin();p != mm.end();++p,++i,k *= 2) {
        cout << i << " :";
        if(p->size()) {
            for(auto m = p->begin();m != p->end();++m) {
                cout << *m << "~" << *m+k << " ";
            }
        }
        cout << endl;
    }
}

void *Buddy::Apply(int size) {
    //从不小于size的内存地址开始
    int i;
    for(i = 0;i != 12;++i) {
        if(pow(2,i) >= size) {
            for(auto p = mm.begin()+i;p != mm.end();++p) {
                if(p->size()) {//有空间可以用于分配
                    int q = *(p->begin());
                    p->erase(p->begin());

                    int surplus = pow(2,p-mm.begin()) - size;            
                    //将剩余空间分解插入到空闲链表上
                    if(surplus > 0) {
                        Alloc(q+size,surplus); 
                    }
                    return (void *)(area.get()+q);
                }
            }
            return NULL;
        }
    }
    return NULL;
}

void Buddy::Release(void *address,size_t size) {
    long t = (char *)address - (char *)area.get();
    Alloc(t,size);
}

