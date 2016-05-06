'''
	代码完成时间： 2014-12-19 01:38 AM
	单数组方式实现八皇后问题
	采用python3语言实现
	@author dainslef
'''

#! /usr/bin/python3

queen = 8
count = 0
Map = list(range(queen))        #python3中range()函数返回的是迭代对象，需要显式地进行类型转换才能得到列表

def show():
    for i in range(queen):
        for p in range(queen):
            Map[i] == p and print("X  ", end = " ") or print("_  ", end = " ")
            if p == queen - 1:
                print()

def find(row, line):
    for i in range(row):
        if Map[i] == line or abs(Map[i] - line) == abs(i - row):
            return False
    return True

def Queen(row):
    if row == queen:
        global count        #使用global关键字声明全局变量
        count += 1
        print("找到了第" + str(count) + "种解法：")
        show()
    else:
        for i in range(queen):
            if find(row, i):
                Map[row] = i
                Queen(row + 1)

Queen(0)
print("\n共有{0}种解法。".format(count))