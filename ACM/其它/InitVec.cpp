#include <vector>
#include <ctime>
#include <thread>
using namespace std;

void GetRandVec(vector<int> &vec,int size,int k) {
    unsigned int c = clock();
    vec.resize(size);
    for(int i = 0;i < size;++i) {
        vec[i] = rand_r(&c)%k;
    }
}


