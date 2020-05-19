#include <iostream>
using namespace std;

bool Hav(int m,int n) {
    if(m%n == 0 || n%m == 0)
        return true;

    if(m%2 == 0 && n%2 == 0)
        return true;

    for(int i = 2;i <= min(m,n) && i <= max(m,n)/2;++i) {
        if(m%i == 0 && n%i == 0)
            return true;
    }
    return false;
}
int main()
{
    int n;
    cin >> n;
    int ar[n];
    for(int i = 0;i != n;++i)
        cin >> ar[i];

    for(int i = 0;i != n;++i)
        if(ar[i] == 1) {
            cout << "YES" << endl;        
            return 0;
        }

    if(n == 1) {
        cout << "NO" << endl;
        return 0;
    }

    for(int i = 0;i != n;++i)
        for(int j = i+1;j != n;++j) {
            if(!Hav(ar[i],ar[j])) {
                cout << "YES" << endl;
                return 0;
            }
        }
            
    cout << "NO" << endl;
    
    
    return 0;
}

