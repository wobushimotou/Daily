#!/usr/bin/env python
# coding=utf-8
# 寻找水仙花数
for n in range(100,201):
    unit = int(n%10)
    decade = int((n/10)%10)
    hundred = int(n/100)
    if(n == unit**3+decade**3+hundred**3):
        print('%d是水仙花数'%(n))

# 完全数
for n in range(1,101):
    sum = int(0)
    for i in range(1,n):
        if n%i == 0:
            sum += i
    if sum == n:
        print('%d是完全数'%(n))

# 斐波那契数列
f1 = int(1)
f2 = int(1)
print(f1,f2,sep=' ',end=' ')
for i in range (1,21):
    f2 = f1 + f2
    f1 = f2 - f1
    print(f2,end = ' ')

