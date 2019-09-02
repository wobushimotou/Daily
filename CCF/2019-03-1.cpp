#include <iostream>
#include <vector>
#include <iomanip>
using namespace std;
int main()
{   
    int n;
    cin >> n;
    vector<double> ar;
    
    for(int i = 0;i != n;++i) {
        double num;
        cin >> num;
        ar.push_back(num);
    }

    double Min,Max,Middle;
    Min = Max = ar[0];
    for(auto e:ar) {
        if(e < Min) {
            Min = e;
        }
        if(e > Max) {
            Max = e;
        }
    }
    if(ar.size()%2 == 0) {
        Middle = (ar[ar.size()/2-1] + ar[ar.size()/2])/2;
    }
    else
        Middle = ar[ar.size()/2];
    cout << Max << " ";
    cout << setprecision(2) << Middle << " ";
    cout << Min << endl;
    return 0;
}

