#include <vector>
#include <ctime>
#include <thread>
#include <unistd.h>

#define SIZE_INT 4
#define SIZE_CHAR 1
using namespace std;

char GetRandChar(void) {

    unsigned int c = clock();
    usleep(1);
    int n = rand_r(&c)%26;
    int k = rand_r(&c)%2;
    if(k == 0)
        return 'a'+n;
    else
        return 'A'+n;
}


int GetRandInt(int k) {

    unsigned int c = clock();
    usleep(1);
    int n = rand_r(&c)%k;
    return n;
}


void GetRandVec(vector<int> &vec,int size,int k) {
    vec.resize(size);
    for(int i = 0;i != size;++i) {
        vec[i] = GetRandInt(k);
    }
}


void GetRandVec(vector<string> &vec,int size,int k) {
    unsigned int c = clock();
    vec.resize(size);
    for(int i = 0;i != size;++i) {
        int _length = 1+rand_r(&c)%(k-1);
        for(int j = 0;j != _length;++j) {
            vec[i].push_back(GetRandChar());
        }
    }
}

