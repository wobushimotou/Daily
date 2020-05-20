#include <iostream>
#include <vector>
#include <algorithm>

struct Point{
    int x;
    int y;
    bool operator<(const Point &r) {
        if(x < r.x)
            return true;
        else if(x > r.x){
            return false;
        }
        else {
            if(y < r.y)
                return true;
            else
                return false;
        }
    }
};



int main()
{
    int x = 0;
    int y = 0;
    std::vector<Point> vec;
    while(std::cin >> x >> y) {
        Point p;
        p.x = x;
        p.y = y;
        vec.push_back(p);
    }
    
    std::sort(vec.begin(),vec.end());

    for(auto &e : vec)
        std::cout << e.x << " " << e.y << std::endl;

    return 0;
}

