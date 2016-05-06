/*
 * 代码完成时间： 2014-12-04 17：53 PM
 * 2011年硕士研究生计算机入学考试 第42题
 * 一个长度为L的升序序列S，处在第L/2位置的数为中位数，现有两个等长序列A和B，求出A和B序列所包含的所有元素的中位数。
 * 该算法的时间复杂度为O(n)。
 * 算法核心思想：由于是两串有序序列合并，故中位数应该就是从小到大排序L位置上的数字，故用min保存当前较小数，temp保存较大数，每一轮都比出一个剩余数里最小的数，到第L个最小的数就是中位数。
 */

/**
 *
 * @author dainslef
 */
 
#include <iostream>

using namespace std;

int Median(int L, int *a, int *b)
{
	auto min = 0, temp = 0;
	if (a[L - 1] < b[0])
		return a[L - 1];
	else if (b[L - 1] < a[0])
		return b[L - 1];
	else
	{
		if (a[0] < b[0])
		{
			min = a[0];
			temp = b[0];
		}
		else
		{
			min = b[0];
			temp = a[0];
		}
		for (auto i = 0; i < L; i++)
		{
			if (a[i] < b[i])
			{
				if (temp < a[i])
				{
					min = temp;
					temp = a[i];
				}
				else
					min = a[i];
			}
			else
			{
				if (temp < b[i])
				{
					min = temp;
					temp = b[i];
				}
				else
					min = b[i];
			}
		}
		return min;
	}
}

int main(void)
{
	int L;
	cout << "请输入序列的长度： ";
	cin >> L;
	int a[L], b[L];
	cout << "请从小到大依次输入序列A的内容：" << endl;
	for (auto &i : a)
		cin >> i;
	cout << "请输从小到大依次入序列B的内容：" << endl;
	for (auto &i : b)
		cin >> i;
	cout << "中位数是： " << Median(L, a, b) << endl;
	return 0;
}

