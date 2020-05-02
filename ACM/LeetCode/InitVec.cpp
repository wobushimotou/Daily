#include <vector>
#include <algorithm>
#include <ctime>
#include <thread>
using namespace std;

void GetRandVec(vector<int> &vec,int size,int l,int r) {
    unsigned int c = clock();
    /* vec.resize(size); */
    for(int i = 0;i < size;++i) {
        int k = rand_r(&c)%(r-l);
        vec.push_back(l+k);
    }
}


