#include <iostream>
#include <vector>
#include <deque>
using namespace std;
struct Node{
    long n;
    long l;
    Node(long _n,long _l):n(_n),l(_l){}
};

long Min = 0xffffffff;
deque<Node> deq;

void Add(deque<Node> &deq,long n,long l,long s) {
    for(auto p = deq.begin();p != deq.end();++p)
        if(p->n == n) {
            if(p->l <= l)
                return;
        }

    deq.push_back({n,l});

    if(n >= s-2 && Min > l)
        Min = l;
}

void f(vector<int>& vec,long size) {
    long s = vec.size();
    Node n(0,0);
    Node n2(size,0);
    Node n3(size*2,0);
    deq.push_back(n);
    deq.push_back(n2);
    deq.push_back(n3);

    while(deq.size() > 0) {
        auto p = deq.begin();
        if(p->n < s-3) {
            long ar[3] = {0xffffffff,0xffffffff,0xffffffff};
            for(long i = 1;i <= 3;++i) {
                long g = p->n%size;

                long t = p->n + (i-1-g)*size+1;
                long l = p->l+abs(vec[t]-vec[p->n]);
                
                if(l < ar[2]) {
                    ar[0] = t;
                    ar[1] = l;
                    ar[2] = l;
                }
            }

            cout << ar[0] << ":" << ar[1] << endl;
            Add(deq,ar[0],ar[1],s);

        }
        deq.pop_front();
    }
}
int main()
{
    long size;
    vector<int> vec;

    /* cin >> size; */
    /* vec.resize(size*3); */
    /* long num; */
    /* for(int i = 0;i < size*3;++i) { */
    /*     cin >> num; */
    /*     vec[i] = num; */
    /* } */

    vec = {5,9,5,4,4,
        4,7,4,10,3,
        2,10,9,2,3};

    size = 5;

    f(vec,size);
    cout << Min  << endl;

    return 0;
}

