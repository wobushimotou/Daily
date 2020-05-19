#include <stdlib.h>
struct n_bit{
    unsigned char *bits;
    unsigned int idx;

};

struct n_bit func(n_bit num) {
    int len = 0;
    unsigned char *p = num.bits;
    //计算原长度
    while(p) {
        len++;
        p++;
    }

    struct n_bit ret;

    //申请空间
    ret.bits = (unsigned char *)malloc(len+num.idx);

    //按位反转
    for(unsigned int i = 0;i != len+num.idx;++i) {
        if(i < num.idx)
            ret.bits[i] = 1;
        else
            ret.bits[i] = (num.bits[i-num.idx]==1)?0:1;

    //计算偏移量
    int zero = 0;
    unsigned char *q = ret.bits;
    while(q) {
        if(*q != 0)
            break;
        zero++;
        q++;
    }

    
    unsigned char *f = (unsigned char *)malloc(len - zero);
    
    unsigned char *temp = f;
    //将按位反转得到的值存储在新空间
    while(q) {
        *temp = *q;
        temp++;
        q++;
    }
    
    //将新空间指针与原空间指针交换
    q = ret.bits;
    ret.bits = f;
    f = q;

    //释放旧空间
    free(f);

    ret.idx = zero;

    return ret;
}
