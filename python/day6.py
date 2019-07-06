#!/usr/bin/env python
# coding=utf-8
# 求最大公约数和最小公倍数
def gcd(x,y):
    (x,y) = (y,x) if x > y else (x,y)
    for f in range(x,0,-1):
        if x%f == 0 and y%f == 0:
            return f

def lcm(x,y):
    if x%y == 0 or y%x == 0:
        return x if x>y else y
    return x*y

def main():
    if True:
        def f():
            global a
            a = 200
    else:
        def f(x):
            global a
            a = x
    f()
    print(a)

if __name__ == '__main__':
    main()
