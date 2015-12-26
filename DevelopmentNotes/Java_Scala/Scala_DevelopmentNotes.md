[TOC]

##Scala开发环境
在**Linux/Unix**环境下，无需额外的Scala配置，只需从对应发行版的包管理器中直接安装Scala开发包即可。
在**Windows**环境下，需要新建环境变量`SCALA_HOME`，环境变量的值即为Scala的安装目录，然后将`%SCALA_HOME%\bin`加入**PATH**环境变量中。

###让VIM支持Scala语法高亮
vim默认不支持Scala的语法高亮，可以使用**Derek Wyatt**开发的`vim-scala`插件，代码托管在**GitHub**上，项目主页是：
`https://github.com/derekwyatt/vim-scala`
可以使用**Vundle**来安装此插件，在配置文件`.vimrc`中添加：

```vim
Plugin 'derekwyatt/vim-scala'
```

###让Eclipse支持Scala项目
安装`Scala IDE`插件即可。

###编译/执行Scala代码
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

###使用Scala解释器
在命令行中输入无参数的`scala`指令即可进入交互式的Scala解释器。
常用的Scala解释器**指令**：

```scala
scala> :quit				//退出解释器
scala> :reset				//重置解释器的状态，会清空已保存的变量、类、方法等所有内容
```

Scala解释器与Python解释器类似，可以直接将代码一行行地输入解释器，解释器会执行代码并给出反馈，对初学者而言是一个练习的好方法。



##Scala基本语言特性
相比`Java``C++`等语言，`Scala`融合了`OOP``FP`等编程范式，同时语法上更**灵活**。

###语法基础(概览)
- Scala语言中不强制要求分号，可以依行断句，只有一行带有多个语句时才要求分号隔开。
- 使用`var``val`定义`变量``常量`，类型可以由编译器推导，也可以显式指定。定义变量时甚至可以省略`var``val`关键字，无关键字时定义的变量默认即为`val`，在定义变量的同时就需要初始化变量，否则报错(抽象类中除外)。
- 使用`def`关键字定义**方法**，`var``val`定义**函数**，需要注意的是使用`var`定义的函数是可以更改实现的，但`def`定义的方法一经定义实现就**不可改变**。
- 没有**自增/自减**操作符。
- 所有类型皆为对象，基础类型如`Int``Double`等都是类，函数/方法返回值的空类型为`Unit`，相当于Java/C++中的`void`。
- 没有原生enum类型，应继承枚举助手类`Enumeration`。
- 不提供类似Java/C++中的**三目运算符**，但`if`语句表达式带有**返回值**，可以实现类似效果。
- 访问类成员权限默认为`public`，因而没有`public`关键字，但有`private`和`protected`关键字，作用与Java大致相同，但支持**更细粒度**的权限控制。
- 可以使用操作符作为函数名，达到类似C++/C#中操作符重载的效果。
- 类的成员变量可以与方法名称**相同**。

###Hello World
创建文件`Test.scala`，输入以下代码：

```scala
object Test {
	def main(args: Array[String]): Unit		//带有等号的方法可以省略返回值类型由编译器进行推导
		= println("Hello World!")
}
```

与Java类似，Scala也是从主方法`main`中开始执行整个程序，不过main方法并不定义在类中，而是定义在**单例对象**中(使用object关键字创建单例对象)。
将主方法写在class中能够通过编译，但生成的字节码文件在执行时会出错。
也可以不手动定义main方法而去让伴生对象继承`App`特质，即可直接执行代码语句，例如：

```scala
object Test extends App {
	println("Hello World!")
}
```

单例对象的名称可以与源码文件的文件名不同。

###方法(Method)
与Java不同，Scala中同时支持`函数`与`方法`(Java只有方法而没有真正意义上的"函数"，只有与"函数"类似的"静态方法")。
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

无参方法与空参方法只能存在一个，但二者在使用方式上略有不同，无参方法在调用时只能直接使用方法名，在方法名后加上括号调用就会出错；但空参方法既可以使用带有括号的方法调用方式，也可以省略括号，例如：

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
在Scala中，方法中参数允许带有**默认值**：

