#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <algorithm>
#include <numeric>
#include <map>
#include <set>


using namespace std;
class Quote{
private:
    string book;
protected:
    double price;
public:
    Quote() = default;
    Quote(double num,const string &name) : book(name),price(num) {}
    string isbn() const{ return book; }
    virtual double net_price(size_t n) const { return price*n; } 
    virtual string debug() const { return book+" "+to_string(price);}
};

class Bulk_quote : public Quote{
protected:
    size_t min_qty = 0;
    double discount = 0.0;
public:
    Bulk_quote() = default;
    Bulk_quote(double num,const string &name,size_t n,double dc) : Quote(num,name),min_qty(n),discount(dc) { }
    double net_price(size_t n) const override;
    string debug() const override { return Quote::debug()+" "+to_string(min_qty)+" "+to_string(discount); }
};

class Limit_quote : public Bulk_quote{
public:
    Limit_quote() = default;
    Limit_quote(double num,const string &name,size_t n,double dc) : Bulk_quote(num,name,n,dc){}
    double net_price(size_t n) const override;
    string debug() const override { return Bulk_quote::debug();}

};

double Bulk_quote::net_price(size_t n) const
{
    if(n >= min_qty)
        return n*(1-discount)*price;
    else
        return n*price;
}

double Limit_quote::net_price(size_t n) const
{
    if(n <= min_qty)
        return n*(1-discount)*price;
    else
        return n*price;
}

double print_total(ostream &os,const Quote &item,size_t n)
{
    double ret = item.net_price(n);
    os << "ISBN: " << item.isbn() << " #sold: " << n << " total due: " << ret << endl;
    return ret;
}

class Disc_quote : public Quote{
protected:
    size_t quantity = 0;
    double discount = 0.0;
public:
    Disc_quote() = default;
    Disc_quote(const string &book,double price,size_t qty,double dc) : Quote(price,book),quantity(qty),discount(dc) {  }
    double net_price(size_t n)const = 0;
};

class Bulk_quote2 : public Disc_quote{
public:
    Bulk_quote2() = default;
    Bulk_quote2(const string &book,double price,size_t qty,double dc) : Disc_quote(book,price,qty,dc) {  }
    double net_price(size_t n)const override;
};

double Bulk_quote2::net_price(size_t n)const
{
    if(n >= quantity)
        return n*(1-discount)*price;
    else
        return n*price;
}

class Base{
public:
    void pub_mem();
protected:
    int prot_mem();
private:
    char priv_mem();
};

class Pub_Derv : public Base{
    void memfcn(Base &b) { b = *this; }

};

class Priv_Derv : private Base{
    void memfcn(Base &b) { b = *this; }

};

class Prot_Derv : protected Base{
    void memfcn(Base &b) { b = *this; }

};

class Derived_from_Public : public Pub_Derv{
    void memfcn(Base &b) { b = *this; }

};

class Derived_from_Protected : public Prot_Derv{
    void memfcn(Base &b) { b = *this; }

};

class Derived_from_Private : public Priv_Derv{
    //void memfcn(Base &b) { Priv_Derv Pd = *this;b = Pd; }

};

int f(int a,Quote &b)
{
    return a + b.net_price(10);
}

int f2(int a,shared_ptr<Quote> &b)
{
    return a + b->net_price(10);
}

double Sum(vector<shared_ptr<Quote>> &vec)
{
    return accumulate(vec.begin(),vec.end(),0,f2);
}
bool compare(shared_ptr<Quote> &a,shared_ptr<Quote> &b)
{
    return a->isbn() < b->isbn();
}
int main()
{
    multiset<shared_ptr<Quote>,decltype(compare) *> items{compare};
    return 0;
}

