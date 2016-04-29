[TOC]

## 入口函数
C#中允许以下4种形式的入口函数：

```csharp
static void Main();
static void Main(string[] args);
static int Main();
static int Main(string[] args);
```

C#允许多种入口函数形式，一般采用第二种(默认)。
与Java不同，C#并不强制要求主类的类名与主类所在文件的文件名相同。
实际上，C#由于支持`部分类`特性，也不可能要求类名与源码文件名相同。



## 数据类型
C#的数据类型分为两类：值类型和引用类型。
一般而言，值类型用于**存储数据**，引用类型用于**定义行为**。

### 值类型(Value Type)
值类型具体包括**预定义值类型**、**自定义值类型**和**枚举类型**。

所有值类型隐式派生于`System.ValueType`类。
系统预定义的值类型`int`是`System`命名空间中`Sytem.Int32`结构体的别名。
`System.Int32`结构的定义为：

```csharp
public struct Int32 : IComparable, IFormattable, IConvertible, IComparable<int>, IEquatable<int>;
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

```csharp
public abstract class ValueType;
```

可空类型对应`System.Nullable<T>`结构体：

```csharp
public struct Nullable<T> where T : struct;
```

值类型实例通常分配在线程的**栈(stack)**上，并且不包含任何指向实例数据的指针，因为变量本身就包含了其实例数据。
值类型在复制时是**值传递(pass by value)**，会复制当前值类型变量包含的内容。

### 引用类型(Reference Type)
引用类型包括数组(派生于`System.Array`)，字符串`string`(`System.String`类的别名)，自定义类(派生于`System.Object`)，委托类型(派生于`System.Delegate`)，`object`类型(`System.Object`)的别名。

引用类型与值类型比较：

- 值类型和引用类型都可以**实现接口**，但值类型**不能**再派生出新的子类型。
- 引用类型可以为`null`，但值类型不行(除了**可空类型**)。
- 引用类型复制是传递引用，值类型复制是拷贝整个对象。
- 值类型分配内存在线程栈上，出栈自动释放；引用类型分配内存在托管堆上，由`GC`负责内存回收。



## 成员属性
C#类中成员有一种被称为`属性`。

- 属性的访问方式与成员变量类似；通过定义`set`和`get`块的内容，能够通过属性给成员变量赋值或是获取成员变量的值。
- `set`和`get`可以分别设置**访问权限**，不加关键字时访问权限与所在的属性相同。
- `set`块中使用关键字`value`来代表给属性的赋值。`get`块必须返回一个与属性类型相符的值。
- `set`块和`get`块**不是**必须同时存在的，只有`set/get`块的属性被称为`只读/只写属性`。
- 属性前允许使用`static`修饰，表示定义静态属性，与静态变量类似。

如下代码所示：

```csharp
using System;

class A
{
	int num = 0;

	public int a
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
		Console.WriteLine(a.a);
		a.a = 100;
		Console.WriteLine(a.a);
	}
}
```

输出结果：

```
0
100
```

可知，对类A中属性a的赋值通过a的set块中的value传给了A类私有成员num，通过a的get块获取了私有成员num的值。

### 自动成员属性
在`C#3.0`之后，可以使用更为简便的自动属性，只需使用`set`、`get`关键字，而**不必**定义一个与属性相关的变量并编写`set`、`get`块代码，编译器会**自动生成**一个**私有变量**保存属性的内容。
如上个例子中的成员属性a可以简写成：

```csharp
public int a { get; set; }
```

同时，不用定义私有变量`num`来存储属性的内容，编译器会自动生成一个变量。

### 成员属性初始化
在`C#6.0`中，开始支持对自动成员属性进行**类内初始化**，可以直接在类中对自动成员属性**赋初值**：

```csharp
public int a { get; set; } = "Hello World!";
```

该特性也同样支持**只读属性**：

```csharp
public int a { get; } = "Hello World!";
```



## 结构类型(struct)
与`C++`完全不同，`C#`中的`结构体`与`类`有**很大区别**：

