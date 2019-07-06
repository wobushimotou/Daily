#!/usr/bin/env python
# coding=utf-8
#英制单位英寸和公制单位厘米互换
value = float(input('请输入长度:'))
unit = str(input('请输入单位:'))
if unit == 'in' or unit == '英寸':
    print('%f英寸=%f厘米'%(value,value*2.54))
elif unit == 'cm' or unit == '厘米':
    print('%f厘米=%f英寸'%(value,value/2.54))
else:
    print('请输入有效单位')

#掷骰子决定做什么
from random import randint

face = randint(1,6)
if face == 1:
    result = '唱'
elif face == 2:
    result = '跳'
elif face == 3:
    result = 'rap'
elif face == 4:
    result = '篮球'
elif face == 5:
    result = '基尼'
else:
    result = '太美'
print(result)

