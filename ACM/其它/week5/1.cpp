/*
 *  分糖果问题，每个人有分值，当比周围人分值大时则必须所分的糖果比他们多，每个人至少有一颗
 *
 * */
#include <iostream>
#include <vector>

using namespace std;
int main()
{
    vector<int> vec1;
    vector<int> vec2;
    int num;
    while(cin >> num) {
        vec1.push_back(num);
        vec2.push_back(1);
    }

    size_t Min = 0;
    for(size_t i = 0;i != vec1.size();++i) {
        if(vec1[i] < vec1[Min])
            Min = i;
    }

    for(size_t i = Min+1;i != vec1.size();++i) {
        if(vec1[i] > vec1[i-1])
            vec2[i] = vec2[i-1]+1;
        else
            vec2[i] = 1;
    }

    for(int i = Min-1;i >= 0;--i) {
        if(vec1[i] > vec1[i+1])
            vec2[i] = vec2[i+1]+1;
        else
            vec2[i] = 1;
    }

    for(auto p = vec2.begin();p != vec2.end();++p)
        cout << *p << " ";
    cout << endl;

    return 0;
}

