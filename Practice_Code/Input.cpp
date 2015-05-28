#include <iostream>
#include <sstream>
#include <vector>
#include <string.h>

using namespace std;

namespace myspace
{
	class A
	{
	public:
		A(const vector<int> &v) : num(0), sum(0), vt(v) {};
		int getAnswer(char **);
		int num;
	private:
		int sum;
		vector<int> vt;
	};
}

int main(int argc, char **argv)
{
	vector<int> v;
	//vector<int>::iterator it;
	
	if (argc == 1)		//如果没有输入参数则直接结束程序
	{
		cout << "请输入参数！" << endl;
		return 0;
	}
	
	for (auto i = 2; i < argc; ++i)
	{
		int num;
		stringstream ss(argv[i]);
		ss >> num;		//将字符串类型转化为整型。
		v.push_back(num);
	}

	auto str = argv[1];
	if (!strncmp(str, "--help", 6))
	{
		cout << "请在第一个参数中填入计算符号，后面的参数输入要计算的数字！" << endl;
		return 0;
	}

	myspace::A a(v);
	cout << "得到的计算结果为：" << a.getAnswer(argv) << endl;
	cout << "参与计算的数值个数：" << a.num << endl;
	return 0;
}

int myspace::A::getAnswer(char **argv)
{
	for (auto i = begin(vt); i != end(vt); ++i)
	{
		switch (argv[1][0])
		{
		case '+':
			sum += *i;		//i即为迭代器，由auto关键字类型推断得到。
			break;
		case '-':
			if (sum == 0)
				sum = *i;
			else
				sum -= *i;
			break;
		case '/':
			if (sum == 0)
				sum = *i;
			else
				sum /= *i;
			break;
		case '*':
			if (sum == 0)
				sum = *i;
			else
				sum *= *i;
			break;
		}
		num++;
	}
	return sum;
}
