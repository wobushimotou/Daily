#include <iostream>
#include <algorithm>
#include <vector>
#include <stack>
#include <deque>
#include <map>
#include <set>
using namespace std;

struct Node{
    Node() : x(0),y(0),k(0){}
    Node(int _x,int _y,int _k):x(_x),y(_y),k(_k){  }
    int x;
    int y;
    int k;
    bool operator<(const Node &p)const {
        return x < p.x;
    }
    bool operator==(const Node &p)const {
        return p.x == x && p.y == y && p.k == k;
    }
};

int shortestPath(vector<vector<int>>& grid, int k) {
    vector<vector<int>> vec = {{0,1},{0,-1},{1,0},{-1,0}};
    int w = grid.size();
    int l = grid.at(0).size();

    int arr[100][100];
    for(int i = 0;i != 100;++i)
        for(int j = 0;j != 100;++j)
            arr[i][j] = -1;
    if(k >= w+l-3)
        return w+l-2;

    int step = 0;
    deque<Node> stk;
    set<Node> sst;

    Node temp;
    stk.push_back(temp);
    while(stk.size()) {
        int n = stk.size();
        for(int i = 0;i != n;++i) {
            temp = stk.front();
            stk.pop_front();

            if(temp.x == w-1 && temp.y == l-1)
                return step;

            for(auto &e:vec) {
                int nx = temp.x + e[0];
                int ny = temp.y + e[1];
                if(nx >= 0 && nx < w && ny >= 0 && ny < l) {
                    int nk = (grid[nx][ny])?(temp.k+1):temp.k;
                    Node t(nx,ny,nk);
                    if(nk <= k && (arr[nx][ny] == -1 || nk <= arr[nx][ny] )){
                        stk.push_back(t);
                        arr[nx][ny] = nk;
                    }
                }
            }
        }
        step++;
    }

    return -1;
}

int main()
{
    vector<vector<int>> grid;
    int k;
    grid = {{0,0,0},{1,1,0},{0,0,0},{0,1,1},{0,0,0}};

    k = 1;
    cout << shortestPath(grid,k) << endl;    
    return 0;
}

