/*
 * 代码完成时间： 2014-11-25 01：48 AM
 * 2013年硕士研究生计算机入学考试 第41题
 * 设一个数组，数组中重复出现次数超过数组半数的元素称为主元素，找出数组中的主元素。
 * 时间复杂度为O(n^2)，循环嵌套循环的方式效率很不理想。
 */

/**
 *
 * @author dainslef
 */

#include <iostream>

using namespace std;

auto flag = false;		//定义一个标志，用于判断是否有主元素
int size;
int example;		//定义用于比较的模板元素

int count(int num, int *a)
{
	example = a[num];
	auto sum = 1;		//默认情况下，模板元素已经存在了一次
	for (auto i = num + 1; i < size; i++)
	{
		if (a[i] == example)
			sum++;		//从模板元素的下一个元素开始一直比到数组结束，如果有元素与模板元素相等，则重复次数加1
	}
	return sum;
}

int main()
{
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
	for (auto i = 0; i <= avg; i++)		//比较无需全部做完，只需要比前面一半的元素
	{
		if (count(i, a) > avg)
		{
			cout << "该数组中存在主元素，主元素的值为： " << example <<endl;
			flag = true;
			break;		//主元素只会存在一个，找到一个符合要求的即可结束循环
		}
	}
	if (flag == false)
		cout << "该数组没有主元素！" << endl;
	return 0;
}
