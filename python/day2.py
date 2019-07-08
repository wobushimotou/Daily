#!/usr/bin/env python
# coding=utf-8
def main():
    #将华氏温度转化为摄氏温度
    f = float(input('输入华氏温度:'));
    print('%.1f华氏温度=%.1f摄氏温度'%(f,(f-32)/1.8))

    #输入圆的半径计算周长和面积
    import math
    redius = float(input('输入半径:'))
    print('半径为%.1f的圆的面积为:%.1f'%(redius,math.pi*redius**2))
    print('半径为%.1f的圆的周长为:%.1f'%(redius,math.pi*redius*2))

#输入年份判断是不是闰年
def IsLeapYear(year):
    return (year%100 != 0) and (year%4 == 0) or (year%400 == 0)

if __name__ == "__main__":
    main()
