<!-- TOC -->

- [*Scala* 开发环境](#scala-开发环境)
	- [使用 *Vim*](#使用-vim)
	- [使用 *Eclipse*](#使用-eclipse)
	- [使用 *IDEA*](#使用-idea)
	- [*Scala* 编译工具](#scala-编译工具)
	- [反编译](#反编译)
	- [*Scala REPL*](#scala-repl)
- [Hello World](#hello-world)
- [*Method* (方法)](#method-方法)
	- [方法返回值](#方法返回值)
	- [空参数方法与无参数方法](#空参数方法与无参数方法)
	- [参数默认值](#参数默认值)
- [*Function* (函数)](#function-函数)
	- [函数组合](#函数组合)
	- [*Partial Function* (偏函数)](#partial-function-偏函数)
	- [*Partial Applied Function* (部分应用函数)](#partial-applied-function-部分应用函数)
- [块表达式](#块表达式)
	- [赋值表达式](#赋值表达式)
- [*OOP*](#oop)
	- [访问权限](#访问权限)
	- [字段](#字段)
	- [*Constructor* (构造器)](#constructor-构造器)
	- [多态](#多态)
	- [复制类实例](#复制类实例)
	- [匿名类初始化](#匿名类初始化)
- [*Singleton Objects* (单例对象)](#singleton-objects-单例对象)
	- [单例类型](#单例类型)
	- [初始化](#初始化)
	- [*Companions* (伴生对象)](#companions-伴生对象)
- [*apply()/update()* 方法](#applyupdate-方法)
	- [无参 *apply* 方法](#无参-apply-方法)
- [*unapply()/unapplySeq()* 方法](#unapplyunapplyseq-方法)
- [*Trait* (特质)](#trait-特质)
	- [*Mixin* (混入)](#mixin-混入)
	- [重写冲突方法、字段](#重写冲突方法字段)
	- [构造顺序](#构造顺序)
	- [线性化顺序](#线性化顺序)
	- [线性化与 *override*](#线性化与-override)
	- [线性化与类型关系](#线性化与类型关系)
	- [线性化与泛型](#线性化与泛型)
- [*Case Class* (样例类)](#case-class-样例类)
	- [避免重定义样例类自动生成的方法](#避免重定义样例类自动生成的方法)
- [类型](#类型)
	- [基础类型](#基础类型)
	- [*Bottom* (底类型)](#bottom-底类型)
	- [*Option* (可空类型)](#option-可空类型)
- [类型系统](#类型系统)
	- [类型参数](#类型参数)
	- [类型约束](#类型约束)
	- [*View Bounds* (视图界定)](#view-bounds-视图界定)
	- [*Content Bounds*](#content-bounds)
	- [*Variances* (型变)](#variances-型变)
	- [*Higer Kinded Type* (高阶类型)](#higer-kinded-type-高阶类型)
- [*continue* 与 *break*](#continue-与-break)
- [*Pattern Matching* (模式匹配)](#pattern-matching-模式匹配)
	- [简单匹配](#简单匹配)
	- [类型匹配](#类型匹配)
	- [解构](#解构)
- [*sealed* 和 *final* 关键字](#sealed-和-final-关键字)
	- [*sealed* 用于模式匹配](#sealed-用于模式匹配)
- [格式化输出](#格式化输出)
	- [*StringLike.format()* 格式化输出](#stringlikeformat-格式化输出)
	- [s字符串插值器](#s字符串插值器)
	- [f字符串插值器](#f字符串插值器)
	- [raw字符串插值器](#raw字符串插值器)
- [终端输入](#终端输入)
- [*Enumerate* (枚举)](#enumerate-枚举)
	- [继承枚举类](#继承枚举类)
	- [访问枚举内容](#访问枚举内容)
	- [调用枚举类型](#调用枚举类型)
	- [限定枚举类型](#限定枚举类型)
- [基础数据结构](#基础数据结构)
	- [定长数组](#定长数组)
	- [*Tuple* (元组)](#tuple-元组)
- [容器](#容器)
	- [容器可变性](#容器可变性)
	- [*List* (列表)](#list-列表)
	- [*ArrayBuffer* (变长数组)](#arraybuffer-变长数组)
	- [*Set* (集合)](#set-集合)
	- [*Map* (映射)](#map-映射)
	- [*GenTraversableLike*](#gentraversablelike)
	- [集合有序性](#集合有序性)
- [*Higher Order Function* (高阶函数)](#higher-order-function-高阶函数)
	- [*for/yeild* 语句](#foryeild-语句)
- [*Exception* (异常)](#exception-异常)
	- [*scala.util.Try[T]*](#scalautiltryt)
- [*Package* (包)](#package-包)
	- [包与路径](#包与路径)
	- [扩展用法](#扩展用法)
	- [默认导入](#默认导入)
	- [包对象](#包对象)
- [*Implicit Conversions* (隐式转换)](#implicit-conversions-隐式转换)
	- [定义隐式转换](#定义隐式转换)
	- [隐式参数](#隐式参数)
	- [隐式类](#隐式类)
- [*TypeClass*](#typeclass)
- [求值策略](#求值策略)
	- [参数的求值策略](#参数的求值策略)
	- [**&&**、**||** 运算符](#-运算符)
- [并发编程](#并发编程)
	- [*Future*](#future)
	- [*Promise*](#promise)
	- [*async/await*](#asyncawait)
	- [*synchronized*](#synchronized)
- [*Reflect* (反射)](#reflect-反射)
	- [反射机制相关类型](#反射机制相关类型)
- [*Annotation* (注解)](#annotation-注解)
	- [自定义注解](#自定义注解)
	- [解析注解](#解析注解)
- [*XML* 解析](#xml-解析)
	- [节点类型](#节点类型)
	- [读写 XML 文件](#读写-xml-文件)
	- [查找节点](#查找节点)
	- [节点属性](#节点属性)
	- [遍历节点](#遍历节点)
	- [创建 XML](#创建-xml)

<!-- /TOC -->



## *Scala* 开发环境
`Scala`是基于`JVM`的编程语言，配置`Scala`开发环境前需要正确安装与配置`JDK`。

- **Linux/Unix**系统：

	使用发行版自带的包管理器安装`Scala`。

	```
	# apt install scala //Debian系
	# pacman -S scala //Arch系
	$ brew install scala //macOS
	```

- **Windows**系统：

	1. 安装`Oracle JDK`。
	1. 从`http://www.scala-lang.org/files/archive/`下载`Scala SDK`。
	1. 设置环境变量`SCALA_HOME`。
	1. 将`%SCALA_HOME%\bin`加入`PATH`环境变量中。

### 使用 *Vim*
`Vim`默认不支持`Scala`语言，需要安装`vim-scala`插件提供`Scala`支持。  
使用**Vundle**安装此插件，在配置文件`.vimrc`中添加：

```vim
Plugin 'derekwyatt/vim-scala'
```

### 使用 *Eclipse*
安装`Scala IDE`插件。

### 使用 *IDEA*
安装`JetBrains`官方提供的`Scala`插件。

### *Scala* 编译工具
与编译Java代码类似，编译Scala代码使用`scalac`命令：

```
$ scalac *.scala
```

编译后即可得到字节码文件`*.class`。  
执行字节码可以使用`scala`指令：

```
$ scala 主类类名
```

对于使用了`包(package)`的源码，在用`scalac`指令进行编译时，编译器会自动根据包路径创建对应的目录，然后在对应的包路径下生成对应的class文件。

运行带有包路径的字节码需要在包路径的相对根目录下，执行：

```
$ scala 包路径.主类名
```

### 反编译
使用`scalap`可以反编译字节码得到Scala代码：

```
$ scalap *.class
```

或者

```
$ scalap 类名
```

如果需要查看字节码的对应生成的Java代码，可以使用`javap`工具：

```
$ javap 类名
```

使用`javap`可以直接查看生成的字节码：

```
$ javap -c 类名
```

默认情况下，通过反编译得到的Scala以及Java代码只能看到公有方法的声明，方法实现以及私有、保护成员均**不可见**。  
查看所有成员需要添加`-p/-private`参数：

```
$ javap -private 类名
$ scalap -private 类名
```

### *Scala REPL*
在命令行中输入无参数的`scala`指令即可进入交互式的`Scala REPL`。  
常用的`Scala REPL`指令：

```scala
scala> :quit //退出解释器
scala> :reset //重置解释器的状态，会清空已保存的变量、类、方法等所有内容
```

`Scala REPL`与`Python REPL`类似，可以直接输入代码并立即获得反馈。



## Hello World
创建文件`Main.scala`，输入以下代码：

```scala
object Main {
  def main(args: Array[String]) =
    println("Hello World!")
}
```

与`Java`类似，`Scala`也是从主方法`main`中开始执行整个程序。  
`Scala`中的`main`方法并不定义在类中，而是定义在**单例对象**中(使用`object`关键字创建单例对象)。  
将`main`方法写在`class`中能够通过编译，但生成的字节码文件在执行时会出错。

可以不手动定义`main`方法而让单例对象继承`App`特质，即可直接执行代码语句，例如：

```scala
object Main extends App {
  println("Hello World!")
}
```



## *Method* (方法)
方法使用`def`关键字定义，一个典型的方法格式如下：

```scala
def methodName(args: Type)：Type = {
  /* function_body */
}
```

### 方法返回值
大部分情况下，对于拥有返回值的方法，方法的返回值类型可**省略**，如下所示：

```scala
def methodName(args: Type) = {
  /* function_body */
}
```

但出于代码的可读性考虑，对于公有方法，**不建议**省略返回值类型。

对于方法体仅有单行代码的情形，可直接省略方法体外部的花括号：

```scala
def methodName(args: Type) = /* function_body */
```

大部分情况下，方法体**不需要**显式使用`return`关键字来给出方法返回值，编译器会将方法体内部最后一句代码的返回值类型做为整个函数的返回值，如下所示：

```scala
def num = {
  200 //编译器推断出返回值为 Int 类型
}
```

在方法具有多个返回点或需要提前返回时，需要显式使用`return`表示方法结束，如下所示：

```scala
// 不使用 return 时，方法永远返回 50
def num(num: Int): Int = {
  if (num < 0) return 20
  if (num == 0) return 30
  50
}
```

方法体内部使用了`return`关键字，则返回值不再由编译器推导，需要手动写明返回值类型。

方法体前的**等号**代表方法体有返回值，编译器会推断方法体的返回值：

- 在显式指定方法返回类型的情况下，方法体前的等号必须写出，即使返回类型为代表无返回值的`Unit`类型。
- 若方法无返回值且未写出返回类型，方法体前的等号可以省略。
 
方法和函数的形参**不需要**也**不能**使用`val`、`var`关键字修饰，只需写明类型即可。

### 空参数方法与无参数方法
方法允许省略参数，空的参数表可以直接**省略**，如：

```scala
def getNum: Int = 100
def getNum(): Int = 100 //以上两个定义只能存在一个
```

无参数方法与空参数方法只能存在一个，二者在使用方式上略有不同：

- 无参方法在调用时只能直接使用方法名，在方法名后加上括号调用就会出错。
- 空参方法既可以使用带有括号的方法调用方式，也可以省略括号。

如下所示：

```scala
scala> def getNum: Int = 100 //定义了方法 getNum: Int
getNum: Int
scala> getNum //正确，返回 100
res0: Int = 100
scala> getNum() //错误，提示 error: Int does not take parameters
<console>:12: error: Int does not take parameters
  getNum()
        ^
scala> def getNum(): Int = 200 //定义了方法 getNum(): Int，覆盖了之前定义的 getNum: Int
getNum: ()Int
scala> getNum //正确，返回 200
res1: Int = 200
scala> getNum() //正确，返回 200
res2: Int = 200
```

同时，无参方法不能与已有字段名称相同(编译报错)，而空参方法允许带有同名的字段。

### 参数默认值
在Scala中，方法中的参数允许带有**默认值**：

```scala
scala> var num = 100
num: Int = 100
scala> def setNum(p: Int = 0) { num = p } //方法的参数不能由默认值进行类型推导，即使给参数写明了默认值，也依然需要显式指明类型
setNum: (p: Int)Unit
scala> setNum() //对于有参数的方法，即使参数带有默认值使得参数表可以为空但在调用时依然不能省略括号，否则报错
scala> println(num)
0 //输出0
```

若方法中包含多个同类型并带有默认值的参数，调用时默认匹配第一个参数：

```scala
scala> def func(num1: Int = 100, num2: Int = 200) = println(s"$num1 $num2")
func: (num1: Int, num2: Int)Unit
scala> func(300)
300 200
```

在常见的支持方法参数默认值的编程语言中，参数默认值会有一些限制：

- `C#`中的参数默认值只能是编译时常量。
- `C++`中的参数默认值可以是成员变量、全局变量，但不能是函数结果。
- `C++`中使用非静态成员变量做为参数默认值时，类实例必须设定默认值在之前创建，不能在设定默认值的表达式中创建实例获取成员变量。

在`Scala`中方法的参数默认值可以是变量，类内字段，甚至是另一个方法的返回结果。  
如下所示：

```scala
class Test {
  var num = 23333
}

object Main extends App {
  def get(num: Int = (new Test).num) = num //Scala支持使用new操作符创建实例获取成员字段做为默认值
  def show(num: Int = get()) = println(num)
  show()
}
```

输出结果：

```
23333
```

- 默认参数与方法重载

	在Scala中，若一个带有默认的参数的方法省略默认参数时签名与一个已经存在的方法相同，编译器并不会报错(C++编译器则会报错)。  
	在调用方法时优先使用**无默认值**的版本(处理逻辑类似于C#)：

	```scala
	object Main extends App {
	  def func() = println("No Args")
	  def func(num: Int = 100) = println(num)
	  func()
	}
	```

	输出结果：

	```
	No Args
	```

- 具名参数

	在Scala中，调用方法时可以在参数表中写明参数的名称，该特性被称为**具名参数**。  
	对于方法中包含多个同类型并带有默认值参数的情况下，使用该特性可以显式指定要传入的是哪一个参数：

	```scala
	scala> func(num2 = 300)
	100 300
	```

- 默认参数顺序

	与C++不同，在Scala中，方法参数的默认值**不需要**从尾部开始连续出现，参数的默认值可以交错出现：

	```scala
	scala> def func(int: Int, str: String = "String", char: Char, double: Double = 123.0) = println(s"$int $str $char $double")
	func: (int: Int, str: String, char: Char, double: Double)Unit
	scala> func(100, 'c')
	<console>:12: error: not enough arguments for method func: (int: Int, str: String, char: Char, double: Double)Unit.
	Unspecified value parameter char.
	    func(100, 'c')
	        ^
	scala> func(int = 100, char = 'c') //对于默认参数不连续的方法，需要使用"具名参数"特性
	100 String c 123.0
	```



## *Function* (函数)
函数使用`var/val`关键字定义，即函数是一个存储了函数对象的字段。

一个典型的函数定义如下：

```scala
var functionName: FuncType = 符合签名的方法/函数/Lambda
```

函数类型为`Function*`，根据参数数目的不同，
Scala中提供了`Function0[+R]`(无参数)到`Function22[-T1, ..., -T22, +R]`共**23**种函数类型，
即函数最多可以拥有**22**个参数。

函数类型`(A, B, C, ...) => D`形式的语法实际是`Function`类型的语法糖，例如：

- 类型`() => String`实际类型为`Function0[String]`。
- 类型`Int => String`实际类型为`Function1[Int, String]`。
- 类型`(Int, Int) => String`实际类型为`Function2[Int, Int, String]`。
- 依此类推...

函数是一个`Function`类型的实例，方法中的一些特性不能用在函数中：

- 函数**不存在**重载，作用域内的一个函数实例只能有一个实现。
- 函数**不允许**带有默认值。
- 函数**不允许**定义隐式参数。
- 函数**不允许**柯里化(不能定义多参数表)。
- 函数不能带有泛型参数。
- 函数参数类型为**传名参数**时，需要写明函数的完整定义，不能采用推导返回值的语法。
- 空参函数的括号不可省略，直接使用函数名不代表调用空参函数，而是访问函数实例。

如下所示：

```scala
scala> var show100: () => Int = () => 100
show100: () => Int = <function0>
scala> show100 //直接使用函数名得到的是函数对象而非调用函数
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

### 函数组合
在Scala中，函数允许进行组合。  
函数组合有两种方式：

1. `a compose b`实际调用次序为`a(b())`。
1. `a andThen b`实际调用次序为`b(a())`。

方法不能直接进行组合，需要将其转化为函数(方法名之后加`_`符号)。

```scala
object Main extends App {

  def add(num: Int) = num + 100
  def double(num: Int) = num * 2

  //只有函数能进行组合,方法需要加"_"符号转化成函数
  val compose = add _ compose double
  val andThen = add _ andThen double

  println(compose(100) == add(double(100)))
  println(andThen(100) == double(add(100)))
}
```

输出结果：

```
true
true
```

### *Partial Function* (偏函数)
偏函数是一个定义域有限的函数，偏函数类似数学意义上的函数，只能接收**一个**参数，只对**有限**的输入值返回结果。

在Scala中使用类型`PartialFunction[-A, +B]`来表示偏函数。  
`PartialFunction[-A, +B]`继承于`A => B`类型，即偏函数具有普通函数的功能，是普通函数的一类特例。

可以使用**模式匹配**中的`case`语法来定义有限定义域的偏函数，一个最简单的偏函数如下所示：

```scala
scala> val func: PartialFunction[Int, Int] = { case 0 => 0 }
func: PartialFunction[Int,Int] = <function1>
```

这个偏函数只在输入值为`0`时有意义：

```scala
scala> func(0)
res1: Int = 0

scala> func(1)
scala.MatchError: 1 (of class java.lang.Integer)
  at scala.PartialFunction$$anon$1.apply(PartialFunction.scala:253)
  at scala.PartialFunction$$anon$1.apply(PartialFunction.scala:251)
  at $anonfun$1.applyOrElse(<console>:11)
  at $anonfun$1.applyOrElse(<console>:11)
  at scala.runtime.AbstractPartialFunction$mcII$sp.apply$mcII$sp(AbstractPartialFunction.scala:36)
  ... 32 elided

scala> func(-1)
scala.MatchError: -1 (of class java.lang.Integer)
  at scala.PartialFunction$$anon$1.apply(PartialFunction.scala:253)
  at scala.PartialFunction$$anon$1.apply(PartialFunction.scala:251)
  at $anonfun$1.applyOrElse(<console>:11)
  at $anonfun$1.applyOrElse(<console>:11)
  at scala.runtime.AbstractPartialFunction$mcII$sp.apply$mcII$sp(AbstractPartialFunction.scala:36)
  ... 32 elided
```

一个偏函数可以通过添加多个`case`语句块来添加多个定义域的返回结果：

```scala
scala> val func1: PartialFunction[Int, Int] = { case n if n > 0 => 1; case n if n < 0 => -1 }
func1: PartialFunction[Int,Int] = <function1>

scala> func1(-11111)
res3: Int = -1

scala> func1(11111)
res4: Int = 1

scala> func1(0)
scala.MatchError: 0 (of class java.lang.Integer)
  at scala.PartialFunction$$anon$1.apply(PartialFunction.scala:253)
  at scala.PartialFunction$$anon$1.apply(PartialFunction.scala:251)
  at $anonfun$1.applyOrElse(<console>:11)
  at $anonfun$1.applyOrElse(<console>:11)
  at scala.runtime.AbstractPartialFunction$mcII$sp.apply$mcII$sp(AbstractPartialFunction.scala:36)
  ... 32 elided
```

偏函数`func1()`对于定义域`(-∞，0)`返回`-1`，对于定义域`(0, +∞)`返回`1`。

偏函数可以使用`isDefinedAt()`方法来检验在给定的参数在偏函数中是否有定义：

```scala
scala> func1.isDefinedAt(10000)
res7: Boolean = true

scala> func1.isDefinedAt(-10000)
res8: Boolean = true

scala> func1.isDefinedAt(0)
res9: Boolean = false
```

使用`orElse()()`方法在一个偏函数没有定义的时候尝试调用另一个偏函数：

```scala
scala> func1.orElse(func)(0)
res10: Int = 0
```

函数`func1()`对于`0`没有定义，而函数`func()`对于`0`有定义，则在参数取`0`时调用`func()`函数的返回值。

使用`case`语法编写的代码块为`Anonymous Function`(匿名函数)，在上下文语义不明确的情况下，需要显式指定类型。  
如下所示：

```scala
scala> val func = { case 0 => 0 }
<console>:11: error: missing parameter type for expanded function
The argument types of an anonymous function must be fully known. (SLS 8.5)
Expected type was: ?
       val func = { case 0 => 0 }
                  ^
```

`case`函数语法还可以用在高阶函数中。

### *Partial Applied Function* (部分应用函数)
部分应用函数是逻辑上的概念，表示一个已经指定了部分参数的函数。  
将一个拥有多个参数的函数指定部分参数的值构成一个参数较少的新函数，新的函数即为**部分应用函数**。

Python中的偏函数与Scala中的偏函数是完全不同的概念，Python中偏函数的概念类似于Scala中的部分应用函数。

定义一个拥有2个参数的`sum()`函数，返回两个参数的和：

```scala
scala> def sum(num1: Int, num2: Int) = num1 + num2
sum: (num1: Int, num2: Int)Int
```

指定第二个参数始终为`100`，创建一个部分应用函数：

```scala
scala> val sum100 = sum(_: Int, 100)
sum100: Int => Int = $$Lambda$1539/1030946825@62e49cf9

scala> sum100(100)
res11: Int = 200
```

`sum100()`即为`sum()`指定了第二参数的部分应用函数。



## 块表达式
在`Scala`中，花括号`{ }`中可以包含一个或多个语句序列，称为**块表达式**。  
块表达式的**最后一条语句**会做为块表达式的结果。如下所示：

```scala
scala> { println("Block Expr!"); 23333 }
Block Expr!
res3: Int = 23333
```

方法、函数的参数可由对应返回类型的块表达式替代，如下所示：

```scala
def test(num: Int) = println(num)

test({
  println("Block Expr!")
  23333
})
```

当方法、函数仅接收**单一参数**时，小括号可省略：

```scala
def test(num: Int) = println(num)

test {
  println("Block Expr!")
  23333
}
```

### 赋值表达式
赋值表达式的值返回值为`Unit`(无返回值)。  
如下所示：

```scala
scala> var _num = 0
_num: Int = 0
scala> def testNum(num: Int): Int = _num = num //由编译器推断出的返回值类型为Unit
<console>:12: error: type mismatch;
found   : Unit
required: Int
  def testNum(num: Int): Int = _num = num
                                      ^
```



## *OOP*
Scala是一门同时具有函数式与面向对象特性的**多重范式语言**，除了具有函数式特性外，对**OOP**也有着完整的支持。

### 访问权限
`Scala`中没有`public`关键字，成员和类、特质的默认访问权限即为**公有**。  
`Scala`中公有类的名称不强制要求与源码文件相同，同时一个文件中可以包含多个公有类的定义。

保护成员使用关键字`protected`，私有成员使用关键字`private`，作用大体上与`Java`相同，但在访问权限上支持**更细粒度**的划分。

- **类、特质、单例对象**定义前可以使用访问权限修饰，`private`和`protected`权限的**类、单例、特质**等仅限同包内访问。
- 顶层类允许使用`protected`权限修饰(与Java不同，Java仅允许内部类使用`protected`修饰)。
- 访问权限关键字用于类时，还可以写在类名与主构造器之间(特质、单例对象没有这种用法)，用于指定主构造器的访问权限。
- 访问级别关键字之后可以使用`[]`操作符设定更具体的访问区域限制。  
	访问区域限制可以是：
	1. 当前类
	1. 当前定义类的外部类(若存在外部类)
	1. 当前类所属包名(包内的所有类实例可访问)
	1. `this`关键字(仅当前实例可访问)
- 访问权限关键字之后若不写明具体的访问限制区域，则默认限制为当前类可访问(与Java行为基本一致，但Java中的保护成员包内可见)。

如下所示：

```scala
package TestCode {

  private class A //类定义前可以使用访问权限修饰
  protected class B //类定义的访问权限可以为protected

  case class Num private(num: Int = 200) //权限修饰符可以用在类名与主构造器之间，代表构造器私有

  // 即使主构造器参数为空，也不能直接以权限关键字结尾
  class Test protected() //或者写成 class Test protected {}

  class Access(a: Int = 1, var b: Double = 2.0) {
    def showOther1(access: Access) = access.show1 //出错，access非当前类实例，无访问权限
    def showOther2(access: Access) = access.show2 //正常访问
    def showOther3(access: Access) = access.show3 //正常访问
    private[this] def show1 = println(a + " " + b) //限定当前实例可访问
    private[Access] def show2 = println(a + " " + b) //类似Java中的private，当前类的任意实例皆可相互访问私有成员
    private[TestCode] def show3 = println(a + " " + b) //作用域为包名，此时的访问权限类似Java中的default访问权限，当前包中类的实例皆可访问到该私有成员
  }

}
```

### 字段
Scala类中的字段不仅仅是定义了一个成员变量，编译器生成字节码时可能会自动为字段生成与字段同名的`getter`和`setter`方法。

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
	public void num_$eq(int); //var字段生成了setter/getter
	public java.lang.String str(); //val字段生成了getter
	public Test();
}
```

若对象的的权限为私有，则对应生成的`setter`和`getter`方法同样为**私有**权限。

生成`setter/getter`方法遵循以下规则：

- `val`关键字定义的字段为**只读**字断，编译器只生成`getter`方法，不生成`setter`方法。
- 若访问权限为`private[this]`，则编译器不会为其合成`setter`和`getter`方法，  
	但`protected[this]`和`private`访问权限正常生成`setter/getter`方法。
- 若定义了字段没有对其进行初始化，则该字段即为**抽象字段**。  
	带有抽象字段的类前需要加上`abstract`关键字，且不能被直接实例化。
- 重写抽象字段不需要使用`override`关键字。

如下所示：

```scala
class Override {

  var m = 100 //普通成员字段会自动合成setter/getter方法
  /*
  def m(): Int = m //错误，提示重复定义
  def m_=(m: Int) { this.m = m } //错误，提示重复定义
  */
  def m(m: Int) {} //正常，签名未冲突

  /*
    私有this字段不会合成setter/getter方法，
    但自行手动定义同名的setter/getter方法时有许多限制(getter方法需要空参且写明返回值)，
    且没有实用价值(setter方法使用报错)	
  */
  private[this] var num = 100
  def num(): Int = num //正常
  def num_=(num: Int) {
    this.num = num
  } //正常，虽然定义时不报错，但赋值时报错
  /*
  def num = this.num //报错
  def num: Int = num //报错
  def num: Int = this.num //报错
  */

  // 常用的私有变量自定义setter/getter风格是私有字段名前加上下划线
  private[this] var _abc = 0
  def abc = _abc
  def abc_=(abc: Int) = _abc = abc
  /*
    也可以写成：
    def abc_=(abc: Int) { _abc = abc }
  */
}
```

在Scala中，字段名称可以与方法名称**相同**。

- 默认情况下，生成的`setter/getter`方法就与字段同名。  
	手动在代码中创建与`setter/getter`签名相同的方法会导致编译错误。
- 访问权限为`private[this]`的字段可以手动定义该字段的`setter/getter`方法(编译器不自动合成)。
- 在实际编码过程中，虽然给`private[this]`的字段定义同名的`setter`、`getter`方法不会报错，但调用过程中会提示错误(如上例子中给num字段赋值会得到错误`reassignment to val`，因此不要手动给字段定义同名的`setter`、`getter`方法)。

此外，由于字段名称可以与方法名称相同，因而即使编译器生成了`setter`、`getter`方法，编码者依然可以使用字段名称定义其它签名的重载函数。

### *Constructor* (构造器)
在Scala中构造方法的作用与Java类似，用于在创建类实例的同时对指定的成员进行初始化。  
Scala中类可以拥有一个**主构造器(primary constructor)**和任意个**辅助构造器(auxiliary constructor)**。

构造器的基本使用方法：

- 主构造器的参数定义紧跟在类名之后，辅助构造器定义在类体中，使用`this`关键字。
- 在辅助构造器的代码中必须立即调用主构造器或其它辅助构造器，之后才能执行其它代码。
- 调用父类的构造器必须在主构造器中，写在父类类名之后。

如下所示：

```scala
class Constructor(a: Int, var b: Double = 2.0) { //构造器参数紧跟在类名之后，构造器中的参数可以带有默认值
  //在构造器中创建了字段b，a变量没有显式使用var/val关键字，同时也没有被其它方法引用，因而仅仅作为临时变量存在

  //定义辅助构造器，使用this关键字
  def this() = this(2, 3.0) //辅助构造器的函数体中必须最终调用主构造器，辅助构造器即使没有参数也必须也必须带括号
}

//只有主构造器能够调用父类构造器，调用的父类构造器可以是主构造器，也可以是辅助构造器
class ExtendConstructor(a: Int = 2, c: Double = 4.0) extends Constructor(a, c) {
  def this() {
    //a = 100 //代码要在构造器调用之后，放在this()之前会报错
    this(2, 4.0)
    //super(2, 4.0) //在Scala中没有这种用法，父类的构造函数只能由主构造器调用
  }
}
```

- 主构造器作用域

	在`Scala`中，主构造器的实际范围为整个类内作用域。  
	即在类作用域内，可以直接在类内添加普通代码语句。  
	类内的普通代码语句即为构造方法的内容，在类实例构造时即被调用。

	如下所示：

	```scala
	class Test(str: String) {
	  println(str)
	}
	```

	类体中直接包含了普通的语句代码，而非成员定义。

	在类内作用域中直接添加普通代码时，需要考虑变量初始化顺序，如下所示：

	```scala
	class Test0 {
	  println(str)
	  val str = "abc"
	}

	class Test1 {
	  val str = "abc"
	  println(str)
	}

	object Main extends App {
	  new Test0()
	  new Test1()
	}
	```

	输出结果：

	```
	null
	abc
	```

	类作用域中的普通语句可以直接引用类内定义的成员字段(即使成员字段定义在语句之后)。  
	但若成员字段的定义语句在执行语句之后，则成员字段在被引用时**未初始化**。

- 主构造器访问权限

	在**类名**之后，**主构造器参数**之前可以添加访问权限修饰符，用于限定主构造器的访问权限。  
	如下所示：

	```scala
	class Test private(num: Int) {
	  def show() = println(num)
	}

	// Scala中单例模式的写法
	object Test {
	  lazy val instance = Test()
	  private def apply() = new Test(100) //正确，伴生对象中可以访问类的私有成员，包括私有主构造器
	}

	object Main extends App {
	  Test.instance.show() //正确，获取单例
	  new Test(100).show() //错误，无法直接访问私有构造器
	}
	```

- 主构造器参数做为成员字段

	主构造器的参数中若添加了`var/val`关键字，则该参数将作为类的成员字段存在。  
	构造器参数前使用`var`关键字，如下所示：

	```scala
	class Constructor(var num: Int)
	```

	编译为Java代码为：

	```java
	public class Constructor {
		private int num;
		public int num();
		public void num_$eq(int);
		public Constructor(int);
	}
	```

	可以看到，编译器为`var`字段`num`生成了`setter`、`getter`方法和一个与字段同名的私有变量。

	构造器参数前使用`val`关键字，如下所示：

	```scala
	class Constructor(val num: Int)
	```

	编译为Java代码为：

	```java
	public class Constructor {
		private final int num;
		public int num();
		public Constructor(int);
	}
	```

	可以看到，编译器为`val`字段`num`生成了`getter`方法和一个与字段同名的`final`私有变量。

	构造器参数前加上**访问权限修饰符**则生成的方法类似，但方法前会添加对应的访问权限(Scala中的`protected`限定符编译为Java后变为`public`)，如下所示：

	```scala
	class Constructor0(protected[this] var num: Int)
	class Constructor1(private val num: Int)
	```

	编译为Java代码为：

	```java
	public class Constructor0 {
		private int num;
		public int num();
		public void num_$eq(int);
		public Constructor0(int);
	}
	public class Constructor1 {
		private final int num;
		private int num();
		public Constructor1(int);
	}
	```

	只有访问权限为`private[this]`时，编译器才不会为引用的字段生成`setter/getter`，而仅仅生成一个私有成员变量。

- 主构造器参数的默认字段生成规则

	主构造器的参数中若没有使用`val/val`关键字，则默认修饰为`private[this] val`。  
	编译器默认不会为该参数生成`setter/getter`方法以及私有成员变量，除非被其它成员方法引用。

	如下所示：

	```scala
	class Constructor0(num: Int)
	class Constructor1(private[this] val num: Int)
	```

	编译为Java代码为：

	```java
	public class Constructor0 {
		public Constructor0(double);
	}
	public class Constructor1 {
		public Constructor1(double);
	}
	```

	编译得到的Java代码完全相同。

	当该参数被其它成员方法引用时，编译器会为其生成对应的`final`私有成员变量(但没有生成`setter/getter`)。  
	只要构造器参数没有使用`var`关键字标记，则生成的成员变量就带有`final`属性。

	如下所示：

	```scala
	class Constructor0(num: Int) {
	  def get = num
	}
	class Constructor1(private[this] val num: Int) {
	  def get = num
	}
	```

	编译为Java代码为：

	```java
	public class Constructor0 {
		private final int num;
		public int get();
		public Constructor0(int);
	}
	public class Constructor1 {
		private final int num;
		public int get();
		public Constructor1(int);
	}
	```

	辅助构造器中的参数与普通函数参数类似，仅在构造器代码段内部生效(不作为字段存在)，辅助构造器的参数前不能添加`var/val`关键字。

- 默认构造方法

	一个类如果没有显式写明主构造器参数，则默认生成一个**空参**构造方法。

	对于一个如下的**空类**：

	```scala
	class Empty
	```

	实际相当于：

	```scala
	class Empty() { }
	```

	编译成Java代码后为：

	```java
	public class Empty {
		public Empty() { ... };
	}
	```

	可以采用如下方式实例化：

	```scala
	new Empty()
	new Empty //空参方法括号可省略
	```

	与主流的OOP语言不同，一个使用默认生成的空参构造函数的作为主构造器的类即使定义了其它构造器，默认生成的主构造器**依然存在**。  
	如下所示：

	```scala
	class Default {
	  def this(num: Int) = this
	}
	```

	编译成Java代码后为：

	```java
	public class Default {
		public Default();
		public Default(int);
	}
	```

	可以看到，默认的空参构造方法依然存在。

	主构造器不能在类体中重新定义，如下所示：

	```scala
	class Default {
	  //编译报错，主构造器已为空参，不能重复定义
	  def this() { ... }
	}
	```

### 多态
Scala作为OOP语言，支持多态。

- 重写

	子类重写父类的非抽象方法、字段时，需要显式地在方法定义前加上`override`关键字，否则无法通过编译。  
	实现抽象方法则不需要。  
	重写遵循以下规则：

	- `def`只能重写另一个`def`。
	- `val`可以重写另一个`val`以及不带有参数的`def`。
	- `var`只能重写另一个抽象的`var`(即只有定义没有实现)。

- 重载

	`Scala`支持方法重载，签名不同名称相同的方法可以共存。  
	`Scala`可以使用**操作符**作为方法名称，可以实现类似**C++/C#**中**操作符重载**的效果。

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
    // Cloneable接口中clone()返回的是Object型，即Scala中的Any，需要进行强制类型转换
    val clone = super.clone.asInstanceOf[Clone]
    clone.nums = nums.clone //深复制需要对成员中的引用类型调用clone()
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
    val clone = super.clone //不必进行强制类型转换，类型已在泛型参数中指定
    clone.nums = nums.clone
    clone
  }
}
```

### 匿名类初始化
在Scala中，创建类实例的**同时**可以直接对类的成员变量进行初始化。

如下所示：

```scala
object Init extends App {
  val num = new Num {
    num = 100
    name = "Num"
  } //相当于创建了一个匿名类，然后向上转型到类Num上
  println(s"${num.name} ${num.num}") //正常输出了初始化的值
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
		}}; //匿名类的构造函数的函数名为空，因此可以使用大括号直接嵌套的方式
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



## *Singleton Objects* (单例对象)
使用`object`关键字定义单例对象。  
单例对象是一个实例，可以在单例对象内部定义常见的内容，如字段、方法等：

```scala
scala> object Test { val num = 2333; private[this] val msg = "6666"; def show() = println(msg) }
defined object Test

scala> Test.num
res1: Int = 2333

scala> Test.msg //单例对象的内部成员支持访问权限控制
<console>:13: error: value msg is not a member of object Test
       Test.msg
            ^

scala> Test.show()
6666
```

### 单例类型
单例对象可以继承其它类型、混入特质：

```scala
scala> class Base { def showBase() { println("Show Base") } }
defined class Base

scala> trait Trait { def showTrait() { println("Show Trait") } }
defined trait Trait

scala> object Test extends Base with Trait
defined object Test

scala> Test.showBase()
Show Base

scala> Test.showTrait()
Show Trait
```

单例对象的类型使用`单例名称.type`表示单例自身的类型。  
继承了类、混入了特质的单例的单例类型能够正常通过继承关系的判定。  
如下所示：

```scala
scala> import scala.reflect.runtime.universe.typeOf
import scala.reflect.runtime.universe.typeOf

scala> typeOf[Test.type] //单例自身的类型信息
res1: reflect.runtime.universe.Type = Test.type

scala> typeOf[Test.type] <:< typeOf[Base]
res2: Boolean = true

scala> typeOf[Test.type] <:< typeOf[Trait]
res3: Boolean = true
```

### 初始化
单例对象默认即带有延迟初始化的特性。  
单例在定义时并未初始化，初始化行为发生在单例首次被访问时。

若在单例构造器中添加带有副作用的语句，则副作用会在首次访问单例时出现。  
如下所示：

```scala
scala> object Test { println("Init Singleton Test") }
defined object Test

scala> Test //首次访问单例，单例进行初始化，触发副作用
Init Singleton Test
res0: Test.type = Test$@16ea0f22

scala> Test //再次访问单例，单例已被初始化，不再触发副作用
res1: Test.type = Test$@16ea0f22
```

### *Companions* (伴生对象)
`Companions`(伴生对象)是一类特殊的单例对象。  
每一个类可以拥有一个同名的**伴生对象**(单例)，伴生对象具有以下特征/限制：

- 一个类和其伴生对象的定义必须写在同一个文件中。
- 伴生对象与同名类之间可以相互访问私有、保护成员。

Scala相比Java是更加纯粹的面向对象语言，Scala中没有`static`关键字和**静态成员**的概念，
Scala使用**伴生对象**来达到近似静态成员的作用。  
对于Java代码中定义的静态字段、静态方法，在Scala中也以单例对象的语法进行访问。



## *apply()/update()* 方法
`apply()/update()`方法是Scala中的**语法糖**。
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

如下所示：

```scala
object Main extends App {
  var a = new Apply(0, 0)
  val show = () => println(a.num1 + " " + a.num2)
  a(1) //相当于调用 a.apply(1)
  show() //输出 1 2
  a(100, 200) = Apply(10, 20) //相当于调用 a.update(100, 200, new Apply(10, 20))
  show() //输出 90 180
  Apply(1000, 2000) = a
  show() //输出 1000 2000
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

// 单例对象同样可以定义 apply()/update() 方法
object Apply {
  def apply(num1: Int, num2: Int) = new Apply(num1, num2)
  def update(num1: Int, num2: Int, test: Apply) {
    test.num1 = num1
    test.num2 = num2
  }
}
```

输出结果：

```
1 2
90 180
1000 180
```

### 无参 *apply* 方法
`apply()`方法对应的无参数形式`apply`方法在通常情形下并不生效，
字段、类会被优先解析为本身的含义(值、类型)。  
如下所示：

```scala
scala> object Test { def apply { println("Print test") } }
defined object Test

scala> Test //直接使用单例对象名称被解析为单例对应类型
res1: Test.type = Test$@3a5b7d7e

scala> Test.apply //显式调用 apply 方法
Print test

scala> class Test { def apply { println("Print test") } }

scala> val t = new Test
t: Test = Test@4c5379f5

scala> t //直接使用字段名称被解析为字段自身
res8: Test = Test@4c5379f5

scala> t.apply //显式调用 apply 方法
Print test
```

在无参`apply`方法带有**泛型参数**时，可以正常使用带有泛型参数的省略形式。  
如下所示：

```scala
scala> object Test { def apply[T] { println("Print test") } }

scala> Test[Any] //带有泛型参数，省略 apply 方法，正常执行调用
Print test

scala> class Test { def apply[T] { println("Print test") } }

scala> val t = new Test
t: Test = Test@6f88319b

scala> t[Any] //字段名称带有泛型参数，亦被解析为无参泛型 apply 调用
Print test
```



## *unapply()/unapplySeq()* 方法
**提取器**用于解构对象，通过实现`unapply()`方法定义解构行为。

- `unapply()`方法则与`apply()`方法相反，可以从对象中提取出需要的数据(在实际使用过程中，可以从任意的目标里提取数据)。
- `unapply()`方法返回值必须为`Option`及其子类，单一返回值使用`Option[T]`，多个返回值可以包含在元组中`Option[(T1, T2, T3, ...)]`。
- `unapply()`方法虽然也可以定义在类中，但一般定义在**伴生对象**中(在类中定义没有合适的语法使用)。

假设有伴生对象名为`Unapply`，则：

```scala
val Unapply(arg1, arg2, arg3, ...) = value
```

等价于：

```scala
val (arg1, arg2, arg3, ...) = Unapply.unapply(value)
```

如下所示：

```scala
object TestUnapply extends App {
  val Unapply(num1) = 1 //提取一个值
  println(num1)
  val Unapply(num2, num3) = Unapply(100, 200) //提取多个值
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

如下所示：

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
  def unapplySeq(str: String) = Option(str split "\\.") //split()方法接收的是正则表达式，小数点、加减乘除之类的符号需要转义
}
```

输出结果：

```
Case Nothing
abc cde
abc cde efg
```



## *Trait* (特质)
Scala中的`trait`特质对应Java中的`interface`接口。  
相比Java中的接口，Scala中的特质除了不能自定义有参构造器、不能被直接实例化之外，拥有绝大部分类的特性。

`trait`内可以添加普通代码语句(默认构造器)、定义成员变量以及成员方法。  
`trait`内的成员方法可以为抽象方法，也可以带有方法的实现。  
`trait`中的成员同样可以设置访问权限。

### *Mixin* (混入)
Scala不支持**多重继承**，一个类只能拥有一个父类，但可以**混入(mixin)**多个特质。

- **Mixin**机制相比传统的单根继承，保留了多重继承的大部分优点。
- 使用`with`关键字混入特质，一个类中混入多个特质时，会将第一个扩展的特质的父类作为自身的父类，同时，后续混入的特质都必须是从该父类派生。
- 若同时继承类并混入特质，需要将继承的类写在`extends`关键字的后面，`with`只能混入**特质**，不能混入**类**。

如下所示：

```scala
class BaseA

class BaseB

trait TraitA extends BaseA

trait TraitB extends BaseB

/* 编译报错，提示：
 * superclass BaseA
 * is not a subclass of the superclass BaseB
 * of the mixin trait TraitB
 */
class TestExtend extends TraitA with TraitB

/* 编译报错，提示：
 * class BaseA needs to be a trait to be mixed in
 */
class ExtendClass extends TraitA with BaseA
```

`TestExtend`类中，特质`TraitA`的父类`BaseA`并不是特质`TraitB`父类`BaseB`的父类，而Scala中一个类只能拥有一个父类，因而无法通过编译。  
`ExtendClass`类中，应该继承`BaseA`后混入特质`TraitA`，`with`关键字之后的必需是特质而不能是类名。

### 重写冲突方法、字段
混入机制需要解决**富接口**带来的成员冲突问题。  
当一个类的父类与后续混入的特质中带有相同名称的字段或相同签名的方法时，需要在子类重写这些冲突的内容，否则无法通过编译。

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
  override def get = 77 //对于冲突的内容，必需显式重写
}
```

### 构造顺序
对于混入的内容，按照以下顺序进行构造：

1. 按继承树依次从最外层的父类开始构造。
1. 按照特质出现的顺序从左往右依次构造特质。
1. 在一个特质中，若该特质存在父特质，则先构造父特质。  
	若多个特质拥有相同的父特质，该父特质不会被重复构造。
1. 最后构造当前类。

如下所示：

```scala
class ClassBase {
  println("ClassBase")
}

class ClassChild extends ClassBase {
  println("ClassChild")
}

trait TraitBase {
  println("TraitBase")
}

trait TraitA extends TraitBase {
  println("TraitA")
}

trait TraitB extends TraitA {
  println("TraitB")
}

class Main extends App {
  new ClassChild with TraitA with TraitB {
    println("Now") //当前特质最后进行构造
  }
}
```

输出结果：

```
ClassBase
ClassChild
TraitBase
TraitA
TraitB
Now
```

### 线性化顺序
`Scala`的混入机制是`线性化`的，对于冲突的内容，构造中的后一个实现会顶替前一个。  
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

trait TraitC extends TraitB {
  override def get = 111
}

class TestExtend extends BaseA with TraitA with TraitC {
  override def get = super.get //使用父类的实现时不需要显式指定到底是哪一个，编译器会自动按照线性化顺序选择最后的实现，即TraitC中的实现，即返回111
  //override def get = super[BaseA].get //也可以使用继承自其它特质或类的实现
  //override def get = super[TraitB].get //错误，必需使用直接混入的类或特质，不能使用继承层级中更远的类或特质
}
```

### 线性化与 *override*
在重写抽象字段时，是否使用`override`关键字在混入时行为存在差异。  
如下所示：

```scala
trait Name {
  def name: String
}

trait NameA extends Name {
  def name = "A"
}

trait NameB extends Name {
  def name = "B"
}

object Main extends App {
  new NameA extends NameB //编译出错
}
```

混入两个重写了同一个抽象方法/字段的特质时，若未使用`override`关键字，则混入时编译出错，需要显式重写冲突内容。

若特质使用了`override`关键字进行重写，则混入时依据线性化顺序决定最终的实现(保留最后混入的实现)。  
如下所示：

```scala
trait Name {
  def name: String
}

trait NameA extends Name {
  override def name = "A"
}

trait NameB extends Name {
  override def name = "B"
}

object Main extends App {
  (new NameA extends NameB).name //返回 "B"
  (new NameB extends NameA).name //返回 "A"
}
```

混入多个存在冲突内容的特质时，不需要所有的特质都使用`override`关键字进行重写，
仅需要最后一个混入的特质使用`override`重写冲突内容。  
如下所示：

```scala
trait Name {
  def name: String
}

trait NameA extends Name {
  def name = "A"
}

trait NameB extends Name {
  override def name = "B"
}

object Main extends App {
  (new NameA extends NameB).name //返回 "B"
  (new NameB extends NameA).name //编译出错
}
```

### 线性化与类型关系
在混入带有冲突内容的特质时，冲突内容的类型不能为完全无关的类型。  
如下所示：

```scala
scala> class A
defined class A

scala> class B
defined class B

scala> trait TraitA { val t: A }
defined trait TraitA

scala> trait TraitB { val t: B }
defined trait TraitB

scala> trait TestMixin extends TraitA with TraitB
<console>:13: error: overriding value t in trait TraitA of type A;
 value t in trait TraitB of type B has incompatible type
       trait TestMixin extends TraitA with TraitB
             ^
```

混入冲突内容时，冲突内容的类型可以不完全相同，但需要满足继承关系，同时子类位于线性化顺序的**最右端**，
即满足`最右端类型 <: 冲突字段类型链中最具体的类型`。  
如下所示：

```scala
scala> class Base
defined class Base

scala> class Child extends Base
defined class Child

scala> trait TraitA { val t: Base }
defined trait TraitA

scala> trait TraitB { val t: Child }
defined trait TraitB

scala> trait TestMixin extends TraitA with TraitB
defined trait TestMixin
```

线性化过程中，冲突字段使用更具体的子类类型取代了父类类型。  
调整混入顺序，则出现类型不兼容的提示：

```scala
scala> trait TestMixin extends TraitB with TraitA
<console>:13: error: overriding value t in trait TraitB of type Child;
 value t in trait TraitA of type Base has incompatible type
       trait TestMixin extends TraitB with TraitA
             ^
```

线性化的最右端需要为更**具体**的类型，但混入顺序中间的冲突字段不必都比前一个冲突字段更具体
(中间字段类型仅需存在父子类关系即可，可为基类)。  
如下所示：

```scala
scala> trait TestMixin extends TraitB with TraitA { val t: Child }
defined trait TestMixin //冲突字段的混入类型链为 Child => Base => Child
```

### 线性化与泛型
当混入特质带有冲突内容类型为泛型参数时，只要泛型参数满足继承类型约束，并保证子类位于线性化顺序的最右端，
同样可以正常进行类型定义。  
如下所示：

```scala
scala> trait Test
defined trait Test

scala> trait TraitA { val t: Test }
defined trait TraitA

scala> trait TraitB[T <: Test] { val t: T }
defined trait TraitB

scala> trait TestMixin[T <: Test] extends TraitA with TraitB[T]
defined trait TestMixin //使用类型下界

scala> trait TestMixin[T <: Test] extends TraitB[T] with TraitA { val t: T }
defined trait TestMixin //冲突字段的混入类型链为 T => Test => T

scala> trait TraitC[T >: Test] { val t: T }
defined trait TraitC

scala> trait TestMixin[T >: Test] extends TraitC[T] with TraitA
defined trait TestMixin //使用类型上界

scala> trait TestMixin[T >: Test] extends TraitA with TraitC[T] { val t: Test }
defined trait TestMixin //冲突字段的混入类型链为 Test => T => Test
```



## *Case Class* (样例类)
样例类是一种特殊的类，通常用在**模式匹配**中。  
在类定义前使用`case`关键字即可定义一个样例类。

相比普通的类，样例类有以下特性：

- 样例类构造器中的字段默认使用`val`关键字定义(即默认为公有访问权限，而不是普通类默认的`private[this]`)。
- 样例类默认即实现了`apply()`方法用于构造对象和`unapply()`方法用于模式匹配。
- 样例类默认实现了`toString`、`equals`、`hashCode`、`copy`等其它方法。

如下所示：

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

  //样例类经常用于模式匹配中(unapply()方法的应用)
  def show(ca: Case) = ca match {
    case Case(num, _) if num > 100 => println("Case.num > 100")
    case Case(100, _) => println("Case.num == 100")
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

### 避免重定义样例类自动生成的方法
手动创建样例类的伴生对象时，应避免定义与样例类自动生成方法签名相同的方法(`apply()/unapply()`等)，否则编译报错。  
如下所示：

```scala
object Main extends App {

  case class Case(num: Int)

  object Case {
    def apply(num: Int) = new Case(num) //编译报错
    def unapply(arg: Case) = Option(arg.num) //编译报错
  }

}
```

错误提示：

```
error: method apply is defined twice;
  the conflicting method apply was defined at line 6:9
  case class Case(num: Int)
             ^
error: method unapply is defined twice;
  the conflicting method unapply was defined at line 7:9
  case class Case(num: Int)
             ^
```

若伴生对象中的自定义方法与默认生成的方法签名不同，则正常编译。  
如下所示：

```scala
object Main extends App {

  case class Case(num: Int)

  object Case {
    def apply(num1: Int, num2: Int) = new Case(num1 + num2) //正常编译
    def unapply(arg: (Case, Case)) = Option(arg._1.num, arg._2.num) //正常编译
  }

}
```



## 类型
在Scala中，所有的类型**皆为对象**，所有类型都从根类`Any`继承，`Any`有`AnyVal`和`AnyRef`两个子类。

### 基础类型
基础类型如`Int`、`Float`、`Double`、`Unit`等全部从`AnyVal`类中派生。  
可以直接在泛型中直接使用这些类作为类型参数。  
同时，`Scala`中提供了`隐式转换(ImplicitConversion)`来保证`Int`、`Float`、`Double`等类型之间可以**自动进行转换**。

所有的基础类型之外的引用类型派生自类`AnyRef`。

- 基础类型转换

	基础类型与字符串(String)等类型之间的转换也由类提供的成员函数进行。  
	将数值与字符串相互转换，如下所示：

	```scala
	val str = 100.toString
	val num = str.toInt
	```

### *Bottom* (底类型)
`Scala`中存在底类型(`Bottom Type`)。底类型包括`Nothing`和`Null`。

- `Nothing`

	`Nothing`是所有类型的子类型，定义为`final trait Nothing extends Any`。  
	`Nothing`特质没有实例。

	一些特殊的操作返回类型为`Nothing`，如抛出异常：

	```scala
	scala> def e = throw new Exception
	e: Nothing
	```
	
	`Nothing`做为返回类型能协助更精确地进行类型推导。  
	例如，在`if`语句中抛出异常：

	```scala
	scala> def num(n: Int) = if (n > 0) n else throw new Exception
	num: (n: Int)Int
	```

	抛出异常的语句返回值类型为`Nothing`，是任意类型的子类(也是`Int`的子类)，整条语句返回值类型被推导为`Int`。

- `Null`

	`Null`是所有引用类型`AnyRef`的子类型。  
	`Null`特质拥有唯一实例`null`(类似于`Java`中`null`的作用)。

### *Option* (可空类型)
`Option[T]`表示可空类型，`Option[T]`包含两个子类：

- `Some[T]`，代表包含有效值。
- `None`，代表值不存在。

`Optionp[T]`类型的伴生对象中提供了`apply()`方法用于构建实例：

- 任意的非`null`值会得到`Some[T]`返回值。  
- `null`值会得到`None`返回值。

如下所示：

```scala
scala> Option(123)
res10: Option[Int] = Some(123)

scala> Option(null)
res11: Option[Null] = None
```

`Option[T]`类型常用方法如下所示：

```scala
sealed abstract class Option[+A] extends Product with Serializable {
  ...
  def isEmpty: Boolean
  def isDefined: Boolean
  def get: A
  final def getOrElse[B >: A](default: => B): B
  final def orElse[B >: A](alternative: => Option[B]): Option[B]
  final def foreach[U](f: A => U)
  final def map[B](f: A => B): Option[B]
  final def fold[B](ifEmpty: => B)(f: A => B): B
  final def exists(p: A => Boolean): Boolean
  final def forall(p: A => Boolean): Boolean
  final def contains[A1 >: A](elem: A1): Boolean
  ...
}
```

使用`get`方法获取值，目标值不存在时会触发异常。  
使用`getOrElse()`方法获取值，参数中需要传入备用的默认值，目标值不存在时将使用默认值做为返回结果。  
如下所示：

```scala
scala> val str1 = Option("test")
str1: Option[String] = Some(test)

scala> val str2 = Option.empty[String]
str2: Option[String] = None

scala> str1 getOrElse "Get Value Failed!"
res6: String = test

scala> str2 getOrElse "Get Value Failed!"
res7: String = Get Value Failed!
```

`foreach()`高阶函数会在值存在时应用操作：

```scala
scala> Option(123) foreach println
123 //有值时打印输出

scala> Option(null) foreach println  //无值时无输出
```

`map()`高阶函数用于将目标值映射到新的`Option`中。  
`fold()`高阶函数用于使用目标值执行表达式并输出返回结果，在目标值不存在时使用提供的值做为返回结果，提供的值需要与表达式返回结果类型相同。  
如下所示：

```scala
scala> Option("abc") map (_.length)
res4: Option[Int] = Some(3)

scala> Option.empty[Int] map (_.length)
res5: Option[Int] = None

scala> Option("abc").fold(0)(_.length)
res8: Int = 3 //目标值存在时输出表达式结果

scala> Option.empty[String].fold(0)(_.length)
res9: Int = 0 //目标值不存在时使用提供的值做为返回结果
```

可空类型也可以用于**模式匹配**中。  
如下所示：

```scala
object TestOption extends App {
  val l = Option(123) :: None :: Nil
  for (num <- l) num match {
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



## 类型系统
`Scala`是静态类型语言，具有强大的类型系统。

### 类型参数
定义类型时允许带有类型参数。

`Scala`中使用以下方式定义类型参数：

- 使用泛型语法，`class Xxx[T]/trait Xxx[T]`
- 使用`type`关键字定义未绑定到具体类型的**抽象类型**(`Abstract Type`)，`trait Xxx { type T }`

泛型语法类似于`Java/C#`，但在`Scala`中使用中括号`[]`代替尖括号`<>`。  
构建示例时需要将泛型参数替换为实际类型。  
如下所示：

```scala
scala> trait Xxx[T] { val t: T }
defined trait Xxx //定义带有泛型参数的类型

scala> val x = new Xxx[String] { val t = "t" }
x: Xxx[String] = $anon$1@7ca16520

scala> x.t
res1: String = t

scala> :type x
Xxx[String]
```

抽象类型与抽象成员类似，需要在构建实例时提供具体实现。  
如下所示：

```scala
scala> trait Xxx { type T; val t: T }
defined trait Xxx //定义带有抽象类型的类型

scala> val x = new Xxx { type T = String; val t = "t" }
x: Xxx{type T = String} = $anon$1@36acfcff

scala> x.t
res2: x.T = t

scala> :type x
Xxx{type T = String}
```

### 类型约束
定义类型参数时可以设置类型约束，用于限制传入的类型参数：

- `Upper Type Bounds` 上界(上层类型约束)，语法`T <: Xxx`
- `Lower Type Bounds` 下界(低级类型约束)，语法`T >: Xxx`

`Upper Type Bounds`用于限定类型参数为指定类型的**子类**。  
如下所示：

```scala
scala> trait Other
defined trait Other

scala> trait Base
defined trait Base

scala> trait Child extends Base
defined trait Child

scala> def test[T <: Base](t: T) = t
test: [T <: Base](t: T)T

scala> test[Base](null)
res1: Base = null

scala> test[Child](null)
res2: Child = null

scala> test[Other](null)
<console>:14: error: type arguments [Other] do not conform to method test's type parameter bounds [T <: Base]
       test[Other](null)
           ^
```

类型约束亦可用于类型定义，`class/trait`均支持该特性：

```scala
scala> class Test[T <: Base]
defined class Test

scala> new Test[Child]
res3: Test[Child] = Test@65b73689

scala> new Test[Other]
<console>:13: error: type arguments [Other] do not conform to class Test's type parameter bounds [T <: Base]
       val res1 =
           ^
<console>:14: error: type arguments [Other] do not conform to class Test's type parameter bounds [T <: Base]
       new Test[Other]
           ^

scala> trait Test[T <: Base]
defined trait Test

scala> new Test[Child] { }
res4: Test[Child] = $anon$1@7836c79

scala> new Test[Other] { }
<console>:13: error: type arguments [Other] do not conform to trait Test's type parameter bounds [T <: Base]
       val res3 =
           ^
<console>:14: error: type arguments [Other] do not conform to trait Test's type parameter bounds [T <: Base]
       new Test[Other] { }
           ^
```

`Lower Type Bounds`用于限定类型参数为另一类型的**父类**。  
如下所示：

```scala
scala> trait Other
defined trait Other

scala> trait Base
defined trait Base

scala> trait Child extends Base
defined trait Child

scala> def test[T >: Child](t: T) = t
test: [T >: Child](t: T)T

scala> test[Base](null)
res1: Base = null

scala> test[Child](null)
res2: Child = null

scala> test[Other](null)
<console>:14: error: type arguments [Other] do not conform to method test's type parameter bounds [T >: Child]
       test[Other](null)
           ^
```

使用`Lower Type Bounds`可以将传入的更细粒度的类型转换为更粗粒度的类型。

### *View Bounds* (视图界定)
`View Bounds`(视图界定)相比普通类型约束更加**宽松**，类型参数不必自身满足类型约束，仅需类型参数能被**隐式转换**为满足类型约束的类型。

视图界定语法为`T <% Xxx`，可用于方法定义与类型定义。  
与类型界定不同，**不存在**`T >% Xxx`这样的语法。  
如下所示：

```scala
scala> trait Other
defined trait Other

scala> trait Base
defined trait Base

scala> trait Child extends Base
defined trait Child

scala> def test[T <% Base](t: T) = t //使用视图界定会生成隐式参数表
test: [T](t: T)(implicit evidence$1: T => Base)T

scala> test[Child](null) //与上级类型约束类似，使用子类能够满足约束条件
res1: Child = null

scala> test[Other](null) //使用无关类型不能满足约束条件
<console>:14: error: No implicit view available from Other => Base.
       test[Other](null)
                  ^

scala> implicit def otherToChild(t: Other) = null: Child //定义隐式转换
otherToChild: (t: Other)Child

scala> test[Other](null) //提供符合要求的隐式转换后能够正常调用方法
res3: Other = null
```

实际上视图界定是隐式参数的语法糖，使用视图界定时会生成`implicit xxx: T => Xxx`形式的隐式参数表。  
不能带有有参构造器的`trait`类型**不能**使用视图界定特性。  
如下所示：

```scala
scala> class Test[T <% Base] //定义类型时使用视图界定
defined class Test

scala> trait Test[T <% Base] //特质无法使用视图界定特性
<console>:1: error: traits cannot have type parameters with context bounds `: ...' nor view bounds `<% ...'
       trait Test[T <% Base]
                            ^
```

### *Content Bounds*
`Content Bounds`(上下文界定)要求上下文中存在类型为`Xxx[T]`的隐式值。

上下文界定语法为`T: Xxx`，可用于方法定义与类型定义。  
如下所示：

```scala
scala> class Xxx[T]
defined class Xxx

scala> def test[T: Xxx] = null //上下文界定用于方法类型参数，生成隐式参数表
test: [T](implicit evidence$1: Xxx[T])Null

scala> class Test[T: Xxx] //上下文界定用于类型定义
defined class Test

scala> test[Int] //调用方法出错，缺少符合要求隐式值
<console>:14: error: could not find implicit value for evidence parameter of type Xxx[Int]
       test[Int]
           ^

scala> new Test[Int] //构建实例出错，缺少符合要求隐式值
<console>:14: error: could not find implicit value for evidence parameter of type Xxx[Int]
       new Test[Int]
       ^

scala> implicit object XxxInt extends Xxx[Int] //提供隐式值
defined object XxxInt

scala> test[Int] //正常调用
res1: Null = null

scala> new Test[Int] //正常构建实例
res2: Test[Int] = Test@62640933
```

与视图界定类似，上下文界定亦是隐式参数的语法糖，使用上下文界定会生成`implicit xxx: Xxx[T]`的隐式参数表。  
不能带有有参构造器的`trait`类型**不能**使用上下文界定特性。  
如下所示：

```scala
scala> trait Test[T: Xxx]
<console>:1: error: traits cannot have type parameters with context bounds `: ...' nor view bounds `<% ...'
trait Test[T: Xxx]
                  ^
```

上下文界定生成的隐式参数表中的隐式参数名称有编译器合成，无法直接通过参数名称访问该隐式值。  
获取隐式值需要使用`Predef`包中定义的`implicitly[T]()`方法。  
如下所示：

```scala
scala> def test[T: Seq] = println(implicitly[Seq[T]]) //打印获取到的隐式值
test: [T](implicit evidence$1: Seq[T])Unit

scala> implicit val seq = Seq(6, 6, 6) //提供隐式值
seq: Seq[Int] = List(6, 6, 6)

scala> test[Int] //调用使用了上下文界定的方法，输出隐式值
List(6, 6, 6)
```

### *Variances* (型变)
泛型类型在使用不同类型参数时默认**不存在**继承关系。  
如下所示：

```scala
scala> import scala.reflect.runtime.universe._
import scala.reflect.runtime.universe._

scala> class Test[T]
defined class Test

scala> class Base
defined class Base

scala> class Child extends Base
defined class Child

scala> typeOf[Test[Base]] =:= typeOf[Test[Child]]
res1: Boolean = false //带有不同类型参数的泛型类是不相等的类型

scala> typeOf[Test[Base]] <:< typeOf[Test[Child]]
res2: Boolean = false //类型参数的继承关系不影响泛型类型自身
```

使用`variances`特性可使类型参数的继承关系扩展到承载类型参数的泛型类型自身。  
`variances`特性分为`covariance`(协变)和`contravariance`(逆变)。  
型变特性语法如下所示：

```scala
class Test[T] //invariance，无型变
class Test[+T] //covariance，协变
class Test[-T] //contravariance，逆变
```

- `Covariance` (协变)

	类型参数声明为`covariance`(协变)时，泛型类型的继承关系与类型参数相同。  
	如下所示：

	```scala
	scala> class Test[+T] //定义带有协变类型参数的泛型类型
	defined class Test

	scala> typeOf[Child] <:< typeOf[Base]
	res3: Boolean = true

	scala> typeOf[Test[Child]] <:< typeOf[Test[Base]]
	res4: Boolean = true //泛型类型的继承关系与类型参数相同
	```

	带有协变类型参数的泛型类型用于方法参数/返回值中，使方法能接受/返回带有子类类型参数的泛型类型。  
	如下所示：

	```scala
	scala> class Test[T]
	defined class Test

	scala> def test(t: Test[Base]) = t.toString
	test: (t: Test[Base])String

	scala> test(new Test[Child]) //泛型类型的参数不支持协变，报错
	<console>:18: error: type mismatch;
	 found   : Test[Child]
	 required: Test[Base]
	Note: Child <: Base, but class Test is invariant in type T.
	You may wish to define T as +T instead. (SLS 4.5)
	       test(new Test[Child])
	            ^

	scala> def test: Test[Base] = new Test[Child]
	<console>:17: error: type mismatch;
	 found   : Test[Child]
	 required: Test[Base]
	Note: Child <: Base, but class Test is invariant in type T.
	You may wish to define T as +T instead. (SLS 4.5)
	       def test: Test[Base] = new Test[Child]
	                              ^

	scala> class Test[+T]
	defined class Test

	scala> def test(t: Test[Child]) = t.toString
	test: (t: Test[Child])String

	scala> test(new Test[Child]) //正常调用方法
	res5: String = Test@61fbec8a

	scala> def test: Test[Base] = new Test[Child]
	test: Test[Base]
	```

- `Contravariance` (逆变)

	类型参数声明为`contravariance`(逆变)时，泛型类型的继承关系与类型参数相反。  
	如下所示：

	```scala
	scala> class Test[-T] //定义带有逆变类型参数的泛型类型
	defined class Test

	scala> typeOf[Child] <:< typeOf[Base]
	res6: Boolean = true

	scala> typeOf[Test[Base]] <:< typeOf[Test[Child]]
	res7: Boolean = true //泛型类型的继承关系与类型参数相反
	```

协变与逆变的类型参数需要在正确的位置使用，即`covariant position`(协变点)和`contravariant position`(逆变点)。

- `Covariant Position` (协变点)

	协变点指方法的**返回值**位置。  
	根据**里氏替换原则**，子类的方法返回值应比父类更具体。

- `Contravariant Position` (逆变点)

	逆变点指方法的**参数**位置。  
	根据**里氏替换原则**，能通过父类实例调用的方法一定能通过子类实例调用，因此子类方法参数类型接收范围应比父类更广。

在错误的位置使用型变类型参数会导致编译错误：

```scala
scala> trait Test[+T] { def test(t: T) } 
<console>:14: error: covariant type T occurs in contravariant position in type T of value t
       trait Test[+T] { def test(t: T) }
                                 ^

scala> trait Test[+T] { def test: T } 
defined trait Test

scala> trait Test[-T] { def test: T } 
<console>:14: error: contravariant type T occurs in covariant position in type => T of method test
       trait Test[-T] { def test: T }
                            ^

scala> trait Test[-T] { def test(t: T) } 
defined trait Test
```

### *Higer Kinded Type* (高阶类型)
高阶类型是对类型的高级抽象，是类型参数为类型构造器的泛型类型。  
如下所示：

```scala
scala> import scala.language.higherKinds
import scala.language.higherKinds

scala> class Test[T[_]]
defined class Test
```

类型`Test`接收一个类型为`T[_]`的类型参数，仅能使用泛型类型做为类型参数：

```scala
scala> new Test[Int] //使用普通类型做为类型参数，报错
<console>:14: error: Int takes no type parameters, expected: one
       new Test[Int]
                ^

scala> new Test[Seq] //使用泛型类型为类型参数，正确
res1: Test[Seq] = Test@11cc9e1e
```

`Type Theory`(类型理论)中的`Kind`(类型)在`Scala`中的对应概念：

| 类型 | 含义 | Scala中的对应概念 | 实例 |
|:---:|:----:|:--------------:|:----:|
| * | 类型 | 普通类型，或带有具体类型参数的泛型类型 | `Int`, `List[Int]` |
| * -> * | 一阶类型(类型构造器) | 泛型类型 | `List[_]`, `Seq[_]` |
| * -> ... -> * | 一阶类型(带有多个参数的类型构造器)| 带有多个类型参数的泛型类型 | `Map[_, _]`, `Function2[_, _, _]`, `Tuple4[_, _, _, _]` |
| (* -> *) -> * | 高阶类型(参数为类型构造器的类型构造器)| 带有泛型类型参数的泛型类型 | `List[T[_]]`, `Seq[T[_]]` |



## *continue* 与 *break*
`Scala`**没有**提供主流语言中的`continue`和`break`关键字用于流程控制。

其它语言中的`continue`功能可以通过`for`语句条件后添加`if`判断条件实现或使用**守卫**。  
`break`功能可以由`scala.util.control.Breaks`类提供。

- `Breaks`类中定义了`breakable()`和`break()`成员方法如下所示：

	```scala
	def breakable(op: => Unit): Unit {
	  try op catch {
	    // 判断异常是否为breakException，是则捕获，其它异常则继续向外传递
	    case ex: BreakControl => if (ex ne breakException) throw ex
	  }
	}
	def break(): Nothing = { throw breakException }
	```

	由代码可知，`breakable()`方法接收传名参数`op`，捕获`breakException`异常。  
	`break()`方法产生`breakException`异常。

	将需要使用break的循环代码块作为传名参数`op`传入`breakable()`方法中，`op`代码块中调用`break()`产生`breakException`异常被捕获，中断函数，达到跳出循环的目的。

	使用`Breaks`，如下所示：

	```scala
	import scala.util.control.Breaks.{breakable, break}

	object Main extends App {

	  breakable {
	    //使用break的代码块作为传名参数传入breakable中
	    for (i <- 1 to 10) {
	      if (i == 8) break		//跳出循环
	    }
	  }

	}
	```



## *Pattern Matching* (模式匹配)
**模式匹配**是`Scala`的核心功能之一。  
`Scala`的**模式匹配**提供了诸多强大的特性，主要功能如下：

- 跳转表(类似与主流语言中的`switch`语句)
- 类型匹配
- 条件执行
- 解构(`destructuring`)

### 简单匹配
**模式匹配**能够提供与其他语言中`switch`语句类似的简单匹配功能。

使用`match`关键字开始一个模式匹配语句。  
使用`case`关键字添加一个匹配值。

基本语法如下所示：

```scala
变量 match {
  case 条件1 => ...
  case 条件2 => ...
  ...
  case _ => ...
}
```

`Scala`中的`match`语句具有返回值，可为变量赋值。  
`Scala`中没有`break`关键字，`match`语句中的`case`条件不会被穿越。  
某些需要穿越`case`条件的情形，应使用`|`操作符连接多个条件。

每个`case`条件语句可以使用`@`操作符绑定一个变量名。  
每个`case`条件之后可以添加**守卫**(`if 条件语句...`)，用于添加额外的匹配条件。

如下所示：

```scala
object Main extends App {

  val (str0, str1, str2, str3, str4) = ("str0", "str1", "str2", "xxxx", "")

  def switch(str: String) = {
    print(s"String: $str => ")
    str match {
      case "str0" => println("Match case str0"); 0
      case "str1" | "str2" => println("Match case str1 | str2"); 1 //使用 | 操作符连接多个模式匹配条件
      case s@_ if s.length > 3 => //使用 @ 操作符指代整个匹配条件，使用 if 添加守卫
        println("Match case which string's length is larger then 3"); s.length
      case s@("a" | "bb" | "cccc") => s.length //使用 @ 指代多个匹配条件
      case _ => println("No match"); -1
    }
  }

  val re0 = switch(str0) //case语句后的最后一句做会做为整个match表达式的返回值
  val re1 = switch(str1)
  val re2 = switch(str2)
  val re3 = switch(str3)
  val re4 = switch(str4)

  println()

  print(
    s"""|str0 return $re0
        |str1 return $re1
        |str2 return $re2
        |str3 return $re3
        |str4 return $re4
        |""".stripMargin
  )

}
```

输出结果：

```
String: str0 => Match case str0
String: str1 => Match case str1 | str2
String: str2 => Match case str1 | str2
String: xxxx => Match case which string's length is larger then 3
String:  => No match

str0 return 0
str1 return 1
str2 return 1
str3 return 4
str4 return -1
```

### 类型匹配
**模式匹配**可用于匹配对象的实际类型。

对于以基类传入的对象实例，使用模式匹配可以匹配其真实类型。  
如下所示：

```scala
object Main extends App {

  class Language(val name: String)

  class Cpp extends Language("C++")
  class CSharp extends Language("C#")
  class Haskell extends Language("Haskell")
  class Scala(val scala: String = "Scala is best!") extends Language("Scala")
  class Java extends Language("Java")

  def typeMatch(lang: Any) = lang match {
    case s: Scala => println(s.scala)
    case _: CSharp | _: Cpp => println("Match C# or CPP!") //匹配多种类型
    case l: Language => println(s"Other language: ${l.name}")
    case _ => println("No match!")
  }

  typeMatch(new Scala)
  typeMatch(new Cpp)
  typeMatch(new CSharp)
  typeMatch(new Haskell)
  typeMatch(new Java)
  typeMatch(null)

}
```

输出结果：

```
Scala is best!
Match C# or CPP!
Match C# or CPP!
Other language: Haskell
Other language: Java
No match!
```

当模式匹配匹配泛型类型时，由于`JVM`采用`Type Erasure`的方式实现泛型，因而泛型类型的泛型参数无法准确匹配。  
如下所示：

```scala
object Main extends App {

  val list = 1 :: 2 :: 3 :: Nil // list实际类型为List[Int]

  list match {
    case _: List[String] => println("Match type: List[String]")
    case _: List[Int] => println("Match type: List[Int]")
    case _ => println("No match!")
  }

}
```

输出结果：

```
Match type: List[String]
```

由输出结果可知，模式匹配并未正确匹配类型的泛型参数。  
对于此类情况，`Scala`编译器在编译时会对代码做出警告。

### 解构
**模式匹配**可用于解构任意定义了`unapply()`方法的类型。

常见的数据结构如**元组**、`List[T]`等均支持解构操作。  
解构元组、`List[T]`：

```scala
scala> def destruct(obj: Any) =
     | obj match {
     |   case first :: second :: _ => println(s"Match list: $first, $second, ...")
     |   case (first, second) => println(s"Match tuple: $first, $second")
     | }
destruct: (obj: Any)Unit

scala> destruct { 1 :: 2 :: 3 :: Nil }
Match list: 1, 2, ...

scala> destruct (1, 2)
Match tuple: 1, 2

scala> destruct (1, 2, 3)
scala.MatchError: (1,2,3) (of class scala.Tuple3) //元组数目不匹配，出错
  at .destruct(<console>:14)
  ... 27 elided
```

亦可使用`Case Class`(样例类)特性定义为模式匹配优化的类，样例类会自动生成用于解构的`unapply()`方法。  
解构样例类：

```scala
scala> case class User(name: String, age: Int)
defined class User

scala> case class Manager(name: String, right: Int)
defined class Manager

scala> def destruct(obj: Any) =
     | obj match {
     |   case User(name, age) => println(s"User name: $name, age: $age")
     |   case Manager(name, right) => println(s"Manager name: $name, right: $right")
     | }
destruct: (obj: Any)Unit

scala> destruct(User("Dainslef", 25))
User name: Dainslef, age: 25

scala> destruct(Manager("Dainslef", 2333))
Manager name: Dainslef, right: 2333
```

解构类型时，亦可使用**值匹配**(多个候选值同样使用`|`操作符连接)，还可使用`@`操作符指代匹配表达式/子表达式。  
如下所示：

```scala
scala> def destruct(obj: Any) = obj match {
     |   case m@Manager("A" | "B", _) => m.toString //解构表达式中匹配多个值，使用 @ 指代整个匹配表达式
     |   case User(_, age@(10 | 20 | 30)) => s"Age: $age" //使用 @ 指代局部匹配表达式
     | }
destruct: (obj: Any)String
```



## *sealed* 和 *final* 关键字
`sealed`和`final`都是`Scala`语言的**关键字**。

- `final`关键字作用与`Java`中相同：

	`final`用在类之前，表示类不可继承；  
	`final`用在方法之前，表示方法不可被重写。

- `sealed`关键字作用与`C#`中的`sealed`不同：

	在Scala中，`sealed`的作用是防止继承被滥用。  
	`sealed`修饰的类其子类定义需要与该类在统一文件中。

### *sealed* 用于模式匹配
使用`sealed`关键字修饰的类型用于模式匹配时，编译器会对匹配条件进行检查。  
若匹配路径没有被完全覆盖，则会给出警告。  
如下所示：

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

`StringLike`类型提供了一系列方便强大的字符操作方法，格式化字符串可以使用其提供的`format()`方法(使用方式类似于静态方法`String.format()`，但使用方法调用者作为格式化内容而非方法的首个参数)。  
如下所示：

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
在`Scala 2.10`之后，还可以使用字符串插值器`s""`，基本用法如下所示：

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

如下所示：

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
scala> list foreach println
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
在`Scala`中，没有语言级别的枚举类型，枚举的功能可以通过**继承**枚举类`Enumeration`实现。

### 继承枚举类
继承枚举类`Enumeration`可以在成员中使用无参方法`Value`给每个枚举成员赋值。  
默认的`Value`方法会按**变量名**生成**枚举名**和并自动从`0`开始生成**枚举ID**，若需要手动设定枚举名称和枚举ID则可以使用`Value`方法的重载`Value(id: Int, name: Strig)`。

如下所示：

```scala
object Color extends Enumeration {

  // 自动赋值枚举成员
  val Red, Green, Blue = Value
  /*
  * 相当于分别初始化：
  * val Red = Value
  * val Green = Value
  * val Blue = Value
  */

  // 手动使用 Value(id: Int, name: String) 方法手动进行id和name的设置
  // 使用重载有參版本的Value(id: Int, name: String)不能一次性给多个枚举成员赋值，会编译报错(id冲突)
  val White = Value(100, "white")
  val Black = Value(200, "black")

}

object TestEnumeration extends App {

  Color.values foreach { color => 
    println(s"ID: ${color.id}, Str: $color")
  }

}
```

输出结果：

```
ID: 0, Str: Red
ID: 1, Str: Green
ID: 2, Str: Blue
ID: 100, Str: white
ID: 200, Str: black
```

`Enumeration`类的默认构造方法带有一个`Int`类型参数，用于指定枚举ID的**起始大小**，如下所示：

```scala
object Color extends Enumeration(100) {
  val Red, Green, Blue, White, Black = Value //枚举Id将从100开始
}

object Main extends App {

  Color.values foreach { color =>
    println(s"ID: ${color.id}, Str: $color")
  }

}
```

输出结果：

```
ID: 100, Str: Red
ID: 101, Str: Green
ID: 102, Str: Blue
ID: 103, Str: White
ID: 104, Str: Black
```

### 访问枚举内容
枚举单例支持以多种形式访问：

- 通过枚举成员访问，类似于其它常见编程语言(`Enum.member`)
- 通过枚举ID进行访问，语法类似数组(`Enum(id)`)
- 通过枚举名称进行访问，使用`withName`成员方法(`Enum withName "xxx"`)

枚举内部的成员全部保存在一个`Set`容器中，可使用`values`成员方法访问。

以前文中的`Color`单例对象为例，使用多种方式访问枚举内容，如下所示：

```scala
object Color extends Enumeration {
  val Red, Green, Blue = Value
  val White = Value(100, "white")
  val Black = Value(200, "black")
}

object Main extends App {

  def showEnum(color: Color.Value) = println(s"ID: ${color.id}, Str: $color")

  // 通过枚举ID访问枚举
  showEnum(Color(0))
  showEnum(Color(100))

  println()

  // 通过枚举名称访问枚举
  showEnum(Color withName "Green")
  showEnum(Color withName "black")

  println()

  // 遍历枚举内容
  Color.values foreach showEnum
}
```

输出结果：

```
ID: 0, Str: Red
ID: 100, Str: white

ID: 1, Str: Green
ID: 200, Str: black

ID: 0, Str: Red
ID: 1, Str: Green
ID: 2, Str: Blue
ID: 100, Str: white
ID: 200, Str: black
```

### 调用枚举类型
继承了枚举类的单例对象名并**不能**直接用于表示枚举类型。  
对应的枚举类型应使用对象内部定义的抽象类型`Value`来表示，即`单例对象名称.Value`。

以前文中的`Color`单例对象为例，对应的枚举类型应使用`Color.Value`表示。  
将枚举做为参数传递，如下所示：

```scala
object Color extends Enumeration {
  val Red, Green, Blue = Value
  val White = Value(100, "white")
  val Black = Value(200, "black")
}

object Main extends App {
  // Xxx.Value才是真正的枚举类型
  def showEnum(color: Color.Value) = println(s"ID: ${color.id}, Str: $color")
  showEnum(Color.blue)
  showEnum(Color.white)
}
```

输出结果：

```
ID: 2, Str: Blue
ID: 100, Str: white
```

### 限定枚举类型
`Scala`通过使用单例继承`Enumeration`类来提供枚举功能，**枚举值**的类型实际为`单例.Value`。  
由于`Scala`中每个实例的内部类的类型均**不相同**，需要使用**类型投影**来表示通用的枚举类型。  
**枚举值**的类型投影为`Enumeration#Value`。  
在泛型方法中，可以使用泛型约束`T <: Enumeration#Value`来限定泛型参数为枚举类型。  
如下所示：

```scala
scala> def testEnum[T <: Enumeration#Value](enum: T) = println(enum) //打印枚举参数名称
testEnum: [T <: Enumeration#Value](enum: T)Unit

scala> object Enum extends Enumeration { val enum0, enum1  = Value }
defined object Enum

scala> testEnum(Enum.enum0) //传入枚举类型参数
enum0

scala> testEnum(Enum.enum1)
enum1

scala> testEnum(123) //使用其它类型不满足泛型约束，报错
<console>:13: error: inferred type arguments [Int] do not conform to method testEnum's type parameter bounds [T <: Enumeration#Value]
       testEnum(123)
       ^
<console>:13: error: type mismatch;
 found   : Int(123)
 required: T
       testEnum(123)
                ^
```

通过构建特定的枚举基类，可以实现限定**指定类别**的枚举。  
如下所示：

```scala
scala> class MyEnumeration extends Enumeration //自定义枚举基类
defined class MyEnumeration

scala> def testMyEnum[T <: MyEnumeration#Value](enum: T) = println(enum) //限定枚举从自定义基类MyEnumeration中继承
testMyEnum: [T <: MyEnumeration#Value](enum: T)Unit

scala> object Enum extends Enumeration { val enum0, enum1  = Value } //普通枚举
defined object Enum

scala> object MyEnum extends MyEnumeration { val enum0, enum1  = Value } //从自定义基类MyEnumeration继承的枚举
defined object MyEnum

scala> testMyEnum(MyEnum.enum0) //参数为从自定义枚举基类MyEnumeration继承的枚举单例的枚举值，正常
enum0

scala> testMyEnum(MyEnum.enum1)
enum1

scala> testMyEnum(Enum.enum1) //参数为普通枚举单例的枚举值，错误
<console>:14: error: inferred type arguments [Enum.Value] do not conform to method testMyEnum's type parameter bounds [T <: MyEnumeration#Value]
       testMyEnum(Enum.enum1)
       ^
<console>:14: error: type mismatch;
 found   : Enum.Value
 required: T
       testMyEnum(Enum.enum1)
                       ^
```



## 基础数据结构
Scala常用的基础结构包括**数组**和**元组**。

### 定长数组
在Scala中定长数组使用`Array[T]`进行表示，定长数组与Java中概念类似。

构建一个固定长度的数组如下所示：

```scala
scala> val array = new Array[Int](10) //构建一个长度为10的Int型数组
array: Array[Int] = Array(0, 0, 0, 0, 0, 0, 0, 0, 0, 0)
scala> val a = Array(100, 200) //使用伴生对象的apply()方法创建数组
a: Array[Int] = Array(100, 200)
scala> array(5) //获取数组中指定位置的值(使用小括号中加偏移量)
res1: Int = 0
scala> array(5) = 10 //给指定位置的元素赋值
scala> array //查看赋值结果
res2: Array[Int] = Array(0, 0, 0, 0, 0, 10, 0, 0, 0, 0)
scala> array(100) //数组访问越界会抛出异常
java.lang.ArrayIndexOutOfBoundsException: 100
  ... 33 elided
```

### *Tuple* (元组)
元组是最简单的容器，无需额外的类型名称，直接使用`(value1, value2, value3, ...)`就可以构建出一个元祖。如下所示：

```scala
scala> val tuple = (1, 2, 3)
tuple: (Int, Int, Int) = (1,2,3)
```

元组中允许包含**重复**的值，也允许不同类型的值，但元组一经创建，内容便不可改变。

元组**不支持**直接使用`for`循环进行遍历。  
`Tuple`类型混入了`scala.Product`特质，可以使用无参方法`productIterator`获取可迭代的对象用于遍历。  
如下所示：

```scala
for (t <- tuple.productIterator) println(t) //命令式遍历
tuple.productIterator foreach println //函数式遍历
```

元组可以通过`元组对象._索引号`的形式访问。元组下标从`1`开始而非`0`，如下所示：

```scala
scala> println(tuple._1 + " " + tuple._2 + " " + tuple._3)
1 2 3
```

元组可以用来一次性初始化多个变量：

```scala
scala> val (a, b, c) = tuple //等价于 val (a, b, c) = (1, 2, 3)
a: Int = 1
b: Int = 2
c: Int = 3
scala> println(s"$a $b $c")
1 2 3
```

元组可以包含**不同**的类型：

```scala
scala> val (num, str) = (123, "456")
num: Int = 123
str: String = 456
```

元组用作函数返回类型时，即可让一个函数拥有多个返回值，如下所示：

```scala
object TestTuple extends App {
  def getNum(num1: Int, num2: Int, num3: Int) = (num1, num2, num3)
  val (num1, num2, num3) = getNum(1, 2, 3)
  println(s"$num1 $num2 $num3")
}
```

输出结果：

```
1 2 3
```

当一个方法的参数表中仅包含**单个元组**时，调用方法时可省略元组外部括号，在**柯里化**情形下同样有效，如下所示：

```scala
def add(n1: (Int, Int, Int))(n2: (Int, Int)) = n1._1 + n1._2 + n1._3 + n2._1 + n2._2
add(1, 2, 3)(4, 5) //参数直接传入，无需外部括号
```



## 容器
Scala的容器按数据结构分为`序列(Seq)`、`集合(Set)`和`映射(Map)`三大类。

- `序列(Seq)`

	有序容器，按照元素添加的顺序排列。  
	`Seq`的子类`IndexedSeq`允许类似数组的方式按照下标进行访问。

- `集合(Set)`

	数学意义上的集合，不包含重复元素。  
	`Set`的子类`SortedSet`中元素以某种顺序排序。

- `映射(Map)`

	`键 - 值`对偶的集合。  
	`Map`的子类`SortedMap`中键值以某种顺序排序。

基本的集合类型继承树如下所示：

```
Traversable
│
Iterable
├── Seq
│    ├── IndexedSeq
│    └── LinearSeq
├── Set
│    ├── SortedSet
│    └── BitSet
└── Map
     └── SortedMap
```

### 容器可变性
容器按照是否**可变**分为：

- **不可变容器**`scala.collection.immmutable._`
- **可变容器**`scala.collection.mutable._`。

`Scala`为函数式语言，默认的容器类型使用**不可变**实现。

### *List* (列表)
在Scala中，`List[T]`类型的完整包路径为`scala.collection.immutable.List`，继承于`Seq`。  
List为**不可变对象**，可以使用`for`操作符进行遍历。

构建一个列表：

```scala
scala> val list0 = List(1, 2, 3)
list0: List[Int] = List(1, 2, 3)
```

除了直接使用`List`单例提供的`apply()`方法构建列表对象之外，还可以使用`::`操作符来将多个值构成列表。  
`::`操作符为**右结合性**运算符。  
使用`::`操作符构成列表时，列表的最后一个值必须为`Nil`，如下所示：

```scala
scala> val list1 = 0 :: 1 :: 2 :: 3 :: Nil
list1: List[Int] = List(0, 1, 2, 3)
```

列表同样允许不同类型的值，也允许重复的值，如下所示：

```scala
scala> val list2 = 1 :: 1 :: "str" :: 2.0 :: Nil
list2: List[Any] = List(1, 1, str, 2.0)
```

若列表中存储的若是相同的类型，则编译器会将`List[T]`推导为具体的类型。  
若列表中成员类型各不相同，则编译器会使用所有类型的基类`Any`作为泛型类型即`List[Any]`。

列表支持从已有的列表进行创建：

```scala
scala> val list0 = 1 :: 2 :: 3 :: Nil
list0: List[Int] = List(1, 2, 3)
scala> val list1 = 0 :: list0 //向列表头部增加元素
list1: List[Int] = List(0, 1, 2, 3)
scala> val list2 = list0 :: 4 //列表不能从尾部添加元素(List以Nil结尾)
<console>:11: error: value :: is not a member of Int
  val list2 = list0 :: 4
                    ^
```

使用`:::`运算符可以叠加两个列表：

```scala
scala> val list2 = list0 ::: list1
list2: List[Int] = List(1, 2, 3, 0, 1, 2, 3)
```

也可以使用`++`运算符连接两个列表：

```
scala> val list3 = list0 ++ list1
list3: List[Int] = List(1, 2, 3, 0, 1, 2, 3)
```

`:::`与`++`对于列表而言，作用完全相同。  
`:::`是`List`类型特有的运算符，`++`继承于特质`TraversableLike`，也可用于一些其它的集合类型。

列表同样支持通过索引进行访问，语法与`Array[T]`类型类似：

```scala
scala> list0(0)
res0: Int = 1
```

### *ArrayBuffer* (变长数组)
在Scala中，变长数组使用`ArrayBuffer[T]`，完整路径`scala.collection.mutable.ArrayBuffer`，继承于`Seq`。  
Scala中的`ArrayBuffer`相当于Java中的`ArrayList`，可存储任意数量的元素。  
创建`ArrayBuffer`：

```scala
scala> val arrayBuffer = new ArrayBuffer[Int]
arrayBuffer: scala.collection.mutable.ArrayBuffer[Int] = ArrayBuffer()
val a = ArrayBuffer(100, 200)  //同样可以使用伴生对象的apply()方法创建ArrayBuffer
a: scala.collection.mutable.ArrayBuffer[Int] = ArrayBuffer(100, 200)
```

`ArrayBuffer`定义了方法`+=`和`-=`用于**增加**和**删除**元素：

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

需要注意的是，`+=`、`-=`只是**方法名**并不是**运算符**。  
`ArrayBuffer`没有提供`+`、`-`方法，以下的写法会**报错**：

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
scala> arrayBuffer.insert(1, -100) //在索引1的位置插入数值-100
scala> arrayBuffer
res17: scala.collection.mutable.ArrayBuffer[Int] = ArrayBuffer(10, -100, 100)
```

插入多个元素：

```scala
scala> arrayBuffer.insert(1, 7, 8, 9) //在索引1的位置插入数值7，8，9
scala> arrayBuffer
res19: scala.collection.mutable.ArrayBuffer[Int] = ArrayBuffer(10, 7, 8, 9, -100, 100)
```

删除操作类似，移除操作可以指定首尾进行**批量移除**：

```scala
scala> arrayBuffer.remove(1, 4)
scala> arrayBuffer
res21: scala.collection.mutable.ArrayBuffer[Int] = ArrayBuffer(10, 100)  //删除了索引1到4位之间的元素
```

需要注意的是，`ArrayBuffer`是**线性结构**，只有在尾部进行插入删除操作才是高效的，在其它位置进行的元素操作都会造成大量的元素移动。  
`ArrayBuffer`的不可变版本对应为`scala.collection.immutable.Vector`。

### *Set* (集合)
`Set[T]`类型为数学意义上的集合，集合内不允许重复元素。  
`Set`完整包路径为`scala.collection.immutable.Set`。  
集合同样允许任意类型的元素，但集合中不能包含重复的元素。

在使用`Set`类的`apply()`方法构建集合时，重复的元素会被忽略，如下所示：

```scala
scala> val set = Set(1, 1, 's', "str")
set: scala.collection.immutable.Set[Any] = Set(1, s, str) //重复的元素"1"被忽略了
```

`Set`可以使用`+`、`-`操作符来增加或是减少元素并返回新的集合。  
使用`+`、`-`操作符会返回新的集合，但原集合内的值不会发生改变，如下所示：

```scala
scala> val set1 = set + 3
set0: scala.collection.immutable.Set[Any] = Set(1, s, str, 3) //原集合添加元素输出新的集合

scala> set
res1: scala.collection.immutable.Set[Any] = Set(1, s, str) //原集合本身没有变化

scala> val set2 = set - 's'
set2: scala.collection.immutable.Set[Any] = Set(1, str) //从集合中移除一个元素

scala> set
res3: scala.collection.immutable.Set[Any] = Set(1, s, str)

scala> set + (1, 2, 3) //可直接添加元组
res4: scala.collection.immutable.Set[Any] = Set(s, 1, 2, str, 3)

scala> set - (1, 2, 3) //通过元组删除数据
res5: scala.collection.immutable.Set[Any] = Set(s, str)
```

当引用为变量时，`Set`可以使用`+=`、`-=`来增加或减少内部的元素：

```scala
scala> var set = Set(1, 2, 3)
set: scala.collection.immutable.Set[Int] = Set(1, 2, 3)

scala> set += 4 //增加元素"4"

scala> set
res6: scala.collection.immutable.Set[Int] = Set(1, 2, 3, 4)

scala> set -= 4 //移除元素"4"

scala> set
res7: scala.collection.immutable.Set[Int] = Set(1, 2, 3)
```

`Set`的`+=`、`-=`操作并非定义的方法，只是类似常规语言的操作符简写，如：

```scala
var set = Set(1, 2, 3)
set += 4
```

实际等价于：

```scala
var set = Set(1, 2, 3)
set = set + 4
```

对不可变类型的变量使用`+=`、`-=`操作，实际上改变了变量指向的实例。  
当不可变类型实例为**常量**时，则不能使用`+=`、`-=`操作，因为常量的实例指向不可变，如下所示：

```scala
scala> val set = Set(1, 2, 3)
set: scala.collection.immutable.Set[Int] = Set(1, 2, 3)

scala> set += 4
<console>:13: error: value += is not a member of scala.collection.immutable.Set[Int]
       set += 4
           ^
```

实际相当于：

```scala
scala> val set = Set(1, 2, 3)
set: scala.collection.immutable.Set[Int] = Set(1, 2, 3)

scala> set = set + 4
<console>:12: error: reassignment to val
       set = set + 4
           ^
```

`Set`支持数学意义上的交集、并集、差集等操作：

- 交集：

	```scala
	scala> Set(1, 2, 3) & Set(2, 5)
	res0: scala.collection.immutable.Set[Int] = Set(2)

	scala> Set(1, 2, 3) intersect Set(2, 5)
	res1: scala.collection.immutable.Set[Int] = Set(2)
	```

- 并集：

	```scala
	scala> Set(1, 2, 3) | Set(2, 5)
	res2: scala.collection.immutable.Set[Int] = Set(1, 2, 3, 5)

	scala> Set(1, 2, 3) ++ Set(2, 5)
	res3: scala.collection.immutable.Set[Int] = Set(1, 2, 3, 5)

	scala> Set(1, 2, 3) union Set(2, 5)
	res4: scala.collection.immutable.Set[Int] = Set(1, 2, 3, 5)
	```

- 差集：

	```scala
	scala> Set(1, 2, 3) &~ Set(2, 5)
	res5: scala.collection.immutable.Set[Int] = Set(1, 3)

	scala> Set(1, 2, 3) -- Set(2, 5)
	res6: scala.collection.immutable.Set[Int] = Set(1, 3)

	scala> Set(1, 2, 3) diff Set(2, 5)
	res7: scala.collection.immutable.Set[Int] = Set(1, 3)
	```

`scala.collection.immutable.Set`以哈希集实现，元素依据**HashCode**进行组织。

`Set`的相关类型有：

- `scala.collection.mutable.LinkedHashSet` 链式哈希集，依照插入的顺序排列
- `scala.collection.immutable.SortedSet` 红黑树实现的排序集

### *Map* (映射)
`Map[A, B]`类型的完整包路径为`scala.collection.immutable.Map`。  
映射中的每一个元素都是一组`对偶(Tuple2)`，分别为key和value，key不可重复。  
通过`->`操作符可以将两个值组成一组对偶，如下所示：

```scala
scala> var map = Map(1 -> "1", 2 -> "2", 3 -> "3")
map: scala.collection.immutable.Map[Int,String] = Map(1 -> 1, 2 -> 2, 3 -> 3)
scala> for ((key, value) <- map) println(s"key: $key value: $value")
key: 1 value: 1
key: 2 value: 2
key: 3 value: 3 //使用for循环遍历map
scala> for (value <- map.values) println(s"value: $value")
value: 1
value: 2
value: 3 //仅遍历map的value
scala> for (key <- map.keys) println(s"value: $key")
value: 1
value: 2
value: 3 //仅遍历map的key
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
scala> map  //更改的结果作为返回值输出，原本的Map值没有任何改变
res23: scala.collection.immutable.Map[Int,String] = Map(1 -> 1, 2 -> 2, 3 -> 3)
```

与`Set`类似，当实例字段为可变量时，`Map`也支持`+=`、`-=`操作。  

除了不可变的`scala.collection.immutable.Map`外，还有可变的`scala.collection.mutable.Map`类型。  
Scala还提供了多种不同结构的`Map`实现，如`HashMap`、`ListMap`、`LinkedHashMap`等。

### *GenTraversableLike*
`GenTraversableLike`特质定义了访问容器内头尾元素的方法：

```scala
trait GenTraversableLike[+A, +Repr] extends Any with GenTraversableOnce[A] with Parallelizable[A, parallel.ParIterable[A]] {
  ...
  def head: A //获取第一个元素，元素不存在时抛出NoSuchElementException
  def headOption: Option[A] //获取第一个元素的Option，元素不存在时为None值
  def tail: Repr //获取除了第一个元素之外的其余所有元素
  def last: A //获取最后一个元素，元素不存在时抛出异常
  def lastOption: Option[A] //获取最后一个元素的Option
  ...
}
```

多数容器都间接混入了`GenTraversableLike`特质，如`List`、`Seq`、`Vector`、`Map`等。  
对于混入了`GenTraversableLike`的类型且支持索引访问的类型，使用`xxx.head`比`xxx(0)`更符合Scala风格。

### 集合有序性
`Scala`默认`Set/Map`无论`mutable/immutable`均为**无序**。  
如下所示：

```scala
object Main extends App {

  val imSet = Set(1, 2, 3, 4, 5)
  val imMap = Map(
    1 -> 1,
    2 -> 2,
    3 -> 3,
    4 -> 4,
    5 -> 5
  )

  val muSet = collection.mutable.Set(1, 2, 3, 4, 5)
  val muMap = collection.mutable.Map(
    1 -> 1,
    2 -> 2,
    3 -> 3,
    4 -> 4,
    5 -> 5
  )

  println(s"Immutable Set: ${imSet.toString}")
  println(s"Immutable Map: ${imMap.toString}")
  println(s"Mutable Set: ${muSet.toString}")
  println(s"Mutable Map: ${muMap.toString}")

}
```

输出结果：(`Scala 2.12.2 && macOS 10.12.4`)

```
Immutable Set: Set(5, 1, 2, 3, 4)
Immutable Map: Map(5 -> 5, 1 -> 1, 2 -> 2, 3 -> 3, 4 -> 4)
Mutable Set: Set(1, 5, 2, 3, 4)
Mutable Map: Map(2 -> 2, 5 -> 5, 4 -> 4, 1 -> 1, 3 -> 3)
```

`Set/Map`存在特定规则的有序版本`SortedSet/SortedMap`。  
`SortedSet/SortedMap`在构造时需要提供`scala.math.Ordering[T]`特质用于决定内部成员的排序规则。  
`Scala`已实现了常见类型(`Int`、`String`等)的`Ordering`特质，使用常见类型时不必显式传入。

`immutable`容器存在有序类型`ListSet/ListMap`。  
`mutable`容器存在有序类型`LinkedHashSet/LinkedHashMap`，按照元素添加的顺序排列。  
如下所示：

```scala
object Main extends App {

  val imSet = collection.immutable.ListSet(1 to 10: _*)
  val imMap = collection.immutable.ListMap(
    1 -> 1,
    2 -> 2,
    3 -> 3,
    4 -> 4,
    5 -> 5
  )

  val muSet = collection.mutable.LinkedHashSet(1 to 10: _*)
  val muMap = collection.mutable.LinkedHashMap(
    1 -> 1,
    2 -> 2,
    3 -> 3,
    4 -> 4,
    5 -> 5
  )

  println(s"Immutable ListSet: ${imSet.toString}")
  println(s"Immutable ListMap: ${imMap.toString}")
  println(s"Mutable LinkedHashSet: ${muSet.toString}")
  println(s"Mutable LinkedHashMap: ${muMap.toString}")

}
```

输出结果：(`Scala 2.12.2 && macOS 10.12.4`)

```
Immutable ListSet: ListSet(1, 2, 3, 4, 5, 6, 7, 8, 9, 10)
Immutable ListMap: ListMap(1 -> 1, 2 -> 2, 3 -> 3, 4 -> 4, 5 -> 5)
Mutable LinkedHashSet: Set(1, 2, 3, 4, 5, 6, 7, 8, 9, 10)
Mutable LinkedHashMap: Map(1 -> 1, 2 -> 2, 3 -> 3, 4 -> 4, 5 -> 5)
```

`immutable`容器不存在`LinkedHashSet/LinkedHashMap`类型。  
`mutable`容器不存在`ListSet`类型，存在`ListMap`类型，但无序。

有序容器使用`toSet/toMap`等方法向无序容器转换，内部成员会重新变为**无序**。



## *Higher Order Function* (高阶函数)
**高阶函数**是**函数式编程**中的概念，在数学中，也叫做**算子**(运算符)或**泛函**。  
**接受一个或多个函数作为输入**或者**输出一个函数**的函数被称为高阶函数。

在`Scala`中，容器类提供了高阶函数作为容器数据操作的接口。  
常见的高阶函数有`map`、`reduce`、`flatMap`、`filter`、`find`、`fold`、`foreach`等。

### *for/yeild* 语句
`Scala`中同样提供了`yield`关键字，用于构建集合。  
`Scala`中的`yield`语句不是惰性生成，与传统语言的**生成器**概念不同。  
如下所示：

```scala
scala> for (i <- 1 to 5) yield i
res20: scala.collection.immutable.IndexedSeq[Int] = Vector(1, 2, 3, 4, 5)

// 使用for语句内置的守卫语法限制输出
scala> for (i <- 1 to 5 if i > 2) yield i
res21: scala.collection.immutable.IndexedSeq[Int] = Vector(3, 4, 5)

// 生成器的生成结果与被遍历的容器类型相关
scala> for (i <- 1 :: 2 :: 3 :: 4 :: 5 :: Nil if i > 2) yield i
res24: List[Int] = List(3, 4, 5)

// 生成的结果不是目标容器则可以进行转换
scala> (for (i <- List(1, 2, 3, 4, 5) if i > 2) yield i) toSet
res27: scala.collection.immutable.Set[Int] = Set(3, 4, 5)
```

`Scala`中的`for/yield`语句实际是高阶函数的语法糖，`yeild`语句可以还原为高阶函数的形式：

```scala
// 从1到5的数中找出偶数，并将数值翻倍

// 使用命令式编程风格，使用守卫和生成器
scala> for (i <- 1 to 5 if i % 2 == 0) yield i * 2
res13: scala.collection.immutable.IndexedSeq[Int] = Vector(4, 8)

// 使用函数式编程风格，使用高阶函数
scala> 1 to 5 filter { _ % 2 == 0 } map { _ * 2 }
res15: scala.collection.immutable.IndexedSeq[Int] = Vector(4, 8)
```



## *Exception* (异常)
`Scala`沿用了`Java`的异常机制，但相关语法略有不同。

- 抛出异常

	`Scala`同样使用`throw`语句抛出异常，与`Java`语法类似。如下所示：

	```scala
	throw new XxxException
	```

	`Java`中要求将方法内可能抛出的异常明确地在方法签名中列出，但在`Scala`中不需要。  
	
	对于需要被`Java`调用的`Scala`方法，可以使用`@throw`注解来标明方法中可能抛出的异常，使方法在`Java`端生成正确的签名：

	```scala
	@throw(classOf[XxxException])
	def testSException {
		throw new XxxExeption
	}
	```

	对应的`Java`代码：

	```java
	void testException() throw XxxException {
		throw new XxxExeption
	}
	```

- 捕获异常

	`Scala`中同样使用`try ... catch ... finally ...`语句进行异常捕获，但语法略有不同：

	1. 在`Scala`中，`catch`子句没有参数，直接在语句内部使用**模式匹配**进行异常捕获。  
		如下所示：

		```scala
		try {
			...
		} catch {
			case ex: Exception1 => ...
			case ex: Exception2 => ...
			... 
		}
		```

		对应`Java`代码：

		```java
		try {
			...
		} catch (Exception1 ex) {
			...
		} catch (Exception2 ex) {
			...
		}
		```

	1. 单条`try`语句可省略花括号，`try`语句可不带有`case`、`finally`单独存在。

		如下所示：

		```scala
		scala> try 2333
		<console>:12: warning: A try without a catch or finally is equivalent to putting its body in a block; no exceptions are handled.
		       try 2333
		       ^
		res9: Int = 2333 //有警告，但正常执行
		```

	1. `Scala`中的`try ... catch ... finally ...`语句具有返回值。

		使用返回值时，需要保证`try`语句以及`catch`子句中的每一个`case`拥有相同的返回值类型。  
		`finally`子句不做为返回值，也不影响返回值类型的推导。  
		如下所示：

		```scala
		scala> try 2333
		res9: Int = 2333 //try语句返回值

		scala> try 2333 catch { case _ => 666 }
		res10: Int = 2333 //try与case返回值类型相同时，正确推导出整条语句的返回值类型

		scala> try 2333 catch { case _ => "666" }
		res11: Any = 2333 //try与case返回值类型不同时，结果类型推导为Any

		scala> try 2333 catch { case _ => 666 } finally "666"
		res12: Int = 2333 //finally语句不影响try表达式结果类型
		```

### *scala.util.Try[T]*
从`Scala 2.10`开始，标准库中提供了`scala.util.Try[T]`类型对异常处理操作的抽象。  
`Try`类型的伴生对象中提供了接收传名参数的`apply()`方法，用于构建`Try`类型实例：

```scala
object Try {
  def apply[T](r: => T): Try[T] = ...
}
```

使用`Try`与普通的异常处理类似，将可能触发异常的语句包含在`Try`代码块中：

```scala
Try {
  ... //可能抛出异常的代码
}
```

泛型参数`T`即为代码块的返回值类型。

与`Option`类型的设计类似，`Try`类型拥有子类：

- `scala.util.Success[T]` 表示代码正常执行完毕，包含正常执行的结果
- `scala.util.Failure[T]` 表示代码执行中触发了异常，包含异常信息

`Try`类型也提供了与`Option`类型相似的高阶函数，常用方法定义如下：

```scala
sealed abstract class Try[+T] extends Product with Serializable {
  ...
  def get: T //获取语句块的执行结果
  def getOrElse[U >: T](default: => U): U //语句执行失败时使用给定的默认值做为返回结果
  def foreach[U](f: T => U): Unit //语句执行成功时执行函数f，否则不进行操作
  def map[U](f: T => U): Try[U] //以上一个操作的执行结果为入参执行下一个操作，同样返回Try类型
  def fold[U](fa: Throwable => U, fb: T => U): U
  def toOption: Option[T] //将语句块的执行结果转换为Option形式
  ...
}
```

使用`get`方法获取`Try`语句块的执行结果：

```scala
scala> Try { 123 } get
res5: Int = 123
```

若`Try`语句块触发了异常，则使用`get`方法获取执行结果同样抛出异常：

```scala
scala> Try { "Dainslef".toInt } get
java.lang.NumberFormatException: For input string: "Dainslef"
  at java.lang.NumberFormatException.forInputString(NumberFormatException.java:65)
  at java.lang.Integer.parseInt(Integer.java:580)
  at java.lang.Integer.parseInt(Integer.java:615)
  at scala.collection.immutable.StringLike.toInt(StringLike.scala:301)
  at scala.collection.immutable.StringLike.toInt$(StringLike.scala:301)
  at scala.collection.immutable.StringOps.toInt(StringOps.scala:29)
  at .$anonfun$res6$1(<console>:13)
  at scala.runtime.java8.JFunction0$mcI$sp.apply(JFunction0$mcI$sp.java:12)
  at scala.util.Try$.apply(Try.scala:209)
  ... 29 elided
```

可以使用`getOrElse()`方法在触发异常时提供默认值：

```scala
scala> Try { "Dainslef".toInt } getOrElse 233
res3: Int = 233
```

使用`foreach()`高阶函数在`Try`语句块执行成功时执行操作：

```scala
scala> Try { 123 } foreach println
123
```

在`Try`语句块执行失败时`foreach()`高阶函数不执行：

```scala
scala> Try { "Dainslef".toInt } foreach println //无输出

```

`fold()`高阶函数用法与`Option`类型类似，在`Try`语句块成功是执行成功表达式并输出返回结果，在`Try`语句块失败时执行失败表达式并返回结果，两类表达式返回结果类型需要相同。  
如下所示：

```scala
scala> Try { "Dainslef".toInt } fold (_ => "Failed", _ => "Success")
res10: String = Failed //执行失败

scala> Try { "Dainslef" } fold (_ => "Failed", _ => "Success")
res11: String = Success //执行成功
```

`toOption`方法用于将`Try[T]`语句块的执行结果转换为`Option[T]`类型，语句块执行成功得到`Some[T]`，执行失败得到`None`。  
如下所示：

```scala
scala> Try { "Dainslef".toInt } toOption
res1: Option[Int] = None //执行失败，得到 None

scala> Try { 233.3.toInt } toOption
res2: Option[Int] = Some(233) //执行成功，得到 Some(233)
```



## *Package* (包)
`Scala`中的包用法基本与`Java`类似：

- 使用`package`关键字定义包路径。
- 使用`import`关键字导入包路径。

### 包与路径
在`Scala`中，包路径是**逻辑概念**，源码文件**不必**按照包路径存放到对应的目录下。

`Scala`中使用`_`符号表示导入该路径下的所有包和成员：

```scala
import java.awt._ //等价于java中的 import java.awt.*
```

导入路径规则与`Java`中的类似，处于同一级包路径下的类可以直接使用不必导入。

- 导入策略

	在导入包时，`Scala`默认采用**相对路径**。  
	在外层路径的包使用内层路径的包时，可省略共同的路径部分直接以当前路径为起点访问内层路径包。

	如下所示：

	```scala
	// file1
	package com.dainslef

	class Test

	// file2
	package com

	// 导入路径时以当前包为起点，不必从最外层路径开始导入
	import dainslef.Test

	object Main extends App {
	  println(classOf[Test].getName)
	}
	```

	而在`Java`中，无论包的层次关系如何，都需要通过绝对路径进行导入。

	上例对应`Java`版本如下所示：

	```java
	// file1
	package com.dainslef;

	class Test {
	};

	// file2
	package com;

	// 导入路径时从时需要从最外层路径开始导入，不能写成 import dainslef.Test
	import com.dainslef.Test;

	public class Main {
	
		public static void main(String[] args) {
			System.out.println(Test.class.getName());
		}
	
	}
	```

- 默认包与绝对路径导入

	在`Java`和`Scala`中，不使用`package`关键字打包的代码即位于**默认包**下，没有对应的包名。  
	在`Scala`中使用`_root_`指代默认包。

	`Scala`中默认的`import`操作是基于相对路径的，但`Scala`同样支持以**绝对路径**进行`import`操作：

	- 以`_root_`为导入起始路径，即代表以绝对路径的形式导入内容。
	- 使用绝对路径访问内容能避免一些命名冲突。

	上例中的代码中的`Test`类以绝对路径导入，导入语句可写成：

	```scala
	import _root_.com.dainslef.Test
	```

- 默认包的限制

	默认包没有名称，其内容只能被同在默认包下的其它内容访问。  
	内层包无法访问外部默认包的内容，即使使用`_root_`访问绝对路径依旧无法访问。

	如下所示：

	```scala
	// file1
	// 定义单例在默认包中
	object Test {
	  val test = "Test string..."
	}

	// file2
	package com

	object Main extends App {
	  // 在内层包中访问外部默认包的内容
	  println(Test.test) //错误，提示 "not found: value Test"
	  println(_root_.Test.test) //错误，提示 "object Test is not a member of package <root>"
	}
	```

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
import java.lang.Math.abs //导入Math类中的静态方法abs
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
如下所示：

```scala
package object Package {
  var num0 = 0
  protected var num1 = 1
  private var num2 = 2
}

package Package {
  object Test extends App {
    println(num0) //正确，可以直接访问包对象的公有成员，不用使用前缀
    println(num1) //错误，不能访问包对象的保护成员
    println(num2) //错误，不能访问包对象的私有成员
  }
}
```

通常情况下，包对象的定义应放置在包路径下的`package.scala`文件中。



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
  import Implicit.intToImpl //当隐式转换没有定义在当前作用域也不在实例的伴生对象中时需要显式导入
  100.show //Int型被隐式转换为Implicit类型
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
  val impl1 = new Impl1
  impl1.test //实例由Impl1类型隐式转换成了Impl2类型
  impl1.show(impl1) //可以通过将实例隐式转换为Impl2类型来满足方法调用，但编译器实际执行的操作是将参数隐式转换成了Impl2类型
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
  implicit val impl = 200.0 //隐式值可以定义在伴生对象中
  def testImplicit(implicit num: Double) = println(num)
}

object Main extends App {
  import Implicit.impl //不在当前作用域中的隐式参数需要显式引入
  Implicit.testImplicit
}
```

输出结果：

```
200.0
```

**单例对象**定义时也可添加`implicit`关键字成为隐式值。  
如下所示：

```scala
object Main extends App {

  trait Base[T] { val value: T }
  implicit object Test extends Base[Int] { val value = 2333 } //以单例对象形式定义隐式类

  def testImplicit[T](implicit base: Base[T]) = println(base.value)

  testImplicit //无需参数调用隐式方法

}
```

输出结果：

```
2333
```

隐式参数的限制：

- 用于声明隐式参数的`implicit`关键字只能出现在参数表的最前端，隐式参数的声明对当前参数表内的**所有参数**有效。
- 使用柯里化定义多个参数表时，只能声明**最后一个**参数表内的参数为隐式参数。
- 一个隐式参数在被调用的作用域内存在多个匹配的同类型隐式值时，编译报错。

如下所示：

```scala
def testImplicit(implicit num0: Int, num1: Int) {} //正确。num0、num1，皆为隐式参数
def testImplicit(implicit num0: Int, implicit num1: Int) {} //错误。只能在参数表的首个参数前添加implicit关键字修饰
def testImplicit(num0: Int, implicit num1: Int) {} //错误。只能在参数表的首个参数前添加implicit关键字修饰

def testImplicit(num: Int)(implicit num0: Int, num1: Int) {} //正确。对于柯里化函数，最后一个参数表可以设为隐式参数
def testImplicit(implicit num0: Int)(implicit num1: Double) {} //错误。一个方法不允许拥有多个隐式参数表
def testImplicit(implicit num0: Int)(num1: Double) {} //错误。只有最后一个参数表可以设为隐式参数表
```

- 隐式参数与参数默认值

	隐式参数与参数默认值特性**可以**共存。

	当一个方法的所有隐式参数均带有默认值时，可以直接调用，如下所示：

	```scala
	object Main extends App {

	  // 方法带有默认参数以及参数默认值
	  def testImplicit(implicit num0: Int = 0, num1: Double = 0) = println(s"$num0 $num1")

	  // 直接调用，无需隐式参数
	  testImplicit
	}
	```

	输出结果：

	```
	0 0.0
	```

- 隐式参数与默认值的优先级

	- 当一个方法的隐式参数带有部分默认值时，隐式调用时只需提供没有默认值的部分参数。
	- 当一个隐式参数既有默认值又有隐式值时，会优先使用隐式值。

	如下所示：

	```scala
	object Main extends App {

	  def testImplicit(implicit num0: Int = 0, num1: Double) = println(s"$num0 $num1")

	  // 只需为没有默认值的参数提供隐式值
	  implicit val num1 = 2.0
	  testImplicit

	  // 此时num0既有隐式值，也有参数默认值
	  implicit val num0 = 1
	  testImplicit
	}
	```

	输出结果：

	```
	0 2.0
	1 2.0
	```

	输出结果说明第二次调用`testImplicit()`方法时，优先采用了隐式值而非参数默认值。

	隐式值与参数默认值在方法调用时区别如下：

	- 采用参数默认值时，即使参数全部拥有默认值，参数表不可省略(`()`操作符必须存在)。
	- 采用隐式值时，隐式参数全部具有隐式值或默认值时，参数表直接省略。

	当一个隐式参数表的所有参数均带有默认值且作用域内也拥有满足条件的隐式值时，调用方法时带有`()`操作符为使用默认值，省略参数表为使用隐式值。

	如下所示：

	```scala
	object Test extends App {

	  def testImplicit(implicit num0: Int = 0, num1: Double = 0) = println(s"$num0 $num1")

	  implicit val num0 = 1
	  implicit val num1 = 1.0

	  testImplicit //全部采用隐式值
	  testImplicit() //全部采用默认值
	}
	```

	输出结果：

	```
	1 1.0
	0 0.0
	```

### 隐式类
类定义前同样可以使用`implicit`成为**隐式类**。

- 隐式类的主构造器**有且只有**一个参数，同时，该参数**不能**为隐式参数。
- 隐式类的主构造器不能通过参数默认值、隐式参数等形式来模拟成参数表成只有一个参数的情况。
- 隐式类特性**不能**与样例类共存，即一个类在定义时不能同时带有`implicit`和`case`关键字。
- 隐式类**不能**定义在外部区域(包，以及包对象)，隐式类只能定义在类体、函数体、单例对象中。

与**隐式转换**类似，当一个实例调用了**不存在**或**无法访问**的成员方法，编译器会为之搜索作用域中可访问的隐式类。  
若隐式类的构造器参数与实例相同且带有实例调用的方法，则自动调用该隐式类的构造器。  
如下所示：

```scala
object Main extends App {

  case class Source(num: Int) {
    private def show = print(num)
  }

  implicit class Impl(source: Source) {
    def show = println("Implicit Class")
    def show(num: Int) = println(s"Implicit Class: $num")
  }

  Source(0).show //调用无法访问的成员方法可能触发隐式转换
  Source(0).show(100) //调用不存在的方法也能触发隐式转换
}
```

输出结果：

```
Implicit Class
Implicit Class: 100
```



## *TypeClass*
`Type Class`即**类型类**，是一种通过泛型参数实现多态的方式。  
根据不同的泛型参数，签名相同的方法会调用不同的实现。

Scala中使用**隐式参数**特性来实现TypeClass。  
定义一个带有泛型参数的类型(TypeClass)，和使用隐式参数接收该泛型实例的方法：

```scala
scala> trait TypeClass[T] {
     |   def doSomething(): Unit
     | }
defined trait TypeClass

scala> def testTypeClass[T]()(implicit typeClass: TypeClass[T]) = typeClass.doSomething()
testTypeClass: [T]()(implicit typeClass: TypeClass[T])Unit
```

使用隐式单例为TypeClass提供不同的实现：

```scala
scala> implicit object IntTypeClass extends TypeClass[Int] {
     |   def doSomething() = println("Int Type Class")
     | }
defined object IntTypeClass

scala> implicit object StringTypeClass extends TypeClass[String] {
     |   def doSomething() = println("String Type Class")
     | }
defined object StringTypeClass
```

调用`testTypeClass()`方法时，使用不同的泛型参数编译器会自动选择合适的隐式对象做为实现：

```scala
scala> testTypeClass[Int]()
Int Type Class

scala> testTypeClass[String]()
String Type Class

scala> testTypeClass[Double]() //使用未提供隐式实例的泛型参数时，报错
<console>:16: error: could not find implicit value for parameter typeClass: TypeClass[Double]
       testTypeClass[Double]()
                            ^
```

完整示例：

```scala
object Main extends App {

  trait TypeClass[T] {
    def doSomething(t: T): Unit
  }

  def testTypeClass[T]()(implicit typeClass: TypeClass[T]) = typeClass.doSomething()

  implicit object IntTypeClass extends TypeClass[Int] {
    def doSomething(t: T) = println(s"Int Type Class: $t")
  }

  implicit object StringTypeClass extends TypeClass[String] {
    def doSomething(t: T) = println(s"String Type Class: $t")
  }

  testTypeClass(233)
  testTypeClass("666")

}
```

输出结果：

```
Int Type Class
String Type Class
```

`C++`中的**模板特化**功能上亦与TypeClass类似。



## 求值策略
`Scala`中存在三种求值策略：

1. `Call by Value`，在表达式定义时立即求值，仅在定义时求值**一次**。
1. `Call by Name`，在表达式调用时求值，每次调用都会对表达式重新求值。
1. `Call bt Need`，在表达式首次调用时求值，仅在首次被访问时求值**一次**。

使用`val/var`定义字段时即为即为直接求值，字段值在定义时即被确定；  
使用`val/var`定义字段时若搭配`lazy`关键字，则字段在首次被访问时求值；  
使用`def`定义无参方法时即为传名调用，方法在调用时才会求值，且每次调用重新求值。  
如下所示：

```scala
object Main extends App {

  var num = 23333

  // 立即求值，test0 值为 23333
  val test0 = {
    println("Call test0")
    num
  }

  // 在调用表达式时才会进行求值，每次都求值
  def test1 = {
    println("Call test1")
    num
  }

  // 首次调用时求值，之后不再求值
  lazy val test2 = {
    println("Call test2")
    num
  }

  println(s"test0: $test0, test1: $test1")
  num = 44444
  println(s"test0: $test0, test1: $test1, test2: $test2")
  num = 66666
  println(s"test0: $test0, test1: $test1, test2: $test2")

}
```

输出结果：

```
Call test0
Call test1
test0: 23333, test1: 23333
Call test1
Call test2
test0: 23333, test1: 44444, test2: 44444
Call test1
test0: 23333, test1: 66666, test2: 44444
```

`Call by Value`的字段`test0`在定义时值已被确定，仅在定义时求值一次，三次输出结果相同；  
`Call by Name`的字段`test1`在每次调用时重新求值，三次输出结果不同；  
`Call by Need`的字段`test2`在首次被访问时进行求值，两次输出结果相同。

### 参数的求值策略
与大多数编程语言类似，`Scala`中的方法、函数的参数默认即为`Call by Value`，参数在传入时立即求值，如下所示：

```scala
object Main extends App {

  def show(num: Int) {
    println("Run show()!")
    println(s"num: $num")
  }

  show {
    println("Call show()!")
    23333
  }

}
```

输出结果：

```
Call show()!
Run show()!
num: 23333
```

做为参数的代码块在传入方法时便已被执行。

使用`By-name parameter`(**传名参数**)特性可以使方法参数变为`Call by Name`。  
传名参数语法为在类型前添加`=>`操作符，上述例子改用传名参数，如下所示：

```scala
object Main extends App {

  // 参数 num 为传名参数
  def show(num: => Int) {
    println("Run show()!")
    println(s"num: $num")
  }

  show {
    println("Call show()!")
    23333
  }

}
```

输出结果：

```
Run show()!
Call show()!
num: 23333
```

做为传名参数的代码块在传入方法时并未执行，在参数被访问时才真正执行。

### **&&**、**||** 运算符
在传统编程语言中，双目运算符`&&`、`||`具有`Call by Name`特性：

- 若`&&`运算符左侧表达式值为`false`，则右侧表达式不被执行。
- 若`||`运算符左侧表达式值为`true`，则右侧表达式不被执行。

如下所示：

```scala
object Main extends App {

  {
    println("expr1_1")
    false
  } && {
    println("expr1_2")
    false
  }

  {
    println("expr2_1")
    true
  } || {
    println("expr2_2")
    false
  }

}
```

在`C++`中，代码**近似**于：

```cpp
#include <iostream>

using namespace std;

int main(void)
{
	[] {
		cout << "expr1_1" << endl;
		return false;
	} () && [] {
		cout << "expr1_2" << endl;
		return false;
	} ();

	[] {
		cout << "expr2_1" << endl;
		return true;
	} () || [] {
		cout << "expr2_2" << endl;
		return false;
	} ();

	return 0;
}
```

输出结果：

```
expr1_1
expr2_1
```

输出结果中没有`&&`、`||`运算符右侧表达式的输出，表达式并未被执行。

- 模拟`&&`、`||`运算符

	编写自定义方法`and()`、`or()`在不使用内建`&&`、`||`的情况下模拟`&&`、`||`运算符。

	若使用`Call by Value`，如下所示：

	```scala
	object Main extends App {

	  // 使用隐式类为 Boolean 类型提供额外操作
	  implicit class Operate(bool: Boolean) {
	    def and(bool: Boolean) = if (!this.bool) false else bool
	    def or(bool: Boolean) = if (this.bool) true else bool
	  }

	  {
	    println("expr1_1")
	    false
	  } and {
	    println("expr1_2")
	    false
	  }

	  {
	    println("expr2_1")
	    true
	  } or {
	    println("expr2_2")
	    false
	  }

	}
	```

	输出结果：

	```
	expr1_1
	expr1_2
	expr2_1
	expr2_2
	```

	输出结果中`and()`、`or()`方法右侧的表达式已被执行。  
	在`Call by Value`的求值策略下，参数一经传入便已被求值，不符合`&&`、`||`运算符逻辑。

	将源码修改为`Call by Name`：

	```scala
	object Main extends App {

	  // 方法参数采用传名参数特性
	  implicit class Operate(bool: Boolean) {
	    def and(bool: => Boolean) = if (!this.bool) false else bool
	    def or(bool: => Boolean) = if (this.bool) true else bool
	  }

	  {
	    println("expr1_1")
	    false
	  } and {
	    println("expr1_2")
	    false
	  }

	  {
	    println("expr2_1")
	    true
	  } or {
	    println("expr2_2")
	    false
	  }

	}
	```

	输出结果：

	```
	expr1_1
	expr2_1
	```

	使用`Call by Name`求值策略下，右侧表达式并未执行，符合`&&`、`||`运算符逻辑。



## 并发编程
作为`JVM`平台的编程语言，`Scala`可以直接调用`Java`的并发`API`。  
并发编程是`Scala`的擅长领域，除了`Java`标准库提供的并发API，`Scala`还提供下列并发技术：

- `Scala`标准库中提供了`Future/Promise/Async`库来进行异步编程。
- 基于`Scala`的`Akka`完整实现了`Actor`模型。

### *Future*
`Future`是一组异步操作的抽象，完整包路径为`scala.concurrent.Future`。

- 构建与启动`Future`

	`Future`为**特质**，没有构造函数，无法直接构建实例。  
	创建一个`Future`实例需要使用伴生对象中重写的`apply()`方法，声明如下：

	```scala
	def apply[T](body: =>T)(implicit @deprecatedName('execctx) executor: ExecutionContext): Future[T]
	```

	- `body`参数为**传名参数**，包含了需要异步执行的代码块。
	- `T`参数为泛型参数，表示异步执行的代码块最终的返回值类型。
	- `executor`参数为隐式参数，用于指定异步代码的执行器。  
	`scala.concurrent.ExecutionContext.Implicits.global`提供了默认的执行器。

	构建一个`Future`，基本代码如下：

	```scala
	import scala.concurrent.Future
	import scala.concurrent.ExecutionContext.Implicits.global

	val future = Future[XXX] {
	  /* Code you want to excute... */
	}
	```

	与传统的并发库设计不同，`Future`并没有提供诸如`start()/run()`之类的方法用于显式开始异步代码块的执行。  
	在完成`Future`实例构建的同时，作为参数传入的代码块就已自动开始异步执行。

- *Callbacks* (异步回调)

	与传统的并发库设计类似，`Future`采用回调的方式来处理异步操作完成的结果。  
	`Future`实例提供了`onComplete()`成员方法来绑定回调函数，声明如下：

	```scala
	def onComplete[U](@deprecatedName('func) f: Try[T] => U)(implicit executor: ExecutionContext): Unit
	```

	- `f`参数为被回调的高阶函数。
	- `executor`参数作用与上述`apply()`方法中类似。

	被回调的高阶函数类型为`Try[T] => U`。  
	抽象类`Try[T]`类似于`Option[T]`，拥有两个样例类子类`Success[T]`和`Failure[T]`，定义如下：

	```scala
	final case class Success[+T](value: T) extends Try[T] { ... }
	final case class Failure[+T](exception: Throwable) extends Try[T] { ... }
	```

	在编写回调函数时，可使用模式匹配语法：

	- 对于**成功**的异步操作，匹配内容是异步操作的返回值。
	- 对于**失败**的异步操作，匹配内容是导致异步操作失败的异常。

	`Future`也提供了`onSuccess()/onFailure()`方法接收偏函数分别处理异步操作成功/失败时的情况。  
	当只需要处理某一类情况时，可以直接使用对应方法。

	一个`Future`实例可以**多次**调用`onComplete()/onSuccess()/onFailure()`来添加多个回调操作。  
	多个回调操作都会被执行，但执行的先后顺序**不确定**。

	回调处理异步操作结果的基本代码如下：

	```scala
	import scala.util.{Failure, Success}

	future onComplete {
	  case Success(xxx) => ...
	  case Failure(xxx) => ...
	}

	future onSuccess {
	  re: T => ...
	}

	future onFailure {
	  case ex => ...
	}
	```

- 同步等待

	在个别情况下，可能需要等待异步操作执行完毕。
	等待`Future`纸型完毕可以使用`Await`单例，完整包路径为`scala.concurrent.Await`。

	`Await`单例提供了`result()`方法用于同步等待`Future`执行完毕，定义如下：

	```scala
	def result[T](awaitable: Awaitable[T], atMost: Duration): T
	```

	- `awaitable`参数为`Awaitable`类型，用于表示一个可等待的操作，`Future`特质为其子类，可支持传入`Future`实例作为参数。
	- `atMost`参数为同步等待的时间。

	基本用法如下：

	```scala
	import scala.concurrent.Await
	import scala.concurrent.duration.Duration

	val result = Await.result(future, Duration.Inf)
	println(result)
	...
	```

 	- `Duration` (时间类型)

		时间参数类型为`Duration`，为抽象类，完整路径为`scala.concurrent.duration.Duration`。  
		`Duration`的伴生对象内定义了`apply()`方法，声明如下：

		```scala
		def apply(length: Long, unit: TimeUnit): FiniteDuration
		```

		- `length`参数为时间数值。
		- `unit`参数为时间单位。

		构建的时间对象为`Duration`的子类，有限时间`FiniteDuration`。  
		`Duration`中有两个成员`Inf`、`MinusInf`分别用来表示**无限大/无限小**的时间。

		`TimeUnit`类型完整包路径为`java.util.concurrent.TimeUnit`，为枚举类型，包含以下枚举成员：

		- `java.util.concurrent.TimeUnit.DAYS` 天
		- `java.util.concurrent.TimeUnit.HOURS` 小时
		- `java.util.concurrent.TimeUnit.MICROSECONDS` 微秒
		- `java.util.concurrent.TimeUnit.MILLISECONDS` 毫秒
		- `java.util.concurrent.TimeUnit.MINUTES` 分钟
		- `java.util.concurrent.TimeUnit.NANOSECONDS` 纳秒
		- `java.util.concurrent.TimeUnit.SECONDS` 秒

		在`import scala.concurrent.duration`包中定义了一系列隐式类`DurationInt/DurationLong/DurationDouble`。  
		引用对应隐式类即可使用对应的DSL语法来构建时间对象`FiniteDuration`，如：

		- `1000 days`被转换为`Duration(1000, java.util.concurrent.TimeUnit.DAYS)`
		- `1000 minutes`被转换为`Duration(1000, java.util.concurrent.TimeUnit.SECONDS)`
		- ...

		诸如此类...  
		在`scala.concurrent.duration.DurationConversions`特质中定义了完整的转化语法。

- *blocking* (阻塞块)

	`Future`是异步执行的，不会阻塞基础的执行线程。但在某些情况下，阻塞是必要的，需要区别两种形式的执行线程阻塞：

	- 从`Future`内部调用任意代码阻塞线程。
	- 在`Future`外部等待一个`Future`完成。

	在`Future`外部主动阻塞等待应使用`Await`类，在`Future`内部阻塞则应使用`blocking`方法。  
	`blocking`定义在包对象`scala.concurrent`中，是一个接收**传名参数**的泛型方法，定义如下所示：

	```scala
	def future[T](body: =>T)(implicit @deprecatedName('execctx) executor: ExecutionContext): Future[T] = Future[T](body)
	```

	`blocking`块的作用是向执行器(`ExecutionContext`)标记可能造成阻塞的代码，并调整执行器的行为。  
	对于默认的执行器`scala.concurrent.ExecutionContext.Implicits.global`，在`Future`中包含`blocking`块时，会新建线程来执行`Future`而不是等待复用已有的线程。

	如下所示：

	```scala
	import scala.concurrent.Future
	import scala.concurrent.ExecutionContext.Implicits.global

	object Main extends App {

	  for (n <- 0 to 30)
	    Future {
	      println(s"Index: $n Thread Name: ${Thread.currentThread.getName}")
	      Thread.sleep(3000)
	    }

	  scala.io.StdIn.readLine()
	}
	```

	输出结果：(Scala 2.11.8 && ArchLinux x64)

	```
	Index: 4 Thread Name: ForkJoinPool-1-worker-5
	Index: 2 Thread Name: ForkJoinPool-1-worker-9
	Index: 0 Thread Name: ForkJoinPool-1-worker-13
	Index: 7 Thread Name: ForkJoinPool-1-worker-15
	Index: 3 Thread Name: ForkJoinPool-1-worker-7
	Index: 1 Thread Name: ForkJoinPool-1-worker-11
	Index: 6 Thread Name: ForkJoinPool-1-worker-3
	Index: 5 Thread Name: ForkJoinPool-1-worker-1
	Index: 8 Thread Name: ForkJoinPool-1-worker-11
	Index: 14 Thread Name: ForkJoinPool-1-worker-15
	Index: 10 Thread Name: ForkJoinPool-1-worker-9
	Index: 13 Thread Name: ForkJoinPool-1-worker-13
	Index: 12 Thread Name: ForkJoinPool-1-worker-1
	Index: 11 Thread Name: ForkJoinPool-1-worker-3
	Index: 9 Thread Name: ForkJoinPool-1-worker-7
	Index: 15 Thread Name: ForkJoinPool-1-worker-5
	Index: 16 Thread Name: ForkJoinPool-1-worker-11
	Index: 17 Thread Name: ForkJoinPool-1-worker-15
	Index: 19 Thread Name: ForkJoinPool-1-worker-13
	Index: 18 Thread Name: ForkJoinPool-1-worker-9
	Index: 22 Thread Name: ForkJoinPool-1-worker-7
	Index: 21 Thread Name: ForkJoinPool-1-worker-1
	Index: 20 Thread Name: ForkJoinPool-1-worker-3
	Index: 23 Thread Name: ForkJoinPool-1-worker-5
	Index: 24 Thread Name: ForkJoinPool-1-worker-11
	Index: 25 Thread Name: ForkJoinPool-1-worker-15
	Index: 26 Thread Name: ForkJoinPool-1-worker-13
	Index: 27 Thread Name: ForkJoinPool-1-worker-9
	Index: 28 Thread Name: ForkJoinPool-1-worker-7
	Index: 29 Thread Name: ForkJoinPool-1-worker-1
	Index: 30 Thread Name: ForkJoinPool-1-worker-3
	```

	打印执行结果的过程中，输出流出现了几次3秒的停顿。  
	从结果中不难看出，执行器只开辟了`15`个处理线程，在所有处理线程都处于`sleep`状态时，输出流便停止。

	尝试将`sleep()`函数写在`blocking`中：

	```scala
	import scala.concurrent.{Future, blocking}
	import scala.concurrent.ExecutionContext.Implicits.global

	object Main extends App {
	  for (n <- 0 to 30)
	    Future {
	      println(s"Index: $n Thread before blocking: ${Thread.currentThread.getName}")
	      blocking {
	        println(s"Index: $n Blocking: ${Thread.currentThread.getName}")
	        Thread.sleep(3000)
	      }
	      println(s"Index: $n Thread after blocking: ${Thread.currentThread.getName}")
	    }

	  scala.io.StdIn.readLine()
	}
	```

	输出结果：(Scala 2.11.8 && ArchLinux x64)

	```
	Index: 6 Thread before blocking: ForkJoinPool-1-worker-1
	Index: 2 Thread before blocking: ForkJoinPool-1-worker-9
	Index: 3 Thread before blocking: ForkJoinPool-1-worker-7
	Index: 1 Thread before blocking: ForkJoinPool-1-worker-11
	Index: 5 Thread before blocking: ForkJoinPool-1-worker-3
	Index: 7 Thread before blocking: ForkJoinPool-1-worker-15
	Index: 0 Thread before blocking: ForkJoinPool-1-worker-13
	Index: 4 Thread before blocking: ForkJoinPool-1-worker-5
	Index: 4 Blocking: ForkJoinPool-1-worker-5
	Index: 7 Blocking: ForkJoinPool-1-worker-15
	Index: 5 Blocking: ForkJoinPool-1-worker-3
	Index: 2 Blocking: ForkJoinPool-1-worker-9
	Index: 8 Thread before blocking: ForkJoinPool-1-worker-23
	Index: 8 Blocking: ForkJoinPool-1-worker-23
	Index: 9 Thread before blocking: ForkJoinPool-1-worker-27
	Index: 1 Blocking: ForkJoinPool-1-worker-11
	Index: 3 Blocking: ForkJoinPool-1-worker-7
	Index: 10 Thread before blocking: ForkJoinPool-1-worker-31
	Index: 9 Blocking: ForkJoinPool-1-worker-27
	Index: 6 Blocking: ForkJoinPool-1-worker-1
	Index: 10 Blocking: ForkJoinPool-1-worker-31
	Index: 0 Blocking: ForkJoinPool-1-worker-13
	Index: 11 Thread before blocking: ForkJoinPool-1-worker-17
	Index: 11 Blocking: ForkJoinPool-1-worker-17
	Index: 12 Thread before blocking: ForkJoinPool-1-worker-21
	Index: 12 Blocking: ForkJoinPool-1-worker-21
	Index: 13 Thread before blocking: ForkJoinPool-1-worker-19
	Index: 13 Blocking: ForkJoinPool-1-worker-19
	Index: 14 Thread before blocking: ForkJoinPool-1-worker-25
	Index: 14 Blocking: ForkJoinPool-1-worker-25
	Index: 15 Thread before blocking: ForkJoinPool-1-worker-29
	Index: 15 Blocking: ForkJoinPool-1-worker-29
	Index: 16 Thread before blocking: ForkJoinPool-1-worker-47
	Index: 16 Blocking: ForkJoinPool-1-worker-47
	Index: 17 Thread before blocking: ForkJoinPool-1-worker-45
	Index: 17 Blocking: ForkJoinPool-1-worker-45
	Index: 18 Thread before blocking: ForkJoinPool-1-worker-59
	Index: 18 Blocking: ForkJoinPool-1-worker-59
	Index: 19 Thread before blocking: ForkJoinPool-1-worker-39
	Index: 19 Blocking: ForkJoinPool-1-worker-39
	Index: 20 Thread before blocking: ForkJoinPool-1-worker-53
	Index: 20 Blocking: ForkJoinPool-1-worker-53
	Index: 21 Thread before blocking: ForkJoinPool-1-worker-37
	Index: 21 Blocking: ForkJoinPool-1-worker-37
	Index: 22 Thread before blocking: ForkJoinPool-1-worker-51
	Index: 22 Blocking: ForkJoinPool-1-worker-51
	Index: 23 Thread before blocking: ForkJoinPool-1-worker-35
	Index: 23 Blocking: ForkJoinPool-1-worker-35
	Index: 24 Thread before blocking: ForkJoinPool-1-worker-49
	Index: 24 Blocking: ForkJoinPool-1-worker-49
	Index: 25 Thread before blocking: ForkJoinPool-1-worker-63
	Index: 25 Blocking: ForkJoinPool-1-worker-63
	Index: 26 Thread before blocking: ForkJoinPool-1-worker-43
	Index: 26 Blocking: ForkJoinPool-1-worker-43
	Index: 27 Thread before blocking: ForkJoinPool-1-worker-57
	Index: 27 Blocking: ForkJoinPool-1-worker-57
	Index: 28 Thread before blocking: ForkJoinPool-1-worker-41
	Index: 28 Blocking: ForkJoinPool-1-worker-41
	Index: 29 Thread before blocking: ForkJoinPool-1-worker-55
	Index: 29 Blocking: ForkJoinPool-1-worker-55
	Index: 30 Thread before blocking: ForkJoinPool-1-worker-33
	Index: 30 Blocking: ForkJoinPool-1-worker-33
	Index: 4 Thread after blocking: ForkJoinPool-1-worker-5
	Index: 7 Thread after blocking: ForkJoinPool-1-worker-15
	Index: 5 Thread after blocking: ForkJoinPool-1-worker-3
	Index: 2 Thread after blocking: ForkJoinPool-1-worker-9
	Index: 8 Thread after blocking: ForkJoinPool-1-worker-23
	Index: 1 Thread after blocking: ForkJoinPool-1-worker-11
	Index: 3 Thread after blocking: ForkJoinPool-1-worker-7
	Index: 9 Thread after blocking: ForkJoinPool-1-worker-27
	Index: 6 Thread after blocking: ForkJoinPool-1-worker-1
	Index: 10 Thread after blocking: ForkJoinPool-1-worker-31
	Index: 0 Thread after blocking: ForkJoinPool-1-worker-13
	Index: 11 Thread after blocking: ForkJoinPool-1-worker-17
	Index: 12 Thread after blocking: ForkJoinPool-1-worker-21
	Index: 13 Thread after blocking: ForkJoinPool-1-worker-19
	Index: 14 Thread after blocking: ForkJoinPool-1-worker-25
	Index: 15 Thread after blocking: ForkJoinPool-1-worker-29
	Index: 16 Thread after blocking: ForkJoinPool-1-worker-47
	Index: 17 Thread after blocking: ForkJoinPool-1-worker-45
	Index: 18 Thread after blocking: ForkJoinPool-1-worker-59
	Index: 19 Thread after blocking: ForkJoinPool-1-worker-39
	Index: 20 Thread after blocking: ForkJoinPool-1-worker-53
	Index: 21 Thread after blocking: ForkJoinPool-1-worker-37
	Index: 22 Thread after blocking: ForkJoinPool-1-worker-51
	Index: 23 Thread after blocking: ForkJoinPool-1-worker-35
	Index: 24 Thread after blocking: ForkJoinPool-1-worker-49
	Index: 25 Thread after blocking: ForkJoinPool-1-worker-63
	Index: 26 Thread after blocking: ForkJoinPool-1-worker-43
	Index: 27 Thread after blocking: ForkJoinPool-1-worker-57
	Index: 28 Thread after blocking: ForkJoinPool-1-worker-41
	Index: 29 Thread after blocking: ForkJoinPool-1-worker-55
	Index: 30 Thread after blocking: ForkJoinPool-1-worker-33
	```

	整个输出过程中，仅有**一次**3秒的停顿。  
	分析输出结果，可以得知：

	1. 执行器开辟的工作线程的数量明显大于没有`blocking`时的数量(线程数目`> 50`)。  
	即使用`blocking`改变了执行器的线程创建策略。
	1. 相同`Index`输出的线程名称相同，`blocking`包含的代码、之后的代码并没有运行在独立的线程。  
	即一个独立的`Future`运行在一个线程，**没有**像`C#`中的`async`方法那样被切分到不同的线程执行。

### *Promise*
`Promise`为特质，完整包路径为`scala.concurrent.Promise`。

- `Future`提供了带有**只读占位符**(`read-only placeholder`)的返回值，只有一个异步操作完全结束才能获取其返回值。
- `Promise`则提供了可写的、单一指派(`writable、single-assignment`)的分配容器。

使用`Promise`：

1. `Promise`特质的伴生对象中提供了空参的`apply()`方法用于构建默认的`Promise`实例(`DefaultPromise`类型)。
1. `Promise`实例提供了无参的`future`方法用于获取自身的`Future`实例。
1. `Promise`实例可以通过`success()/failure()`方法标记自身`Future`实例的执行结果，使用`isCompleted`方法判断`Future`实例的执行状态。
1. `Promise`实例的`success()/failure()`方法只能选其一，且只能调用一次。`success()/failure()`方法一旦被调用，自身`Future`实例的执行结果便已确定，不可更改。
1. 多个`Future`可通过`Promise`共享数据。
1. `Promise`能使用`completeWith()`绑定一个其它的`Future`，让自身同被绑定的`Future`拥有相同的执行状态和**执行结果**。

实例，一个`Future`通过使用`Promise`获取另一个`Future`中的执行状态(**不是**执行结束的返回内容)，基本代码如下：

```scala
import scala.concurrent.{Future, Promise, Await}
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

### *synchronized*
`Java`中提供了`synchronized`关键字用于多线程环境下的变量同步。  
`Scala`中提供了类似的机制，但语法略有不同。

`Scala`中的`synchronized`不是语言级别的关键字，仅仅做为**成员方法**存在，方法签名为：

```scala
def synchronized[T](t: T): T
```

所有类型都包含此方法。

调用语法为：

```scala
变量名.synchronized(语句)
```

使用中缀表达式和块语法：

```scala
变量名 synchronized {
  语句1
  语句2
  ...
}
```

在类中直接调用`synchronized()`方法，锁定变量为当前类实例。  
在单例对象/伴生对象中直接调用`synchronized()`方法，锁定变量为单例对象、伴生对象实例。

`Scala`中的`synchronized`没有`Java`中修饰方法的功能，但可以模拟出类似效果。  
如下所示：

`Java`代码：

```java
class TestSync {
	synchronized public void test() { ... }
	synchronized public static void staticTest() { ... }
}
```

等价`Scala`代码：

```scala
class TestSync {
  def test() = synchronized[Unit] { ... }
}
object TestSync {
  def staticTest() = synchronized[Unit] { ... }
}
```



## *Reflect* (反射)
`Scala 2.10`之后提供了自身的反射相关`API`。

`Java`标准库中的反射`API`不支持`Scala`的专有语言特性。  
`Scala`自身提供的反射`API`能完整地支持所有`Scala`语言特性。

到目前版本(`Scala 2.12`)为止，反射相关功能依然是`Expermental`(**实验性**)的，相关`API`在后续版本中可能会有较大改动。

### 反射机制相关类型
反射`API`相关的类型定义在包路径`scala.reflect.runtime.universe`中。

- `Type`

	包含类型内的成员信息(定义的字段`fields`、方法`methods`、类型别名`type aliases`等)、类型继承关系、基类信息等。

	`Type`类型类似于`Java`反射机制中的`Class`类型，获取`Type`实例是整个反射流程的起始步骤。  
	通过`typeOf[T]`方法可以获取指定类型的`Type`实例。

	`Type`类型可用于筛选出需要反射的成员的符号信息：

	- `Type.decls` 获取用户定义的成员的`Symbol`
	- `Type.members` 获取类内所有成员的`Symbol`
	- `Type.decl()/member()` 获取指定`TermName`的成员`Symbol`

	`Type`类型可用于比较：

	- 通过操作符`=:=`比较是否相等
	- 通过操作符`<:<`比较是否子类

- `Symbol`

	包含实例/成员的完整信息。

	`Symbol`建立了名称与所指向的类型的绑定(`establish bindings between a name and the entity it refers to`)。  
	`Symbol`包含了类型(`class/trait/object`等)或成员(`val/var/def`等)的所有可用信息(`contain all available information about the declaration of an entity or a member`)。

	根据包含信息的类别差异，`Symbol`类型存在以下子类：

	- `TypeSymbol`

		`TypeSymbol`表示类型、类、特质的定义，以及类型参数(`TypeSymbol represents type, class, and trait declarations, as well as type parameters`)。

		存在以下子类：

		- `ClassSymbol`

			提供对包含在类、特质中所有信息的访问(`Provides access to all information contained in a class or trait declaration`)。

		构建`TypeSymbol`：
		
		- `Type.typeSymbol` 通过`Type`实例获取类型对应的`TypeSymbol`
		- `symbolOf[T]` 直接通过泛型参数构建`TypeSymbol`

	- `TermSymbol`

		`TermSymbol`表示字段、方法、单例的定义，以及包、参数(`The type of term symbols representing val, var, def, and object declarations as well as packages and value parameters`)。

		存在以下子类：

		- `MethodSymbol`

			表示方法定义(`method symbols representing def declarations`)。  
			支持查询方法是否为(主)构造器，或方法是否支持可变参数等(`It supports queries like checking whether a method is a (primary) constructor, or whether a method supports variable-length argument lists`)。

		- `ModuleSymbol`

			表示单例定义(`module symbols representing object declarations`)。

- `Mirror`

	所有反射提供的信息需要通过`Mirror`来获取(`All information provided by reflection is made accessible through mirrors`)。

	使用`runtimeMirror()`方法以`ClassLoader`为参数构建`Mirror`实例。

	通过`Mirror.reflect()`获取`InstanceMirror`，用于反射访问/修改字段，调用方法。  
	通过`Mirror.reflectClass()`获取`ClassMirror`，可获取类型构造方法反射构建实例。  
	通过`Mirror.reflectModule()`获取`ModuleMirror`，可获取单例对象实例。

如下所示：

```scala
import scala.reflect.runtime.universe._

object Main extends App {

  class TestReflect(init: Int) {
    val field = init
    def showField = {
      println("Call method 'showField'")
      2333
    }
  }

  val run = runtimeMirror(getClass.getClassLoader)

  // 反射获取构造器MethodSymbol，构造器名称为 <init>
  val constructor = typeOf[TestReflect].decl(TermName("<init>")).asMethod
  val instance = run //通过构造器的MethodSymbol反射构建实例
    .reflectClass(symbolOf[TestReflect].asClass)
    .reflectConstructor(constructor).apply(2333)

  // 遍历筛选特定成员
  typeOf[TestReflect].decls foreach {
    case term: TermSymbol if term.name == TermName("field") =>
      println(s"Field name: ${term.name}, value: ${run.reflect(instance).reflectField(term).get}")
    case method: MethodSymbol if method.name == TermName("showField") =>
      println(s"Method name: ${method.name}, value: ${run.reflect(instance).reflectMethod(method).apply()}")
    case _ =>
  }

}
```

输出结果：

```
Field name: field, value: 2333
Call method 'showField'
Method name: showField, value: 2333
```

注意事项：

- `Symbol`类型的成员方法`name`返回类型为`NameType`。  
	`NameType`不要直接与文本比较，应使用`toString`方法转换为文本进行比较。  
	或者将`NameType`与`TermName`类型进行比较。
- 类内方法的`MethodSymbol`对应的`TermName`与方法名称相同，一个方法的多个重载`TermName`相同。
- 对于无重载的方法，使用`Type.decl()/member()`根据名称查找到的`Symbol`可直接使用`Symbol.asSymbol`方法转化为`MethodSymbol`。
- 对于拥有重载的方法，使用`Type.decl()/member()`方法根据名称查找获取到的是包含重载信息的`TermSymbol`。  
	对该`TermSymbol`实例使用`Symbol.alternatives`方法可获取包含所有同名重载方法信息的`List[MethodSymbol]`。  
	通过分析每个`MethodSymbol`的信息选取正确的重载。



## *Annotation* (注解)
`Scala`中的注解语法与`Java`中类似。  
标准库定义的注解相关内容在包`scala.annotation`中。

注解的基本语法为：

```scala
@注解名称(注解参数...)
```

与`Java`注解的用法类似，注解参数不是必须的，一个元素允许拥有多个注解。

### 自定义注解
`Scala 2.10`之前，`Scala`并未提供自定义注解功能，自定义注解需要在`Java`源码中进行。  
`Scala 2.10`开始，作为`Reflect`功能的一部分，`Scala`提供了自定义注解支持。

与反射相关功能类似，到目前版本(`Scala 2.12`)为止，注解相关功能依然是`Expermental`(**实验性**)的，注解相关`API`一直处于变化中。

`Scala`中的自定义注解不是**接口/特质**，而是**类**。  
自定义注解需要从注解特质中继承，`Scala`中提供了两类注解特质：

- `scala.annotation.ClassfileAnnotation` 由`Java`编译器生成注解
- `scala.annotation.StaticAnnotation` 由`Scala`编译器生成注解

两类注解特质都继承自基类`scala.annotation.Annotation`。  
定义注解类语法与普通类相同：

```scala
// 标记注解
class 注解名称 extends StaticAnnotation/ClassfileAnnotation

// 有参注解
class 注解名称(参数表...) extends StaticAnnotation/ClassfileAnnotation
```

两类注解特质的基类相同，因此自定义注解类时**允许**同时混入两类注解特质。  
继承自`ClassfileAnnotation`基类的注解在使用时参数应以`具名参数(named arguments)`形式传入。  
继承自`StaticAnnotation`基类的注解无此限制。  
如下所示：

```scala
import scala.annotation.{ClassfileAnnotation, StaticAnnotation}

class CustomStaticAnnotation(name: String) extends StaticAnnotation
class CustomClassfileAnnotation(name: String) extends ClassfileAnnotation

@CustomStaticAnnotation("2333") //正确
@CustomClassfileAnnotation("2333") //错误，Java注解需要以具名参数形式进行传入
@CustomClassfileAnnotation(name = "2333") //正确
class Test
```

### 解析注解
通过反射机制获取注解信息，相关`API`位于`scala.reflect.runtime.universe`包路径下。

获取注解：

- 获取类的注解：

	1. 使用`typeOf()`方法，获取`Type`类型的类信息。
	1. 通过`Type.typeSymbol`获取`Symbol`。
	1. 通过`Symbol.annotations`获取`List[Annotation]`(注解列表)。

- 获取方法/成员字段的注解：

	1. 使用`typeOf()`方法，获取`Type`类型的类信息。
	1. 通过`Type.decls/decl()`方法筛选出目标成员的`Symbol`。
	1. 通过`Symbol.annotations`获取`List[Annotation]`(注解列表)。

- 获取方法参数的注解：

	1. 使用`typeOf()`方法，获取`Type`类型的类信息。
	1. 通过`Type.decls/decl()`方法筛选出目标方法的`MethodSymbol`。
	1. 通过`MethodSymbol.paramLists`方法获取目标方法的参数表(`List[List[Symbol]]`类型，方法柯里化可能会有多个参数表)。
	1. 通过`Symbol.annotations`获取`List[Annotation]`(注解列表)。

`Scala`注解类型为`scala.reflect.runtime.universe.Annotation`。  
在`Scala 2.11`之前，`Annotation`类型提供了`scalaArgs/javaArgs`等无参方法用于获取注解信息，但在`Scala 2.11`版本中，这些方法已被标记为`deprecated`。  
应使用`Annotation.tree`方法获取注解语法树，类型为`scala.reflect.runtime.universe.Tree`。

如下所示：

```scala
import scala.annotation.StaticAnnotation
import scala.reflect.runtime.universe._

class CustomAnnotation(name: String, num: Int) extends StaticAnnotation

@CustomAnnotation("Annotation for Class", 2333)
class Test {
  @CustomAnnotation("Annotation for Class", 6666)
  val ff = ""
}

object Main extends App {

  {
    // 获取类型注解
    val tpe: Type = typeOf[Test]
    val symbol: Symbol = tpe.typeSymbol //获取类型符号信息
    val annotation: Annotation = symbol.annotations.head
    val tree: Tree = annotation.tree //获取语法树

    // 解析注解语法树...
  }

  {
    // 获取成员字段注解
    val tpe: Type = typeOf[Test]
    val symbol: Symbol = tpe.decl(TermName("ff ")) //获取字段符号信息
    val annotation: Annotation = symbol.annotations.head
    val tree: Tree = annotation.tree

    // 解析注解语法树...
  }

}
```

通过`scala.reflect.api.Printer.showRaw()`方法可以获取语法树的文本。  
注解语法树中包含了注解参数信息，可以通过模式匹配提取。

如下所示：

```scala
import scala.annotation.StaticAnnotation
import scala.reflect.runtime.universe._

class CustomAnnotation(name: String, num: Int) extends StaticAnnotation

@CustomAnnotation("Annotation for Class", 2333)
class Test

object Main extends App {

  // 获取类型注解
  val tpe: Type = typeOf[Test]
  val symbol: Symbol = tpe.typeSymbol //获取类型符号信息
  val annotation: Annotation = symbol.annotations.head
  val tree: Tree = annotation.tree //获取语法树

  println(showRaw(tree)) //打印语法树
  val Apply(_, Literal(Constant(name: String)) :: Literal(Constant(num: Int)) :: Nil) = tree
  println(s"Annotation args: name -> $name, num -> $num")

}
```

输出结果：(`Scala 2.12.2 && macOS 10.12.5`)

```
Apply(Select(New(TypeTree()), termNames.CONSTRUCTOR), List(Literal(Constant("Annotation for Class")), Literal(Constant(2333))))
Annotation args: name -> Annotation for Class, num -> 2333
```

注意事项：

- 解析注解参数需要基于语法树结构，不要使用**参数默认值**特性，使用默认参数的注解生成的语法树不包含注解信息的默认值。
- 类内字段会有多个`TermSymbol`，对应不同的`TermName`，包含注解信息的`TermName`为`字段名称 + 空格`。
- 样例类的构造器参数作为类的成员存在，但若在参数上添加注解，注解信息并未附加在字段信息中。  
	提取样例类构造器成员的注解信息需要以获取方法参数注解的方式进行，查找构造器方法(`TermName("<init>")`)，获取参数成员(`Method.paramLists`)。
- 使用`Annotation.tree`方法获取注解语法树(`Tree`类型)，再使用`Tree.tpe`方法获取注解语法树类型信息(`Type`类型)，与直接使用`typeOf[注解类型]`获取的注解类型信息相同，可以用于比较筛选注解类型。

完整的注解解析实例，如下所示：

```scala
import scala.annotation.StaticAnnotation
import scala.reflect.runtime.universe._

class CustomAnnotation(name: String, num: Int) extends StaticAnnotation {
  override def toString = s"Annotation args: name -> $name, num -> $num"
}

@CustomAnnotation("Annotation for Class", 2333)
class Test {
  @CustomAnnotation("Annotation for Member", 6666)
  val ff = ""
  def mm(ss: String, @CustomAnnotation("Annotation for Arg", 9999) arg: Int) = ""
}

object Main extends App {

  // 获取指定类型的注解信息，通过 Annotation.tree.tpe 获取注解的 Type 类型，以此进行筛选
  def getClassAnnotation[T: TypeTag, U: TypeTag] =
    symbolOf[T].annotations.find(_.tree.tpe =:= typeOf[U])

  // 通过字段名称获取指定类型的注解信息，注意查找字段名称时添加空格
  def getMemberAnnotation[T: TypeTag, U: TypeTag](memberName: String) =
    typeOf[T].decl(TermName(s"$memberName ")).annotations.find(_.tree.tpe =:= typeOf[U])

  // 通过方法名称和参数名称获取指定类型的注解信息
  def getArgAnnotation[T: TypeTag, U: TypeTag](methodName: String, argName: String) =
    typeOf[T].decl(TermName(methodName)).asMethod.paramLists.collect {
      case symbols => symbols.find(_.name == TermName(argName))
    }.headOption.fold(Option[Annotation](null))(_.get.annotations.find(_.tree.tpe =:= typeOf[U]))

  // 解析语法树，获取注解数据
  def getCustomAnnotationData(tree: Tree) = {
    val Apply(_, Literal(Constant(name: String)) :: Literal(Constant(num: Int)) :: Nil) = tree
    new CustomAnnotation(name, num)
  }

  getClassAnnotation[Test, CustomAnnotation].map(_.tree) foreach { classAnnotationTree =>
    val classAnnotation = getCustomAnnotationData(classAnnotationTree)
    println(classAnnotation)
  }

  getMemberAnnotation[Test, CustomAnnotation]("ff").map(_.tree) foreach { memberAnnotationTree =>
    val memberAnnotation = getCustomAnnotationData(memberAnnotationTree)
    println(memberAnnotation)
  }

  getArgAnnotation[Test, CustomAnnotation]("mm", "arg").map(_.tree) foreach { argAnnotationTree =>
    val argAnnotation = getCustomAnnotationData(argAnnotationTree)
    println(argAnnotation)
  }

}
```

输出结果：(`Scala 2.12.2 && macOS 10.12.5`)

```
Annotation args: name -> Annotation for Class, num -> 2333
Annotation args: name -> Annotation for Member, num -> 6666
Annotation args: name -> Annotation for Arg, num -> 9999
```



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

使用`\()`、`\\()`方法同样可以进行属性查找。  
在参数字符串前加`@`字符表示搜索的内容为**属性**，如`\("@num")`表示查找名为`num`的属性内容。  
使用`\()`方法查找属性时，查找的的范围**不是**子节点的属性，而是**当前**节点的属性。

`NodeSeq`类型提供了`\@()`方法在**当前**子节点中进行属性查找，直接使用属性名作为参数，无需再添加`@`字符。  
如下所示：

```scala
// 参数为属性名称
def \@(attributeName: String): String
```

`Node`类型提供了`attribute()`以及`attributes`方法从节点中获取属性。  
如下所示：

```scala
// 获取带有指定属性的节点
final def attribute(key: String): Option[Seq[Node]]
// 获取所有属性
def attributes: MetaData
```

`attributes`方法返回的类型为`MetaData`。
`MetaData`类型支持遍历操作，定义了`key`、`value`方法用于获取属性的键值。  
如下所示：

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
object Xml extends App {

  val xmlFile = XML.loadFile(getClass.getResource("Example.xml").getPath)

  val showChild: Node => Unit = _.child foreach {

    // 使用标签匹配，可以将表达式嵌在匹配语句中
    case <One>{text}</One> => println(s"case <One>{text}</One>: $text")

    // 标签匹配支持多级嵌套标签，不支持在标签中直接添加属性
    case <Node><Two>{text}</Two></Node> =>
      println(s"case <Node><Two>{text}</Two></Node>: $text")

    // 匹配多级标签需要节点内部不换行
    case <Node><Three>{text}</Three></Node> =>
      println(s"case <Node><Three>{text}</Three></Node>: $text")

    // 使用 @ 操作符给匹配的节点标记变量名称(n 为 Node 类型)
    case n@<Three>{_}</Three> =>
      println(s"case n@<Three>{_}</Three>, n text: ${n.text}, n type: ${n.getClass}")

    // 遍历属性
    case n@<Four>{_}</Four> if n \@ "arg_one" == "arg_4_1" =>
      println(s"case n@<Four>{_}</Four>, n text: ${n.text}, n type: ${n.getClass}, n.attributes: ")
      n.attributes foreach { attr =>
        println(s"attribute name: ${attr.key} attribute value: ${attr.value.text}")
      }

    // 使用 @ 操作符给节点内容标记变量名称(n 为 Text 类型)
    case <Four>{n@_}</Four> =>
      println(s"case <Four>{n@_}</Four>, n text: ${n.text}, n type: ${n.getClass}")

    /*
      匹配其它类型节点，注意不能写成：
      case _ if node.child.length > 0 => ... 或 case _ if node.child.nonEmpty => ...
      (空指针不能调用方法)
    */
    case node if node.child != null => showChild(node)

  }

  showChild(xmlFile)
}
```

输出结果：

```
case <One>{text}</One>: node1
case <Node><Two>{text}</Two></Node>: node2
case n@<Three>{_}</Three>, n text: node3, n type: class scala.xml.Elem
case <Four>{n@_}</Four>, n text: node4_1, n type: class scala.xml.Text
case n@<Four>{_}</Four>, n text: node4_2, n type: class scala.xml.Elem, n.attributes:
attribute name: arg_two attribute value: arg_4_2
attribute name: arg_one attribute value: arg_4_1
```

### 创建 XML
可以直接将代码嵌入`XML`语句中：

```scala
scala> val str = "Test"
str: String = Test
scala> val node0 = <li>{ str }</li> //xml节点内容可以插入变量,使用花括号区分表达式与xml本身内容
node0: scala.xml.Elem = <li>Test</li>
scala> val node1 = <li name={ str }>test</li> //xml属性中插入变量
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
