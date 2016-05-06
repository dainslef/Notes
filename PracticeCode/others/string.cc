/*
 * 代码完成时间： 2015-06-19 20：44 PM
 * 自行实现String类，模仿std::string的构造函数以及重载等号运算符。
 */

/**
 *
 * @author dainslef
 */

#include <iostream>
#include <string.h>

using namespace std;

class String
{
public:
	String(const char* = "");
	String(const String&);
	String& operator=(const String&);
	String& operator=(const char*);
	~String();
	char* const& operator*();

private:
	char *str;			//用于保存字符数据
};

String::String(const char *str)
{
	cout << "使用构造函数：String(const char*)" << endl;
	this->str = new char[strlen(str)];
	for (int i = 0; str[i] != '\0'; i++)
		this->str[i] = str[i];
}

String::String(const String &str)
{
	cout << "使用构造函数：String(const String&)" << endl;
	this->str = new char[strlen(str.str)];		//私有成员能在所属类内被访问，即使不是同一实例。
	for (int i = 0; str.str[i] != '\0'; i++)
		this->str[i] = str.str[i];
}

String::~String()
{
	cout << "clear!" << endl;
	delete[] str;
}

String& String::operator=(const String &str)
{
	delete[] this->str;		//给str分配新的内存之前删除旧的，避免内存泄漏。
	this->str = new char[strlen(str.str)];
	for (int i = 0; str.str[i] != '\0'; i++)
		this->str[i] = str.str[i];
	return *this;
}

String& String::operator=(const char *str)
{
	delete[] this->str;		//删除数组指针要用delete[]操作符而不是delete
	this->str = new char[strlen(str)];
	for (int i = 0; str[i] != '\0'; i++)
		this->str[i] = str[i];
	return *this;
}

char* const& String::operator*()
{
	return str;
}

int main(void)
{
	String str("test");
	String str1;
	String str2 = str;
	cout << "str内容：" << *str << endl;
	cout << "str1内容：" << *str1 << endl;
	cout << "str3内容：" << *str2 << endl;
	str1 = str;
	cout << "str1 = str;\nstr1内容：" << *str1 << endl;
	str = "test1";
	cout << "str1 = \"test1\";\nstr内容：" << *str1 << endl;
	str1 = "test2";
	cout << "str1 = \"test2\";\nstr1内容：" << *str1 << endl;
	
	string sys_str("test");
	string sys_str1;
	string sys_str2 = sys_str;
	cout << "sys_str内容：" << sys_str << endl;
	cout << "sys_str1内容：" << sys_str1 << endl;
	cout << "sys_str2容：" << sys_str2 << endl;
	sys_str1 = sys_str;
	cout << "sys_str1 = sys_str;\nsys_str1内容：" << sys_str1 << endl;
	sys_str = "test1";
	cout << "sys_str = \"test1\";\nsys_str1内容：" << sys_str1 << endl;

	return 0;
}
