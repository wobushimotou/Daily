#include <iostream>
#include <vector>
#include <map>
#include <stack>

using namespace std;

struct Node{
    Node() : x(0),y(0),k(0){}
    int x;
    int y;
    int k;
};
vector<vector<int>> vec = {{0,1},{0,-1},{1,0},{-1,0}};
int shortestPath(vector<vector<int>>& grid, int k) {
    int w = grid.size();
    int l = grid.at(0).size();

    if(k >= w+l-3) 
        return w+l-2;

    int step = 0;
    stack<Node> stk;
    Node temp;
    stk.push(temp);
    while(stk.size()) {
        int n = stk.size();
        for(int i = 0;i != n;++i) {
            temp = stk.top();
            stk.pop();
            
            if(temp.k > k)
                continue;
            if(temp.x == w-1 && temp.y == l-1)
                return step;

            for(auto &e:vec) {
                int nx = temp.x + e[0];
                int ny = temp.y + e[1];
                if(nx >= 0 && nx < w && nx >= 0 && ny < l) {
                    int nk = (grid[nx][ny])?(temp.k+1):temp.k;

                }
            }
        }
    }
}
int main()
{
    return 0;
}

