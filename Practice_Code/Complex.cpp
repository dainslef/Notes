/*
 * 代码完成时间： 2014-11-8 16：48 PM
 * C++语言程序设计 4-20
 * 定义一个复数类，计算结果。 
 */

/**
 *
 * @author dainslef
 */

#include <iostream>
#include <sstream>

using namespace std;

class Complex
{
public:
	Complex(float a, float b) 
	{
		this->a = a;
		this->b = b;
	}
	Complex(float a) : a(a) {}	
	void add(Complex &complex)
	{
		auto sum = a + complex.a;
		stringstream ss;
		//ostringstream ss;
		ss << sum << " + " << b << "i";
		c = ss.str();
	}	
	void show()
	{
		cout << c << endl;
	}
private:
	int a, b;
	string c;
};

int main(int argc, char *argv[])
{
	Complex c1(3, 5);
	Complex c2 = 4.5;	//在c++中,此语句的作用等价于 Complex c2(4.5)
	c1.add(c2);
	c1.show();
	return 0;
}
