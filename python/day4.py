#!/usr/bin/env python
# coding=utf-8
# 猜数字游戏
import random

answer = random.randint(1,100)
counter = 0
while True:
    counter += 1
    number = int(input('请输入:'))
    if number < answer:
        print('小于')
    elif number == answer:
        print('猜对了')
        break
    else:
        print('大于')
print('你总共猜了%d次'%(counter))

