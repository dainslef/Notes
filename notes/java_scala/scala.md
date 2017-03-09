[TOC]

## *Scala* 开发环境
在**Linux/Unix**环境下，无需额外的Scala配置，只需从对应发行版的包管理器中直接安装Scala开发包即可。

在**Windows**环境下，从**Scala官网**下载`Scala SDK`，解压到指定位置，新建环境变量`SCALA_HOME`，环境变量的值即为Scala的解压位置，然后将`%SCALA_HOME%\bin`加入**PATH**环境变量中。

### 使用 *Vim*
vim默认不支持Scala的语法高亮，可以使用**Derek Wyatt**开发的`vim-scala`插件，代码托管在**GitHub**上，项目主页是：

`https://github.com/derekwyatt/vim-scala`

可以使用**Vundle**来安装此插件，在配置文件`.vimrc`中添加：

```vim
Plugin 'derekwyatt/vim-scala'
```

### 使用 *Eclipse*
安装`Scala IDE`插件即可。

### *Scala* 编译工具
与编译Java代码类似，编译Scala代码使用`scalac`命令：

`$ scalac [*.scala]`

编译后即可得到字节码文件*.class。

执行字节码可以使用`scala`指令：

`$ scala [主类名]`

对于使用了`包(package)`的源码，在用`scalac`指令进行编译时，编译器会自动根据包路径创建对应的目录，然后在对应的包路径下生成对应的class文件。

运行带有包路径的字节码需要在包路径的相对根目录下，执行：

`$ scala [包路径].[主类名]`

需要注意的是，虽然Scala是基于`JVM`的语言，但`scalac`编译得到的字节码直接由java命令执行会出现一些错误。
此外，虽然Scala并不强制要求类名要与文件名相同，但在部分IDE中，如果类名与文件名不同，构建项目会出现错误。

### 反编译
使用`scalap`可以反编译字节码得到Scala代码：

`$ scalap [*.class]`

或者

`$ scalap [类名]`

如果需要查看字节码的对应生成的Java代码，可以使用`javap`工具：

`$ javap [类名]`

使用`javap`可以直接查看生成的字节码：

`$ javap -c [类名]`

默认情况下，通过反编译得到的Scala以及Java代码只能看到公有方法的声明，方法实现以及私有、保护成员均**不可见**。
查看所有成员需要添加`-private`参数：

```
$ javap -private [类名]
$ scalap -private [类名]
```

### 使用Scala解释器
在命令行中输入无参数的`scala`指令即可进入交互式的Scala解释器。
常用的Scala解释器**指令**：

```scala
scala> :quit				//退出解释器
scala> :reset				//重置解释器的状态，会清空已保存的变量、类、方法等所有内容
```

Scala解释器与Python解释器类似，可以直接将代码一行行地输入解释器，解释器会执行代码并给出反馈，对初学者而言是一个练习的好方法。



## 基本语言特性
相比`Java`、`C++`等语言，`Scala`融合了`OOP`、`FP`等编程范式，同时语法上更**灵活**。

### 语法基础(概览)
- Scala语言中不强制要求分号，可以依行断句，只有一行带有多个语句时才要求分号隔开。
- 使用`var/val`定义`变量/常量`，类型可以由编译器推导，也可以显式指定。定义变量时甚至可以省略`var`、`val`关键字，无关键字时定义的变量默认即为`val`，在定义变量的同时就需要初始化变量，否则报错(抽象类中除外)。
- 使用`def`关键字定义**方法**，`var/val`定义**函数**。需要注意的是使用`var`定义的函数是可以更改实现的，但`def`定义的方法一经定义实现就**不可改变**。
- 所有类型皆为对象，基础类型如`Int`、`Double`等都是类，函数/方法返回值的空类型为`Unit`，相当于Java/C++中的`void`。
- 可以使用操作符作为函数名，达到类似C++/C#中操作符重载的效果。
- 类的成员变量可以与方法名称**相同**。

### 与传统语言的差异
- 没有**自增/自减**操作符。
- 没有原生enum类型，应继承枚举助手类`Enumeration`。
- 没有`break`、`continue`关键字，但有相关的`Breaks`包提供类似功能。
- 没有**三目运算符**，但`if`表达式带有**返回值**，可以实现类似效果。
- 类成员权限默认共有，没有`public`关键字(有`private`和`protected`关键字)。

### Hello World
创建文件`Test.scala`，输入以下代码：

```scala
object Test {
	def main(args: Array[String]): Unit		//带有等号的方法可以省略返回值类型由编译器进行推导
		= println("Hello World!")
}
```

与Java类似，Scala也是从主方法`main`中开始执行整个程序，不过`main`方法并不定义在类中，而是定义在**单例对象**中(使用`object`关键字创建单例对象)。
将主方法写在`class`中能够通过编译，但生成的字节码文件在执行时会出错。

可以不手动定义`main`方法而让单例对象继承`App`特质，即可直接执行代码语句，例如：

```scala
object Test extends App {
	println("Hello World!")
}
```

### *Method* (方法)
与Java不同，Scala中同时支持**函数**与**方法**(Java只有方法而没有真正意义上的**函数**，只有与函数类似的**静态方法**)。

方法由`def`关键字定义，可以被def方法、val函数重写。一个典型的方法格式如下：

```scala
def methodName(args: Type)：Type = {
	/* function_body */
}
```

Scala中方法体**不需要**显式使用`return`关键字来给出方法返回值，编译器会将函数体的最后一句代码推导出类型做为整个函数的返回值。
对于有返回值的方法，必须要在方法定义中加入**等号**，否则编译器**不会**推导返回值。
即使方法的返回值为`Unit`，只要显式指定了返回值类型，则必须在方法体中加入等号。
方法和函数的形参**不需要**也**不能**使用`val``var`关键字声明，只需写明类型即可。

在Scala中，方法允许省略参数，空的参数表可以直接**省略**，如：

```scala
def getNum: Int = 100
def getNum(): Int = 100					//以上两个定义作用相同，但只能存在一个
```

无参方法与空参方法只能存在一个，但二者在使用方式上略有不同：

- 无参方法在调用时只能直接使用方法名，在方法名后加上括号调用就会出错。
- 空参方法既可以使用带有括号的方法调用方式，也可以省略括号。

如下所示：

```scala
scala> def getNum: Int = 100			//定义了方法 getNum: Int
getNum: Int
scala> getNum							//正确，返回 100
res0: Int = 100
scala> getNum()							//错误，提示 error: Int does not take parameters
<console>:12: error: Int does not take parameters
	getNum()
		  ^
scala> def getNum(): Int = 200			//定义了方法 getNum(): Int
getNum: ()Int
scala> getNum							//正确，返回 200
res1: Int = 200
scala> getNum()							//正确，返回 200
res2: Int = 200
```

同时，无参方法不能与已有字段名称相同(编译报错)，而空参方法允许带有同名的字段。
需要注意的是，在Scala中，赋值表达式的值为`Unit`，而不是类似Java/C++中的以被赋值的变量类型为表达式的值。例如：

```scala
scala> var _num = 0
_num: Int = 0
scala> def testNum(num: Int): Int = _num = num		//由编译器推断出的返回值类型为Unit
<console>:12: error: type mismatch;
found   : Unit
required: Int
	def testNum(num: Int): Int = _num = num
									  ^
```

参数默认值
> 在Scala中，方法中的参数允许带有**默认值**：
>
>	```scala
>	scala> var num = 100
>	num: Int = 100
>	scala> def setNum(p: Int = 0) { num = p }		//方法的参数不能由默认值进行类型推导，即使给参数写明了默认值，也依然需要显式指明类型
>	setNum: (p: Int)Unit
>	scala> setNum()				//对于有参数的方法，即使参数带有默认值使得参数表可以为空但在调用时依然不能省略括号，否则报错
>	scala> println(num)
>	0							//输出0
>	```
>
> 如果一个方法中包含多个同类型并带有默认值的参数，调用时默认匹配第一个参数：
>
>	```scala
>	scala> def func(num1: Int = 100, num2: Int = 200) = println(s"$num1 $num2")
>	func: (num1: Int, num2: Int)Unit
>	scala> func(300)
>	300 200
>	```
>
> 在常见的支持方法参数默认值的编程语言中，参数默认值会有一些限制：
>
>	- `C#`中的参数默认值只能是编译时常量。
>	- `C++`中的参数默认值可以是成员变量、全局变量，但不能是函数结果。
>	- `C++`中使用非静态成员变量做为参数默认值时，类实例必须设定默认值在之前创建，不能在设定默认值的表达式中创建实例获取成员变量。
>
> 在`Scala`中方法的参数默认值可以是变量，类内字段，甚至是另一个方法的返回结果。
>
> 如下代码所示：
>
>	```scala
>	class Test {
>		var num = 23333
>	}
>
>	object Main extends App {
>
>		def get(num: Int = (new Test).num) = num	//Scala支持使用new操作符创建实例获取成员字段做为默认值
>		def show(num: Int = get()) = println(num)
>
>		show()
>	}
>	```
>
> 输出结果：
>
>	```
>	23333
>	```

