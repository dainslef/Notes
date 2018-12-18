# 概述
`Objective-C`是C语言的面向对象扩展。与C++不同，Objective-C是C语言的**严格超集**，完全兼容C语法。
任何原始的C语言源码不经修改就可以直接使用Objective-C编译器编译，在Objective-C中使用C语言代码也是完全合法的。

在实现上，Objective-C的语言标准由Apple公司主导，并广泛用于macOS和iOS中。
主流的C语言编译器如GCC、Clang等均支持编译Objective-C源码的编译。



# 主要特点
作为C语言的面向对象超集，Objective-C基础语法与C语言完全相同，仅在OOP方面做出扩展。
Objective-C的面向对象语法源于`Smalltalk`学派的消息传递风格，与C++使用的`Simula`风格有较大差异。

主要语法：

- 用`[对象名 方法名: 参数表]`传递消息，消息的作用类似Simula风格中的`对象名.方法名(参数表)`。
与传统的OOP语言不同，Objective-C中的消息并不关注发送消息的对象成员是否存在，即可以向对象中**不存在**的成员发送消息，
这只会在编译时收到编译器发出的警告，而不会导致编译失败；同时运行时到此语句时，程序会向终端发出错误信息并终止。
- 用`+`定义类方法(即静态方法，无须实例化即可调用)，用`-`定义实例方法(类似于一般的成员方法，需要实例化)。
- 一个类在定义时需要给出基类，没有基类就从`NSObject`类中派生。
- `@interface`定义类，`@end`作为定义结束标志。
- `@implementation`中存放类成员函数的实现，`@end`作为实现结束标志，在@implementation区段中，
可以创建未在@interface中定义的变量和函数，且这些未定义的内容是不能通过消息访问的(类似于传统OOP概念中的私有成员函数)。
- 方法不存在访问权限，存在访问权限的只有@interface区域中的**成员变量**，
一般权限有`@public`、`@protected`、`@private`等，成员变量的默认权限为`@protected`。
- Objective-C中的成员变量不同通过`实例名.成员变量`来访问或是赋值，
要使用`实例名.成员变量`方式访问成员则需要定义为**属性**，使用关键字`@property`。
- 通过定义`init`方法来实现构造函数，默认类的实例化为`MyObject* object = [[MyObject alloc] init: 参数表];`。
如果类使用默认构造方法，还可以使用`MyObject* object = [MyObject new];`来进行类的实例化。
需要注意，Objective-C中的类对象必须是指针，否则无法通过编译。
与C++/Java等语言不同，在Objective-C中即使你定义了其它的构造方法，默认的构造方法依然会保留。
- Objective-C重写`dealloc`方法来自定义析构函数。
与C++不同，自定义dealloc中要使用`[super dealloc]`语句来显式调用父类的析构函数。
- Objective-C是**单继承**语言，但有`@protocal`协议区段来实现类似Java中的**接口**。
Objective-C的协议中不能包含变量与属性(即只能定义方法)。与其它高级语言不同，协议中的方法不是必须实现的。
- Objective-C是**动态类型**语言，可以向属性`id`发送任意类型的消息。
- Objective-C允许一个类中的静态与非静态函数拥有同样的函数原型，C++/C#/Java则不允许。
- Onjective-C中，成员函数的参数能够使用变量标签名称来标志变量的作用。
成员函数的函数名就可以视为第一个参数的参数标签，从第二个参数开始，就可以为参数自定义标签，
格式为`(返回值类型) 函数名: (参数类型) 参数名 标签名: (参数类型) 参数名 标签名: (参数类型) 参数名 .....`。
函数标签也被视为函数的一部分，一个成员函数在类定义时使用了函数标签，则该成员函数的对应函数实现也应该写上相同的函数标签，
同时向类发送消息时，添加参数也要写上与成员函数定义时完全相同的函数标签，三者缺一不可。
- Objective-C不完全支持重载，不支持重载C语言部分的全局函数。
在Objective-C代码中，同一个类中不能存在函数名相同、参数个数相同、参数类型不同的两个方法(即不支持`AD-HOC`重载)，
但函数名相同、参数个数不同的函数是允许的。此外，在Objective-C中，函数标签也被视为函数签名的一部分，
定义两个函数名相同、参数个数相同、参数类型不同、参数标签不同的函数是允许的，但仅仅是参数标签不同则不能通过编译。



# Objective-C 与 C++ 语法对照
Objective-C与C++的相近概念的语法对比。

- 创建对象实例

	C++:

	```cpp
	MyObject* object = new MyObject();
	```

	Objective-C：

	```objc
	MyObject* object = [[MyObject alloc] init]; //alloc是分配内存的意思
	MyObject* object = [MyObject new]; //如果只是调用默认构造函数，则可以使用new关键字将分配内存和初始化整合为一步
	```

- 类定义

	C++：

	```cpp
	class A
	{
	public:
		A(int);
		～A();
		int getA();
		static int get(int);

	private:
		int a;
	};
	```

	Objective-C：

	```objc
	// Objective-C中的类必须从某个类中继承，如果没有直接父类，就从默认的NSObject中继承
	@interface A : NSObject
	{
		@private int a;
	}
	- (id) init: (int) num; //构造方法
	- (void) dealloc; //析构方法
	- (int) getA;
	+ (int) get: (int) num;
	@end
	```

- 类实现

	C++：

	```cpp
	A::A(int num)
	{
		a = num;
	}

	A::~A()
	{
	}

	int A::getA()
	{
		return a;
	}

	int A::get(int num) //静态成员函数只需要在声明时写明static关键字，定义时不需要
	{
		return num;
	}
	```

	Objective-C：

	```objc
	@implementation A
	- (id) init: (int) num
	{
		if (self = [super init]) //若需调用父类的有参构造函数，使用"[super init: 参数表]"
			a = num;
		return self;
		/*
			构造函数还可以用更简单的方式实现：
			a = num;
			return self;
		*/
	}

	- (void) dealloc
	{
		[super dealloc]; //在Objective-C中，重写析构函数时必须显式地调用父类的析构函数
		/*
			要释放的内存；
		*/
	}

	- (int) get
	{
		return a;
	}

	+ (int) getA: (int) num
	{
		return num;
	}
	@end
	```

- 类的实例化与方法调用

	C++：

	```cpp
	A* a = new A(5);
	a->get(); //调用普通成员函数
	A::getA(3); //调用静态成员函数
	A::getA(a->get());
	```

	Objective-C：

	```objc
	A* a = [[A alloc] init: 5]; //有参构造函数
	[a get]; //调用普通成员函数
	[A getA: 3]; //调用静态成员函数
	[A getA: [a get]]; //调用函数可以相互嵌套
	```

- 定义、采纳协议

	C++：

	```cpp
	class B
	{
	public:
		virtual void show(char*) = 0;
	};

	class C : public B { };
	```

	Objective-C：

	```objc
	@protocal B
	- (void) show: (char*) str; //定义接口的抽象方法
	@end

	@interface C : NSObject <B> //类C采纳协议B(基类仍是NSObject)
	@end
	```
