#!/usr/bin/env python
# coding=utf-8
def main():
    for val in fib(20):
        print(val,end=' ')

def fib(n):
    a,b = 1,1
    for i in range(n):
        a,b = b,a+b
        yield a

if __name__ == '__main__':
    main()
