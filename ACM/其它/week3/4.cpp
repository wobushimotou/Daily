/*
 *  探险家走迷宫问题
 *
 *
 * */
#include <iostream>
#include <vector>
#include <deque>
#include <algorithm>
#include <stdlib.h>
using namespace std;
struct way{
    way(int _x,int _y,int _key,int _step) {
        x = _x;
        y = _y;
        keys.resize(_key);
        step = _step;
    }
    way(int _x,int _y,vector<char> _keys,int _step) {
        x = _x;
        y = _y;
        keys = _keys;
        step = _step;
    }
    int x;
    int y;
    vector<char> keys;  //所拥有的钥匙集合
    int step;
};

deque<way> Ways;
char ar[5][5];

bool IsKey(int x,int y) {
    if(ar[x][y] >= 'a' && ar[x][y] <= 'z')
        return true;
    return false;
}
bool IsWay(int x,int y) {
    if(ar[x][y] == '1' || ar[x][y] == '2' || ar[x][y] == '3' || IsKey(x,y))
        return true;
    return false;
}
bool IsDoor(int x,int y) {
   if(ar[x][y] >= 'A' && ar[x][y] <= 'Z')
       return true;
   return false;
}

vector<char> find_vec(int x,int y) {
    for(auto p = Ways.begin();p != Ways.end();++p) {
        if(p->x == x && p->y == y)
            return p->keys;
    }
    return {};
}

int Find() {
    int b[4][2] = {{-1,0},{0,-1},{1,0},{0,1}};
    while(true) {
        int _x = Ways.front().x;
        int _y = Ways.front().y;
        int step = Ways.front().step;
        char c = ar[_x][_y];
        if(c == '3')
            break;
        for(int i = 0;i < 4;++i) {
            if(IsWay(_x+b[i][0],_y+b[i][1])) {
                vector<char> vec = find_vec(_x,_y);
                if(IsKey(_x+b[i][0],_y+b[i][1])) {
                    vec.push_back(ar[_x+b[i][0]][_y+b[i][1]]);
                }
                Ways.push_back(way(_x+b[i][0],_y+b[i][1],vec,step+1));
            }
            if(IsDoor(_x+b[i][0],_y+b[i][1])) {
                vector<char> vec = find_vec(_x,_y);
                if(find(vec.begin(),vec.end(),ar[_x+b[i][0]][_y+b[i][1]]+32) != vec.end()) {
                    Ways.push_back(way(_x+b[i][0],_y+b[i][1],vec,step+1));
                }
            }
        }
        Ways.pop_front();
    }

    return Ways.front().step;
}
int main()
{
    int m,n;
    cin >> m >> n;
    char num;
    int begin_x;
    int begin_y;
    for(int i = 0;i < m;++i)
        for(int j = 0;j < n;++j) {
            cin >> num;
            ar[i][j] = num;
            if(num == '2') {
                begin_x = i;
                begin_y = j;
            }
        }
     
    Ways.push_back(way(begin_x,begin_y,0,0));
    cout << Find() << endl;

    return 0;
}

