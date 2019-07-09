#!/usr/bin/env python
# coding=utf-8
#定义类描述数字时钟
from time import sleep
import os
class Clock:
    def __init__(self,hour=0,minute=0,second=0):
        self.__hour = hour
        self.__minute = minute
        self.__second = second
    def run(self):
        self.__second += 1
        if(self.__second == 60):
            self.__minute += 1
            self.__second = 0
        if(self.__minute == 60):
            self.__hour += 1
            self.__minute = 0
        if(self.__hour == 24):
            self.hour = 0

    def show(self):
        return '%2d:%2d:%2d'%(self.__hour,self.__minute,self.__second)

def main():
    c = Clock()
    while True:
        print(c.show())
        sleep(1)
        os.system('clear')
        c.run()

if __name__ == '__main__':
    main()