```scala
scala> var num = 100
num: Int = 100
scala> def setNum(p: Int = 0) { num = p }		//方法/函数的参数不能由默认值进行类型推导，即使给参数写明了默认值，也依然需要显式指明类型
setNum: (p: Int)Unit
scala> setNum()				//对于有参数的方法，即使参数带有默认值使得参数表可以为空但在调用时依然不能省略括号，否则报错
scala> println(num)
0							//输出0
```

需要注意的是，在Scala中，赋值表达式的值为`Unit`，而不是类似Java/C++中的以被赋值的变量类型为表达式的值。例如：
pre
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

###函数(Function)
在Scala中函数使用`var``val`关键字定义，即函数是一个存储了函数对象的字段。
一个典型的函数定义如下：

```scala
var functionName: FuncType = 符合签名的方法/函数/Lambda
```

需要注意的是，函数**不允许**省略参数，因为函数名做为表达式时的语义为函数名所代表的函数内容而非函数调用。空参函数的括号不可省略，直接使用函数名并不代表调用空参函数，比如：

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

与**C++**中的Lambda用法类似：

```cpp
#include <iostream>

using namespace std;

int main(void)
{
	([](const string& str) { cout << str << endl; })("Hello World!");
}
```

然而在**C#**中，Lambda需要先创建对象才能使用，同样的语句需要写成：

```csharp
using System;

class Test
{
	static void Main(string[] args)
		=> new Action<string>(str => Console.WriteLine(str))("Hello World!");
}
```

###传名参数(By-name Parameter)
当一个方法接收的**参数**为**空**时，该参数即为**传名参数(By-name Parameter)**，如下所示：

```scala
def func(arg: => T) ...
```

可以使用传名参数可以接收任意数量的代码，如下所示：

```scala
object Main extends App {

	def show(args: => Unit) = args

	//单行语句可直接作为参数
	show(println("123"))

	//多行语句可放在大括号中
	show {
		println("456")
		println("789")
	}
}
```

运行结果：
123
456
789

###函数作为参数
Scala为函数式编程语言，在Scala中函数对象可以直接作为参数传递。
当函数作为参数存在时，传名参数与普通的空参函数参数定义**不能**同时存在，如下定义只能存在一个：

```scala
def func(arg: () => T) = arg
def func(arg: => T) = arg
var func: (() => T) => T = (arg: () => T) => arg
```

在接收参数时，空参函数参数只能接收同样空参的函数，即`() =>`不能被省略，而传名参数则无此限制。



##类型系统
在Scala中，所有的类型**皆为对象**，所有类型都从根类`Any`继承，`Any`有`AnyVal`和`AnyRef`两个子类。
在Scala中，基础类型如`Int``Float``Double``Unit`等全部从`AnyVal`类中派生，因而可以直接在泛型中直接使用这些类作为类型参数。
同时，Scala中提供了`隐式转换(ImplicitConversion)`来保证`Int``Float``Double`等类型之间可以**自动进行转换**。
基础类型与字符串(String)等类型之间的转换也由类提供的成员函数进行，如将数值与字符串相互转换可以使用如下代码：

```scala
var str = 100.toString
var num = str.toInt
```

在Scala中，所有的基础类型之外的引用类型派生自类`AnyRef`。

###底类型(Bottom)
与Java不同，Scala中存在底类型(bottom)。底类型包括`Nothing`和`Null`。

- `Nothing`是所有类型`Any`的子类型，定义为`final trait Nothing extends Any`。
- `Nothing`特质没有实例。
- `Null`是所有引用类型`AnyRef`的子类型，定义为`final trait Null extends AnyRef`。
- `Null`特质拥有唯一实例`null`(类似于Java中`null`的作用)。

###可空类型
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
123
No Value



##Scala中的OOP
Scala是一门同时具有函数式与面向对象特性的多重范式的语言，除了具有函数式特性外，对**OOP**也有着完整的支持。