- C#中的结构体为**值类型**，在**栈(stack)**中分配内存，而引用类型则仅在栈中保存**引用(reference)**，类型实体内存分配在**堆(heap)**中。同时由于结构体为值类型，因而复制结构体时是完全复制出一个新的结构体实例，而非引用类型的引用传递。
- C#中结构体的默认访问权限是`private`，且结构体成员变量**不能**直接赋初值(需要通过有参构造函数赋初值)。
- C#中结构类型全部继承自`System.ValueType`类，但结构体是隐式**密封(sealed)**的，**不能**被继承。
- C#中结构体可以用来实现接口。用来实现接口的结构体虽然本身为值类型，但如果发生**向上转型**重新变为父类接口对象则值类型的特性也将随之消失。
- 由于C#中结构体不能被继承，因此结构体定义时不能使用`sealed`和`abstract`关键字，结构体成员定义时也不能使用`protected`和`internal`等关键字。
- C#中结构体带有默认的无参构造函数，且该默认构造函数一直存在(无论你是否创建了有参构造函数)，默认的无参构造函数**不能**被自定义(改写)。
- 创建有参构造函数时，必须在该构造函数中初始化所有的成员变量，否则无法通过编译。
- 创建结构体时可以不使用`new`操作符，不使用`new`操作符创建的结构体对象中的结构体成员全部处于未初始化状态，需要经过初始化操作(手动访问赋值)之后方可使用。
- 如果需要使用结构体提供的有参构造函数，则必须使用`new`操作符进行对象创建，语法类似于`class`。
- 在C#中结构体成员可以使用`static`修饰，结构体也可以创建静态构造函数。
- 在C#中结构体中可以正常使用泛型。



## 静态构造函数
静态构造函数是C#中特有的概念，用于在类首次被使用前进行静态成员的初始化。

- 静态构造函数与普通构造函数一样在类中定义，但静态构造函数不能带有参数和访问权限，一个类/结构体只能定义一个静态构造函数，静态构造函数与类的无参构造函数虽然参数表相同，但不会冲突。
- 静态构造函数只能初始化静态成员(貌似是废话)，如果一个类中有静态成员赋了初值(类内初始化)，则.NET会自动为其创建默认的静态构造函数。
- 静态构造函数不需要手动调用，在首次使用创建类实例或是方位类的静态成员时会由.NET自动调用，静态构造函数在全局只会被**调用一次**。



## 静态类
在C#中，类定义前可以使用`static`关键字表示定义一个**静态类**。

- 静态类只能包含静态成员，且是密封(sealed)的，不能被实例化和继承。
- 静态类不能从普通类中派生，而静态类本身不可被继承，因而实际上所有静态类都从`object`中派生。
- 静态类不能定义普通构造函数，但能够定义静态构造函数。
- 静态类在首次被引用前加载，初始化其成员字段并调用该类的静态构造函数。
- 一个类的静态构造函数仅被调用一次，在程序驻留的应用程序域的生存期内，静态类一直保留在内存中。
- 扩展方法只能定义在静态类中。
- `const`常量自带静态特性，可以定义在静态类中。



## 扩展方法(Extension Methods)
扩展方法能够在不改变现有类结构的前提下，向已存在的类型添加方法，并让这些方法像普通成员方法一样地被调用。

- 扩展方法本质上是一种特殊的**静态方法**，且必须定义在**静态类**中。
- 扩展方法被定义为静态方法，但调用时的语法与实例方法相同。
- 扩展方法的第一个参数必须带有`this`关键字，且类型必须是需要被扩展的类型(即第一个参数接收被扩展类型的实例)。
- 扩展方法本质上是一个语法糖，并不是真正向已有的类中添加了成员方法，因此扩展方法无法访问被扩展类的**私有成员**。
- 扩展方法在编译成**IL**中间代码时会被转换为对静态方法的调用。

如下代码所示：

```csharp
using System;

static class ExtensionMethod
{
	public static bool IsNull(this object obj)
		=> obj == null ? true : false;
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
上个例子中代码在Scala中可以写成：

```scala
object Test extends App {

