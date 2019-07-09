#!/usr/bin/env python
# coding=utf-8
#在屏幕上显示跑马灯文字
import os
import time
import random

def horse():
    content = '北京欢迎你为你开天辟地......'
    while True:
        #清理屏幕输出
        os.system('clear')
        print(content)
        #休眠200毫秒
        time.sleep(0.2)
        content = content[1:] + content[0]

#产生指定长度的验证码,验证码由大小写字母和数字组成
def IdentifyingCode(clen):
    all_chars = '0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ'    
    pos = len(all_chars)
    code = ''
    for i in range(clen):
        n = random.randint(0,pos)
        code += all_chars[n]
    return code

#返回给定文件的后缀名
def GetSuffix(filename):
    pos = filename.find('.')
    if pos > 0 and pos < len(filename)-1:
        return filename[pos+1:]
    else:
        return ''

#返回传入列表中最大和第二大的元素的值
def GetMax(l):
    l2 = sorted(l,reverse=True)
    return l2[0],l2[1]

from day2 import IsLeapYear
#计算指定的年月日是这一年的第几天
def WhichDay(year,month,day):
    day_of_month = [31,28,31,30,31,30,31,31,30,31,30,31]
    if(IsLeapYear(year)):
        day_of_month[1] += 1

    sum = 0;
    for i in range(0,month):
        if i == month-1:
            sum += day
            break
        sum += day_of_month[i]
    return sum

#打印杨辉三角
def Triangle(n):
    l = [[]] * n
    for i in range(0,n):
        l[i] = [None]*(i+1)
        for j in range(len(l[i])):
            if i == 0 or j == 0:
                l[i][j] = 1
            elif i == j:
                l[i][j] = 1
            else:
                l[i][j] = l[i-1][j] + l[i-1][j-1]
            print(l[i][j],end=' ')
        print()
        

def main():
    pass




if __name__ == '__main__':
    main()
