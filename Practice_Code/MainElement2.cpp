/*
 * 代码完成时间： 2014-11-25 01：48 AM
 * 2013年硕士研究生计算机入学考试 第41题
 * 设一个数组，数组中重复出现次数超过数组半数的元素称为主元素，找出数组中的主元素作为函数返回值，不存在主元素时返回值-1
 * 标准答案的第二种做法，时间复杂度为O(n)，空间复杂度为O(n)，是一种用空间换时间的做法。
 * 此种算法中引入了一个辅助数组，用于存储原数组中的各个元素出现的次数，然后将出现次数最多的元素记录下来。
 */

/**
 *
 * @author dainslef
 */

#include <iostream>

using namespace std;

int count(int num, int *a)
{
	auto max = 0;
	for (auto i = 0; i < num; i++)
		if (a[i] > max)
			max = a[i];		//找出最大的元素
	auto *p = new int[max];		//创建辅助数组，分配的空间要能装下a中最大的元素
	for (auto i = 0; i < max; i++)
		p[i] = 0;		//初始化数组
	auto temp = 0, now = 0; 		//定义now用来保存上一轮中出现最多的次数的元素的位置，用temp表示该元素的出现次数
	for (auto i = 0; i < num; i++)
	{
		p[a[i]]++;
		if (p[a[i]] > temp)
		{
			temp = p[a[i]];
			now = i;
		}
	}
	delete[] p;		//释放指针指向的内存区域
	if (temp > num / 2)
		return a[now];
	else
		return -1;
}

int main()
{
	int size;
	cout << "请输入数组的长度" << endl;
	cin >> size;
	auto avg = size / 2;
	int a[size];
	cout << "请依次输入数组的元素：" << endl;
	for (auto &i : a)
		cin >> i;
	cout << "您输入的数组内容为： ";
	for (auto i : a)
		cout << i << " ";
	cout << endl;
	if (count(size, a) == -1)
		cout << "该数组没有主元素！" << endl;
	else
		cout << "数组中存在主元素！主元素为： " << count(size, a) << endl;
	return 0;
}