  implicit class ExtensionMethod(obj: Any) {
    def isNull = if (obj == null) true else false
  }

  var obj: Any = null
  println(obj.isNull)
}
```

输出结果：

```
true
```



## 泛型
值类型转变为引用类型会经过`装箱(boxing)`操作，而引用类型转变为值类型则要经过`拆箱(unboxing)`操作。
一个容器需要接收多种类型时，可能就需要将接受参数的类型设置为`object`型(即所有类型的父类)，值类型在转化到`object`型时就需要进行装箱操作，频繁地装箱与拆箱会有较高的开销。
`object`类型并不安全(可能同时接收到不同的类型)，因而可以使用**泛型**来**显式指定**需要接收的类型(编译器会检查接收类型是否符合指定泛型)，对于值类型而言，使用泛型还可以避免重复的装箱与拆箱操作。

C#中泛型可以使用`where`关键字进行泛型约束，指定接收的类型的继承关系，例如：

```csharp
class A<T> where T : B
{
	/* code */
}
```

就指定了泛型类T必须是`B`或`B的子类`。

### 泛型类的静态成员
在C#中，同一个泛型类的不同泛型类型的静态成员是相互独立的，静态成员共享只在同一种泛型类型的泛型类之间。
例如：

```csharp
struct Test<T>
{
	static public int a;
}

class Program
{
	static void Main(string[] args)
	{
		Test<int>.a = 100;
		Test<uint>.a = 200;				//两个a并不是同一个
		Console.WriteLine(Test<int>.a);
	}
}
```

输出结果：

```
100
```



## 委托(delegate)和事件(event)
**委托**让C#拥有了函数对象的概念，使一个方法可以作为参数被传递。
**事件**让C#拥有了语言级别的消息通信机制。

### 委托(delegate)
委托是C#特有的概念，委托的作用类似于C/C++中的函数指针，但委托是类型安全的。

在C#中，委托实际上是一个类，因而使用方式与`class`类似。
委托支持加减运算符操作，一个委托实例能够通过加法运算绑定多个**签名相同**的函数。
定义委托：

```csharp
delegate 返回值类型 委托名(参数表);
```

需要注意的是，委托与类以及函数类似，委托的定义是不能嵌套在函数中的。委托的定义可以在全局、命名空间或是作为某个类的成员，但委托的定义不能放在函数的函数体内。

委托前可以使用访问权限关键字(`public`、`private`、`protected`等)进行限制，但委托定义不能使用`static`关键字(委托实例作为一个**类的成员**存在时才可以使用`static`关键字)。
委托可以绑定`static`或是非`static`成员函数，委托同样可以绑定当前类之外的符合签名要求的其它类的可见成员函数(`public`、`internal`成员)。

`delegate`关键字还可以用来定义**匿名函数**，实例化委托或是增加委托实例绑定时都可以使用委托匿名函数。

委托实例化：

```csharp
委托名 委托实例名;											//与事件相同，委托也可以只定义不初始化
委托名 委托实例名 = new 委托名(符合委托签名的函数名);
委托名 委托实例名 = 符合委托签名的当前类成员函数名;			//可以省略使用构造函数
委托名 委托实例名 = 类实例/类名.符合委托签名的公有非static/static成员函数名;	//委托同样可以绑定到其他类的可见成员函数
委托名 委托实例名 = delegate(符合委托签名的参数表)			//匿名委托
{
	函数内容;
};
```

增加/删除委托绑定函数：

```csharp
委托实例名 += 符合委托签名的函数名;
委托实例名 -= 已绑定到委托的函数名;
委托实例名 += delegate(符合委托签名的参数表)
{
	函数内容;
};
```

一个委托可以同加减运算符动态地更改绑定的函数个数。
委托在使用时类似一个普通的函数，调用委托：

```csharp
委托实例名(符合委托签名的参数表);
```

调用委托会把委托绑定的所有函数按照绑定的先后次序**依次执行**，如果绑定的函数拥有返回值，则将**最后一个**绑定函数的返回值作为整个委托实例的返回值。
委托类型作为函数的形参时，传入实参时可以直接使用符合委托签名的函数名，无需手动使用new操作符构建委托对象。

### 事件(event)
事件是委托的扩展概念，事件本质上是一类特殊的委托实例(不是委托类型)，创建事件前需要先定义一个委托，然后才能将事件与委托绑定。

定义事件：

```csharp
event 委托名 事件名;
event 委托名 事件名 = new 委托名(符合委托签名的函数名);		//事件也可以在定义时就初始化
event 委托名 事件名 = 符合委托函数签名的函数名;				//可以省略使用构造函数
event 委托名 事件名 = delegate(符合委托签名的参数表)		//匿名委托
{
	函数内容;
};
```

给事件添加/删除处理函数：

```csharp
事件名 += 符合委托签名的函数名;
事件名 -= 已绑定到事件的函数名;
事件名 += delegate(符合委托签名的参数表)
{
	函数内容;
};
```

触发事件：

```csharp
事件名(符合委托签名的参数表);
```

由于事件是一种特殊的**委托实例**，因此与委托不同，不能在全局区域和命名空间中定义事件，只能将事件作为某个类的成员来进行定义，事件与普通的成员类似，受到类的访问权限控制。

调用事件与调用委托实例方法是完全相同的。
事件机制是其他C#高级技术的基础。

实例代码：

```csharp
using System;