###构造器(Constructor)
在Scala中构造方法的作用与Java类似，用于在创建类实例的同时对指定的成员进行初始化。
在语法上，Scala中类可以拥有一个**主构造器(primary constructor)**和任意个**辅助构造器(auxiliary constructor)**。
主构造器的参数定义紧跟在类名之后，辅助构造器定义在类体中，使用this关键字，在辅助构造器中最终必须调用主构造器。
调用父类的主构造器必须在主构造器中，写在父类类名之后。
需要注意的是，主构造器的参数将成为类的成员，而辅助构造器中的参数则与普通函数参数类似，仅在构造器代码段内部生效。
如下代码所示：

```scala
//定义主构造器
class Constructor(a: Int = 1, var b: Double = 2.0) {		//构造器参数紧跟在类名之后，构造器中的参数可以带有默认值
	//在构造器中创建了两个字段，如果没有显式使用var/val关键字创建字段，则创建的字段是当前实例私有切不可变的(private[this] val)

	//定义辅助构造器，使用this关键字
	def this() = this(2, 3.0)		//辅助构造器的函数体中必须最终调用主构造器，辅助构造器即使没有参数也必须也必须带括号
}

//只有主构造器能够调用父类构造器
class ExtendConstructor(a: Int = 2, c: Double = 4.0) extends Constructor(a, c) {
	def this() {
		//a = 100					//对成员字段进行操作要在主构造器调用之后，放在this()之前会报错
		this(2, 4.0)
		//super(2, 4.0)				//在Scala中没有这种用法，父类的构造函数只能由主构造器调用
	}
}
```

###访问权限
Scala中的成员默认访问权限即为公有，因而Scala中没有`public`关键字。
Scala中的保护成员和私有成员使用关键字`protected``private`，作用大体上与Java相同，但Scala在访问权限上支持**更细粒度**的划分。
在Scala中，访问级别关键字之后可以使用中括号带上更具体的访问区域限制，可以是当前定义的类、当前定义类的外部类(若存在外部类)、包名(某个包内的所有类实例可访问)或是`this`关键字(仅当前实例可访问)。
访问权限关键字之后若不写明具体的访问限制区域，则默认限制为当前类可访问(与Java行为基本一致，但Java中的保护成员包内可见)。
如下代码所示：

```scala
package TestCode ｛

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

###字段
Scala类中的字段不仅仅是定义了一个成员变量，编译器还可能会自动为字段生成与字段同名的`getter`和`setter`方法。

- `var`关键字定义的字段编译器会同时为其生成`setter`和`getter`方法，若对象的的权限为私有/保护，则对应生成的`setter`和`getter`方法同样为**私有/保护**权限。
- `val`关键字定义的字段为**只读**字断，编译器不会为其合成`setter`方法。
- 若访问权限为`private[this]`，则编译器不会为其合成`setter`和`getter`方法(`protected[this]`正常生成`setter``getter`方法)。
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

在Scala中，字段名称可以与方法名称**相同**，默认情况下，合成的`setter``getter`方法就与字段同名，手动在代码中创建与`setter``getter`签名相同的方法会导致编译错误，但在访问权限为`private[this]`时编译器不合成默认的`getter``setter`方法时可以手动定义`setter``getter`方法。
需要注意的是，在实际编码过程中，虽然给`private[this]`的字段定义同名的`setter``getter`方法不会报错，但实际调用过程中会提示错误(如上例子中给num字段赋值回得到错误**reassignment to val**，因此不要手动给字段定义同名的`setter``getter`方法)。
此外，由于字段名称可以与方法名称相同，因而即使编译器生成了`setter``getter`方法，编码者依然可以使用字段名称定义其它签名的重载函数。

###多态
####*重写*
在Scala中，默认情况下，子类的并不会重写父类的同名方法，而是需要显式地在方法定义前加上`override`关键字才会发生重写行为。
Scala中的重写遵循以下规则：

- def只能重写另一个def。
- var只能重写另一个抽象的var(即只有定义没有实现)。
- val可以重写另一个val以及不带有参数的def。

####*重载*
Scala支持函数重载，并且可以使用**操作符**作为函数名，使用操作符作为函数名可以达到类似**C++**中**操作符重载**的效果。

###伴生对象
在Scala中没有`static`关键字，也没有**静态成员**的概念，Scala使用**单例对象**来达到近似静态成员的作用。
每一个类可以拥有一个同名的**伴生对象**(单例)，伴生对象使用object关键字定义，且一个类和其伴生对象的定义必须写在同一个文件中。

###apply()/update()方法
在Scala中，允许使用函数风格进行一些对象操作。
假设有一个**类实例a**，使用：

```scala
a(arg1, arg2, arg3, ...)
```

此表达式等价于：

```scala
a.apply(arg1, arg2, arg3, ...)
```

同样的，使用：

```scala
a(arg1, arg2, arg3, ...) = value
```

等价于：

```scala
a.update(arg1, arg2, arg3, ..., value)
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
1 2
90 180
1000 180

