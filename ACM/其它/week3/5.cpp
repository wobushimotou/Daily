/*
 *  查看商品问题,输入偏移量，还需看的数量，列表１总数量，列表２总数量
 *  得出之后看的列表１的开始和结束区间,列表２的开始和结束区间
 *
 *
 * */
#include <iostream>

using namespace std;
int main()
{
    int offset,num,v1,v2;
    cin >> offset >> num >> v1 >> v2;
    int l1,r1,l2,r2;
    if(offset > v1) {
        l1 = v1;
        r1 = v1;
        if(offset-v1 > v2) {
            l2 = v2;
            r2 = v2;
        }
        else {
            l2 = offset-v1;
            if(v2 - l2 > num) {
                r2 = l2 + num;
            }
            else {
                r2 = v2;
            }
        }
    }
    else {
        l1 = offset;
        if(num + l1 > v1) {
            r1 = v1;
            l2 = 0;
            r2 = num+l1 - v1;
        }
        else {
            r1 = offset+num;
            l2 = 0;
            r2 = 0;
        }

    }
    cout << l1 <<" "<< r1 <<" "<< l2 <<" "<< r2 << endl;
    return 0;
}