namespace ConsoleApplication1
{
	delegate void getMessage(string mes);					//委托可以定义在全局区域或是命名空间

	class Program
	{
		static void Main(string[] args)
		{
			Event events = new Event();
			events.myEvent += Program.eventHandler;
			events.myEvent += delegate(string str)			//事件绑定到委托匿名方法
			{
				Console.WriteLine("This is the {0}!", str);
			};
			events.showEvent("Test Text");					//触发事件
		}

		static void eventHandler(string str)
		{
			Console.WriteLine("This is the eventHandler!");
		}
	}

	class Event
	{
		public event getMessage myEvent;		//定义事件
		public void showEvent(string str)		//触发事件的函数
		{
			myEvent(str);		//调用事件实例，触发事件
		}
	}
}
```
输出结果：

```
This is the eventHandler!
This is the Test Text!
```



## *Lambda* 表达式
在`C#3.0`之后，引入了`Lambda表达式`的概念，开始支持**函数式编程**。基本语法为：

```csharp
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

```csharp
delegate int GetDouble(double num1, double num2);
GetDouble getDouble1 = delegate(double num1, double num2) { return (int)(num1 + num2); };
GetDouble getDouble2 = (num1, num2) => (int)(num1 + num2);
GetDouble getDouble3 = (double num1, double num2) => { return (int)(num1 + num2); };		//三种形式效果完全相同
```

需要注意的是，使用`Lambda`代替匿名委托虽然能够减少代码量，但这并不代表`Lambda`能够完全取代匿名委托，C#的`Lambda`中参数不能带有关键字`ref``out`，如果需要使用**引用参数**则还需要使用匿名委托。

### 使用函数对象表示 *Lambda*
C#中定义了一系列类型用来表示委托和Lambda对象。

- 使用`Action`表示不带参数且返回值为`void`类型的`Lambda`，注意，不需要也**不能**画蛇添足地写成`Action<>`形式。
- 使用`Action<T1, T2...>`表示带参数的`void`型返回值的`Lambda`。
- 使用`Func<T1, T2..., R>`表示返回值类型不为空的`Lambda`(**最后一个**泛型参数为函数返回值的类型)。
- `Action<>`、`Func<>`等泛型类型至多接收8个参数。
- C#中的`Lambda`**不能**直接加括号执行，而是需要创建一个函数对象或显式指明类型才能执行(即不能直接`(() => {})();`来执行`Lambda`)。
- 与Java的残废`Lambda`不同，C#的`Lambda`可以捕获并**修改**外部变量，而Java中的外部变量在`Lambda`中带有`final`属性，只能读取不能更改。

### *Lambda* 作用域
在C#中，`Lambda`能够访问到在`Lambda`被定义的作用域中的所有成员。
如果`Lambda`表达式在类中被定义，则`Lambda`表达式能够访问到类的成员。
如同函数一样，`Lambda`有自己的作用域，`Lambda`内部定义的变量是**不能**在外部访问到的。

示例代码-1：

```csharp
using System;

