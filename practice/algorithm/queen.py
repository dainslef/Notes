'''
	代码完成时间： 2014-12-19 01:38 AM
	单数组方式实现八皇后问题
	采用python3语言实现
	@author dainslef
'''

#! /usr/bin/python3

QUEEN_SIZE = 8

count = 0
chessBoard = list(range(QUEEN_SIZE))        # Python3中range()函数返回的是迭代对象，需要显式地进行类型转换才能得到列表

def show():
    for i in range(QUEEN_SIZE):
        for p in range(QUEEN_SIZE):
            chessBoard[i] == p and print("X ", end = " ") or print("_ ", end = " ")
            if p == QUEEN_SIZE - 1:
                print()

def find(row, line):
    for i in range(row):
        if chessBoard[i] == line or abs(chessBoard[i] - line) == abs(i - row):
            return False
    return True

def queen(row):
    if row == QUEEN_SIZE:
        global count        # 使用global关键字声明全局变量
        count += 1
        print("\n找到了第" + str(count) + "种解法：")
        show()
    else:
        for i in range(QUEEN_SIZE):
            if find(row, i):
                chessBoard[row] = i
                queen(row + 1)

queen(0)
print("\n共有{0}种解法。".format(count))