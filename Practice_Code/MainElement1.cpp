/*
 * 代码完成时间： 2014-11-25 01：48 AM
 * 2013年硕士研究生计算机入学考试 第41题
 * 设一个数组，数组中重复出现次数超过数组半数的元素称为主元素，找出数组中的主元素作为函数返回值，不存在主元素时返回值-1
 * 标准答案的做法时间复杂度为O(n)，空间复杂度为O(1)，效率最高。
 * 标准答案的算法思想是，由于主元素出现的次数一定大于数组的一半，因此设置计数器sum，在主元素出现时加1，未出现时减1，减到0就换另外的下个元素当example。如果存在主元素，则一定会有sum > 0，故只需要判断最后的example是否为主元素即可。
 */

/**
 *
 * @author dainslef
 */

#include <iostream>

using namespace std;

int count(int num, int *a)
{
	auto example = a[0];
	auto sum = 0;
	for (auto i = 0; i < num; i++)
		if (example == a[i])
			sum++;
		else if (sum > 0)
			sum--;
		else
		{
			example = a[i];
			sum = 1;
		}
	for (auto i = 0, sum = 0; i < num; i++)
		if (example == a[i])
			sum++;
	if (sum > num / 2)		//检测得到的结果是否满足条件
		return example;
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