class Test
{
	static int num = 100;
	static Action setNum200 = () => num = 200;

	static void setNum(int newNum) {
		new Action<int>(n => num = n)(newNum);		//不能直接执行Lambda，需要创建函数对象或显式类型转换才能执行
		//或者写成 ((Action<int>)(n => num = n))(newNum);
	}

	static void Main(string[] args)
	{
		Console.WriteLine(num);
		setNum200();
		Console.WriteLine(num);
		setNum(500);
		Console.WriteLine(num);
	}
}
```

输出结果：(Mono 4.0.2 && ArchLinux x86\_64)

```
100
200
500
```

### 使用 *Lambda* 定义成员函数
在`C#6.0`中，开始支持使用`Lambda`直接定义成员函数。
**示例代码-1**使用新的语法可以使用如下格式书写。

示例代码-2：

```csharp
using System;

class Test
{
	static int num = 100;
	static Action setNum200 = () => num = 200;

	static void setNum(int newNum)
		=> new Action<int>(n => num = n)(newNum);		//直接使用Lambda实现成员函数

	static void Main(string[] args)
	{
		Console.WriteLine(num);
		setNum200();
		Console.WriteLine(num);
		setNum(500);
		Console.WriteLine(num);
	}
}
```



## 并发编程
在C#中，主要的并发技术有**异步委托**以及常见的**Thread**类。

### 异步委托
默认情况下，执行一个委托实例操作是**同步**的，但委托实例同样可以使用成员函数`BeginInvoke()`进行异步回调。

- `BeginInvoke()`除了接收原有委托签名的参数之外，参数表尾部额外带有两个参数，分别为`AsyncCallback`委托类型和`object`类型。
- `AsyncCallback`委托在回调委托运行结束之后触发，`AsyncCallback`委托接收一个`IAsyncResult`类型的参数。
- `object`类型用于传递一些参数给`AsyncCallback`委托。
- `BeginInvoke()`的最后两个参数可以为`null`。
- `BeginInvoke()`返回`IAsyncResult`类型，使用`IAsyncResult.IsCompleted`属性可以判断回调委托的执行状态，使用`IAsyncResult.AsyncState`属性获取`BeginInvoke()`参数表中的最后一个`object`类型的传入参数。

#### *使用`EndInvoke()`等待异步委托返回*
如果需要等待异步执行的委托结束，可以使用`EndInvoke()`成员函数。

- `EndInvoke()`接受一个`IAsyncResult`类型的参数(即`BeginInvoke()`的返回值)。
- `EndInvoke()`的返回值即为异步委托的返回值。
- 在异步委托执行完毕之前，`EndInvoke()`会一直阻塞当前线程，直到异步委托结束。

如下代码所示：

```csharp
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

#### *使用`WaitOne()`等待异步委托返回*
`BeginInvoke()`的返回值`IAsyncResult`类型的`AsyncWaitHandle`属性会返回一个`WaitHandle`类型的等待句柄。
该句柄的成员方法`WaitHandle.WaitOne()`接受`int`型参数作为超时时间，使用此方法可以实现等待指定时间(单位为**毫秒**)的效果。
`WaitHandle.WaitOne()`的返回值为`bool`类型，用于表示异步委托是否结束。

如下代码所示：

```csharp
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

可以看到，超时时间设为1000毫秒，此时异步委托尚未执行完毕，因而`IAsyncResult.IsCompleted`属性为`false`。

### *Thread* 类
与常规的**OOP**语言类似，C#中也可以使用`Thread`类来进行并发编程。

