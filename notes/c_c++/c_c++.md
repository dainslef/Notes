<!-- TOC -->

- [内存区](#内存区)
- [C/C++中函数定义的区别](#cc中函数定义的区别)
- [C/C++中 static 关键字的区别](#cc中-static-关键字的区别)
	- [static (C)](#static-c)
	- [static (C++)](#static-c)
- [C/C++中 const 关键字的区别](#cc中-const-关键字的区别)
	- [const 变量初始化](#const-变量初始化)
	- [const 变量作为数组长度](#const-变量作为数组长度)
- [运算精度](#运算精度)
- [8进制与16进制](#8进制与16进制)
- [sizeof 运算符](#sizeof-运算符)
- [列表初始化](#列表初始化)
	- [数组初始化](#数组初始化)
	- [designated initializers (C99)](#designated-initializers-c99)
	- [二维数组初始化](#二维数组初始化)
	- [类/结构体列表初始化 (C++98)](#类结构体列表初始化-c98)
	- [统一初始化 (C++11)](#统一初始化-c11)
	- [std::initializer_list<T> (C++11)](#stdinitializer_listt-c11)
- [结构体对齐](#结构体对齐)
	- [指定结构体对齐大小](#指定结构体对齐大小)
- [变长参数](#变长参数)
	- [自定义变长参数函数](#自定义变长参数函数)
	- [通过地址获取变长参数内容](#通过地址获取变长参数内容)
	- [变长参数宏](#变长参数宏)
- [自增自减运算符的优先级](#自增自减运算符的优先级)
- [编译器自动生成的成员函数](#编译器自动生成的成员函数)
	- [控制默认生成的成员函数](#控制默认生成的成员函数)
- [继承](#继承)
- [指针运算](#指针运算)
	- [数组名的含义](#数组名的含义)
	- [指针数组与数组指针](#指针数组与数组指针)
- [C++对象模型](#c对象模型)
	- [成员函数](#成员函数)
	- [虚函数](#虚函数)
- [参数默认值](#参数默认值)
- [函数定义嵌套](#函数定义嵌套)
- [lvalue reference (左值引用) / rvalue reference (右值引用)](#lvalue-reference-左值引用--rvalue-reference-右值引用)
	- [rvalue reference (右值引用)](#rvalue-reference-右值引用)
	- [universal reference (通用引用)](#universal-reference-通用引用)
	- [reference collapsing (引用折叠)](#reference-collapsing-引用折叠)
	- [move semantics (移动语义)](#move-semantics-移动语义)
	- [std::move()](#stdmove)
	- [std::forward](#stdforward)
	- [注意事项](#注意事项)
	- [成员函数的引用限定](#成员函数的引用限定)
- [引用与指针](#引用与指针)
- [函数指针](#函数指针)
	- [成员指针](#成员指针)
- [template (模板)](#template-模板)
	- [模版编译](#模版编译)
	- [模版定义与声明分离](#模版定义与声明分离)
	- [模版的高级用法](#模版的高级用法)
	- [模版形参默认值](#模版形参默认值)
	- [模板与重载](#模板与重载)
	- [模版特化](#模版特化)
	- [模版递归](#模版递归)
	- [变长模版 (C++11)](#变长模版-c11)
	- [禁止特定类型的模板参数](#禁止特定类型的模板参数)
- [_Generic (C11)](#_generic-c11)
- [assert (断言)](#assert-断言)
	- [断言宏](#断言宏)
	- [静态断言 (C11)](#静态断言-c11)
	- [静态断言 (C++11)](#静态断言-c11)
- [auto 类型推导](#auto-类型推导)
	- [Lambda](#lambda)
	- [复用 Lambda](#复用-lambda)
	- [变量捕获](#变量捕获)
	- [C++14 中的 Lambda 新特性](#c14-中的-lambda-新特性)
- [STL 容器](#stl-容器)
	- [迭代器](#迭代器)
	- [序列式容器](#序列式容器)
	- [关联式容器](#关联式容器)
- [Smart Pointer (智能指针)](#smart-pointer-智能指针)
	- [智能指针的一般性用法](#智能指针的一般性用法)
	- [智能指针的转型](#智能指针的转型)
	- [改变做为形参传入的智能指针所指向的内容](#改变做为形参传入的智能指针所指向的内容)
- [std::bind()](#stdbind)
	- [bind() 绑定普通函数](#bind-绑定普通函数)
	- [bind() 绑定非静态成员函数](#bind-绑定非静态成员函数)
- [boost::signals2](#boostsignals2)
	- [定义信号](#定义信号)
	- [连接槽函数](#连接槽函数)
	- [取消连接](#取消连接)
	- [获取信号返回值](#获取信号返回值)
- [Boost 时间库](#boost-时间库)
	- [获取当前时间](#获取当前时间)
	- [获取时间间隔](#获取时间间隔)
- [std::chrono (标准时间库)](#stdchrono-标准时间库)
	- [std::chrono::duration](#stdchronoduration)
	- [std::time_point](#stdtime_point)
	- [时钟类型](#时钟类型)
	- [基本用法示例](#基本用法示例)
- [C/C++中一些编码中遇到的错误](#cc中一些编码中遇到的错误)
	- [multiple definition of](#multiple-definition-of)
	- [在 switch 的 case 语句中定义局部变量](#在-switch-的-case-语句中定义局部变量)
- [常用的C标准库函数](#常用的c标准库函数)
	- [memset()](#memset)
	- [memcpy()](#memcpy)
	- [strcpy() 函数](#strcpy-函数)
	- [setjmp() / longjmp()](#setjmp--longjmp)
	- [sigsetjmp() / siglongjmp()](#sigsetjmp--siglongjmp)
	- [getopt() / getopt_long()](#getopt--getopt_long)
- [一些关键字、特殊值的含义/用法](#一些关键字特殊值的含义用法)
	- [explicit 关键字](#explicit-关键字)
	- [restrict 关键字](#restrict-关键字)
	- [mutable 关键字](#mutable-关键字)
	- [using 关键字](#using-关键字)
	- [移位运算符](#移位运算符)
	- [npos 成员](#npos-成员)
- [常见错误](#常见错误)
	- [error: jump to case label](#error-jump-to-case-label)
	- [warning: `...` will be initialized after [-Wreorder] ...](#warning--will-be-initialized-after--wreorder-)

<!-- /TOC -->



# 内存区
C/C++中，内存分为5个区，分别是**堆区**，**栈区**，**静态区**，**文字常量区**，**程序代码区**。

| 名称 | 含义 |
| :- | :- |
| 栈区(stack) | 由编译器自动分配释放，存放函数的参数值，局部变量的值等。其操作方式类似于数据结构中的栈，地址由高到低。 |
| 堆区(heap) | 由`malloc`/`new`分配的空间，地址由低向高增长，需要程序员手动释放(`free`/`delete`)，否则程序结束时可能由OS回收。堆区与数据结构中的堆不同，分配方式类似于链表。 |
| 全局/静态变量区(static) | 全局变量和静态变量存储在此区域，已初始化的全局变量和静态变量在一块区域，未初始化的全局变量和未初始化的静态变量在相邻的另一块区域，程序结束后由系统释放。 |
| 文字常量区 | 常量字符串存放在此区域，程序结束后由系统释放。 |
| 程序代码区 | 存放函数体的二进制代码。 |

举例：

```c
int a = 0; //全局初始化区
char* p1; //全局未初始化区

int main()
{
	int b; //栈区
	char s[] = "abc"; //栈区
	char* p2; //栈区
	char* p3 = "123456"; //"123456"在常量区，p3在栈区
	static int c = 0; //全局/静态已初始化区
	p2 = (char*)malloc(10); //malloc分配得来得10字节的区域就在堆区
	strcpy(p1, "123456"); //"123456"放在常量区，编译器可能会将它与p3所指向的"123456"优化到一块区域
	return 0;
}
```



# C/C++中函数定义的区别
- 在C语言中，函数的定义中，参数**不能**只写参数类型而没有参数名。
- 在C++中，函数的定义里，参数**允许**只写参数类型而没有参数名。
- 在C语言中，`function()`参数表为空代表这个函数可以接收**任意个**参数， 而`function(void)`才代表函数不接收参数，
因此，对于任意参数的函数，都可以用空参数表的形式做函数声明(C语言不支持函数重载，一个函数名对应的函数实现只会有一个)。
- 在C++中，`function()`参数表为空与`function(void)`意义相同，都表示该函数**不接收任何参数**。
而且C++支持**函数重载**，一个函数名根据参数不同可以有多个实现，因此，在C++中函数声明必须与函数定义的原型**完全相同**。



# C/C++中 static 关键字的区别

## static (C)
- C语言中，`static`用在**函数/全局变量**前表示该**函数/全局变量**为当前文件的**内部函数/全局变量**，
只能在该文件中被访问，当前文件被其它源码`include`时该变量**不可访问**。
- `static`用在局部变量前，则成为**静态**局部变量，静态局部变量**不在**栈区分配内存而是在**全局变量区**中分配空间，
因此保存在静态局部变量中的值不会随着函数运行结束而被**自动释放**，下次执行该函数，
该函数内部的静态局部变量不会重新分配空间，因而而是依然使用上次函数执行结束时的值。

## static (C++)
在C++中，除了C语言中的用法之外，还可以用在类的成员前，表示**静态成员**，静态成员只能初始化一次，全局仅有一个实体。

- 静态成员不依赖于类的实例而存在，无需进行类实例化即可直接通过类名进行访问。
一个类的无论有多少个实例，这些实例的静态成员都指向同一块内存区域(即同一个类的静态成员变量只要有一个变化，
其他的也会变化，因为这些类的静态成员变量实际上是同一个)。
- 静态成员之间能够相互访问，没有`this`指针，静态成员函数不能访问非静态成员函数和非静态数据成员。
- 由于没有`this`指针的额外开销，因此静态成员函数与类的普通成员函数相比速度上会有少许的增长。
- 静态成员函数在类内声明时使用`static`关键字，在类外定义时不再使用`static`关键字。
- 静态成员变量必须在类外初始化，在类中的静态成员变量定义仅等同于声明，若静态成员变量没有在类外进行初始化，
引用时会出现`未定义引用`错误。
- 普通静态成员变量不能进行类内初始化，只有**常静态成员变量**(`const static`)才能进行类内初始化。

静态成员变量初始化的格式为：

```cpp
数据类型 类名::静态成员变量名; //使用默认构造器
数据类型 类名::静态成员变量名(参数...); //显式使用构造函数初始化静态变量
数据类型 类名::静态成员变量名 = 值; //静态成员变量的初始化需要在全局区域，不能在函数体/类内
```

类的静态成员变量有两种访问形式：

```cpp
类实例名.静态成员变量名;
类名::静态成员变量名;
```

类的静态成员变量在逻辑上依然受到类的访问权限的制约，`private`、`protected`的静态成员变量依然无法在类外访问，但可以在类外赋初值。

注意事项：

- 普通类的静态成员变量在类内仅仅是**声明**了该变量，要使用该成员变量还需要在全局区域进行定义。
该定义**不能**写在头文件中，否则一旦该头文件被**多个**源码文件包含，
连接时会出现`multiple definition of ***`(**多重定义**)错误。
- **静态成员变量定义不能写在头文件中**的规则仅仅对于普通类有效，对于**模板类**则不再适用。
模板类的静态成员定义同样需要写在头文件内。
模板类的编译模型与常规代码不同，在定义时并不实际生成代码，只有在被其它代码引用时编译器才会为其生成对应的模板代码，
因而模板类在头文件中定义静态成员不存在多重定义问题。
同时大多数编译器**不支持**`export`分离模板定义模型(如`g++`、`clang++`等)，
因此模板类的定义**必须**写在头文件内(**模板特化**情形除外)。

示例：

头文件`test.h`：

```cpp
#pragma once

class A
{
public:
	static int a;
	static int b;
};

int A::a = 1; //错误，普通类头文件内进行静态成员定义造成多重定义错误

template <class T>
class B
{
public:
	static int a;
	static int b;
	static int c;
	static int d;
};

template <class T>
int B<T>::a; //正确，在头文件中定义模板类的静态成员
```

源码文件`test.cc`：

```cpp
#include "test.h"

int A::b = 2; //正确，普通类的静态成员在代码文件中定义，而非头文件

template <class T>
int B<T>::b = 2; //错误，模板类的静态成员在代码文件中定义由于模板编译模型无法找到，提示"未定义的引用"

template <>
int B<int>::c = 3; //正确，模板特化定义可以写在源码文件中

template <>
int B<int>::d; //错误，模板特化定义必须使用显式定义(使用赋值操作符/构造函数等)
```

入口源码文件`main.cc`：

```cpp
#include "test.h"

#include <iostream>

using namespace std;

int main(void)
{
	cout << A::a << endl;
	cout << A::b << endl;

	cout << B<int>::a << endl;
	cout << B<int>::b << endl;
	cout << B<int>::c << endl;
	cout << B<int>::d << endl;

	return 0;
}
```

编译输出(G++ 6.1.1 && ArchLinux x64)：

```
/tmp/ccSLIJuT.o:(.data+0x0): multiple definition of `A::a'
/tmp/ccAkJrHZ.o:(.data+0x0): first defined here
/tmp/ccAkJrHZ.o: In function `main':
main.cc:(.text+0x63): undefined reference to `B<int>::b'
main.cc:(.text+0xa1): undefined reference to `B<int>::d'
collect2: error: ld returned 1 exit status
```



# C/C++中 const 关键字的区别

## const 变量初始化
在C语言中，`const`变量在定义时可以不初始化，编译器会自动为其初始化为一个默认值。
在C++中，`const`变量在定义的同时必须显式地初始化，定义没有初始化的`const`变量将无法通过编译。

在`C++98`中，`const`变量在类中定义时，则初始化需要放在构造函数的初始化列表中。
在C++11中，成员变量初始化可以直接在类中进行，`const`成员变量也一样可以在类中初始化。

## const 变量作为数组长度
对于以下代码：

```cpp
const int length = 10;
int array[length];
```

在部分C语言编译器中会报错，但在C++中正确。
`C99`开始支持变量作为数组长度定义，但不是所有编译器都支持这个特性(`GCC`能够支持)。
`ANSI C`中，数组的长度只能由常量定义，即使`const`变量的值不会发生变化，但仍然**不是**常量。



# 运算精度
在`C/C++`运算中，需要注意精度的转换的时机，如下表达式：

```c
double num = 1 / 3;
printf("%f\n", num);
```

输出结果(GCC 5.3.0 && ArchLinux x64)：

```
0.000000
```

- 进行除法运算的两个操作数皆为**整型**，`1 / 3`的结果为`0`，运算结束之后转换为**双精度浮点型**，精度提升，
但提升是以整型计算的结果`0`作为原始值的，因而提升之后的结果为`0.000000`。
- 对于结果可能为浮点数的运算，至少需要一个操作数为浮点型才能保证运算结果正确。



# 8进制与16进制
在`C/C++`中，表示8进制与16进制数值需要在数值前加前缀：

- 表示**8进制**数值，在数值前加`0`：

	示例：

	```c
	int num0 = 011; //等于10进制数 "9"
	//int num1 = 089; //编译报错，8进制数中不能出现大于等于 "8" 的数值
	```

- 表示**16进制**数值，在数值前加`0x`：

	示例：

	```c
	int num0 = 0x11; //等于10进制数 "17"
	int num1 = 0xab; //等于10进制数 "171"
	//int num2 = 0xgh; //编译报错，16进制数中不能出现大于等于"f"的数值
	```

C/C++中，**没有**提供表示2进制数值字面量的方式。



# sizeof 运算符
`sizeof`运算符**不是**函数，在**编译时**生效。
指针与数组的区别之一就是使用sizeof返回的大小不同：

- 对于数组而言，虽然数组名可以代表数组的首地址，`sizeof`对于指针返回的大小总是`8`(64bit OS)或是`4`(32bit OS)。
- 将**数组名**作为参数返回的是`数组类型 * 元素个数`的大小。

示例：

```cpp
#include <stdio.h>

int main(void)
{
	char* str = "12345";
	char chars[5] = "12345";
	printf("%d %d\n", sizeof(str), sizeof(chars));
	return 0;
}
```

输出结果：(GCC 4.9.1 && ArchLinux x64)

```
8 5
```

由结果可知，`str`的类型为`char*`，是指针，大小为`8`，`chars`类型为`char[]`，大小为`5 * 1 = 5`。



# 列表初始化
在C/C++中允许直接使用花括号进行初始化。

## 数组初始化
在C/C++中，使用花括号可以在数组定义时进行初始化，示例：

```c
type array_name[] = { value0, value1, ... }; //由初始化内容决定数组长度
type array_name[size] = { value0, value1, ... }; //指定数组长度
```

## designated initializers (C99)
在`C99`中，扩充了花括号初始化数组的功能，允许指定范围进行初始化(`designated initializers`)，
但C++中没有引入此特性，以下代码只能在**C编译器**下编译通过：

```c
// 实际数组内容为 " 1,1,1,1,2,2,0,3,3,3 " ，没有初始化的部分依然为默认值
int nums[10] =
{
	[0 ... 3] = 1,
	[4 ... 5] = 2,
	[7 ... 9] = 3
};

struct Student
{
	int class;
	int grade;
};

// 指定范围初始化用在结构体中，数组长度由初始化语句推断为6
struct Student students[] =
{
	[0 ... 3].class = 1,
	[4 ... 5].grade = 2
};
```

## 二维数组初始化
在C/C++中，多维数组可以直接使用花括号初始化。
二维数组的定义示例：

```c
类型 数组名[行数][列数];
```

二维数组在定义同时初始化则可以省略第一维的大小(只需要设置列大小)。
示例：

```c
类型 数组名[][列数] = { /*初始化内容*/ };
```

多维数组在初始化时可以按行初始化(嵌套花括号)，也可以直接顺序初始化(只使用一次花括号)。
示例：

```c
// 四种方式结果完全相同
char s0[][3] = { "abc", "def" }; //实际大小为[2][3]
char s1[][3] = { 'a', 'b', 'c', 'd', 'e', 'f' };
char s2[2][3] = { {'a', 'b', 'c'}, "def" }; //按行初始化
char s3[2][3] = { '1', '2', '3', '4', '5', '6' }; //顺序初始化
```

## 类/结构体列表初始化 (C++98)
对于`class`和`struct`而言，在`C++98`中，若成员变量皆为**公有成员**且**未手动定义**构造函数时，
可以使用列表进行初始化，示例：

```cpp
struct S
{
	int num1;
	int num2;
	int num3;
};

class C
{
public:
	int num1;
	int num2;
	int num3;
};

int main(void)
{
	S s = { 1, 2, 3 };
	C c = { 1, 2, 3 };

	return 0;
}
```

带有**非公有变量**的结构/类不能使用列表初始化，带有自定义构造函数的结构/类也不能使用列表初始化：

```cpp
struct S
{
	//编译时报错，提示"error: in C++98 ‘s’ must be initialized by constructor, not by ‘{...}’"
	S(int num1, int num2, int num3) : num1(num1), num2(num2), num3(num3) {};

	int num1, num2, num3;
};

class C
{
public:
	int num1;

// 编译报错，错误信息：
// error: could not convert ‘{1, 2, 3}’ from ‘<brace-enclosed initializer list>’ to ‘C’
protected:
	int num2;

private:
	int num3;
};

int main(void)
{
	S s = { 1, 2, 3 };
	C c = { 1, 2, 3 };

	return 0;
}
```

## 统一初始化 (C++11)
在C++11中，新增了**统一初始化**特性，带有非公有成员和自定义构造函数的类同样可以使用列表初始化，
只需要列表参数与构造函数相匹配即可：

```cpp
// C++11标准下编译成功
// C++98标准下编译出错，错误信息：
// error: in C++98 ‘s’ must be initialized by constructor, not by ‘{...}’
struct S
{
	S(int num1, int num2) : num1(num1), num2(num2), num3(num2) {}

	int num1;

protected:
	int num2;

private:
	int num3;
};

int main(void)
{
	S s = { 1, 2 };
	return 0;
}
```

统一初始化特性还可以用在动态分配数组上，并且用于赋值的等号也可以省略：

```cpp
int a[3] { 1, 2, 3 };
int* b = new int[3] { 1, 2, 3 };
```

STL中多数容器都已支持了列表初始化：

```cpp
std::vector<int> v { 1, 2, 3 };
std::map<int, int> m { {1, 6}, {2, 6}, {3, 6} };
```

即使是单个变量，也可以使用列表初始化：

```cpp
int a { 100 };
```

在函数参数中使用列表能够防止精度下降：

```cpp
auto func = [](int a) {};

// 正常
func(100.0);
// 编译报错，错误信息：
// error: narrowing conversion of ‘1.0e+2’ from ‘double’ to ‘int’ inside { } [-Wnarrowing]
func({ 100.0 });
```

在C++11中，使用了**类内初始化**特性的类若未显式定义有参构造函数，则**不能**使用统一初始化特性：

```cpp
#include <iostream>

using namespace std;

struct Test
{
	int num = 0;
	string name = "";
};

int main(void)
{
	Test t { 2333, "2333" };
	return 0;
}
```

`GCC 7.2.0`版本下，使用`g++ -std=c++11`编译，得到如下错误输出：

```
init.cc: In function 'int main()':
init.cc:13:24: error: no matching function for call to 'Test::Test(<brace-enclosed initializer list>)'
  Test t { 2333, "2333" };
                        ^
init.cc:5:8: note: candidate: constexpr Test::Test()
 struct Test
        ^~~~
init.cc:5:8: note:   candidate expects 0 arguments, 2 provided
init.cc:5:8: note: candidate: Test::Test(const Test&)
init.cc:5:8: note:   candidate expects 1 argument, 2 provided
init.cc:5:8: note: candidate: Test::Test(Test&&)
init.cc:5:8: note:   candidate expects 1 argument, 2 provided
```

`C++ 14`中则无此限制，使用`g++ -std=c++14`编译，正常编译通过。

## std::initializer_list<T> (C++11)
自定义类型可以通过使用`std::initializer_list<T>`类型做为构造方法参数来支持**变长**的统一初始化参数表：

```cpp
#include <iostream>
#include <initializer_list>

template <class T>
class Init
{
public:
	Init(const std::initializer_list<T>& l)
	{
		for (const T& i : l)
			std::cout << i << " ";
		std::cout << std::endl;
	}
};

int main(void)
{
	Init<int> { 1 };
	Init<int> { 1, 2, 3 };
	Init<std::string> { "One", "Two", "Three" };
	return 0;
}
```

输出结果：

```
1
1 2 3
One Two Three
```

当存在多个符合初始化列表签名的构造方法时，优先调用使用`std::initializer_list<T>`类型做为参数的构造方法：

```cpp
#include <iostream>
#include <initializer_list>

class Init0
{
public:
	Init0(int num0, int num1)
	{
		std::cout << "Init0: Call for normal..." << std::endl;
	}
};

class Init1
{
public:
	Init1(const std::initializer_list<int>& l)
	{
		std::cout << "Init1: Call for initializer_list..." << std::endl;
	}
	Init1(int num0, int num1)
	{
		std::cout << "Init1: Call for normal..." << std::endl;
	}
};

int main(void)
{
	Init0 { 1, 2 }; //可用统一初始化语法调用普通构造方法
	Init1 { 1, 2 }; //当存在接收std::initializer_list<T>参数的构造方法时，统一初始化语法优先调用该构造方法

	return 0;
}
```

输出结果：

```
Init0: Call for normal...
Init1: Call for initializer_list...
```



# 结构体对齐
出于性能考虑，多数编译器会对结构体内的成员变量进行大小对齐。
由于结构体对齐，结构体的大小与变量大小之和有时并不相等。
在`GCC/Clang`等编译器中，默认结构体按照内部的**最大**的成员变量的长度来进行对齐。

即使结构体内的变量长度未达到最大成员的长度，也会占有该大小的空间。
多个小长度的成员能够共存在同一片对齐区域内。但若出现了最大长度的成员变量，则下一个成员重新对齐。

示例：

```cpp
struct A
{
	int a;
	char b;
};
```

结构体`A`大小为`8`。
`A`按照最大的成员变量的类型`int`的长度进行对齐，变量`b`虽然只有`1`个字节，
但实际占用`4`个字节的大小，因而结构体的大小为`8`个字节。

```cpp
struct B
{
	int a;
	char b;
	char c;
};
```

结构体`B`大小依旧为`8`。
`B`中成员变量`b`按照`int`型的`4`个字节进行对齐，但并未将4个字节的空间完全使用，故变量`c`继续使用这`4`个字节的空间。

```cpp
struct C
{
	char b;
	int a;
	char c;
};
```

结构体`C`的大小为`12`。
变量`b`按照`int`型的`4`个字节进行对齐，但下一个变量`a`也为`int`型，需要占用`4`个字节，`b`的剩余空间不够使用，
`a`变量便会再占用`4`个字节的空间，而由于`a`变量是完全使用对齐空间的，下一个变量`c`则需要重新分配对齐空间，
又占用`4`个字节的空间，故结构体`C`的大小为`4 + 4 + 4 = 12`。

## 指定结构体对齐大小
在一些特殊的场景下(如结构体需要转换为字节流时)，需要使用紧凑内存布局，不需要为性能而强制对齐结构体，此时可以指定结构体的对齐方式。

`GCC/Clang`编译器支持在结构体定义后追加扩展指令`__attribute__ ((packed))`，可取消结构体对齐：

```c
// 编译器为 GCC/Clang
struct A
{
	int a;
	char b;
} __attribute__((packed)); //结构体大小为5
```

`MSVC`编译器支持在结构体定义前使用专属编译器指令`__declspec(align(n))`，可部分调整编译器的对齐大小，但不能小于默认对齐大小：

```c
// 编译器为 MSVC

__declspec(align(16)) //对齐大小数值必须为2的幂
struct A
{
	int a;
	char b;
}; //结构体大小16，对齐大小被提升至16

__declspec(align(1)) //对齐大小小于默认对齐大小，不生效
struct A
{
	int a;
	char b;
}; //结构体大小8，设置的对齐大小未生效
```

`GCC/Clang/MSVC`等编译器均支持预处理指令`#pragma pack(n)`，该指令可指定结构体对齐数值：

```c
#pragma pack(1) //结构体大小按1对齐

struct A
{
	int a;
	char b;
}; //结构体大小为5

#pragma pack(2) //结构体大小按2对齐

struct B
{
	int a;
	char b;
}; //结构体大小为6

#pragma pack() //无数值时恢复默认对齐方式
```



# 变长参数
C语言不支持**函数重载**，但是依然可以定义变长参数函数，使用`...`符号代表可变参数表。
不能定义一个参数仅为`...`的函数，一个函数如果接受变长参数，则至少需要有一个确定参数。

典型的变长参数函数定义：

```c
type function(type arg, ...);
```

标准库中存在大量变长参数函数，如打印输出函数`printf()`就可以接收变长参数。

## 自定义变长参数函数
自行编写变长参数函数可以使用`stdarg.h`头文件中提供的宏，示例：

```c
#include <stdarg.h>
void va_start(va_list ap, argN);
void va_copy(va_list dest, va_list src);
type va_arg(va_list ap, type);
void va_end(va_list ap);
```

使用方法：

1. 先要创建`va_list`变量用于记录位置，然后使用`va_start()`宏初始化`va_list`变量，参数`argN`为函数第一个参数。
1. 通过`va_arg()`获取当前`va_list`的下一个参数值，`type`为下一个参数的类型。每次运行这个宏，`va_list`会随之下移一个位置。
1. 当所有变量都读出之后可以关闭`va_list`，使用`va_end()`宏。

示例：

```c
#include <stdio.h>
#include <stdarg.h>

int get(int s, ...)
{
	va_list arg;
	va_start(arg, s); //初始化arg
	printf("%d ", va_arg(arg, int)); //第一次运行宏得到第二个参数的值
	printf("%d ", va_arg(arg, int)); //第二次运行宏得到第三个参数的值
	va_end(arg);
	return 0;
}

int main(void)
{
	get(5, 30, 40);
	return 0;
}
```

## 通过地址获取变长参数内容
除了使用`stdarg.h`头文件中所提供的宏来获取变长参数内容之外，还可以直接以取地址的方式来获取变长参数的内容。

在C语言中，函数的参数压栈的顺序是**从右向左**，而栈底为高地址，栈顶低地址，因此靠后的参数先进栈为高地址，靠前的参数后进栈为低地址。
与结构体对齐类似，参数在压栈过程中编译器会对其进行内存对齐，因此在计算变长参数的偏移地址时需要考虑参数类型的对齐情况。

在不同平台下，变量类型所占字节数是不同的：

- 在`Windows x86`中，`int`、`char`、`float`、`long`、`指针`以及为未指定类型的整数等，以4个字节对齐。
`double`、`long long`以及未指定类型的小数等以8个字节对齐。
- 在`Unix x86_64`中，除了`long double`之外，大部分类型都以8个字节对齐。

示例：

```c
#include <stdio.h>

void get(float a, ...)
{
	printf("%f %c %d\n", a, *(char*)(&a + 1), *(int*)(&a + 2));
}

int main(void)
{
	get(9.9, 'b', 888);
	return 0;
}
```

输出结果：(VS 2013 && Windows 8.1 x64)

```
9.900000 b 888
```

输出结果：(GCC 5.1.0 && ArchLinux x64)

```
9.900000   98
```

从结果不难看出，Unix环境下输出的参数内容产生了偏差，是由于数据不同平台数据类型长度不同，内存对齐方式不同导致的。
要使Unix环境下能够显示参数，修改`printf()`函数中的内容：

```c
printf("%f %c %d\n", a, *(char*)((long*)&a + 1), *((long*)&a + 2));
```

即可在`Unix x86_64`环境下正常输出结果。

## 变长参数宏
`C99`中规定了宏可以像函数一样拥有可变参数表。
使用`...`代表可变参数表，使用`__VA_ARGS__`代表传入的参数内容。

以标准库中的`printf()`函数为例，为`printf()`函数定义具有可变参数的宏，示例：

```c
#define PRINTF(str, ...) printf(str, __VA_ARGS__) //MSVC中允许空的可变参数表，GCC中不允许
```

对于`GCC/Clang`等编译器，支持如下扩展语法：

```c
#define PRINTF(str, args...) printf(str, args) //不支持非空可变参数表
```

可变参数可被命名，直接通过名称获取可变参数。

可变参数不可为空，否则编译出错。
若允许空的可变参数表，获取可变参数表时名称前添加`##`操作符(在可变参数非空时才进行宏连接)：

```c
// 支持可空可变参数表
#define PRINTF(str, args...) printf(str, ##args) //GCC/Clang
#define PRINTF(str, ...) printf(str, ##__VA_ARGS__) //MSVC/GCC/Clang
```



# 自增自减运算符的优先级
自增自减运算符根据出现位置的不同，可能在语句之前或语句之后执行，且对整个语句生效(部分编译器约定不同，比如`Clang`)。

例如：

```c
int a = 0;
printf("%d %d\n", a, ++a);
```

输出结果为：

```
1 1	(GCC 4.9.2 && ArchLinux x64)
0 1	(Clang 3.5.1 && ArchLinux x64)
```

在`Clang`中会给出警告：`warning: unsequenced modification and access to 'a'`，即无序地修改和存取变量a。

```c
int a[5] = { 1, 2, 3, 4, 5 };
int b[5] = { 0 };
int* c = a;
int* d = b;
while (*d++ = *c++);
for (int i = 0; i < 5; i++)
	printf("%d ", b[i]);
```

输出结果：

```
1 2 3 4 5
```

GCC与Clang输出相同，但在Clang中会给出警告，
`warning: using the result of an assignment as a condition without parentheses [-Wparentheses]`，
即仅使用了条件任务而没有使用括号(未使用循环体)。

`while (*d++ = *c++);`的作用是复制数组内容。
先将指针`c`指向的内容取出即`*c`，复制到指针d指向的内容即`*d`，然后执行自增运算符，左右的指针都自增1位，
同时指向数组下一个元素，然后while语句判断`*d`的内容。
由于在C/C++中，非0数值均被视为true，故循环可继续执行，直到数组结束，指针指向空内容为止。

用`while (*d++ = *c++);`进行复制内容时需要注意，如果复制的内容中含有0，则复制会提前结束。
此类语句还可以用来复制**字符数组**，字符串以`\0`结尾，复制到字符串结尾自动停止。



# 编译器自动生成的成员函数
一个没有任何内容的空类并不为空，编译器会自动为其增加成员：

1. 空构造函数。
1. 复制构造函数。
1. 空析构函数。
1. 重载等号为复制对象。
1. 取址运算符重载(一对，带`const`/不带`const`)。

这些函数只有在第一次被调用时，才会被编译器创建。
所有自动生成的成员函数都是`inline`和`public`的。

在C++11中，若类未定义自己的复制构造函数，则还会生成默认的**移动构造函数**和并重载等号为**移动赋值运算符**。

若自行定义了复制构造函数而未定义移动构造函数，则使用右值对象做参数实例化时，
会调用复制构造函数(`const左值引用`能够绑定在右值对象上，但如果存在移动构造函数则会优先匹配接收右值的移动构造函数)。

默认情况下，由编译器生成的默认复制构造函数以及重载等号都是**浅复制**，
即对于指针变量，只会复制指针中保存的地址，而不会复制指针指向的内存区域。
若需要深复制，则需要自行实现这些函数以改变复制行为。

一个空类：

```cpp
class Empty { };
```

实际上等价于：

```cpp
class Empty
{
public:
	Empty(); //默认的空构造函数
	Empty(const Empty&); //复制构造函数
	Empty(Empty&&); //C++11，移动构造函数
	~Empty(); //默认的析构函数
	Empty* operator&(); //重载取地址运算符
	const Empty* operator&() const; //带const的取址运算符
	Empty& operator=(const Empty&); //重载等号为对象内容复制
	Empty& operator=(Empty&&); //C++11，重载等号为移动对象
};
```

## 控制默认生成的成员函数
在C++11中，引入了`delete`、`default`关键字，用于控制默认成员函数的生成。

`delete`用于禁止合成某类默认成员函数：

```cpp
class Test
{
public:
	Test() = delete; //禁止默认的构造函数
	Test(const Test&) = delete; //禁止默认的复制构造函数
	... 其它类似
};
```

在类定义时，若手动定义了有参构造函数，则编译器不会再为之合成默认的无参构造函数。
若需要保留默认的无参构造函数，则使用`default`关键字，示例：

```cpp
class Test
{
public:
	Test(int) {};
	Test() = default; //使用default关键字合成默认无参构造函数
};
```

在某些情况下，由编译器生成的空参构造函数相比编码者手动编写的更加高效。



# 继承
C++中的继承分为公有继承`public`、保护继承`protected`以及私有继承`private`，不显式指定继承方式时默认为**私有继承**。

- **公有继承**继承父类的可继承成员的同时**不改变**这些成员在子类中的访问权限，
但**保护继承**、**私有继承**会将继承来的成员限制在子类中的访问权限。
- 公有继承类似于其他高级语言(Java/C#)中的继承，**只有**公有继承能够表达出其他语言中的继承关系(子类来源于父类)。
- 私有继承与保护继承的类可以正常实现一些OOP特性如`override`、`虚函数`等，但其子类实例**不**支持**向上转型**。
- C++在发生**重写**行为时，**不强制**要求子类的重写函数访问权限要大于等于父类，在发生**向上转型**时，
父类的虚函数如果被子类重写，则调用子类的实现，不受子类的重写函数的访问权限影响(即使子类重写函数是私有的，父类实例一样调用子类重写的实现)。

示例：

```cpp
// 私有继承
#include <iostream>

using namesapce std;

class A
{
public:
	virtual int get() { return 100; }
};

class B : A
{
private:
	int get() { return A::get() + 100; }
};

int main(void)
{
	A* a = new B; //报错，提示 " 'A' is an inaccessible base of 'B' "
	return 0;
}

// 向上转型访问子类私有实现
#include <iostream>

using namesapce std;

class A
{
public:
	virtual int get() { return 100; }
};

class B : public A
{
private:
	int get() { return A::get() + 100; }
};

int main(void)
{
	A* a = new B;
	cout << a->get() << endl; //正确，调用子类实现，输出200
	cout << B().get() << endl; //错误，提示"within this context"
	return 0;
}
```



# 指针运算
在C/C++中，对指针进行加减运算时，并不是直接对地址的大小加上数值得到新的地址，
而是原地址加上由`操作数 * 指针所指向的内容的类型大小`得到的偏移量计算出的地址。

示例：

```c
#include <stdio.h>

int main(void)
{
	long* a = (long*)0x1; //内存地址赋值给指针之前需要进行强制类型转换，否则编译器不知道内存的类型
	printf("%p\n", a + 1); //打印指针使用%p，会以"0x...."的格式输出
	int b[] = { 1, 2, 3 };
	printf("%d, %d", *(b + 1), *((int*)(&b + 1) - 1));
	return 0;
}
```

输出结果：(GCC 4.9.2 && ArchLinux x64)

```
0x9
2, 3
```

由例子中不难看出，`a + 1`代表的地址不是简单地将`a`的地址`0x1`加上`1`，
而是`a`的地址加上指针所指向的数据类型`long`的大小(8个字节)乘以操作数`1`得到的值`0x9`。
对于数组`b`，单独使用数组名称代表的是数组首元素的地址`&b[0]`，`b + 1`代表的是`b[0]`的下一个元素`b[1]`，
而`&b`代表的是整个数组的首地址，虽然二者`b == &b`的值相同，但意义完全不同，`&b + 1`代表的是b的整个数组结束后的下一个位置。

## 数组名的含义
对于数组名而言，在`sizeof`和**指针加减**两种操作中分别有不同的含义。

- 使用`sizeof`操作符时，数组名代表**整个数组**，如果用数组名作为参数，则返回的值为`数组包含的类型的大小 * 数组数量`。
- 进行地址加减操作时，数组名表示的是**数组第一个元素的地址**，`数组名 + 1`实际上代表**数组第二个元素的地址**，
而`&数组名`才代表整个数组的**起始地址**，`&数组名 + 1`代表数组**结束**之后的下一个位置。

## 指针数组与数组指针
指针数组是包含多个指针的**数组变量**，语法格式如下：

```c
// []操作符优先级比*操作符高，先于变量名结合，因而变量为数组类型，数组的内容为指针
type* point_array[size];
```

数组指针是指向一个数组的**指针变量**，语法格式如下：

```c
// 使用括号令*操作符先于变量名结合，因而变量为指针类型，指针指向的内容为数组
type (*array_point)[size];
```

如下代码所示：

```c
#include <stdio.h>

int main(void)
{
	int num_1 = 1, num_2 = 2, num_3 = 3;

	int array[] = { num_1, num_2, num_3 };
	int* point_array[] = { &num_1, &num_2, &num_3 }; //指针数组
	int (*array_point)[] = &array; //数组指针

	return 0;
}
```



# C++对象模型
在C++中，没有虚函数的情况下，只有**非静态数据成员**存储在类内，
其它的**静态数据成员、静态成员函数、非静态成员函数**都存储在全局区，增加这些成员**不会**引起类大小的变化。

在有虚函数且多重继承的情况下，多个父类按照其声明顺序依次排列，而每个类的区域内部先是一个虚表指针(vptr)，
然后是普通成员变量，子类与第一个继承的父类共用一个虚表，子类的普通成员紧跟在最后一个父类的普通成员之后。

类的成员函数和静态成员变量实际是全局的，因此类的实例中并不包含这些内容，
使用sizeof计算类的大小时也不会把这些内容计算进去，通过地址访问类的成员进行地址计算时需要忽略这些成员的大小。

## 成员函数
C++中，普通成员函数(包括静态成员函数，但虚函数除外)并不是直接存放在类中的，而是像普通的全局函数一样存放。
成员函数在经过C++编译器处理后，函数名会被改写，而函数名就指明了该函数的类归属以及参数信息。

普通成员函数仅仅是逻辑上存在于类中，成员函数的实际实现并不依赖于类。
空类大小为1，但向空类中添加任意个普通成员函数，类大小仍然是1。

存在虚函数的情况下，类中会保存有一个虚表指针`vptr`，用于保存类中虚函数的地址，向空类中添加一个**虚函数**，
则类的大小变为单倍指针大小(虚表指针大小)，增加虚函数的个数，类大小不改变。

## 虚函数
C++中只有虚函数才能被子类重写`override`，非虚函数会被子类的同名函数隐藏(无论函数原型是否完全相同)。
C++中使用`virtual`关键字定义虚函数，虚函数可以只有函数定义而没有函数实现，没有函数实现的虚函数称为纯虚函数，
C++中使用`= 0`或`= nullptr`(C++11新增语法)来表示一个虚函数为纯虚函数(类似于Java和C#中的`abstract`方法)。
拥有一个或以上纯虚函数的类称为抽象类，抽象类不能被实例化，也不能在构造函数的内容中使用，但C++11之后可以用在构造函数的初始化序列中。

一个函数不能既是虚函数又是静态函数(`static`和`virtual`关键字不能共存)，静态函数是全局的，无需实例化就能被调用，
不能够被重写，不能实现向上转型调用子类同名方法实现。

虚函数通过一张虚函数表来实现。类实例的最前位置有一个虚表指针`vptr`，指向一张虚函数表，
虚函数表中按声明顺序存放了所有该类的虚成员函数的地址，可以通过该表中的地址调用对应的函数实现。
虚函数表的最后位置多加了一个节点作为虚函数表的结束标志，
在VS中，结束标志是`NULL`，在gcc中用0表示虚函数表结束，用1表示接下来的位置还有别的虚函数表。

在**单继承无重写**的情况下，子类对象和父类对象的虚函数按照声明顺序出现在虚函数表中，
子类的虚函数在表中的位置处于父类虚函数之后。
在**单继承且向上转型**的情况下，如果父类虚函数被子类重写，
则父类对象中的虚函数表中存放的虚函数地址会被替换成子类的对应函数地址，以此实现运行时多态。
在**多重继承**的情况下，子类的对象会按照声明中的顺序生成多个父类虚函数表，子类的成员虚函数放置于**首个父类**的虚函数表中。
多个虚函数表之间不是直接相连的，而是按照继承顺序下的该类中的成员内容完全结束之后才会开始下一个类的虚函数表。

示例：

```cpp
#include <iostream>

using namespace std;

// 类A有两个虚函数和一个成员变量，由于内存对齐，类A的大小为16(虚表大小8，变量对齐到8)
class A
{
	virtual int get(int);
	virtual int get();
	char a = 'A';
};

// 单一继承的情况
class B : A
{
	virtual int get1();
};

class C
{
	char c = 'C';
	virtual int get();
};

// 多重继承的情况
class D : A, C
{
	char d = 'D';
	virtual int get2();
};

// 单一继承并发生override的情况
class E : public A
{
	int get();
};

int A::get(int)
{
	cout << "A::get(int)" << endl;
	return 0;
}

int A::get()
{
	cout << "A::get()" << endl;
	return 0;
}

int B::get1()
{
	cout << "B::get1()" << endl;
	return 0;
}

int C::get()
{
	cout << "C::get()" << endl;
	return 0;
}

int D::get2()
{
	cout << "D::get2()" << endl;
	return 0;
}

int E::get()
{
	cout << "E::get()" << endl;
	return 0;
}

int main(void)
{
	A* a = new E;
	B b;
	D d;

	// 在64bit的Linux中，普通指针的大小为8B，故需要转换为一个占有8个字节的类型来保存内容，否则可能会发生截断
	cout << "调用类A的get(int)函数 ";
	((int (*)())*(long*)*(long*)&d)();
	cout << "调用类A的get()函数 ";
	((int (*)())*((long*)*(long*)&d + 1))();
	cout << "调用类D的get2()函数 ";
	((int (*)())*((long*)*(long*)&d + 2))();

	cout << "类A的变量a的值 " << (char)*((long*)&d + 1) << endl;
	cout << "类C的变量a的值 " << *(char*)((long*)&d + 3) << endl;

	// 类D继承于类A和C，D的虚函数添加到了类A虚表的末尾，因而类D中的变量a处于类C中的变量a的下一个位置
	cout << "类D的变量a的值 " << *((char*)((long*)&d + 3) + 1) << endl;

	cout << "调用类B的get1()函数 ";
	((int (*)())*((long*)*(long*)&b + 2))();
	cout << "调用类C的get()函数 ";
	((int (*)())*(long*)*((long*)&d + 2))();
	cout << "调用类A的get(int)函数 ";
	((int (*)())*((long*)*(long*)&*a))();

	cout << "向上转型使用A类指针调用类E的get()函数 ";
	((int (*)())*((long*)*(long*)&*a + 1))();

	return 0;
}
```

输出结果：(GCC 4.9.2 && ArchLinux x64)

```
调用类A的get(int)函数 A::get(int)
调用类A的get()函数 A::get()
调用类D的get2()函数 D::get2()
类A的变量a的值 A
类C的变量a的值 C
类D的变量a的值 D
调用类B的get1()函数 B::get1()
调用类C的get()函数 C::get()
调用类A的get(int)函数 A::get(int)
向上转型使用A类指针调用类E的get()函数 E::get()
```

输出结果分析：

`D`类继承于`A``C`两个类，生成类两张虚表，`D`的虚函数`get2`的地址保存在`A`的虚函数表中，位于虚函数表的最后一个位置。

`A`类的大小为16，`A`类的内容结束后就是`C`的内容，因此`C`的虚表指针地址为`类实例起始地址 + 16`即`&d + 16`，
用8个字节的`long`型做转换可以写成`(long*)&d + 2`，而`D`类自己的变量`a`地址位于类`C`结束位置的下一个位置(类`D`的虚函数在`A`末尾，
故没有单独虚表)，同时又因为类`D`没有单独的虚表，则根据结构体长度对齐的原则，类`D`的变量`a`会紧接着类`C`的变量`a`，
即`(char*)((long*)&d + 3) + 1`。

`E`类继承与`A`，只有一张虚表，通过向上转型得到的实例`a`中，`E`的`get()`重写了父类`A`的虚函数`get()`，
`(long*)*(long*)&*a`是虚函数表的首地址，存放是`A`类的第一个成员虚函数`get(int)`，
`(long*)*(long*)&*a + 1`是虚函数表中的第二个内容的地址，地址中存放的原本是类A的第二个虚函数`get()`，
但在向上转型的实例中，被替换成了子类`E`的`get()`函数的地址。

在多重继承时，如果继承的多个父类中都有符合子类函数签名的虚函数，则子类会将所有符合条件的虚表中的父类虚函数指针替换成子类的函数指针。

在`VS`中运行此段代码，只会输出前两个结果，因为在VSC编译器下，多个虚表之间不直接相连，
在类成员结束之后并未直接开始下一个虚表，而是隔着一些特殊的字段并用0进行填充，不能通过直接加减类实例地址来得到下一个虚表地址。



# 参数默认值
C++允许在定义函数是给函数的参数设定**默认值**，在调用这个函数时，如果没有给出对应参数的值，就会使用默认的参数值。

- 在调用具有默认参数的函数时，如果使用参数了一个参数的默认值，则其它带有默认值的参数也应该使用默认值，
若不准备使用参数的默认值，则所有带默认值的参数的默认值都不应该被使用。
- 带有默认值的函数参数需要连续出现，即一旦有一个参数开始有默认值，
之后的参数都需要有默认值(即带有默认值的参数与无默认值的参数不能够交错出现)。
- 参数的默认值只能在函数的声明或定义的其中一处指定，不能两处都指定。
- 参数默认值在定义中指定时，需要注意定义必须写在该函数被调用前默认参数才能生效，否则依然按照声明中的无默认值格式调用。
- 带有默认参数的函数在定义时需要注意不能与重载函数相冲突。
- 函数默认值只在有函数被常规调用时才有效，如果使用函数指针调用函数则函数默认值无效。

示例：

```cpp
int got(int a = 3);

int got(int a = 3) //编译报错，默认参数只能出现在定义或是声明中的其中一处
{
	return a;
}

int get(int b = 3, int a) //编译报错，一旦有一个参数带有默认值，后面的参数都应拥有默认值
{
	return b;
}

int get(int b = 3)
{
	return b;
}

int get()
{
	return a;
}

int main(void)
{
	get(); //编译报错，有两个函数都符合要求。
	int (*p)(int) = got;
	p(); //编译报错，参数过少。
	p(100); //正常。
	return 0;
}
```



# 函数定义嵌套
在C/C++标准中，函数定义必须完全平行、相互独立，函数定义的内部不能嵌套另一个函数的定义。

`GNU C`扩充了C的语法，在`GCC`中嵌套函数定义是**允许**的行为(只有`gcc`！`clang`、`clang++`、`g++`并不允许嵌套函数定义！)
以下的代码在`GCC`中可以顺利编译并得到执行结果：

```c
#include <stdio.h>

int got(int num)
{
	int got(int num)
	{
		return num;
	}
	return got(num);
}

int main(void)
{
	printf("%d\n", got(100));
	return 0;
}
```

输出结果：(GCC 5.1.0 && ArchLinux x64)

```
100
```



# lvalue reference (左值引用) / rvalue reference (右值引用)
在C++中，`左值(lvalue)`代表**持久性**的对象，`右值(rvalue)`代表**短暂**的对象。
左值可以被**取地址**，右值不能被取地址。
右值在语句结束前没有绑定一个引用，则会被丢弃。

引用绑定规则：

- **非const左值引用**(`T&`)可以绑定到非const左值。
- **const左值引用**(`const T&`)可以绑定到任意左值和任意右值(无论是否const)。
- **非const右值引用**(`T&&`)可以绑定到非const右值。
- **const右值引用**(`const T&&`)可以绑定到任意右值(无论是否const)。

## rvalue reference (右值引用)
在C++11中加入了**右值引用**的概念。
使用`类型&&`表示引用绑定一个来自**右值**的引用，示例：

```cpp
int&& = 23333;
```

右值引用仅能绑定右值，而右值在语句结束前没有绑定引用会被销毁，因而右值可以被安全地**转移**。

## universal reference (通用引用)
`类型&&`并不总是表示一个**右值引用**，在类型由推断得到时，表示**通用引用**。
**通用引用**能绑定到任意左值/右值，编译器根据实际传入的值类型决定引用类型。

常见的通用引用有如下情形：

- `auto declaration` (auto声明)

	`auto&&`能绑定任意左值/右值，示例：

	```cpp
	auto&& num0 = 2333; //绑定右值，推断为 int&&
	auto&& num1 = num0; //绑定左值，推断为 int&
	```

- `function template parameters` (模版函数参数)

	模版函数的参数为`T&&`形式时，会根据实际传入参数推断引用类型，示例：

	```cpp
	template <class T>
	void ref(T&&) { } //模版参数表为 T&& 形式时，为通用引用

	int main(void)
	{
		const int& r_ref = 2333;
		int&& l_ref = 2333;

		ref(r_ref); //右值引用 => 左值 => 模版参数类型 T&
		ref(l_ref); //const左值引用 => 左值 => 模版参数类型 T&
		ref(2333); //右值 => 模版参数类型 T&&

		return 0;
	}
	```

	模版函数的返回值为`T&&`形式并不构成通用引用，示例：

	```cpp
	template <class T>
	T&& ref(T&& t)
	{
		return t;
	}

	int main(void)
	{
		ref(2333);
		return 0;
	}
	```

	编译出错，提示：(clang-802.0.42 && macOS 10.12.6)

	```
	ref.cc:4:9: error: rvalue reference to type 'int' cannot bind to lvalue of 	type 'int'
	        return t;
	               ^
	ref.cc:9:2: note: in instantiation of function template specialization 	'ref<int>' requested here
	        ref(2333);
	        ^
	1 error generated.
	```

	模版类的成员函数参数表中带有`T&&`形式的模版参数时，并不是通用引用。
	模版类在构造时模版参数已经确定，并不由推导得到，示例：

	```cpp
	template <class T>
	class Ref
	{
	public:
		void ref(T&&) { } //使用 int 作为模版参数时，参数表已被确定为 void ref(int&&) 故仅能接受右值参数
	};

	int main(void)
	{
		const int& r_ref = 2333;
		int&& l_ref = 2333;

		Ref<int>().ref(r_ref); //编译报错，参数类型不匹配(需要右值)
		Ref<int>().ref(l_ref); //编译报错，参数类型不匹配(需要右值)
		Ref<int>().ref(2333); //编译通过

		return 0;
	}
	```

	编译出错，提示：(clang-802.0.42 && macOS 10.12.6)

	```
	ref.cc:13:17: error: binding value of type 'const int' to reference to type 'int' drops 'const' qualifier
	        Ref<int>().ref(r_ref);
	                       ^~~~~
	ref.cc:5:14: note: passing argument to parameter here
	        void ref(T&&) { }
	                    ^
	ref.cc:14:17: error: rvalue reference to type 'int' cannot bind to lvalue of 	type 'int'
	        Ref<int>().ref(l_ref);
	                       ^~~~~
	ref.cc:5:14: note: passing argument to parameter here
	        void ref(T&&) { }
	                    ^
	2 errors generated.
	```

## reference collapsing (引用折叠)
对于参数即为引用类型的模版函数，若传入模版参数时使用引用形式的模版参数，则会产生**引用折叠**。
示例：

```cpp
template <class T>
void test(T& t) { }

test<int&>(...);
```

调用函数时使用`int&`作为模版参数参数，则理论上参数类型为`int& + &`，即`int`类型引用的引用(`Reference to Reference`)。
而`C++`不允许`Reference to Reference`，编译器会将引用进行叠加。
引用叠加遵循以下规则：

```cpp
T& + T => T&
T& + T& => T&
T& + T&& => T&
T&& + T => T&&
T&& + T& => T&
T&& + T&& => T&&
```

实例代码：

```cpp
#include <iostream>

using namespace std;

template <class T>
void test_(T& t)
{
	cout << "T&" << endl;
}

template <class T>
void test__(T&& t)
{
	cout << "T&&" << endl;
}

int main(void)
{
	int num = 2333;

	test_<int>(num); // T& + T => T& 接收左值
	test_<int&>(num); // T& + T& => T& 接收左值
	test_<int&&>(num); // T& + T&& => T& 接收左值

	test__<int>(2333); // T&& + T => T&& 接收右值
	test__<int&>(num); // T&& + T& => T& 接收左值
	test__<int&&>(2333); // T&& + T&& => T&& 接收右值

	return 0;
}
```

## move semantics (移动语义)
在C++11之前，通过原有对象构造新对象仅有一种方式，即**复制构造函数**，示例：

```cpp
class Type
{
	Type(const Type&);
}
```

复制构造函数中传入参数为**const左值引用**(`const 类型&`)，const左值引用绑定的对象可能为右值，也可能为左值，
因而无法确定参数对象的生命周期。
在复制构造函数中，为了实现真正的对象拷贝(深复制)，若原对象中存在指针成员，需要重新申请内存，
并拷贝原对象的指针成员所指向的堆内存。

在C++11之后，新增了**移动语义**。
对于使用**右值**构造对象的场景，可以定义**移动构造函数**：

```cpp
class Type
{
	Type(T&&);
};
```

移动构造函数中传入参数为**右值引用**(`T&&`)，右值引用绑定的参数一定为右值，因而参数的生命周期仅到语句结束，可以被安全地**移动**。
在移动构造函数中，原对象中的所有内容皆可被安全地**转移**，不必深拷贝，原对象中的指针成员直接复制地址即可。

C++11之前缺少表示右值的方法，无法区分原对象来自左值或是右值，进而无法确定原对象的生命周期。
对于所有原对象，出于安全考虑，都需要**深复制**整个对象，在原对象为**右值**时，会带来不必要的开销。
C++11之后引入了右值引用和移动语义，以右值构建对象时，若对象类型同时定义了复制构造函数和移动构造函数，
会**优先匹配**该类型的移动构造函数，避免复制整个对象带来的不必要的开销。

## std::move()
右值引用自身为**左值**，将右值引用直接作为参数传递时会被作为左值对待，示例：

```cpp
#include <iostream>

using namespace std;

void ref(int&)
{
	cout << "Left reference." << endl;
}

void ref(int&&)
{
	cout << "Right reference." << endl;
}

int main(void)
{
	int&& r_ref = 2333;
	ref(r_ref);

	return 0;
}
```

输出结果：(clang-802.0.42 && macOS 10.12.6)

```
Left reference.
```

在传递右值引用时需要将其还原为`右值`才能真正触发移动构造函数。
C++11提供了`std::move()`函数用于将右值引用转换为右值，以`GCC 7.1`为例，实现如下：

```cpp
/**
 *  @brief  Convert a value to an rvalue.
 *  @param  __t  A thing of arbitrary type.
 *  @return The parameter cast to an rvalue-reference to allow moving it.
*/
template<typename _Tp>
  constexpr typename std::remove_reference<_Tp>::type&&
  move(_Tp&& __t) noexcept
  { return static_cast<typename std::remove_reference<_Tp>::type&&>(__t); }
```

上述实例使用`std::move()`转移右值引用，即可被真正被视为右值，示例：

```cpp
#include <iostream>

using namespace std;

void ref(int&)
{
	cout << "Left reference." << endl;
}

void ref(int&&)
{
	cout << "Right reference." << endl;
}

int main(void)
{
	int&& r_ref = 2333;
	ref(std::move(r_ref));

	return 0;
}
```

输出结果：(clang-802.0.42 && macOS 10.12.6)

```
Right reference.
```

## std::forward
`std::move()`会无视传入值的左右值类型统一转换为右值。
对于需要保留参数左右值类型的场景，应使用`std::forward()`。以`GCC 7.1`为例，实现如下：

```cpp
template<typename _Tp>
  inline _Tp&&
  forward(typename std::remove_reference<_Tp>::type& __t)
  { return static_cast<_Tp&&>(__t); }

template<typename _Tp>
  inline _Tp&&
  forward(typename std::remove_reference<_Tp>::type&& __t)
  {
    static_assert(!std::is_lvalue_reference<_Tp>::value, "template argument"
    " substituting _Tp is an lvalue reference type");
    return static_cast<_Tp&&>(__t);
  }
```

`std::forward()`传入左值时返回左值引用类型，传入右值时返回右值引用类型。
使用`std::forward()`，示例：

```cpp
#include <iostream>

using namespace std;

void ref(int&)
{
	cout << "Left reference." << endl;
}

void ref(int&&)
{
	cout << "Right reference." << endl;
}

int main(void)
{
	int n = 2333;
	int& l_ref = n;
	ref(std::forward<int&>(l_ref));
	ref(std::forward<int&&>(2333));

	return 0;
}
```

输出结果：

```
Left reference.
Right reference.
```

`std::forward()`在调用时需要写明模板参数类型，否则无法通过编译。
可以借助**通用引用**规则编写模板函数进行封装：

```cpp
#include <iostream>

using namespace std;

void ref(int&)
{
	cout << "Left reference." << endl;
}

void ref(int&&)
{
	cout << "Right reference." << endl;
}

template <class T>
void call_ref(T&& t)
{
	ref(std::forward<T>(t));
}

int main(void)
{
	int n = 2333;
	int& l_ref = n;
	call_ref(l_ref);
	call_ref(2333);

	return 0;
}
```

输出结果：

```
Left reference.
Right reference.
```

`std::forward()`能够根据参数左右值类型智能地转化出合适的引用类型，这个特性被称为`perfect forwarding`(完美转发)。

## 注意事项
无论左值引用或是右值引用本身都是左值，因此虽然不能直接对右值取地址，但可以对右值引用取地址。

引用一但绑定就不可更改，因此引用与指针不同，
指针分为`const 类型名* 指针名`(指向const内容的指针)和`类型名* const 指针名`(自身保存地址不可变的const指针)，
而引用本身一定是不可变的，因此只有`const 类型名& 引用名`(绑定const值的引用)，而没有真正的const引用，
`类型名& const 引用名`这样的定义编译报错。

举例：

```cpp
const int& a = 1; //正确，const左值引用可以绑定到右值
int&& b = 1; //正确，非const右值引用可以绑定到右值
int& x = 1; //错误，非const左值引用不能绑定到右值
int& x = a; //错误，非const左值引用不能绑定到const左值
int& x = b; //正确，非const左值引用可以绑定到非const左值
const int& x = std::move(a); //正确，const左值引用可以绑定到const右值
const int& x = std::move(b); //正确，const左值引用可以绑定到非const右值
int&& x = std::move(a); //错误，非const右值引用不能绑定到const右值
int&& x = std::move(b); //正确，非const右值引用可以绑定到非const右值
const int&& x = std::move(a); //正确，const右值引用可以绑定到非const右值
const int&& x = std::move(b); //正确，const右值引用可以绑定到非const右值
```

## 成员函数的引用限定
C++11之后，可以在类的成员函数定义之后添加左值引用(&)或右值引用(&&)符号。

- 成员函数的引用限定用于限制函数调用者的值类型(左值/右值)。
- 成员函数若带有左值引用限定符，则只有对象为左值时才能被调用。
- 成员函数若带有右值引用限定符，则只有对象为右值时才能被调用。
- 一个类中允许存在函数签名完全相同，而分别带有左值限定符和右值限定符的两个成员函数(不会造成定义冲突，根据对象的值类型只会有一个被调用)。
- 一旦定义了一个带有引用限定符的成员函数，则不能定义与该成员函数签名完全相同的无引用限定符版本。
- 引用限定符只能用于普通成员函数，而不能加在静态成员函数之后(静态成员可以不通过实例访问，因此左值/右值限定没有意义)。

如下代码所示：

```cpp
#include <iostream>

using namespace std;

class Test
{
public:
	void show() & { cout << "&" << endl; }
	void show() && { cout << "&&" << endl; }
	//void show() { /* code */ } //错误，定义了带有引用限定符的成员函数，则不能再定义该函数的无引用限定符版本
	//static void show() & { /* code */ } //错误，静态成员函数不能带有引用限定符
	virtual test() const & final {} //当引用限定符与后置const、final等关键字一同使用时需要注意位置
};

int main(void)
{
	Test t;
	t.show(); //左值对象调用的函数为"void show() &"
	Test().show(); //右值对象调用的函数为"void show() &&"
	return 0;
}
```

输出结果：(GCC 5.3.0 && ArchLinux x64)

```
&
&&
```



# 引用与指针
C++中，引用同样可以绑定在指针类型上。
语法格式如下：

```cpp
// 左值引用绑定指针
类型名*& 引用名 = 变量名;
类型名* const& 引用名 = const右值/非const右值/变量名;

// 右值引用绑定指针
类型名*&& 引用名 = 非const右值;
类型名* const&& 引用名 = const右值/非const右值;
```

一般来说，带`const`限定的变量可以接收非`const`变量的值，反之则不可。
举例：

```cpp
int a = 0;
const int b = 0;
int* c = &a;
//int* d = &b; //错误，const变量的地址应该有指向const变量的指针保存
const int* d = &b;
const int* e = &a; //正确，非const变量的地址也可以由指向const变量的指针保存
int* const f = &a; //正确，const指针
//int* g = f; //错误，const指针不能传递给非const指针
const int* const g = f; //正确，const指针可以传递给指向const变量的const指针

int*& x = c; //非const左值引用绑定非const指针变量(非const左值)
int*&& x = &a; //右值引用直接绑定到非const地址(非const右值)
int* const& x = &a; //const左值引用绑定到非const地址(非const右值)
const int* const& x = std::move(d); //const左值引用绑定到指向const值的指针的右值，第一个const代表引用绑定的指针所指向的值是带有const的
const int* const&& x = std::move(e); //const右值引用绑定到指向const值的指针的右值
int* const&& x = std::move(f); //const右值引用绑定到const指针的右值
const int*&& x = std::move(d); //非const右值引用绑定到指向const值的指针的右值
const int* const& x = std::move(g);
const int* const&& x = std::move(g); //对于指向const变量的const指针的右值可以使用const左值引用或const右值引用来绑定，第一个const不能省略！
```



# 函数指针
函数指针保存一个函数的地址，是指向函数的指针。
对于函数而言，函数名称即为函数的地址，可直接赋值给函数指针。函数指针亦可直接使用函数语法调用。

函数相关指针语法：

- 一般函数指针

	```cpp
	// 定义
	返回类型 (*指针名)(参数类型) = 函数名;

	// 使用
	指针名(参数);
	```

- 返回函数指针的函数

	```cpp
	// 定义
	所指向函数的返回类型 (*函数名(函数参数表))(所指向函数的参数表);

	// 使用
	符合所指向函数的函数原型的函数指针 = 函数名(实参);
	```

函数指针语法较为复杂，可使用`typedef`/`#define`等语法简化函数指针的表达：

- 使用`typedef`关键字来定义函数指针。函数签名被定义为一个类型。
- 使用`#define`宏来定义指针，宏只做简单的内容替换(需要注意运算符优先级)。

示例：

```cpp
int getNum(int a)
{
	reuturn a;
}

// 直接定义函数指针
int (*p1)(int) = getNum;

// 使用typedef关键字定义类型
typedef int (*P2)(int);
P2 p2 = getNum;

// 使用宏定义函数指针
#define P3(p) int (*p)(int)
P3(p3) = getNum;
```

## 成员指针
**成员指针**是指向类内成员函数的一类特殊的函数指针。
普通函数指针/静态成员函数指针为单倍指针大小，而成员指针在不同的C++实现中存在不同的大小：

- 在g++/clang++中，成员指针为双倍普通指针大小
- 在VS中，成员指针根据继承方式的不同可能出现单倍大小、双倍大小、三倍大小甚至四倍大小的指针

成员指针相关语法：

- C++普通成员函数指针

	```cpp
	// 定义
	返回类型 (类名::*指针名)(参数表) = &类名::函数名;

	// 使用
	(类实例名.*指针名)(实参);
	```

- C++静态成员函数指针(类似于普通函数指针)

	```cpp
	// 定义
	返回类型 (*指针名)(参数表) = &类名::函数名;
	返回类型 (*指针名)(参数表) = &(类名::函数名)

	// 使用
	指针名(实参);
	(*指针名)(实参);
	```

示例：

```cpp
#include <iostream>

using namespace std;

class A
{
public:
	int m = 100;
	int getNum(int);
	static int getZero(int);
};

int A::getNum(int num)
{
	return num;
}

int A::getZero(int)
{
	return 0;
}

int getOne(int)
{
	return 1;
}

int main()
{
	A a;
	P p = getOne;
	T(s) = A::getZero;
	int (A::*x)(int) = &A::getNum;
	cout << p(0) << " " << s(0) << " " << (a.*x)(123) << endl;
	cout << sizeof(p) << " " << sizeof(s) << " " << sizeof(x) << endl;
	return 0;
}
```

输出结果：(gcc 4.9.1 & ArchLinux 64bit)

```
1 0 123
8 8 16
```

输出结果：(VS 2013 & Windows 8.1 64bit)

```
1 0 123
8 8 8
```

补充：

函数的函数名代表该函数的地址，可以直接传递给符合要求(函数签名对应)的函数指针变量，
可以像使用原函数一样使用函数指针(非静态成员函数指针除外)。
C++标准规定，非静态成员函数不是左值，因此非静态成员函数不存在表达式中从函数左值到指针右值的隐式转换，
非静态成员函数指针必须通过`&`运算符显式获得。

标准的成员指针语法是`&类名::成员名`，VS还允许`&(类名::普通成员名)`，
但这样的方式在更为规范的编译器(例如g++/clang++)中会报错(g++/clang++将`类名::普通成员名`视为直接访问非静态变量，因此报错)。

g++/clang++等编译环境不支持虚继承的情况下，从子类创建虚基类的成员函数指针，但VS支持这个特性；
因此g++/clang++中的函数指针始终为双倍大小，而VS中可能会随着继承方式的变化而变化。
VS中多倍函数指针大小的详情：

- 单倍指针

	对于非派生类、单继承类，类成员函数指针保存的就是成员函数的内存起始地址。

- 双倍指针

	对于多重继承类，类成员函数指针保存的是成员函数的内存起始地址与this指针调整值。(GCC/Clang对于所有函数指针采用此类处理方式)
	因为对于多继承类的类成员函数指针，可能对应于该类自身的成员函数，或者最左基类的成员函数，这两种情形都不需要调整this指针。
	如果类成员函数指针保存的其他的非最左基类的成员函数的地址，
	根据C++标准，非最左基类实例的开始地址与派生类实例的开始地址肯定不同，所以需要调整this指针，使其指向非最左基类实例。

- 三倍指针

	对于多重继承且虚继承的类，类成员函数指针保存的就是成员函数的内存起始地址、this指针调整值、虚基类调整值在虚基表(vbtable)中的位置共计3项。
	以常见的"菱形虚继承"为例。最派生类多重继承了两个类，称为左父类、右父类；两个父类共享继承了一个虚基类。
	派生类的成员函数指针可能保存了这四个类的成员函数的内存地址。
	如果成员函数指针保存了派生类或左父类的成员函数地址，则不需要调整this指针值。
	如果如果成员函数指针保存了右父类的成员函数地址，则this指针值要加上一个偏移值，指向右父类实例的地址。
	如果成员函数指针保存了虚基类的成员函数地址，由于C++类继承的复杂多态性质，
	必须到派生类虚基表的相应条目查出虚基类地址的偏移值，依此来调整this指针指向虚基类。

- 四倍指针

	C++标准允许一个仅仅是声明但没有定义的类(forward declaration)的成员函数指针，
	可以被定义、被调用。这种情况下，实际上对该类一无所知。这称作未知类型(unknown)的成员函数指针。
	该类的成员函数指针需要留出4项数据位置，分别用于保存成员函数的内存起始地址、this指针调整值、
	虚基表到类的开始地址的偏移值(vtordisp)、虚基类调整值在虚基表(vbtable)中的位置，共计4项。



# template (模板)
`泛型`在C++中的实现被称为**模版**`template`，模版可以用在类和函数中。模板是C++中编译时多态的一类形式。

- 当模版用在函数中时，调用模版函数时可以不显式指定模版类型，编译器会根据调用函数的参数类型进行自动推导。
此外，不能给一个模版类型指定两种不同的类型。
- 当模板函数在接收特定参数时如果与已有的普通函数的原型相同，则会优先调用普通函数的实现。

示例：

```cpp
#include <iostream>

using namesapce std;

template <class T>
T get(T t, T c)
{
	return t;
}

int main(void)
{
	// 正确，显式指定模版函数的模版类型为int
	cout << get<int>(123, 123) << endl;

	// 正确，根据调用函数时传入的参数推导出模版类型为int
	cout << get(123, 123) << endl;

	// 错误，没有显式指定模版类型时，对于同一个类型传入模版的参数必须类型完全相同，
	// 而 get(123, 12.3) 会让编译器推导为 get(int, double)
	//cout << get(123, 12.3) << endl;

	// 正确，如果在调用模版函数时显式指定了模版类型，则对于同一个模版类型可以使用兼容的参数类型(不一定要完全相同)，
	// 编译器会自动进行隐式的强制类型转换
	cout << get<int>(123, 12.3) << endl;

	return 0;
}
```

模板可以应用于整个类或类内的某个函数：

- 当模版用在类中时，则该类在实例化时必须显式指定模版的类型。
- 当模版用在类内部的某个成员函数中时，带有模版函数的类实例化方式与普通类无异，
而该类的成员模版函数使用方式类似于普通模版函数，可以不显式地指定模版类型而让编译器来推导。

## 模版编译
C++模版属于**编译时多态**，模版代码在编译时即生成完毕。

- 当编译器遇到模版定义时，**不**直接生成代码，而是在实例化了一个模版的特定版本时才会根据模版实參类型生成特定的代码。
- 为了在编译时生成特定的模版代码，编译器需要模版函数/模版类成员函数的**定义**，而不仅仅是声明。
- 模版类成员函数/模版函数的定义与声明需要在**同一个**文件中，**默认情况下**，
模版函数/模版成员函数**不支持**定义与声明拆分在**不同**的文件中。

## 模版定义与声明分离
受限于模板机制的实现，C++中的模版类成员函数/模版函数**不能**拆分到不同文件中。

若预先知道模版会使用哪些具体的模板参数并以此进行实例化，则可以在源码文件中**显式实例化特定类型的模版**，
则该类型的模版函数便会在编译到该源码文件时生成，以此来实现模版定义与声明分离。

示例：

文件`test.h`:

```cpp
template <class T>
class Test
{
public:
	T get();

	template <class V>
	V get(V v);
};
```

文件`test.cc`:

```cpp
#include "test.h"

// 显式声明特定类型的模版
template class Test<int>;
// 对于模板类的模板成员函数，则需要为模板类指定模板参数
template int Test<int>::get(int num);

template <class T>
T Test<T>::get()
{
	return 100;
}

template <class T>
template <class S>
S Test<T>::get(S s)
{
	return s;
}
```

文件`main.cc`:

```cpp
#include "test.h"
#include <iostream>

using namespace std;

int main(void)
{
	cout << Test<int>().get() << endl; //正确
	cout << Test<double>().get() << endl; //编译报错，提示 undefined reference to `Test<double>::get()'
	cout << Test<int>().get(100) << endl; //正确
	cout << Test<int>().get(100.0) << endl; //编译报错，提示 undefined reference to `double Test<int>::get<double>(double)'
	cout << Test<double>().get(100) << endl; //编译报错，提示 undefined reference to `int Test<double>::get<int>(int)'
	return 0;
}
```

模板类内的成员模板函数函数定义较为复杂，需要同时指定类的模板参数以及自身的模板参数。

## 模版的高级用法
- C++的模版能够接收类型形参和部分非类型形参，模版的非类型形参只能是整形、指针和引用，比如`int a`可以作为模版的形参，
但`double a`、`string a`则不可以，而`double* a`、`string* a`则可以，对象的引用和指针是符合要求的。
- 调用非类型模板形参的实参必须是一个常量表达式，即他必须能在编译时计算出结果。
需要注意的是，任何局部对象，局部变量，局部对象的地址，局部变量的地址都不是一个常量表达式，都不能用作非类型模板形参的实参。
- 全局指针类型，全局变量，全局对象也不是一个常量表达式，不能用作非类型模板形参的实参。
- 全局变量的地址或引用，全局对象的地址或引用`const`类型变量是常量表达式，可以用作非类型模板形参的实参。
- `sizeof`表达式的结果是一个常量表达式，也能用作非类型模板形参的实参。
- 模版函数如果使用了非类型形参，则在调用该模版函数时必须显式指定模版实参，因为编译器只能推导模版类型，非类型的模版参数需要显式地指定。

## 模版形参默认值
- C++11之前可以为**模版类**的**类型形参**提供默认值，但**不能**为**模板函数**的**类型形参**提供默认值。
模板函数和模板类都**可以**为模板的**非类型形参**提供默认值。
- C++11之后，无论模版函数或是模版类的类型形参和非类型形参都可以拥有默认值(`g++ 4.9.2`和`vs 2013`测试通过)。
- 模版形参默认值的用法类似于函数参数形参默认值，即从第一个有默认值的形参开始，之后的形参都应拥有默认值，并且形参默认值在声明或定义只需要出现一处即可。
- 即使一个模版类的所有模版形参都拥有默认值，全部采用默认参数来实例化这个模版类时类名之后依然需要有一对空的尖括号`>`来表示实例化的是一个模版类。

## 模板与重载
C++中模板是在编译时根据实例化时使用的**模版参数**编译成对应的函数。
C++作为编译性语言，模板是在编译期实现的，属于编译时多态的一种。

- 类模板与重载

	对于模板类而言，如果一个模板类成员函数(无论是否静态)在确定了类型之后与原有的成员函数原型发生冲突则在编译时就会报错。
	若模板类成员函数在使用某种类型时**可能**与已有的函数原型发生冲突，但只要没使用该类型，就能通过编译。
	如下代码所示：

	文件`test.h`

	```cpp
	template <class T>
	class Test
	{
	public:
		T get(T t1, T t2) { return t1 + t2; }
		int get(int num1, int num2) { return num1 + num2 + 1; }
	};
	```

	文件`test.cc`

	```cpp
	#include "test.h"

	int main(void)
	{
		Test<int> t; //编译报错，提示"error: ‘int Test<T>::get(int, int) [with T = int]’ cannot be overloaded"
	}
	```

	当`Test`类使用`int`型作为模板实例化类型时，与原有函数原型发生冲突。

- 成员函数模板与重载

	对于成员函数模板而言，**允许**成员模板函数与原有的类内成员函数具有**完全相同**的函数原型。
	调用时，默认优先调用普通成员函数，但可以通过显式写明模板参数的形式调用成员模板函数。
	示例：

	文件`test.h`

	```cpp
	class Test
	{
	public:
		template <class T>
		T get(T t1, T t2) { return t1 + t2; }
		int get(int num1, int num2) { return num1 + num2 + 1; }
	};
	```

	文件`test.cc`

	```cpp
	#include "test.h"
	#include <iostream>

	using namesapce std;

	int main(void)
	{
		Test t; //带有成员模板函数的类实例化方式与普通类完全相同
		cout << t.get(100, 100) << endl; //输出201，默认调用非模板函数
		cout << t.get<int>(100, 100) << endl; //输出200，显式指定模板参数时调用模板函数
	}
	```

## 模版特化
C++支持`模版特化`，即对于特定的模版参数类型可以指定其实现。
如有以下模版类，有两个模版参数`T`和`S`：

```cpp
template <class T, class S>
class Template
{
	/* code */
};
```

可以指定其模版类型为某种类型时的类定义，如需要特化模版皆为参数为`int`型时的类定义可以写成：

```cpp
template <>
class Template<int, int>
{
	/* code */
};
```

特化时显式指定`所有`模版参数的类型被称为`完全特化`，类模版还支持`偏特化`，即只指定一部分的模版类型参数：

```cpp
template <class T>
class Template<T, int>
{
	/* code */
};
```

类`Temp`的后一个模版参数的类型被显式指定为`int`，而模版参数`T`依然由用户指定。
除了`模版类`之外，C++中模版函数也同样支持**模版特化**。

如以下模版函数：

```cpp
template <class T, class S>
T func(T t, S s)
{
	/* code */
}
```

若需要特化其模版参数全为`int`型，则可以写成：

```cpp
template <>
int func<int, int>(int t, int s)
{
	/* code */
}
```

模版类型参数也可省略，写成：

```cpp
template <>
int func(int t, int s)
{
	/* code */
}
```

需要注意，模版函数**不支持**`偏特化`，即以下的写法**不能**通过编译：

```cpp
template <class T>
T func<T, int>(T t, int s) //error
{
	/* code */
}
```

C++不允许模版函数偏特化，`偏特化`的模版函数在编译时会报错，提示`error: function template partial specialization is not allowed`。

## 模版递归
C++中，模版函数与模版类皆可正常进行递归展开，模版递归需要使用**模版特化**作为递归结束标志，防止模版被无限展开。

使用递归模版函数计算**斐波那契数列**：

```cpp
#include <iostream>

template <int num>
int fibonacci()
{
	return fibonacci<num - 1>() + fibonacci<num - 2>();
}

template <>
int fibonacci<0>()
{
	return 0;
}

template <>
int fibonacci<1>()
{
	return 1;
}

int main(void)
{
	std::cout << fibonacci<10>() << std::endl;
	return 0;
}
```

由于模版展开是在**编译时**进行的，利用模版递归特性可以让一些计算在编译时发生，提升代码效率。

利用模版在编译时计算**斐波那契数列**：

```cpp
#include <iostream>

template <int num>
class Fibonacci
{
public:
	// 利用静态变量保存计算结果，静态变量值在编译时计算完成
	// 也可以使用"const static"变量，初始化代码可以直接写在类的内部
	static int value;
};

template <int num>
int Fibonacci<num>::value = Fibonacci<num - 1>::value + Fibonacci<num - 2>::value;

template <>
class Fibonacci<0>
{
public:
	static int value;
};
int Fibonacci<0>::value = 0;

template <>
class Fibonacci<1>
{
public:
	static int value;
};
int Fibonacci<1>::value = 1;

int main(void)
{
	// 使用g++能正常输出结果：55，但clang++并没有在编译时确定静态变量的值，输出结果：0
	// 静态成员变量value的值在编译时已经确定，不在运行时计算，更高效
	std::cout << Fibonacci<10>::value << std::endl;
	return 0;
}
```

## 变长模版 (C++11)
C++11加入了**变长模版**特性，使用`template <typename... T>`或`template <class... T>`来表示有数目不定的模版参数。
定义变长模版变量写成`T... arg_name`，调用变长模版变量也要在参数名称后加上引号，写成`arg_name...`。
使用`sizeof...`操作符可以计算模版参数包的个数(**不是**类型大小)。
通过模版类型的**自动推导**，变长的模版参数包可以使用**递归**的方式逐一取出参数。

示例，计算一个变长序列之和：

```cpp
#include <iostream>

using namespace std;

//定义模版函数的推导终止点，防止无限递归
template <class T>
T sum(const T& t)
{
	return t;
}

template <class T, class... Args>
T sum(const T& t, const Args&... args)
{
	return sum(args...) + t;
}

int main(void)
{
	cout << sum(100) << endl;
	cout << sum(100, 200) << endl;
	cout << sum(100, 200, 300) << endl;
	cout << sum(100, 200, 300, 400) << endl;
	return 0;
}
```

输出结果：

```
100
300
600
1000
```

## 禁止特定类型的模板参数
C++11之后，可以禁止接受某种类型做为模板参数，使用`delete`关键字将模板函数的某种实现标记为**删除**的，示例：

```cpp
template <class T>
T test(T&& t)
{
	return t;
}

template <>
int test(int&& num) = delete;

test<int>(100); //错误，提示"无法引用，函数xxx是已删除的函数"
```



# _Generic (C11)
在C11中，引入了新关键字`_Generic`，使用`_Generic`可以一定程度上实现**泛型**功能(不过功能上远远不能与C++的模板机制相比)。

`_Generic`语法如下：

```c
_Generic(expr, type_1: expr_1, type_2: expr_2, ..., default: expr_default)
```

- `expr`为一个表达式。
- `type_1`、`type_2`为类型。
- `expr_1`、`expr_2`为对应类型的返回表达式。

若`expr`表达式的类型与之后类型列表中的某种类型匹配时，`_Generic()`语句会将匹配的类型的表达式作为语句结果，
若`expr`表达式与类型列表中所有类型都不匹配，则使用`default`对应的表达式作为语句结果。

基本用法示例：

```c
#define G(x) _Generic(x, int: 100, double: 200.0)

int a = 0;
double b = 0.0;

printf("%d\n", G(a)); //打印 100
printf("%f\n", G(b)); //打印 200.000000
```

`default`可以不设定，但编译时若`expr`没有匹配的类型则会**报错**。

```c
#define G(x) _Generic(x, int: 100, double: 200.0)

float s = 0;

printf("%d\n", G(s)); //报错 error: ‘_Generic’ selector of type ‘float’ is not compatible with any association
```

使用`_Generic`可以一定程度上实现模版函数：

```c
#include <stdio.h>

struct T
{
	int data;
};

_Bool max_int(const int num_1, const int num_2)
{
	printf("call max_int\n");
	return num_1 > num_2;
}

_Bool max_double(const double num_1, const double num_2)
{
	printf("call max_double\n");
	return num_1 > num_2;
}

_Bool max_T(const struct T t_1, const struct T t_2)
{
	printf("call max_T\n");
	return t_1.data > t_2.data;
}

// 若x大于y，返回1，否则返回0
#define MAX(x, y) \
	_Generic(x, int: max_int, double: max_double, struct T: max_T)(x, y)

int main(int argc, char** argv)
{
	// MAX宏根据不同的具体参数类型选择不同的实现
	if (MAX(200, 100))
		printf("True\n");

	if (MAX(200.0, 100.0))
		printf("True\n");

	// 传统的宏能够实现基础类型的比较，但对于自定义结构类型无能为力
	if (MAX((struct T){ 200 }, (struct T){ 100 }))
		printf("True\n");

	return 0;
}
```

输出结果：(GCC 6.1.1 && ArchLinux x64)

```
call max_int
True
call max_double
True
call max_T
True
```



# assert (断言)
**断言**是调试中常用的一种宏，常用于**条件检查**。

## 断言宏
**断言**是一种**预处理宏**，其定义位于头文件`assert.h`中，不同平台的实际定义不尽相同，但表达式结构类似，示例：

```cpp
assert(expr);
```

`assert`接受一个表达式作为条件，表达式为真(非0)时，程序正常执行，表达式为假(值为0)，assert输出信息并终止程序的执行。

## 静态断言 (C11)
C11中引入了**静态断言**关键字`_Static_assert`，与普通的断言不同，**静态断言**不是宏，而是一个语言级别的**关键字**。
静态断言在编译时生效，接受常量表达式，若接收的常量表达式值为假，则在编译阶段直接报错。

`_Static_assert`关键字用法示例：

```cpp
_Static_assert(expr, error_str);
```

若`expr`表达式为假，则`error_str`则作为编译错误信息被输出。

## 静态断言 (C++11)
C++11中同样引入了**静态断言**关键字`static_assert`，用法与C11中的`_Static_assert`相同。

- 使用静态断言实现范型约束

	**静态断言**搭配标准库中的模版类`std::is_base_of<Base, Der>`，
	能够实现类似`Java`、`C#`等高级语言中的范型约束效果。
	示例：

	```cpp
	#include <iostream>

	using namespace std;

	class Base { };

	class Der : public Base { };

	class Private : Base { };

	class Other { };

	int main(void)
	{
		// Right
		static_assert(is_base_of<Base, Der>::value, "Need class Base.");

		// Right
		static_assert(is_base_of<Base, Private>::value, "Need class Base.");

		// error: static_assert failed "Need class Base."
		static_assert(is_base_of<Base, Other>::value, "Need class Base.");

		return 0;
	}
	```

	通过静态成员`std::is_base_of<Base, Der>::value`来判定作为参数的两个类是否存在继承关系。
	类`Base`与`Der`存在继承关系，因而编译通过，但类`Other`与`Base`不存在继承关系，因而编译报错。

	需要注意的是，**私有继承**虽然不支持转型操作，但继承关系依然存在，能够通过继承关系检测。



# auto 类型推导
C++11中，标准重新定义了`auto`关键字的作用，auto关键字现在用于推导变量的类型。

使用auto推导类型时，需要注意：

1. `auto`默认得到目标变量的值复制。
1. `auto&`得到目标变量的引用，只能绑定到左值上。
1. `const auto&`得到目标变量的const引用，可以绑定任何值，但得到的内容为const，不可修改。
1. `const auto&&`得到const右值引用，只能绑定右值。
1. `auto&&`得到目标变量的**通用引用**`universal reference`，能够绑定到**任何值**，同时**不带有**const限制。

`auto&&`与普用右值引用不同，普通右值引用只能绑定到右值上，示例：

```cpp
int a = 0;
auto&& b = 0; //绑定右值
auto&& c = a; //绑定左值
c = 1;
cout << a << endl; //打印输出："1"，c为a的引用，而不是值复制
cout << &a << " " << &c << endl; //打印输出结果相同，c和a为同一块地址，即同一个变量
```



## Lambda
C++11中引入了Lambda表达式，语法格式为：

```cpp
[当前作用域变量捕获方式](参数表) { 函数体; }; //标准形式
[当前作用域变量捕获方式] { 函数体; }; //无需参数的形式
[当前作用域变量捕获方式](参数表) -> 返回类型 { 函数体; }; //显式指定返回值的形式
```

需要注意的是，与普通函数相同，如果需要表达式有返回值则需要在函数体中使用`return`语句返回值。
与Java/C#等语言不同，C++中的Lambda**不能**省略参数类型，也不能在函数体只有一句的时候省略函数体外的花括号。

## 复用 Lambda
如果需要重复使用一个Lambda，可将其构造为函数对象`std::function`：

```cpp
std::function<返回类型(参数表)> 函数对象名 = [当前作用域变量引用方式](参数表) { 函数体; };
```

需要注意的是，函数对象是一个**类实例**，不是函数指针，但如果一个Lambda没有捕获任何变量，则可以与函数指针进行转化。

`std::function`重载了`bool`运算符，可用于判断函数对象是否有效：

```cpp
#include <iostream>
#include <functional>

using namespace std;

int main(void)
{
	function<void()> func;
	cout << (func ? "true" : "false") << endl; //输出"false"
	func = [] {};
	cout << (func ? "true" : "false") << endl; //输出"true"
	return 0;
}
```

## 变量捕获
Lambda可以捕获当前作用域中的变量(闭包)，`[=]`表示当前作用域的变量全部取值传递，`[&]`表示当前作用域的变量全部取引用传递。

可以只设置需要的变量，并设置不同的传递方式，如`[a, &b, c]`表示变量`a`和`c`为值传递，`b`为引用传递。
可以在传递所用变量的基础上分别设定指定变量的传递方式，如`[=, &a]`表示除了`a`之外的变量全部为值传递，
`a`为引用传递，而`[&, a]`表示除`a`外的所有变量为引用传递，`a`为值传递。
设置全局传递方式的操作符要放在设置单个变量的操作符之前，类似`[&a, =]`、`[b, &]`的写法无法通过编译。

采用值传递方式捕获的变量带有`const`属性。

Lambda表达式的参数可以是**引用**或**指针**，作为**返回值**时**不能**为引用传递，但依然可以为指针类型。
对于没有捕获变量的Lambda，可以直接转化为原生的函数指针。
Lambda与普通函数最大的区别在与Lamdba可以捕获当前作用域中的变量，而函数不可以。
一但Lambda没有捕获当前作用域中的变量，则该Lambda便可以转化为一个普通函数，即可以使用原生函数指针表示。

示例：

```cpp
#include <iostream>
#include <functional>

using namespace std;

int main(void)
{
	int a = 1;
	int b = 2;
	function<int(int, int)> test = //可以直接使用auto类型推断
			[=, &a](int x, int y) { return a = x + y + b; };
	test(1, 1);
	cout << a << endl;

	// 未捕获变量的Lambda可以转化为函数指针
	int (*get_num)(int) = [](int num) { return num; };
	cout << "Run lambda function point:" << get_num(100) << endl;

	return 0;
}
```

输出结果：(GCC 5.1.0 && ArchLinux x64)

```
4
Run lambda function point: 100
```

## C++14 中的 Lambda 新特性
C++14中，加入了模版Lambda，支持在Lambda使用**表达式**捕获作用域中的变量，
且没有捕获变量的Lambda可以与函数指针进行转化(不是`std::function`)。

- C++11中，Lambda中的参数必须显式指定参数的类型，C++14中，参数的类型可以使用`auto`关键字，
编译器会对所有的被使用的该表达式进行参数类型推断，然后根据使用的参数类型编译出对应的Lambda实例。
- C++11中，对变量的捕获包括值捕获和左值引用捕获两种，C++14中，Lambda中支持使用**表达式**捕获，
通过简单的表达式进行一些捕获值初始化`lambda capture initializers`，
或是对捕获变量重命名(设置全局传递方式的操作符依然要放在最前面)。

示例：

```cpp
#include <iostream>

using namespace std;

int main(void)
{
	// 模版Lambda表达式
	auto lambda1 = [](auto num) { return num; };
	cout << "Use int as args: " << lambda1(100) << endl;
	cout << "Use string as args: " << lambda1("string") << endl;

	// Lambda表达式支持表达式捕获
	int a = 100, b = 200, c = 300;

	// 以捕获值的方式捕获变量a，并用a的值加上50并命名为num1，然后将b的引用命名为num2
	auto lambda2 = [=, num1 = a + 50, &num2 = b]() { num2 = num1 + c; };
	lambda2();
	cout << "After run lambda2, the value b is: " << b << endl;

	// 捕获变量名称可以与原始变量相同(局部变量掩盖原则)
	// 捕获表达式中可以使用C++11中引入的统一初始化语法
	// lambda2与lambda3等价
	auto lambda3 = [=, a { a + 50 }, &b = b] { b = a + c; };
	lambda3();
	cout << "After run lambda3, the value b is: " << b << endl;

	return 0;
}
```

输出结果：(GCC 5.2.0 && ArchLinux x64)

```
Use int as args: 100
Use string as args: string
After run lambda2, the value b is: 450
After run lambda2, the value b is: 450
```



# STL 容器
容器`Containers`是用来存储和管理数据的数据结构。容器一般分为序列式容器`Sequence Containers`和关联式容器`Associative Containers`。

- 常用的**序列式容器**有`vector(向量)`、`list`(双向链表)、`deque`(双向队列)。
- 常用的**关联式容器**有`set`(集合)、`map`(映射)、`multiset`(多重集合)、`multimap`(多重映射)。

以上的7中容器对象都有以下成员方法：

```cpp
bool empty() const; //判断容器是否为空
size_type max_size(); //返回容器最大能存储的元素个数
size_type size(); //返回容器中当前已经存储的元素的数量
void swap(contain_type &container); //交换当前容器对象与container容器对象中的内容
void clear(); //清空容器中的内容
iterator erase(iterator position); //擦除指定迭代器位置的内容
iterator erase(iterator first, iterator last); //擦除[first, end)位置的内容
```

## 迭代器
各类容器中都内置了迭代器，可通过以下函数创建迭代器：

```cpp
iterator begin(); //返回一个指向首元素的迭代器
iterator end();
iterator rbegin(); //返回一个指向首元素的迭代器，逆序遍历
iterator rend();
```

在C++11之后，可以使用新的`std::begin()`和`std::end()`函数来创建迭代器。
以`vector`为例，创建和使用迭代器：

```cpp
vector<int> vector_int; //创建容器对象
vector<int>::iterator iterator_int; //创建迭代器对象
iterator_int = vector_int.begin(); //初始化迭代器
iterator_int = std::begin(vector_int); //C++11风格的迭代器初始化
++iterator_int; //迭代器向下移动一个位置
--iterator_int; //迭代器返回上一个位置
*iterator_int; //取出迭代器在当前位置的内容
cin >> *iterator_int; //向迭代器指代的位置中输入内容
std::advance(iterator_int, num); //像iterator_int增加指定的偏移量
```

## 序列式容器
序列式容器中元素的次序与元素的值无关，只与元素插入的顺序有关。

序列式容器都有以下常用成员函数：

```cpp
void pop_back(); //删除容器尾部的最后一个元素
void push_back(const T& x); //在容器尾部添加一个元素
reference front(); //返回容器内首个元素的引用(可以通过此函数修改元素的值)
reference back(); //返回容器最末元素的引用
iterator insert(iterator position, const T& x);
void insert(iterator position, size_type n, const T& x);
template <class InputIterator>
void insert(iterator position, InputIterator first, InputIterator last);
```

序列式容器都提供了以下构造函数，以`vector`为例：

```cpp
vector();
vector(size_type num, const TYPE& val); //使用num个值为val的元素初始化vector
vector(const vector& from);
vector(input_iterator start, input_iterator end); //使用某个已存在的vector的[start, end)来构建一个新的vector
```

- *vector* 容器特点

	`vector`容器是数组式的容器类型。
	`vector`容器中存储的数据元素被放在一块连续的内存中。
	`vector`容器支持**随机存取**，可以通过数组式的下标(即`[]`操作符)进行元素访问、修改。

	`vector`容器虽支持`insert()`等函数来进行插入操作，
	但由于内部采用线性结构，因而`insert()`函数在头部或是中间插入元素时需要进行大量复制操作，
	插入效率很低，在执行头部、中部删除元素操作时也同样效率低。

- *list* 容器特点

	`list`容器采用**双向链表**实现。
	`list`容器存储的元素所处的内存空间不连续。
	由于链表的特性，元素之间是通过指针相连的，因而`list`容器在任意位置插入和删除元素时效率都很高。

	`list`容器**不支持**随机存取，不可使用`[]`操作符访问元素，同时相比`vector`容器消耗的内存更多。
	`list`容器有着一些`vector`没有的方法，比如`pop_front()`、`push_front(const T &x)`、`remove(const T &value)`等。
	使用`remove()`方法可以移除容器中所有值为`value`的元素。

- *deque* 容器特点

	`deque`容器为**双向队列**。
	`deque`兼顾了`list`和`vector`的优点，能够方便地增加、删除元素，也能够使用`[]`操作符随机存取元素。
	`deque`的缺点是需要消耗较高的内存。

## 关联式容器
关联式容器通过键值`key`来存取元素，元素次序与插入顺序**无关**。

- 关联式容器**不提供**`front()`、`back()`、`push_front/push_back(const T&)`、`pop_front/pop_back()`之类的操作。
- 关联式容器可以进行比较，需要定义`<`操作符，所有作为关联式容器`key`的类型都必须重载`<`运算符，其它操作符不作要求。
- 关联式容器提供`clear()`和`erase()`函数，但返回值为`void`而不是下一个元素的迭代器。

常见的关联式容器特点：

- *set*、*multiset* 容器特点

	`set/multiset`容器保存键值，对应数学概念中的`集合`。
	`set/multiset`的实现采用的平衡二叉搜索树，插入、查询、删除等操作时间复杂度均为`O(lgN)`。
	`set`不允许重复值，但`multiset`允许重复值。

- *map*、*multimap* 容器特点

	`map/multimap`容器同时保存键值和实际值，每一个元素都是一个`pair<key, value>`类型。
	`map`容器不允许相同键值`key`的元素，但`multimap`允许。
	`map`容器可以使用数组下标形式(`[]`操作符)来获取指定键值的元素中的实际值。
	`multimap`由于键值可以重复，一个键值可以对应多个实际值，因而不能采用下标的形式获取实际值。

	`pair`类型中有两个成员，`first`和`second`，分别保存键值和实际数据。
	通过访问`first`和`second`两个成员可以获取键值和实际数据。
	使用`find()`函数可以查找某个键值，返回一个迭代器，通过遍历该迭代器可以获取某个键值的所有对应值。

	可以通过`lower_bound()`、`upper_bound()`等函数获取迭代器，用于遍历元素。
	与`STL`的迭代器相同，`lower_bound()`返回指向参数键值的第一个元素位置的迭代器，
	而`upper_bound()`返回指向参数键值最后一个元素的下一个元素位置的迭代器。

`map`使用注意事项：

- 对于`map`等关联式容器来说，key若为指针类型，则将指针的值(指针包含的地址)作为键值，而非指针所指向的内容。
因而两个内容相同的不同数组对`map`而言就是两个不同的键值。
- 并非所有类型均可作为key，作为key的类型必须重载`<`运算符，否则会出现编译错误：
`二进制“<”: 没有找到接受“xxx”类型的左操作数的运算符(或没有可接受的转换)`
- 一些类型已经默认重载了`<`运算符如`std::string`、`QString`等，可以直接作为key使用。
- 当访问容器的索引越界时，**不会**像其它高级语言如C#、Java一样抛出异常，而是返回对应类型的零值。



# Smart Pointer (智能指针)
C++中除了手动使用`new`、`delete`操作符来进行动态内存管理之外，还可以使用智能指针管理动态内存，使用智能指针管理的动态内存会在不被需要时自动释放。

`Boost`库中提供了六种智能指针用来管理动态内存，分别是`shared_ptr`、`shared_array`、`scoped_ptr`、`scoped_array`、`weak_ptr`、`intrusive_ptr`，定义在`/usr/include/boost/smart_ptr/`路径下对应名称的头文件中。

在C++11中，`boost`库中的`shared_ptr`、`weak_ptr`被纳入了标准库，定义在`/usr/include/c++/版本号/memory`头文件中。
C++11之前，标准库中可以使用`auto_ptr`智能指针，在C++11之后，标准库中增添了`shared_ptr`、`unique_ptr`、`weak_ptr`等智能指针。
原先的`auto_ptr`已经不推荐使用。

需要注意的是，`Boost`库与标准库中的同名类是不能相互转换的(即`std::shared_ptr`不能转换为`boost::shared_ptr`)。

## 智能指针的一般性用法
智能指针重载了`->`操作符，使开发者可以使用此操作符访问智能指针保存的对象的公有成员，对于智能指针自身的成员，依然使用`.`操作符访问。
以`shared_ptr`为例：

```cpp
shared_ptr<T> ptr; //创建一个空的、尚未初始化的动态指针
shared_ptr<T> ptr(new T(args)); //创建智能指针对象并开辟内存进行初始化，无参数时调用默认的构造函数
shared_ptr<T> ptr(T* t); //由指针t所指向的动态内存绑定到智能指针(如果t为空指针，则智能指针绑定空内容)
ptr->...; //访问智能指针指向的动态内存对象的公有成员
ptr.reset(); //重置智能指针
```

智能指针重载了`operate bool()`支持使用布尔运算形式展示指针是否为空。
智能指针重载了`operate ==()`支持与其它智能指针以及`nullptr`进行比较。

示例：

```cpp
shared_ptr<T> ptr0;
shared_ptr<T> ptr1(new T(args));
ptr0 ? true : false; // false
ptr1 ? true : false; // true
ptr0 == nullptr ? true : false; // true
ptr0 == nullptr ? true : false; // false
```

标准库中的各类智能指针特性：

- `std::auto_ptr`(已过时)

	一块动态内存只能绑定一个`auto_ptr`，若将一个绑定了动态内存的`auto_ptr`复制给另一个`auto_ptr`则动态内存的所有权会被转移到新的`auto_ptr`上，
	旧的`auto_ptr`不再指向原先的动态内存。

- `std::unique_ptr`

	来自于`boost::scoped_ptr`，类似于`auto_ptr`，但`unique_ptr`的限制更多，
	一块动态内存只能绑定一个`unique_ptr`，同时`unique_ptr`不能进行复制。

- `std::shared_ptr`

	来自于`boost::shared_ptr`，基于**引用计数**的共享智能指针。
	一块动态内存可以被多个`shared_ptr`绑定。
	每增加一个智能指针的绑定，则引用计数加1，当引用计数为0时释放指向的动态内存。
	`shared_ptr`的内存管理完全交由编译器完成，不能手动释放`shared_ptr`管理的动态内存(没有`release()`成员函数)。

	`shared_ptr`使用`make_shared<T>(args)`函数进行构造。
	使用`reset()`成员函数会将当前智能指针管理的动态内存引用计数减1，如果引用计数为0则释放动态内存。
	`shared_ptr`的`reset()`成员函数可以带有参数，参数可以是`new`构造函数或是对象指针，
	作用是将原先的托管对象引用计数减1然后管理新的对象(新对象引用计数加1)。

- `std::weak_ptr`

	来自于`boost::weak_ptr`，为了解决`shared_ptr`中的**循环引用**问题而引入的**弱引用**智能指针。
	`weak_ptr`不能单独绑定一块动态内存(即不能新建动态内存初始化`weak_ptr`)，而是由`shared_ptr`转化而来。

`shared_ptr/weak_ptr`使用：

- `weak_ptr`可以使用构造函数与`shared_ptr`相互转换(即以已有的`shared_ptr`对象为参数构造`weak_ptr`对象)，
一块动态内存被`weak_ptr`智能指针绑定或是绑定该动态内存的`weak_ptr`被销毁不会增加/减少原有的`shared_ptr`的引用计数。
- `shared_ptr`和`weak_ptr`都没有`release()`成员函数，即不能手动释放动态内存。`weak_ptr`不能直接调用指向对象的成员函数，
调用指向对象的成员函数之前需要先使用`weak_ptr`自身的`lock()`方法将自身转变为`shared_ptr`，然后再调用指向对象的成员函数。

## 智能指针的转型
C++的类型转换操作符`dynamic_cast<>()`、`static_cast<>()`、`const_cast<>()`**不能**用于智能指针对象的转换，
智能指针实际是一个包含了指针的容器对象，并不能简单地转换为普通指针类型。
将智能指针对象进行转型需要使用`dynamic_pointer_cast<>()`、`static_pointer_cast<>()`、`const_pointer_cast<>()`，
其中的模版参数为目标对象的类型(不是指针类型)。

## 改变做为形参传入的智能指针所指向的内容
当智能指针做为形参时，如果需要改变指针指向的内容，则需要像普通指针一样，
将新的内容赋值到`*智能指针对象`上(此项操作需要智能指针已被初始化且被分配了足够的内存)。

如果智能指针是`shared_ptr`，则还需要考虑到智能指针保存内容的生命周期。

若传入尚未初始化的智能指针，需要在函数内对其进行初始化，且还要保证外部能使用这个指针，此时需要传递智能指针的引用或地址，
保证函数内部能访问到原始的智能指针，否则进行的操作都是对形参复制的智能指针进行的，不会改变外部的智能指针未被初始化的状态。

例如：

```cpp
#include <iostream>
#include <memory>
#include <stdio.h>

using namespace std;

void init(shared_ptr<int> temp) //如果需要函数改变传入的未初始化的智能指针，正确的方法是传入引用或是传入智能指针的地址(指针)
{
	shared_ptr<int> num(new int);
	*num = 100;
	temp = num;
}

int main(void)
{
	shared_ptr<int> temp;
	init(temp);
	cout << *temp << endl; //错误，运行init()函数之后，外部的智能指针temp实际上并未发生变化，依然处于未初始化状态，试图访问其内容会报错
	system("pause");
	return 0;
}
```

输出结果：(VS 2015 && Windows10 x64)

```
报错，提示访问空指针(0x0000000)。
```



# std::bind()
C++11中引入该函数，来源于`boost::bind()`，作用是通过设定原有函数的某些参数值为固定值来生成具有新参数表的函数(类似`Python`中的部分应用函数)，
`bind()`本质上是一个`call_adapter`。
`bind()`既可以绑定当前类的成员函数，也可以绑定全局函数/静态函数或是其他类的具有访问权限的成员函数。

## bind() 绑定普通函数

```cpp
bind(func_name, args...);
```

`bind()`用于绑定一般的函数(可直接访问的函数，比如全局函数，其他类的可访问静态成员函数)时第一个参数为需要绑定的函数名，
后面的参数为绑定函数的参数表，可以向参数表中加入对应类型的常量，
不需要绑定常量的参数可以用参数占位符`std::placeholders::_1`、`std::placeholders::_2`...或者`boost::_1`、`boost::_2`...)替代。

## bind() 绑定非静态成员函数

```cpp
bind(&class_name::func_name, 对象实例/对象指针/智能指针, args...);
```

- `bind()`用于绑定非静态成员函数时，需要通过类实例进行访问，第二个参数需要为绑定函数所在类的实例、指针或是智能指针。
- `bind()`绑定当前类的成员函数可以直接传递`this`指针。

实例代码：

```cpp
#include <iostream>
#include <functional>
#include <memory>

using namespace std;

int get0(int a)
{
	return a;
}

class A
{
public:
	A(int num) : num(num) {};
	int get(int, int);
	int num;
};

int A::get(int a, int b)
{
	return num = a;
}

int main(void)
{
	A a1(888);
	A* a2 = new A(888);
	shared_ptr<A> a3 = make_shared<A>(888);

	function<int()> p0 = bind(get0, 100);
	function<int(int)> p1 = bind(A::get, a1, 1, placeholders::_1);
	function<int(int)> p2 = bind(A::get, a2, 2, placeholders::_1);
	auto p3 = bind(A::get, a3, 3, placeholders::_1);
	auto p4 = bind(A::get, ref(a1), 1, placeholders::_1);

	cout << p0() << endl;
	cout << p1(0) << " p1()调用后num的值：";
	cout << a1.num << endl;
	cout << p2(0) << " p2()调用后num的值：";
	cout << a2->num << endl;
	cout << p3(0) << " p3()调用后num的值：";
	cout << a3->num << endl;
	cout << p4(0) << " p4()调用后num的值：";
	cout << a1.num << endl;

	delete a2;

	return 0;
}
```

输出结果：(GCC 5.1.0 && ArchLinux x64)

```
100
1 p1()调用后num的值：888
2 p2()调用后num的值：2
3 p3()调用后num的值：3
1 p4()调用后num的值：1
```

将类实例作为参数进行绑定的时候，对类实例进行的是值传递，即复制一个类对象，
因此调用`bind()`生成之后的函数对象不会对原先的类实例进行修改(但传递类指针、类智能指针的时候，只是复制对象地址，类内存是同一块，因此修改会同步)。
若需要在`bind()`是进行对象引用传递，则可以使用`std::ref()`、`std::cref()`函数。



# boost::signals2
使用`Boost`库中的`signals2`可以实现近似C#中**委托**的效果，使用`signals2`需要包含头文件`/usr/include/boost/signals2.hpp`。
`Boost`库中的`boost::signals2`相比原先的`boost::signals`而言是**线程安全**的，原先的`boost::signals`现在已被废弃。

## 定义信号
定义信号使用`boost::signals2::signal<>`，模板参数为需要连接的函数的函数原型。
若需要连接的函数的原型为`void func(int, int)`，则定义信号时应该写成`boost::signals2::signal<void(int, int)>`。

`boost::signals2::signal`是**不可复制**的类型。

## 连接槽函数
连接槽函数使用`connect()`成员函数，该函数有两个重载，定义如下：

```cpp
connection connect(const slot_type& slot, connect_position position = at_back);
connection connect(const group_type& group, const slot_type& slot, connect_position position = at_back);
```

- 连接槽函数时改变签名

	被连接的槽函数必须要符合信号定义时的模板参数中的函数原型，必须函数原型参数个数完全相同且类型兼容(由于绑定槽函数时是传递槽函数的地址，
	因此函数默认参数被忽略，因而参数个数必须完全相同)。
	若需要绑定的函数参数表与信号定义的参数表数目不同，可以采用`std::bind()`生成具有新参数表的函数进行连接。

	若需要连接的槽函数为一个类的非静态成员函数，则也需要通过`std::bind()`将非静态成员函数绑定一个类实例之后再进行连接，
	否则会连接失败(没有实例无法访问非静态成员函数)。

	若被连接的槽函数有多个重载，则需要进行强制类型转换来转换为无歧义函数指针才能进行连接。

- `connect()`组别

	使用`connect()`函数的第二个重载进行槽函数连接时，可以在第一个参数的位置设置槽函数的组别，
	组别可以是一个整型数值(可以为负数)，不同组别之间的槽函数按照组号由小到大的顺序执行。

- `connect()`优先级

	`connect()`成员函数的最后一个参数用于设定槽函数的组内优先级，默认情况下取值为`boost::signals2::at_back`，
	多个槽函数连接时返回值为最后一个连接的槽函数的返回值，需要优先执行的槽函数可以设定为`boost::signals2::at_front`。

## 取消连接
取消连接使用`disconnect()`成员函数，该函数有两个重载，定义如下：

```cpp
void disconnect(const group_type& group); //断开指定组别的所有槽的连接
void disconnect(const T& slot); //断开指定槽
```

还可以一次性断开所有槽：

```cpp
void disconnect_all_slots();
```

需要注意的是，每次连接槽函数成功之后都会返回一个`boost::signals2::connection`对象，
通过调用该对象的`disconnect()`函数也能实现指定槽函数连接的断开。

## 获取信号返回值
信号的返回值是由合并器`combiner`管理的，在定义信号对象时，会调用`boost`默认的合并器类管理返回值，
如果需要使用自定义合成器类，则定义需要写成`boost::signals2::signal<func(type), combiner<type>>`。

定义完信号之后，可以像调用普通函数一样调用信号对象，所有被信号连接的槽函数都将会被触发(重载`()`操作符)，同时返回的一个合并器类的对象。

默认的合并器类只保存最后一次被触发的槽函数的返回值，使用`*`操作符或是`value()`成员函数可以获得合并器中保存的值。

实例代码：

```cpp
#include <boost/signals2.hpp>
#include <iostream>

using namespace std;

class A
{
public:
	boost::signals2::signal<int(int)> sig;
};

class B
{
public:
	int slot1(int, char);
	int slot1(int, int, int);
	int slot2(double, int);
};

int B::slot1(int, char)
{
	cout << "This is slot1(int, char)." << endl;
	return 100;
}

int B::slot1(int, int, int)
{
	cout << "This is slot1(int, int, int)." << endl;
	return 200;
}

int B::slot2(double, int)
{
	cout << "This is slot2." << endl;
	return 300;
}

int main(void)
{
	A a;
	B b;

	a.sig.connect(1, boost::bind(&B::slot1, b, _1, 'a'));
	boost::signals2::connection link =
		a.sig.connect(1, boost::bind(&B::slot1, b, _1, 1, 2),
		boost::signals2::at_front);
	a.sig.connect(2, boost::bind(&B::slot2, b, 1.0, _1));

	cout << *a.sig(0) << endl;
	cout << "\nDisconnect slot1(int, int, int)." << endl;

	link.disconnect(); //取消槽函数slot1(int, int, int)的连接

	cout << a.sig(1).value() << endl; //调用value()成员函数获取合并器返回值
	return 0;
}
```

输出结果：(GCC 5.1.0 && ArchLinux x64)：

```
This is slot1(int, int, int).
This is slot1(int, char).
This is slot2.
300

Disconnect slot1(int, int, int).
This is slot1(int, char).
This is slot2.
300
```



# Boost 时间库
`boost`时间库提供了跨平台的时间解决方案，相关头文件为`/usr/include/boost/date_time/posix_time/posix_time.hpp`。

## 获取当前时间
时间使用`boost::posix_time::ptime`类型表示。

- 使用`boost::posix_time::second_clock/microsec_clock::universal_time()`可以获取当前`UTC`时间的秒数/微秒数。
- 使用`boost::posix_time::second_clock/microsec_clock::local_time()`可以获取当前本地时间的秒数/微秒数。
- 使用`boost::posix_time::to_iso_string()`可以以获取的`boost::posix_time::ptime`作为参数，然后输出为标准的字符串`std::string`来表示时间。

## 获取时间间隔
- `boost::posix_time::ptime`类重载了减号，两个`boost::posix_time::ptime`对象可以相减得到类型为`boost::posix_time::time_duration`的时间间隔。
- `boost::posix_time::time_duration`可以使用`total_microseconds()`、`total_milliseconds()`、`total_nanoseconds()`、`total_seconds()`分别获取时间间隔对应的微秒/毫秒/纳秒/秒等作为单位的时间表示。



# std::chrono (标准时间库)
`std::chrono`是C++11中引入的标准时间库，来自于`boost::chrono`。

`std::chrono`中主要包含以下内容：

- `std::chrono::duration`用于表示一段**时间间隔**。
- `std::chrono::time_point`用于表示某一个**时间点**。
- `std::chrono::system_clock`用于表示系统时钟。
- `std::chrono::steady_clock`递增时钟(不会因为时钟修改而减少值)。

## std::chrono::duration
`std::chrono::duration`在`GCC 6.2.1`的定义如下：

```cpp
template<typename _Rep, typename _Period = ratio<1>>
struct duration;
```

- `_Rep`为时间的数值类型，可以为`int`、`double`等常见的数值类型。
- `_Period`为时间的**单位**，以**秒**作为换算基准，使用`std::ratio`类型表示。

时间间隔相关类型定义：

- 类型`std::radio`

	`std::ratio`类型用于描述换算比，基本定义如下：

	```cpp
	template<intmax_t _Num, intmax_t _Den = 1>
	struct ratio
	{
		...
	};
	```

	模板参数均为数值，`_Num`为分子，`_Den`为分母。
	`std::ratio<1, 1>`表示`1/1`即`1`，`std::ratio<200, -1>`表示`200/-1`即`-200`。

- 时间单位

	标准库时间以秒为换算基础(即将**秒**定义为`std::radio<1, 1>`)，定义了其它标准时间单位：

	```cpp
	/// nanoseconds
	typedef duration<int64_t, nano> nanoseconds;
	/// microseconds
	typedef duration<int64_t, micro> microseconds;
	/// milliseconds
	typedef duration<int64_t, milli> milliseconds;
	/// seconds
	typedef duration<int64_t> seconds;
	/// minutes
	typedef duration<int64_t, ratio<60>> minutes;
	/// hours
	typedef duration<int64_t, ratio<3600>> hours;
	```

	其中，`nano`、`micro`、`milli`的定义在`radio`头文件中：

	```cpp
	typedef ratio<1, 1000000000> nano;
	typedef ratio<1, 1000000> micro;
	typedef ratio<1, 1000> milli;
	```

- 时间转换

	不同的时间单位之间相互转换使用`std::chrono::duration_cast()`函数，该函数定义如下：

	```cpp
	/// duration_cast
	template<typename _ToDur, typename _Rep, typename _Period>
	constexpr typename enable_if<__is_duration<_ToDur>::value, _ToDur>::type
	duration_cast(const duration<_Rep, _Period>& __d)
	{
		...
	}
	```

	模板参数`_ToDur`表示需要转换成的目标时间单位，`_Rep`、`_Period`用于表示被转换时间的单位。
	简单的用法示例：

	```cpp
	#include <iostream>
	#include <chrono>

	int main(void)
	{
		std::chrono::hours hour(1); //一个小时的时间间隔
		std::chrono::minutes mintue = std::chrono::duration_cast<std::chrono::minutes>(hour); //转换为分钟
		std::cout << "Hour: " << hour.count() << std::endl;
		std::cout << "Mintue: " << mintue.count() << std::endl;

		return 0;
	}
	```

	输出结果：(GCC 6.2.1 && ArchLinux x64)

	```
	Hour: 1
	Mintue: 60
	```

## std::time_point
`std::chrono::time_point`表示某一个时间点，基本定义如下：

```cpp
template<typename _Clock, typename _Dur>
struct time_point
{
	...
};
```

模版参数`_Dur`为时间的单位(带有模版参数的具体`std::chrono::duration`)，`_Clock`定义了时间点使用的**时钟类型**。

- `std::chrono::time_point`可以与时间间隔`std::chrono::duration`进行加减运算，得到新的时间点。
- 时间点同样拥有`time_point_cast()`用于在不同单位的时间点之间进行转换，模板参数、使用方法与`std::chrono::duration`的对应函数类似。

## 时钟类型
时钟类型中定义了时间的相关单位，不同的时钟类型有着不同的精确度。

- 时钟类型有`std::chrono::system_clock`、`std::chrono::steady_clock`、`std::chrono::high_resolution_clock`等。
- 在Linux下，`std::chrono::system_clock`的`std::chrono::duration`为`std::chrono::nanoseconds`，即系统时间精确到**纳秒**。
- `std::chrono::high_resolution_clock`代表当前系统中最高精确度的时钟，在Linux下，该类型为`std::chrono::system_clock`的别名。

标准时钟`std::chrono::system_clock`具有以下常用方法：

- `std::chrono::system_clock::now()`可以获得当前时间的时间点(`std::chrono::time_point`类型)。
- `std::chrono::system_clock::to_time_t()`/`std::chrono::system_clock::from_time_t()`函数将`std::chrono::time_point`与`POSIX`中定义的时间类型`time_t`相互转换(`time_t`类型可进一步使用`localtime()/asctime()/ctime()`等函数进一步转换得到可读的时间)。

## 基本用法示例
以指定格式输出系统时间，并进行简单的时间运算。

```cpp
#include <iostream>
#include <chrono>

using namespace std;

int main(void)
{
	// 获取当前系统时间
	chrono::time_point<chrono::system_clock, chrono::nanoseconds> now = chrono::system_clock::now();

	// 转换为POSIX标准单位
	time_t time_now = chrono::system_clock::to_time_t(now);

	// 输出时间内容
	tm* st_tm = localtime(&time_now);
	cout << "Year: " << st_tm->tm_year << endl;
	cout << "Month: " << st_tm->tm_mon << endl;
	cout << "Hour: " << st_tm->tm_hour << endl;
	cout << "Minute: " << st_tm->tm_min << endl;

	// 以标准格式打印当前时间
	cout << "\nAsctime: " << std::ctime(&time_now) << endl;

	// 当前时间添加一小时时间间隔
	chrono::time_point<chrono::system_clock, chrono::nanoseconds> now_after_hour = now + chrono::hours(1);
	time_t time_after_hour = chrono::system_clock::to_time_t(now_after_hour);

	// 输出添加间隔后的时间
	cout << "After one hour: " << ctime(&time_after_hour) << endl;

	// 反向计算间隔，并以分钟为单位输出
	cout << "Minutes: " << chrono::duration_cast<chrono::minutes>(now_after_hour - now).count() << endl;

	return 0;
}
```

输出结果：

```
Year: 116
Month: 8
Hour: 17
Minute: 57

Asctime: Thu Sep 22 17:57:05 2016

After one hour: Thu Sep 22 18:57:05 2016

Minutes: 60
```



# C/C++中一些编码中遇到的错误

## multiple definition of
在头文件中定义全局变量，若该头文件被多次包含，会出现**多重定义**错误，
即使你在头文件的定义中正确地使用了`#ifndef #define #endif`或是`#pragma once`宏。

正确的定义全局变量的方法是将定义写在代码文件中，然后在头文件里用`extern`关键字添加声明即可。

`#ifndef #define #endif`宏只能保证**编译阶段**代码段不被重复包含，但变量定义是对每个源文件均有效，
源文件编译得到的目标文件里每一个都含有该变量的定义，虽然编译时不会报错，
但当目标文件连接时，多个目标文件中包含相同变量定义会产生多重定义冲突。

在C++中，若全局变量定义在某个命名空间中，则源码中的定义和头文件中的`extern`声明需要位于相同命名空间中。

举例：

```cpp
// 头文件 xxx.h
namespace A
{
	extern int a;
}

// 代码文件 xxx.cc
namespace A
{
	int a = 0;
}
```

## 在 switch 的 case 语句中定义局部变量
在C语言中，不允许在`switch`的`case`语句内直接定义局部变量，以下语句是错误的：

```cpp
int a = 0;
switch (a)
{
case 0:
	int b = 0;
	break;
}
```

无法通过编译，C语言编译器会提示`crosses initialization of 'int b'`。
以上语句在C++编译器中也会给出同样的错误。

但C++中允许另一种写法：

```cpp
int a = 0;
switch (a)
{
case 0:
	int b;
	b = 0;
	break;
}
```

将定义与赋值拆开可以通过C++编译器，但依旧会在C编译器中报错。
出现此种情况是因为在C/C++中，case标签不具有独立的作用域，同时在不使用break语句的情况下，
case标签中的变量定义语句根据传入值的不同不一定会被执行，变量不一定会被定义，因而在C/C++中不允许这样的行为。
正确的做法是在需要在case标签内容中定义变量时使用`{}`来构建一个独立作用域，使变量定义对其它case标签不可见。
示例：

```cpp
int a = 0;
switch (a)
{
case 0:
	{
		int b = 0;
		break;
	}
}
```

以上代码可以在C/C++编译器中编译通过。



# 常用的C标准库函数
在C++中，为标准C库头文件提供了对应的C++版本，示例：

| C标准库头文件 | C++标准库头文件 | 主要功能 |
| :-: | :-: | :- |
| stdio.h | cstdio | IO函数，如`printf()`、`scanf()`等 |
| string.h | cstring | 字符处理函数，如`strcmp()`、`strlen()`等 |
| stddef.h | cstddef | 基础类型定义 |
| stdlib.h | cstdlib | 数值转换(`atoi()`等)、内存分配(`malloc()`、`free()`等)，系统功能(`exit()`、`system()`等) |
| stdint.h | cstdint | 扩展的整形定义，如`uint8_t`、`uint64_t/`等 |
| time.h | ctime | 时间函数，如`ctime()`、`asctime()`、`localtime()`等 |
| math.h | cmath | 数学函数，如`abs()`、`sin()`、`cos()`等 |

## memset()
初始化内存块常使用`memset()`函数，函数定义为：

```c
#include <string.h>
void* memset(void* s, int c, size_t n);
```

作用是将指针`s`所指向的区域的前`n`位用`ASC`码值`c`填充。
注意`c`的取值为`ASC`码值，即如果`c`取`0`，则指针`s`所指向的区域的前`n`为全部用空白填充(相当于全是`\0`)，如果`c`取`49`，
则相当于用数字`1`来填充，依此类推。

## memcpy()
拷贝内存常用`memcpy()`函数，函数定义为：

```c
#include <string.h>
void *memcpy(void *dest, const void *src, size_t n);
```

从指针`src`指向的内容中复制`n`个字节到`dest`指针指向的内容。
函数返回值是一个指向`dest`指向内容的指针。

## strcpy() 函数
复制字符数组常用`strcpy()`函数，函数定义为：

```c
#include <string.h>
char* stpcpy(char* restrict s1, const char* restrict s2);
```

将指针`s2`指向的内容复制到`s1`指向的区域。
函数返回指针复制内容后的指针`s1`，返回值的作用是使该函数能够更连贯地用于表达式。

## setjmp() / longjmp()
使用`goto`语句只能在函数内部进行跳转，使用`setjmp()/longjmp()`函数能够实现**跨函数跳转**。
`setjmp()/longjmp()`常用在**错误处理**中，程序在各个位置的异常都可以跳转回一个统一的位置进行错误处理。

函数定义如下：

```c
#include <setjmp.h>
int setjmp(jmp_buf env);
void longjmp(jmp_buf env, int val);
```

- `env`参数保存函数局部栈数据，用于之后的状态恢复。
- `val`参数用于指定`longjmp()`调用后，从`setjmp()`函数恢复时的返回值。

通过调用`setjmp()`函数设置恢复点，调用`setjmp()`函数之后，会将当前局部环境信息写入`env`变量中用于之后的恢复操作。
首次调用`setjmp()`函数返回值为`0`，之后调用`longjmp()`函数可跳转到上次调用`setjmp()`的位置，
`longjmp()`函数中的参数`val`为`setjmp()`返回值。
在`setjmp()`调用后，直到从`longjmp()`函数返回期间，信号会一直被**阻塞**。

示例：

```c
#include <stdio.h>
#include <setjmp.h>

jmp_buf env; //env变量用于保存函数栈信息

void func(void)
{
	printf("Call func()\n");
	longjmp(env, 1); //跳转回setjmp()的位置，setjmp()的返回值为-1
	printf("After longjmp()\n"); //longjmp()之后的代码没有执行
}

int main(void)
{
	switch(setjmp(env)) //跨函数跳转
	{
	case 0:
		printf("First\n");
		func();
		break;
	case 1:
		printf("Second\n");
		break;
	}

	return 0;
}
```

运行结果：(GCC 5.4.0 && ArchLinux x64)

```
First
Call func()
Second
```

## sigsetjmp() / siglongjmp()
`POSIX`对于使用在**信号处理函数**内部使用`longjmp()`跳转回`setjmp()`位置时是否恢复信号状态**未定义**。
在不同的Unix中，从`longjmp()`跳转回`setjmp()`位置时可能恢复信号处理和信号屏蔽，也可能**不恢复**。
实测在`Linux`中**不会**恢复信号状态。

`POSIX`提供了`sigsetjmp()/siglongjmp()`用于在**信号处理函数**内部进行跳转。

```c
#include <setjmp.h>
int sigsetjmp(sigjmp_buf env, int savesigs);
void siglongjmp(sigjmp_buf env, int val);
```

- `savesigs`参数用于设置是否保存信号状态，取`0`时不保存信号数据，取**非零**保存信号状态。

若**不保存**信号状态，则从信号处理函数内跳转回`setjmp()`位置时，原有的信号处理函数绑定、信号屏蔽字都会恢复默认值。

示例：

```c
#include <stdio.h>
#include <setjmp.h>
#include <signal.h>
#include <unistd.h>

jmp_buf env; //env变量用于保存函数栈信息

void deal_signal(int sig_num)
{
	printf("Deal signal!\n");
	siglongjmp(env, 1);
}

int main(void)
{
	signal(SIGINT, deal_signal);

	switch(sigsetjmp(env, 0)) //不保存信号数据则跳转回此处时原先注册的信号处理函数失效
	{
	case 0:
		printf("First\n");
		break;
	case 1:
		printf("Second\n");
		break;
	}

	sleep(5);

	return 0;
}
```

运行结果(GCC 5.3.0 && ArchLinux x64)：

```
First
^CDeal signal!
Second
^C^C^C^C
```

第一次发送`SIGINT`信号触发了`deal_signal()`函数，从信号处理函数`deal_signal()`内部跳转回`sigsetjmp()`位置时，
由于之前**未设置**保存信号数据，因而再次接收到信号`SIGINT`时，`deal_signal()`函数不再触发，直到程序结束。

若保存信号数据(`setjmp()`的`savesig`参数为`1`时)，函数输出结果为：

```
First
^CDeal signal!
Second
^CDeal signal!
Second
......
```

可以看出，保存信号数据的情况下，`SIGINT`信号无论多少次发送都会正常跳转会`sigsetjmp()`位置。

## getopt() / getopt_long()
`getopt()/getopt_long()`用于处理命令行参数。定义如下：

```c
#include <unistd.h>
int getopt(int argc, char* const argv[], const char* optstring);

extern char* optarg;
extern int optind, opterr, optopt;

#include <getopt.h>
int getopt_long(int argc, char* const argv[],
		const char* optstring, const struct option* longopts, int* longindex);
int getopt_long_only(int argc, char* const argv[], const char* optstring,
		const struct option* longopts, int* longindex);
```

使用`getopt()`函数处理单字符参数，如`-v/-x/-h`等：

- `argc/argv`参数为从`main()`函数中传入的命令行参数信息。
- `optstring`参数为接收参数的字符数组。

`optstring`参数按以下规则解析：

- 一个字符表示接收一个对应参数，如`"vxh"`表示接收参数格式`-v -x -h`。
- 字符后添加单冒号表示参数带有内容，如`"h:"`表示接收参数格式`-h xxx`、`-hxxx`，若参数未添加内容则不被识别(如`-h`)。
- 字符后添加双冒号表示参数带有可选的参数内容，如`"h::"`表示接收参数格式`-h xxx`、`-hxxx`或`-h`，不强制要求参数带有内容。

若参数带有内容，参数的内容会被写入全局变量`optarg`中(变量声明在头文件`getopt.h`中)。
每次执行`getopt()`函数仅会获取一个参数，获取多个参数需要循环执行`getopt()`函数。
通过全局变量`optind`决定获取参数的位置，`getopt()`函数内部会修改`optind`的值。

执行成功时，`getopt()`函数返回匹配到的参数字符(`ASCII`值)，失败时返回`-1`。

实例代码如下：

```c
#include <getopt.h>
#include <stdio.h>

int main(int argc, char* argv[])
{
	char arg = 0;
	while ((arg = getopt(argc, argv, "ab:c::")) > 0)
	{
		switch (arg)
		{
		case 'a':
			printf("Receive arg: -a\n");
			break;
		case 'b':
			printf("Receive arg: -b, content: %s\n", optarg);
			break;
		case 'c':
			printf("Receive arg: -c, content: %s\n", optarg);
			break;
		}
	}

	return 0;
}
```

编译测试：

```
$ cc test.c -o test_arg

$ test_arg -a
Receive arg: -a

$ test_arg -b
test_arg: option requires an argument -- b

$ test_arg -bssss
Receive arg: -b, content: ssss

$ test_arg -b ssss
Receive arg: -b, content: ssss

$ test_arg -c
Receive arg: -c, content: (null)

$ test_arg -cssss
Receive arg: -c, content: ssss

$ test_arg -a -bbbbb -ccccc
Receive arg: -a
Receive arg: -b, content: bbbb
Receive arg: -c, content: cccc
```

`getopt()`仅支持单字符参数，`getopt_long()`支持长参数，如`--version --help`等：

- `argc/argv/optstring`等参数与`getopt()`函数中功能类似。
- `longopts`参数为长指令的描述结构数组。
- `longindex`参数为匹配到的指令在`longopts`数组中位置(传入地址，匹配到长指令时索引值写入该地址，
如匹配到短指令或未匹配到指令，则不设置该参数)。

`longopts`参数的类型为`struct option`，定义在`getopt.h`文件中：

```c
struct option
{
	const char* name;
	int has_arg;
	int* flag;
	int val;
};
```

- `name`成员为长参数的名称，不包含`--`部分。
- `has_arg`成员标识参数是否带有参数内容，`getopt.h`头文件中定义了以下行为：
	- `no_argument` 不包含参数
	- `required_argument` 要求参数内容
	- `optional_argument` 可选参数内容
- `flag`成员用于决定函数的返回行为，取值`nullptr`时函数返回`val`成员的值，否则函数返回`0`，并将`val`内容写入该地址。
- `val`成员在`flag`取值`nullptr`时做为函数的返回值。

示例：

```c
#include <getopt.h>
#include <stdio.h>

int main(int argc, char* argv[])
{
	int arg, index, flag = -1;

	struct option opts[] =
	{
		{ "aaa", no_argument, NULL, 'a' },
		{ "bbb", required_argument, NULL, 'b' },
		{ "ccc", optional_argument, NULL, 'c' },
		{ "23", no_argument, &flag, 2333 }
	};

	while ((arg = getopt_long(argc, argv, "ab:c::", (struct option*)&opts, &index)) >= 0)
	{
		switch (arg)
		{
		case 'a':
			printf("Receive arg: -a, index: %d\n", index);
			break;
		case 'b':
			printf("Receive arg: -b, content: %s, index: %d\n", optarg, index);
			break;
		case 'c':
			printf("Receive arg: -c, content: %s, index: %d\n", optarg, index);
			break;
		case 0:
			printf("Receive arg: --23, index: %d, flag: %d\n", index, flag);
			break;
		}
	}

	return 0;
}
```

编译测试：

```
$ cc test.c -o test_arg

$ test_arg -b
test_arg: option requires an argument -- b

$ test_arg -b=2333
Receive arg: -b, content: =2333, index: -1

$ test_arg -b 2333
Receive arg: -b, content: 2333, index: -1

$ test_arg --bbb
test_arg: option requires an argument -- bbb

$ test_arg --bbb=2333
Receive arg: -b, content: 2333, index: 1

$ test_arg --bbb 2333
Receive arg: -b, content: 2333, index: 1

$ test_arg --23
Receive arg: --23, index: 3, flag: 2333
```



# 一些关键字、特殊值的含义/用法

## explicit 关键字
C++中的关键字`explicit`作用是防止构造函数隐式转换的发生。

默认情况下，在C++中，使用`类名 实例名 = 参数`的形式创建一个类的实例。
当`参数`刚好符合类的构造函数参数要求，此时编译器会隐式的调用这个类的构造函数来创建类的实例。
但有些情况下，需要避免这种隐式转换的发生，这时，在类的构造函数声明时，
在在构造函数名之前加上`explicit`关键字即可避免隐式转换发生。

采用`explicit`关键字声明的构造函数只能够被显式地调用。

## restrict 关键字
`C99`中新引入了关键字`restrict`，restrict关键字用在指针的定义中，格式为`变量类型* restrict 指针名`，
作用是是告知编译器该指针是指针所指向区域的**唯一**访问方式，
所有修改该指针指向内容的操作都只能通过该指针进行，而**不能**通过其它变量或指针来修改。

restrict关键字不会改变指针的用法，但会让编译器更加安全高效准确地优化代码，
使用restrict关键字定义的指针的指向不应进行改动。restrict关键字只在支持`C99`以上的C编译器中使用，
C++**没有**引入这个关键字。

## mutable 关键字
`mutable`关键字用于定义一个易变的变量，只能用于修饰类的非静态数据成员，语法格式上与`const`类似。
普通成员变量在`const`修饰的成员函数中不可修改，
但使用了`mutable`关键字定义的变量，即使是在const成员函数中，依然可被修改。

C语言**没有**这个关键字。

## using 关键字
`using`用于简化处于命名空间中的内容的使用。如：

```cpp
using namespace std;
using std::string;
using namespace 命名空间名称;
using 命名空间名称::类型名称/变量名称;
```

using用于定义类型的别名(类似于typedef)。如：

```cpp
using List = std::list<int>; //等价于 typedef class std::list<int> List;
using point = int (*a)(int, int);
```

using用于定义模板类型的部分有参别名(typedef不能定义部分参数化模版类型)。如：

```cpp
template <class T>
using Map = std::map<int, T>;
```

using用于在子类隐藏了父类的函数时，使子类能够使用父类原先被隐藏的函数。如：

```cpp
using 父类类名::被隐藏函数的函数名;
```

## 移位运算符
移位运算符的作用是将一个数的对应二进制值左移或右移指定的位数。

```cpp
int a = 1;
int b = a << 10; //b = 1024
int c = b >> 5; //c = 32
```

`a`的二进制值也是1，将十进制的1的二进制值左移10位则结果为`1 * 2 ^ 10`，即1024。
1024的二进制值右移5位结果为`1 * 2 ^ 5`，即32。

## npos 成员
多数C++标准容器都提供了`npos`成员，`npos`用来表示不会被取到的下标，类型为`容器类型::size_type`，
一般取值为`-1`(实际值取决于编译器的具体实现)。

使用容器提供的`find()`成员函数查找内容时，如果目标内容没有被找到，则返回`容器类型::npos`。



# 常见错误

## error: jump to case label
对于`switch`语句，每个`case`子句不具有独立作用域，在`case`子句中定义局部变量需要使用花括号建立独立作用域。
若未未使用花括号建立独立作用域且`case`子句内创建的变量不同，则出现此警告。

## warning: `...` will be initialized after [-Wreorder] ...
在构造方法中使用初始化列表，若初始化列表中参数顺序与类定义中出现的顺序不同，则出现此警告。