默认参数与方法重载
> 在Scala中，若一个带有默认的参数的方法省略默认参数时签名与一个已经存在的方法相同，编译器并不会报错(C++编译器则会报错)，而是在调用方法时优先使用**无默认值**的版本(处理逻辑类似于C#)：
>
>	```scala
>	object Main extends App {
>		def func() = println("No Args")
>		def func(num: Int = 100) = println(num)
>		func()
>	}
>	```
>
> 输出结果：
>
>	```
>	No Args
>	```

具名参数
> 在Scala中，调用方法时可以在参数表中写明参数的名称，该特性被称为"具名参数"。
> 对于方法中包含多个同类型并带有默认值参数的情况下，使用该特性可以显式指定要传入的是哪一个参数：
>
>	```scala
>	scala> func(num2 = 300)
>	100 300
>	```
>
> 与C++不同，Scala中，方法参数的默认值**不需要**连续，参数的默认值可以交错出现，甚至是颠倒参数顺序：
>
>	```scala
>	scala> def func(int: Int, str: String = "String", char: Char, double: Double = 123.0) = println(s"$int $str $char $double")
>	func: (int: Int, str: String, char: Char, double: Double)Unit
>	scala> func(100, 'c')
>	<console>:12: error: not enough arguments for method func: (int: Int, str: String, char: Char, double: Double)Unit.
>	Unspecified value parameter char.
>			func(100, 'c')
>				^
>	scala> func(int = 100, char = 'c')			//对于默认参数不连续的方法，需要使用"具名参数"
>	100 String c 123.0
>	```

*By-name Parameter* (传名参数)
> 当一个方法接收的**参数**为**空**时，该参数即为**传名参数(By-name Parameter)**，如下所示：
>
>	```scala
>	def func(arg: => T) ...
>	```
>
> 可以使用传名参数可以接收任意数量的代码，如下所示：
>
>	```scala
>	object Main extends App {
>
>		def show(args: => Unit) = args
>
>		//单行语句可直接作为参数
>		show(println("123"))
>
>		//多行语句可放在大括号中
>		show {
>			println("456")
>			println("789")
>		}
>	}
>	```
>
> 运行结果：
>
>	```
>	123
>	456
>	789
>	```

### *Function* (函数)
在Scala中函数使用`var/val`关键字定义，即函数是一个存储了函数对象的字段。

一个典型的函数定义如下：

```scala
var functionName: FuncType = 符合签名的方法/函数/Lambda
```

Scala中的函数类型为`Function`，根据参数数目的不同，Scala中提供了`Function0[+R]`(无参数)到`Function22[-T1, ..., -T22, +R]`共23种函数类型，即Scala中的函数，最多可以拥有**22**个参数。

函数本质上是一个`Function`类型的实例，方法中的一些特性不能用在函数中：

- 函数**不存在**重载，作用域内的一个函数实例只能有一个实现。
- 函数**不允许**带有默认值。
- 函数**不允许**定义隐式参数。
- 函数**不允许**柯里化(不能定义多参数表)。
- 函数参数类型为**传名参数**时，需要写明函数的完整定义，不能采用推导返回值的语法。
- 空参函数的括号不可省略，直接使用函数名不代表调用空参函数，而是访问函数实例。

如下所示：

```scala
scala> var show100: () => Int = () => 100
show100: () => Int = <function0>
scala> show100				//直接使用函数名得到的是函数对象而非调用函数
res0: () => Int = <function0>
scala> show100()
res1: Int = 100
```

在Scala中，可以直接使用Lambda创建匿名函数后立即使用：

```scala
scala> ((str: String) => println(str))("Hello World!")
Hello World!
```

与`C++`中的`Lambda`用法类似：

```cpp
#include <iostream>

using namespace std;

int main(void)
{
	[](const string& str) { cout << str << endl; } ("Hello World!");
	return 0;
}
```

然而在`C#`中，`Lambda`需要创建对象或显式指明类型才能使用，同样的语句需要写成：

```cs
using System;

class Test
{
	static void Main(string[] args)
		=> new Action<string>(str => Console.WriteLine(str))("Hello World!");
		//或者写成 ((Action<string>)(str => Console.WriteLine(str)))("Hello World!");
}
```

函数组合
> 在Scala中，函数允许进行组合。
> 函数组合有两种方式，`a compose b`实际调用次序为`a(b())`，`a andThen b`实际调用次序为`b(a())`。
> 需要注意的是，方法不能直接进行组合，需要将其转化为函数(方法名之后加`_`符号)。
>
>	```scala
>	object Main extends App {
>		def add(num: Int) = num + 100
>		def double(num: Int) = num * 2
>
>		//只有函数能进行组合,方法需要加"_"符号转化成函数
>		val compose = add _ compose double
>		val andThen = add _ andThen double
>
>		println(compose(100) == add(double(100)))
>		println(andThen(100) == double(add(100)))
>	}
>	```
>
> 输出结果：
>
>	```
>	true
>	true
>	```

*Partial Function* (偏函数)
> 偏函数是一个定义域有限的函数，在Scala中使用类型`PartialFunction[-A, +B]`来表示偏函数。
> 偏函数类似数学意义上的函数，只能接收**一个**参数，同时偏函数只对**有限**的输入值返回结果。
>
> 在Scala中，使用**模式匹配**语法中的`case`关键字来实现偏函数，一个最简单的偏函数如下所示：
>
>	```scala
>	scala> val func: PartialFunction[Int, Int] = { case 0 => 0 }
>	func: PartialFunction[Int,Int] = <function1>
>	```
>
> 这个偏函数只在输入值为`0`时有意义：
>
>	```scala
>	scala> func(0)
>	res1: Int = 0
>
>	scala> func(1)
>	scala.MatchError: 1 (of class java.lang.Integer)
>		at scala.PartialFunction$$anon$1.apply(PartialFunction.scala:253)
>		at scala.PartialFunction$$anon$1.apply(PartialFunction.scala:251)
>		at $anonfun$1.applyOrElse(<console>:11)
>		at $anonfun$1.applyOrElse(<console>:11)
>		at scala.runtime.AbstractPartialFunction$mcII$sp.apply$mcII$sp(AbstractPartialFunction.scala:36)
>		... 32 elided
>
>	scala> func(-1)
>	scala.MatchError: -1 (of class java.lang.Integer)
>		at scala.PartialFunction$$anon$1.apply(PartialFunction.scala:253)
>		at scala.PartialFunction$$anon$1.apply(PartialFunction.scala:251)
>		at $anonfun$1.applyOrElse(<console>:11)
>		at $anonfun$1.applyOrElse(<console>:11)
>		at scala.runtime.AbstractPartialFunction$mcII$sp.apply$mcII$sp(AbstractPartialFunction.scala:36)
>		... 32 elided
>	```
>
> 一个偏函数可以通过添加多个`case`语句块来添加多个定义域的返回结果：
>
>	```scala
>	scala> val func1: PartialFunction[Int, Int] = { case n if n > 0 => 1; case n if n < 0 => -1 }
>	func1: PartialFunction[Int,Int] = <function1>
>
>	scala> func1(-11111)
>	res3: Int = -1
>
>	scala> func1(11111)
>	res4: Int = 1
>
>	scala> func1(0)
>	scala.MatchError: 0 (of class java.lang.Integer)
>		at scala.PartialFunction$$anon$1.apply(PartialFunction.scala:253)
>		at scala.PartialFunction$$anon$1.apply(PartialFunction.scala:251)
>		at $anonfun$1.applyOrElse(<console>:11)
>		at $anonfun$1.applyOrElse(<console>:11)
>		at scala.runtime.AbstractPartialFunction$mcII$sp.apply$mcII$sp(AbstractPartialFunction.scala:36)
>		... 32 elided
>	```
>
> 偏函数`func1()`对于定义域`(-∞，0)`返回`-1`，对于定义域`(0, +∞)`返回`1`。
>
> 偏函数可以使用`isDefinedAt()`方法来检验在给定的参数在偏函数中是否有定义：
>
>	```scala
>	scala> func1.isDefinedAt(10000)
>	res7: Boolean = true
>
>	scala> func1.isDefinedAt(-10000)
>	res8: Boolean = true
>
>	scala> func1.isDefinedAt(0)
>	res9: Boolean = false
>	```
>
> 使用`orElse()()`方法在一个偏函数没有定义的时候尝试调用另一个偏函数：
>
>	```scala
>	scala> func1.orElse(func)(0)
>	res10: Int = 0
>	```
>
> 函数`func1()`对于`0`没有定义，而函数`func()`对于`0`有定义，则在参数取`0`时调用`func()`函数的返回值。

*Partial Applied Function* (部分应用函数)
> 部分应用函数是逻辑上的概念，表示一个已经指定了部分参数的函数。
> 将一个拥有多个参数的函数指定部分参数的值构成一个参数较少的新函数，新的函数即为**部分应用函数**。
>
> Python中的偏函数与Scala中的偏函数是完全不同的概念，Python中偏函数的概念类似于Scala中的部分应用函数。
>
> 定义一个拥有2个参数的`sum()`函数，返回两个参数的和：
>
>	```scala
>	scala> def sum(num1: Int, num2: Int) = num1 + num2
>	sum: (num1: Int, num2: Int)Int
>	```
>
> 指定第二个参数始终为`100`，创建一个部分应用函数：
>
>	```scala
>	scala> def sum100 = sum(_: Int, 100)
>	sum100: Int => Int
>
>	scala> sum100(100)
>	res11: Int = 200
>	```
>
> `sum100()`便是`sum()`指定了第二参数的部分应用函数。

### *continue* 与 *break*
`Scala`**没有**提供主流语言中的`continue`和`break`关键字用于流程控制。

其它语言中的`continue`功能可以通过`for`语句条件后添加`if`判断条件实现或使用**守卫**。

`break`功能可以由`scala.util.control.Breaks`类提供。

> `Breaks`类中定义了`breakable()`和`break()`成员方法如下所示：
>
>	```scala
>	def breakable(op: => Unit): Unit {
>		try { op } catch {
>			// 判断异常是否为breakException，是则捕获，其它异常则继续向外传递
>			case ex: BreakControl => if (ex ne breakException) throw ex
>		}
>	}
>	def break(): Nothing = { throw breakException }
>	```
>
> 由代码可知，`breakable()`方法接收传名参数`op`，捕获`breakException`异常。
> `break()`方法产生`breakException`异常。
>
> 将需要使用break的循环代码块作为传名参数`op`传入`breakable()`方法中，`op`代码块中调用`break()`产生`breakException`异常被捕获，中断函数，达到跳出循环的目的。
>
> 使用`Breaks`如下代码所示：
>
>	```scala
>	import scala.util.control.Breaks.{ breakable, break }
>
>	object Main extends App {
>
>		breakable {
>			//使用break的代码块作为传名参数传入breakable中
>			for (i <- 1 to 10) {
>				if (i == 8) break		//跳出循环
>			}
>		}
>
>	}
>	```



## 类型系统
在Scala中，所有的类型**皆为对象**，所有类型都从根类`Any`继承，`Any`有`AnyVal`和`AnyRef`两个子类。

### 基础类型
在Scala中，基础类型如`Int`、`Float`、`Double`、`Unit`等全部从`AnyVal`类中派生，因而可以直接在泛型中直接使用这些类作为类型参数。
同时，Scala中提供了`隐式转换(ImplicitConversion)`来保证`Int`、`Float`、`Double`等类型之间可以**自动进行转换**。

在Scala中，所有的基础类型之外的引用类型派生自类`AnyRef`。

基础类型转换
> 基础类型与字符串(String)等类型之间的转换也由类提供的成员函数进行，如将数值与字符串相互转换可以使用如下代码：
>
>	```scala
>	var str = 100.toString
>	var num = str.toInt
>	```

### *Bottom* (底类型)
与Java不同，Scala中存在底类型(bottom)。底类型包括`Nothing`和`Null`。

- `Nothing`是所有类型`Any`的子类型，定义为`final trait Nothing extends Any`。
- `Nothing`特质没有实例。
- `Null`是所有引用类型`AnyRef`的子类型，定义为`final trait Null extends AnyRef`。
- `Null`特质拥有唯一实例`null`(类似于Java中`null`的作用)。

### 可空类型
在Scala中，使用`Option[T]`表示可空类型，`Option[T]`包含两个子类，`Some[T]`和`None`，分别代表值存在/值不存在。
对`Option[T]`类型使用`getOrElse()`方法来获取存在的值或是当值不存在时使用指定的值，如下所示：

```scala
scala> var str1: Option[String] = "test"
<console>:10: error: type mismatch;			//赋值失败，Option[T]只能接收Option及其子类
found   : String("test")
required: Option[String]
	var str1: Option[String] = "test"
							   ^
scala> var str1: Option[String] = Option("test")
str1: Option[String] = Some(test)
scala> var str2: Option[String] = None
str2: Option[String] = None
scala> println(str1 getOrElse "Get Value Failed!")
test
scala> println(str2 getOrElse "Get Value Failed!")
Get Value Failed!							//输出getOrElse()方法中设定的值
```

可空类型也可以用于**模式匹配**中，如下代码所示：

```scala
object TestOption extends App {
	var s  = List(Some(123), None)
	for (num <- s)
		num match {
			case Some(x) => println(x)
			case None => println("No Value")
		}
}
```

运行结果：

```
123
No Value
```



## *OOP*
Scala是一门同时具有函数式与面向对象特性的**多重范式语言**，除了具有函数式特性外，对**OOP**也有着完整的支持。

与`Java`不同，`Scala`中公有类的名称不强制要求与源码文件相同，同时一个文件中可以包含多个公有类的定义。

### 访问权限
Scala中的成员和类、特质的默认访问权限即为**公有**，因而Scala中没有`public`关键字。

Scala中的保护成员使用关键字`protected`，私有成员使用关键字`private`，作用大体上与Java相同，但Scala在访问权限上支持**更细粒度**的划分。

- Scala的类定义、特质定义、单例对象定义前可以使用访问权限修饰，`private`和`protected`权限的类等仅限同一个包内访问。
- Scala中的顶层类允许使用`protected`权限修饰(与Java不同，Java仅允许内部类使用`protected`修饰)。
- Scala中的访问权限关键字用于类时，还可以写在类名与主构造器之间(特质、单例对象没有这种用法)，用于指定主构造器的访问权限。
- 访问级别关键字之后可以使用`[]`操作符设定更具体的访问区域限制，可以是当前定义的类、当前定义类的外部类(若存在外部类)、包名(某个包内的所有类实例可访问)或是`this`关键字(仅当前实例可访问)。
- 访问权限关键字之后若不写明具体的访问限制区域，则默认限制为当前类可访问(与Java行为基本一致，但Java中的保护成员包内可见)。

如下代码所示：

```scala
package TestCode ｛

	private class A			//类定义前可以使用访问权限修饰
	protected class B		//类定义的访问权限可以为protected

	case class Num private(num: Int = 200)		//权限修饰符可以用在类名与主构造器之间，代表构造器私有
	class Test protected ()						//即使主构造器参数为空，也不能直接以权限关键字结尾
	//或者写成 class Test protected {}

	class Access(a: Int = 1, var b: Double = 2.0) {
		def showOther1(access: Access) = access.show1			//出错，access非当前类实例，无访问权限
		def showOther2(access: Access) = access.show2			//正常访问
		def showOther3(access: Access) = access.show3			//正常访问
		private[this] def show1 = println(a + " " + b)			//限定当前实例可访问
		private[Access] def show2 = println(a + " " + b)		//类似Java中的private，当前类的任意实例皆可相互访问私有成员
		private[TestCode] def show3 = println(a + " " + b)		//作用域为包名，此时的访问权限类似Java中的default访问权限，当前包中类的实例皆可访问到该私有成员
	}

}
```

### 字段
Scala类中的字段不仅仅是定义了一个成员变量，编译器生成字节码时可能会自动为字段生成与字段同名的`getter`和`setter`方法。

- `var`关键字定义的字段编译器会同时为其生成`setter`和`getter`方法。
- `val`关键字定义的字段编译器会为其生成`getter`方法。

如下所示：

```scala
class Test {
	var num: Int = { ... }
	val str: String = { ... }
}
```

生成的Java代码：

```java
public class Test {
	private int num;
	private final java.lang.String str;
	public int num();
	public void num_$eq(int);			//var字段生成了setter/getter
	public java.lang.String str();		//val字段生成了getter
	public Test();
}
```

若对象的的权限为私有，则对应生成的`setter`和`getter`方法同样为**私有**权限。

生成`setter/getter`方法遵循以下规则：

- `val`关键字定义的字段为**只读**字断，编译器只生成`getter`方法，不生成`setter`方法。
- 若访问权限为`private[this]`，则编译器不会为其合成`setter`和`getter`方法(`protected[this]`和`private`访问权限正常生成`setter/getter`方法)。
- 若定义了字段没有对其进行初始化，则该字段即为**抽象字段**，带有抽象字段的类前需要加上`abstract`关键字，且不能被直接实例化。
- 重写抽象字段不需要使用`override`关键字。

如下所示：

```scala
class Override {

	var m = 100									//普通成员字段会自动合成setter/getter方法
	/*
	def m(): Int = m							//错误，提示重复定义
	def m_=(m: Int) { this.m = m }				//错误，提示重复定义
	*/
	def m(m: Int) {}							//正常，签名未冲突

	private[this] var num = 100					//私有this字段不会合成setter/getter方法，但自行手动定义同名的setter/getter方法时有许多限制(getter方法需要空参且写明返回值)，且没有实用价值(setter方法使用报错)
	def num(): Int = num						//正常
	def num_=(num: Int) { this.num = num }		//正常，虽然定义时不报错，但赋值时报错
	/*
	def num = this.num							//报错
	def num: Int = num							//报错
	def num: Int = this.num						//报错
	*/

	//常用的私有变量自定义setter/getter风格是私有字段名前加上下划线
	private[this] var _abc = 0
	def abc = _abc
	def abc_=(abc: Int): Unit = _abc = abc
	/*
		也可以写成：
		def abc_=(abc: Int) { _abc = abc }
	*/
}
```

在Scala中，字段名称可以与方法名称**相同**。

- 默认情况下，合成的`setter`、`getter`方法就与字段同名，手动在代码中创建与`setter`、`getter`签名相同的方法会导致编译错误。
- 访问权限为`private[this]`时编译器不合成默认的`getter`、`setter`方法时可以手动定义`setter`、`getter`方法。
- 在实际编码过程中，虽然给`private[this]`的字段定义同名的`setter`、`getter`方法不会报错，但调用过程中会提示错误(如上例子中给num字段赋值回得到错误`reassignment to val`，因此不要手动给字段定义同名的`setter`、`getter`方法)。

此外，由于字段名称可以与方法名称相同，因而即使编译器生成了`setter`、`getter`方法，编码者依然可以使用字段名称定义其它签名的重载函数。

### *Constructor* (构造器)
在Scala中构造方法的作用与Java类似，用于在创建类实例的同时对指定的成员进行初始化。
在语法上，Scala中类可以拥有一个**主构造器(primary constructor)**和任意个**辅助构造器(auxiliary constructor)**。

构造器的基本使用方法：

- 主构造器的参数定义紧跟在类名之后，辅助构造器定义在类体中，使用`this`关键字。
- 在辅助构造器的代码中必须立即调用主构造器或其它辅助构造器，之后才能执行其它代码。
- 调用父类的构造器必须在主构造器中，写在父类类名之后。

如下代码所示：

```scala
//定义主构造器
class Constructor(a: Int, var b: Double = 2.0) {		//构造器参数紧跟在类名之后，构造器中的参数可以带有默认值
	//在构造器中创建了字段b，a变量没有显式使用var/val关键字，同时也没有被其它方法引用，因而仅仅作为临时变量存在

	//定义辅助构造器，使用this关键字
	def this() = this(2, 3.0)		//辅助构造器的函数体中必须最终调用主构造器，辅助构造器即使没有参数也必须也必须带括号
}

//只有主构造器能够调用父类构造器，调用的父类构造器可以是主构造器，也可以是辅助构造器
class ExtendConstructor(a: Int = 2, c: Double = 4.0) extends Constructor(a, c) {
	def this() {
		//a = 100					//代码要在构造器调用之后，放在this()之前会报错
		this(2, 4.0)
		//super(2, 4.0)				//在Scala中没有这种用法，父类的构造函数只能由主构造器调用
	}
}
```

主构造器作用域
> 在`Scala`中，主构造器的实际作用范围为整个类内作用域。
> 即在类作用域内，不仅可以像`Java`、`C#`、`C++`等传统`OOP`语言一样定义成员字段和成员方法，更可以直接在类内添加普通代码语句。
>
> 如下所示：
>
>	```scala
>	class Test(str: String) {
>		println(str)
>	}
>	```
>
> 类体中直接包含了普通的语句代码，而非成员定义。
>
> 在类内作用域中直接添加普通代码时，需要考虑变量初始化顺序，如下所示：
>
>	```scala
>	class Test0 {
>		println(str)
>		val str = "abc"
>	}
>
>	class Test1 {
>		val str = "abc"
>		println(str)
>	}
>
>	object Main extends App {
>		new Test0()
>		new Test1()
>	}
>	```
>
> 输出结果：
>
>	```
>	null
>	abc
>	```
>
> 类作用域中的普通语句可以直接引用类内定义的成员字段(即使成员字段定义在语句之后)，但若成员字段的定义语句在执行语句之后，则成员字段在被引用时**未初始化**。

主构造器访问权限
> 在**类名**之后，**主构造器参数**之前可以添加访问权限修饰符，用于限定主构造器的访问权限。
>
> 如下所示：
>
>	```scala
>	class Test private(num: Int) {
>		def show() = println(num)
>	}
>
>	object Test {
>		lazy val instance = Test()
>		private def apply() = new Test(100)		//正确，伴生对象中可以访问类的私有成员，包括私有主构造器
>	}
>
>	object Main extends App {
>		Test.instance.show()					//正确，获取单例
>		new Test(100).show()					//错误，无法直接访问私有构造器
>	}
>	```

主构造器参数做为成员字段
> 主构造器的参数中若添加了`var/val`关键字，则该参数将作为类的成员字段存在。
> 构造器参数前使用`var`关键字，如下代码所示：
>
>	```scala
>	class Constructor(var num: Int)
>	```
>
>	编译为Java代码为：
>
>	```java
>	public class Constructor {
>		private int num;
>		public int num();
>		public void num_$eq(int);
>		public Constructor(int);
>	}
>	```
>
> 可以看到，编译器为`var`字段`num`生成了`setter`、`getter`方法和一个与字段同名的私有变量。
>
> 构造器参数前使用`val`关键字，如下所示：
>
>	```scala
>	class Constructor(val num: Int)
>	```
>
> 编译为Java代码为：
>
>	```java
>	public class Constructor {
>		private final int num;
>		public int num();
>		public Constructor(int);
>	}
>	```
>
> 可以看到，编译器为val字段`num`生成了`getter`方法和一个与字段同名的`final`私有变量。
>
> 构造器参数前加上**访问权限修饰符**则生成的方法类似，但方法前会添加对应的访问权限(Scala中的`protected`限定符编译为Java后变为`public`)，如下所示：
>
>	```scala
>	class Constructor0(protected[this] var num: Int)
>	class Constructor1(private val num: Int)
>	```
>
> 编译为Java代码为：
>
>	```java
>	public class Constructor0 {
>		private int num;
>		public int num();
>		public void num_$eq(int);
>		public Constructor0(int);
>	}
>	public class Constructor1 {
>		private final int num;
>		private int num();
>		public Constructor1(int);
>	}
>	```
>
> 只有访问权限为`private[this]`时，编译器才不会为引用的字段生成`setter/getter`，而仅仅生成一个私有成员变量。

主构造器参数的默认字段生成规则
> 主构造器的参数中若没有使用`val/val`关键字，则默认修饰为`private[this] val`。
> 编译器默认不会为该参数生成`setter/getter`方法以及私有成员变量，除非被其它成员方法引用。
>
> 如下代码所示：
>
>	```scala
>	class Constructor0(num: Int)
>	class Constructor1(private[this] val num: Int)
>	```
>
> 编译为Java代码为：
>
>	```java
>	public class Constructor0 {
>		public Constructor0(double);
>	}
>	public class Constructor1 {
>		public Constructor1(double);
>	}
>	```
>
> 编译得到的Java代码完全相同。
>
> 当该参数被其它成员方法引用时，编译器会为其生成对应的`final`私有成员变量(但没有生成`setter/getter`)。
> 只要构造器参数没有使用`var`关键字标记，则生成的成员变量就带有`final`属性。
>
> 如下代码所示：
>
>	```scala
>	class Constructor0(num: Int) {
>		def get = num
>	}
>	class Constructor1(private[this] val num: Int) {
>		def get = num
>	}
>	```
>
> 编译为Java代码为：
>
>	```java
>	public class Constructor0 {
>		private final int num;
>		public int get();
>		public Constructor0(int);
>	}
>	public class Constructor1 {
>		private final int num;
>		public int get();
>		public Constructor1(int);
>	}
>	```
>
> 辅助构造器中的参数与普通函数参数类似，仅在构造器代码段内部生效(不作为字段存在)，辅助构造器的参数前不能添加`var/val`关键字。

默认构造方法
> 一个类如果没有显式写明主构造器参数，则默认生成一个**空参**构造方法。
>
> 对于一个如下的**空类**：
>
>	```scala
>	class Empty
>	```
>
> 实际相当于：
>
>	```scala
>	class Empty() {
>	}
>	```
>
> 编译成Java代码后为：
>
>	```java
>	public class Empty {
>		public Empty() { ... };
>	}
>	```
>
> 可以采用如下方式实例化：
>
>	```scala
>	new Empty()
>	new Empty			//空参方法括号可省略
>	```
>
> 与主流的OOP语言不同，一个使用默认生成的空参构造函数的作为主构造器的类即使定义了其它构造器，默认生成的主构造器**依然存在**。
> 如下代码所示：
>
>	```scala
>	class Default {
>		def this(num: Int) = this
>	}
>	```
>
> 编译成Java代码后为：
>
>	```java
>	public class Default {
>		public Default();
>		public Default(int);
>	}
>	```
>
> 可以看到，默认的空参构造方法依然存在。
>
> 主构造器不能在类体中重新定义，如下所示：
>
>	```scala
>	class Default {
>		//编译报错，主构造器已为空参，不能重复定义
>		def this() { ... }
>	}
>	```

### 多态
Scala作为OOP语言，支持多态。

重写
> 在Scala中，默认情况下，子类的并不会重写父类的同名方法，而是需要显式地在方法定义前加上`override`关键字才会发生重写行为。
>
> Scala中的重写遵循以下规则：
>
>	- def只能重写另一个def。
>	- val可以重写另一个val以及不带有参数的def。
>	- var只能重写另一个抽象的var(即只有定义没有实现)。

重载
> Scala支持函数重载，并且可以使用**操作符**作为函数名，使用操作符作为函数名可以达到类似**C++**中**操作符重载**的效果。

### 伴生对象
在Scala中没有`static`关键字，也没有**静态成员**的概念，Scala使用**单例对象**来达到近似静态成员的作用。

- 每一个类可以拥有一个同名的**伴生对象**(单例)，伴生对象使用`object`关键字定义，且一个类和其伴生对象的定义必须写在同一个文件中。
- 伴生对象与同名类之间可以相互访问私有、保护成员。

### *apply()/update()* 方法
在Scala中，允许使用函数风格进行一些对象操作。

假设有一个**实例**`instance`，使用：

```scala
instance(arg1, arg2, arg3, ...)
```

此表达式等价于：

```scala
instance.apply(arg1, arg2, arg3, ...)
```

同样的，使用：

```scala
instance(arg1, arg2, arg3, ...) = value
```

等价于：

```scala
instance.update(arg1, arg2, arg3, ..., value)
```

如下代码所示：

```scala
object Main extends App {
	var a = new Apply(0, 0)
	val show = () => println(a.num1 + " " + a.num2)
	a(1)								//相当于调用 a.apply(1)
	show()								//输出 1 2
	a(100, 200) = Apply(10, 20)			//相当于调用 a.update(100, 200, new Apply(10, 20))
	show()								//输出 90 180
	Apply(1000, 2000) = a
	show()								//输出 1000 2000
}

class Apply(var num1: Int, var num2: Int) {
	def apply(num: Int) {
		this.num1 = num
		this.num2 = num + 1
	}
	def update(num1: Int, num2: Int, test: Apply) {
		this.num1 = num1 - test.num1
		this.num2 = num2 - test.num2
	}
}

object Apply {
	def apply(num1: Int, num2: Int) = new Apply(num1, num2)
	def update(num1: Int, num2: Int, test: Apply) {
		test.num1 = num1
		test.num2 = num2
	}			//伴生对象同样可以拥有apply()/update()方法
}
```

输出结果：

```
1 2
90 180
1000 180
```

### *unapply()/unapplySeq()* 方法
在Scala中，还提供了被称为**提取器**的`unapply()`方法。

- `unapply()`方法则与`apply()`方法相反，可以从对象中提取出需要的数据(在实际使用过程中，可以从任意的目标里提取数据)。
- `unapply()`方法返回值必须为`Option`及其子类，单一返回值使用`Option[T]`，多个返回值可以包含在元组中`Option[(T1, T2, T3, ...)]`。
- `unapply()`方法虽然也可以定义在类中，但一般定义在**伴生对象**中(在类中定义没有合适的语法使用)。

假设有伴生对象名为`Unapply`，则：

```scala
var Unapply(arg1, arg2, arg3, ...) = value
```

等价于：

```scala
var (arg1, arg2, arg3, ...) = Unapply.unapply(value)
```

如下代码所示：

```scala
object TestUnapply extends App {
	var Unapply(num1) = 1							//提取一个值
	println(num1)
	var Unapply(num2, num3) = Unapply(100, 200)		//提取多个值
	println(num2 + " " + num3)
}

object Unapply {
	def apply(num1: Int, num2: Int) = new Unapply(num1, num2)
	def unapply(num: Int) = Option(num)
	def unapply(a: Unapply) = Option((a.num1, a.num2))
}

class Unapply(var num1: Int, var num2: Int)
```

输出结果：

```
1
100 200
```

若需要提取**任意长度**的值的序列，则可以使用`unapplySeq()`方法，该方法返回值类型为`Option[Seq[T]]`。
**不要**同时定义`unapplySeq()`方法和`unapply()`方法，会产生冲突。

如下代码所示：

```scala
object TestUnapply extends App {
	def showSplit(str: String) = str match {
		case Unapply(str1, str2) => println(s"$str1 $str2")
		case Unapply(str1, str2, str3) => println(s"$str1 $str2 $str3")
		case _ => println("Case Nothing")
	}
	showSplit("abc")
	showSplit("abc.cde")
	showSplit("abc.cde.efg")
}

object Unapply {
	def unapplySeq(str: String) = Option(str split "\\.")		//split()方法接收的是正则表达式，小数点、加减乘除之类的符号需要转义
}
```

输出结果：

```
Case Nothing
abc cde
abc cde efg
```

### *Case Class* (样例类) 与 *Pattern Matching* (模式匹配)
样例类是一种特殊的类，通常用在**模式匹配**中。
在类定义前使用`case`关键字即可定义一个样例类。

相比普通的类，样例类有以下特性：

- 样例类构造器中的字段默认使用`val`关键字定义(即默认为公有访问权限，而不是普通类默认的`private[this]`)。
- 样例类默认即实现了`apply()`方法用于构造对象和`unapply()`方法用于模式匹配。
- 样例类还默认实现了`toString`、`equals`、`hashCode`、`copy`等方法。
- 如果样例类默认生成的方法不合要求，也可以选择自行定义。

如下代码所示：

```scala
case class Case(num: Int = 100, str: String)

object Main extends App {

	var ca = Case(str = "S13")
	println(ca.num + " " + ca.str)

	//使用样例类提供的copy()方法可以复制出一个字段值相同的类
	var caCopy = ca.copy()
	println(caCopy.num + " " + caCopy.str)

	//也可以在copy()只复制需要的值甚至不使用原先对象的值
	var caCopy1 = ca.copy(200)
	var caCopy2 = ca.copy(str = "Abc")
	var caCopy3 = ca.copy(50, "ABC")
	println(caCopy1.num + " " + caCopy1.str)
	println(caCopy2.num + " " + caCopy2.str)
	println(caCopy3.num + " " + caCopy3.str)

	//样例类的实例之间可以直接比较,只要构造器中的字段值相同便会返回true
	println(ca == caCopy)

	//样例类经常用于模式匹配中
	def show(ca: Case) = ca match {
		case Case(num, _) if num > 100 => println("Case.num > 100")		//模式匹配中条件可以带有守卫
		case Case(100, _) => println("Case.num == 100")					//模式匹配可以精确到具体的数值，而对于不需要的值可以忽略(使用"_"符号)
		case _ => println("Not Matching")
	}

	show(ca)
	show(caCopy1)
	show(caCopy3)
}
```

输出结果：

```
100 S13
100 S13
200 S13
100 Abc
50 ABC
true
Case.num == 100
Case.num > 100
Not Matching
```

### *Trait* (特质)
Scala中的`trait`特质对应Java中的`interface`接口，但相比Java中的接口，Scala中的特质除了没有默认构造器、不能被直接实例化之外，拥有绝大部分类的特性。

Scala中的`trait`可以拥有构造器(非默认)，成员变量以及成员方法，成员方法也可以带有方法的实现，并且`trait`中的成员同样可以设置访问权限。

`Mixin`(混入)
> Scala不支持**多重继承**，一个类只能拥有一个父类，但可以**混入(mixin)**多个特质。
>
>	- Scala中采用的**混入(mixin)**机制相比传统的单根继承，保留了多重继承的大部分优点。
>	- 使用`with`关键字混入特质，一个类中混入多个特质时，会将第一个扩展的特质的父类作为自身的父类，同时，后续混入的特质都必须是从该父类派生。
>	- 若同时继承类并混入特质，需要将继承的类写在`extends`关键字的后面，`with`只能混入**特质**，不能混入**类**。
>
> 如下所示：
>
>	```scala
>	class BaseA
>
>	class BaseB
>
>	trait TraitA extends BaseA
>
>	trait TraitB extends BaseB
>
>	/* 编译报错，提示：
>	 * superclass BaseA
>	 * is not a subclass of the superclass BaseB
>	 * of the mixin trait TraitB
>	 */
>	class TestExtend extends TraitA with TraitB
>
>	/* 编译报错，提示：
>	 * class BaseA needs to be a trait to be mixed in
>	 */
>	class ExtendClass extends TraitA with BaseA
>	```
>
> `TestExtend`类中，特质`TraitA`的父类`BaseA`并不是特质`TraitB`父类`BaseB`的父类，而Scala中一个类只能拥有一个父类，因而无法通过编译。
> `ExtendClass`类中，应该继承`BaseA`后混入特质`TraitA`，`with`关键字之后的必需是特质而不能是类名。

重写冲突的方法与字段
> 与Java8中相同，混入机制同样需要解决**富接口**带来的成员冲突问题，当一个类的父类与后续混入的特质中带有相同名称的字段或相同签名的方法时，需要在子类重写这些冲突的内容，否则无法通过编译。
>
> 如下所示：
>
>	```scala
>	class BaseA {
>		def get = 123
>	}
>
>	trait TraitA {
>		def get = 456
>	}
>
>	trait TraitB {
>		def get = 789
>	}
>
>	class TestExtend extends BaseA with TraitA with TraitB {
>		override def get = 77		//对于冲突的内容，必需显式重写
>	}
>	```

混入顺序
> 对于混入的内容，按照以下顺序进行构造：
>
>	- 首先构造父类。
>	- 按照特质出现的顺序从左往右依次构造特质。
>	- 在一个特质中，若该特质存在父特质，则先构造父特质。若多个特质拥有相同的父特质，该父特质不会被重复构造。
>	- 最后构造子类。
>
> Scala的混入机制是`线性化`的，对于冲突的内容，构造中的后一个实现会顶替前一个。
> 线性化顺序与构造顺序`相反`，对于同名字段的内容，最终保留的是最右端的类或特质的实现。
>
> 如下所示：
>
>	```scala
>	class BaseA {
>		def get = 123
>	}
>
>	trait TraitA {
>		def get = 456
>	}
>
>	trait TraitB {
>		def get = 789
>	}
>
>	trait TraitC extends TraitA {
>		override def get = 111
>	}
>
>	class TestExtend extends BaseA with TraitA with TraitC {
>		override def get = super.get				//使用父类的实现时不需要显式指定到底是哪一个，编译器会自动按照线性化顺序选择最后的实现，即TraitC中的实现，即返回111
>		//override def get = super[BaseA].get		//也可以使用继承自其它特质或类的实现
>		//override def get = super[TraitB].get		//错误，必需使用直接混入的类或特质，不能使用继承层级中更远的类或特质
>	}
>	```

### 复制类实例
Scala与Java类似，类实例赋值仅仅是复制了一个引用，实例所指向的内存区域并未被复制。

若需要真正复制一个对象，需要调用对象的`clone()`方法。
`clone()`方法定义在`Object`类中，但由于是`protected`成员，不可直接调用，若需要自行实现类的复制功能，则需要实现`Cloneable`接口。

如下所示：

```scala
class Clone extends Cloneable {
	var nums = Array(1, 2, 3)
	var str = "TestClone"
	override def clone = {
		val clone = super.clone.asInstanceOf[Clone]		//Cloneable接口中clone()返回的是Object型，即Scala中的Any，需要进行强制类型转换
		clone.nums = nums.clone			//深复制需要对成员中的引用类型调用clone()
		clone
	}
}
```

与Java中类似，如果需要实现**深复制**，则需要对类成员中的`AnyRef`及其子类调用`clone()`进行复制。
对于`AnyVal`子类如`Int`、`Double`等类型，没有提供重载的`clone()`方法，但这些类型默认即为值复制，无需额外的操作。
Java中的特例`java.lang.String`在Scala中同样有效，对于`String`类型，在重写`clone()`时也可当作基本类型对待。

在Scala中，还可以直接继承`scala.collection.mutable.Cloneable[T]`特质：

```scala
import scala.collection.mutable.Cloneable

class Clone extends Cloneable[Clone] {
	var nums = Array(1, 2, 3)
	var str = "TestClone"
	override def clone = {
		val clone = super.clone			//不必进行强制类型转换，类型已在泛型参数中指定
		clone.nums = nums.clone
		clone
	}
}
```

### 匿名类初始化
在Scala中，创建类实例的**同时**可以直接对类的成员变量进行初始化。

如下代码所示：

```scala
object Init extends App {
	var num = new Num {
		num = 100
		name = "Num"
	}		//相当于创建了一个匿名类，然后向上转型到类Num上
	println(s"${num.name} ${num.num}")		//正常输出了初始化的值
}

class Num {
	var num: Int = 0
	var name: String = ""
}
```

以上代码用**Java**改写为：

```java
class Init {
	public static void main(String[] args) {
		Num num = new Num() {{
			num = 100;
			name = "Num";
		}};		//匿名类的构造函数的函数名为空，因此可以使用大括号直接嵌套的方式
		System.out.println(num.name + " " + num.num);
	}
}

class Num {
	int num = 0;
	String name = "";
}
```

输出结果：

```
Num 100
```



## *sealed* 和 *final* 关键字
`sealed`和`final`都是Scala语言的关键字。

- `final`关键字作用与Java中相同。用在类之前，表示类不可继承；用在方法之前，表示方法不可被重写。
- `sealed`关键字作用与C#中的`sealed`不同，在Scala中，`sealed`修饰的类其子类定义需要与该类在统一文件中。`sealed`的作用是防止继承被滥用。

### *sealed* 用于模式匹配
使用`sealed`关键字修饰的类型在用于模式匹配时，编译器会对匹配条件进行检查，如果匹配路径没有被完全覆盖，则会给出警告。

如下代码所示：

```scala
sealed abstract class Lang(name: String)

case class C(name: String = "C") extends Lang(name)
case class CPP(name: String = "C++") extends Lang(name)
case class CSharp(name: String = "C#") extends Lang(name)

object Main extends App {
	def getLangName(lang: Lang) = lang match {
		case C(name) => name
		case CPP(name) => name
	}
}
```

编译时会得到警告：

```
Main.scala:10: warning: match may not be exhaustive.
It would fail on the following input: CSharp(_)
	lang match {
	^
one warning found
```

编译器提示**匹配可能会有遗漏**。

若代码中去掉基类定义前的`sealed`关键字，则编译器不再输出警告。



## 格式化输出
使用`print()/println()`可以打印`String`类型的文本输出。
复杂文本可以使用类似Java的字符串拼接方式(使用操作符`+`)。

- `StringLike.format()`方法。
- `StringContext`类中的`s()`、`f()`、`raw()`等插值器方法用于以指定的方式输出字符串。

### *StringLike.format()* 格式化输出
在Scala中，字符串依然使用Java中标准的`String`类型，但通过**隐式转换**特性，`String`可以被自动构造为`StringLike`类型。

`StringLike`类型提供了一系列方便强大的字符操作方法，格式化字符串可以使用其提供的`format()`方法(使用方式类似于静态方法`String.format()`，但使用方法调用者作为格式化内容而非方法的首个参数)，如下所示：

```scala
scala> "Test format str:\nString %s\nInt %d\nFloat %f\n".format("Hello World!", 666, 666.666)
res0: String =
"Test format str:
String Hello World!
Int 666
Float 666.666
"
```

### s字符串插值器
在Scala 2.10之后，还可以使用字符串插值器`s""`，基本用法如下所示：

```scala
scala> var str = "Hello World"
str: String = Hello World

//使用插值器后，在变量前使用"$"符号即可将变量值作为文本插入
scala> s"The str is $str"
res0: String = The str is Hello World

scala> var num = 200
num: Int = 200
scala> s"The num is $num"
res1: String = The num is 200
```

使用`${expr}`的方式可以在插值器中引用复杂表达式：

```scala
scala> var (a, b, c) = (1, "Test", 2.0)
a: Int = 1
b: String = Test
c: Double = 2.0

scala> s"${"%d %s %f".format(a, b, c)} ${a + c}"
res2: String = 1 Test 2.000000 3.0
```

`s""`字符串插值器实际上相当于调用`StringContext.s()`，`r""`、`raw""`插值器类似。

### f字符串插值器
除了`s""`字符串插值器，还有带有格式化功能的`f""`插值器。

相比s插值器，f插值器可以带有格式化参数，在不使用格式化参数的情况下，f插值器作用与s插值器相同。如下所示：

```scala
scala> var (a, b) = (1.0, 2.5)
a: Double = 1.0
b: Double = 2.5

//引用变量之后紧跟格式化字符
scala> f"$a%6.3f $b%10.5f"
res3: String = " 1.000    2.50000"
```

### raw字符串插值器
`raw""`插值器用法与`s""`类似，但不会转义反斜杠。如下所示：

```scala
scala> raw"\n\s\\b\\%''^#@ $num"
res15: String = \n\s\\b\\%''^#@ 3.0
```



## 终端输入
早期的Scala中`Console`类提供了一系列的终端输入方法，在现在的版本中这些方法已经被**废弃**。

- 当前版本的Scala获取终端输入需要使用包`scala.io.StdIn`中的相关方法。
- `scala.io.StdIn`中的相关方法签名与先前的`Console`类中完全相同。
- 使用`readLine()`获取单行文本输入，返回`String`类型。
- 使用`readInt()/readFloat()/readChar()/readLong()...`等方法获取特定类型的输出，当输入的内容不匹配时，会抛出异常。
- 使用`readf()/readf1()/readf2()/readf3()`等方法能以`java.text.MessageFormat`语法格式化接收的终端输入。

如下代码所示：

```scala
scala> val str = scala.io.StdIn.readLine()		//自行脑补终端输入"Test input"
str: String = Test input
scala> val int = scala.io.StdIn.readInt()		//自行脑补终端输入"200"
int: Int = 200

//输入内容不匹配读取类型时会抛出异常
scala> val double = scala.io.StdIn.readDouble()
java.lang.NumberFormatException: For input string: "test"
  at sun.misc.FloatingDecimal.readJavaFormatString(FloatingDecimal.java:2043)
  at sun.misc.FloatingDecimal.parseDouble(FloatingDecimal.java:110)
  at java.lang.Double.parseDouble(Double.java:538)
  at scala.collection.immutable.StringLike$class.toDouble(StringLike.scala:284)
  at scala.collection.immutable.StringOps.toDouble(StringOps.scala:30)
  at scala.io.StdIn$class.readDouble(StdIn.scala:155)
  at scala.io.StdIn$.readDouble(StdIn.scala:229)
  ... 33 elided

//readf()可以接收任意数量的值，返回值为List[Any]类型
scala> val list = scala.io.StdIn.readf("{0} + {1}")				//自行脑补终端输入"Test + Input"
list: List[Any] = List(Test, Input)								//按照格式化字符串提取出了输入内容
scala> list foreach { println }
Test
Input

//readf1()仅能接收一个值，返回接收的值
scala> val num = scala.io.StdIn.readf1("This is {0}")			//自行脑补终端输入"This is 666"
num: Any = 666
//readf2()/readf3()接收两个/三个值，返回值为Tuple类型
scala> val tuple = scala.io.StdIn.readf3("{0} + {1} + {2}")		//自行脑补终端输入"One + Two + Three"
tuple: (Any, Any, Any) = (On,Two,Three)
```



## *Enumerate* (枚举)
在Scala中，没有语言级别的枚举类型，枚举的功能可以通过**继承**枚举类`Enumeration`实现。

### 继承枚举类
继承枚举类`Enumeration`可以在成员中使用无参方法`Value`给每个枚举成员赋值。
默认的`Value`方法会按**变量名**生成**枚举名**和并自动从`0`开始生成**枚举ID**，若需要手动设定枚举名称和枚举ID则可以使用`Value`方法的重载`Value(id: Int, name: Strig)`。

如下代码所示：

```scala
object Color extends Enumeration {

	// 自动赋值枚举成员
	val red, green, blue = Value

	/*
	* 相当于分别初始化：
	* val red = Value
	* val green = Value
	* val blue = Value
	*/

	// 手动使用 Value(id: Int, name: String) 方法手动进行id和name的设置
	val white = Value(100, "White")
	val black = Value(200, "Black")
	// 使用重载有參版本的Value(id: Int, name: String)不能采用自动赋值的方式，会编译报错
}

object TestEnumeration extends App {
	println(Color.red.toString + ":" + Color.red.id + " " + Color.green + ":"
		+ Color.green.id + " " + Color.blue + ":" + Color.blue.id)
	println(Color.white + ":" + Color.white.id + " " + Color.black + ":" + Color.black.id)
}
```

输出结果：

```
red:0 green:1 blue:2
White:100 Black:200
```

### 调用枚举类型
继承了枚举类的单例对象名并不能直接用于表示枚举类型，对应的枚举类型应使用对象内部定义的抽象类型`Value`来表示，即`单例对象名称.Value`。

以前文中的`Color`单例对象为例，对应的枚举类型应使用`Color.Value`表示。

将枚举做为参数传递，如下代码所示：

```scala
object Color extends Enumeration {
	val red, green, blue = Value
	val white = Value(100, "White")
	val black = Value(200, "Black")
}

object Main extends App {
	// Xxx.Value才是真正的枚举类型
	def showEnum(color: Color.Value) = println(s"ID: ${color.id}, Str: ${color.toString}")
	showEnum(Color.blue)
	showEnum(Color.white)
}
```

输出结果：

```
ID: 2, Str: blue
ID: 100, Str: White
```

### 访问枚举内容
枚举单例支持以多种形式访问：

- 通过枚举成员访问，类似于其它常见编程语言(`Enum.member`)
- 通过枚举ID进行访问，语法类似数组(`Enum(id)`)
- 通过枚举名称进行访问，使用`withName`成员方法(`Enum withName "xxx"`)

枚举内部的成员全部保存在一个`Set`容器中，可使用`values`成员方法访问。

以前文中的`Color`单例对象为例，使用多种方式访问枚举内容，如下代码所示：

```scala
object Color extends Enumeration {
  val red, green, blue = Value
  val white = Value(100, "White")
  val black = Value(200, "Black")
}

object Main extends App {

	def showEnum(color: Color.Value) = println(s"ID: ${color.id}, Str: ${color.toString}")

	// 通过枚举ID访问枚举
	showEnum(Color(0))
	showEnum(Color(100))

	println()

	// 通过枚举名称访问枚举
	showEnum(Color withName "green")
	showEnum(Color withName "Black")

	println()

	// 遍历枚举内容
	for (color <- Color.values)
		showEnum(color)
}
```

输出结果：

```
ID: 0, Str: red
ID: 100, Str: White

ID: 1, Str: green
ID: 200, Str: Black

ID: 0, Str: red
ID: 1, Str: green
ID: 2, Str: blue
ID: 100, Str: White
ID: 200, Str: Black
```



## 基础数据结构
Scala常用的基础结构包括**数组**和**元组**。

### 定长数组
在Scala中定长数组使用`Array[T]`进行表示，定长数组与Java中概念类似。

构建一个固定长度的数组如下所示：

```scala
scala> var array = new Array[Int](10)			//构建一个长度为10的Int型数组
array: Array[Int] = Array(0, 0, 0, 0, 0, 0, 0, 0, 0, 0)
scala> var a = Array(100, 200)					//使用伴生对象的apply()方法创建数组
a: Array[Int] = Array(100, 200)
scala> array(5)									//获取数组中指定位置的值(使用小括号中加偏移量)
res1: Int = 0
scala> array(5) = 10							//给指定位置的元素赋值
scala> array									//查看赋值结果
res2: Array[Int] = Array(0, 0, 0, 0, 0, 10, 0, 0, 0, 0)
scala> array(100)								//数组访问越界会抛出异常
java.lang.ArrayIndexOutOfBoundsException: 100
  ... 33 elided
```

需要注意的是，Scala定长数组与Java中的定长数组仅仅是语法不同，并无本质区别，`new Array[Int](10)`相当于Java中的`new int[10]`。

### *Tuple* (元组)
元组是最简单的容器，无需额外的类型名称，直接使用`(value1, value2, value3, ...)`就可以构建出一个元祖。如下所示：

```scala
scala> var tuple = (1, 2, 3)
tuple: (Int, Int, Int) = (1,2,3)
```

元组中允许包含**重复**的值，也允许不同类型的值，但元组一经创建，内容便不可改变。

元组可以通过`元组对象._索引号`的形式访问。元组下标从`1`开始而非`0`，如下所示：

```scala
scala> println(tuple._1 + " " + tuple._2 + " " + tuple._3)
1 2 3
```

元组可以用来一次性初始化多个变量：

```scala
scala> var (a, b, c) = tuple			//等价于 var (a, b, c) = (1, 2, 3)
a: Int = 1
b: Int = 2
c: Int = 3
scala> println(s"$a $b $c")
1 2 3
```

元组可以包含**不同**的类型：

```scala
scala> var (num, str) = (123, "456")
num: Int = 123
str: String = 456
```

元组用作函数返回类型时，即可让一个函数拥有多个返回值，如下所示：

```scala
object TestTuple extends App {
	def getNum(num1: Int, num2: Int, num3: Int) = (num1, num2, num3)
	var (num1, num2, num3) = getNum(1, 2, 3)
	println(s"$num1 $num2 $num3")
}
```

输出结果：

```
1 2 3
```

需要注意的是，元组**不支持**使用`for`循环进行遍历。



## 容器
Scala的容器按数据结构分为`序列(Seq)`、`集合(Set)`和`映射(Map)`三大类。

- `序列(Seq)`为有序容器，按照元素添加的顺序排列，其中，`Seq`的子类`IndexedSeq`允许类似数组的方式按照下标进行访问。
- `集合(Set)`为数学意义上的集合，不包含重复元素，其中，`Set`的子类`SortedSet`中元素以某种顺序排序。
- `映射(Map)`为`键 - 值`对偶的集合，其中，`Map`的子类`SortedMap`中键值以某种顺序排序。

容器按照是否可变分为**不可变容器**`scala.collection.immmutable._`和**可变容器**`scala.collection.mutable._`。

### *List* (列表) 与 *ListBuffer* (可变列表)
在Scala中，`List[T]`类型的完整包路径为`scala.collection.immutable.List`，继承于`Seq`。
List为**不可变对象**，可以使用`for`操作符进行遍历。

构建一个列表：

```scala
scala> var list0 = List(1, 2, 3)
list0: List[Int] = List(1, 2, 3)
```

除了直接使用List类型提供的`apply()`方法构建列表对象之外，还可以使用`::`操作符来将多个值构成列表，使用操作符构成列表时需要注意，列表的最后一个值必须为`Nil`，如下所示：

```scala
scala> var list1 = 0 :: 1 :: 2 :: 3 :: Nil
list1: List[Int] = List(0, 1, 2, 3)
```

列表同样允许不同类型的值，也允许重复的值，如下所示：

```scala
scala> var list2 = 1 :: 1 :: "str" :: 2.0 :: Nil
list2: List[Any] = List(1, 1, str, 2.0)
```

若列表中存储的若是相同的类型，则编译器会将`List[T]`推导为具体的类型，若列表中成员类型各不相同，则编译器会使用所有类型的基类`Any`作为泛型类型及`List[Any]`。

列表支持从已有的列表进行创建：

```scala
scala> var list0 = 1 :: 2 :: 3 :: Nil
list0: List[Int] = List(1, 2, 3)
scala> var list1 = 0 :: list0				//向列表头部增加元素
list1: List[Int] = List(0, 1, 2, 3)
scala> var list2 = list0 :: 4				//列表是不能从尾部创建(List以Nil结尾)
<console>:11: error: value :: is not a member of Int
	var list2 = list0 :: 4
					  ^
```

使用`:::`运算符可以叠加两个列表：

```scala
scala> var list2 = list0 ::: list1
list2: List[Int] = List(1, 2, 3, 0, 1, 2, 3)
也可以使用"++"运算符连接两个列表：
scala> var list3 = list0 ++ list1
list3: List[Int] = List(1, 2, 3, 0, 1, 2, 3)
```

`:::`与`++`对于列表而言，作用完全相同，只不过`:::`是`List`类型特有的运算符，而`++`继承于特质`TraversableLike`，也可用于一些其它的集合类型。

列表同样支持通过索引进行访问，语法与`Array[T]`类型类似：

```scala
scala> list0(0)
res0: Int = 1
```

在Scala中，同样支持可变列表类型(`ListBuffer`)。

- 可变列表`scala.collection.mutable.LinkedList`在现在的版本中(2.11.7)已被标记为废弃的。
- 当前版本可以使用`scala.collection.mutable.ListBuffer`为可变列表。
- 不可变列表`List`不支持`+=`和`-=`运算，但`ListBuffer`类型支持。
- `ListBuffer`不支持`::`以及`:::`运算符。

`ListBuffer[T]`类的常规操作如下所示：

```scala
object TestList extends App {
	import scala.collection.mutable._
	val show: ListBuffer[Any] => Unit = for (s <- _) print(s"$s ")
	var listBuffer = ListBuffer(1, "str", 2.0)
	listBuffer.remove(0)				//移除指定索引位置的值
	show(listBuffer)
	println
	listBuffer += "num"					//添加新值
	show(listBuffer)
	println
	listBuffer.update(2, "new")			//改变指定位置的值
	show(listBuffer)
}
```

输出结果：

```
str 2.0
str 2.0 num
str 2.0 new
```

### *ArrayBuffer* (变长数组)
在Scala中，变长数组使用`ArrayBuffer[T]`进行表示，`ArrayBuffer`不在默认导入的包路径中，位于`scala.collection.mutable.ArrayBuffer`，继承于`Seq`。
Scala中的`ArrayBuffer`相当于Java中的`ArrayList`，可存储任意数量的元素，创建一个`ArrayBuffer`：

```scala
scala> var arrayBuffer = new ArrayBuffer[Int]
arrayBuffer: scala.collection.mutable.ArrayBuffer[Int] = ArrayBuffer()
var a = ArrayBuffer(100, 200)					//同样可以使用伴生对象的apply()方法创建ArrayBuffer
a: scala.collection.mutable.ArrayBuffer[Int] = ArrayBuffer(100, 200)
```

`ArrayBuffer`可以使用`+=`和`-=`进行**增加**与**删除**元素：

```scala
scala> arrayBuffer += 10
res10: scala.collection.mutable.ArrayBuffer[Int] = ArrayBuffer(10)
scala> arrayBuffer += 100
res11: scala.collection.mutable.ArrayBuffer[Int] = ArrayBuffer(10, 100)
scala> arrayBuffer += 1000
res12: scala.collection.mutable.ArrayBuffer[Int] = ArrayBuffer(10, 100, 1000)
scala> arrayBuffer -= 1000
res13: scala.collection.mutable.ArrayBuffer[Int] = ArrayBuffer(10, 100)
```

需要注意的是，`+=`、`-=`只是**方法名**并不是**运算符**，因此，以下的写法会**报错**：

```scala
arrayBuffer = arrayBuffer + 10
<console>:12: error: type mismatch;
found : Int(10)
required: String
	arrayBuffer = arrayBuffer + 10
								^
```

与Java中的`ArrayList`类似，`ArrayBuffer`也允许在**任意位置**进行元素插入：

```scala
scala> arrayBuffer.insert(1, -100)					//在索引1的位置插入数值-100
scala> arrayBuffer
res17: scala.collection.mutable.ArrayBuffer[Int] = ArrayBuffer(10, -100, 100)
```

插入多个元素：

```scala
scala> arrayBuffer.insert(1, 7, 8, 9)				//在索引1的位置插入数值7，8，9
scala> arrayBuffer
res19: scala.collection.mutable.ArrayBuffer[Int] = ArrayBuffer(10, 7, 8, 9, -100, 100)
```

删除操作类似，移除操作可以指定首尾进行**批量移除**：

```scala
scala> arrayBuffer.remove(1, 4)
scala> arrayBuffer
res21: scala.collection.mutable.ArrayBuffer[Int] = ArrayBuffer(10, 100)		//删除了索引1到4位之间的元素
```

需要注意的是，`ArrayBuffer`是**线性结构**，只有在尾部进行插入删除操作才是高效的，在其它位置进行的元素操作都会造成大量的元素移动。
`ArrayBuffer`的不可变版本对应为`scala.collection.immutable.Vector`。

### *Set* (集合)
`Set[T]`类型为数学意义上的集合，集合内不允许重复元素。
`Set`完整包路径为`scala.collection.immutable.Set`。
集合同样允许任意类型的元素，但集合中不能包含重复的元素。

在使用`Set`类的`apply()`方法构建集合时，重复的元素会被忽略，如下所示：

```scala
scala> var set = Set(1, 1, 's', "str")
set: scala.collection.immutable.Set[Any] = Set(1, s, str)		//重复的元素"1"被忽略了
```

`Set`可以使用`+`、`-`操作符来增加或是减少元素并返回新的集合。
使用`+`、`-`操作符会返回新的集合，但原集合内的值不会发生改变，如下所示：

```scala
scala> var set1 = set + 3
set1: scala.collection.immutable.Set[Any] = Set(1, s, str, 3)	//原集合添加元素输出新的集合
scala> set
res0: scala.collection.immutable.Set[Any] = Set(1, s, str)		//原集合本身没有变化
scala> var set2 = set - 's'
set2: scala.collection.immutable.Set[Any] = Set(1, str)			//从集合中移除一个元素
scala> set
res1: scala.collection.immutable.Set[Any] = Set(1, s, str)
```

与动态数组`ArrayBuffer`类似，集合可以使用`+=`、`-=`来增加或减少内部的元素：

```scala
scala> var set = Set(1, 2, 3)
set: scala.collection.immutable.Set[Int] = Set(1, 2, 3)
scala> set += 4					//增加元素"4"
scala> set
res14: scala.collection.immutable.Set[Int] = Set(1, 2, 3, 4)
scala> set -= 4					//移除元素"4"
scala> set
res16: scala.collection.immutable.Set[Int] = Set(1, 2, 3)
```

使用`contains()`方法可以判断某个元素是否在集合中：

```scala
scala> set.contains('s')
res2: Boolean = true
```

使用`find()`方法可以传入一个高阶函数`T => Boolean`自定义规则进行查找，`find()`方法返回`Option[T]`，如下所示：

```scala
scala> var set = Set(1, 2, 3, 's', "str")
set: scala.collection.immutable.Set[Any] = Set(s, 1, 2, str, 3)
scala> set.find(_.isInstanceOf[Int])
res7: Option[Any] = Some(1)					//返回第一个匹配到的元素
scala> set.find(_.isInstanceOf[Double])
res8: Option[Any] = None					//没有匹配则返回None
```

`scala.collection.immutable.Set`以哈希集实现，元素依据HashCode进行组织。

`Set`的相关类型还有：

- `scala.collection.mutable.LinkedHashSet` 链式哈希集，依照插入的顺序排列
- `scala.collection.immutable.SortedSet` 红黑树实现的排序集

### *Map* (映射)
`Map[A, B]`类型的完整包路径为`scala.collection.immutable.Map`。
映射中的每一个元素都是一组`对偶(Tuple2)`，分别为key和value，key不可重复，通过`->`操作符可以将两个值组成一组对偶，如下所示：

```scala
scala> var map = Map(1 -> "1", 2 -> "2", 3 -> "3")
map: scala.collection.immutable.Map[Int,String] = Map(1 -> 1, 2 -> 2, 3 -> 3)
scala> for ((key, value) <- map) println(s"key: $key value: $value")
key: 1 value: 1
key: 2 value: 2
key: 3 value: 3								//使用for循环遍历map
scala> for (value <- map.values) println(s"value: $value ")
value: 1
value: 2
value: 3									//仅遍历map的value
scala> for (key <- map.keys) println(s"value: $key ")
value: 1
value: 2
value: 3									//仅遍历map的key
```

使用`updated()`方法可以更新指定key对应的value之后输出，通过`+`方法添加对偶后输出，也可以通过`-`移除指定key的对偶后输出。
但这些操作不会改变原本映射的内容：

```scala
scala> map.updated(1, "0")
res20: scala.collection.immutable.Map[Int,String] = Map(1 -> 0, 2 -> 2, 3 -> 3)
scala> map + (4 -> "4")
res21: scala.collection.immutable.Map[Int,String] = Map(1 -> 1, 2 -> 2, 3 -> 3, 4 -> 4)
scala> map - 1
res22: scala.collection.immutable.Map[Int,String] = Map(2 -> 2, 3 -> 3)
scala> map									//更改的结果作为返回值输出，原本的Map值没有任何改变
res23: scala.collection.immutable.Map[Int,String] = Map(1 -> 1, 2 -> 2, 3 -> 3)
```

与`Set`、`ListBuffer`等类似，`Map`也支持`+=`、`-=`操作符。
`Map`使用`+=`向自身添加对偶，使用`-=`从自身移除指定key对应的对偶。
除了不可变的`scala.collection.immutable.Map`外，还有可变的`scala.collection.mutable.Map`类型。
Scala还提供了多种不同结构的`Map`实现，如`HashMap`、`ListMap`、`LinkedHashMap`等。



##  *Higher Order Function* (高阶函数)
**高阶函数**是**函数式编程**中的概念，在数学中，也叫做**算子**(运算符)或**泛函**。
**接受一个或多个函数作为输入**或者**输出一个函数**的函数被称为高阶函数。

在`Scala`中，容器类提供了高阶函数作为容器数据操作的接口，常见的高阶函数有`map`、`reduce`、`flatMap`、`filter`、`find`、`fold`、`foreach`等。



## *Generators* (生成器)
`Scala`中同样提供了`yield`关键字，支持生成器语法。
使用`yield`可以将循环中每一轮的结果以容器的形式输出，使用`yeild`可以方便生成一系列的特定值。

如下所示：

```scala
scala> for (i <- 1 to 5) yield i
res20: scala.collection.immutable.IndexedSeq[Int] = Vector(1, 2, 3, 4, 5)

//使用for语句内置的守卫语法限制输出
scala> for (i <- 1 to 5 if i > 2) yield i
res21: scala.collection.immutable.IndexedSeq[Int] = Vector(3, 4, 5)

//生成器的生成结果与被遍历的容器类型相关
scala> for (i <- 1 :: 2 :: 3 :: 4 :: 5 :: Nil if i > 2) yield i
res24: List[Int] = List(3, 4, 5)

//生成的结果不是目标容器则可以进行转换
scala> (for (i <- List(1, 2, 3, 4, 5) if i > 2) yield i) toSet
res27: scala.collection.immutable.Set[Int] = Set(3, 4, 5)
```

### 使用高阶函数替代生成器
Scala中可以使用高阶函数，以函数式风格实现类似`yield`的效果。

```scala
//从1到5的数中找出偶数，并将数值翻倍

//使用命令式编程风格，使用守卫和生成器
scala> for (i <- 1 to 5 if i % 2 == 0) yield i * 2
res13: scala.collection.immutable.IndexedSeq[Int] = Vector(4, 8)

//使用函数式编程风格，使用高阶函数
scala> 1 to 5 filter { _ % 2 == 0 } map { _ * 2 }
res15: scala.collection.immutable.IndexedSeq[Int] = Vector(4, 8)
```



## *Package* (包)
`Scala`中的包用法基本与`Java`类似：

- 使用`package`关键字定义包路径。
- 使用`import`关键字导入包路径。

### 包与路径
在`Scala`中，包路径是**逻辑概念**，源码文件**不必**按照包路径存放到对应的目录下。

`Scala`中使用`_`符号表示导入该路径下的所有包和成员：

```scala
import java.awt._	//等价于java中的 import java.awt.*
```

导入路径规则与`Java`中的类似，处于同一级包路径下的类可以直接使用不必导入。

导入策略
> 在导入包时，`Scala`默认采用**相对路径**，在外层路径的包使用内层路径的包时，可省略共同的路径部分直接以当前路径为起点访问内层路径包。
>
> 如下代码所示：
>
>	```scala
>	// file1
>	package com.dainslef
>
>	class Test
>
>
>	// file2
>	package com
>
>	// 导入路径时以当前包为起点，不必从最外层路径开始导入
>	import dainslef.Test
>
>	object Main extends App {
>		println(classOf[Test].getName)
>	}
>	```
>
> 而在`Java`中，无论包的层次关系如何，都需要通过绝对路径进行导入。
>
> 上例对应`Java`版本如下代码所示：
>
>	```java
>	// file1
>	package com.dainslef;
>
>	class Test {
>	};
>
>
>	// file2
>	package com;
>
>	// 导入路径时从时需要从最外层路径开始导入，不能写成 import dainslef.Test
>	import com.dainslef.Test;
>
>	public class Main {
>
>		public static void main(String[] args) {
>			System.out.println(Test.class.getName());
>		}
>
>	}
>	```

默认包与绝对路径导入
> 在`Java`和`Scala`中，不使用`package`关键字打包的代码即位于**默认包**下，没有对应的包名。  
> 在`Scala`中使用`_root_`指代默认包。
>
> `Scala`中默认的`import`操作是基于相对路径的，但`Scala`同样支持以**绝对路径**进行`import`操作：
>
>	- 以`_root_`为导入起始路径，即代表以绝对路径的形式导入内容。
>	- 使用绝对路径访问内容能避免一些命名冲突。
>
> 上例中的代码中的`Test`类以绝对路径导入，导入语句可写成：
>
>	```scala
>	import _root_.com.dainslef.Test
>	```

默认包的限制
> 默认包没有名称，其内容只能被同在默认包下的其它内容访问。  
> 内层包无法访问外部默认包的内容，即使使用`_root_`访问绝对路径依旧无法访问。
>
> 如下代码所示：
>
>	```scala
>	// file1
>	// 定义单例在默认包中
>	object Test {
>		val test = "Test string..."
>	}
>
>	// file2
>	package com
>
>	object Main extends App {
>		// 在内层包中访问外部默认包的内容
>		println(Test.test)				//错误，提示 "not found: value Test"
>		println(_root_.Test.test)		//错误，提示 "object Test is not a member of package <root>"
>	}
>	```

### 扩展用法
`Scala`包机制在Java的基础上扩充了更多的功能。

在一个语句中导入包内的**多个**指定的类：

```scala
import java.awt.{Color, Font}
```
在导入一个包的同时可以将包内的类进行重命名：

```scala
import java.awt.{Color => JavaColor}
```

如果不希望某个类被导入，则可以用以下方式隐藏某个类：

```scala
import java.awt.{Color => _}
```

`Scala`中的`import`带有类似`Java 1.6`中的`static import`特性：

```scala
import java.lang.Math.abs		//导入Math类中的静态方法abs
```

在Scala中，包引入了名称相同的类不会发生冲突，而是后引入的类**覆盖**之前引入的类。  
在Scala中，`import`语句可以出现在**任意位置**，不必总是放在文件的顶部，`import`语句的作用域直到该语句块结束。

### 默认导入
默认情况下，Scala会导入以下几个包路径：

```scala
import java.lang._
import scala._
import Predef._
```

有些Scala包中的类名与Java包中的类名相同，但由于Scala包的引入语句在后，因此，例如`Scala.StringBuiler`类会覆盖`Java.lang.StringBuilder`。

### 包对象
在Scala中，每个包可以带有一个与包名相同的**包对象**，包内的所有类都可以直接访问该包对象的公有成员。  
如下代码所示：

```scala
package object Package {
	var num0 = 0
	protected var num1 = 1
	private var num2 = 2
}

package Package {
	object Test extends App {
		println(num0)		//正确，可以直接访问包对象的公有成员，不用使用前缀
		println(num1)		//错误，不能访问包对象的保护成员
		println(num2)		//错误，不能访问包对象的私有成员
	}
}
```



## *Implicit Conversions* (隐式转换)
隐式转换在构建类库时是一个强大的工具。  
使用隐式转换特性需要在编译时添加`-language:implicitConversions`选项。

### 定义隐式转换
Scala是**强类型**语言，不同类型之间的变量默认**不会**自动进行转换。  
若需要提供类型之间的自动转换功能，需要显式使用`implicit`关键字自定义隐式转换。  
隐式转换可以定义在**当前类**中或是**伴生对象**中，只要需要进行转换时能被访问到即可。  

当传入参数的类型与函数需要的类型不同时，编译器便会查找是否有合适的隐式转换，如下所示：

```scala
class Implicit(val num: Int)

object Implicit {
	implicit def implToInt(impl: Implicit) = impl.num
	def apply(num: Int) = new Implicit(num)
}

object Main extends App {

	implicit def implToStr(impl: Implicit) = impl.num.toString

	def showNum(num: Int) = println(num)
	def showStr(str: String) = println(str)

	showNum(Implicit(100))
	showStr(Implicit(200))
}
```

当访问一个实例不存在的成员时，编译器也会查找是否存在隐式转换，能将其转化为拥有此成员的类型，如下所示：

```scala
class Implicit(val num: Int) {
	def show = println(num)
}

object Implicit {
	implicit def intToImpl(num: Int) = new Implicit(num)
}

object Main extends App {
	import Implicit.intToImpl			//当隐式转换没有定义在当前作用域也不在实例的伴生对象中时需要显式导入
	100.show							//Int型被隐式转换为Implicit类型
}
```

当一个实例自身和方法的参数都能通过隐式转换来满足方法调用时，优先转换方法参数而不是实例自身，如下所示：

```scala
class Impl1(val str: String = "100") {
	def show(impl: Impl2) = println(impl.str)
}

object Impl1 {
	implicit def impl1ToImpl2(impl: Impl1) = new Impl2(impl.str)
}

class Impl2(val str: String = "200") {
	def show(impl: Impl1) = println(impl.str)
	def test = println(300)
}

object Main extends App {
	var impl1 = new Impl1
	impl1.test					//实例由Impl1类型隐式转换成了Impl2类型
	impl1.show(impl1)			//可以通过将实例隐式转换为Impl2类型来满足方法调用，但编译器实际执行的操作是将参数隐式转换成了Impl2类型
}
```

输出结果：

```
300
100
```

`Scala`标准类库中大量使用了隐式转换特性。
以`String`类型为例，源自`Java`标准库的`String`类型自身并未定义`toInt/toDouble`等成员方法，在调用这些方法时，`String`被**隐式转换**成定义了这些方法的`StringLike`类型来执行这些操作。

### 隐式参数
函数和方法的参数前可以添加关键字`implicit`来将一个参数标记为**隐式参数**。  
当调用方法时没有对隐式参数赋值，则编译器会尝试为隐式参数寻找匹配的隐式值。

变量前可以通过添加`implicit`关键字成为隐式值。  
如下所示：

```scala
object Implicit {
	implicit val impl = 200.0	//隐式值可以定义在伴生对象中
	def testImplicit(implicit num: Double) {
		println(num)
	}
}

object Main extends App {
	import Implicit.impl		//不在当前作用域中的隐式参数需要显式引入
	Implicit.testImplicit
}
```

输出结果：

```
200.0
```

隐式参数的限制：

- 用于声明隐式参数的`implicit`关键字只能出现在参数表的最前端，隐式参数的声明对当前参数表内的**所有参数**有效。
- 使用柯里化定义多个参数表时，只能声明**最后一个**参数表内的参数为隐式参数。
- 一个隐式参数在被调用的作用域内存在多个匹配的同类型隐式值时，编译报错。

如下所示：

```scala
def testImplicit(implicit num0: Int, num1: Int) {}				//正确。num0、num1，皆为隐式参数
def testImplicit(implicit num0: Int, implicit num1: Int) {}		//错误。只能在参数表的首个参数前添加implicit关键字修饰
def testImplicit(num0: Int, implicit num1: Int) {}				//错误。只能在参数表的首个参数前添加implicit关键字修饰

def testImplicit(num: Int)(implicit num0: Int, num1: Int) {}	//正确。对于柯里化函数，最后一个参数表可以设为隐式参数
def testImplicit(implicit num0: Int)(implicit num1: Double) {}	//错误。一个方法不允许拥有多个隐式参数表
def testImplicit(implicit num0: Int)(num1: Double) {}			//错误。只有最后一个参数表可以设为隐式参数表
```

隐式参数与参数默认值
> 隐式参数与参数默认值特性**可以**共存。
>
> 当一个方法的所有隐式参数均带有默认值时，可以直接调用，如下所示：
>
>	```scala
>	object Main extends App {
>
>		// 方法带有默认参数以及参数默认值
>		def testImplicit(implicit num0: Int = 0, num1: Double = 0) = println(s"$num0 $num1")
>
>		// 直接调用，无需隐式参数
>		testImplicit
>	}
>	```
>
> 输出结果：
>
>	```
>	0 0.0
>	```
>
> 隐式参数与默认值的优先级
>
>	- 当一个方法的隐式参数带有部分默认值时，隐式调用时只需提供没有默认值的部分参数。
>	- 当一个隐式参数既有默认值又有隐式值时，会优先使用隐式值。
>
> 如下所示：
>
>	```scala
>	object Main extends App {
>
>		def testImplicit(implicit num0: Int = 0, num1: Double) = println(s"$num0 $num1")
>
>		// 只需为没有默认值的参数提供隐式值
>		implicit val num1 = 2.0
>		testImplicit
>
>		// 此时num0既有隐式值，也有参数默认值
>		implicit val num0 = 1
>		testImplicit
>	}
>	```
>
> 输出结果：
>
>	```
>	0 2.0
>	1 2.0
>	```
>
> 输出结果说明第二次调用`testImplicit()`方法时，优先采用了隐式值而非参数默认值。
>
> 隐式值与参数默认值在方法调用时区别如下：
>
>	- 采用参数默认值时，即使参数全部拥有默认值，参数表不可省略(`()`操作符必须存在)。
>	- 采用隐式值时，隐式参数全部具有隐式值或默认值时，参数表直接省略。
>
> 当一个隐式参数表的所有参数均带有默认值且作用域内也拥有满足条件的隐式值时，调用方法时带有`()`操作符为使用默认值，省略参数表为使用隐式值。
>
> 如下所示：
>
>	```scala
>	object Test extends App {
>
>		def testImplicit(implicit num0: Int = 0, num1: Double = 0) = println(s"$num0 $num1")
>
>		implicit val num0 = 1
>		implicit val num1 = 1.0
>
>		testImplicit			//全部采用隐式值
>		testImplicit()			//全部采用默认值
>	}
>	```
>
> 输出结果：
>
>	```
>	1 1.0
>	0 0.0
>	```

### 隐式类
类定义前同样可以使用`implicit`成为**隐式类**。

- 隐式类的主构造器**有且只有**一个参数，同时，该参数**不能**为隐式参数。
- 隐式类的主构造器不能通过参数默认值、隐式参数等形式来模拟成参数表成只有一个参数的情况。
- 隐式类特性**不能**与样例类共存，即一个类在定义时不能同时带有`implicit`和`case`关键字。
- 隐式类**不能**定义在外部区域(包，以及包对象)，隐式类只能定义在类体、函数体、单例对象中。

与**隐式转换**类似，当一个实例调用了**不存在**或**无法访问**的成员方法，编译器会为之搜索作用域中可访问的隐式类，若隐式类的构造器参数与实例相同且带有实例调用的方法，则自动调用该隐式类的构造器。  
如下代码所示：

```scala
object Main extends App {

	case class Source(num: Int) {
		private def show = print(num)
	}

	implicit class Impl(source: Source) {
		def show = println("Implicit Class")
		def show(num: Int) = println(s"Implicit Class: $num")
	}

	Source(0).show				//调用无法访问的成员方法可能触发隐式转换
	Source(0).show(100)			//调用不存在的方法也能触发隐式转换
}
```

输出结果：

```
Implicit Class
Implicit Class: 100
```



## 并发编程
作为`JVM`平台的编程语言，`Scala`可以直接调用`Java`的并发`API`。  
并发编程是`Scala`的擅长领域，除了`Java`标准库提供的并发API，`Scala`还提供下列并发技术：

- `Scala`标准库中提供了`Future/Promise/Async`库来进行异步编程。
- 基于`Scala`的`Akka`完整实现了`Actor`模型。

### *Scala Future*
`Future`是一组异步操作的抽象，完整包路径为`scala.concurrent.Future`。

构建与启动`Future`
> `Future`为**特质**，没有构造函数，无法直接构建实例。  
> 创建一个`Future`实例需要使用伴生对象中重写的`apply()`方法，声明如下：
>
>	```scala
>	def apply[T](body: =>T)(implicit @deprecatedName('execctx) executor: ExecutionContext): Future[T]
>	```
>
>	- `body`参数为**传名参数**，包含了需要异步执行的代码块。
>	- `T`参数为泛型参数，表示异步执行的代码块最终的返回值类型。
>	- `executor`参数为隐式参数，用于指定异步代码的执行器。`scala.concurrent.ExecutionContext.Implicits.global`提供了默认的执行器。
>
> 构建一个`Future`，基本代码如下：
>
>	```scala
>	import scala.concurrent.Future
>	import scala.concurrent.ExecutionContext.Implicits.global
>
>	val future = Future[XXX] {
>		/* Code you want to excute... */
>	}
>	```
>
> 与传统的并发库设计不同，`Future`并没有提供诸如`start()/run()`之类的方法用于显式开始异步代码块的执行，在完成`Future`实例构建的同时，作为参数的代码块就自动开始异步执行了。

*Callbacks* (异步回调)
> 与传统的并发库设计类似，`Future`采用回调的方式来处理异步操作完成的结果。  
> `Future`实例提供了`onComplete()`成员方法来绑定回调函数，声明如下：
>
>	```scala
>	def onComplete[U](@deprecatedName('func) f: Try[T] => U)(implicit executor: ExecutionContext): Unit
>	```
>
>	- `f`参数为被回调的高阶函数。
>	- `executor`参数作用与上述`apply()`方法中类似。
>
> 被回调的高阶函数类型为`Try[T] => U`，其中抽象类`Try[T]`类似于`Option[T]`，拥有两个样例类子类`Success[T]`和`Failure[T]`，定义如下：
>
>	```scala
>	final case class Success[+T](value: T) extends Try[T] { ... }
>	final case class Failure[+T](exception: Throwable) extends Try[T] { ... }
>	```
>
> 在编写回调函数时，可使用模式匹配语法：
>
>	- 对于**成功**的异步操作，匹配内容是异步操作的返回值。
>	- 对于**失败**的异步操作，匹配内容是导致异步操作失败的异常。
>
> `Future`也提供了`onSuccess()/onFailure()`方法接收偏函数分别处理异步操作成功/失败时的情况，当只需要处理某一类情况时，可以直接使用对应方法。
>
> 一个`Future`实例可以**多次**调用`onComplete()/onSuccess()/onFailure()`来添加多个回调操作，这些回调操作都会被执行，但执行的先后顺序**不确定**。
>
> 回调处理异步操作结果的基本代码如下：
>
>	```scala
>	import scala.util.{Failure, Success}
>
>	future onComplete {
>		case Success(xxx) => ...
>		case Failure(xxx) => ...
>	}
>
>	future onSuccess {
>		re: T => ...
>	}
>
>	future onFailure {
>		case ex => ...
>	}
>	```

同步等待
> 在个别情况下，可能需要等待异步操作执行完毕。
> 等待`Future`纸型完毕可以使用`Await`单例，完整包路径为`scala.concurrent.Await`。
>
> `Await`单例提供了`result()`方法用于同步等待`Future`执行完毕，定义如下：
>
>	```scala
>	def result[T](awaitable: Awaitable[T], atMost: Duration): T
>	```
>
>	- `awaitable`参数为`Awaitable`类型，用于表示一个可等待的操作，`Future`特质为其子类，可支持传入`Future`实例作为参数。
>	- `atMost`参数为同步等待的时间。
>
> 基本用法如下：
>
>	```scala
>	import scala.concurrent.Await
>	import scala.concurrent.duration.Duration
>
>	val result = Await.result(future, Duration.Inf)
>	println(result)
>	...
>	```
>
> `Duration` (时间类型)
>> 时间参数类型为`Duration`，为抽象类，完整路径为`scala.concurrent.duration.Duration`。
>>
>> `Duration`的伴生对象内定义了`apply()`方法，声明如下：
>>
>>	```scala
>>	def apply(length: Long, unit: TimeUnit): FiniteDuration
>>	```
>>
>>	- `length`参数为时间数值。
>>	- `unit`参数为时间单位。
>>
>> 构建的时间对象为`Duration`的子类，有限时间`FiniteDuration`。  
>> `Duration`中有两个成员`Inf`、`MinusInf`分别用来表示**无限大/无限小**的时间。
>>
>> `TimeUnit`类型完整包路径为`java.util.concurrent.TimeUnit`，为枚举类型，包含以下枚举成员：
>>
>>	- `java.util.concurrent.TimeUnit.DAYS` 天
>>	- `java.util.concurrent.TimeUnit.HOURS` 小时
>>	- `java.util.concurrent.TimeUnit.MICROSECONDS` 微秒
>>	- `java.util.concurrent.TimeUnit.MILLISECONDS` 毫秒
>>	- `java.util.concurrent.TimeUnit.MINUTES` 分钟
>>	- `java.util.concurrent.TimeUnit.NANOSECONDS` 纳秒
>>	- `java.util.concurrent.TimeUnit.SECONDS` 秒
>>
>> 在`import scala.concurrent.duration`包中定义了一系列隐式类`DurationInt/DurationLong/DurationDouble`。  
>> 引用对应隐式类即可使用对应的DSL语法来构建时间对象`FiniteDuration`，如：
>>
>>	- `1000 days`被转换为`Duration(1000, java.util.concurrent.TimeUnit.DAYS)`
>>	- `1000 minutes`被转换为`Duration(1000, java.util.concurrent.TimeUnit.SECONDS)`
>>	- ...
>>
>> 诸如此类...  
>> 在`scala.concurrent.duration.DurationConversions`特质中定义了完整的转化语法。

*blocking* (阻塞块)
> `Future`是异步执行的，不会阻塞基础的执行线程。但在某些情况下，阻塞是必要的，需要区别两种形式的执行线程阻塞：
>
>	- 从`Future`内部调用任意代码阻塞线程。
>	- 在`Future`外部等待一个`Future`完成。
>
> 在`Future`外部主动阻塞等待应使用`Await`类，在`Future`内部阻塞则应使用`blocking`方法。  
> `blocking`定义在包对象`scala.concurrent`中，是一个接收**传名参数**的泛型方法，定义如下所示：
>
>	```scala
>	def future[T](body: =>T)(implicit @deprecatedName('execctx) executor: ExecutionContext): Future[T] = Future[T](body)
>	```
>
> `blocking`块的作用是向执行器(`ExecutionContext`)标记可能造成阻塞的代码，并调整执行器的行为。  
> 对于默认的执行器`scala.concurrent.ExecutionContext.Implicits.global`，在`Future`中包含`blocking`块时，会新建线程来执行`Future`而不是等待复用已有的线程。
>
> 如下代码所示：
>
>	```scala
>	import scala.concurrent.Future
>	import scala.concurrent.ExecutionContext.Implicits.global
>
>	object Main extends App {
>
>		for (n <- 0 to 30)
>			Future {
>				println(s"Index: $n Thread Name: ${Thread.currentThread.getName}")
>				Thread.sleep(3000)
>			}
>
>		scala.io.StdIn.readLine()
>	}
>	```
>
> 输出结果：(Scala 2.11.8 && ArchLinux x64)
>
>	```
>	Index: 4 Thread Name: ForkJoinPool-1-worker-5
>	Index: 2 Thread Name: ForkJoinPool-1-worker-9
>	Index: 0 Thread Name: ForkJoinPool-1-worker-13
>	Index: 7 Thread Name: ForkJoinPool-1-worker-15
>	Index: 3 Thread Name: ForkJoinPool-1-worker-7
>	Index: 1 Thread Name: ForkJoinPool-1-worker-11
>	Index: 6 Thread Name: ForkJoinPool-1-worker-3
>	Index: 5 Thread Name: ForkJoinPool-1-worker-1
>	Index: 8 Thread Name: ForkJoinPool-1-worker-11
>	Index: 14 Thread Name: ForkJoinPool-1-worker-15
>	Index: 10 Thread Name: ForkJoinPool-1-worker-9
>	Index: 13 Thread Name: ForkJoinPool-1-worker-13
>	Index: 12 Thread Name: ForkJoinPool-1-worker-1
>	Index: 11 Thread Name: ForkJoinPool-1-worker-3
>	Index: 9 Thread Name: ForkJoinPool-1-worker-7
>	Index: 15 Thread Name: ForkJoinPool-1-worker-5
>	Index: 16 Thread Name: ForkJoinPool-1-worker-11
>	Index: 17 Thread Name: ForkJoinPool-1-worker-15
>	Index: 19 Thread Name: ForkJoinPool-1-worker-13
>	Index: 18 Thread Name: ForkJoinPool-1-worker-9
>	Index: 22 Thread Name: ForkJoinPool-1-worker-7
>	Index: 21 Thread Name: ForkJoinPool-1-worker-1
>	Index: 20 Thread Name: ForkJoinPool-1-worker-3
>	Index: 23 Thread Name: ForkJoinPool-1-worker-5
>	Index: 24 Thread Name: ForkJoinPool-1-worker-11
>	Index: 25 Thread Name: ForkJoinPool-1-worker-15
>	Index: 26 Thread Name: ForkJoinPool-1-worker-13
>	Index: 27 Thread Name: ForkJoinPool-1-worker-9
>	Index: 28 Thread Name: ForkJoinPool-1-worker-7
>	Index: 29 Thread Name: ForkJoinPool-1-worker-1
>	Index: 30 Thread Name: ForkJoinPool-1-worker-3
>	```
>
> 打印执行结果的过程中，输出流出现了几次3秒的停顿。  
> 从结果中不难看出，执行器只开辟了`15`个处理线程，在所有处理线程都处于`sleep`状态时，输出流便停止。
>
> 尝试将`sleep()`函数写在`blocking`中：
>
>	```scala
>	import scala.concurrent.{Future, blocking}
>	import scala.concurrent.ExecutionContext.Implicits.global
>
>	object Main extends App {
>		for (n <- 0 to 30)
>			Future {
>				println(s"Index: $n Thread before blocking: ${Thread.currentThread.getName}")
>				blocking {
>					println(s"Index: $n Blocking: ${Thread.currentThread.getName}")
>					Thread.sleep(3000)
>				}
>				println(s"Index: $n Thread after blocking: ${Thread.currentThread.getName}")
>			}
>
>		scala.io.StdIn.readLine()
>	}
>	```
>
> 输出结果：(Scala 2.11.8 && ArchLinux x64)
>
>	```
>	Index: 6 Thread before blocking: ForkJoinPool-1-worker-1
>	Index: 2 Thread before blocking: ForkJoinPool-1-worker-9
>	Index: 3 Thread before blocking: ForkJoinPool-1-worker-7
>	Index: 1 Thread before blocking: ForkJoinPool-1-worker-11
>	Index: 5 Thread before blocking: ForkJoinPool-1-worker-3
>	Index: 7 Thread before blocking: ForkJoinPool-1-worker-15
>	Index: 0 Thread before blocking: ForkJoinPool-1-worker-13
>	Index: 4 Thread before blocking: ForkJoinPool-1-worker-5
>	Index: 4 Blocking: ForkJoinPool-1-worker-5
>	Index: 7 Blocking: ForkJoinPool-1-worker-15
>	Index: 5 Blocking: ForkJoinPool-1-worker-3
>	Index: 2 Blocking: ForkJoinPool-1-worker-9
>	Index: 8 Thread before blocking: ForkJoinPool-1-worker-23
>	Index: 8 Blocking: ForkJoinPool-1-worker-23
>	Index: 9 Thread before blocking: ForkJoinPool-1-worker-27
>	Index: 1 Blocking: ForkJoinPool-1-worker-11
>	Index: 3 Blocking: ForkJoinPool-1-worker-7
>	Index: 10 Thread before blocking: ForkJoinPool-1-worker-31
>	Index: 9 Blocking: ForkJoinPool-1-worker-27
>	Index: 6 Blocking: ForkJoinPool-1-worker-1
>	Index: 10 Blocking: ForkJoinPool-1-worker-31
>	Index: 0 Blocking: ForkJoinPool-1-worker-13
>	Index: 11 Thread before blocking: ForkJoinPool-1-worker-17
>	Index: 11 Blocking: ForkJoinPool-1-worker-17
>	Index: 12 Thread before blocking: ForkJoinPool-1-worker-21
>	Index: 12 Blocking: ForkJoinPool-1-worker-21
>	Index: 13 Thread before blocking: ForkJoinPool-1-worker-19
>	Index: 13 Blocking: ForkJoinPool-1-worker-19
>	Index: 14 Thread before blocking: ForkJoinPool-1-worker-25
>	Index: 14 Blocking: ForkJoinPool-1-worker-25
>	Index: 15 Thread before blocking: ForkJoinPool-1-worker-29
>	Index: 15 Blocking: ForkJoinPool-1-worker-29
>	Index: 16 Thread before blocking: ForkJoinPool-1-worker-47
>	Index: 16 Blocking: ForkJoinPool-1-worker-47
>	Index: 17 Thread before blocking: ForkJoinPool-1-worker-45
>	Index: 17 Blocking: ForkJoinPool-1-worker-45
>	Index: 18 Thread before blocking: ForkJoinPool-1-worker-59
>	Index: 18 Blocking: ForkJoinPool-1-worker-59
>	Index: 19 Thread before blocking: ForkJoinPool-1-worker-39
>	Index: 19 Blocking: ForkJoinPool-1-worker-39
>	Index: 20 Thread before blocking: ForkJoinPool-1-worker-53
>	Index: 20 Blocking: ForkJoinPool-1-worker-53
>	Index: 21 Thread before blocking: ForkJoinPool-1-worker-37
>	Index: 21 Blocking: ForkJoinPool-1-worker-37
>	Index: 22 Thread before blocking: ForkJoinPool-1-worker-51
>	Index: 22 Blocking: ForkJoinPool-1-worker-51
>	Index: 23 Thread before blocking: ForkJoinPool-1-worker-35
>	Index: 23 Blocking: ForkJoinPool-1-worker-35
>	Index: 24 Thread before blocking: ForkJoinPool-1-worker-49
>	Index: 24 Blocking: ForkJoinPool-1-worker-49
>	Index: 25 Thread before blocking: ForkJoinPool-1-worker-63
>	Index: 25 Blocking: ForkJoinPool-1-worker-63
>	Index: 26 Thread before blocking: ForkJoinPool-1-worker-43
>	Index: 26 Blocking: ForkJoinPool-1-worker-43
>	Index: 27 Thread before blocking: ForkJoinPool-1-worker-57
>	Index: 27 Blocking: ForkJoinPool-1-worker-57
>	Index: 28 Thread before blocking: ForkJoinPool-1-worker-41
>	Index: 28 Blocking: ForkJoinPool-1-worker-41
>	Index: 29 Thread before blocking: ForkJoinPool-1-worker-55
>	Index: 29 Blocking: ForkJoinPool-1-worker-55
>	Index: 30 Thread before blocking: ForkJoinPool-1-worker-33
>	Index: 30 Blocking: ForkJoinPool-1-worker-33
>	Index: 4 Thread after blocking: ForkJoinPool-1-worker-5
>	Index: 7 Thread after blocking: ForkJoinPool-1-worker-15
>	Index: 5 Thread after blocking: ForkJoinPool-1-worker-3
>	Index: 2 Thread after blocking: ForkJoinPool-1-worker-9
>	Index: 8 Thread after blocking: ForkJoinPool-1-worker-23
>	Index: 1 Thread after blocking: ForkJoinPool-1-worker-11
>	Index: 3 Thread after blocking: ForkJoinPool-1-worker-7
>	Index: 9 Thread after blocking: ForkJoinPool-1-worker-27
>	Index: 6 Thread after blocking: ForkJoinPool-1-worker-1
>	Index: 10 Thread after blocking: ForkJoinPool-1-worker-31
>	Index: 0 Thread after blocking: ForkJoinPool-1-worker-13
>	Index: 11 Thread after blocking: ForkJoinPool-1-worker-17
>	Index: 12 Thread after blocking: ForkJoinPool-1-worker-21
>	Index: 13 Thread after blocking: ForkJoinPool-1-worker-19
>	Index: 14 Thread after blocking: ForkJoinPool-1-worker-25
>	Index: 15 Thread after blocking: ForkJoinPool-1-worker-29
>	Index: 16 Thread after blocking: ForkJoinPool-1-worker-47
>	Index: 17 Thread after blocking: ForkJoinPool-1-worker-45
>	Index: 18 Thread after blocking: ForkJoinPool-1-worker-59
>	Index: 19 Thread after blocking: ForkJoinPool-1-worker-39
>	Index: 20 Thread after blocking: ForkJoinPool-1-worker-53
>	Index: 21 Thread after blocking: ForkJoinPool-1-worker-37
>	Index: 22 Thread after blocking: ForkJoinPool-1-worker-51
>	Index: 23 Thread after blocking: ForkJoinPool-1-worker-35
>	Index: 24 Thread after blocking: ForkJoinPool-1-worker-49
>	Index: 25 Thread after blocking: ForkJoinPool-1-worker-63
>	Index: 26 Thread after blocking: ForkJoinPool-1-worker-43
>	Index: 27 Thread after blocking: ForkJoinPool-1-worker-57
>	Index: 28 Thread after blocking: ForkJoinPool-1-worker-41
>	Index: 29 Thread after blocking: ForkJoinPool-1-worker-55
>	Index: 30 Thread after blocking: ForkJoinPool-1-worker-33
>	```
>
> 整个输出过程中，仅有**一次**3秒的停顿。  
> 分析输出结果，可以得知：
>
>	0. 执行器开辟的工作线程的数量明显大于没有`blocking`时的数量(线程数目`> 50`)。即使用`blocking`改变了执行器的线程创建策略。
>	0. 相同`Index`输出的线程名称相同，`blocking`包含的代码、之后的代码并没有运行在独立的线程。即一个独立的`Future`运行在一个线程，**没有**像`C#`中的`async`方法那样被切分到不同的线程执行。

### *Scala Promise*
`Promise`为特质，完整包路径为`scala.concurrent.Promise`。

- `Future`提供了带有**只读占位符**(`read-only placeholder`)的返回值，只有一个异步操作完全结束才能获取其返回值。
- `Promise`则提供了可写的、单一指派(`writable、single-assignment`)的分配容器。

使用`Promise`：

0. `Promise`特质的伴生对象中提供了空参的`apply()`方法用于构建默认的`Promise`实例(`DefaultPromise`类型)。
0. `Promise`实例提供了无参的`future`方法用于获取自身的`Future`实例。
0. `Promise`实例可以通过`success()/failure()`方法标记自身`Future`实例的执行结果，使用`isCompleted`方法判断`Future`实例的执行状态。
0. `Promise`实例的`success()/failure()`方法只能选其一，且只能调用一次。`success()/failure()`方法一旦被调用，自身`Future`实例的执行结果便已确定，不可更改。
0. 多个`Future`可通过`Promise`共享数据。
0. `Promise`能使用`completeWith()`绑定一个其它的`Future`，让自身同被绑定的`Future`拥有相同的执行状态和**执行结果**。

实例，一个`Future`通过使用`Promise`获取另一个`Future`中的执行状态(**不是**执行结束的返回内容)，基本代码如下：

```scala
import scala.concurrent.{ Future, Promise, Await }
import scala.concurrent.duration.Duration

val promise = Promise[XXX]()
val future = promise.future

println(future.isCompleted)

Future {
	/* do something... */
	promise.success(xxx)
	/* do something... */
}

Future {
	/* do something... */
	val result = Await.result(future, Duration.Inf)
	/* use result... */
}
```

### *async/await*
`Scala`也提供了`Async`库用于简化`Future`的使用。

`Async`完整包路径为`scala.async.Async`。  
当前版本(`Scala 2.11.8`)中，`Async`库尚未进入`Scala`标准库。  
对于使用`sbt`的工程，则需要在`build.sbt`配置文件中添加依赖：

```scala
libraryDependencies += "org.scala-lang.modules" %% "scala-async" % "版本号"
```

单例`Async`的定义如下：

```scala
object Async {
	/**
	* Run the block of code `body` asynchronously. `body` may contain calls to `await` when the results of
	* a `Future` are needed; this is translated into non-blocking code.
	*/
	def async[T](body: T)(implicit execContext: ExecutionContext): Future[T] = macro internal.ScalaConcurrentAsync.asyncImpl[T]

	/**
	* Non-blocking await the on result of `awaitable`. This may only be used directly within an enclosing `async` block.
	*
	* Internally, this will register the remainder of the code in enclosing `async` block as a callback
	* in the `onComplete` handler of `awaitable`, and will *not* block a thread.
	*/
	@compileTimeOnly("`await` must be enclosed in an `async` block")
	def await[T](awaitable: Future[T]): T = ??? // No implementation here, as calls to this are translated to `onComplete` by the macro.
}
```

- `async`用法类似`Future`的`apply()`方法，接收传名参数`body`作为异步执行的内容，接收隐式参数`execContext`作为执行器。
- `await`只能用在`async`代码块中，作用类似`Await.result()`方法。

`async`利用了`Scala`的宏机制，`await`本质上是`async`代码块中的一个关键字。
由于宏机制的一些限制，不能将`await`用在循环、异常捕捉代码块以及闭包中。



## *XML* 解析
Scala标准库中内置了XML支持，XML相关类在包`scala.xml`中。

### 节点类型
`Node`是最基础的XML节点类型(抽象类)。  
`NodeSeq`用于记录节点的序列，继承自`Seq[Node]`。

相关类型继承关系图如下所示：

```
Seq[Node]
│ 
NodeSeq
├── Document
└── Node
	 ├── Elem
	 └── SpecialNode
	 		 ├── EnityRef
			 ├── ProcInstr
			 ├── Conment
			 └── Atom
			 	 ├── Text
				 ├── PCData
				 └── Unparsed
```

`Node`类型定义了一系列用于获取节点信息的方法：

- `prefix`成员方法，用于获取**当前节点**的标签**前缀**。
- `child`成员方法(抽象方法)，用于获取**子节点**的**序列**。
- `attributes`成员方法，用于获取**当前节点**的**属性**。
- `label`成员方法(抽象方法)，用于获取**当前节点**的**标签名称**。
- `text`成员方法，用于获取**当前节点**的**文本内容**。

如下所示：

```scala
def prefix: String = null
def child: Seq[Node]
def attributes: MetaData = Null
def label: String
override def text: String = super.text
```

`Node`类型的伴生对象中定义了**提取器**，可以用于提取节点中的**标签名称**、**属性**、**子节点**等内容：

```scala
def unapplySeq(n: Node) = Some((n.label, n.attributes, n.child))
```

`Elem`类型继承于`Node`类型，实现了`Node`类型中的抽象内容。

### 读写 XML 文件
读写XML文件可以使用`XMLLoader`特质以及继承于`XMLLoader[Elem]`的单例对象`XML`。

- `XMLLoader`的实例方法`loadFile()`可以从指定路径加载XML文件进行解析，方法返回由输入XML文件生成的`Elem`节点对象。
- `XML`对象的方法`save()`和`write()`可用于将节点(`Node`类型)写入到文件中。
- `save()`方法接收文件路径(`String`类型)作为参数，大部分参数带有默认值。
- `write()`接收`java.io.Writer`类型作为参数，参数没有默认值。

### 查找节点
`NodeSeq`类提供了`\()`、`\\()`等方法用于节点的查找，继承于`NodeSeq`类的`Node`、`Elem`等类型都可以使用这些方法进行节点查找。

`\()`以及`\\()`方法签名类似，接收节点名称作为参数(`String`类型)，返回节点序列(`NodeSeq`类型)。

如下所示：

```scala
// 返回当前节点下一级子节点中指定名称节点的序列
def \(that: String): NodeSeq
// 返回当前节点所有子节点中指定名称节点的序列
def \\(that: String): NodeSeq
```

- 使用`loadFile()`方法加载XML文件后，返回的`Elem`类型的当前节点为**根节点**。
- 节点查找支持使用**模式匹配**的方式。
- 使用模式匹配方式查找节点时，匹配表达式中的节点标签不能带有属性(不支持此语法)。

### 节点属性
节点属性内容可以直接从节点中获取，也可以通过查找获取属性内容。

使用`\()`、`\\()`方法同样可以进行属性查找，需要在属性名字符串前加上`@`字符表示搜索的内容为**属性**，如`\("@num")`表示查找名称为`num`的属性内容。
在使用`\()`方法查找属性时，查找的的范围**不是**子节点的属性，而是**当前**节点的属性。

`NodeSeq`类型提供了`\@()`方法在**当前**子节点中进行属性查找，直接使用属性名作为参数，无需再添加`@`字符，如下所示：

```scala
// 参数为属性名称
def \@(attributeName: String): String
```

`Node`类型提供了`attribute()`以及`attributes`方法从节点中获取属性，如下所示：

```scala
// 获取带有指定属性的节点
final def attribute(key: String): Option[Seq[Node]]
// 获取所有属性
def attributes: MetaData
```

`attributes`方法返回的类型为`MetaData`。
`MetaData`类型支持遍历操作，定义了`key`、`value`方法用于获取属性的键值，如下所示：

```scala
// 获取指定属性的值
def apply(key: String): Seq[Node]
// 获取当前属性名称
def key: String
// 获取当前属性名称对应的属性值
def value: Seq[Node]
```

### 遍历节点
`Elem`类型的成员字段`child`保存了子节点的序列(`Seq[Node]`类型)，可以通过`for`循环语句或高阶函数进行遍历。

有如下测试XML文件：

```xml
<!-- FileName: Example.xml -->
<Root>
	<Node arg="arg_node1">
		<One>node1</One>
	</Node>
	<Node arg="arg_node2"><Two arg="arg_2">node2</Two></Node>
	<Node arg="arg_node4">
		<Three arg="arg_3">node3</Three>
	</Node>
	<Node arg="arg_node4">
		<Four arg="arg_4">node4_1</Four>
		<Four arg_one="arg_4_1" arg_two="arg_4_2">node4_2</Four>
	</Node>
</Root>
```

代码如下所示：

```scala
import scala.xml._

object Main extends App {

	val xmlFile = XML.loadFile(getClass.getResource("Example.xml").getPath)

	val showChild: Node => Unit = _.child foreach { node => node match {

			// 使用标签匹配，可以将表达式嵌在匹配语句中
			case <One>{text}</One> => println(s"case <One>{text}</One>: $text")

			// 标签匹配支持多级嵌套标签，不支持在标签中直接添加属性
			case <Node><Two>{text}</Two></Node> =>
				println(s"case <Node><Two>{text}</Two></Node>: $text")

			// 匹配多级标签需要节点内部不换行
			case <Node><Three>{text}</Three></Node> =>
				println(s"case <Node><Three>{text}</Three></Node>: $text")

			// 使用 @ 操作符给匹配的节点标记变量名称(n 为 Node 类型)
			case n @ <Three>{_}</Three> =>
				println(s"case n @ <Three>{_}</Three>, n text: ${n.text}, n type: ${n.getClass}")

			// 遍历属性
			case n @ <Four>{_}</Four> if n \@ "arg_one" == "arg_4_1" =>
				println(s"case n @ <Four>{_}</Four>, n text: ${n.text}, n type: ${n.getClass}, n.attributes: ")
				n.attributes foreach { attr =>
					println(s"attribute name: ${attr.key} attribute value: ${attr.value.text}")
				}

			// 使用 @ 操作符给节点内容标记变量名称(n 为 Text 类型)
			case <Four>{n @ _}</Four> =>
				println(s"case <Four>{n @ _}</Four>, n text: ${n.text}, n type: ${n.getClass}")

			/*
			匹配其它类型节点，注意不能写成：
				case _ if node.child.length > 0 => ... 或 case _ if node.child.nonEmpty => ...
				(空指针不能调用方法)
			*/
			case _ if node.child != null => showChild(node)

		}
	}

	showChild(xmlFile)
}
```

输出结果：

```
case <One>{text}</One>: node1
case <Node><Two>{text}</Two></Node>: node2
case n @ <Three>{_}</Three>, n text: node3, n type: class scala.xml.Elem
case <Four>{n @ _}</Four>, n text: node4_1, n type: class scala.xml.Text
case n @ <Four>{_}</Four>, n text: node4_2, n type: class scala.xml.Elem, n.attributes:
attribute name: arg_two attribute value: arg_4_2
attribute name: arg_one attribute value: arg_4_1
```

### 创建 XML
可以直接将代码嵌入`XML`语句中：

```scala
scala> val str = "Test"
str: String = Test
scala> val node0 = <li>{ str }</li>				//xml节点内容可以插入变量,使用花括号区分表达式与xml本身内容
node0: scala.xml.Elem = <li>Test</li>
scala> val node1 = <li name={ str }>test</li>	//xml属性中插入变量
node1: scala.xml.Elem = <li name="Test">test</li>
```

可以将复杂的表达式在XML语句中进行**多重嵌套**：

```scala
scala> val node3 = <ul>{ for (i <- 1 to 3) yield <li>{ i }</li> }</ul>
node3: scala.xml.Elem = <ul><li>1</li><li>2</li><li>3</li></ul>
```

在Scala中，节点是**不可变**的，拼接节点的正确方式是使用`Elem`类型的`cospy()`方法，并在复制时重新设定`child`参数。

`copy()`方法的定义如下所示：

```scala
def copy(
	prefix: String = this.prefix,
	label: String = this.label,
	attributes: MetaData = this.attributes,
	scope: NamespaceBinding = this.scope,
	minimizeEmpty: Boolean = this.minimizeEmpty,
	child: Seq[Node] = this.child.toSeq): Elem = Elem(prefix, label, attributes, scope, minimizeEmpty, child: _*)
```

使用`copy()`方法拼接节点如下所示：

```scala
//使用具名参数指定子节点内容
scala> node3.copy(child = node0 ++ node1)
res0: scala.xml.Elem = <ul><li>Test</li><li name="Test">test</li></ul>

//保留原节点的内容进行拼接
scala> node3.copy(child = node3.child ++ node0 ++ node1)
res1: scala.xml.Elem = <ul><li>1</li><li>2</li><li>3</li><li>Test</li><li name="Test">test</li></ul>

//创建新节点时也可以设定其它属性，如标签名、标签前缀等
scala> node3.copy(child = node0 ++ node1, prefix = "Test", label = "test")
res2: scala.xml.Elem = <Test:test><li>Test</li><li name="Test">test</li></Test:test>
```