#### *创建与启动线程*
`Thread`类拥有四种构造函数，可以分别以`ThreadStart`或`ParameterizedThreadStart`委托实例做为参数构建一个线程对象。
两种委托的区别是前者不能带有参数，后者带有一个`Object`类型的参数，两种委托返回值都为`void`。
`Thread`类在构造时还可以接收一个`int`型参数用于指定线程的最大堆栈大小。
使用`Thread.Start()`方法可以启动线程，如下代码所示：

```csharp
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
This is thread!
The arg is: test args.

#### *等待线程结束*
使用成员方法`Thread.Join()`能够等待指定线程结束，在等待的线程结束前，该方法会一直阻塞**当前**线程。



## *WinFrom* 开发注记
`C#`对应的**GUI**库为基于`.NET Framework`的`Windows Form`。

### 常见控件类型
在`Windows Form`中，控件相关的类大多派生于`System.Windows.Forms.Control`。
控件的名称也与其它的GUI库类似：

- `Form` 窗体，类似于Qt中的**QFrame**
- `Label` 标签文本
- `Button` 按钮
- `RadioButton` 单选框
- `CheckBox` 复选框
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

```csharp
public delegate void EventHandler(object sender, EventArgs e);
```

`sender`参数指明了事件的发出者，而`e`参数携带了事件的具体信息，`EventArgs`是所有`.NET Framework`类库中事件的基类，实际的事件类型只有符合`EventHandler`委托签名的函数才能被绑定到`Windows Form`的控件事件上。

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

```csharp
protected override void WndProc(ref Message m);
```

重写其即可处理**Windows消息**。
`Message`类完整路径为`System.Windows.Forms.Message`，该类包装了Windows消息，包含以下属性：

- `HWnd` 获取或设置消息的窗口句柄
- `LParam` 指定消息的**LParam**字段
- `Msg` 获取或设置消息的**ID**号
- `Result` 指定为响应消息处理而向**Windows**返回的值
- `WParam` 获取或设置消息的**WParam**字段



## 调用C/C++动态链接库
C#支持调用使用`C/C++`语言编写的`dll`。
加载动态链接库需要指定dll的路径以及符号名称：

```csharp
[DLLImport("DLL Library"), EntryPoint = "Symbol Name"]
public/protected/private extern Type Func (Type args...)
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

`internal`关键字用在类、接口前表示只能在当前项目中访问该类、接口。
拥有`internel`关键字的类不能被`public`类继承。
默认不添加关键字的情况下，类和接口的访问属性即为`internal`。

`internal`关键字用在类内成员之前表示只能在当前项目中访问该成员。
在对类内成员使用时，`internal`关键字可以搭配`protected`关键字使用，即定义一个只能被当前项目的子类访问的成员。

### *readonly* 关键字
`readonly`关键字修饰的变量赋值只能在变量定义时或是在该变量所属类的构造函数中。

与`const`关键字相比，`const`关键字定义的变量必须在定义时就初始化。
`const`定义的变量被视为编译时常量，而`readonly`定义的变量被视为运行时常量。
在C#中`const`只能修饰值类型以及`string`类型和值为`null`的引用类型，被`const`修饰的变量自动带有`static`属性，`const`关键字与`static`关键字不能共同修饰同一个变量。
`const`变量由于是**静态**的，因而可以被定义在静态类中。
`readonly`没有这些限制，可以修饰任意类型，被`readonly`修饰的变量也默认**不带**`static`属性。

### *partial* 关键字
`partial`关键字用于定义`部分类`(局部类型)，局部类型允许我们将一个类、结构或接口分成几个部分，分别实现在几个不同的源码文件中。

在`Windows From`中，窗口类代码便使用了部分类特性，对于同一个窗口类，由VS窗体编辑器生成的GUI代码在文件**GUI类名.Designer.cs**文件中，而由用户编写的界面控制代码放在**GUI类名.cs**文件中，两个文件中的代码本质上属于同一个类，`部分类`特性巧妙地隔离开了**由IDE产生的代码**与**用户自行编写的代码**，使代码结构更清晰。
