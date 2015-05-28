/*
 * 代码完成时间： 2014-12-19 01:38 AM
 * 单数组方式实现八皇后问题
 * 标准c语言实现
 */

/**
 *
 * @author dainslef
 */

#include <stdio.h>
#include <stdlib.h>
#define queen 8

int count = 0;
int Map[queen] = {0};		//用数组Map来记录每一行皇后的位置，Map[1] = 2表示皇后的位置在第1行的第2个位置。

void show()		//打印找到的解法
{
	for (int i = 0; i < queen; i++)
		for (int p = 0; p < queen; p++)
		{
			p == Map[i] ? printf("X  ") : printf("_  ");
			if (p == queen - 1)		//每行结束要输出换行符，表示换行
				printf("\n");
		}
}

int find(int row, int line)		//判断给定的位置是否为安全位置
{
	for (int i = 0; i < row; i++)		//从第0行开始遍历到当前行
		if (Map[i] == line || abs(Map[i] - line) == abs(i - row))		//找到每一行的皇后位置。因为采用递归的方式按行摆放，故需要考虑的情况只有:1.该位置的纵向上已经有棋子(横向不用考虑)。2.该位置的斜向上已经有棋子，斜率为1或是-1都表示该位置不可摆放棋子
			return 1;		//出现问题返回1
	
	return 0;		//没有危险返回0
}

void Queen(int row)
{
	if (row == queen)		//递归退出条件，表示8个皇后已经拜放完毕，此时可以将统计方法总数的计数器加1
	{
		count++;
		printf("找到了第%d种解法：\n", count);
		show();
	}
	else
	{
		for (int i = 0; i < queen; i++)
			if (!find(row, i))		//测试(row, i)位置是否可以摆放
			{
				Map[row] = i;
				Queen(row + 1);
			}
	}
}

int main(void)
{
	Queen(0);
	printf("\n共找到了%d种算法。\n", count);
	return 0;
}