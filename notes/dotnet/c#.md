<!-- TOC -->

- [入口函数](#入口函数)
- [数据类型](#数据类型)
	- [*Value Type* (值类型)](#value-type-值类型)
	- [*Reference Type* (引用类型)](#reference-type-引用类型)
	- [可空类型与 *?*、*??* 操作符](#可空类型与--操作符)
	- [*Type alias* (类型别名)](#type-alias-类型别名)
- [字符转换](#字符转换)
	- [*byte[]* 与 *string* 转换](#byte-与-string-转换)
- [*Property* (属性)](#property-属性)
	- [自动成员属性](#自动成员属性)
	- [成员属性初始化](#成员属性初始化)
	- [属性表达式](#属性表达式)
- [*struct* (结构类型)](#struct-结构类型)
- [*static* 关键字](#static-关键字)
	- [静态方法](#静态方法)
	- [静态字段](#静态字段)
	- [静态构造函数](#静态构造函数)
	- [静态类](#静态类)
- [*Extension Methods* (扩展方法)](#extension-methods-扩展方法)
	- [在 *Scala* 中模拟扩展方法](#在-scala-中模拟扩展方法)
	- [扩展方法的应用场景](#扩展方法的应用场景)
- [泛型](#泛型)
	- [泛型约束](#泛型约束)
	- [*Variance* (变性)](#variance-变性)
	- [泛型类的静态成员](#泛型类的静态成员)
- [*delegate* (委托) 和 *event* (事件)](#delegate-委托-和-event-事件)
	- [*delegate* (委托)](#delegate-委托)
	- [*event* (事件)](#event-事件)
	- [自定义添加/删除操作的事件](#自定义添加删除操作的事件)
- [*Lambda*](#lambda)
	- [*Lambda* 实现委托(delegate)](#lambda-实现委托delegate)
	- [使用函数对象表示 *Lambda*](#使用函数对象表示-lambda)
	- [*Lambda* 作用域](#lambda-作用域)
	- [使用 *Lambda* 语法定义成员函数](#使用-lambda-语法定义成员函数)
- [*Pattern Matching* (模式匹配)](#pattern-matching-模式匹配)
	- [*is* 表达式](#is-表达式)
	- [*switch* 模式匹配](#switch-模式匹配)
- [并发编程](#并发编程)
	- [*Thread* 类](#thread-类)
	- [异步委托](#异步委托)
	- [*Task* 类](#task-类)
	- [*async/await* 关键字](#asyncawait-关键字)
	- [*lock* 关键字](#lock-关键字)
- [*Reflection* (反射)](#reflection-反射)
	- [反射机制的相关类型](#反射机制的相关类型)
	- [*Type*/*TypeInfo* 类型](#typetypeinfo-类型)
	- [反射获取成员信息](#反射获取成员信息)
- [*Attribute* (特性)](#attribute-特性)
	- [使用特性](#使用特性)
	- [自定义特性](#自定义特性)
- [动态代理](#动态代理)
- [*FTP*](#ftp)
	- [创建 *FTP* 请求](#创建-ftp-请求)
	- [下载](#下载)
	- [上传](#上传)
- [*WinFrom* 开发注记](#winfrom-开发注记)
	- [常见控件类型](#常见控件类型)
	- [容器控件](#容器控件)
	- [布局与样式](#布局与样式)
	- [控件事件](#控件事件)
	- [接收Windows消息](#接收windows消息)
- [调用 *C/C++* 动态链接库](#调用-cc-动态链接库)
- [特殊关键字](#特殊关键字)
	- [*internal* 关键字](#internal-关键字)
	- [*readonly* 关键字](#readonly-关键字)
	- [*partial* 关键字](#partial-关键字)
	- [*params* 关键字](#params-关键字)
- [常见问题](#常见问题)
	- [处理`\0`结尾字符串](#处理\0结尾字符串)
	- [MySQL 中 *TINYINT* 类型](#mysql-中-tinyint-类型)
	- [*DEBUG* 模式](#debug-模式)
	- [输出代码文件名、行号](#输出代码文件名行号)

<!-- /TOC -->



## 入口函数
`C#`中允许以下4种形式的入口函数：

```cs
static void Main();
static void Main(string[] args);
static int Main();
static int Main(string[] args);
```

`C#`允许多种入口函数形式，一般采用第二种(默认)。

与`Java`不同，`C#`并不强制要求主类的类名与主类所在文件的文件名相同。  
实际上，`C#`由于支持`部分类`特性，也不可能要求类名与源码文件名相同。



## 数据类型
C#的数据类型分为两类：值类型和引用类型。  
一般而言，值类型用于**存储数据**，引用类型用于**定义行为**。

### *Value Type* (值类型)
值类型具体包括**预定义值类型**、**自定义值类型**和**枚举类型**。  
所有值类型隐式派生于`System.ValueType`类。

例如，系统预定义的值类型`int`是`System`命名空间中`System.Int32`结构体的别名。  
`System.Int32`结构的定义为：

```cs
public struct Int32 : IComparable, IFormattable, IConvertible, IComparable<int>, IEquatable<int>
{
	...
}
```

其它的预定义值类型也是类似的`结构类型(Struct)`的别名：

| 别名 | 实际类型 |
|:----|:--------|
| sbyte | System.SByte |
| short | System.Int16 |
| int | System.Int32 |
| long | System.Int64 |
| byte | System.Byte |
| ushort | System.UInt16 |
| uint | System.UInt32 |
| ulong | System.UInt64 |
| char | System.Char |
| float | System.Single |
| double | System.Double |
| decimal | System.Decimal(一般用于财务计算) |
| bool | System.Boolean |
| enum | System.Enum(枚举类型) |

用户定义的结构体，从`System.ValueType`类中继承：

```cs
public abstract class ValueType {};
```

值类型实例通常分配在线程的**栈(stack)**上，并且不包含任何指向实例数据的指针，因为变量本身就包含了其实例数据。  
值类型在复制时是**值传递(pass by value)**，会复制当前值类型变量包含的内容。

### *Reference Type* (引用类型)
引用类型包括：

- 数组(派生于`System.Array`)
- 字符串`string`(`System.String`类的别名)
- 自定义类(派生于`System.Object`)
- 委托类型(派生于`System.Delegate`)
- `object`类型(`System.Object`)的别名

引用类型与值类型比较：

- 值类型和引用类型都可以**实现接口**，但值类型**不能**再派生出新的子类型。
- 引用类型可以为`null`，但值类型不行(除了**可空类型**)。
- 引用类型复制是传递引用，值类型复制是拷贝整个对象。
- 值类型分配内存在线程栈上，出栈自动释放；引用类型分配内存在托管堆上，由`GC`负责内存回收。

### 可空类型与 *?*、*??* 操作符
在`C#`中，值类型不能为`null`，对值类型赋值`null`会得到错误，如下所示：

```cs
int num = null; //错误信息："Cannot convert null to 'int' because it is a non-nullable value type"
```

在传统的值类型后添加`?`符号，即成为对应的**可空类型**。  
可空类型的实际类型为`System.Nullable<T>`结构体：

```cs
public struct Nullable<T> where T : struct
{
	...
}
```

假设有值类型`T`，对应的可空类型声明可以为：

```cs
T? variable;
System.Nullable<T> variable;
```

可空类型提供以下**只读属性**用于检查/获取保存的实际值：

- `HasValue`属性类型为`bool`类型，当变量包含非`null`值时，返回`true`。
- `Value`属性类型为可空类型对应的值类型，当可空类型保存的值**不为**`null`时，返回保存的值，否则抛出`InvalidOperationException`异常。

- `??`操作符

	`??`运算符用于在可空类型/引用类型值为`null`时返回默认值，如下所示：

	```cs
	int? num0 = null;
	num0 ?? 1; //可空变量为null时返回指定的默认值1
	int? num1 = 0;
	num1 ?? 1; //可空变量不为null时返回保存的值0
	string str = null;
	str ?? "test" //??操作符同样可以用在普通引用类型上
	```

- `?`操作符

	`?`操作符可用于在访问引用类型/可空类型前对目标对象进行检查，访问的实例为`null`则不执行操作。  
	如下所示：

	```cs
	using System;

	class Test
	{
		public void Show() => Console.WriteLine("Called Show()");
		public int GetNum() => 1;
	}

	class Program
	{
		static void Main(string[] args)
		{
			Test test = null;
			Console.WriteLine("First Call:");
			test?.Show(); //实例为null，不调用方法
			int? num = test?.GetNum(); //返回可空类型，实例为null时返回值为null
			Console.WriteLine(num); //打印结果为空(null)
			Console.WriteLine("Second Call:");
			test = new Test();
			test?.Show(); //实例不为null，正常调用方法
			num = test?.GetNum();
			Console.WriteLine(num); //打印结果为1
		}
	}
	```

	输出结果：

	```
	First Call:

	Second Call:
	Called Show()
	1
	```

	使用`?`运算符的语句带有可空类型/引用类型的返回值，当受检对象未通过`null`检查，后续语句不执行，同时整个语句返回`null`。  
	利用此特性可搭配`??`运算符组合使用：

	```cs
	int? num = null;
	Console.WriteLine(num?.ToString() ?? "Empty"); //打印 "Empty"
	num = 2333;
	Console.WriteLine(num?.ToString() ?? "Empty"); //打印 "2333"
	```

	`?`运算符还可结合索引运算符`[]`使用：

	```cs
	int?[] nums = { null, 2333, null, 666 };

	Console.WriteLine(nums?[0]?.ToString() ?? "Error"); //打印 "Error"
	Console.WriteLine(nums?[1]?.ToString() ?? "Error"); //打印 "2333"
	```

### *Type alias* (类型别名)
C#中使用`using`关键字为已有类型创建**别名**，基本用法与`C++11`中添加的新`using`语法相似。  
如下所示：

```cs
namespace Np
{
	using Fvoid = Action; //普通类型别名
	using FInt = Func<int>; //泛型类型需要指定具体类型

	// C#不支持高阶类型
	using FInInt<In> = Func<In, int>; //错误
	using Ft<R> = Func<R>; //错误
}
```

`C#`中的类型别名有较多**限制**：

- 不支持定义**高阶类型**，`C++11`中的`using`支持此功能。
- 不能在命名空间之外的区域定义类型别名(全局区域、类体、函数体内皆不可定义别名)，`C++11`的`using`无此限制。



## 字符转换
`System.Text.Encoding`抽象类定义了一系列的编码转换方法。

### *byte[]* 与 *string* 转换
- 使用`string System.Text.Encoding.ASCII.GetString(byte[] bytes)`获取byte数组的对应string字符串。
- 使用`byte[] System.Text.Encoding.ASCII.GetBytes(string s)`获取string字符串对应的byte数组。



## *Property* (属性)
`C#`类中成员有一种被称为`属性`。

- 属性的访问方式与成员变量类似；通过定义`set`和`get`块的内容，能够通过属性给成员变量赋值或是获取成员变量的值。
- `set`和`get`可以分别设置**访问权限**，不加关键字时访问权限与所在的属性相同。
- `set`块中使用局部关键字`value`来代表给属性的赋值。`get`块必须返回一个与属性类型相符的值。
- `set`块和`get`块**不是**必须同时存在的，只有`set/get`块的属性被称为`只读/只写属性`。
- 属性前允许使用`static`修饰，表示定义静态属性，与静态变量类似。

如下代码所示：

```cs
using System;

class A
{
	private int num = 0;

	public int Num
	{
		set
		{
			num = value;
		}
		get
		{
			return num;
		}
	}
}

class Program
{
	static void Main(string[] args)
	{
		A a = new A();
		Console.WriteLine(a.Num);
		a.Num = 100;
		Console.WriteLine(a.Num);
	}
}
```

输出结果：

```
0
100
```

对类`A`中属性`Num`的赋值通过属性的`set`块中的局部关键字`value`传给了`A`类私有成员`num`，通过`Num`属性的`get`块获取了私有成员`num`的值。

### 自动成员属性
在`C# 3.0`之后，可以使用**自动属性**。  
自动属性只需直接使用`set`、`get`关键字，**不必**定义属性相关的私有变量并编写`set`、`get`块代码。  
编译器会为自动属性生成私有变量保存属性的内容。

上述例子中成员属性`Num`可以简写为：

```cs
public int Num { get; set; }
```

同时，不用定义私有变量`num`来存储属性的内容，编译器会自动生成一个变量。

### 成员属性初始化
在`C# 6.0`中，开始支持对自动成员属性进行**类内初始化**，可以直接在类中对自动成员属性**赋初值**：

```cs
public int Num { get; set; } = 0;
```

该特性也同样支持**只读属性**：

```cs
public int Num { get; } = 0;
```

### 属性表达式
在`C# 6.0`中，对于**只读属性**，可以使用简化的语法进行定义。  
有如下只读属性：

```cs
private int num = 0;
public int Num 
{
	get
	{
		return num;
	}
}
```

在`C# 6.0`中可以使用基于表达式的简化语法：

```cs
private int num = 0;
public int Num => num;
```

在`C# 7.0`中，对于普通属性也提供了表达式语法。  
有如下属性：

```cs
private int num = 0;
public int Num 
{
	get
	{
		return num;
	}
	set
	{
		num = value;
	}
}
```

在`C# 7.0`中可以使用简化语法：

```cs
private int num = 0;
public int Num 
{
	get => num;
	set => num = value;
}
```



## *struct* (结构类型)
与`C++`完全不同，`C#`中的`结构体`与`类`有**很大区别**：

- C#中的结构体为**值类型**，在**栈(stack)**中分配内存，而引用类型则仅在栈中保存**引用(reference)**，类型实体内存分配在**堆(heap)**中。
- 由于结构体为值类型，复制结构体时是完全复制出一个新的结构体实例，而非引用类型的引用传递。
- C#中结构体的默认访问权限是`private`，且结构体成员变量**不能**直接赋初值(需要通过有参构造函数赋初值)。
- C#中结构类型全部继承自`System.ValueType`类，但结构体是隐式**密封(sealed)**的，**不能**被继承。
- C#中结构体可以用来实现接口。用来实现接口的结构体虽然本身为值类型，但如果发生**向上转型**重新变为父类接口对象则值类型的特性也将随之消失。
- C#中结构体不能被继承，因而结构体定义时不能使用`sealed`和`abstract`关键字，结构体成员定义时也不能使用`protected`和`internal`等关键字。
- C#中结构体带有默认的无参构造函数，且该默认构造函数一直存在(无论你是否创建了有参构造函数)，默认的无参构造函数**不能**被自定义(改写)。
- 创建有参构造函数时，必须在该构造函数中初始化所有的成员变量，否则无法通过编译。
- 创建结构体时可以不使用`new`操作符，不使用`new`操作符创建的结构体对象中的结构体成员全部处于未初始化状态，需要经过初始化操作(手动访问赋值)之后方可使用。
- 如果需要使用结构体提供的有参构造函数，则必须使用`new`操作符进行对象创建，语法类似于`class`。
- 在C#中结构体成员可以使用`static`修饰，结构体也可以创建静态构造函数。
- 在C#中结构体中可以正常使用泛型。



## *static* 关键字
在`C#`中，`static`关键字用于定义**静态类**、**静态方法**、**静态属性**、**静态字段**。

### 静态方法
静态方法与实例无关，只能直接通过类名进行访问：

- 在传统的`OOP`语言如`C++`、`Java`中，并不限制通过实例访问静态方法，作用与通过类名访问静态方法相同。
- 在`C#`中，**不允许**通过实例访问静态方法，调用静态方法只能通过**类名**。

通过实例访问静态方法会在编译时得到错误：

```
error CS0176: Member 'xxx.xxx()' cannot be accessed with an instance reference; qualify it with a type name instead`
```

### 静态字段
静态字段的概念与其它传统`OOP`语言如`C++`、`Java`类似，一个类的静态字段全局唯一。  
与静态方法类似，使用实例访问静态字段会在编译时报错，在`C#`中，只能通过类名访问静态字段。

- 字段初始化

	在`C#`中，成员字段初始化时不能引用非静态成员。  
	如下代码所示：

	```cs
	class Test
	{
		int num = 0;
		int num1 = num; //编译报错
	}
	```

	在`Java`、`C++`、`Scala`中，则允许成员字段初始化时引用其它字段。

- 静态字段初始化

	在`C#`中，静态字段初始化时能够引用其它静态成员，但需要注意成员定义的**先后顺序**。  
	若引用的静态字段定义在当前静态字段之后，则当前静态不会被初始化。  
	如下所示：

	```cs
	class Test
	{
		static int num = num1; //字段num1定义在num之后，num不会被初始化，值为0(默认值)
		static int num1 = 100;
	}
	```

### 静态构造函数
静态构造函数是`C#`中特有的概念，用于在类首次被使用前进行静态成员的初始化。

- 静态构造函数与普通构造函数一样在类中定义。
- 静态构造函数不能带有参数和访问权限。
- 一个类/结构体只能定义一个静态构造函数。
- 静态构造函数与类的无参构造函数虽然参数表相同，但不会冲突。
- 静态构造函数只能初始化静态成员，若类中有静态成员赋了初值(类内初始化)，则.NET会自动为其创建默认的静态构造函数。
- 静态构造函数不需要手动调用，在首次使用创建类实例或是方位类的静态成员时会由.NET自动调用，静态构造函数在全局只会被**调用一次**。

### 静态类
在`C#`中，类定义前可以使用`static`关键字表示定义一个**静态类**。

- 静态类只能包含静态成员，且是密封(`sealed`)的，不能被实例化和继承。
- 静态类不能从普通类中派生，而静态类本身不可被继承，因而实际上所有静态类都从`object`中派生。
- 静态类不能定义普通构造函数，但能够定义静态构造函数。
- 静态类在首次被引用前加载，初始化其成员字段并调用该类的静态构造函数。
- 一个类的静态构造函数仅被调用一次，在程序驻留的应用程序域的生存期内，静态类一直保留在内存中。
- 扩展方法只能定义在静态类中。
- `const`常量自带静态特性，可以定义在静态类中。



## *Extension Methods* (扩展方法)
扩展方法能够在不改变现有类结构的前提下，向已存在的类型添加方法，并让这些方法像普通成员方法一样地被调用。

- 扩展方法本质上是一种特殊的**静态方法**，且必须定义在**静态类**中。
- 扩展方法被定义为静态方法，但调用时的语法与实例方法相同。
- 扩展方法的第一个参数必须带有`this`关键字，且类型必须是需要被扩展的类型(即第一个参数接收被扩展类型的实例)。
- 扩展方法本质上是一个语法糖，并不是真正向已有的类中添加了成员方法，因此扩展方法无法访问被扩展类的**私有成员**。
- 扩展方法在编译成**IL**中间代码时会被转换为对静态方法的调用。

如下代码所示：

```cs
using System;

static class ExtensionMethod
{
	public static bool IsNull(this object obj) => obj == null ? true : false;
}

class Test
{
	static void Main(string[] args)
	{
		object obj = null;
		Console.WriteLine(obj.IsNull());
		//实际等价于 Console.WriteLine(ExtensionMethod.IsNull(obj));
	}
}
```

输出结果：

```
True
```

### 在 *Scala* 中模拟扩展方法
在`Scala`中，可以利用**隐式类**特性来获得与C#中扩展方法类似的效果。

上述例子在`Scala`中可以写成：

```scala
object Test extends App {

  implicit class ExtensionMethod(obj: Any) {
    def isNull = if (obj == null) true else false
  }

  val obj: Any = null
  println(obj.isNull)

}
```

输出结果：

```
true
```

### 扩展方法的应用场景
扩展方法主要用于向一些不方便改动的类型添加额外的方法，并让添加的方法能够以常规语法调用。

在`C#`标准库中，典型的扩展案例为`System.Linq.Enumerable`类。  
该类为`System.Collections.Generic.IEnumerable<T>`类型添加了大量`LINQ`风格的扩展方法定义。

使用扩展方法时需要节制，滥用扩展方法会造成代码难以理解。



## 泛型
值类型转变为引用类型会经过`装箱(boxing)`操作，而引用类型转变为值类型则要经过`拆箱(unboxing)`操作。

一个容器需要接收多种类型时，可能就需要将接受参数的类型设置为`object`型(即所有类型的父类)。  
值类型在转化到`object`型时就需要进行装箱操作，频繁地装箱与拆箱会有较高的开销。  
`object`类型并不安全(可能同时接收到不同的类型)，因而可以使用**泛型**来**显式指定**需要接收的类型(编译器会检查接收类型是否符合指定泛型)。  
对于值类型而言，使用泛型还可以避免重复的装箱与拆箱操作。

### 泛型约束
C#中泛型可以使用`where`关键字进行泛型约束，例如：

```cs
class A<T> where T : XXX
{
	S Get<S>() where S : XXXX { }
}
```

拥有多个泛型参数时，使用多个`where`语句限制多个泛型参数：

```cs
// 泛型参数T必须从XXX类型派生，泛型参数V必须从XXXX类型派生
class B<T, V> where T : XXX where V : XXXX { }
```

在C#中，泛型约束支持以下形式：

- `T : struct` 限制类型参数为结构类型，存在多个泛型约束条件时，该条件需要置于首位
- `T : class` 限制类型参数为引用类型，存在多个泛型约束条件时，该条件需要置于首位
- `T : new()` 类型参数必须具有可访问的无参构造函数，存在多个泛型约束条件时，该条件需要置于末尾
- `T : 接口名称` 类型参数必须实现了指定接口
- `T : 类名称` 类型参数必须为指定类型或其子类
- `T : V` 类型参数`T`必须为类型参数`V`的派生类型(裸类型约束)

一个泛型参数可以使用多个条件进行约束，例如：

```cs
// 泛型参数T必须为引用类型，同时从类型V派生
class C<T, V> where T : class, T : V { }
```

### *Variance* (变性)
泛型类型在使用不同类型参数时默认**不存在**继承关系。
如下所示：

```cs
csharp> class Child : Base { };
csharp> List<Base> list = new List<Child>(); //泛型参数的继承关系无法作用于范型自身
(1,20): error CS0029: Cannot implicitly convert type `System.Collections.Generic.List<Child>' to `System.Collections.Generic.List<Base>'
csharp> List<Base> list = new List<Child>() as List<Base>; //不可进行强制类型转换
(1,38): error CS0039: Cannot convert type `System.Collections.Generic.List<Child>' to `System.Collections.Generic.List<Base>' via a built-in conversion
```

使用`variances`特性可使类型参数的继承关系扩展到承载类型参数的泛型类型自身。  
`variances`特性分为`covariance`(协变)和`contravariance`(逆变)。  
在泛型参数前使用`int/out`关键字表示该泛型参数**变性**，如下所示：

```cs
csharp> interface ICovariance<in T> {}; //逆变
csharp> interface IContravariance<out T> {}; //协变
```

与`Scala`、`Kotlin`不同，在C#中，`variances`仅支持`interface`和`delegate`。  
`class`和`struct`无法使用`variances`特性，如下所示：

```cs
csharp> class Test<out T> {}; 
(1,17): error CS1960: Variant type parameters can only be used with interfaces and delegates
csharp> struct Test<in T> {};
(1,17): error CS1960: Variant type parameters can only be used with interfaces and delegates
```

- `Covariance` (协变)

	类型参数声明为`covariance`(协变)时，泛型类型的继承关系与类型参数相同。  
	如下所示：

	```cs
	csharp> interface ICovariance<out T> {};
	csharp> class Covariance<T> : ICovariance<T> {};
	csharp> ICovariance<Base> covariance = new Covariance<Child>(); //协变
	```

- `Contravariance` (逆变)

	类型参数声明为`contravariance`(逆变)时，泛型类型的继承关系与类型参数相反。  
	如下所示：

	```cs
	csharp> interface IContravariance<in T> {};
	csharp> class Contravariance<T> : IContravariance<T> {};
	csharp> IContravariance<Child> contravariance = new Contravariance<Base>(); //逆变
	```

### 泛型类的静态成员
不同于Java中`Type Erasure`形式的泛型实现，`.Net`中采用类似C++的实现，同一泛型类使用不同泛型参数时会独立生成代码。  
C#中，同一泛型类使用不同类型参数时，各自的静态成员是相互独立的。  
静态成员共享仅在使用相同类型参数的泛型类之间。

如下代码所示：

```cs
struct Test<T>
{
	public static int a;
}

class Program
{
	static void Main(string[] args)
	{
		Test<int>.a = 100;
		Test<uint>.a = 200; //两个a并不是同一个
		Console.WriteLine(Test<int>.a);
	}
}
```

输出结果：

```
100
```



## *delegate* (委托) 和 *event* (事件)
**委托**让C#拥有了函数对象的概念，使一个方法可以作为参数被传递。  
**事件**让C#拥有了语言级别的消息通信机制。

### *delegate* (委托)
委托是C#特有的概念，委托的作用类似于C/C++中的函数指针，但委托是类型安全的。

在`C#`中，委托实际上是一个类，因而使用方式与`class`类似。  
委托支持加减运算符操作，一个委托实例能够通过加法运算绑定多个**签名相同**的函数。

定义委托：

```cs
delegate 返回值类型 委托名(参数表);
```

委托的定义可以在全局、命名空间或是作为某个类的成员，但委托的定义不能放在方法体内部。

委托前可以使用访问权限关键字(`public`、`private`、`protected`等)进行限制，但委托定义不能使用`static`关键字(委托实例作为一个**类的成员**存在时才可以使用`static`关键字)。  
委托可以绑定`static`或是非`static`成员函数，委托同样可以绑定当前类之外的符合签名要求的其它类的可见成员函数(`public`、`internal`成员)。

`delegate`关键字还可以用来定义**匿名函数**，实例化委托或是增加委托实例绑定时都可以使用委托匿名函数。

委托实例化：

```cs
委托名 委托实例名; //与事件相同，委托也可以只定义不初始化
委托名 委托实例名 = new 委托名(符合委托签名的函数名);
委托名 委托实例名 = 符合委托签名的当前类成员函数名; //可以省略使用构造函数
委托名 委托实例名 = 类实例/类名.符合委托签名的公有非static/static成员函数名; //委托同样可以绑定到其他类的可见成员函数
委托名 委托实例名 = delegate(符合委托签名的参数表) //匿名委托
{
	函数内容;
};
```

增加/删除委托绑定函数：

```cs
委托实例名 += 符合委托签名的函数名;
委托实例名 -= 已绑定到委托的函数名;
委托实例名 += delegate(符合委托签名的参数表)
{
	函数内容;
};
```

一个委托可以同加减运算符动态地更改绑定的函数个数。  
委托在使用时类似一个普通的函数，调用委托：

```cs
委托实例名(符合委托签名的参数表);
```

调用委托会把委托绑定的所有函数按照绑定的先后次序**依次执行**。  
若绑定的方法拥有返回值，则将**最后一个**绑定方法的返回值作为整个委托实例的返回值。  
委托类型作为函数的形参时，传入实参时可以直接使用符合委托签名的函数名，无需手动使用`new`操作符构建委托对象。

### *event* (事件)
事件是委托的扩展概念，事件本质上是一类特殊的委托实例(不是委托类型)，创建事件前需要先定义一个委托，然后才能将事件与委托绑定。

定义事件：

```cs
event 委托名 事件名;
event 委托名 事件名 = new 委托名(符合委托签名的函数名); //事件也可以在定义时就初始化
event 委托名 事件名 = 符合委托函数签名的函数名; //可以省略使用构造函数
event 委托名 事件名 = delegate(符合委托签名的参数表) //匿名委托
{
	函数内容;
};
```

给事件添加/删除处理函数：

```cs
事件名 += 符合委托签名的函数名;
事件名 -= 已绑定到事件的函数名;
事件名 += delegate(符合委托签名的参数表)
{
	函数内容;
};
```

触发事件：

```cs
事件名(符合委托签名的参数表);
```

事件是一种特殊的**委托实例**：

- 与委托不同，不能在全局区域和命名空间中定义事件，只能将事件作为某个类的成员来进行定义。
- 事件与普通的成员类似，受到类的访问权限控制。
- 事件的访问权限不能高于用于定义事件的委托。
- 调用事件与调用委托实例的方式完全相同。

事件机制是其他`C#`高级技术的基础。

实例代码：

```cs
using System;

delegate void Delegate(string str); //委托可以定义在全局区域或是命名空间

class Program
{
	static event Delegate Event; //定义事件

	static void Main(string[] args)
	{
		Event += str => Console.WriteLine(str); //为事件绑定方法
		Event("Test Event!"); //触发事件
	}
}
```

输出结果：

```
Test Event!
```

### 自定义添加/删除操作的事件
在定义事件时，可以选择自行实现事件的`+=`、`-=`操作符，语法类似**属性**：

- 使用`add`、`remove`关键字标志代码块来对应`+=`、`-=`操作符的行为。
- 与**属性**定义中的`set`代码块类似，事件定义中的`add`、`remove`代码块中包含**隐含参数**`value`，`value`代表操作符的参数，即符合事件委托签名的方法。
- `add`、`remove`代码块不包含其它参数，同时代码块也没有返回值(返回`void`)。

示例代码如下所示：

```cs
using System;

delegate void Delegate(string str);

class Program
{
	static event Delegate Event //定义事件
	{
		add //对应事件的"+="操作符
		{
			XXXX += value //隐含参数value表示传入的方法
			//do something...
		}
		remove //对应事件的"-="操作符
		{
			XXXX -= value
			//do something...
		}
	}
}
```

自定义`+=`、`-=`运算符行为的事件**不能**像普通事件那样直接以函数的语法调用，调用时编译器会报错：

```
error CS0079: The event XXX can only appear on the left hand side of += or -= operator
```

自定义运算符事件的真正用途是为其它事件提供**包装**，实例如下所示：

```cs
using System;

delegate void Delegate(string str); //委托可以定义在全局区域或是命名空间

class Program
{
	private static Delegate _event; //真正用于绑定方法的事件

	// 自定义事件，在添加、移除方法时在终端输出信息
	static event Delegate Event
	{
		add //对应事件的"+="操作符
		{
			Console.WriteLine("Add Method!"); //在终端打印"Add Method!"
			_event += value; //将传入的方法绑定到_event上
		}
		remove //对应事件的"-="操作符
		{
			Console.WriteLine("Remove Method!"); //在终端打印"Remove Method!"
			_event -= value; //将传入的方法与_event解绑
		}
	}

	static void Main(string[] args)
	{
		Delegate del = str => Console.WriteLine(str);

		Event += del; //事件绑定委托

		//Event("Test Event!"); //使用Event()触发事件会在编译时报错
		_event("Test Event!"); //触发事件还是需要使用真正被包装的事件

		Event -= del; //事件与委托解绑
	}
}
```

输出结果：

```
Add Method!
Test Event!
Remove Method!
```



## *Lambda*
在`C#3.0`之后，引入了`Lambda表达式`的概念，基本语法为：

```cs
() => 单一表达式;
(参数表) => 单一表达式;
单个参数 => 单一表达式;
(参数表) => { 多行表达式; };
```

- 当参数表中只有一个参数时，参数表外的括号可以省略，但有多个参数或是无参数时括号不可省略。
- 参数表中可以不显式指定参数类型，在表达式只有一条语句时，该语句如有返回值，则被作为整个`Lambda`的返回值。
- 如果表达式有多条语句(使用花括号)时，需要显式使用`return`关键字指定返回值。
- 参数表可以不指定参数类型交由编译器隐式推导，也可以显式指定参数类型，显式指定与隐式指定不可混用，一旦有参数使用了显式指定或隐式指定，其余的参数必须使用相同的指定方式。

### *Lambda* 实现委托(delegate)
在C#中，`Lambda`概念与委托相通，可以使用`Lambda`以更简洁的方式代替匿名委托实现委托实例。

例如：

```cs
delegate int GetDouble(double num1, double num2);

GetDouble getDouble1 = delegate(double num1, double num2) { return (int)(num1 + num2); };
GetDouble getDouble2 = (num1, num2) => (int)(num1 + num2);
GetDouble getDouble3 = (double num1, double num2) => { return (int)(num1 + num2); };		//三种形式效果完全相同
```

需要注意的是，使用`Lambda`代替匿名委托虽然能够减少代码量，但这并不代表`Lambda`能够完全取代匿名委托。  
`Lambda`中参数不能带有关键字`ref`、`out`，如果需要使用**引用参数**则依然需要使用匿名委托。

### 使用函数对象表示 *Lambda*
C#中定义了一系列类型用来表示委托和Lambda对象。

- 使用`Action`表示不带参数且返回值为`void`类型的`Lambda`，注意，不需要也**不能**画蛇添足地写成`Action<>`形式。
- 使用`Action<T1, T2...>`表示带参数的`void`型返回值的`Lambda`。
- 使用`Func<T1, T2..., R>`表示返回值类型不为空的`Lambda`(**最后一个**泛型参数为函数返回值的类型)。
- `Action<>`、`Func<>`等泛型类型至多接收`8`个参数。
- `C#`中的`Lambda`**不能**直接加括号执行，而是需要创建一个函数对象或显式指明类型才能执行(即不能直接`(() => {})();`来执行`Lambda`)。
- 与`Java`的**残废**`Lambda`不同，`C#`的`Lambda`可以捕获并**修改**外部作用域变量，而`Java`中外部作用域变量在`Lambda`中带有`final`属性，只能读取不能更改。

### *Lambda* 作用域
在`C#`中，`Lambda`能够访问到在`Lambda`被定义的作用域中的所有成员。  
如果`Lambda`表达式在类中被定义，则`Lambda`表达式能够访问到类的成员。  
如同函数一样，`Lambda`有自己的作用域，`Lambda`内部定义的变量在外部作用域**不可访问**。

示例代码-1：

```cs
using System;

class Test
{
	static int num = 100;
	static Action setNum200 = () => num = 200;

	static void SetNum(int newNum) {
		/*
			不能直接执行Lambda，需要创建函数对象或显式类型转换才能执行。
			另一种写法： ((Action<int>)(n => num = n))(newNum);
		*/
		new Action<int>(n => num = n)(newNum);
	}

	static void Main(string[] args)
	{
		Console.WriteLine(num);
		setNum200();
		Console.WriteLine(num);
		SetNum(500);
		Console.WriteLine(num);
	}
}
```

输出结果：(Mono 4.0.2 && ArchLinux x64)

```
100
200
500
```

### 使用 *Lambda* 语法定义成员函数
在`C# 6.0`中，开始支持使用`Lambda`语法直接定义**单行**的成员函数。  
**示例代码-1**使用新的语法可以使用如下格式书写：

示例代码-2：

```cs
using System;

class Test
{
	static int num = 100;
	static Action setNum200 = () => num = 200;

	static void SetNum(int newNum)
		=> new Action<int>(n => num = n)(newNum); //直接使用Lambda实现成员函数

	static void Main(string[] args)
	{
		Console.WriteLine(num);
		setNum200();
		Console.WriteLine(num);
		SetNum(500);
		Console.WriteLine(num);
	}
}
```

在`C# 6.0`中，表达式语法以下限制：

- 不能应用于**构造方法**、**析构方法**和**属性访问器**。
- 单行表达式不能为`throw`语句(不能在表达式中抛出异常)。

在`C# 7.0`中，表达式语法更加完善，在以上场景可以使用。



## *Pattern Matching* (模式匹配)
`C# 7.0`中加入了**模式匹配**特性，支持根据对象类型提供不同的行为。

在`C# 7.0`中，支持模式匹配的新特性包括：

- `is`表达式。
- `switch`声明更新。

### *is* 表达式
`is`表达式具有比较对象类型的功能，在早期版本的`C#`中，比较变量类型并进行转换：

```cs
object obj = 100;

int num;
if (obj is int)
	num = (int)obj;
```

在`C# 7.0`中，可以在比较对象类型相同时直接创建变量：

```cs
object obj = 100;

int num;
if (obj is int i)
	num = i;
```

### *switch* 模式匹配
在`C# 7.0`中，`switch`表达式的`case`标签中支持根据对象类型进行跳转：

```cs
object xxx = ...;

switch (xxx)
{
	// 匹配 int 类型
	case int num:
		...
		break;
	// 匹配 double 类型
	case double num:
		...
		break;
	default:
		...
		break;
}
```

若不需要在匹配类型后使用变量，则可使用下划线`_`代替变量名称：

```cs
object xxx = ...;

switch (xxx)
{
	case string _:
		...
		break;
	default:
		...
		break;
}
```

`case`标签可以带有`when`子句，用于添加额外的匹配条件，类似于`Scala`中的**守卫**语法：

```cs
object xxx = ...;

switch (xxx)
{
	// 匹配 int 类型，且需要匹配的数值大于100
	case int num when num > 100:
		...
		break;
	// 匹配 string 类型，且需要匹配的字符串长度大于5
	case string str when str.Length > 5:
		...
		break;
	default:
		...
		break;
}
```



## 并发编程
在`C#`中，除了常见的`Thread`类，主要的并发技术有**异步委托**、`Task`类、`async/await`等。

### *Thread* 类
与常规的**OOP**语言类似，C#中也可以使用`Thread`类来进行并发编程，`Thread`类完整路径为`System.Threading.Thread`。

- 创建与启动线程

	`Thread`类拥有四种构造函数，可以分别以`ThreadStart`或`ParameterizedThreadStart`委托实例做为参数构建一个线程对象。  
	两种委托的区别是前者不能带有参数，后者带有一个`Object`类型的参数，两种委托返回值都为`void`。  
	`Thread`类在构造时还可以接收一个`int`型参数用于指定线程的最大堆栈大小。

	使用`Thread.Start()`方法可以启动线程，如下代码所示：

	```cs
	using System;
	using System.Threading;

	class Program
	{
		static void Main(string[] args)
		{
			Thread thread = new Thread(() => Console.WriteLine("This is thread!"));
			thread.Start();
			thread = new Thread(arg => Console.WriteLine("The arg is: " + arg));
			thread.Start("test args.");
		}
	}
	```

	运行结果：

	```
	This is thread!
	The arg is: test args.
	```

- 等待线程结束
	
	使用成员方法`Thread.Join()`能够等待指定线程结束，在等待的线程结束前，该方法会一直阻塞**当前**线程。

- 获取线程ID

	每个线程都有独立的线程ID。  
	`Thread.CurrentThread.ManagedThreadId`属性保存了当前线程的ID，可以通过比较线程ID来判断代码是否在相同的线程执行。

### 异步委托
委托实例执行操作默认**同步**执行，但委托实例同样可以**异步**执行操作。

- 使用`BeginInvoke()`进行异步回调

	`BeginInvoke()`除了接收原有委托签名的参数之外，参数表尾部额外带有两个参数，分别为`AsyncCallback`委托类型和`object`类型：

	1. `AsyncCallback`委托在回调委托运行结束之后触发，`AsyncCallback`委托接收一个`IAsyncResult`类型的参数。
	1. `object`类型用于传递一些参数给`AsyncCallback`委托。

	`BeginInvoke()`的最后两个参数可以为`null`。  
	`BeginInvoke()`返回`IAsyncResult`类型：
	
	1. 使用`IAsyncResult.IsCompleted`属性可以判断回调委托的执行状态。
	1. 使用`IAsyncResult.AsyncState`属性获取`BeginInvoke()`参数表中的最后一个`object`类型的传入参数。

- 使用`EndInvoke()`等待异步委托返回

	若需等待异步执行的委托结束，可以使用`EndInvoke()`成员函数。

	- `EndInvoke()`接受一个`IAsyncResult`类型的参数(即`BeginInvoke()`的返回值)。
	- `EndInvoke()`的返回值即为异步委托的返回值。
	- 在异步委托执行完毕之前，`EndInvoke()`会一直阻塞当前线程，直到异步委托结束。

	如下代码所示：

	```cs
	using System;
	using System.Threading;

	delegate int Delegate();

	class Program
	{
		static void Main(string[] args)
		{
			//用于回调的委托
			Delegate del = () =>
			{
				Thread.Sleep(1000);
				Console.WriteLine("Thread is running!");
				return 100;
			};

			//使用BeginInvoke()进行异步委托回调
			IAsyncResult result = del.BeginInvoke(ar =>
			{
				//异步委托结束时执行该Lambda，打印传入参数
				Console.WriteLine("The object arg is: {0}", (int)ar.AsyncState);
			}, 200);

			Console.WriteLine("Program start...");
			Console.WriteLine("The return value is: {0}", del.EndInvoke(result));

			//使用IAsyncResult.IsCompleted属性判断委托是否执行完毕
			Console.WriteLine("The thread status is: {0}", result.IsCompleted);
		}
	}
	```

	运行结果：

	```
	Program start...
	Thread is running!
	The return value is: 100
	The thread status is: True
	The object arg is: 200
	```

	委托实例`del`虽然先被调用，但由于是异步调用，`Sleep()`了1000毫秒之后再输出的字符位于主线程之后。

- 使用`WaitOne()`等待异步委托返回

	`BeginInvoke()`的返回值`IAsyncResult`类型的`AsyncWaitHandle`属性会返回一个`WaitHandle`类型的等待句柄：

	- `WaitHandle.WaitOne()`接受`int`型参数作为超时时间，使用此方法可以实现等待指定时间(单位为**毫秒**)的效果。
	- `WaitHandle.WaitOne()`的返回值为`bool`类型，用于表示异步委托是否结束。

	如下所示：

	```cs
	using System;
	using System.Threading;

	delegate int Delegate();

	class Program
	{
		static void Main(string[] args)
		{
			//用于回调的委托
			Delegate del = () =>
			{
				Thread.Sleep(1000);
				Console.WriteLine("Thread is running!");
				return 100;
			};

			//使用BeginInvoke()进行异步委托回调
			IAsyncResult result = del.BeginInvoke(ar =>
					Console.WriteLine("The object arg is: {0}", (int)ar.AsyncState), 200);

			Console.WriteLine("Program start...");
			if (result.AsyncWaitHandle.WaitOne(1000))
				Console.WriteLine("The return value is: {0}", del.EndInvoke(result));

			//使用IAsyncResult.IsCompleted属性判断委托是否执行完毕
			Console.WriteLine("The thread status is: {0}", result.IsCompleted);
		}
	}
	```

	执行结果：

	```
	Program start...
	The thread status is: False
	```

	超时时间设为1000毫秒，由输出结果可知，此时异步委托尚未执行完毕，因而`IAsyncResult.IsCompleted`属性为`false`。

### *Task* 类
`Task`类是`.NET 4.0`之后提供的异步操作抽象，完整路径为`System.Threading.Tasks.Task`。

`Task`类用于表示无返回值的异步操作，对于带有返回值的异步操作应使用`Task`类的子类`Task<TResult>`。  
`Task`类创建的任务会加入线程池中。

`Task/Task<TResult>`类的主要构造函数如下：

```cs
// 接收Action类型作为异步操作的执行内容
public Task(Action action);
// 首参数为带有一个参数的Action<Object>类型，第二参数为要传入的内容
public Task(Action<object> action, object state);
// TaskCreationOptions类型为枚举，并设定TaskScheduler的执行策略
public Task(Action action, TaskCreationOptions creationOptions);

// 在Task<TResult>类中接收Func<TResult>类型作为异步执行的内容
public Task(Func<TResult> function);
public Task(Func<object, TResult> function, object state);
```

创建完毕的`Task`可以使用`Start()`方法开始执行：

```cs
// 将任务添加到当前的TaskScheduler(任务调度器)中，任务调度器选择合适的时机执行
public void Start();
// 将任务添加到特定的TaskScheduler中
public void Start(TaskScheduler scheduler);
```

在实际开发中，更多情况下使用`Task`类的静态方法`Run()`或者工厂类`TaskFactory`的成员方法`StartNew()`来创建和启动新的任务。

`Task`类中的一些常用方法：

```cs
// 将参数中的异步操作在当前调度器中排队，并返回Task对象
public static Task Run(Action action);
public static Task<TResult> Run<TResult>(Func<TResult> function);

// 等待Task完成
public void Wait(); //等待当前任务完成
public static void WaitAll(params Task[] tasks); //等待任务数组中的所有任务完成
public static bool WaitAll(Task[] tasks, int millisecondsTimeout;) //等待指定时间
```

### *async/await* 关键字
`C# 5.0`之后引入了`async`和`await`关键字，在语言层面给予了并发更好的支持。

1. `async`用于标记**异步方法**：

	- `async`关键字是**上下文关键字**，只有在修饰方法与Lambda时才会被当作关键字处理，在其它区域将被作为标识符处理。
	- `async`关键字可以标记静态方法，但不能标记**入口点**(`Main()`方法)。
	- `async`标记的方法返回值必须为`Task`、`Task<TResult>`、`void`其中之一。

1. `await`用于等待异步方法的结果：

	- `await`关键字同样是**上下文关键字**，只有在`async`标记的方法中才被视为关键字。
	- `await`关键字可以用在`async`方法和`Task`、`Task<TResult>`之前，用于等待异步任务执行结束。

一个简单的`async`方法结构如下：

```cs
async Task testAsync()
{
	... //顺序执行的内容

	return await Task.Run(() =>
	{
		... //异步执行的内容
	});
}
```

并不是方法使用`async`关键字标记了就是异步方法，直接出现在`async`方法内部的语句也是同步执行的，**异步执行的内容**需要使用`Task`类执行。  
事实上，一个不包含任何`await`语句的`async`方法将是同步执行的，此时编译器会给出警告。

简单示例，使用`async/await`在屏幕并发输出内容：

```cs
using System;
using System.Threading;
using System.Threading.Tasks;

class Program
{
	// Task.Run()方法中的Function是真正异步执行的内容
	static async Task<int> Async() =>
		await Task.Run<int>(() =>
		{
			// 线程ID与Handler()方法不同
			Console.WriteLine("Async() Thread ID: [{0}]", Thread.CurrentThread.ManagedThreadId);

			for (int i = 0; i < 5; i++)
			{
				Thread.Sleep(100);
				Console.WriteLine("Async: Run{0}", i);
			}

			Console.WriteLine("Over");
			return 666;
		});

	// 返回值为void的async方法AsyncHandler()仅仅是包装器
	static async void AsyncHandler()
	{
		// 方法体中的内容实际为同步执行，与Main()函数线程ID相同
		Console.WriteLine("Handler() Thread ID: [{0}]", Thread.CurrentThread.ManagedThreadId);

		// 调用异步方法Async()不会阻塞，Async()方法开始异步执行
		Task<int> task = Async();

		// 每隔0.1s打印输出，此时异步方法Async()也在另一线程中执行，同步打印输出
		for (int i = 0; i < 3; i++)
		{
			Thread.Sleep(100);
			Console.WriteLine("Handler: Run{0}", i);
		}

		// 在使用await之前的代码都运行在与Main()函数相同的线程
		Console.WriteLine("Handler()-1 Thread ID: [{0}]", Thread.CurrentThread.ManagedThreadId);

		// AsyncHandler()中的循环执行3次，此时异步方法Async()尚未执行完毕，使用await关键字会阻塞函数
		// 在Main()函数中，从调用await开始，AsyncHandler()就已返回了
		Console.WriteLine(await task);

		// 使用await之后的代码运行在Async()方法所处的线程
		Console.WriteLine("Handler()-2 Thread ID: [{0}]", Thread.CurrentThread.ManagedThreadId);

		// 打印AsyncHandler()函数真正执行完毕信息
		Console.WriteLine("Handler Really Finished!");
	}

	// Main方法不能标记为异步
	static void Main(string[] args)
	{
		Console.WriteLine("Main() Thread ID: [{0}]", Thread.CurrentThread.ManagedThreadId);
		AsyncHandler();

		// 打印AsyncHandler()函数在Main()中已经执行完毕的信息
		Console.WriteLine("Handler Finished in Main!");

		// AsyncHandler()在实际执行完成之前就返回了，需要阻塞主线程等待AsyncHandler()真正执行完毕
		Console.ReadLine();
	}
}
```

输出结果：(`Mono 4.4.0 && ArchLinux x64`)

```
Main() Thread ID: [1]
Handler() Thread ID: [1]
Async() Thread ID: [4]
Handler: Run0
Async: Run0
Handler: Run1
Async: Run1
Async: Run2
Handler: Run2
Handler()-1 Thread ID: [1]
Handler Finished in Main!
Async: Run3
Async: Run4
Over
666
Handler()-2 Thread ID: [4]
Handler Really Finished!

```

由上述程序中不难看出，在`async`关键字标记的异步方法中，使用`await`之前的代码都是同步执行的，在调用了`await`之后，剩余的代码便异步运行在独立的线程。

### *lock* 关键字
`C#`语言提供了与`Java`中`synchronized`类似的`lock`关键字，基本语法如下：

```cs
lock (object)
{
	/* do something */
}
```

`lock`块开始时锁定`object`，在lock代码块结束后释放锁。  
锁定相同`object`的`lock`代码块同一时刻只能被一个线程执行。

- 基本用法

	`lock`关键字用法基本与`Java`中`synchronized`关键字类似：

	- 被锁定的`object`可以是引用类型实例、`this`引用、以及类型(`typeof(XXX)`)。
	- `lock`关键字**不能**用于修饰方法。
	- lock块中不能使用`await`关键字。

	`Java`笔记中的例子使用`C#`可以改写为：

	```cs
	using System;
	using System.Threading;

	class Example
	{
		public void ShowOne()
		{
			lock (this)
			{
				for (int i = 0; i < 5; i++)
				{
					Console.WriteLine(Thread.CurrentThread.Name + " ShowOne()");
					Thread.Sleep(100);
				}
			}
		}

		public void ShowTwo()
		{
			lock (this)
			{
				for (int i = 0; i < 5; i++)
				{
					Console.WriteLine(Thread.CurrentThread.Name + " ShowTwo()");
					Thread.Sleep(100);
				}
			}
		}
	}

	class Program
	{
		static void Main(string[] args)
		{
			Example example = new Example();

			Thread threadOne = new Thread(() => example.ShowOne());
			Thread threadTwo = new Thread(() => example.ShowTwo());
			threadOne.Name = "Thread One";
			threadTwo.Name = "Thread Two";
			threadOne.Start();
			threadTwo.Start();
		}
	}
	```

	输出结果：(`Mono 4.4.1 && ArchLinux x64`)

	```
	Thread One ShowOne()
	Thread One ShowOne()
	Thread One ShowOne()
	Thread One ShowOne()
	Thread One ShowOne()
	Thread Two ShowTwo()
	Thread Two ShowTwo()
	Thread Two ShowTwo()
	Thread Two ShowTwo()
	Thread Two ShowTwo()
	```

- lock实现

	`lock`块在实现上使用了`Monitor`类。  
	`lock (object) { ... }`实际相当于：

	```
	Monitor.Enter(object);
	...
	Monitor.Exit(object);
	```

 在进入lock块时调用`Monitor.Enter()`，离开时调用`Monitor.Exit()`。

- 死锁问题

	在`MSDN`中提到了应避免锁定`public`访问权限的内容，在实际编码中，常见的三类lock行为都可能引发死锁：

	- 若实例可被公共访问，则`lock(this)`可能死锁。
	- 若类型`XXX`可被公共访问，则`lock(typeof(XXX))`可能死锁。
	- 使用`lock("XXX")`时，同一进程中使用锁定相同字符串的代码块都将共享同一个锁。

	定义示例类`Example`：

	```cs
	class Example
	{
		public void Lock()
		{
			// 锁定this
			lock (this)
			{
				Console.WriteLine("Lock!");
			}
		}

		public static void StaticLock()
		{
			// 锁定类型
			lock (typeof(Example))
			{
				Console.WriteLine("StaticLock!");
			}
		}

		public void StringLock()
		{
			// 锁定字符串
			lock ("Lock")
			{
				Console.WriteLine("StringLock!");
			}
		}
	}
	```

	分别针对三种情况编写主函数测试。

	锁定`this`：

	```cs
	class Program
	{
		static void Main(string[] args)
		{
			Example example = new Example();

			lock (example)
			{
				Thread thread = new Thread(() => example.Lock());
				thread.Start();
				thread.Join();
			}
		}
	}
	```

	锁定类型：

	```cs
	class Program
	{
		static void Main(string[] args)
		{
			lock (typeof(Example))
			{
				Thread thread = new Thread(() => Example.StaticLock());
				thread.Start();
				thread.Join();
			}
		}
	}
	```

	锁定相同字符串：

	```cs
	class Program
	{
		static void Main(string[] args)
		{
			Example example = new Example();

			lock ("Lock")
			{
				Thread thread = new Thread(() => example.StringLock());
				thread.Start();
				thread.Join();
			}
		}
	}
	```

	三段代码执行后均无输出，且程序不退出，均死锁。

	需要注意的是，`lock`锁定对象是基于**线程**的，在同一线程内的代码不受影响。  
	如下所示的代码**不会**发生死锁：

	```cs
	using System;
	using System.Threading;

	class Example
	{
		public void Lock()
		{
			lock (this)
			{
				Console.WriteLine("Lock!");
			}
		}
	}

	class Program
	{
		static void Main(string[] args)
		{
			Example example = new Example();

			lock (example)
			{
				// 虽然实例example与Lock()方法内部锁定的this相同，但代码运行在同一线程，不会死锁。
				example.Lock();
			}
		}
	}
	```

	锁定类型、字符串时类似。



## *Reflection* (反射)
`C#`中的**反射**机制与`Java`等高级语言类似，反射机制的主要作用：

- 获取类型的成员信息，包括私有成员。
- 通过成员信息访问/修改字段、属性，调用成员方法。
- 判断类型的继承关系。
- 动态生成类型实例。
- 获取类型特性(`Attribute`)信息。

在`C#`中，反射相关API在命名空间`System.Reflection`中。

### 反射机制的相关类型
`C#`语言相比`Java`，类内的成员种类更多，用于描述成员信息反射类型结构也与`Java`不尽相同。

- `System.Type`

	表示一个类型(类、结构体、接口)。

- `System.Reflection.XxxInfo`

	表示类内的成员信息，主要包含：

	1. `ConstructorInfo` 构造器信息
	1. `FieldInfo` 成员变量(字段)信息
	1. `EventInfo` 事件信息
	1. `MethodInfo` 方法信息
	1. `PropertyInfo` 属性信息
	1. `TypeInfo` 类型信息

	继承树如下所示：

	```
	MemberInfo
	├─ Type
	│   └─ TypeInfo
	├─ MethodBase
	│   ├─ MethodInfo
	│   ├─ EventInfo
	│   └─ ConstructorInfo
	├─ FieldInfo
	└─ PropertyInfo
	```

	`PropertyInfo`、`MethodInfo`等描述类成员信息的类型均直接或间接从抽象基类`MemberInfo`中继承。

### *Type*/*TypeInfo* 类型
`C#`中的`Type`类型作用近似于`Java`反射机制中的`Class`类型，`Type`类定义了类型的反射操作。  
获取目标类型的`Type`实例是使用反射功能的起始步骤。

获取`Type`实例可以通过以下方式：

- `typeof(T)` 通过`typeof`操作符直接由类型获取
- `instance.GetType()` 通过目标实例的`GetType()`方法获取
- `Type.GetType("Xxx")` 通过`Type`类型的静态方法`Type.GetType(string)`以类型名称字符串获取

`TypeInfo`类型为`Type`类型的子类，在`Type`类型的基础上额外提供了以下内容：

- 用于访问各类成员信息集合的**属性**(`DeclaredMethods`、`DeclaredFields`等)。
- 用于获取由该类型定义的成员信息的**方法**(`GetDeclaredMethod()`、`GetDeclaredField()`等)。

### 反射获取成员信息
`Type`类型提供了与Java中`Class`类型类似的接口。  
反射获取类型成员信息的相关`API`遵循以下命名规则：

- `GetXxx(string)` 获取**指定公有成员**
- `GetXxxs()` 获取**所有公有成员**
- `GetXxx(string, BindingFlags)` 获取满足`BindingFlags`的**指定成员**
- `GetXxxs(BindingFlags)` 获取满足`BindingFlags`的**所有成员**

在`C#`中，`GetXxx()/GetXxxs()`方法包含多个重载版本。

- 默认的的无参`GetXxx()/GetXxxs()`方法只能获取公有成员。
- 通过`BindingFlags`枚举可设定反射的搜索范围(**是否搜索非公有成员**/**是否搜索继承而来的成员**/...)，多个`BindingFlags`可使用**逻辑或**操作符相连。

`BindingFlags`枚举完整路径为`System.Reflection.BindingFlags`，定义如下：

```cs
namespace System.Reflection
{
	// 指定控制绑定和由反射执行的成员和类型搜索方法的标志。
	[ComVisible(true)]
	[Flags]
	public enum BindingFlags
	{
		// 不指定绑定标志。
		Default = 0,
		// 指定当绑定时不应考虑成员名的大小写。
		IgnoreCase = 1,
		// 指定只应考虑在所提供类型的层次结构级别上声明的成员。不考虑继承成员。
		DeclaredOnly = 2,
		// 指定实例成员将包括在搜索中。
		Instance = 4,
		// 指定静态成员将包括在搜索中。
		Static = 8,
		// 指定公共成员将包括在搜索中。
		Public = 16,
		// 指定非公共成员将包括在搜索中。
		NonPublic = 32,
		// 指定应返回层次结构上的公共静态成员和受保护的静态成员。不返回继承类中的私有静态成员。静态成员包括字段、方法、事件和属性。不返回嵌套类型。
		FlattenHierarchy = 64,
		// 指定要调用一个方法。它不能是构造函数或类型初始值设定项。
		InvokeMethod = 256,
		// 指定“反射”应该创建指定类型的实例。调用与给定参数匹配的构造函数。忽略提供的成员名。如果未指定查找类型，将应用 (Instance |Public)。调用类型初始值设定项是不可能的。
		CreateInstance = 512,
		// 指定应返回指定字段的值。
		GetField = 1024,
		// 指定应设置指定字段的值。
		SetField = 2048,
		// 指定应返回指定属性的值。
		GetProperty = 4096,
		// 指定应设置指定属性的值。对于 COM 属性，指定此绑定标志与指定 PutDispProperty 和 PutRefDispProperty 是等效的。
		SetProperty = 8192,
		// 指定应调用 COM 对象的 PROPPUT 成员。PROPPUT 指定使用值的属性设置函数。如果属性同时具有 PROPPUT 和 PROPPUTREF，而且需要区分调用哪一个，请使用 PutDispProperty。
		PutDispProperty = 16384,
		// 指定应调用 COM 对象的 PROPPUTREF 成员。PROPPUTREF 指定使用引用而不是值的属性设置函数。如果属性同时具有 PROPPUT 和 PROPPUTREF，而且需要区分调用哪一个，请使用 PutRefDispProperty。
		PutRefDispProperty = 32768,
		// 指定提供参数的类型必须与对应形参的类型完全匹配。如果调用方提供一个非空 Binder 对象，则“反射”将引发异常，因为这意味着调用方正在提供的 BindToXXX 实现将选取适当的方法。
		ExactBinding = 65536,
		// 未实现。
		SuppressChangeType = 131072,
		// 返回其参数计数与提供参数的数目匹配的成员集。此绑定标志用于所带参数具有默认值的方法和带变量参数 (varargs) 的方法。此标志应只与 System.Type.InvokeMember(System.String,System.Reflection.BindingFlags,System.Reflection.Binder,System.Object,System.Object[],System.Reflection.ParameterModifier[],System.Globalization.CultureInfo,System.String[]) 一起使用。
		OptionalParamBinding = 262144,
		// 在 COM 互操作中用于指定可以忽略成员的返回值。
		IgnoreReturn = 16777216
	}
}
```

- 反射获取类型的**完整路径**

	`Type`类型的`FullName`成员属性保存了类型的**完整路径**：

	```cs
	typeof(Xxx).FullName;
	```

- 反射获取类型的**成员变量**/**成员属性**

	获取所有成员字段/属性信息：

	```cs
	// 获取所有公有成员字段
	public FieldInfo[] GetFields();
	// 获取bindingAttr范围内的所有成员字段
	public abstract FieldInfo[] GetFields(BindingFlags bindingAttr);
	// 获取成员属性的API类似
	public PropertyInfo[] GetProperties();
	public abstract PropertyInfo[] GetProperties(BindingFlags bindingAttr);
	```

	获取指定成员字段/属性信息：

	```cs
	// 获取指定名称的字段
	public FieldInfo GetField(string name);
	// 以bindingAttr为搜索标志，获取指定名称的字段
	public abstract FieldInfo GetField(string name, BindingFlags bindingAttr);
	// 获取指定名称的属性
	public PropertyInfo GetProperty(string name);
	// 通过名称与返回值类型获取属性
	public PropertyInfo GetProperty(string name, Type returnType);
	// 通过名称与参数类型获取属性(索引属性)
	public PropertyInfo GetProperty(string name, Type[] types);
	// 以bindingAttr为搜索标志，获取指定名称的属性
	public PropertyInfo GetProperty(string name, BindingFlags bindingAttr);
	public PropertyInfo GetProperty(string name, Type returnType, Type[] types);
	public PropertyInfo GetProperty(string name, Type returnType,
			Type[] types, ParameterModifier[] modifiers);
	public PropertyInfo GetProperty(string name, BindingFlags bindingAttr,
			Binder binder, Type returnType, Type[] types, ParameterModifier[] modifiers);
	```

- 反射获取类型的**成员方法**/**构造方法**

	获取所有成员方法/构造方法：

	```cs
	public MethodInfo[] GetMethods();
	public abstract MethodInfo[] GetMethods(BindingFlags bindingAttr);
	public ConstructorInfo[] GetConstructors();
	public abstract ConstructorInfo[] GetConstructors(BindingFlags bindingAttr);
	```

	获取指定签名的成员方法：

	```cs
	// 查找指定名称的成员方法(适用于不存在方法重载的情形，若查找到多个方法会抛出异常)
	public MethodInfo GetMethod(string name);
	// 查找指定名称的成员方法，使用签名参数获取方法
	public MethodInfo GetMethod(string name, BindingFlags bindingAttr,
			Binder binder, Type[] types, ParameterModifier[] modifiers);
	// 构造方法与类名相同，不存在使用名称获取的方式，应使用签名参数类型获取指定构造方法
	public ConstructorInfo GetConstructor(BindingFlags bindingAttr,
			Binder binder, Type[] types, ParameterModifier[] modifiers);
	...
	```

	- `binder`参数用于设定绑定相关信息，一般使用默认默认绑定`Type.DefaultBinder`。
	- `modifiers`参数用于设定签名参数的附加修饰符，一般可置为`null`，默认的联编程序不处理此参数。



## *Attribute* (特性)
`.Net`平台中的**特性**类似于`JVM`平台中的**注解**，作用都是向特定的元素添加元数据。

`MSDN`中关于**特性**的介绍：

```
特性提供功能强大的方法，用以将元数据或声明信息与代码（程序集、类型、方法、属性等）相关联。 特性与程序实体关联后，即可在运行时使用名为“反射”的技术查询特性。
```

在`Java`中，注解是**接口**，在`C#`中，特性是**类**。

### 使用特性
特性的基本语法为：

```cs
[特性名称(特性参数...)] 被修饰的元素
```

特性参数可以是定位参数、未命名参数或命名参数，定位参数部分需要匹配特性的构造器，命名参数是可选的，由特性类的公有属性和公有字段决定。

- 使用**多个**特性

	被多个特性修饰时，可以使用以下语法：

	```cs
	[特性名称1(特性1参数...)]
	[特性名称2(特性2参数...)]
	被修饰的元素
	```

	或将多个特性合并在一行中：

	```cs
	[特性名称1(特性1参数...), 特性名称2(特性2参数...)]
	被修饰的元素
	```

### 自定义特性
在`C#`中，所有特性都从基类`System.Attribute`中继承。

- 特性名称

	根据约定，所有特性类名称都以单词`Attribute`结束，以便将它们与`.NET Framework`中的其他项区分。  
	使用特性时，不需要追加`Attribute`后缀(使用带有`Attribute`后缀的全称也不会报错)。

- 特性类字段类型

	特性类可以提供一些字段和属性，不应提供公共方法，事件等。  
	在定义特性类的构造方法，字段和属性时，对数据类型有严格的要求。  
	类型只能为：`Boolean, Char, Byte, Sbyte, Int16, UInt16, Int32, Int64, Single, Double, String, Type, Object, Enum`，可以使用这些类型对应的数组类型。

- 定位参数与命名参数

	特性类可以具有定位参数和命名参数。  
	特性类的每个公共实例构造函数为该属性类定义一个有效的定位参数序列。  
	特性类的每个非静态公共读写字段和属性为该属性类定义一个命名参数。

- 构造函数

	特性类的构造函数决定了在使用特性时应传入怎样的特性参数(特性的定位参数需要与构造函数参数表相匹配)。  
	一个特性类可以拥有多个构造函数，使用特性时特性的定位参数只需与其中任意一个构造函数匹配即可。  
	定义了空参构造函数的特性在使用时只需要写出特性名称即可(特性参数的小括号省略)。

- 配置自定义特性

	使用`System.AttributeUsage`特性可以指定其它特性的使用方式。  
	`AttributeUsage`类的定义如下所示：

	```cs
	using System.Reflection;
	using System.Runtime.InteropServices;
	using System.Security;

	namespace System
	{
		[AttributeUsage(AttributeTargets.Class, Inherited = true)]
		[ComVisible(true)]
		public sealed class AttributeUsageAttribute : Attribute
		{
			public AttributeUsageAttribute(AttributeTargets validOn);
			public bool AllowMultiple { get; set; }
			public bool Inherited { get; set; }
			public AttributeTargets ValidOn { get; }
		}
	}
	```

	其中：

	- `AllowMultiple`属性用于设置一个特性可否被多次添加到一个元素上。
	- `Inherited`属性用于设定特性是否可被继承。
	- `ValidOn`属性用于设定特性的可作用对象(类型为`AttributeTargets`枚举，多个标识位使用逻辑或操作符`|`连接)。

	`AttributeTargets`枚举定义如下：

	```cs
	using System.Runtime.InteropServices;

	namespace System
	{
		[ComVisible(true)]
		[Flags]
		public enum AttributeTargets
		{
			Assembly = 1, //可以对程序集应用特性
			Module = 2, //可以对模块应用特性
			Class = 4, //可以对类应用特性
			Struct = 8, //可以对结构应用属性
			Enum = 16, //可以对枚举应用特性
			Constructor = 32, //可以对构造函数应用特性
			Method = 64, //可以对方法应用特性
			Property = 128, //可以对属性应用特性
			Field = 256, //可以对字段应用特性
			Event = 512, //可以对事件应用特性
			Interface = 1024, //可以对接口应用特性
			Parameter = 2048, //可以对参数应用特性
			Delegate = 4096, //可以对委托应用特性
			ReturnValue = 8192, //可以对返回值应用特性
			GenericParameter = 16384, //可以对泛型参数应用特性
			All = 32767 //可以对任何应用程序元素应用特性
		}
	}
	```

- 获取特性

	使用**反射**机制可以从指定元素提取特性。  
	例如`Attribute.GetCustomAttribute()`、`MemberInfo.GetCustomAttributes()`等相关方法可获取元素中的特性信息。

自定义特性示例：

```cs
using System;

// 特性Test1可作用于所有元素，不允许多次应用到一个元素，不可被继承
[AttributeUsage(AttributeTargets.All, AllowMultiple = false, Inherited = false)]
class Test1Attribute : Attribute
{
	public string Info = "";
	public int Id = 0;

	public Test1Attribute(int id) { Id = id; }

	public void ShowAttribute() => Console.WriteLine("Id: {0}, Info: {1}", Id, Info);
}

// 特性Test2可作用于类、属性、字段等元素，允许多次应用到一个元素，不可被继承
[AttributeUsage(AttributeTargets.Class | AttributeTargets.Property | AttributeTargets.Field,
		AllowMultiple = true, Inherited = false)]
class Test2Attribute : Attribute
{
	public string Name { get; set; } = "Null";

	public void ShowAttribute() => Console.WriteLine("Name: {0}", Name);
}

[Test1(1, Info = "Test1")] //使用特性时，可简化名称，Attribute后缀可省略
[Test2, Test2(Name = "Test2")] //AllowMultiple为true的特性可多次修饰一个元素，且多个特性可合并在一个语句中
class Test
{
	[Test1Attribute(2, Info = "Test1Attribute")] //使用特性也可以不省略Attribute后缀
	public string Property { get; set; } = "";
}

class Program
{
	static void Main(string[] args)
	{
		Console.WriteLine("Find attribute at class Test:");
		// 获取Test类上的特性
		foreach (var attr in typeof(Test).GetCustomAttributes(false))
		{
			if (attr as Test1Attribute != null)
				(attr as Test1Attribute).ShowAttribute();
			else if (attr as Test2Attribute != null)
				(attr as Test2Attribute).ShowAttribute();
		}

		Console.WriteLine();

		Console.WriteLine("Find attribute at property Test.Property:");
		// 获取Test类Name属性的特性
		foreach (var attr in typeof(Test).GetProperty("Property").GetCustomAttributes(false))
		{
			if (attr as Test1Attribute != null)
				(attr as Test1Attribute).ShowAttribute();
		}
	}
}
```

输出结果：

```
Find attribute at class Test:
Id: 1, Info: Test1
Name: Null
Name: Test2

Find attribute at property Test.Property:
Id: 2, Info: Test1Attribute
```



## 动态代理
在`C#`中，提供了类似`Java`中的**动态代理**机制。

`C#`中实现动态代理需要以下内容：

- 代理规则类需要从基类`System.Runtime.Remoting.Proxies.RealProxy`中派生。
- 被代理的类需要从基类`System.MarshalByRefObject`中派生。

与`Java`不同，在`C#`中，要使一个类能被代理需要该类从抽象基类`System.MarshalByRefObject`中继承。

如下所示：

```cs
using System;

class Xxx : MarshalByRefObject
{
	...
}
```

编写代理规则需要继承抽象基类`System.Runtime.Remoting.Proxies.RealProxy`，并实现其中的`Invoke()`抽象方法。

一个基本的`RealProxy`泛型封装如下所示：

```cs
// 限定泛型参数为MarshalByRefObject子类
class Proxy<T> : RealProxy where T : MarshalByRefObject
{
	// 保存被代理类的实例以及代理方法执行前后的操作
	private T t = null;
	private Action beforeAction = null;
	private Action afterAction = null;

	// 使用代理类Type做为基类MarshalByRefObject的构造方法参数
	public Proxy(T t, Action before = null, Action after = null) : base(typeof(T))
	{
		this.t = t;
		beforeAction = before;
		afterAction = after;
	}

	// 编写代理规则
	public override IMessage Invoke(IMessage msg)
	{
		// 将消息接口转换为方法调用消息接口
		IMethodCallMessage method = msg as IMethodCallMessage;

		// 执行实例方法调用前的代理操作
		beforeAction?.Invoke();

		// 通过方法消息执行真正的方法体
		object result = method.MethodBase.Invoke(t, method.Args);

		// 执行实例方法调用后的代理操作
		afterAction?.Invoke();

		// 构建方法返回信息
		return new ReturnMessage(result, null, 0, method.LogicalCallContext, method);
	}

	// 封装获取代理的接口
	public T GetProxy() => GetTransparentProxy() as T;
}
```

- `RealProxy`类中定义了`GetTransparentProxy()`方法，使用该方法可获取应用了代理规则之后的实例。
- 需要使用被代理类的`Type`类型做为基类`RealProxy`的构造函数参数，否则获取的代理实例为空指针。

简单的动态代理完整实例如下所示：

```cs
using System;
using System.Runtime.Remoting.Messaging;
using System.Runtime.Remoting.Proxies;

// 被代理的类，需要继承自基类MarshalByRefObject
class Example : MarshalByRefObject
{
	public string GetName() => "Example";
	public void Print(string str) => Console.WriteLine(str);
}

// 代理规则类，需要继承自基类RealProxy
class ExampleProxy : RealProxy
{
	private Example example = null;

	// 使用被代理类的Type类型做为基类构造器参数
	public ExampleProxy(Example example) : base(typeof(Example)) { this.example = example; }

	// 实现代理规则
	public override IMessage Invoke(IMessage msg)
	{
		IMethodCallMessage callMsg = msg as IMethodCallMessage;

		// 打印调用方法的名称
		Console.WriteLine("Call method: {0}", callMsg.MethodName);

		object result = callMsg.MethodBase.Invoke(example, callMsg.Args);

		// 打印调用方法的结果
		Console.WriteLine("Method result: {0}\n", result);

		return new ReturnMessage(result, null, 0, callMsg.LogicalCallContext, callMsg);
	}
}

class Program
{
	static void Main(string[] args)
	{
		// 构建原始实例
		Example example = new Example();
		// 获取应用了代理规则后的实例
		Example exampleProxy = new ExampleProxy(example).GetTransparentProxy() as Example;

		// 调用方法
		exampleProxy.GetName();
		exampleProxy.Print("Test Proxy!");

		Console.ReadLine();
	}
}
```

输出结果：

```
Call method: GetName
Method result: Example

Call method: Print
Test Proxy!
Method result:

```

由输出结果可知，在访问被代理实例的成员方法时触发了定义的代理操作。



## *FTP*
在`.Net`平台中，标准库内置了对`FTP`协议的支持。

`FTP`相关的类均位于`System.Net`命名空间，常见的有：

- `WebRequest` 表示对`URI`(统一资源标识符)的请求，是未实现的抽象类
- `WebResponse` 表示对`URI`(统一资源标识符)的回应，是未实现的抽象类
- `FtpWebRequest` 表示`FTP`协议的客户端请求，是`WebRequest`的子类实现
- `FtpWebResponse` 表示`FTP`协议的服务端回应，是`WebResponse`的子类实现
- `WebRequestMethods` 定义了各类协议的具体请求方法字符串，`FTP`协议的方法定义位于其内部类`WebRequestMethods.Ftp`中

### 创建 *FTP* 请求
`WebRequest`类的静态成员方法`WebRequest.Create(string)`，以`FTP`路径字符串为参数即可构建一个未设定操作的`FTP`请求：

```cs
string ftpUri = $"ftp://ip地址/路径...";
FtpWebRequest ftpRequest = WebRequest.Create(ftpUri) as FtpWebRequest;
```

对于需要账户的`FTP`服务端，需要在请求中设定账户和密码：

```cs
string ftpUserName = "...", ftpUserPassword = "...";
ftpRequest.Credentials = new NetworkCredential(ftpUserName, ftpUserPassword);
```

### 下载
在一个未设定操作的`FTP`请求创建完毕后，设置请求对象的`Method`属性为`RETR`(`FTP`协议中规定的下载指令)。

```cs
ftpRequest.Method = "RETR";
```

`WebRequestMethods.Ftp`中定义了各类`FTP`操作的指令文本，下载操作可以使用：

```cs
ftpRequest.Method = WebRequestMethods.Ftp.DownloadFile;
```

下载请求设定完毕后，执行以下操作：

1. 使用`WebRequest`类成员方法`WebRequest.GetResponse()`获取服务端回应，并向下转型为`FtpWebResponse`回应。
1. 使用`FtpWebResponse`类成员方法`FtpWebResponse.GetResponseStream()`获取回应中包含的文件流(`Stream`类)，并将其写入本地文件。

完整实例代码：

```cs
/// <summary>
/// 下载文件，保存到指定路径
/// </summary>
/// <param name="ftpUri">FTP目标路径</param>
/// <param name="savePath">保存到本地的路径</param>
/// <param name="ftpUserName">FTP用户名</param>
/// <param name="ftpUserPassword">FTP用户密码</param>
/// <returns>下载是否成功</returns>
public bool DownloadFile(string ftpUri, string savePath, string ftpUserName, string ftpUserPassword)
{
	bool result = false;

	try
	{
		FtpWebRequest request = WebRequest.Create(ftpUri) as FtpWebRequest;

		// 设定下载请求，填充FTP用户名/密码
		request.Method = WebRequestMethods.Ftp.DownloadFile;
		request.Credentials = new NetworkCredential(ftpUserName, ftpUserPassword);

		// 对于请求回应、文件流等资源，需要使用using语句或显式关闭资源
		using (FtpWebResponse response = request.GetResponse() as FtpWebResponse)
		{
			// 复制回应数据流到文件流中
			using (FileStream file = new FileStream(savePath, FileMode.Create))
				response.GetResponseStream().CopyTo(file);

			// 验证操作状态，打印操作结果
			Console.WriteLine($"Operate status: {response.StatusDescription}");
			if (response.StatusCode == FtpStatusCode.ClosingData) result = true;
		}
	}
	catch (Exception ex) { Console.WriteLine(ex.StackTrace); }

	return result;
}
```

### 上传
上传操作与下载略有不同，首先对未设定操作的`FTP`请求设置操作：

```cs
ftpRequest.Method = WebRequestMethods.Ftp.UploadFile;
```

若使用了**网络代理**(如翻墙工具等)，则还需要将请求的`Proxy`属性置为`null`，
否则会产生`用 HTTP 代理时不支持请求的 FTP 命令。`异常。

```cs
ftpRequest.Proxy = null;
```

之后执行以下操作：

1. 设定请求的`ContentLength`属性，表示上传文件的大小。
1. 使用`FtpWebRequest`类成员方法`FtpWebRequest.GetRequestStream()`获取请求文件流。
1. 将本地待上传文件复制到请求文件流中。
1. 使用`FtpWebResponse`类成员方法`FtpWebResponse.GetResponse()`获取操作回应。

完整实例代码：

```cs
/// <summary>
/// 上传文件到指定FTP路径
/// </summary>
/// <param name="ftpUri">FTP目标路径</param>
/// <param name="localPath">待上传的本地文件路径</param>
/// <param name="ftpUserName">FTP用户名</param>
/// <param name="ftpUserPassword">FTP用户密码</param>
/// <returns>上传是否成功</returns>
public bool UploadFile(string ftpUri, string localPath, string ftpUserName, string ftpUserPassword)
{
	bool result = false;

	try
	{
		FtpWebRequest request = WebRequest.Create(ftpUri) as FtpWebRequest;

		// 设定下载请求，填充FTP用户名/密码
		request.Proxy = null;
		request.Method = WebRequestMethods.Ftp.UploadFile;
		request.Credentials = new NetworkCredential(ftpUserName, ftpUserPassword);

		using (FileStream file = new FileStream(localPath, FileMode.Open))
		{
			// 设定待上传的文件大小，复制文件数据流到请求文件流中
			request.ContentLength = file.Length;
			using (Stream upStream = request.GetRequestStream()) file.CopyTo(upStream);
		}
		using (FtpWebResponse response = request.GetResponse() as FtpWebResponse)
		{
			// 验证操作状态，打印操作结果
			Console.WriteLine($"Operate status: {response.StatusDescription}");
			if (response.StatusCode == FtpStatusCode.ClosingData) result = true;
		}
	}
	catch (Exception ex) { Console.WriteLine(ex.StackTrace); }

	return result;
}
```



## *WinFrom* 开发注记
`C#`对应的**GUI**库为基于`.NET Framework`的`Windows Form`。

### 常见控件类型
在`Windows Form`中，控件相关的类大多派生于`System.Windows.Forms.Control`。  
控件的名称也与其它的GUI库类似：

- `Form` 窗体，类似于Qt中的**QFrame**
- `Label` 标签文本，类似于Qt中的**QLabel**
- `Button` 按钮，类似于Qt中的**QPushButton**
- `RadioButton` 单选框，类似于Qt中的**QRadioButton**
- `CheckBox` 复选框，类似于Qt中的**QCheckBox**
- `CheckedListBox` 多行复选框
- `ListBox` 列表框，类似于Qt中的**QListWidget**
- `TextBox` 简单文本框，类似于Qt中的**QLineEdit**
- `RichTextBox` 富文本框，类似于Qt中的**QTextEdit**
- `TreeView` 树形控件，类似于Qt中的**QTreeWidget**

### 容器控件
在`Windows From`中，常见的容器控件有：

- `Panel` 最基本的面板容器
- `GroupBox` 控件组面板，类似于Qt中的**QGroupBox**

部分容器自带布局，放入其中的控件会按照其布局排列：

- `FlowLayoutPanel` 流布局面板
- `TableLayoutPanel` 表格布局面板

### 布局与样式
在`Windows From`中，控件的大小与位置一般是固定的。  
若需要控件大小自动变化，则应使用`AutoSize`属性。  
一般情况下，控件的位置不会随着窗口大小的变化而自动排列位置，需要通过设置`Archor`属性来指定扩展的方向。  
控件还可以通过设置`Dock`属性指定需要停靠的边框。

### 控件事件
一个标准的`Windows Form`控件中定义了多种事件，通过将指定的事件处理函数绑定到事件上，当满足事件触发的条件时，绑定的函数便会被回调。  
一个事件可以绑定多个事件处理函数，一个事件处理函数也可以被多个事件绑定。

普通的事件签名没有限制，但`.NET Framework`类库中的所有事件均基于`EventHandler`委托，定义如下：

```cs
public delegate void EventHandler(object sender, EventArgs e);
```

`sender`参数指明了事件的发出者，而`e`参数携带了事件的具体信息，`EventArgs`是所有`.NET Framework`类库中事件的基类，
实际的事件类型只有符合`EventHandler`委托签名的函数才能被绑定到`Windows Form`的控件事件上。

常用的`Windows Form`控件事件有：

- `Load` 载入窗体时触发，一般可用于初始化一些UI设置(`Form`类)
- `Click` 点按控件时触发
- `MouseDown` 鼠标按下时触发
- `MouseUp` 鼠标抬起时触发
- `KeyDown` 按键按下时触发
- `KeyUp` 按键抬起时触发
- `GotFocus` 接收焦点时触发

### 接收Windows消息
在`Windows Form`中，所有从`System.Windows.Forms.Control`派生的类都包含以下方法：

```cs
protected override void WndProc(ref Message m);
```

重写其即可处理**Windows消息**。

`Message`类完整路径为`System.Windows.Forms.Message`，该类包装了Windows消息，包含以下属性：

- `HWnd` 获取或设置消息的窗口句柄
- `LParam` 指定消息的**LParam**字段
- `Msg` 获取或设置消息的**ID**号
- `Result` 指定为响应消息处理而向**Windows**返回的值
- `WParam` 获取或设置消息的**WParam**字段



## 调用 *C/C++* 动态链接库
C#支持调用`C/C++`语言编写的`dll`。

使用`DLLImport`特性修饰一个方法。  
加载动态链接库需要指定dll的路径以及符号名称：

```cs
[DLLImport("DLL Library", EntryPoint = "Symbol Name")]
public/protected/private extern Type Func(Type args...);
```

声明方法的名称可以与dll中导出符号名称不同，只需在标注的`EntryPoint`中写明对应的符号名称。  
声明的方法参数表必须与dll中的参数表**完全匹配**。

C#中的常见类型与C++中类型之间的转换关系：

| C++ | C# |
|:----|:---|
| void* | System.IntPtr |
| void** | ref System.IntPtr |
| unsigned char | System.Byte |
| short | System.Int16 |
| unsigned short | System.UInt16 |
| int | System.Int32 |
| int* | System.IntPtr |
| int** | ref System.IntPtr |
| unsigned int | System.UInt32 |
| long | System.Int64 |
| unsigned long | System.UInt32 |
| char | System.Char |
| char* | System.String |
| wchar_t* | System.String |
| const char* | System.String |
| float | System.Single |
| double | System.Double |
| byte* | System.Byte[] |
| unsigned char | System.Byte |
| unsigned char* | ref System.Byte |



## 特殊关键字

### *internal* 关键字
类和类成员前可以使用`internal`关键字。

- `internal`关键字修饰类

	`internal`关键字用在类、接口前表示只能在当前项目中访问该类、接口。  
	`internel`关键字修饰的类不能被`public`类继承。  
	默认不添加关键字的情况下，类和接口的访问属性即为`internal`。

- `internal`关键字修饰成员

	`internal`关键字用在类内成员之前表示只能在当前项目中访问该成员。  
	在对类内成员使用时，`internal`关键字可以搭配`protected`关键字使用，即定义一个只能被当前项目的子类访问的成员。

需要注意的是，`internal`修饰的类不能作为`public`成员出现在其它类中。

### *readonly* 关键字
`readonly`关键字用于修饰**运行时只读**变量。  
`readonly`变量的赋值操作只能发生在以下情形：

- 在变量定义时。
- 在变量所属类的构造函数中。

与`const`关键字的异同：

- `const`修饰的变量被视为**编译时常量**，`readonly`修饰的变量被视为**运行时常量**。
- `const`关键字修饰的变量须在**定义时**立即初始化。
- `const`仅能修饰**值类型**/`string`类型/`null`，`readonly`可以修饰任意类型，
- `const`修饰的变量自动带有`static`特性：

	`const`关键字与`static`关键字不能共同修饰相同变量。  
	`const`修饰的变量**可以**被定义在静态类中。

- `readonly`修饰的变量默认**不带有**`static`属性：

	`readonly`与`static`关键字可一同使用表示**静态只读**变量。

对于引用类型，不能使用`const`关键字修饰，要限制其修改只能使用`readonly`关键字。

### *partial* 关键字
`partial`关键字用于定义`部分类`(局部类型)，局部类型允许我们将一个类、结构或接口分成几个部分，分别实现在几个不同的源码文件中。

在`Windows From`中，窗口类代码便使用了部分类特性。  
对于同一个窗口类，由VS窗体编辑器生成的GUI代码在文件**GUI类名.Designer.cs**文件中，而由用户编写的界面控制代码放在**GUI类名.cs**文件中。  
两个文件中的代码本质上属于同一个类，`部分类`特性巧妙地隔离开了**由IDE产生的代码**与**用户自行编写的代码**，使代码结构更清晰。

### *params* 关键字
`params`用在方法的参数之前，用于标记可变参数。一个方法只能拥有一个`params`参数，且被`params`标记的参数必须为最后一个参数，并且是数组类型。

在调用含有`params`参数的方法时，方法末尾可以追加**任意数量**的类型相符的变量，例如：

```cs
using System;

class Program
{
	static void Print(params int[] nums)
	{
		foreach (int num in nums)
			Console.WriteLine(num);
	}

	static void Main(string[] args) =>
		Print(1, 2, 3, 4, 5); //多个int型参数都被添加到params关键字标记的数组中
}
```



## 常见问题

### 处理`\0`结尾字符串
在C#中，以`\0`结尾的`string`类型尾部的`\0`并不会被自动忽略，在输出是，中文环境下会显示`口口...`，删除字符串中的`\0`可以使用`string`类的`Replace()`成员方法进行字符串替换：

```cs
string test = "aaa\0\0\0";
Console.WriteLine(test); //输出 "aaa口口口"
string testNew = test.Replace("\0", ""); //将 \0 替换为空
Console.WriteLine(testNew); //输出 "aaa"
```

### MySQL 中 *TINYINT* 类型
在`MySQL`中没有内置的`bool`类型，`bool`类型常常使用最小的整型数据类型`TINYINT`表示。

在C#中，会将`TINYINT(1)`视为`bool`类型处理，对于类型为`TINYINT(1)`的列，使用`ToString()`方法转换得到的是文本`true/false`而非字面意义数值。  
要使`TINYINT`不被视为`bool`类型，需要调整数据列的显示宽度，即类型设为`TINYINT(2)`或是其它大于`1`的值。

### *DEBUG* 模式
在C#中，可使用类似C/C++的宏针对`DEBUG/RELEASE`模式下进行额外的操作，语法如下：

```cs
#if DEBUG
// do something...
#else
// do something...
#endif
```

### 输出代码文件名、行号
在输出日志时，常常需要输出打印日志的代码位置以便跟踪查看。

- 使用`StackStrace`获取调试信息

	使用`StackStrace`类通过反射可以得到函数调用者的栈信息，并从中获取代码信息。  
	使用`StackTrace`的`GetFrame(int index)`成员方法获取指定的堆栈帧(`StackFrame`类型)。

	- 索引`0`为当前函数堆栈的信息。
	- 索引`1`为函数调用者的堆栈信息，以此类推，可获取多级调用者信息。
	- 使用`StackFrame`类可以获得堆栈所在的方法名称、源码文件名称，代码行号等，还可进一步获得类型信息。

- `.Net 4.5`新增特性

	在`.Net 4.5`中引入了三种`Attribute`用于获取方法的调用成员名称、调用文件、调用代码行号：

	- `System.Runtime.CompilerServices.CallerMemberNameAttribute` 成员名称
	- `System.Runtime.CompilerServices.CallerFilePathAttribute` 调用文件
	- `System.Runtime.CompilerServices.CallerLineNumberAttribute` 调用行号

	三种特性用于修饰日志函数的参数(参数需要有默认值)，编译器会自动为参数补充对应的调用信息，如下所示：

	```cs
	using System.Runtime.CompilerServices;

	void PrintLog(string log,
			[CallerMemberName] string member = "",
			[CallerFilePath] string file = "",
			[CallerLineNumber] int line = 0)
	{
		Console.WriteLine("Log: {0}", log);

		Console.WriteLine("MemberName: {0}", member);
		Console.WriteLine("FilePath: {0}", file);
		Console.WriteLine("LineNumber: {0}", line);
	}
	```