###提取器
在Scala中，还提供了被称为**提取器**的`unapply()`方法。
`unapply()`方法则与`apply()`方法相反，可以从对象中提取出需要的数据(在实际使用过程中，可以从任意的目标里提取数据)。
`unapply()`方法返回值必须为`Option`及其子类，单一返回值使用`Option[T]`，多个返回值可以包含在元组中`Option[(T1, T2, T3, ...)]`。
`unapply()`方法虽然也可以定义在类中，但一般在伴生对象中使用(在类中定义没有合适的语法使用)。
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

class Unapply(var num1: Int, var num2: Int) {
}
```

输出结果：
1
100 200

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
Case Nothing
abc cde
abc cde efg

###特质(trait)
Scala中的`trait`特质对应Java中的`interface`接口，但相比Java中的接口，Scala中的特质除了没有默认构造器、不能被直接实例化之外，拥有绝大部分类的特性。
Scala中的`trait`可以拥有构造器(非默认)，成员变量以及成员方法，成员方法也可以带有方法的实现，并且`trait`中的成员同样可以设置访问权限。

####*混入(mixin)*

- Scala不支持**多重继承**，一个类只能拥有一个父类，但可以**混入(mixin)**多个特质。
- Scala中采用的**混入(mixin)**机制相比传统的单根继承，保留了多重继承的大部分优点。
- 使用`with`关键字混入特质，一个类中混入多个特质时，会将第一个扩展的特质的父类作为自身的父类，同时，后续混入的特质都必须是从该父类派生。
- 若同时继承类并混入特质，需要将继承的类写在`extends`关键字的后面，`with`只能混入**特质**，不能混入**类**。

如下所示：

```scala
class BaseA {
}

class BaseB {
}

trait TraitA extends BaseA {
}

trait TraitB extends BaseB {
}

/* 编译报错，提示：
 * superclass BaseA
 * is not a subclass of the superclass BaseB
 * of the mixin trait TraitB
 */
class TestExtend extends TraitA with TraitB {
}

/* 编译报错，提示：
 * class BaseA needs to be a trait to be mixed in
 */
class ExtendClass extends TraitA with BaseA {
}
```

`TestExtend`类中，特质`TraitA`的父类`BaseA`并不是特质`TraitB`父类`BaseB`的父类，而Scala中一个类只能拥有一个父类，因而无法通过编译。
`ExtendClass`类中，应该继承`BaseA`后混入特质`TraitA`，`with`关键字之后的必需是特质而不能是类名。

####*重写冲突的方法与字段*
与Java8中相同，混入机制同样需要解决富接口带来的成员冲突问题，当一个类的父类与后续混入的特质中带有相同名称的字段或相同签名的方法时，需要在子类重写这些冲突的内容。
如下所示：

```scala
class BaseA {
	def get = 123
}

trait TraitA {
	def get = 456
}

trait TraitB {
	def get = 789
}

