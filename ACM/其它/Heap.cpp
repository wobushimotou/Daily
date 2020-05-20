#include <iostream>
#include <vector>
using namespace std;
template <typename T>
class Heap{
    private:
        vector<T> vec;
        void shift_up(int i);
        void shift_down(int i);
    public:
        /* Heap(); */
        Heap(initializer_list<T> l);
        void Push(T &data);
        void Pop();
        T Top() {
            return vec[1];
        }
        bool empty() {
            return vec.size()-1;
        }
        void Print() {
            for(auto &e:vec)
                cout << e << " ";
            cout << endl;
        }
};

template <typename T>
Heap<T>::Heap(initializer_list<T> l) {
    vec.resize(l.size()+1);
    std::copy(l.begin(),l.end(),vec.begin()+1);

    int E = vec.size()-1;
    while(E >= 1) {
        if(2*E < vec.size()) {
            int N = 2*E;
            if(N+1 < vec.size() && vec[N+1] < vec[N])
                N++;

            if(vec[N] < vec[E])
                shift_down(E);
        }
        E--;
    }
}

template <typename T>
void Heap<T>::shift_up(int i) {
    while(i >= 2) {
        if(vec[i] < vec[i/2]) {
            swap(vec[i],vec[i/2]);
        }
        else
            break;
        i = i/2;
    }
}


template <typename T>
void Heap<T>::shift_down(int i) {
    int E;
    while(i < vec.size()) {
        E = i*2;
        if(E < vec.size()) {
            if(E+1 < vec.size() && vec[E+1] < vec[E]) 
                E++;

            if(vec[E] < vec[i]) {
                swap(vec[E],vec[i]);
            }

            i = E;
        }
        else
            break;
    }
}

template <typename T>
void Heap<T>::Push(T &data) {
    vec.push_back(data);
    shift_up(vec.size()-1);
}

template <typename T>
void Heap<T>::Pop() {
    swap(vec[1],vec[vec.size()-1]);
    vec.erase(vec.end()-1);
    shift_down(1);
}

template <typename T>
void head_sort(Heap<T> &heap) {

}

int main()
{
    Heap<int> heap = {2,7,3,4,5,1,6};

    int n = 0;

    /* while(cin >> n) { */
    /*     heap.Push(n); */
    /*     heap.Print(); */
    /* } */

    while(heap.empty()) {
        cout << heap.Top() << " ";
        /* heap.Print(); */
        heap.Pop();
    }
    cout << endl;
    return 0;
}