class TestExtend extends BaseA with TraitA with TraitB {
	override def get = 77		//对于冲突的内容，必需显式重写
}
```

####*混入顺序*
对于混入的内容，按照以下顺序进行构造：

- 首先构造父类。
- 按照特质出现的顺序从左往右依次构造特质。
- 在一个特质中，若该特质存在父特质，则先构造父特质。若多个特质拥有相同的父特质，该父特质不会被重复构造。
- 最后构造子类。

Scala的混入机制是`线性化`的，对于冲突的内容，构造中的后一个实现会顶替前一个。
线性化顺序与构造顺序`相反`，对于同名字段的内容，最终保留的是最右端的类或特质的实现。
如下所示：

```scala
class BaseA {
	def get = 123
}

trait TraitA {
	def get = 456
}

trait TraitB {
	def get = 789
}

trait TraitC extends TraitA {
	override def get = 111
}

class TestExtend extends BaseA with TraitA with TraitC {
	override def get = super.get				//使用父类的实现时不需要显式指定到底是哪一个，编译器会自动按照线性化顺序选择最后的实现，即TraitC中的实现，即返回111
	//override def get = super[BaseA].get		//也可以使用继承自其它特质或类的实现
	//override def get = super[TraitB].get		//错误，必需使用直接混入的类或特质，不能使用继承层级中更远的类或特质
}
```

###复制类实例
Scala与Java类似，类实例赋值仅仅是复制了一个引用，实例所指向的内存区域并未被复制。
若需要真正复制一个对象，需要调用对象的`clone()`方法。
`clone()`方法定义在`Object`类中，但由于是`protected`成员，不可直接调用，若需要自行实现类的复制功能，则需要实现`Cloneable`接口。
例如：

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
对于`AnyVal`子类如`Int``Double`等类型，没有提供重载的`clone()`方法，但这些类型默认即为值复制，无需额外的操作。
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

###使用匿名类初始化
在Scala中，创建类实例的**同时**可以直接对类的成员变量进行初始化。
如下代码所示：

```scala
object Init extends App {
	var num = new Num {
		num = 100
		name = "Num"
	}		//相当于创建了一个匿名类，然后向上转型到类Num上
	println(num.name + " " + num.num)		//正常输出了初始化的值
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
Num 100



##枚举(Enumerate)
在Scala中，没有语言级别的枚举类型，枚举的功能可以通过**继承**枚举类`Enumeration`实现。

###继承枚举类
继承枚举类`Enumeration`可以在成员中使用无参方法`Value`给每个枚举成员赋值。
默认的Value方法会按变量名生成枚举名和并从0开始生成枚举ID，若需要手动设定枚举的名称喝枚举ID则可以使用Value方法的重载`Value(id: Int, name: Strig)`。
如下代码所示：

```scala
object Color extends Enumeration {
	var red, green, blue = Value

	/*
	* 相当于分别初始化：
	* var red = Value
	* var green = Value
	* var blue = Value
	*/

	//手动使用Value(id: Int, name: String)方法手动进行id和name的设置
	var white = Value(100, "White")
	var black = Value(200, "Black")
	//使用重载有參版本的Value(id: Int, name: String)不能采用自动赋值的方式，会编译报错
}

object TestEnumeration extends App {
	println(Color.red.toString + ":" + Color.red.id + " " + Color.green + ":"
		+ Color.green.id + " " + Color.blue + ":" + Color.blue.id)
	println(Color.white + ":" + Color.white.id + " " + Color.black + ":" + Color.black.id)
}
```

输出结果：
red:0 green:1 blue:2
White:100 Black:200



##数组
Scala中数组的概念与Java中基本类似。

###定长数组
在Scala中定长数组使用Array[T]进行表示，定长数组与Java中概念类似。
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

###变长数组
在Scala中，变长数组使用`ArrayBuffer[T]`进行表示，`ArrayBuffer`不在默认导入的包路径中，而是位于`scala.collection.mutable.ArrayBuffer`。
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

需要注意的是，`+=``-=`只是**方法名**并不是**运算符**，因此，以下的写法会**报错**：

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



##容器
Scala的容器分为`元组(Tuple)``序列(Seq)``集合(Set)`和`映射(Map)`四大类。

###元组(Tuple)
元组是最简单的容器，无需额外的类型名称，直接使用`(T1, T2, T3)`就可以构建出一个元祖。如下所示：

```scala
scala> var tuple = (1, 2, 3)
tuple: (Int, Int, Int) = (1,2,3)
```

元组中允许包含**重复**的值，也允许不同类型的值，但元组一经创建，内容便不可改变。
元组可以通过`元组对象._索引号`的形式访问，不过元组是从**1**开始而非0，如下所示：

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
1 2 3

需要注意的是，元组**不能**够使用for循环进行遍历。

###列表(List)与可变列表(ListBuffer)
在Scala中，`List[T]`类型的完整包路径为`scala.collection.immmutable.List`。
List为**不可变对象**，可以使用for循环进行遍历。
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

只不过，若列表中存储的若是相同的类型，则编译器会将`List[T]`推导为具体的类型，若列表中成员类型各不相同，则编译器会使用所有类型的基类`Any`作为泛型类型及`List[Any]`。

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

在Scala中，同样支持可变列表类型。
可变列表`scala.collection.mutable.LinkedList`在现在的版本中(2.11.7)已被标记为废弃的。
当前版本可以使用`scala.collection.mutable.ListBuffer`为可变列表。
不可变列表`List`不支持`+=`和`-=`运算，但`ListBuffer`类型支持。
`ListBuffer[T]`类的常规操作如下所示：

```scala
object TestList extends App {
	import scala.collection.mutable._
	val show: ListBuffer[Any] => Unit = for (s <- _) print(s"$s ")
	var listBuffer = ListBuffer(1, "str", 2.0)
	listBuffer remove 0					//移除指定索引位置的值
	show(listBuffer)
	println
	listBuffer += "num"					//添加新值
	show(listBuffer)
	println
	listBuffer update (2, "new")		//改变指定位置的值
	show(listBuffer)
}
```

输出结果：
str 2.0
str 2.0 num
str 2.0 new

###集合(Set)
`Set[T]`完整包路径为`scala.collection.immutable.Set`。
集合同样允许任意类型的元素，但集合中不能包含重复的元素。
在使用`Set`类的`apply()`方法构建集合时，重复的元素会被忽略，如下所示：

```scala
scala> var set = Set(1, 1, 's', "str")
set: scala.collection.immutable.Set[Any] = Set(1, s, str)		//重复的元素"1"被忽略了
```

`Set`可以使用`+``-`操作符来增加或是减少元素并返回新的集合。
使用`+``-`操作符会返回新的集合，但原集合内的值不会发生改变，如下所示：

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

与动态数组`ArrayBuffer`类似，集合可以使用`+=``-=`来增加或减少内部的元素：

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

使用`find()`方法可以传入一个高阶函数`T => Boolean`自定义规则进行查找，`find()`方法返回`Option[T]`，找到一个符合要求的元素立即返回`Some[T]`，找不到则返回`None`，如下所示：

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
`scala.collection.mutable.LinkedHashSet`链式哈希集，依照插入的顺序排列
`scala.collection.immutable.SortedSet`红黑树实现的排序集

###映射(Map)
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
但这些操作不会改变原本Map保存的内容：

```scala
scala> map updated (1, "0")
res20: scala.collection.immutable.Map[Int,String] = Map(1 -> 0, 2 -> 2, 3 -> 3)
scala> map + (4 -> "4")
res21: scala.collection.immutable.Map[Int,String] = Map(1 -> 1, 2 -> 2, 3 -> 3, 4 -> 4)
scala> map - 1
res22: scala.collection.immutable.Map[Int,String] = Map(2 -> 2, 3 -> 3)
scala> map									//更改的结果作为返回值输出，原本的Map值没有任何改变
res23: scala.collection.immutable.Map[Int,String] = Map(1 -> 1, 2 -> 2, 3 -> 3)
```

与`Set``ListBuffer`等类似，`Map`也支持`+=``-=`操作符。
`Map`使用`+=`向自身添加对偶，使用`-=`从自身移除指定key对应的对偶。



##生成器(Generators)
Scala中同样提供了`yield`关键字，支持生成器语法。
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

###使用高阶函数替代生成器
Scala中可以使用高阶函数，以函数式风格实现类似`yield`的效果。

```scala
//从1到5的数中找出偶数，并将数值翻倍

//使用命令式编程风格，使用守卫和生成器
scala> for (i <- 1 to 5 if i % 2 == 0) yield i * 2
res13: scala.collection.immutable.IndexedSeq[Int] = Vector(4, 8)

//使用函数式编程风格，使用高阶函数
scala> 1 to 5 filter (_ % 2 == 0) map (_ * 2)
res15: scala.collection.immutable.IndexedSeq[Int] = Vector(4, 8)
```



##包(Package)与导入(Import)
Scala中的包用法基本与Java类似，但在Java的基础上扩充了更多的功能。
与Java不同，Scala中使用`_`符号代替`*`，表示导入该路径下的所有包和成员。

###扩展用法
Scala中可以在一个语句中导入包内的**多个**指定的类：

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

Scala中的`import`带有类似Java1.6中的`static import`特性：

```scala
import java.lang.Math.abs		//导入Math类中的静态方法abs
```

在Scala中，包引入了名称相同的类不会发生冲突，而是后引入的类**覆盖**之前引入的类。
在Scala中，`import`语句可以出现在**任意位置**，不必总是放在文件的顶部，`import`语句的作用域直到该语句块结束。

###默认包
默认情况下，Scala会导入以下几个包路径：

```scala
import java.lang._
import scala._
import Predef._
```

有些Scala包中的类名与Java包中的类名相同，但由于Scala包的引入语句在后，因此，例如`Scala.StringBuiler`类会覆盖`Java.lang.StringBuilder`。

###包对象
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



##隐式转换与隐式参数
隐式转换在构建类库时是一个强大的工具。
使用隐式转换特性需要在编译时添加`-language:implicitConversions`选项。

###隐式转换
Scala是**强类型**语言，不同类型之间的变量默认**不会**自动进行转换。
如果需要类型之间的自动转换，需要使用`implicit`自定义隐式转换。
隐式转换可以定义在当前类中或是伴生对象中，只要需要进行转换时能被访问到即可。
当传入参数的类型与函数需要的类型不同时，编译器便会查找是否有合适的隐式转换，如下所示：

```scala
class Implicit(val num: Int)

object Implicit {
	implicit def implToInt(impl: Implicit) = impl.num
}

object Main extends App {

	implicit def implToStr(impl: Implicit) = impl.num.toString

	def showNum(num: Int) = println(num)
	def showStr(str: String) = println(str)

	showNum(new Implicit(100))
	showStr(new Implicit(200))
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
	impl1 show (impl1)			//可以通过将实例隐式转换为Impl2类型来满足方法调用，但编译器实际执行的操作是将参数隐式转换成了Impl2类型
}
```

输出结果：
300
100

Scala类库中大量使用了隐式转换特性，如`String`类型本身没有`toInt/toDouble`之类的成员方法，在调用这些方法时，`String`被隐式转换成定义了这些方法的`StringLike`类型来执行这些操作。

###隐式参数
函数和方法的参数前可以添加关键字`implicit`来将一个参数标记为**隐式参数**，当调用方法时没有对隐式参数赋值，则编译器便会为隐式参数寻找匹配的隐式值。
变量前可以通过添加`implicit`关键字成为隐式值。
如下所示：

```scala
class Implicit(implicit var num1: Int, implicit var num2: Double)

object Implicit {
	implicit var impl = 200.0	//隐式值可以定义在伴生对象中
}

object Main extends App {
	implicit var num = 100		//隐式值需要当前作用域内可见
	import Implicit._			//不在当前作用域中的隐式值需要显式导入
	var impl = new Implicit
	var num1 = impl.num1
	var num2 = impl.num2
	println(s"$num1 $num2")
}
```

输出结果：
100 200.0