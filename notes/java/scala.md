<!-- TOC -->

- [配置開發環境](#配置開發環境)
	- [開發工具](#開發工具)
	- [編譯器](#編譯器)
		- [反編譯](#反編譯)
	- [Scala REPL](#scala-repl)
- [Hello World](#hello-world)
- [Method (方法)](#method-方法)
	- [方法返回值](#方法返回值)
	- [空參數方法與無參數方法](#空參數方法與無參數方法)
	- [參數默認值](#參數默認值)
- [Function (函數)](#function-函數)
	- [Function Compose (函數組合)](#function-compose-函數組合)
	- [Partial Function (偏函數)](#partial-function-偏函數)
	- [Partial Applied Function (部分應用函數)](#partial-applied-function-部分應用函數)
- [塊表達式](#塊表達式)
	- [賦值表達式](#賦值表達式)
- [continue 與 break](#continue-與-break)
	- [continue](#continue)
	- [break](#break)
- [OOP](#oop)
	- [訪問權限](#訪問權限)
	- [字段](#字段)
	- [Constructor (構造器)](#constructor-構造器)
	- [多態](#多態)
	- [複製類實例](#複製類實例)
	- [匿名類初始化](#匿名類初始化)
- [Singleton Objects (單例對象)](#singleton-objects-單例對象)
	- [單例類型](#單例類型)
	- [初始化](#初始化)
	- [Companions (伴生對象)](#companions-伴生對象)
- [Trait (特質)](#trait-特質)
	- [Mixin (混入)](#mixin-混入)
	- [重寫衝突方法/字段](#重寫衝突方法字段)
	- [構造順序](#構造順序)
	- [線性化與 super 關鍵字](#線性化與-super-關鍵字)
	- [線性化與 override 關鍵字](#線性化與-override-關鍵字)
	- [線性化與類型關係](#線性化與類型關係)
	- [線性化與泛型](#線性化與泛型)
- [Case Class (樣例類)](#case-class-樣例類)
	- [避免重定義樣例類自動生成的方法](#避免重定義樣例類自動生成的方法)
- [類型](#類型)
	- [值類型](#值類型)
	- [Bottom (底類型)](#bottom-底類型)
	- [Option (可空類型)](#option-可空類型)
- [Pattern Matching (模式匹配)](#pattern-matching-模式匹配)
	- [簡單匹配](#簡單匹配)
	- [類型匹配](#類型匹配)
	- [解構](#解構)
		- [解構Lambda](#解構lambda)
	- [unapply() 與 unapplySeq()](#unapply-與-unapplyseq)
- [apply() 與 update()](#apply-與-update)
	- [無參 apply 方法](#無參-apply-方法)
- [sealed 與 final 關鍵字](#sealed-與-final-關鍵字)
	- [sealed 用於模式匹配](#sealed-用於模式匹配)
	- [sealed 與 ADT](#sealed-與-adt)
- [格式化輸出](#格式化輸出)
	- [StringLike.format() 格式化輸出](#stringlikeformat-格式化輸出)
	- [s字符串插值器](#s字符串插值器)
	- [f字符串插值器](#f字符串插值器)
	- [raw字符串插值器](#raw字符串插值器)
- [終端輸入](#終端輸入)
- [Enumerate (枚舉)](#enumerate-枚舉)
	- [繼承枚舉類](#繼承枚舉類)
	- [訪問枚舉內容](#訪問枚舉內容)
	- [調用枚舉類型](#調用枚舉類型)
	- [限定枚舉類型](#限定枚舉類型)
- [Package (包)](#package-包)
	- [包與路徑](#包與路徑)
	- [擴展用法](#擴展用法)
		- [默認導入](#默認導入)
		- [包對象](#包對象)
- [基礎數據結構](#基礎數據結構)
	- [定長數組](#定長數組)
	- [Tuple (元組)](#tuple-元組)
- [容器](#容器)
	- [容器可變性](#容器可變性)
	- [List (列表)](#list-列表)
	- [ArrayBuffer (變長數組)](#arraybuffer-變長數組)
	- [Set (集合)](#set-集合)
	- [Map (映射)](#map-映射)
	- [GenTraversableLike](#gentraversablelike)
	- [集合有序性](#集合有序性)
- [Higher Order Function (高階函數)](#higher-order-function-高階函數)
	- [for/yeild 語句](#foryeild-語句)
- [Exception (異常)](#exception-異常)
	- [scala.util.Try[T]](#scalautiltryt)
- [XML 解析](#xml-解析)
	- [節點類型](#節點類型)
	- [讀寫 XML 文件](#讀寫-xml-文件)
	- [查找節點](#查找節點)
	- [節點屬性](#節點屬性)
	- [遍歷節點](#遍歷節點)
	- [創建 XML](#創建-xml)
- [Implicit Conversions (隱式轉換)](#implicit-conversions-隱式轉換)
	- [定義隱式轉換](#定義隱式轉換)
	- [隱式參數](#隱式參數)
	- [隱式類](#隱式類)
- [求值策略](#求值策略)
	- [參數的求值策略](#參數的求值策略)
	- [&& 與 || 運算符](#-與--運算符)
		- [模擬 && 、 || 運算符](#模擬----運算符)
- [類型系統](#類型系統)
	- [類型參數](#類型參數)
	- [類型約束](#類型約束)
	- [View Bounds (視圖界定)](#view-bounds-視圖界定)
	- [Content Bounds](#content-bounds)
	- [Variances (型變)](#variances-型變)
- [Higer Kinded Type (高階類型)](#higer-kinded-type-高階類型)
	- [Type Lambda](#type-lambda)
- [Type Class](#type-class)
- [併發編程](#併發編程)
	- [Future](#future)
	- [Promise](#promise)
	- [async/await](#asyncawait)
	- [synchronized](#synchronized)
- [Reflect (反射)](#reflect-反射)
	- [反射機制相關類型](#反射機制相關類型)
		- [Type](#type)
		- [Symbol](#symbol)
	- [補充說明](#補充說明)
- [Annotation (註解)](#annotation-註解)
	- [自定義註解](#自定義註解)
	- [解析註解](#解析註解)

<!-- /TOC -->



# 配置開發環境
Scala是基於`JVM`的編程語言，配置Scala開發環境前需要正確安裝與配置`JDK`。

- **Linux/Unix**系統：

	使用發行版自帶的包管理器安裝Scala：

	```
	# apt install scala //Debian系
	# pacman -S scala //Arch系
	$ brew install scala //macOS
	```

- **Windows**系統：

	1. 安裝`Oracle JDK`。
	1. 從`http://www.scala-lang.org/files/archive/`下載`Scala SDK`。
	1. 設置環境變量`SCALA_HOME`。
	1. 將`%SCALA_HOME%\bin`加入`PATH`環境變量中。

## 開發工具
主流的JavaIDE均支持Scala開發，Vim也有社區提供的對應插件。

- `Vim`

	Vim默認不支持Scala語言，需要安裝`vim-scala`插件提供Scala支持。
	使用**Vundle**安裝此插件，在配置文件`.vimrc`中添加：

	```vim
	Plugin 'derekwyatt/vim-scala'
	```

- `Eclipse`

	安裝`Scala IDE`插件。

- `IDEA`

	安裝JetBrains官方提供的Scala插件。

## 編譯器
與編譯Java代碼類似，編譯Scala代碼使用`scalac`命令：

```
$ scalac *.scala
```

編譯後即可得到字節碼文件`*.class`。執行字節碼可以使用Scala指令：

```
$ scala 主類類名
```

對於使用了`包(package)`的源碼，在用`scalac`指令進行編譯時，編譯器會自動根據包路徑創建對應的目錄，
然後在對應的包路徑下生成對應的class文件。

運行帶有包路徑的字節碼需要在包路徑的相對根目錄下，執行：

```
$ scala 包路徑.主類名
```

### 反編譯
使用`scalap`可以反編譯字節碼得到Scala代碼：

```
$ scalap *.class
```

或者：

```
$ scalap [類名]
```

如果需要查看字節碼的對應生成的Java代碼，可以使用`javap`工具：

```
$ javap [類名]
```

使用`javap`可以直接查看生成的字節碼：

```
$ javap -c [類名]
```

默認情況下，通過反編譯得到的Scala以及Java代碼只能看到公有方法的聲明，方法實現以及私有、保護成員均**不可見**。
查看所有成員需要添加`-p/-private`參數：

```
$ javap -private [類名]
$ scalap -private [類名]
```

## Scala REPL
在命令行中輸入無參數的Scala指令即可進入交互式的`Scala REPL`。
在REPL中可以直接輸入代碼並立即獲得反饋。

常用的REPL指令：

| 指令 | 功能 |
| :- | :- |
| :help | 顯示幫助信息 |
| :h? \<string\> | 搜索歷史信息 |
| :history [num] | 顯示輸入歷史 |
| :quit | 退出REPL |
| :reset [options] | 重置REPL的狀態(清空已保存的變量、類、方法等用戶輸入內容) |
| :require \<path\> | 向CLASSPATH中添加JAR包引用 |
| :javap \<path\|class\> | 反編譯源碼文件/類型 |
| :implicits [-v] | 顯示當前作用域下的隱式對象 |
| :type [-v] <\expr\> | 顯示錶達式的類型 |
| :kind [-v] <\type\> | 顯示類型的Kind(型別)信息 |



# Hello World
創建文件`Main.scala`，輸入以下代碼：

```scala
object Main {
  def main(args: Array[String]) =
    println("Hello World!")
}
```

與Java類似，Scala也是從主方法`main`中開始執行整個程序。
Scala中的`main`方法並不定義在類中，而是定義在**單例對象**中(使用`object`關鍵字創建單例對象)。
將`main`方法寫在`class`中能夠通過編譯，但生成的字節碼文件在執行時會出錯。

可以不手動定義`main`方法而讓單例對象繼承`App`特質，即可直接執行代碼語句，例如：

```scala
object Main extends App {
  println("Hello World!")
}
```



# Method (方法)
方法使用`def`關鍵字定義，一個典型的方法格式如下：

```scala
def methodName(args: Type)：Type = {
  /* function_body */
}
```

## 方法返回值
大部分情況下，對於擁有返回值的方法，方法的返回值類型可**省略**：

```scala
def methodName(args: Type) = {
  /* function_body */
}
```

但出於代碼的可讀性考慮，對於公有方法，**不建議**省略返回值類型。

對於方法體僅有單行代碼的情形，可直接省略方法體外部的花括號：

```scala
def methodName(args: Type) = /* function_body */
```

大部分情況下，方法體**不需要**顯式使用`return`關鍵字來給出方法返回值，
編譯器會將方法體內部最後一句代碼的返回值類型做爲整個函數的返回值。
示例：

```scala
def num = {
  200 //編譯器推斷出返回值爲 Int 類型
}
```

在方法具有多個返回點或需要提前返回時，需要顯式使用`return`表示方法結束：

```scala
// 不使用 return 時，方法永遠返回 50
def num(num: Int): Int = {
  if (num < 0) return 20
  if (num == 0) return 30
  50
}
```

方法體內部使用了`return`關鍵字，則返回值不再由編譯器推導，需要手動寫明返回值類型。

方法體前的**等號**代表方法體有返回值，編譯器會推斷方法體的返回值：

- 在顯式指定方法返回類型的情況下，方法體前的等號必須寫出，即使返回類型爲代表無返回值的`Unit`類型。
- 若方法無返回值且未寫出返回類型，方法體前的等號可以省略。

方法和函數的形參**不需要**也**不能**使用`val`、`var`關鍵字修飾，只需寫明類型即可。

## 空參數方法與無參數方法
方法允許省略參數，空的參數表可以直接**省略**，如：

```scala
def getNum: Int = 100
def getNum(): Int = 100 //以上兩個定義只能存在一個
```

無參數方法與空參數方法只能存在一個，二者在使用方式上略有不同：

- 無參方法在調用時只能直接使用方法名，在方法名後加上括號調用就會出錯。
- 空參方法既可以使用帶有括號的方法調用方式，也可以省略括號。

示例：

```scala
scala> def getNum: Int = 100 //定義了方法 getNum: Int
getNum: Int
scala> getNum //正確，返回 100
res0: Int = 100
scala> getNum() //錯誤，提示 error: Int does not take parameters
<console>:12: error: Int does not take parameters
  getNum()
        ^
scala> def getNum(): Int = 200 //定義了方法 getNum(): Int，覆蓋了之前定義的 getNum: Int
getNum: ()Int
scala> getNum //正確，返回 200
res1: Int = 200
scala> getNum() //正確，返回 200
res2: Int = 200
```

同時，無參方法不能與已有字段名稱相同(編譯報錯)，而空參方法允許帶有同名的字段。

## 參數默認值
在Scala中，方法中的參數允許帶有**默認值**：

```scala
scala> var num = 100
num: Int = 100
scala> def setNum(p: Int = 0) { num = p } //方法的參數不能由默認值進行類型推導，即使給參數寫明瞭默認值，也依然需要顯式指明類型
setNum: (p: Int)Unit
scala> setNum() //對於有參數的方法，即使參數帶有默認值使得參數表可以爲空但在調用時依然不能省略括號，否則報錯
scala> println(num)
0 //輸出0
```

若方法中包含多個同類型並帶有默認值的參數，調用時默認匹配第一個參數：

```scala
scala> def func(num1: Int = 100, num2: Int = 200) = println(s"$num1 $num2")
func: (num1: Int, num2: Int)Unit
scala> func(300)
300 200
```

在常見的支持方法參數默認值的編程語言中，參數默認值會有一些限制：

- `C#`中的參數默認值只能是編譯時常量。
- `C++`中的參數默認值可以是成員變量、全局變量，但不能是函數結果。
- `C++`中使用非靜態成員變量做爲參數默認值時，類實例必須設定默認值在之前創建，不能在設定默認值的表達式中創建實例獲取成員變量。

在Scala中方法的參數默認值可以是變量，類內字段，甚至是另一個方法的返回結果。
示例：

```scala
class Test {
  var num = 23333
}

object Main extends App {
  def get(num: Int = (new Test).num) = num //Scala支持使用new操作符創建實例獲取成員字段做爲默認值
  def show(num: Int = get()) = println(num)
  show()
}
```

輸出結果：

```
23333
```

- 默認參數與方法重載

	在Scala中，若一個帶有默認的參數的方法省略默認參數時簽名與一個已經存在的方法相同，
	編譯器並不會報錯(C++編譯器則會報錯)。在調用方法時優先使用**無默認值**的版本(處理邏輯類似於C#)：

	```scala
	object Main extends App {
	  def func() = println("No Args")
	  def func(num: Int = 100) = println(num)
	  func()
	}
	```

	輸出結果：

	```
	No Args
	```

- 具名參數

	在Scala中，調用方法時可以在參數表中寫明參數的名稱，該特性被稱爲**具名參數**。
	對於方法中包含多個同類型並帶有默認值參數的情況下，使用該特性可以顯式指定要傳入的是哪一個參數：

	```scala
	scala> func(num2 = 300)
	100 300
	```

- 默認參數順序

	與C++不同，在Scala中，方法參數的默認值**不需要**從尾部開始連續出現，參數的默認值可以交錯出現：

	```scala
	scala> def func(int: Int, str: String = "String", char: Char, double: Double = 123.0) = println(s"$int $str $char $double")
	func: (int: Int, str: String, char: Char, double: Double)Unit
	scala> func(100, 'c')
	<console>:12: error: not enough arguments for method func: (int: Int, str: String, char: Char, double: Double)Unit.
	Unspecified value parameter char.
	    func(100, 'c')
	        ^
	scala> func(int = 100, char = 'c') //對於默認參數不連續的方法，需要使用"具名參數"特性
	100 String c 123.0
	```



# Function (函數)
函數使用`var/val`關鍵字定義，即函數是一個存儲了函數對象的字段。

一個典型的函數定義如下：

```scala
var functionName: FuncType = 符合簽名的方法/函數/Lambda
```

函數類型爲`Function*`，根據參數數目的不同，
Scala中提供了`Function0[+R]`(無參數)到`Function22[-T1, ..., -T22, +R]`共**23**種函數類型，
即函數最多可以擁有**22**個參數。

函數類型`(A, B, C, ...) => D`形式的語法實際是`Function`類型的語法糖，例如：

- 類型`() => String`實際類型爲`Function0[String]`。
- 類型`Int => String`實際類型爲`Function1[Int, String]`。
- 類型`(Int, Int) => String`實際類型爲`Function2[Int, Int, String]`。
- 依此類推...

函數是一個`Function`類型的實例，方法中的一些特性不能用在函數中：

- 函數**不存在**重載，作用域內的一個函數實例只能有一個實現。
- 函數**不允許**帶有默認值。
- 函數**不允許**定義隱式參數。
- 函數**不允許**柯里化(不能定義多參數表)。
- 函數不能帶有泛型參數。
- 函數參數類型爲**傳名參數**時，需要寫明函數的完整定義，不能採用推導返回值的語法。
- 空參函數的括號不可省略，直接使用函數名不代表調用空參函數，而是訪問函數實例。

示例：

```scala
scala> var show100: () => Int = () => 100
show100: () => Int = <function0>
scala> show100 //直接使用函數名得到的是函數對象而非調用函數
res0: () => Int = <function0>
scala> show100()
res1: Int = 100
```

在Scala中，可以直接使用Lambda創建匿名函數後立即使用：

```scala
scala> ((str: String) => println(str))("Hello World!")
Hello World!
```

與`C++`中的`Lambda`用法類似：

```cpp
#include <iostream>

using namespace std;

int main(void)
{
	[](const string& str) { cout << str << endl; } ("Hello World!");
	return 0;
}
```

然而在`C#`中，`Lambda`需要創建對象或顯式指明類型才能使用，同樣的語句需要寫成：

```cs
using System;

class Test
{
	static void Main(string[] args)
		=> new Action<string>(str => Console.WriteLine(str))("Hello World!");
		//或者寫成 ((Action<string>)(str => Console.WriteLine(str)))("Hello World!");
}
```

## Function Compose (函數組合)
在Scala中，函數允許進行組合。
函數組合有兩種方式：

1. `a compose b`實際調用次序爲`a(b())`。
1. `a andThen b`實際調用次序爲`b(a())`。

方法不能直接進行組合，需要將其轉化爲函數(方法名之後加`_`符號)。

```scala
object Main extends App {

  def add(num: Int) = num + 100
  def double(num: Int) = num * 2

  //只有函數能進行組合,方法需要加"_"符號轉化成函數
  val compose = add _ compose double
  val andThen = add _ andThen double

  println(compose(100) == add(double(100)))
  println(andThen(100) == double(add(100)))
}
```

輸出結果：

```
true
true
```

## Partial Function (偏函數)
偏函數是一個定義域有限的函數，偏函數類似數學意義上的函數，只能接收**一個**參數，只對**有限**的輸入值返回結果。

在Scala中使用類型`PartialFunction[-A, +B]`來表示偏函數。
`PartialFunction[-A, +B]`繼承於`A => B`類型，即偏函數具有普通函數的功能，是普通函數的一類特例。

可以使用**模式匹配**中的`case`語法來定義有限定義域的偏函數，一個最簡單的偏函數如下所示：

```scala
scala> val func: PartialFunction[Int, Int] = { case 0 => 0 }
func: PartialFunction[Int,Int] = <function1>
```

這個偏函數只在輸入值爲`0`時有意義：

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

一個偏函數可以通過添加多個`case`語句塊來添加多個定義域的返回結果：

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

偏函數`func1()`對於定義域`(-∞，0)`返回`-1`，對於定義域`(0, +∞)`返回`1`。

偏函數可以使用`isDefinedAt()`方法來檢驗在給定的參數在偏函數中是否有定義：

```scala
scala> func1.isDefinedAt(10000)
res7: Boolean = true

scala> func1.isDefinedAt(-10000)
res8: Boolean = true

scala> func1.isDefinedAt(0)
res9: Boolean = false
```

使用`orElse()()`方法在一個偏函數沒有定義的時候嘗試調用另一個偏函數：

```scala
scala> func1.orElse(func)(0)
res10: Int = 0
```

函數`func1()`對於`0`沒有定義，而函數`func()`對於`0`有定義，則在參數取`0`時調用`func()`函數的返回值。

使用`case`語法編寫的代碼塊爲`Anonymous Function`(匿名函數)，在上下文語義不明確的情況下，需要顯式指定類型。
示例：

```scala
scala> val func = { case 0 => 0 }
<console>:11: error: missing parameter type for expanded function
The argument types of an anonymous function must be fully known. (SLS 8.5)
Expected type was: ?
       val func = { case 0 => 0 }
                  ^
```

`case`函數語法還可以用在高階函數中。

## Partial Applied Function (部分應用函數)
部分應用函數是邏輯上的概念，表示一個已經指定了部分參數的函數。
將一個擁有多個參數的函數指定部分參數的值構成一個參數較少的新函數，新的函數即爲**部分應用函數**。

Python中的偏函數與Scala中的偏函數是完全不同的概念，Python中偏函數的概念類似於Scala中的部分應用函數。

定義一個擁有2個參數的`sum()`函數，返回兩個參數的和：

```scala
scala> def sum(num1: Int, num2: Int) = num1 + num2
sum: (num1: Int, num2: Int)Int
```

指定第二個參數始終爲`100`，創建一個部分應用函數：

```scala
scala> val sum100 = sum(_: Int, 100)
sum100: Int => Int = $$Lambda$1539/1030946825@62e49cf9

scala> sum100(100)
res11: Int = 200
```

`sum100()`即爲`sum()`指定了第二參數的部分應用函數。



# 塊表達式
在Scala中，花括號`{ }`中可以包含一個或多個語句序列，稱爲**塊表達式**。
塊表達式的**最後一條語句**會做爲塊表達式的結果：

```scala
scala> { println("Block Expr!"); 23333 }
Block Expr!
res3: Int = 23333
```

方法、函數的參數可由對應返回類型的塊表達式替代：

```scala
def test(num: Int) = println(num)

test({
  println("Block Expr!")
  23333
})
```

當方法、函數僅接收**單一參數**時，小括號可省略：

```scala
def test(num: Int) = println(num)

test {
  println("Block Expr!")
  23333
}
```

## 賦值表達式
賦值表達式的值返回值爲`Unit`(無返回值)：

```scala
scala> var _num = 0
_num: Int = 0
scala> def testNum(num: Int): Int = _num = num //由編譯器推斷出的返回值類型爲Unit
<console>:12: error: type mismatch;
found   : Unit
required: Int
  def testNum(num: Int): Int = _num = num
                                      ^
```



# continue 與 break
Scala**沒有**提供主流語言中的`continue`和`break`關鍵字用於流程控制。

## continue
其它語言中的`continue`功能可以通過`for`語句條件後添加`if`判斷條件實現或使用**守衛**。

簡單的例子如下所示：

- `CPP`

	```cpp
	for (auto i : vector<int> { 1, 2, 3 }) {
		if (i > 2) continue;
		else cout << i << endl;
	}
	```

- Scala

	```scala
	for (i <- 1 to 3 if i > 2) println(i)
	```

## break
`break`功能可以由`scala.util.control.Breaks`類提供。
Breaks類中定義了`breakable()`和`break()`成員方法：

```scala
def breakable(op: => Unit): Unit {
  try op catch {
    // 判斷異常是否爲breakException，是則捕獲，其它異常則繼續向外傳遞
    case ex: BreakControl => if (ex ne breakException) throw ex
  }
}
def break(): Nothing = { throw breakException }
```

由代碼可知，`breakable()`方法接收傳名參數`op`，捕獲`breakException`異常。
`break()`方法產生`breakException`異常。

將需要使用break的循環代碼塊作爲傳名參數`op`傳入`breakable()`方法中，
`op`代碼塊中調用`break()`產`breakException`異常被捕獲，中斷函數，達到跳出循環的目的。

使用`Breaks`：

```scala
import scala.util.control.Breaks.{breakable, break}

object Main extends App {

  breakable {
    //使用break的代碼塊作爲傳名參數傳入breakable中
    for (i <- 1 to 10) {
      if (i == 8) break		//跳出循環
    }
  }

}
```



# OOP
Scala是一門同時具有函數式與面向對象特性的**多重範式語言**，除了具有函數式特性外，對**OOP**也有着完整的支持。

## 訪問權限
Scala中沒有`public`關鍵字，成員和類、特質的默認訪問權限即爲**公有**。
Scala中公有類的名稱不強制要求與源碼文件相同，同時一個文件中可以包含多個公有類的定義。

保護成員使用關鍵字`protected`，私有成員使用關鍵字`private`，作用大體上與Java相同，但在訪問權限上支持**更細粒度**的劃分。

- **類、特質、單例對象**定義前可以使用訪問權限修飾，`private`和`protected`權限的**類、單例、特質**等僅限同包內訪問。
- 頂層類允許使用`protected`權限修飾(與Java不同，Java僅允許內部類使用`protected`修飾)。
- 訪問權限關鍵字用於類時，還可以寫在類名與主構造器之間(特質、單例對象沒有這種用法)，用於指定主構造器的訪問權限。
- 訪問級別關鍵字之後可以使用`[]`操作符設定更具體的訪問區域限制。訪問區域限制可以是：
	1. 當前類
	1. 當前定義類的外部類(若存在外部類)
	1. 當前類所屬包名(包內的所有類實例可訪問)
	1. `this`關鍵字(僅當前實例可訪問)
- 訪問權限關鍵字之後若不寫明具體的訪問限制區域，則默認限制爲當前類可訪問(與Java行爲基本一致，但Java中的保護成員包內可見)。

示例：

```scala
package TestCode {

  private class A //類定義前可以使用訪問權限修飾
  protected class B //類定義的訪問權限可以爲protected

  case class Num private(num: Int = 200) //權限修飾符可以用在類名與主構造器之間，代表構造器私有

  // 即使主構造器參數爲空，也不能直接以權限關鍵字結尾
  class Test protected() //或者寫成 class Test protected {}

  class Access(a: Int = 1, var b: Double = 2.0) {
    def showOther1(access: Access) = access.show1 //出錯，access非當前類實例，無訪問權限
    def showOther2(access: Access) = access.show2 //正常訪問
    def showOther3(access: Access) = access.show3 //正常訪問
    private[this] def show1 = println(a + " " + b) //限定當前實例可訪問
    private[Access] def show2 = println(a + " " + b) //類似Java中的private，當前類的任意實例皆可相互訪問私有成員
    private[TestCode] def show3 = println(a + " " + b) //作用域爲包名，此時的訪問權限類似Java中的default訪問權限，當前包中類的實例皆可訪問到該私有成員
  }

}
```

## 字段
Scala類中的字段不僅僅是定義了一個成員變量，編譯器生成字節碼時可能會自動爲字段生成與字段同名的`getter`和`setter`方法。

示例：

```scala
class Test {
  var num: Int = { ... }
  val str: String = { ... }
}
```

生成的Java代碼：

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

若對象的的權限爲私有，則對應生成的`setter`和`getter`方法同樣爲**私有**權限。

生成`setter/getter`方法遵循以下規則：

- `val`關鍵字定義的字段爲**只讀**字斷，編譯器只生成`getter`方法，不生成`setter`方法。
- 若訪問權限爲`private[this]`，則編譯器不會爲其合成`setter`和`getter`方法，
但`protected[this]`和`private`訪問權限正常生成`setter/getter`方法。
- 若定義了字段沒有對其進行初始化，則該字段即爲**抽象字段**。
帶有抽象字段的類前需要加上`abstract`關鍵字，且不能被直接實例化。
- 重寫抽象字段不需要使用`override`關鍵字。

示例：

```scala
class Override {

  var m = 100 //普通成員字段會自動合成setter/getter方法
  /*
   * def m(): Int = m //錯誤，提示重複定義
   * def m_=(m: Int) { this.m = m } //錯誤，提示重複定義
   */
  def m(m: Int) {} //正常，簽名未衝突

  /*
   * 私有this字段不會合成setter/getter方法，
   * 但自行手動定義同名的setter/getter方法時有許多限制(getter方法需要空參且寫明返回值)，
   * 且沒有實用價值(setter方法使用報錯)
   */
  private[this] var num = 100
  def num(): Int = num //正常
  def num_=(num: Int) {
    this.num = num
  } //正常，雖然定義時不報錯，但賦值時報錯
  /*
   * def num = this.num //報錯
   * def num: Int = num //報錯
   * def num: Int = this.num //報錯
   */

  // 常用的私有變量自定義setter/getter風格是私有字段名前加上下劃線
  private[this] var _abc = 0
  def abc = _abc
  def abc_=(abc: Int) = _abc = abc
  /*
   * 也可以寫成：
   * def abc_=(abc: Int) { _abc = abc }
   */
}
```

在Scala中，字段名稱可以與方法名稱**相同**。

- 默認情況下，生成的`setter/getter`方法就與字段同名。
手動在代碼中創建與`setter/getter`簽名相同的方法會導致編譯錯誤。
- 訪問權限爲`private[this]`的字段可以手動定義該字段的`setter/getter`方法(編譯器不自動合成)。
- 在實際編碼過程中，雖然給`private[this]`的字段定義同名的`setter`、`getter`方法不會報錯，
但調用過程中會提示錯誤(如上例子中給num字段賦值會得到錯誤`reassignment to val`，
因此不要手動給字段定義同名的`setter`、`getter`方法)。

此外，由於字段名稱可以與方法名稱相同，因而即使編譯器生成了`setter`、`getter`方法，編碼者依然可以使用字段名稱定義其它簽名的重載函數。

## Constructor (構造器)
在Scala中構造方法的作用與Java類似，用於在創建類實例的同時對指定的成員進行初始化。
Scala中類可以擁有一個**主構造器(primary constructor)**和任意個**輔助構造器(auxiliary constructor)**。

構造器的基本使用方法：

- 主構造器的參數定義緊跟在類名之後，輔助構造器定義在類體中，使用`this`關鍵字。
- 在輔助構造器的代碼中必須立即調用主構造器或其它輔助構造器，之後才能執行其它代碼。
- 調用父類的構造器必須在主構造器中，寫在父類類名之後。

示例：

```scala
/*
 * 構造器參數緊跟在類名之後，構造器中的參數可以帶有默認值
 * 在構造器中創建了字段b，a變量沒有顯式使用var/val關鍵字，同時也沒有被其它方法引用，因而僅僅作爲臨時變量存在
 */
class Constructor(a: Int, var b: Double = 2.0) {

  /*
   * 定義輔助構造器，使用this關鍵字
   * 輔助構造器的函數體中必須最終調用主構造器，輔助構造器即使沒有參數也必須也必須帶括號
   */
  def this() = this(2, 3.0)

}

//只有主構造器能夠調用父類構造器，調用的父類構造器可以是主構造器，也可以是輔助構造器
class ExtendConstructor(a: Int = 2, c: Double = 4.0) extends Constructor(a, c) {
  def this() {
    //a = 100 //代碼要在構造器調用之後，放在this()之前會報錯
    this(2, 4.0)
    //super(2, 4.0) //在Scala中沒有這種用法，父類的構造函數只能由主構造器調用
  }
}
```

- 主構造器作用域

	在Scala中，主構造器的實際範圍爲整個類內作用域。即在類作用域內，可以直接在類內添加普通代碼語句。
	類內的普通代碼語句即爲構造方法的內容，在類實例構造時即被調用：

	```scala
	class Test(str: String) {
	  println(str)
	}
	```

	類體中直接包含了普通的語句代碼，而非成員定義。

	在類內作用域中直接添加普通代碼時，需要考慮變量初始化順序：

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

	輸出結果：

	```
	null
	abc
	```

	類作用域中的普通語句可以直接引用類內定義的成員字段(即使成員字段定義在語句之後)。
	但若成員字段的定義語句在執行語句之後，則成員字段在被引用時**未初始化**。

- 主構造器訪問權限

	在**類名**之後，**主構造器參數**之前可以添加訪問權限修飾符，用於限定主構造器的訪問權限。
	示例：

	```scala
	class Test private(num: Int) {
	  def show() = println(num)
	}

	// Scala中單例模式的寫法
	object Test {
	  lazy val instance = Test()
	  private def apply() = new Test(100) //正確，伴生對象中可以訪問類的私有成員，包括私有主構造器
	}

	object Main extends App {
	  Test.instance.show() //正確，獲取單例
	  new Test(100).show() //錯誤，無法直接訪問私有構造器
	}
	```

- 主構造器參數做爲成員字段

	主構造器的參數中若添加了`var/val`關鍵字，則該參數將作爲類的成員字段存在。

	構造器參數前使用`var`關鍵字：

	```scala
	class Constructor(var num: Int)
	```

	編譯爲Java代碼爲：

	```java
	public class Constructor {
		private int num;
		public int num();
		public void num_$eq(int);
		public Constructor(int);
	}
	```

	可知編譯器爲`var`字段`num`生成了`setter`、`getter`方法和一個與字段同名的私有變量。

	構造器參數前使用`val`關鍵字：

	```scala
	class Constructor(val num: Int)
	```

	編譯爲Java代碼爲：

	```java
	public class Constructor {
		private final int num;
		public int num();
		public Constructor(int);
	}
	```

	可知編譯器爲`val`字段`num`生成了`getter`方法和一個與字段同名的`final`私有變量。

	構造器參數前加上**訪問權限修飾符**則生成的方法類似，
	但方法前會添加對應的訪問權限(Scala中的`protected`限定符編譯爲Java後變爲`public`)。
	示例：

	```scala
	class Constructor0(protected[this] var num: Int)
	class Constructor1(private val num: Int)
	```

	編譯爲Java代碼爲：

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

	只有訪問權限爲`private[this]`時，編譯器纔不會爲引用的字段生成`setter/getter`，而僅僅生成一個私有成員變量。

- 主構造器參數的默認字段生成規則

	主構造器的參數中若沒有使用`val/val`關鍵字，則默認修飾爲`private[this] val`。
	編譯器默認不會爲該參數生成`setter/getter`方法以及私有成員變量，除非被其它成員方法引用。
	示例：

	```scala
	class Constructor0(num: Int)
	class Constructor1(private[this] val num: Int)
	```

	編譯爲Java代碼爲：

	```java
	public class Constructor0 {
		public Constructor0(double);
	}
	public class Constructor1 {
		public Constructor1(double);
	}
	```

	編譯得到的Java代碼完全相同。

	當該參數被其它成員方法引用時，編譯器會爲其生成對應的`final`私有成員變量(但沒有生成`setter/getter`)。
	只要構造器參數沒有使用`var`關鍵字標記，則生成的成員變量就帶有`final`屬性。
	示例：

	```scala
	class Constructor0(num: Int) {
	  def get = num
	}
	class Constructor1(private[this] val num: Int) {
	  def get = num
	}
	```

	編譯爲Java代碼爲：

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

	輔助構造器中的參數與普通函數參數類似，僅在構造器代碼段內部生效(不作爲字段存在)，輔助構造器的參數前不能添加`var/val`關鍵字。

- 默認構造方法

	一個類如果沒有顯式寫明主構造器參數，則默認生成一個**空參**構造方法。

	對於一個如下的**空類**：

	```scala
	class Empty
	```

	實際相當於：

	```scala
	class Empty() { }
	```

	編譯成Java代碼後爲：

	```java
	public class Empty {
		public Empty() { ... };
	}
	```

	可以採用如下方式實例化：

	```scala
	new Empty()
	new Empty //空參方法括號可省略
	```

	與主流的OOP語言不同，一個使用默認生成的空參構造函數的作爲主構造器的類即使定義了其它構造器，默認生成的主構造器**依然存在**。
	示例：

	```scala
	class Default {
	  def this(num: Int) = this
	}
	```

	編譯成Java代碼後爲：

	```java
	public class Default {
		public Default();
		public Default(int);
	}
	```

	可以看到，默認的空參構造方法依然存在。

	主構造器不能在類體中重新定義：

	```scala
	class Default {
	  //編譯報錯，主構造器已爲空參，不能重複定義
	  def this() { ... }
	}
	```

## 多態
Scala作爲OOP語言，支持多態。

- 重寫

	子類重寫父類的非抽象方法、字段時，需要顯式地在方法定義前加上`override`關鍵字，否則無法通過編譯。
	實現抽象方法則不需要。

	重寫遵循以下規則：

	- `def`只能重寫另一個`def`。
	- `val`可以重寫另一個`val`以及不帶有參數的`def`。
	- `var`只能重寫另一個抽象的`var`(即只有定義沒有實現)。

- 重載

	Scala支持方法重載，簽名不同名稱相同的方法可以共存。
	Scala可以使用**操作符**作爲方法名稱，可以實現類似**C++/C#**中**操作符重載**的效果。

## 複製類實例
Scala與Java類似，類實例賦值僅僅是複製了一個引用，實例所指向的內存區域並未被複制。

若需要真正複製一個對象，需要調用對象的`clone()`方法。`clone()`方法定義在`Object`類中，
但由於是`protected`成員，不可直接調用，若需要自行實現類的複製功能，則需要實現`Cloneable`接口。

示例：

```scala
class Clone extends Cloneable {
  var nums = Array(1, 2, 3)
  var str = "TestClone"
  override def clone = {
    // Cloneable接口中clone()返回的是Object型，即Scala中的Any，需要進行強制類型轉換
    val clone = super.clone.asInstanceOf[Clone]
    clone.nums = nums.clone //深複製需要對成員中的引用類型調用clone()
    clone
  }
}
```

與Java中類似，如果需要實現**深複製**，則需要對類成員中的`AnyRef`及其子類調用`clone()`進行復制。
對於`AnyVal`子類如`Int`、`Double`等類型，沒有提供重載的`clone()`方法，但這些類型默認即爲值複製，無需額外的操作。
Java中的特例`java.lang.String`在Scala中同樣有效，對於`String`類型，在重寫`clone()`時也可當作基本類型對待。

在Scala中，還可以直接繼承`scala.collection.mutable.Cloneable[T]`特質：

```scala
import scala.collection.mutable.Cloneable

class Clone extends Cloneable[Clone] {
  var nums = Array(1, 2, 3)
  var str = "TestClone"
  override def clone = {
    val clone = super.clone //不必進行強制類型轉換，類型已在泛型參數中指定
    clone.nums = nums.clone
    clone
  }
}
```

## 匿名類初始化
在Scala中，創建類實例的**同時**可以直接對類的成員變量進行初始化。

示例：

```scala
object Init extends App {
  val num = new Num {
    num = 100
    name = "Num"
  } //相當於創建了一個匿名類，然後向上轉型到類Num上
  println(s"${num.name} ${num.num}") //正常輸出了初始化的值
}

class Num {
  var num: Int = 0
  var name: String = ""
}
```

以上代碼用**Java**改寫爲：

```java
class Init {
	public static void main(String[] args) {
		Num num = new Num() {{
			num = 100;
			name = "Num";
		}}; //匿名類的構造函數的函數名爲空，因此可以使用大括號直接嵌套的方式
		System.out.println(num.name + " " + num.num);
	}
}

class Num {
	int num = 0;
	String name = "";
}
```

輸出結果：

```
Num 100
```



# Singleton Objects (單例對象)
使用`object`關鍵字定義單例對象。
單例對象是一個實例，可以在單例對象內部定義常見的內容，如字段、方法等：

```scala
scala> object Test { val num = 2333; private[this] val msg = "6666"; def show() = println(msg) }
defined object Test

scala> Test.num
res1: Int = 2333

scala> Test.msg //單例對象的內部成員支持訪問權限控制
<console>:13: error: value msg is not a member of object Test
       Test.msg
            ^

scala> Test.show()
6666
```

## 單例類型
單例對象可以繼承其它類型、混入特質：

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

單例對象的類型使用`單例名稱.type`表示單例自身的類型。
繼承了類、混入了特質的單例的單例類型能夠正常通過繼承關係的判定。
示例：

```scala
scala> import scala.reflect.runtime.universe.typeOf
import scala.reflect.runtime.universe.typeOf

scala> typeOf[Test.type] //單例自身的類型信息
res1: reflect.runtime.universe.Type = Test.type

scala> typeOf[Test.type] <:< typeOf[Base]
res2: Boolean = true

scala> typeOf[Test.type] <:< typeOf[Trait]
res3: Boolean = true
```

## 初始化
單例對象默認即帶有延遲初始化的特性。
單例在定義時並未初始化，初始化行爲發生在單例首次被訪問時。

若在單例構造器中添加帶有副作用的語句，則副作用會在首次訪問單例時出現。
示例：

```scala
scala> object Test { println("Init Singleton Test") }
defined object Test

scala> Test //首次訪問單例，單例進行初始化，觸發副作用
Init Singleton Test
res0: Test.type = Test$@16ea0f22

scala> Test //再次訪問單例，單例已被初始化，不再觸發副作用
res1: Test.type = Test$@16ea0f22
```

## Companions (伴生對象)
`Companions`(伴生對象)是一類特殊的單例對象。
每一個類可以擁有一個同名的**伴生對象**(單例)，伴生對象具有以下特徵/限制：

- 一個類和其伴生對象的定義必須寫在同一個文件中。
- 伴生對象與同名類之間可以相互訪問私有、保護成員。

Scala相比Java是更加純粹的面嚮對象語言，Scala中沒有`static`關鍵字和**靜態成員**的概念，
Scala使用**伴生對象**來達到近似靜態成員的作用。
對於Java代碼中定義的靜態字段、靜態方法，在Scala中也以單例對象的語法進行訪問。



# Trait (特質)
Scala中的`trait`特質對應Java中的`interface`接口。
相比Java中的接口，Scala中的特質除了不能自定義有參構造器、不能被直接實例化之外，擁有絕大部分類的特性。

trait內可以添加普通代碼語句(默認構造器)、定義成員變量以及成員方法。
trait內的成員方法可以爲抽象方法，也可以帶有方法的實現。
trait中的成員同樣可以設置訪問權限。

## Mixin (混入)
Scala不支持**多重繼承**，一個類只能擁有一個父類，但可以**混入(mixin)**多個特質。

- **Mixin**機制相比傳統的單根繼承，保留了多重繼承的大部分優點。
- 使用`with`關鍵字混入特質，一個類中混入多個特質時，會將第一個擴展的特質的父類作爲自身的父類，同時，後續混入的特質都必須是從該父類派生。
- 若同時繼承類並混入特質，需要將繼承的類寫在`extends`關鍵字的後面，`with`只能混入**特質**，不能混入**類**。

示例：

```scala
class BaseA

class BaseB

trait TraitA extends BaseA

trait TraitB extends BaseB

/* 編譯報錯，提示：
 * superclass BaseA
 * is not a subclass of the superclass BaseB
 * of the mixin trait TraitB
 */
class TestExtend extends TraitA with TraitB

/* 編譯報錯，提示：
 * class BaseA needs to be a trait to be mixed in
 */
class ExtendClass extends TraitA with BaseA
```

`TestExtend`類中，特質`TraitA`的父類`BaseA`並不是特質`TraitB`父類`BaseB`的父類，而Scala中一個類只能擁有一個父類，因而無法通過編譯。
`ExtendClass`類中，應該繼承`BaseA`後混入特質`TraitA`，`with`關鍵字之後的必需是特質而不能是類名。

## 重寫衝突方法/字段
混入機制需要解決**富接口**帶來的成員衝突問題。
當一個類的父類與後續混入的特質中帶有相同名稱的字段或相同簽名的方法時，需要在子類重寫這些衝突的內容，否則無法通過編譯。

示例：

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
  override def get = 77 //對於衝突的內容，必需顯式重寫
}
```

## 構造順序
對於混入的內容，按照以下順序進行構造：

1. 按繼承樹依次從最外層的父類開始構造。
1. 按照特質出現的順序從左往右依次構造特質。
1. 在一個特質中，若該特質存在父特質，則先構造父特質。若多個特質擁有相同的父特質，該父特質不會被重複構造。
1. 最後構造當前類。

示例：

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
    println("Now") //當前特質最後進行構造
  }
}
```

輸出結果：

```
ClassBase
ClassChild
TraitBase
TraitA
TraitB
Now
```

## 線性化與 super 關鍵字
Scala的混入機制是**線性化**的，對於衝突的內容，構造中的後一個實現會頂替前一個。
線性化順序與構造順序**相反**，對於同名字段的內容，最終保留的是最右端的類或特質的實現。
示例：

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
  // 使用父類的實現時不需要顯式指定到底是哪一個，編譯器會自動按照線性化順序選擇最後的實現，即TraitC中的實現，即返回111
  override def get = super.get
}
```

使用`super`關鍵字可調用父類、父特質中混入的方法實現，具體調用的實現內容由線性化順序決定。
亦可使用`super[T].xxx`語法顯式指定使用某個父類/父特質中的實現。
super關鍵字具有以下限制：

- 僅能引用直接混入的類或特質的方法，不能使用繼承層級中更遠的類或特質

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

	  override def get = super[BaseA].get //正確，顯式使用父類BaseA中的實現，即返回123

	  /* 錯誤，super關鍵字引用父類/父特質的實現時必需使用直接混入的類或特質，不能使用繼承層級中更遠的類或特質
	   * 編譯報錯：error: super may not be used on value get
	   */
	  override def getTraitB = super[TraitB].get
	}
	```

- 僅能引用混入類或特質的方法，不能引用使用var/val定義的字段

	```scala
	class Base {
	  val num = 123
	}

	class TestExtend extends Base {
	  /* 錯誤，super關鍵字僅能引用父類/父特質的方法，不能引用字段
	   * 編譯報錯：error: super may not be used on value num
	   */
	  override val num = super.num + 1
	}
	```

## 線性化與 override 關鍵字
在重寫抽象字段時，是否使用`override`關鍵字在混入時行爲存在差異。
示例：

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
  new NameA extends NameB //編譯出錯
}
```

混入兩個重寫了同一個抽象方法/字段的特質時，若未使用`override`關鍵字，則混入時編譯出錯，需要顯式重寫衝突內容。

若特質使用了`override`關鍵字進行重寫，則混入時依據線性化順序決定最終的實現(保留最後混入的實現)。
示例：

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

混入多個存在衝突內容的特質時，不需要所有的特質都使用`override`關鍵字進行重寫，
僅需要最後一個混入的特質使用`override`重寫衝突內容。
示例：

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
  (new NameB extends NameA).name //編譯出錯
}
```

## 線性化與類型關係
在混入帶有衝突內容的特質時，衝突內容的類型不能爲完全無關的類型，如下所示：

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

混入同名字段時，同名字段的類型可以不完全相同，但需要滿足繼承關係，同時子類位於線性化順序的**最右端**，
即滿足`最右端類型 <: 同名字段類型鏈中最具體的類型`，如下所示：

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

線性化過程中，同名字段`t`使用更具體的子類類型取代了父類類型。
調整混入順序，則出現類型不兼容的提示：

```scala
scala> trait TestMixin extends TraitB with TraitA
<console>:13: error: overriding value t in trait TraitB of type Child;
 value t in trait TraitA of type Base has incompatible type
       trait TestMixin extends TraitB with TraitA
             ^
```

線性化的最右端需要爲更**具體**的類型，但混入順序中間的同名字段不必都比前一個同名字段更具體
(中間字段類型僅需存在父子類關係即可，可爲基類)，如下所示：

```scala
scala> trait TestMixin extends TraitB with TraitA { val t: Child }
defined trait TestMixin //同名字段的混入類型鏈爲 Child => Base => Child
```

## 線性化與泛型
當混入特質帶有同名字段類型爲泛型參數時，只要泛型參數滿足繼承類型約束，並保證子類位於線性化順序的最右端，
同樣可以正常進行類型定義，如下所示：

```scala
scala> trait Test
defined trait Test

scala> trait TraitA { val t: Test }
defined trait TraitA

scala> trait TraitB[T <: Test] { val t: T }
defined trait TraitB

scala> trait TestMixin[T <: Test] extends TraitA with TraitB[T]
defined trait TestMixin //使用類型下界

scala> trait TestMixin[T <: Test] extends TraitB[T] with TraitA { val t: T }
defined trait TestMixin //同名字段的混入類型鏈爲 T => Test => T

scala> trait TraitC[T >: Test] { val t: T }
defined trait TraitC

scala> trait TestMixin[T >: Test] extends TraitC[T] with TraitA
defined trait TestMixin //使用類型上界

scala> trait TestMixin[T >: Test] extends TraitA with TraitC[T] { val t: Test }
defined trait TestMixin //同名字段的混入類型鏈爲 Test => T => Test
```



# Case Class (樣例類)
樣例類是一種特殊的類，通常用在**模式匹配**中。
在類定義前使用`case`關鍵字即可定義一個樣例類。

相比普通的類，樣例類有以下特性：

- 樣例類構造器中的字段默認使用`val`關鍵字定義(即默認爲公有訪問權限，而不是普通類默認的`private[this]`)。
- 樣例類默認即實現了`apply()`方法用於構造對象和`unapply()`方法用於模式匹配。
- 樣例類默認實現了`toString`、`equals`、`hashCode`、`copy`等其它方法。
- 樣例類實現了序列化接口。

示例：

```scala
case class Case(num: Int = 100, str: String)

object Main extends App {

  var ca = Case(str = "S13")
  println(ca.num + " " + ca.str)

  // 使用樣例類提供的copy()方法可以複製出一個字段值相同的類
  var caCopy = ca.copy()
  println(caCopy.num + " " + caCopy.str)

  // 也可以在copy()只複製需要的值甚至不使用原先對象的值
  var caCopy1 = ca.copy(200)
  var caCopy2 = ca.copy(str = "Abc")
  var caCopy3 = ca.copy(50, "ABC")
  println(caCopy1.num + " " + caCopy1.str)
  println(caCopy2.num + " " + caCopy2.str)
  println(caCopy3.num + " " + caCopy3.str)

  // 樣例類的實例之間可以直接比較,只要構造器中的字段值相同便會返回true
  println(ca == caCopy)

  // 樣例類經常用於模式匹配中(unapply()方法的應用)
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

輸出結果：

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

## 避免重定義樣例類自動生成的方法
手動創建樣例類的伴生對象時，應避免定義與樣例類自動生成方法簽名相同的方法(`apply()/unapply()`等)
，否則編譯報錯，如下所示：

```scala
object Main extends App {

  case class Case(num: Int)

  object Case {
    def apply(num: Int) = new Case(num) //編譯報錯
    def unapply(arg: Case) = Option(arg.num) //編譯報錯
  }

}
```

錯誤提示：

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

若伴生對象中的自定義方法與默認生成的方法簽名不同，則正常編譯，如下所示：

```scala
object Main extends App {

  case class Case(num: Int)

  object Case {
    def apply(num1: Int, num2: Int) = new Case(num1 + num2) //正常編譯
    def unapply(arg: (Case, Case)) = Option(arg._1.num, arg._2.num) //正常編譯
  }

}
```



# 類型
在Scala中，所有的類型**皆爲對象**，所有類型都從根類`Any`繼承，`Any`有`AnyVal`和`AnyRef`兩個子類。

## 值類型
基礎類型如`Int`、`Float`、`Double`、`Unit`等全部從`AnyVal`類中派生。
可以直接在泛型中直接使用這些類作爲類型參數。
同時，Scala中提供了`隱式轉換(ImplicitConversion)`來保證`Int`、`Float`、`Double`等類型之間可以**自動進行轉換**。

所有的基礎類型之外的引用類型派生自類`AnyRef`。

- 基礎類型轉換

	基礎類型與字符串(String)等類型之間的轉換也由類提供的成員函數進行。
	將數值與字符串相互轉換，如下所示：

	```scala
	val str = 100.toString
	val num = str.toInt
	```

## Bottom (底類型)
Scala中存在底類型(`Bottom Type`)。底類型包括`Nothing`和`Null`。

- `Nothing`

	`Nothing`是所有類型的子類型，定義爲`final trait Nothing extends Any`。
	Nothing特質沒有實例。

	一些特殊的操作返回類型爲Nothing，如拋出異常：

	```scala
	scala> def e = throw new Exception
	e: Nothing
	```

	Nothing做爲返回類型能協助更精確地進行類型推導。
	例如，在`if`語句中拋出異常：

	```scala
	scala> def num(n: Int) = if (n > 0) n else throw new Exception
	num: (n: Int)Int
	```

	拋出異常的語句返回值類型爲Nothing，是任意類型的子類(也是Int的子類)，整條語句返回值類型被推導爲Int。

- `Null`

	`Null`是所有引用類型`AnyRef`的子類型。
	Null特質擁有唯一實例`null`(類似於Java中null的作用)。

## Option (可空類型)
`Option[T]`表示可空類型，`Option[T]`包含兩個子類：

- `Some[T]`，代表包含有效值。
- `None`，代表值不存在。

`Optionp[T]`類型的伴生對象中提供了`apply()`方法用於構建實例：

- 任意的非`null`值會得到`Some[T]`返回值。
- `null`值會得到`None`返回值。

示例：

```scala
scala> Option(123)
res10: Option[Int] = Some(123)

scala> Option(null)
res11: Option[Null] = None
```

其它常用方法如下所示：

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

使用`get`方法獲取值，目標值不存在時會觸發異常。
使用`getOrElse()`方法獲取值，參數中需要傳入備用的默認值，目標值不存在時將使用默認值做爲返回結果。
示例：

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

`foreach()`高階函數會在值存在時應用操作：

```scala
scala> Option(123) foreach println
123 //有值時打印輸出

scala> Option(null) foreach println  //無值時無輸出
```

`map()`高階函數用於將目標值映射到新的`Option`中。
`fold()`高階函數用於使用目標值執行表達式並輸出返回結果，在目標值不存在時使用提供的值做爲返回結果，
提供的值需要與表達式返回結果類型相同。
示例：

```scala
scala> Option("abc") map (_.length)
res4: Option[Int] = Some(3)

scala> Option.empty[Int] map (_.length)
res5: Option[Int] = None

scala> Option("abc").fold(0)(_.length)
res8: Int = 3 //目標值存在時輸出表達式結果

scala> Option.empty[String].fold(0)(_.length)
res9: Int = 0 //目標值不存在時使用提供的值做爲返回結果
```

可空類型也可以用於**模式匹配**中，如下所示：

```scala
object TestOption extends App {
  val l = Option(123) :: None :: Nil
  for (num <- l) num match {
    case Some(x) => println(x)
    case None => println("No Value")
  }
}
```

運行結果：

```
123
No Value
```




# Pattern Matching (模式匹配)
**模式匹配**是Scala的核心功能之一。
Scala的**模式匹配**提供了諸多強大的特性，主要功能如下：

- 跳轉表(類似與主流語言中的`switch`語句)
- 類型匹配
- 條件執行
- 解構(`destructuring`)

## 簡單匹配
**模式匹配**能夠提供與其他語言中`switch`語句類似的簡單匹配功能。

使用`match`關鍵字開始一個模式匹配語句。
使用`case`關鍵字添加一個匹配值。

基本語法如下所示：

```scala
變量 match {
  case 條件1 => ...
  case 條件2 => ...
  ...
  case _ => ...
}
```

Scala中的`match`語句具有返回值，可爲變量賦值。
Scala中沒有`break`關鍵字，`match`語句中的`case`條件不會被穿越。
某些需要穿越`case`條件的情形，應使用`|`操作符連接多個條件。

每個`case`條件語句可以使用`@`操作符綁定一個變量名。
每個`case`條件之後可以添加**守衛**(`if 條件語句...`)，用於添加額外的匹配條件。

示例：

```scala
object Main extends App {

  val (str0, str1, str2, str3, str4) = ("str0", "str1", "str2", "xxxx", "")

  def switch(str: String) = {
    print(s"String: $str => ")
    str match {
      case "str0" => println("Match case str0"); 0
      case "str1" | "str2" => println("Match case str1 | str2"); 1 //使用 | 操作符連接多個模式匹配條件
      case s@_ if s.length > 3 => //使用 @ 操作符指代整個匹配條件，使用 if 添加守衛
        println("Match case which string's length is larger then 3"); s.length
      case s@("a" | "bb" | "cccc") => s.length //使用 @ 指代多個匹配條件
      case _ => println("No match"); -1
    }
  }

  val re0 = switch(str0) //case語句後的最後一句做會做爲整個match表達式的返回值
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

輸出結果：

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

## 類型匹配
**模式匹配**可用於匹配對象的實際類型。

對於以基類傳入的對象實例，使用模式匹配可以匹配其真實類型。
示例：

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
    case _: CSharp | _: Cpp => println("Match C# or CPP!") //匹配多種類型
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

輸出結果：

```
Scala is best!
Match C# or CPP!
Match C# or CPP!
Other language: Haskell
Other language: Java
No match!
```

當模式匹配匹配泛型類型時，由於`JVM`採用`Type Erasure`的方式實現泛型，因而泛型類型的泛型參數無法準確匹配，如下所示：

```scala
object Main extends App {

  val list = 1 :: 2 :: 3 :: Nil // list實際類型爲List[Int]

  list match {
    case _: List[String] => println("Match type: List[String]")
    case _: List[Int] => println("Match type: List[Int]")
    case _ => println("No match!")
  }

}
```

輸出結果：

```
Match type: List[String]
```

由輸出結果可知，模式匹配並未正確匹配類型的泛型參數。對於此類情況，Scala編譯器在編譯時會對代碼做出警告。

## 解構
**模式匹配**可用於解構任意定義了`unapply()`方法的類型。

常見的數據結構如**元組**、`List[T]`等均支持解構操作。<br>
解構元組、`List[T]`：

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
scala.MatchError: (1,2,3) (of class scala.Tuple3) //元組數目不匹配，出錯
  at .destruct(<console>:14)
  ... 27 elided
```

亦可使用`Case Class`(樣例類)特性定義爲模式匹配優化的類，樣例類會自動生成用於解構的`unapply()`方法。<br>
解構樣例類：

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

解構類型時，亦可使用**值匹配**(多個候選值同樣使用`|`操作符連接)，還可使用`@`操作符指代匹配表達式/子表達式，如下所示：

```scala
scala> def destruct(obj: Any) = obj match {
     |   case m@Manager("A" | "B", _) => m.toString //解構表達式中匹配多個值，使用 @ 指代整個匹配表達式
     |   case User(_, age@(10 | 20 | 30)) => s"Age: $age" //使用 @ 指代局部匹配表達式
     | }
destruct: (obj: Any)String
```

### 解構Lambda
若一個方法僅接收一個Lambda作為參數，而Lambda的參數為可以結構類型，
則在定義Lambda參數時可直接將複雜的可解構類型解構成更細粒度的參數，語法：

```scala
// 方法定義
def methodName(... => ...) = ...

// 方法調用(若需要解構參數，則不能使用小括號語法進行調用)
methodName {
  case ... => ...
}
```

示例：

```scala
// Lambda的簽名中接收的參數為可解構類型
scala> (Some("Name1" -> 1) :: Some("Name2" -> 2) :: Nil).foreach
   final override def foreach[U](f: Some[(String, Int)] => U): Unit

scala> (Some("Name1" -> 1) :: Some("Name2" -> 2) :: Nil).foreach {
     | case Some((name, value)) => println(s"$name -> $value") // 直接解構了參數
     | }
Name1 -> 1
Name2 -> 2
```

## unapply() 與 unapplySeq()
**提取器**用於解構對象，通過實現`unapply()`方法定義解構行爲。

- `unapply()`方法則與`apply()`方法相反，可以從對象中提取出需要的數據(在實際使用過程中，可以從任意的目標裏提取數據)。
- `unapply()`方法返回值必須爲`Option`及其子類，單一返回值使用`Option[T]`，
多個返回值可以包含在元組中`Option[(T1, T2, T3, ...)]`。
- `unapply()`方法雖然也可以定義在類中，但一般定義在**伴生對象**中(在類中定義沒有合適的語法使用)。

假設有伴生對象名爲`Unapply`，則：

```scala
val Unapply(arg1, arg2, arg3, ...) = value
```

等價於：

```scala
val (arg1, arg2, arg3, ...) = Unapply.unapply(value)
```

示例：

```scala
object TestUnapply extends App {
  val Unapply(num1) = 1 //提取一個值
  println(num1)
  val Unapply(num2, num3) = Unapply(100, 200) //提取多個值
  println(num2 + " " + num3)
}

object Unapply {
  def apply(num1: Int, num2: Int) = new Unapply(num1, num2)
  def unapply(num: Int) = Option(num)
  def unapply(a: Unapply) = Option((a.num1, a.num2))
}

class Unapply(var num1: Int, var num2: Int)
```

輸出結果：

```
1
100 200
```

若需要提取**任意長度**的值的序列，則可以使用`unapplySeq()`方法，該方法返回值類型爲`Option[Seq[T]]`。
**不要**同時定義`unapplySeq()`方法和`unapply()`方法，會產生衝突。

示例：

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
  def unapplySeq(str: String) = Option(str split "\\.") //split()方法接收的是正則表達式，小數點、加減乘除之類的符號需要轉義
}
```

輸出結果：

```
Case Nothing
abc cde
abc cde efg
```



# apply() 與 update()
`apply()/update()`方法是Scala中的**語法糖**。

假設有一個**實例**`instance`，使用：

```scala
instance(arg1, arg2, arg3, ...)
```

此表達式等價於：

```scala
instance.apply(arg1, arg2, arg3, ...)
```

同樣的，使用：

```scala
instance(arg1, arg2, arg3, ...) = value
```

等價於：

```scala
instance.update(arg1, arg2, arg3, ..., value)
```

示例：

```scala
object Main extends App {
  var a = new Apply(0, 0)
  val show = () => println(a.num1 + " " + a.num2)
  a(1) //相當於調用 a.apply(1)
  show() //輸出 1 2
  a(100, 200) = Apply(10, 20) //相當於調用 a.update(100, 200, new Apply(10, 20))
  show() //輸出 90 180
  Apply(1000, 2000) = a
  show() //輸出 1000 2000
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

// 單例對象同樣可以定義 apply()/update() 方法
object Apply {
  def apply(num1: Int, num2: Int) = new Apply(num1, num2)
  def update(num1: Int, num2: Int, test: Apply) {
    test.num1 = num1
    test.num2 = num2
  }
}
```

輸出結果：

```
1 2
90 180
1000 180
```

## 無參 apply 方法
`apply()`方法對應的無參數形式`apply`方法在通常情形下並不生效，字段、類會被優先解析爲本身的含義(值、類型)，如下所示：

```scala
scala> object Test { def apply { println("Print test") } }
defined object Test

scala> Test //直接使用單例對象名稱被解析爲單例對應類型
res1: Test.type = Test$@3a5b7d7e

scala> Test.apply //顯式調用 apply 方法
Print test

scala> class Test { def apply { println("Print test") } }

scala> val t = new Test
t: Test = Test@4c5379f5

scala> t //直接使用字段名稱被解析爲字段自身
res8: Test = Test@4c5379f5

scala> t.apply //顯式調用 apply 方法
Print test
```

在無參apply方法帶有**泛型參數**時，可以正常使用帶有泛型參數的省略形式，如下所示：

```scala
scala> object Test { def apply[T] { println("Print test") } }

scala> Test[Any] //帶有泛型參數，省略 apply 方法，正常執行調用
Print test

scala> class Test { def apply[T] { println("Print test") } }

scala> val t = new Test
t: Test = Test@6f88319b

scala> t[Any] //字段名稱帶有泛型參數，亦被解析爲無參泛型 apply 調用
Print test
```



# sealed 與 final 關鍵字
`sealed`和`final`都是Scala語言的**關鍵字**。

- `final`關鍵字作用與Java中相同：

	`final`用在類之前，表示類不可繼承；
	`final`用在方法之前，表示方法不可被重寫。

- `sealed`關鍵字作用與`C#`中的`sealed`不同：

	C#中的sealed類似Java/Scala中的final，表示類型不可繼承。
	在Scala中，sealed的作用是防止繼承被濫用。
	sealed修飾的類僅能在該類所屬的源碼文件中定義子類，即禁止從外部增加sealed類的子類。

## sealed 用於模式匹配
使用`sealed`關鍵字修飾的類型用於模式匹配時，編譯器會對匹配條件進行檢查。
若匹配路徑沒有被完全覆蓋，則會給出警告：

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

編譯時會得到警告：

```
Main.scala:10: warning: match may not be exhaustive.
It would fail on the following input: CSharp(_)
  lang match {
  ^
one warning found
```

編譯器提示**匹配可能會有遺漏**。若代碼中去掉基類定義前的`sealed`關鍵字，則編譯器不再輸出警告。

## sealed 與 ADT
Scala中sealed類概念上類似於純函數式語言中的`ADT`(Algebraic Datatypes，代數數據類型)。

上文中的例子使用Haskell編寫近似於：

```hs
data Lang =
  C { name :: String } |
  CPP { name :: String } |
  CSharp { name :: String } deriving (Show, Eq)

getLangName :: Lang -> String
getLangName (C name) = name
getLangName (CPP name) = name
```



# 格式化輸出
使用`print()/println()`可以打印`String`類型的文本輸出。複雜文本可以使用類似Java的字符串拼接方式(使用操作符`+`)。

- `StringLike.format()`方法。
- `StringContext`類中的`s()`、`f()`、`raw()`等插值器方法用於以指定的方式輸出字符串。

## StringLike.format() 格式化輸出
在Scala中，字符串依然使用Java中標準的`String`類型，但通過**隱式轉換**特性，`String`可以被自動構造爲`StringLike`類型。

`StringLike`類型提供了一系列方便強大的字符操作方法，格式化字符串可以使用其提供的`format()`方法
(使用方式類似於靜態方法`String.format()`，但使用方法調用者作爲格式化內容而非方法的首個參數)，如下所示：

```scala
scala> "Test format str:\nString %s\nInt %d\nFloat %f\n".format("Hello World!", 666, 666.666)
res0: String =
"Test format str:
String Hello World!
Int 666
Float 666.666
"
```

## s字符串插值器
在`Scala 2.10`之後，還可以使用字符串插值器`s""`，基本用法如下所示：

```scala
scala> var str = "Hello World"
str: String = Hello World

// 使用插值器後，在變量前使用"$"符號即可將變量值作爲文本插入
scala> s"The str is $str"
res0: String = The str is Hello World

scala> var num = 200
num: Int = 200
scala> s"The num is $num"
res1: String = The num is 200
```

使用`${expr}`的方式可以在插值器中引用複雜表達式：

```scala
scala> var (a, b, c) = (1, "Test", 2.0)
a: Int = 1
b: String = Test
c: Double = 2.0

scala> s"${"%d %s %f".format(a, b, c)} ${a + c}"
res2: String = 1 Test 2.000000 3.0
```

`s""`字符串插值器實際上相當於調用`StringContext.s()`，`r""`、`raw""`插值器類似。

## f字符串插值器
除了`s""`字符串插值器，還有帶有格式化功能的`f""`插值器。

相比s插值器，f插值器可以帶有格式化參數，在不使用格式化參數的情況下，f插值器作用與s插值器相同。
示例：

```scala
scala> var (a, b) = (1.0, 2.5)
a: Double = 1.0
b: Double = 2.5

// 引用變量之後緊跟格式化字符
scala> f"$a%6.3f $b%10.5f"
res3: String = " 1.000    2.50000"
```

## raw字符串插值器
`raw""`插值器用法與`s""`類似，但不會轉義反斜槓。
示例：

```scala
scala> raw"\n\s\\b\\%''^#@ $num"
res15: String = \n\s\\b\\%''^#@ 3.0
```



# 終端輸入
早期的Scala中`Console`類提供了一系列的終端輸入方法，在現在的版本中這些方法已經被**廢棄**。
當前版本的Scala獲取終端輸入需要使用包`scala.io.StdIn`中的相關方法。

`scala.io.StdIn`中的相關方法簽名與先前的`Console`類中完全相同，主要API介紹：

- 使用`readLine()`獲取單行文本輸入，返回`String`類型。
- 使用`readInt()/readFloat()/readChar()/readLong()...`等方法獲取特定類型的輸出，當輸入的內容不匹配時，會拋出異常。
- 使用`readf()/readf1()/readf2()/readf3()`等方法能以`java.text.MessageFormat`語法格式化接收的終端輸入。

示例：

```scala
scala> val str = scala.io.StdIn.readLine() //自行腦補終端輸入 "Test input"
str: String = Test input
scala> val int = scala.io.StdIn.readInt() //自行腦補終端輸入 "200"
int: Int = 200

// 輸入內容不匹配讀取類型時會拋出異常
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

// readf() 可以接收任意數量的值，返回值爲 List[Any] 類型
scala> val list = scala.io.StdIn.readf("{0} + {1}") //自行腦補終端輸入 "Test + Input"
list: List[Any] = List(Test, Input) //按照格式化字符串提取出了輸入內容
scala> list foreach println
Test
Input

// readf1() 僅能接收一個值，返回接收的值
scala> val num = scala.io.StdIn.readf1("This is {0}") //自行腦補終端輸入 "This is 666"
num: Any = 666
// readf2()/readf3() 接收兩個/三個值，返回值爲 Tuple 類型
scala> val tuple = scala.io.StdIn.readf3("{0} + {1} + {2}") //自行腦補終端輸入 "One + Two + Three"
tuple: (Any, Any, Any) = (On,Two,Three)
```



# Enumerate (枚舉)
在Scala中，沒有語言級別的枚舉類型，枚舉的功能可以通過**繼承**枚舉類`Enumeration`實現。

## 繼承枚舉類
繼承枚舉類`Enumeration`可以在成員中使用無參方法`Value`給每個枚舉成員賦值。
默認的`Value`方法會按**變量名**生成**枚舉名**和並自動從`0`開始生成**枚舉ID**，
若需手動設定枚舉名稱和枚舉ID則可以使用`Value`方法的重載`Value(id: Int, name: Strig)`。

示例：

```scala
object Color extends Enumeration {

  // 自動賦值枚舉成員
  val Red, Green, Blue = Value
  /*
  * 相當於分別初始化：
  * val Red = Value
  * val Green = Value
  * val Blue = Value
  */

  // 手動使用 Value(id: Int, name: String) 方法手動進行id和name的設置
  // 使用重載有參版本的Value(id: Int, name: String)不能一次性給多個枚舉成員賦值，會編譯報錯(id衝突)
  val White = Value(100, "white")
  val Black = Value(200, "black")

}

object TestEnumeration extends App {

  Color.values foreach { color =>
    println(s"ID: ${color.id}, Str: $color")
  }

}
```

輸出結果：

```
ID: 0, Str: Red
ID: 1, Str: Green
ID: 2, Str: Blue
ID: 100, Str: white
ID: 200, Str: black
```

`Enumeration`類的默認構造方法帶有一個`Int`類型參數，用於指定枚舉ID的**起始大小**，如下所示：

```scala
object Color extends Enumeration(100) {
  val Red, Green, Blue, White, Black = Value //枚舉Id將從100開始
}

object Main extends App {

  Color.values foreach { color =>
    println(s"ID: ${color.id}, Str: $color")
  }

}
```

輸出結果：

```
ID: 100, Str: Red
ID: 101, Str: Green
ID: 102, Str: Blue
ID: 103, Str: White
ID: 104, Str: Black
```

## 訪問枚舉內容
枚舉單例支持以多種形式訪問：

- 通過枚舉成員訪問，類似於其它常見編程語言(`Enum.member`)
- 通過枚舉ID進行訪問，語法類似數組(`Enum(id)`)
- 通過枚舉名稱進行訪問，使用`withName`成員方法(`Enum withName "xxx"`)

枚舉內部的成員全部保存在一個`Set`容器中，可使用`values`成員方法訪問。

以前文中的`Color`單例對象爲例，使用多種方式訪問枚舉內容，如下所示：

```scala
object Color extends Enumeration {
  val Red, Green, Blue = Value
  val White = Value(100, "white")
  val Black = Value(200, "black")
}

object Main extends App {

  def showEnum(color: Color.Value) = println(s"ID: ${color.id}, Str: $color")

  // 通過枚舉ID訪問枚舉
  showEnum(Color(0))
  showEnum(Color(100))

  println()

  // 通過枚舉名稱訪問枚舉
  showEnum(Color withName "Green")
  showEnum(Color withName "black")

  println()

  // 遍歷枚舉內容
  Color.values foreach showEnum
}
```

輸出結果：

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

## 調用枚舉類型
繼承了枚舉類的單例對象名並**不能**直接用於表示枚舉類型。
對應的枚舉類型應使用對象內部定義的抽象類型`Value`來表示，即`單例對象名稱.Value`。

以前文中的`Color`單例對象爲例，對應的枚舉類型應使用`Color.Value`表示。
將枚舉做爲參數傳遞，如下所示：

```scala
object Color extends Enumeration {
  val Red, Green, Blue = Value
  val White = Value(100, "white")
  val Black = Value(200, "black")
}

object Main extends App {
  // Xxx.Value 纔是真正的枚舉類型
  def showEnum(color: Color.Value) = println(s"ID: ${color.id}, Str: $color")
  showEnum(Color.blue)
  showEnum(Color.white)
}
```

輸出結果：

```
ID: 2, Str: Blue
ID: 100, Str: white
```

## 限定枚舉類型
Scala通過使用單例繼承`Enumeration`類來提供枚舉功能，**枚舉值**的類型實際爲`單例.Value`。
由於Scala中每個實例的內部類的類型均**不相同**，需要使用**類型投影**來表示通用的枚舉類型。
**枚舉值**的類型投影爲`Enumeration#Value`。
在泛型方法中，可以使用泛型約束`T <: Enumeration#Value`來限定泛型參數爲枚舉類型。
示例：

```scala
scala> def testEnum[T <: Enumeration#Value](enum: T) = println(enum) //打印枚舉參數名稱
testEnum: [T <: Enumeration#Value](enum: T)Unit

scala> object Enum extends Enumeration { val enum0, enum1  = Value }
defined object Enum

scala> testEnum(Enum.enum0) //傳入枚舉類型參數
enum0

scala> testEnum(Enum.enum1)
enum1

scala> testEnum(123) //使用其它類型不滿足泛型約束，報錯
<console>:13: error: inferred type arguments [Int] do not conform to method testEnum's type parameter bounds [T <: Enumeration#Value]
       testEnum(123)
       ^
<console>:13: error: type mismatch;
 found   : Int(123)
 required: T
       testEnum(123)
                ^
```

通過構建特定的枚舉基類，可以實現限定**指定類別**的枚舉。
示例：

```scala
scala> class MyEnumeration extends Enumeration //自定義枚舉基類
defined class MyEnumeration

scala> def testMyEnum[T <: MyEnumeration#Value](enum: T) = println(enum) //限定枚舉從自定義基類MyEnumeration中繼承
testMyEnum: [T <: MyEnumeration#Value](enum: T)Unit

scala> object Enum extends Enumeration { val enum0, enum1  = Value } //普通枚舉
defined object Enum

scala> object MyEnum extends MyEnumeration { val enum0, enum1  = Value } //從自定義基類MyEnumeration繼承的枚舉
defined object MyEnum

scala> testMyEnum(MyEnum.enum0) //參數爲從自定義枚舉基類MyEnumeration繼承的枚舉單例的枚舉值，正常
enum0

scala> testMyEnum(MyEnum.enum1)
enum1

scala> testMyEnum(Enum.enum1) //參數爲普通枚舉單例的枚舉值，錯誤
<console>:14: error: inferred type arguments [Enum.Value] do not conform to method testMyEnum's type parameter bounds [T <: MyEnumeration#Value]
       testMyEnum(Enum.enum1)
       ^
<console>:14: error: type mismatch;
 found   : Enum.Value
 required: T
       testMyEnum(Enum.enum1)
                       ^
```



# Package (包)
Scala中的包用法基本與Java類似：

- 使用`package`關鍵字定義包路徑。
- 使用`import`關鍵字導入包路徑。

## 包與路徑
在Scala中，包路徑是**邏輯概念**，源碼文件**不必**按照包路徑存放到對應的目錄下。

Scala中使用`_`符號表示導入該路徑下的所有包和成員：

```scala
import java.awt._ //等價於java中的 import java.awt.*
```

導入路徑規則與Java中的類似，處於同一級包路徑下的類可以直接使用不必導入。

- 導入策略

	在導入包時，Scala默認採用**相對路徑**。
	在外層路徑的包使用內層路徑的包時，可省略共同的路徑部分直接以當前路徑爲起點訪問內層路徑包。

	示例：

	```scala
	// file1
	package com.dainslef

	class Test

	// file2
	package com

	// 導入路徑時以當前包爲起點，不必從最外層路徑開始導入
	import dainslef.Test

	object Main extends App {
	  println(classOf[Test].getName)
	}
	```

	而在Java中，無論包的層次關係如何，都需要通過絕對路徑進行導入。

	上例對應Java版本如下所示：

	```java
	// file1
	package com.dainslef;

	class Test {
	};

	// file2
	package com;

	// 導入路徑時從時需要從最外層路徑開始導入，不能寫成 import dainslef.Test
	import com.dainslef.Test;

	public class Main {

		public static void main(String[] args) {
			System.out.println(Test.class.getName());
		}

	}
	```

- 默認包與絕對路徑導入

	在Java和Scala中，不使用`package`關鍵字打包的代碼即位於**默認包**下，沒有對應的包名。
	在Scala中使用`_root_`指代默認包。

	Scala中默認的`import`操作是基於相對路徑的，但Scala同樣支持以**絕對路徑**進行`import`操作：

	- 以`_root_`爲導入起始路徑，即代表以絕對路徑的形式導入內容。
	- 使用絕對路徑訪問內容能避免一些命名衝突。

	上例中的代碼中的`Test`類以絕對路徑導入，導入語句可寫成：

	```scala
	import _root_.com.dainslef.Test
	```

- 默認包的限制

	默認包沒有名稱，其內容只能被同在默認包下的其它內容訪問。
	內層包無法訪問外部默認包的內容，即使使用`_root_`訪問絕對路徑依舊無法訪問。

	示例：

	```scala
	// file1
	// 定義單例在默認包中
	object Test {
	  val test = "Test string..."
	}

	// file2
	package com

	object Main extends App {
	  // 在內層包中訪問外部默認包的內容
	  println(Test.test) //錯誤，提示 "not found: value Test"
	  println(_root_.Test.test) //錯誤，提示 "object Test is not a member of package <root>"
	}
	```

## 擴展用法
Scala包機制在Java的基礎上擴充了更多的功能。

在一個語句中導入包內的**多個**指定的類：

```scala
import java.awt.{Color, Font}
```
在導入一個包的同時可以將包內的類進行重命名：

```scala
import java.awt.{Color => JavaColor}
```

如果不希望某個類被導入，則可以用以下方式隱藏某個類：

```scala
import java.awt.{Color => _}
```

Scala中的`import`帶有類似`Java 1.6`中的`static import`特性：

```scala
import java.lang.Math.abs //導入Math類中的靜態方法abs
```

在Scala中，包引入了名稱相同的類不會發生衝突，而是後引入的類**覆蓋**之前引入的類。
在Scala中，`import`語句可以出現在**任意位置**，不必總是放在文件的頂部，`import`語句的作用域直到該語句塊結束。

### 默認導入
默認情況下，Scala會導入以下幾個包路徑：

```scala
import java.lang._
import scala._
import Predef._
```

有些Scala包中的類名與Java包中的類名相同，但由於Scala包的引入語句在後，因此，例如`Scala.StringBuiler`類會覆蓋`Java.lang.StringBuilder`。

### 包對象
在Scala中，每個包可以帶有一個與包名相同的**包對象**，包內的所有類都可以直接訪問該包對象的公有成員。
示例：

```scala
package object Package {
  var num0 = 0
  protected var num1 = 1
  private var num2 = 2
}

package Package {
  object Test extends App {
    println(num0) //正確，可以直接訪問包對象的公有成員，不用使用前綴
    println(num1) //錯誤，不能訪問包對象的保護成員
    println(num2) //錯誤，不能訪問包對象的私有成員
  }
}
```

通常情況下，包對象的定義應放置在包路徑下的`package.scala`文件中。



# 基礎數據結構
Scala常用的基礎結構包括**數組**和**元組**。

## 定長數組
在Scala中定長數組使用`Array[T]`進行表示，定長數組與Java中概念類似。

構建一個固定長度的數組如下所示：

```scala
scala> val array = new Array[Int](10) //構建一個長度爲10的Int型數組
array: Array[Int] = Array(0, 0, 0, 0, 0, 0, 0, 0, 0, 0)

scala> val a = Array(100, 200) //使用伴生對象的apply()方法創建數組
a: Array[Int] = Array(100, 200)

scala> array(5) //獲取數組中指定位置的值(使用小括號中加偏移量)
res1: Int = 0

scala> array(5) = 10 //給指定位置的元素賦值

scala> array //查看賦值結果
res2: Array[Int] = Array(0, 0, 0, 0, 0, 10, 0, 0, 0, 0)

scala> array(100) //數組訪問越界會拋出異常
java.lang.ArrayIndexOutOfBoundsException: 100
  ... 33 elided
```

## Tuple (元組)
元組是最簡單的容器，無需額外的類型名稱，直接使用`(value1, value2, value3, ...)`就可以構建出一個元祖。
示例：

```scala
scala> val tuple = (1, 2, 3)
tuple: (Int, Int, Int) = (1,2,3)
```

元組中允許包含**重複**的值，也允許不同類型的值，但元組一經創建，內容便不可改變。

元組**不支持**直接使用`for`語句進行遍歷。
`Tuple`類型混入了`scala.Product`特質，可以使用無參方法`Product.productIterator`獲取可迭代的對象用於遍歷。
示例：

```scala
for (t <- tuple.productIterator) println(t) //命令式遍歷
tuple.productIterator foreach println //函數式遍歷
```

由於元組成員可具有**不同**的類型，因而使用`Product.productIterator`遍歷時，迭代對象爲`Any`類型。
對與成員類型相同的元組，可以在遍歷時使用模式匹配：

```scala
scala> val tuple = (1, 2, 3)
tuple: (Int, Int, Int) = (1,2,3)

scala> tuple.productIterator foreach { i => println(i - 1) } //直接遍歷迭代對象爲 Any 類型
<console>:13: error: value - is not a member of Any
       tuple.productIterator foreach { i => println(i - 1) }
                                                      ^

scala> tuple.productIterator foreach { case i: Int => println(i - 1) } //使用模式匹配得到真實類型
0
1
2
```

元組可以通過`元組對象._索引號`的形式訪問。元組下標從`1`開始而非`0`，如下所示：

```scala
scala> println(tuple._1 + " " + tuple._2 + " " + tuple._3)
1 2 3
```

元組可以用來一次性初始化多個變量：

```scala
scala> val (a, b, c) = tuple //等價於 val (a, b, c) = (1, 2, 3)
a: Int = 1
b: Int = 2
c: Int = 3
scala> println(s"$a $b $c")
1 2 3
```

元組可以包含**不同**的類型：

```scala
scala> val (num, str) = (123, "456")
num: Int = 123
str: String = 456
```

元組用作函數返回類型時，即可讓一個函數擁有多個返回值，如下所示：

```scala
object TestTuple extends App {
  def getNum(num1: Int, num2: Int, num3: Int) = (num1, num2, num3)
  val (num1, num2, num3) = getNum(1, 2, 3)
  println(s"$num1 $num2 $num3")
}
```

輸出結果：

```
1 2 3
```

當一個方法的參數表中僅包含**單個元組**時，調用方法時可省略元組外部括號，在**柯里化**情形下同樣有效，如下所示：

```scala
def add(n1: (Int, Int, Int))(n2: (Int, Int)) = n1._1 + n1._2 + n1._3 + n2._1 + n2._2
add(1, 2, 3)(4, 5) //參數直接傳入，無需外部括號
```



# 容器
Scala的容器按數據結構分爲`序列(Seq)`、`集合(Set)`和`映射(Map)`三大類。

- `序列(Seq)`

	有序容器，按照元素添加的順序排列。
	`Seq`的子類`IndexedSeq`允許類似數組的方式按照下標進行訪問。

- `集合(Set)`

	數學意義上的集合，不包含重複元素。
	`Set`的子類`SortedSet`中元素以某種順序排序。

- `映射(Map)`

	`鍵 - 值`對偶的集合。
	`Map`的子類`SortedMap`中鍵值以某種順序排序。

基本的集合類型繼承樹如下所示：

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

## 容器可變性
容器按照是否**可變**分爲：

- **不可變容器**`scala.collection.immmutable._`
- **可變容器**`scala.collection.mutable._`。

Scala爲函數式語言，默認的容器類型使用**不可變**實現。

## List (列表)
在Scala中，`List[T]`類型的完整包路徑爲`scala.collection.immutable.List`，繼承於`Seq`。
List爲**不可變對象**，可以使用`for`操作符進行遍歷。

構建一個列表：

```scala
scala> val list0 = List(1, 2, 3)
list0: List[Int] = List(1, 2, 3)
```

除了直接使用`List`單例提供的`apply()`方法構建列表對象之外，還可以使用`::`操作符來將多個值構成列表。
`::`操作符爲**右結合性**運算符。
使用`::`操作符構成列表時，列表的最後一個值必須爲`Nil`，如下所示：

```scala
scala> val list1 = 0 :: 1 :: 2 :: 3 :: Nil
list1: List[Int] = List(0, 1, 2, 3)
```

列表同樣允許不同類型的值，也允許重複的值，如下所示：

```scala
scala> val list2 = 1 :: 1 :: "str" :: 2.0 :: Nil
list2: List[Any] = List(1, 1, str, 2.0)
```

若列表中存儲的若是相同的類型，則編譯器會將`List[T]`推導爲具體的類型。
若列表中成員類型各不相同，則編譯器會使用所有類型的基類`Any`作爲泛型類型即`List[Any]`。

列表支持從已有的列表進行創建：

```scala
scala> val list0 = 1 :: 2 :: 3 :: Nil
list0: List[Int] = List(1, 2, 3)
scala> val list1 = 0 :: list0 //向列表頭部增加元素
list1: List[Int] = List(0, 1, 2, 3)
scala> val list2 = list0 :: 4 //列表不能從尾部添加元素(List以Nil結尾)
<console>:11: error: value :: is not a member of Int
  val list2 = list0 :: 4
                    ^
```

使用`:::`運算符可以疊加兩個列表：

```scala
scala> val list2 = list0 ::: list1
list2: List[Int] = List(1, 2, 3, 0, 1, 2, 3)
```

也可以使用`++`運算符連接兩個列表：

```
scala> val list3 = list0 ++ list1
list3: List[Int] = List(1, 2, 3, 0, 1, 2, 3)
```

`:::`與`++`對於列表而言，作用完全相同。
`:::`是`List`類型特有的運算符，`++`繼承於特質`TraversableLike`，也可用於一些其它的集合類型。

列表同樣支持通過索引進行訪問，語法與`Array[T]`類型類似：

```scala
scala> list0(0)
res0: Int = 1
```

## ArrayBuffer (變長數組)
在Scala中，變長數組使用`ArrayBuffer[T]`，完整路徑`scala.collection.mutable.ArrayBuffer`，繼承於`Seq`。
Scala中的`ArrayBuffer`相當於Java中的`ArrayList`，可存儲任意數量的元素。
創建`ArrayBuffer`：

```scala
scala> val arrayBuffer = new ArrayBuffer[Int]
arrayBuffer: scala.collection.mutable.ArrayBuffer[Int] = ArrayBuffer()
val a = ArrayBuffer(100, 200)  //同樣可以使用伴生對象的apply()方法創建ArrayBuffer
a: scala.collection.mutable.ArrayBuffer[Int] = ArrayBuffer(100, 200)
```

`ArrayBuffer`定義了方法`+=`和`-=`用於**增加**和**刪除**元素：

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

需要注意的是，`+=`、`-=`只是**方法名**並不是**運算符**。
`ArrayBuffer`沒有提供`+`、`-`方法，以下的寫法會**報錯**：

```scala
arrayBuffer = arrayBuffer + 10
<console>:12: error: type mismatch;
found : Int(10)
required: String
  arrayBuffer = arrayBuffer + 10
                            ^
```

與Java中的`ArrayList`類似，`ArrayBuffer`也允許在**任意位置**進行元素插入：

```scala
scala> arrayBuffer.insert(1, -100) //在索引1的位置插入數值-100
scala> arrayBuffer
res17: scala.collection.mutable.ArrayBuffer[Int] = ArrayBuffer(10, -100, 100)
```

插入多個元素：

```scala
scala> arrayBuffer.insert(1, 7, 8, 9) //在索引1的位置插入數值7，8，9
scala> arrayBuffer
res19: scala.collection.mutable.ArrayBuffer[Int] = ArrayBuffer(10, 7, 8, 9, -100, 100)
```

刪除操作類似，移除操作可以指定首尾進行**批量移除**：

```scala
scala> arrayBuffer.remove(1, 4)
scala> arrayBuffer
res21: scala.collection.mutable.ArrayBuffer[Int] = ArrayBuffer(10, 100)  //刪除了索引1到4位之間的元素
```

需要注意的是，`ArrayBuffer`是**線性結構**，只有在尾部進行插入刪除操作纔是高效的，在其它位置進行的元素操作都會造成大量的元素移動。
`ArrayBuffer`的不可變版本對應爲`scala.collection.immutable.Vector`。

## Set (集合)
`Set[T]`類型爲數學意義上的集合，集合內不允許重複元素。
`Set`完整包路徑爲`scala.collection.immutable.Set`。
集合同樣允許任意類型的元素，但集合中不能包含重複的元素。

在使用`Set`類的`apply()`方法構建集合時，重複的元素會被忽略，如下所示：

```scala
scala> val set = Set(1, 1, 's', "str")
set: scala.collection.immutable.Set[Any] = Set(1, s, str) //重複的元素"1"被忽略了
```

`Set`可以使用`+`、`-`操作符來增加或是減少元素並返回新的集合。
使用`+`、`-`操作符會返回新的集合，但原集合內的值不會發生改變，如下所示：

```scala
scala> val set1 = set + 3
set0: scala.collection.immutable.Set[Any] = Set(1, s, str, 3) //原集合添加元素輸出新的集合

scala> set
res1: scala.collection.immutable.Set[Any] = Set(1, s, str) //原集合本身沒有變化

scala> val set2 = set - 's'
set2: scala.collection.immutable.Set[Any] = Set(1, str) //從集合中移除一個元素

scala> set
res3: scala.collection.immutable.Set[Any] = Set(1, s, str)

scala> set + (1, 2, 3) //可直接添加元組
res4: scala.collection.immutable.Set[Any] = Set(s, 1, 2, str, 3)

scala> set - (1, 2, 3) //通過元組刪除數據
res5: scala.collection.immutable.Set[Any] = Set(s, str)
```

當引用爲變量時，`Set`可以使用`+=`、`-=`來增加或減少內部的元素：

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

`Set`的`+=`、`-=`操作並非定義的方法，只是類似常規語言的操作符簡寫，如：

```scala
var set = Set(1, 2, 3)
set += 4
```

實際等價於：

```scala
var set = Set(1, 2, 3)
set = set + 4
```

對不可變類型的變量使用`+=`、`-=`操作，實際上改變了變量指向的實例。
當不可變類型實例爲**常量**時，則不能使用`+=`、`-=`操作，因爲常量的實例指向不可變，如下所示：

```scala
scala> val set = Set(1, 2, 3)
set: scala.collection.immutable.Set[Int] = Set(1, 2, 3)

scala> set += 4
<console>:13: error: value += is not a member of scala.collection.immutable.Set[Int]
       set += 4
           ^
```

實際相當於：

```scala
scala> val set = Set(1, 2, 3)
set: scala.collection.immutable.Set[Int] = Set(1, 2, 3)

scala> set = set + 4
<console>:12: error: reassignment to val
       set = set + 4
           ^
```

`Set`支持數學意義上的交集、並集、差集等操作：

- 交集：

	```scala
	scala> Set(1, 2, 3) & Set(2, 5)
	res0: scala.collection.immutable.Set[Int] = Set(2)

	scala> Set(1, 2, 3) intersect Set(2, 5)
	res1: scala.collection.immutable.Set[Int] = Set(2)
	```

- 並集：

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

`scala.collection.immutable.Set`以哈希集實現，元素依據**HashCode**進行組織。

`Set`的相關類型有：

- `scala.collection.mutable.LinkedHashSet` 鏈式哈希集，依照插入的順序排列
- `scala.collection.immutable.SortedSet` 紅黑樹實現的排序集

## Map (映射)
`Map[A, B]`類型的完整包路徑爲`scala.collection.immutable.Map`。
映射中的每一個元素都是一組`對偶(Tuple2)`，分別爲key和value，key不可重複。
通過`->`操作符可以將兩個值組成一組對偶，如下所示：

```scala
scala> var map = Map(1 -> "1", 2 -> "2", 3 -> "3")
map: scala.collection.immutable.Map[Int,String] = Map(1 -> 1, 2 -> 2, 3 -> 3)
scala> for ((key, value) <- map) println(s"key: $key value: $value")
key: 1 value: 1
key: 2 value: 2
key: 3 value: 3 //使用for循環遍歷map
scala> for (value <- map.values) println(s"value: $value")
value: 1
value: 2
value: 3 //僅遍歷map的value
scala> for (key <- map.keys) println(s"value: $key")
value: 1
value: 2
value: 3 //僅遍歷map的key
```

使用`updated()`方法可以更新指定key對應的value之後輸出，通過`+`方法添加對偶後輸出，也可以通過`-`移除指定key的對偶後輸出。
但這些操作不會改變原本映射的內容：

```scala
scala> map.updated(1, "0")
res20: scala.collection.immutable.Map[Int,String] = Map(1 -> 0, 2 -> 2, 3 -> 3)
scala> map + (4 -> "4")
res21: scala.collection.immutable.Map[Int,String] = Map(1 -> 1, 2 -> 2, 3 -> 3, 4 -> 4)
scala> map - 1
res22: scala.collection.immutable.Map[Int,String] = Map(2 -> 2, 3 -> 3)
scala> map  //更改的結果作爲返回值輸出，原本的Map值沒有任何改變
res23: scala.collection.immutable.Map[Int,String] = Map(1 -> 1, 2 -> 2, 3 -> 3)
```

與`Set`類似，當實例字段爲可變量時，`Map`也支持`+=`、`-=`操作。

除了不可變的`scala.collection.immutable.Map`外，還有可變的`scala.collection.mutable.Map`類型。
Scala還提供了多種不同結構的`Map`實現，如`HashMap`、`ListMap`、`LinkedHashMap`等。

## GenTraversableLike
`GenTraversableLike`特質定義了訪問容器內頭尾元素的方法：

```scala
trait GenTraversableLike[+A, +Repr] extends Any with GenTraversableOnce[A] with Parallelizable[A, parallel.ParIterable[A]] {
  ...
  def head: A //獲取第一個元素，元素不存在時拋出NoSuchElementException
  def headOption: Option[A] //獲取第一個元素的Option，元素不存在時爲None值
  def tail: Repr //獲取除了第一個元素之外的其餘所有元素
  def last: A //獲取最後一個元素，元素不存在時拋出異常
  def lastOption: Option[A] //獲取最後一個元素的Option
  ...
}
```

多數容器都間接混入了`GenTraversableLike`特質，如`List`、`Seq`、`Vector`、`Map`等。
對於混入了`GenTraversableLike`的類型且支持索引訪問的類型，使用`xxx.head`比`xxx(0)`更符合Scala風格。

## 集合有序性
Scala默認`Set/Map`無論`mutable/immutable`均爲**無序**。
示例：

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

輸出結果：(`Scala 2.12.2 && macOS 10.12.4`)

```
Immutable Set: Set(5, 1, 2, 3, 4)
Immutable Map: Map(5 -> 5, 1 -> 1, 2 -> 2, 3 -> 3, 4 -> 4)
Mutable Set: Set(1, 5, 2, 3, 4)
Mutable Map: Map(2 -> 2, 5 -> 5, 4 -> 4, 1 -> 1, 3 -> 3)
```

`Set/Map`存在特定規則的有序版本`SortedSet/SortedMap`。
`SortedSet/SortedMap`在構造時需要提供`scala.math.Ordering[T]`特質用於決定內部成員的排序規則。
Scala已實現了常見類型(`Int`、`String`等)的`Ordering`特質，使用常見類型時不必顯式傳入。

`immutable`容器存在有序類型`ListSet/ListMap`。
`mutable`容器存在有序類型`LinkedHashSet/LinkedHashMap`，按照元素添加的順序排列。
示例：

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

輸出結果：(`Scala 2.12.2 && macOS 10.12.4`)

```
Immutable ListSet: ListSet(1, 2, 3, 4, 5, 6, 7, 8, 9, 10)
Immutable ListMap: ListMap(1 -> 1, 2 -> 2, 3 -> 3, 4 -> 4, 5 -> 5)
Mutable LinkedHashSet: Set(1, 2, 3, 4, 5, 6, 7, 8, 9, 10)
Mutable LinkedHashMap: Map(1 -> 1, 2 -> 2, 3 -> 3, 4 -> 4, 5 -> 5)
```

`immutable`容器不存在`LinkedHashSet/LinkedHashMap`類型。
`mutable`容器不存在`ListSet`類型，存在`ListMap`類型，但無序。

有序容器使用`toSet/toMap`等方法向無序容器轉換，內部成員會重新變爲**無序**。



# Higher Order Function (高階函數)
**高階函數**是**函數式編程**中的概念，在數學中，也叫做**算子**(運算符)或**泛函**。
**接受一個或多個函數作爲輸入**或者**輸出一個函數**的函數被稱爲高階函數。

在Scala中，容器類提供了高階函數作爲容器數據操作的接口。
常見的高階函數有`map`、`reduce`、`flatMap`、`filter`、`find`、`fold`、`foreach`等。

## for/yeild 語句
Scala中同樣提供了`yield`關鍵字，用於構建集合。
Scala中的`yield`語句不是惰性生成，與傳統語言的**生成器**概念不同。
示例：

```scala
scala> for (i <- 1 to 5) yield i
res20: scala.collection.immutable.IndexedSeq[Int] = Vector(1, 2, 3, 4, 5)

// 使用for語句內置的守衛語法限制輸出
scala> for (i <- 1 to 5 if i > 2) yield i
res21: scala.collection.immutable.IndexedSeq[Int] = Vector(3, 4, 5)

// 生成器的生成結果與被遍歷的容器類型相關
scala> for (i <- 1 :: 2 :: 3 :: 4 :: 5 :: Nil if i > 2) yield i
res24: List[Int] = List(3, 4, 5)

// 生成的結果不是目標容器則可以進行轉換
scala> (for (i <- List(1, 2, 3, 4, 5) if i > 2) yield i) toSet
res27: scala.collection.immutable.Set[Int] = Set(3, 4, 5)
```

Scala中的`for/yield`語句實際是高階函數的語法糖，`yeild`語句可以還原爲高階函數的形式：

```scala
// 從1到5的數中找出偶數，並將數值翻倍

// 使用命令式編程風格，使用守衛和生成器
scala> for (i <- 1 to 5 if i % 2 == 0) yield i * 2
res13: scala.collection.immutable.IndexedSeq[Int] = Vector(4, 8)

// 使用函數式編程風格，使用高階函數
scala> 1 to 5 filter { _ % 2 == 0 } map { _ * 2 }
res15: scala.collection.immutable.IndexedSeq[Int] = Vector(4, 8)
```



# Exception (異常)
Scala沿用了Java的異常機制，但相關語法略有不同。

- 拋出異常

	Scala同樣使用`throw`語句拋出異常，與Java語法類似：

	```scala
	throw new XxxException
	```

	Java中要求將方法內可能拋出的異常明確地在方法簽名中列出，但在Scala中不需要。

	對於需要被Java調用的Scala方法，可以使用`@throw`註解來標明方法中可能拋出的異常，使方法在Java端生成正確的簽名：

	```scala
	@throw(classOf[XxxException])
	def testSException {
		throw new XxxExeption
	}
	```

	對應的Java代碼：

	```java
	void testException() throw XxxException {
		throw new XxxExeption
	}
	```

- 捕獲異常

	Scala中同樣使用`try ... catch ... finally ...`語句進行異常捕獲，但語法略有不同：

	1. 在Scala中，`catch`子句沒有參數，直接在語句內部使用**模式匹配**進行異常捕獲，如下所示：

		```scala
		try {
			...
		} catch {
			case ex: Exception1 => ...
			case ex: Exception2 => ...
			...
		}
		```

		對應Java代碼：

		```java
		try {
			...
		} catch (Exception1 ex) {
			...
		} catch (Exception2 ex) {
			...
		}
		```

	1. 單條`try`語句可省略花括號，`try`語句可不帶有`case`、`finally`單獨存在，如下所示：

		```scala
		scala> try 2333
		<console>:12: warning: A try without a catch or finally is equivalent to putting its body in a block; no exceptions are handled.
		       try 2333
		       ^
		res9: Int = 2333 //有警告，但正常執行
		```

	1. Scala中的`try ... catch ... finally ...`語句具有返回值。

		使用返回值時，需要保證`try`語句以及`catch`子句中的每一個`case`擁有相同的返回值類型。
		`finally`子句不做爲返回值，也不影響返回值類型的推導。
		示例：

		```scala
		scala> try 2333
		res9: Int = 2333 //try語句返回值

		scala> try 2333 catch { case _ => 666 }
		res10: Int = 2333 //try與case返回值類型相同時，正確推導出整條語句的返回值類型

		scala> try 2333 catch { case _ => "666" }
		res11: Any = 2333 //try與case返回值類型不同時，結果類型推導爲Any

		scala> try 2333 catch { case _ => 666 } finally "666"
		res12: Int = 2333 //finally語句不影響try表達式結果類型
		```

## scala.util.Try[T]
從`Scala 2.10`開始，標準庫中提供了`scala.util.Try[T]`類型對異常處理操作的抽象。
`Try`類型的伴生對象中提供了接收傳名參數的`apply()`方法，用於構建`Try`類型實例：

```scala
object Try {
  def apply[T](r: => T): Try[T] = ...
}
```

使用`Try`與普通的異常處理類似，將可能觸發異常的語句包含在`Try`代碼塊中：

```scala
Try {
  ... //可能拋出異常的代碼
}
```

泛型參數`T`即爲代碼塊的返回值類型。

與`Option`類型的設計類似，`Try`類型擁有子類：

- `scala.util.Success[T]` 表示代碼正常執行完畢，包含正常執行的結果
- `scala.util.Failure[T]` 表示代碼執行中觸發了異常，包含異常信息

`Try`類型也提供了與`Option`類型相似的高階函數，常用方法定義如下：

```scala
sealed abstract class Try[+T] extends Product with Serializable {
  ...
  def get: T //獲取語句塊的執行結果
  def getOrElse[U >: T](default: => U): U //語句執行失敗時使用給定的默認值做爲返回結果
  def foreach[U](f: T => U): Unit //語句執行成功時執行函數f，否則不進行操作
  def map[U](f: T => U): Try[U] //以上一個操作的執行結果爲入參執行下一個操作，同樣返回Try類型
  def fold[U](fa: Throwable => U, fb: T => U): U
  def toOption: Option[T] //將語句塊的執行結果轉換爲Option形式
  ...
}
```

使用`get`方法獲取`Try`語句塊的執行結果：

```scala
scala> Try { 123 } get
res5: Int = 123
```

若`Try`語句塊觸發了異常，則使用`get`方法獲取執行結果同樣拋出異常：

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

可以使用`getOrElse()`方法在觸發異常時提供默認值：

```scala
scala> Try { "Dainslef".toInt } getOrElse 233
res3: Int = 233
```

使用`foreach()`高階函數在`Try`語句塊執行成功時執行操作：

```scala
scala> Try { 123 } foreach println
123
```

在`Try`語句塊執行失敗時`foreach()`高階函數不執行：

```scala
scala> Try { "Dainslef".toInt } foreach println //無輸出

```

`fold()`高階函數用法與`Option`類型類似，在`Try`語句塊成功是執行成功表達式並輸出返回結果，
在`Try`語句塊失敗時執行失敗表達式並返回結果，兩類表達式返回結果類型需要相同。
示例：

```scala
scala> Try { "Dainslef".toInt } fold (_ => "Failed", _ => "Success")
res10: String = Failed //執行失敗

scala> Try { "Dainslef" } fold (_ => "Failed", _ => "Success")
res11: String = Success //執行成功
```

`toOption`方法用於將`Try[T]`語句塊的執行結果轉換爲`Option[T]`類型，語句塊執行成功得到`Some[T]`，執行失敗得到`None`。
示例：

```scala
scala> Try { "Dainslef".toInt } toOption
res1: Option[Int] = None //執行失敗，得到 None

scala> Try { 233.3.toInt } toOption
res2: Option[Int] = Some(233) //執行成功，得到 Some(233)
```



# XML 解析
Scala標準庫中內置了XML支持，XML相關類在包`scala.xml`中。

## 節點類型
`Node`是最基礎的XML節點類型(抽象類)。
`NodeSeq`用於記錄節點的序列，繼承自`Seq[Node]`。

相關類型繼承關係圖如下所示：

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

`Node`類型定義了一系列用於獲取節點信息的方法：

- `prefix`成員方法，用於獲取**當前節點**的標籤**前綴**。
- `child`成員方法(抽象方法)，用於獲取**子節點**的**序列**。
- `attributes`成員方法，用於獲取**當前節點**的**屬性**。
- `label`成員方法(抽象方法)，用於獲取**當前節點**的**標籤名稱**。
- `text`成員方法，用於獲取**當前節點**的**文本內容**。

示例：

```scala
def prefix: String = null
def child: Seq[Node]
def attributes: MetaData = Null
def label: String
override def text: String = super.text
```

`Node`類型的伴生對象中定義了**提取器**，可以用於提取節點中的**標籤名稱**、**屬性**、**子節點**等內容：

```scala
def unapplySeq(n: Node) = Some((n.label, n.attributes, n.child))
```

`Elem`類型繼承於`Node`類型，實現了`Node`類型中的抽象內容。

## 讀寫 XML 文件
讀寫XML文件可以使用`XMLLoader`特質以及繼承於`XMLLoader[Elem]`的單例對象`XML`。

- `XMLLoader`的實例方法`loadFile()`可以從指定路徑加載XML文件進行解析，方法返回由輸入XML文件生成的`Elem`節點對象。
- `XML`對象的方法`save()`和`write()`可用於將節點(`Node`類型)寫入到文件中。
- `save()`方法接收文件路徑(`String`類型)作爲參數，大部分參數帶有默認值。
- `write()`接收`java.io.Writer`類型作爲參數，參數沒有默認值。

## 查找節點
`NodeSeq`類提供了`\()`、`\\()`等方法用於節點的查找，繼承於`NodeSeq`類的`Node`、`Elem`等類型都可以使用這些方法進行節點查找。

`\()`以及`\\()`方法簽名類似，接收節點名稱作爲參數(`String`類型)，返回節點序列(`NodeSeq`類型)。

示例：

```scala
// 返回當前節點下一級子節點中指定名稱節點的序列
def \(that: String): NodeSeq
// 返回當前節點所有子節點中指定名稱節點的序列
def \\(that: String): NodeSeq
```

- 使用`loadFile()`方法加載XML文件後，返回的`Elem`類型的當前節點爲**根節點**。
- 節點查找支持使用**模式匹配**的方式。
- 使用模式匹配方式查找節點時，匹配表達式中的節點標籤不能帶有屬性(不支持此語法)。

## 節點屬性
節點屬性內容可以直接從節點中獲取，也可以通過查找獲取屬性內容。

使用`\()`、`\\()`方法同樣可以進行屬性查找。
在參數字符串前加`@`字符表示搜索的內容爲**屬性**，如`\("@num")`表示查找名爲`num`的屬性內容。
使用`\()`方法查找屬性時，查找的的範圍**不是**子節點的屬性，而是**當前**節點的屬性。

`NodeSeq`類型提供了`\@()`方法在**當前**子節點中進行屬性查找，直接使用屬性名作爲參數，無需再添加`@`字符。
示例：

```scala
// 參數爲屬性名稱
def \@(attributeName: String): String
```

`Node`類型提供了`attribute()`以及`attributes`方法從節點中獲取屬性。
示例：

```scala
// 獲取帶有指定屬性的節點
final def attribute(key: String): Option[Seq[Node]]
// 獲取所有屬性
def attributes: MetaData
```

`attributes`方法返回的類型爲`MetaData`。
`MetaData`類型支持遍歷操作，定義了`key`、`value`方法用於獲取屬性的鍵值。
示例：

```scala
// 獲取指定屬性的值
def apply(key: String): Seq[Node]
// 獲取當前屬性名稱
def key: String
// 獲取當前屬性名稱對應的屬性值
def value: Seq[Node]
```

## 遍歷節點
`Elem`類型的成員字段`child`保存了子節點的序列(`Seq[Node]`類型)，可以通過`for`循環語句或高階函數進行遍歷。

有如下測試XML文件：

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

代碼如下所示：

```scala
object Xml extends App {

  val xmlFile = XML.loadFile(getClass.getResource("Example.xml").getPath)

  val showChild: Node => Unit = _.child foreach {

    // 使用標籤匹配，可以將表達式嵌在匹配語句中
    case <One>{text}</One> => println(s"case <One>{text}</One>: $text")

    // 標籤匹配支持多級嵌套標籤，不支持在標籤中直接添加屬性
    case <Node><Two>{text}</Two></Node> =>
      println(s"case <Node><Two>{text}</Two></Node>: $text")

    // 匹配多級標籤需要節點內部不換行
    case <Node><Three>{text}</Three></Node> =>
      println(s"case <Node><Three>{text}</Three></Node>: $text")

    // 使用 @ 操作符給匹配的節點標記變量名稱(n 爲 Node 類型)
    case n@<Three>{_}</Three> =>
      println(s"case n@<Three>{_}</Three>, n text: ${n.text}, n type: ${n.getClass}")

    // 遍歷屬性
    case n@<Four>{_}</Four> if n \@ "arg_one" == "arg_4_1" =>
      println(s"case n@<Four>{_}</Four>, n text: ${n.text}, n type: ${n.getClass}, n.attributes: ")
      n.attributes foreach { attr =>
        println(s"attribute name: ${attr.key} attribute value: ${attr.value.text}")
      }

    // 使用 @ 操作符給節點內容標記變量名稱(n 爲 Text 類型)
    case <Four>{n@_}</Four> =>
      println(s"case <Four>{n@_}</Four>, n text: ${n.text}, n type: ${n.getClass}")

    /*
      匹配其它類型節點，注意不能寫成：
      case _ if node.child.length > 0 => ... 或 case _ if node.child.nonEmpty => ...
      (空指針不能調用方法)
    */
    case node if node.child != null => showChild(node)

  }

  showChild(xmlFile)
}
```

輸出結果：

```
case <One>{text}</One>: node1
case <Node><Two>{text}</Two></Node>: node2
case n@<Three>{_}</Three>, n text: node3, n type: class scala.xml.Elem
case <Four>{n@_}</Four>, n text: node4_1, n type: class scala.xml.Text
case n@<Four>{_}</Four>, n text: node4_2, n type: class scala.xml.Elem, n.attributes:
attribute name: arg_two attribute value: arg_4_2
attribute name: arg_one attribute value: arg_4_1
```

## 創建 XML
可以直接將代碼嵌入`XML`語句中：

```scala
scala> val str = "Test"
str: String = Test
scala> val node0 = <li>{ str }</li> //xml節點內容可以插入變量,使用花括號區分表達式與xml本身內容
node0: scala.xml.Elem = <li>Test</li>
scala> val node1 = <li name={ str }>test</li> //xml屬性中插入變量
node1: scala.xml.Elem = <li name="Test">test</li>
```

可以將複雜的表達式在XML語句中進行**多重嵌套**：

```scala
scala> val node3 = <ul>{ for (i <- 1 to 3) yield <li>{ i }</li> }</ul>
node3: scala.xml.Elem = <ul><li>1</li><li>2</li><li>3</li></ul>
```

在Scala中，節點是**不可變**的，拼接節點的正確方式是使用`Elem`類型的`cospy()`方法，並在複製時重新設定`child`參數。

`copy()`方法的定義如下所示：

```scala
def copy(
  prefix: String = this.prefix,
  label: String = this.label,
  attributes: MetaData = this.attributes,
  scope: NamespaceBinding = this.scope,
  minimizeEmpty: Boolean = this.minimizeEmpty,
  child: Seq[Node] = this.child.toSeq): Elem = Elem(prefix, label, attributes, scope, minimizeEmpty, child: _*)
```

使用`copy()`方法拼接節點如下所示：

```scala
//使用具名參數指定子節點內容
scala> node3.copy(child = node0 ++ node1)
res0: scala.xml.Elem = <ul><li>Test</li><li name="Test">test</li></ul>

//保留原節點的內容進行拼接
scala> node3.copy(child = node3.child ++ node0 ++ node1)
res1: scala.xml.Elem = <ul><li>1</li><li>2</li><li>3</li><li>Test</li><li name="Test">test</li></ul>

//創建新節點時也可以設定其它屬性，如標籤名、標籤前綴等
scala> node3.copy(child = node0 ++ node1, prefix = "Test", label = "test")
res2: scala.xml.Elem = <Test:test><li>Test</li><li name="Test">test</li></Test:test>
```



# Implicit Conversions (隱式轉換)
隱式轉換在構建類庫時是一個強大的工具。
使用隱式轉換特性需要在編譯時添加`-language:implicitConversions`選項。

## 定義隱式轉換
Scala是**強類型**語言，不同類型之間的變量默認**不會**自動進行轉換。
若需要提供類型之間的自動轉換功能，需要顯式使用`implicit`關鍵字自定義隱式轉換。
隱式轉換可以定義在**當前類**中或是**伴生對象**中，只要需要進行轉換時能被訪問到即可。

當傳入參數的類型與函數需要的類型不同時，編譯器便會查找是否有合適的隱式轉換，如下所示：

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

當訪問一個實例不存在的成員時，編譯器也會查找是否存在隱式轉換，能將其轉化爲擁有此成員的類型，如下所示：

```scala
class Implicit(val num: Int) {
  def show = println(num)
}

object Implicit {
  implicit def intToImpl(num: Int) = new Implicit(num)
}

object Main extends App {
  import Implicit.intToImpl //當隱式轉換沒有定義在當前作用域也不在實例的伴生對象中時需要顯式導入
  100.show //Int型被隱式轉換爲Implicit類型
}
```

當一個實例自身和方法的參數都能通過隱式轉換來滿足方法調用時，優先轉換方法參數而不是實例自身，如下所示：

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
  impl1.test //實例由Impl1類型隱式轉換成了Impl2類型
  impl1.show(impl1) //可以通過將實例隱式轉換爲Impl2類型來滿足方法調用，但編譯器實際執行的操作是將參數隱式轉換成了Impl2類型
}
```

輸出結果：

```
300
100
```

Scala標準類庫中大量使用了隱式轉換特性。
以`String`類型爲例，源自Java標準庫的`String`類型自身並未定義`toInt/toDouble`等成員方法，
在調用這些方法時，`String`被**隱式轉換**成定義了這些方法的`StringLike`類型來執行這些操作。

## 隱式參數
函數和方法的參數前可以添加關鍵字`implicit`來將一個參數標記爲**隱式參數**。
當調用方法時沒有對隱式參數賦值，則編譯器會嘗試爲隱式參數尋找匹配的隱式值。

變量前可以通過添加`implicit`關鍵字成爲隱式值。
示例：

```scala
object Implicit {
  implicit val impl = 200.0 //隱式值可以定義在伴生對象中
  def testImplicit(implicit num: Double) = println(num)
}

object Main extends App {
  import Implicit.impl //不在當前作用域中的隱式參數需要顯式引入
  Implicit.testImplicit
}
```

輸出結果：

```
200.0
```

**單例對象**定義時也可添加`implicit`關鍵字成爲隱式值。
示例：

```scala
object Main extends App {

  trait Base[T] { val value: T }
  implicit object Test extends Base[Int] { val value = 2333 } //以單例對象形式定義隱式類

  def testImplicit[T](implicit base: Base[T]) = println(base.value)

  testImplicit //無需參數調用隱式方法

}
```

輸出結果：

```
2333
```

隱式參數的限制：

- 用於聲明隱式參數的`implicit`關鍵字只能出現在參數表的最前端，隱式參數的聲明對當前參數表內的**所有參數**有效。
- 使用柯里化定義多個參數表時，只能聲明**最後一個**參數表內的參數爲隱式參數。
- 一個隱式參數在被調用的作用域內存在多個匹配的同類型隱式值時，編譯報錯。

示例：

```scala
def testImplicit(implicit num0: Int, num1: Int) {} //正確。num0、num1，皆爲隱式參數
def testImplicit(implicit num0: Int, implicit num1: Int) {} //錯誤。只能在參數表的首個參數前添加implicit關鍵字修飾
def testImplicit(num0: Int, implicit num1: Int) {} //錯誤。只能在參數表的首個參數前添加implicit關鍵字修飾

def testImplicit(num: Int)(implicit num0: Int, num1: Int) {} //正確。對於柯里化函數，最後一個參數表可以設爲隱式參數
def testImplicit(implicit num0: Int)(implicit num1: Double) {} //錯誤。一個方法不允許擁有多個隱式參數表
def testImplicit(implicit num0: Int)(num1: Double) {} //錯誤。只有最後一個參數表可以設爲隱式參數表
```

- 隱式參數與參數默認值

	隱式參數與參數默認值特性**可以**共存。

	當一個方法的所有隱式參數均帶有默認值時，可以直接調用，如下所示：

	```scala
	object Main extends App {

	  // 方法帶有默認參數以及參數默認值
	  def testImplicit(implicit num0: Int = 0, num1: Double = 0) = println(s"$num0 $num1")

	  // 直接調用，無需隱式參數
	  testImplicit
	}
	```

	輸出結果：

	```
	0 0.0
	```

- 隱式參數與默認值的優先級

	- 當一個方法的隱式參數帶有部分默認值時，隱式調用時只需提供沒有默認值的部分參數。
	- 當一個隱式參數既有默認值又有隱式值時，會優先使用隱式值。

	示例：

	```scala
	object Main extends App {

	  def testImplicit(implicit num0: Int = 0, num1: Double) = println(s"$num0 $num1")

	  // 只需爲沒有默認值的參數提供隱式值
	  implicit val num1 = 2.0
	  testImplicit

	  // 此時num0既有隱式值，也有參數默認值
	  implicit val num0 = 1
	  testImplicit
	}
	```

	輸出結果：

	```
	0 2.0
	1 2.0
	```

	輸出結果說明第二次調用`testImplicit()`方法時，優先採用了隱式值而非參數默認值。

	隱式值與參數默認值在方法調用時區別如下：

	- 採用參數默認值時，即使參數全部擁有默認值，參數表不可省略(`()`操作符必須存在)。
	- 採用隱式值時，隱式參數全部具有隱式值或默認值時，參數表直接省略。

	當一個隱式參數表的所有參數均帶有默認值且作用域內也擁有滿足條件的隱式值時，調用方法時帶有`()`操作符爲使用默認值，省略參數表爲使用隱式值。

	示例：

	```scala
	object Test extends App {

	  def testImplicit(implicit num0: Int = 0, num1: Double = 0) = println(s"$num0 $num1")

	  implicit val num0 = 1
	  implicit val num1 = 1.0

	  testImplicit //全部採用隱式值
	  testImplicit() //全部採用默認值
	}
	```

	輸出結果：

	```
	1 1.0
	0 0.0
	```

## 隱式類
類定義前同樣可以使用`implicit`成爲**隱式類**。

- 隱式類的主構造器**有且只有**一個參數，同時，該參數**不能**爲隱式參數。
- 隱式類的主構造器不能通過參數默認值、隱式參數等形式來模擬成參數表成只有一個參數的情況。
- 隱式類特性**不能**與樣例類共存，即一個類在定義時不能同時帶有`implicit`和`case`關鍵字。
- 隱式類**不能**定義在外部區域(包，以及包對象)，隱式類只能定義在類體、函數體、單例對象中。

與**隱式轉換**類似，當一個實例調用了**不存在**或**無法訪問**的成員方法，編譯器會爲之搜索作用域中可訪問的隱式類。
若隱式類的構造器參數與實例相同且帶有實例調用的方法，則自動調用該隱式類的構造器。

示例：

```scala
object Main extends App {

  case class Source(num: Int) {
    private def show = print(num)
  }

  implicit class Impl(source: Source) {
    def show = println("Implicit Class")
    def show(num: Int) = println(s"Implicit Class: $num")
  }

  Source(0).show //調用無法訪問的成員方法可能觸發隱式轉換
  Source(0).show(100) //調用不存在的方法也能觸發隱式轉換
}
```

輸出結果：

```
Implicit Class
Implicit Class: 100
```



# 求值策略
常見的編程語言中存在三種求值策略：

1. `Call by value`，在表達式定義時立即求值，僅在定義時求值**一次**。
1. `Call by name`，在表達式調用時求值，每次調用都會對錶達式重新求值。
1. `Call by need`/`Lazy evaluation`，在表達式首次調用時求值，僅在首次被訪問時求值**一次**。

Call by need是Call by name的帶有記憶性的變體，Call by need的字段在需要時被求值，
字段綁定的表達式執行後結果會被存儲，之後再次訪問該字段時，不會再重複執行計算。

在Scala中，Call by value是默認行爲，
函數參數以及使用`val/var`定義字段時即爲即爲直接求值，此類字段值在定義時即被確定；
使用`lazy val`定義的字段(var與lazy不能搭配使用)爲Call by need，此類字段在首次被訪問時求值；
使用`def`定義的字段(無參方法)、傳名參數爲Call by name，此類字段在調用時纔會求值，且每次調用重新求值。

示例：

```scala
object Main extends App {

  var num = 23333

  // 立即求值，test0 值爲 23333
  val test0 = {
    println("Call test0")
    num
  }

  // 在調用表達式時纔會進行求值，每次都求值
  def test1 = {
    println("Call test1")
    num
  }

  // 首次調用時求值，之後不再求值
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

輸出結果：

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

Call by value的字段`test0`在定義時值已被確定，僅在定義時求值一次，三次輸出結果相同；
Call by name的字段`test1`在每次調用時重新求值，三次輸出結果不同；
Call by need的字段`test2`在首次被訪問時進行求值，兩次輸出結果相同。

## 參數的求值策略
與大多數編程語言類似，Scala中的方法參數默認即爲Call by value，參數在傳入時立即求值，如下所示：

```scala
scala> def show(num: Int) {
     |   println("Run show()!")
     |   println(s"num: $num")
     |   println(s"num: $num")
     | }
show: (num: Int)Unit

scala> show {
     |   println("Call show()!")
     |   23333
     | }
Call show()!
Run show()!
num: 23333
num: 23333
```

做爲參數的代碼塊在傳入方法時便已被執行，參數代碼塊僅執行一次。

使用`By-name parameter`(**傳名參數**)特性可以使方法參數變爲Call by Name。
傳名參數語法爲在類型前添加`=>`操作符，上述例子改用傳名參數，如下所示：

```scala
// 參數 num 爲傳名參數
scala> def show(num: => Int) {
     |   println("Run show()!")
     |   println(s"num: $num")
     |   println(s"num: $num")
     | }
show: (num: => Int)Unit

scala> show {
     |   println("Call show()!")
     |   23333
     | }
Run show()!
Call show()!
num: 23333
Call show()!
num: 23333
```

做爲傳名參數的代碼塊在傳入方法時並未執行，在參數被訪問時才真正執行。
每次訪問傳名參數時都重新進行求值。

## && 與 || 運算符
在傳統編程語言中，雙目運算符`&&`、`||`具有Call by name特性：

- 若`&&`運算符左側表達式值爲`false`，則右側表達式不被執行。
- 若`||`運算符左側表達式值爲`true`，則右側表達式不被執行。

示例：

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

在C++中，代碼**近似**於：

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

輸出結果：

```
expr1_1
expr2_1
```

輸出結果中沒有`&&`、`||`運算符右側表達式的輸出，表達式並未被執行。

### 模擬 && 、 || 運算符
編寫自定義方法`and()`、`or()`在不使用內建`&&`、`||`的情況下模擬`&&`、`||`運算符。

使用默認求值策略(Call by value)，如下所示：

```scala
object Main extends App {

  // 使用隱式類爲 Boolean 類型提供額外操作
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

輸出結果：

```
expr1_1
expr1_2
expr2_1
expr2_2
```

輸出結果中`and()`、`or()`方法右側的表達式已被執行。
在Call by value求值策略下，參數一經傳入便已被求值，不符合`&&`、`||`運算符邏輯。

使用傳名參數(Call by name)：

```scala
object Main extends App {

  // 方法參數採用傳名參數特性
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

輸出結果：

```
expr1_1
expr2_1
```

在Call by name求值策略下，右側表達式並未執行，符合`&&`、`||`運算符邏輯。



# 類型系統
Scala是靜態類型語言，具有強大的類型系統。

## 類型參數
定義類型時允許帶有類型參數。

使用以下方式定義類型參數：

- 使用泛型語法，`class Xxx[T]/trait Xxx[T]`
- 使用`type`關鍵字定義未綁定到具體類型的**抽象類型**(`Abstract Type`)，`trait Xxx { type T }`

泛型語法類似於`Java/C#`，但在Scala中使用中括號`[]`代替尖括號`<>`。
構建示例時需要將泛型參數替換爲實際類型。
示例：

```scala
scala> trait Xxx[T] { val t: T }
defined trait Xxx //定義帶有泛型參數的類型

scala> val x = new Xxx[String] { val t = "t" }
x: Xxx[String] = $anon$1@7ca16520

scala> x.t
res1: String = t

scala> :type x
Xxx[String]
```

抽象類型與抽象成員類似，需要在構建實例時提供具體實現。
示例：

```scala
scala> trait Xxx { type T; val t: T }
defined trait Xxx //定義帶有抽象類型的類型

scala> val x = new Xxx { type T = String; val t = "t" }
x: Xxx{type T = String} = $anon$1@36acfcff

scala> x.t
res2: x.T = t

scala> :type x
Xxx{type T = String}
```

## 類型約束
定義類型參數時可以設置類型約束，用於限制傳入的類型參數：

- `Upper Type Bounds` 上界(上層類型約束)，語法`T <: Xxx`
- `Lower Type Bounds` 下界(低級類型約束)，語法`T >: Xxx`

`Upper Type Bounds`用於限定類型參數爲指定類型的**子類**，如下所示：

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

類型約束亦可用於類型定義，`class/trait`均支持該特性：

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

`Lower Type Bounds`用於限定類型參數爲另一類型的**父類**，如下所示：

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

使用`Lower Type Bounds`可以將傳入的更細粒度的類型轉換爲更粗粒度的類型。

## View Bounds (視圖界定)
`View Bounds`(視圖界定)相比普通類型約束更加**寬鬆**，類型參數不必自身滿足類型約束，
僅需類型參數能被**隱式轉換**爲滿足類型約束的類型。

視圖界定語法爲`T <% Xxx`，可用於方法定義與類型定義。
與類型界定不同，**不存在**`T >% Xxx`這樣的語法。
示例：

```scala
scala> trait Other
defined trait Other

scala> trait Base
defined trait Base

scala> trait Child extends Base
defined trait Child

scala> def test[T <% Base](t: T) = t //使用視圖界定會生成隱式參數表
test: [T](t: T)(implicit evidence$1: T => Base)T

scala> test[Child](null) //與上級類型約束類似，使用子類能夠滿足約束條件
res1: Child = null

scala> test[Other](null) //使用無關類型不能滿足約束條件
<console>:14: error: No implicit view available from Other => Base.
       test[Other](null)
                  ^

scala> implicit def otherToChild(t: Other) = null: Child //定義隱式轉換
otherToChild: (t: Other)Child

scala> test[Other](null) //提供符合要求的隱式轉換後能夠正常調用方法
res3: Other = null
```

實際上視圖界定是隱式參數的語法糖，使用視圖界定時會生成`implicit xxx: T => Xxx`形式的隱式參數表。
不能帶有有參構造器的`trait`類型**不能**使用視圖界定特性。
示例：

```scala
scala> class Test[T <% Base] //定義類型時使用視圖界定
defined class Test

scala> trait Test[T <% Base] //特質無法使用視圖界定特性
<console>:1: error: traits cannot have type parameters with context bounds `: ...' nor view bounds `<% ...'
       trait Test[T <% Base]
                            ^
```

## Content Bounds
`Content Bounds`(上下文界定)要求上下文中存在類型爲`Xxx[T]`的隱式值。

上下文界定語法爲`T: Xxx`，可用於方法定義與類型定義，如下所示：

```scala
scala> class Xxx[T]
defined class Xxx

scala> def test[T: Xxx] = null //上下文界定用於方法類型參數，生成隱式參數表
test: [T](implicit evidence$1: Xxx[T])Null

scala> class Test[T: Xxx] //上下文界定用於類型定義
defined class Test

scala> test[Int] //調用方法出錯，缺少符合要求隱式值
<console>:14: error: could not find implicit value for evidence parameter of type Xxx[Int]
       test[Int]
           ^

scala> new Test[Int] //構建實例出錯，缺少符合要求隱式值
<console>:14: error: could not find implicit value for evidence parameter of type Xxx[Int]
       new Test[Int]
       ^

scala> implicit object XxxInt extends Xxx[Int] //提供隱式值
defined object XxxInt

scala> test[Int] //正常調用
res1: Null = null

scala> new Test[Int] //正常構建實例
res2: Test[Int] = Test@62640933
```

與視圖界定類似，上下文界定亦是隱式參數的語法糖，使用上下文界定會生成`implicit xxx: Xxx[T]`的隱式參數表。
不能帶有有參構造器的`trait`類型**不能**使用上下文界定特性。
示例：

```scala
scala> trait Test[T: Xxx]
<console>:1: error: traits cannot have type parameters with context bounds `: ...' nor view bounds `<% ...'
trait Test[T: Xxx]
                  ^
```

上下文界定生成的隱式參數表中的隱式參數名稱有編譯器合成，無法直接通過參數名稱訪問該隱式值。
獲取隱式值需要使用`Predef`包中定義的`implicitly[T]()`方法。
示例：

```scala
scala> def test[T: Seq] = println(implicitly[Seq[T]]) //打印獲取到的隱式值
test: [T](implicit evidence$1: Seq[T])Unit

scala> implicit val seq = Seq(6, 6, 6) //提供隱式值
seq: Seq[Int] = List(6, 6, 6)

scala> test[Int] //調用使用了上下文界定的方法，輸出隱式值
List(6, 6, 6)
```

## Variances (型變)
泛型類型在使用不同類型參數時默認**不存在**繼承關係，如下所示：

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
res1: Boolean = false //帶有不同類型參數的泛型類是不相等的類型

scala> typeOf[Test[Base]] <:< typeOf[Test[Child]]
res2: Boolean = false //類型參數的繼承關係不影響泛型類型自身
```

使用`variances`特性可使類型參數的繼承關係擴展到承載類型參數的泛型類型自身。
`variances`特性分爲`covariance`(協變)和`contravariance`(逆變)。

型變特性語法：

```scala
class Test[T] //invariance，無型變
class Test[+T] //covariance，協變
class Test[-T] //contravariance，逆變
```

- `Covariance` (協變)

	類型參數聲明爲`covariance`(協變)時，泛型類型的繼承關係與類型參數相：

	```scala
	scala> class Test[+T] //定義帶有協變類型參數的泛型類型
	defined class Test

	scala> typeOf[Child] <:< typeOf[Base]
	res3: Boolean = true

	scala> typeOf[Test[Child]] <:< typeOf[Test[Base]]
	res4: Boolean = true //泛型類型的繼承關係與類型參數相同
	```

	帶有協變類型參數的泛型類型用於方法參數/返回值中，使方法能接受/返回帶有子類類型參數的泛型類型：

	```scala
	scala> class Test[T]
	defined class Test

	scala> def test(t: Test[Base]) = t.toString
	test: (t: Test[Base])String

	scala> test(new Test[Child]) //泛型類型的參數不支持協變，報錯
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

	scala> test(new Test[Child]) //正常調用方法
	res5: String = Test@61fbec8a

	scala> def test: Test[Base] = new Test[Child]
	test: Test[Base]
	```

- `Contravariance` (逆變)

	類型參數聲明爲`contravariance`(逆變)時，泛型類型的繼承關係與類型參數相反：

	```scala
	scala> class Test[-T] //定義帶有逆變類型參數的泛型類型
	defined class Test

	scala> typeOf[Child] <:< typeOf[Base]
	res6: Boolean = true

	scala> typeOf[Test[Base]] <:< typeOf[Test[Child]]
	res7: Boolean = true //泛型類型的繼承關係與類型參數相反
	```

協變與逆變的類型參數需要在正確的位置使用，即`covariant position`(協變點)和`contravariant position`(逆變點)。

- `Covariant Position` (協變點)

	協變點指方法的**返回值**位置。
	根據**里氏替換原則**，子類的方法返回值應比父類更具體。

- `Contravariant Position` (逆變點)

	逆變點指方法的**參數**位置。
	根據**里氏替換原則**，能通過父類實例調用的方法一定能通過子類實例調用，因此子類方法參數類型接收範圍應比父類更廣。

在錯誤的位置使用型變類型參數會導致編譯錯誤：

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



# Higer Kinded Type (高階類型)
高階類型是對類型的高級抽象，是類型參數爲類型構造器的泛型類型。
示例：

```scala
scala> import scala.language.higherKinds
import scala.language.higherKinds

scala> class Test[T[_]]
defined class Test
```

類型`Test`接收一個類型爲`T[_]`的類型參數，僅能使用泛型類型做爲類型參數：

```scala
scala> new Test[Int] //使用普通類型做爲類型參數，報錯
<console>:14: error: Int takes no type parameters, expected: one
       new Test[Int]
                ^

scala> new Test[Seq] //使用泛型類型爲類型參數，正確
res1: Test[Seq] = Test@11cc9e1e
```

`Type Theory`(類型理論)中的`Kind`(型別)在Scala中的對應概念：

| Kind | 含義 | Scala中的對應概念 | 實例 |
| :- | :- | :- | :- |
| * | 類型 | 普通類型，或帶有具體類型參數的泛型類型 | `Int`, `List[Int]` |
| * -> * | 一階類型(類型構造器) | 泛型類型 | `List[_]`, `Seq[_]`, `Map[_, String]` |
| * -> ... -> * | 一階類型(帶有多個參數的類型構造器)| 帶有多個類型參數的泛型類型 | `Map[_, _]`, `Function2[_, _, _]`, `Tuple4[_, _, _, _]` |
| (* -> *) -> * | 高階類型(參數爲類型構造器的類型構造器)| 帶有泛型類型參數的泛型類型 | `List[T[_]]`, `Seq[T[_]]` |

## Type Lambda
`Type Lambda`是高階類型的擴展應用，允許在類型參數的位置直接定義新的類型構造器。Scala支持有限的TypeLambda。

定義一個高階類型，類型參數爲接收兩個參數的一階類型：

```scala
scala> import scala.language.higherKinds
import scala.language.higherKinds

scala> class TestTypeLambda[T[_, _]](t: T[_, _])
defined class TestTypeLambda
```

以三元組`(_, _, _)`(`Tuple3[_, _, _]`)爲例，直接傳入實例編譯器報錯。
三元組的類型參數數目與`TestTypeLambda`類型中的類型約束不符，無法通過編譯：

```scala
scala> new TestTypeLambda((1, 2, 3))
<console>:14: error: no type parameters for constructor TestTypeLambda: (t: T[_, _])TestTypeLambda[T] exist so that it can be applied to arguments ((Int, Int, Int))
 --- because ---
argument expression's type is not compatible with formal parameter type;
 found   : (Int, Int, Int)
 required: ?T[_$1, _$2] forSome { type _$1; type _$2 }
       new TestTypeLambda((1, 2, 3))
       ^
<console>:14: error: type mismatch;
 found   : (Int, Int, Int)
 required: T[_, _]
       new TestTypeLambda((1, 2, 3))
                          ^
```

一階類型的參數數目不匹配時可通過`Type Alias`定義新的類型構造器，使類型簽名符合要求：

```scala
scala> type T[A, B] = (A, B, Int)
defined type alias

scala> new TestTypeLambda[T]((1, 2, 3))
res1: TestTypeLambda[T] = TestTypeLambda@222a7429
```

新的`Type Alias`可直接使用`Structural Type`語法在類型參數處定義，並使用`#`語法提取：

```scala
scala> new TestTypeLambda[({ type T[A, B] = (A, B, Int) })#T]((1, 2, 3))
res2: TestTypeLambda[[A, B](A, B, Int)] = TestTypeLambda@403b7be3
```

其中，`({ type T[A, B] = (A, B, Int) })#T`即爲一個TypeLambda，
以函數視角而言，使用Lambda語法表示近似於`(A, B) => Tuple3[A, B, Int]`。

普通Lambda提供值之間的變化邏輯，TypeLambda提供類型層面的轉換邏輯。



# Type Class
`Type Class`即**類型類**，是一種通過泛型參數實現多態的方式。
根據不同的泛型參數，簽名相同的方法會調用不同的實現。

Scala中使用**隱式參數**特性來實現TypeClass。
定義一個帶有泛型參數的類型(TypeClass)，和使用隱式參數接收該泛型實例的方法：

```scala
scala> trait TypeClass[T] {
     |   def doSomething(): Unit
     | }
defined trait TypeClass

scala> def testTypeClass[T]()(implicit typeClass: TypeClass[T]) = typeClass.doSomething()
testTypeClass: [T]()(implicit typeClass: TypeClass[T])Unit
```

使用隱式單例爲TypeClass提供不同的實現：

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

調用`testTypeClass()`方法時，使用不同的泛型參數編譯器會自動選擇合適的隱式對象做爲實現：

```scala
scala> testTypeClass[Int]()
Int Type Class

scala> testTypeClass[String]()
String Type Class

scala> testTypeClass[Double]() //使用未提供隱式實例的泛型參數時，報錯
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

  implicit object IntTypeClass extends TypeClass[Int] {
    def doSomething(t: Int) = println(s"Int Type Class: $t")
  }

  implicit object StringTypeClass extends TypeClass[String] {
    def doSomething(t: String) = println(s"String Type Class: $t")
  }

  def testTypeClass[T: TypeClass](t: T) = implicitly[TypeClass[T]].doSomething(t)

  testTypeClass(233)
  testTypeClass("666")

}
```

TypeClass是`Haskell`等FP語言實現參數化多態的主要方式。
在Haskell中，上述代碼近似於：

```hs
{-# LANGUAGE FlexibleInstances #-}

module Main where

class TypeClass t where
  doSomething :: t -> IO ()

instance TypeClass Int where
  doSomething = print . ("Int Type Class: "++) . show

-- 使用語言擴展 FlexibleInstances 開啓泛型參數特化
instance TypeClass String where
  doSomething = print . ("String Type Class: "++)

testTypeClass :: TypeClass t => t -> IO ()
testTypeClass = doSomething

main :: IO ()
main = do
  testTypeClass (233 :: Int)
  testTypeClass "666"
```

輸出結果：

```
Int Type Class: 233
String Type Class: 666
```

C++中的**模板特化**功能上亦與TypeClass類似。



# 併發編程
作爲JVM平臺的編程語言，Scala可以直接調用Java的併發API。
併發編程是Scala的擅長領域，除了Java標準庫提供的併發API，Scala還提供下列併發技術：

- Scala標準庫中提供了`Future/Promise/Async`庫來進行異步編程。
- 基於Scala的`Akka`完整實現了`Actor`模型。

## Future
`Future`是一組異步操作的抽象，完整包路徑爲`scala.concurrent.Future`。

- 構建與啓動`Future`

	`Future`爲**特質**，沒有構造函數，無法直接構建實例。
	創建一個`Future`實例需要使用伴生對象中重寫的`apply()`方法，聲明如下：

	```scala
	def apply[T](body: =>T)(implicit @deprecatedName('execctx) executor: ExecutionContext): Future[T]
	```

	- `body`參數爲**傳名參數**，包含了需要異步執行的代碼塊。
	- `T`參數爲泛型參數，表示異步執行的代碼塊最終的返回值類型。
	- `executor`參數爲隱式參數，用於指定異步代碼的執行器。
	`scala.concurrent.ExecutionContext.Implicits.global`提供了默認的執行器。

	構建一個`Future`，基本代碼如下：

	```scala
	import scala.concurrent.Future
	import scala.concurrent.ExecutionContext.Implicits.global

	val future = Future[XXX] {
	  /* Code you want to excute... */
	}
	```

	與傳統的併發庫設計不同，`Future`並沒有提供諸如`start()/run()`之類的方法用於顯式開始異步代碼塊的執行。
	在完成`Future`實例構建的同時，作爲參數傳入的代碼塊就已自動開始異步執行。

- Callbacks (異步回調)

	與傳統的併發庫設計類似，`Future`採用回調的方式來處理異步操作完成的結果。
	`Future`實例提供了`onComplete()`成員方法來綁定回調函數，聲明如下：

	```scala
	def onComplete[U](@deprecatedName('func) f: Try[T] => U)(implicit executor: ExecutionContext): Unit
	```

	- `f`參數爲被回調的高階函數。
	- `executor`參數作用與上述`apply()`方法中類似。

	被回調的高階函數類型爲`Try[T] => U`。
	抽象類`Try[T]`類似於`Option[T]`，擁有兩個樣例類子類`Success[T]`和`Failure[T]`，定義如下：

	```scala
	final case class Success[+T](value: T) extends Try[T] { ... }
	final case class Failure[+T](exception: Throwable) extends Try[T] { ... }
	```

	在編寫回調函數時，可使用模式匹配語法：

	- 對於**成功**的異步操作，匹配內容是異步操作的返回值。
	- 對於**失敗**的異步操作，匹配內容是導致異步操作失敗的異常。

	`Future`也提供了`onSuccess()/onFailure()`方法接收偏函數分別處理異步操作成功/失敗時的情況。
	當只需要處理某一類情況時，可以直接使用對應方法。

	一個`Future`實例可以**多次**調用`onComplete()/onSuccess()/onFailure()`來添加多個回調操作。
	多個回調操作都會被執行，但執行的先後順序**不確定**。

	回調處理異步操作結果的基本代碼如下：

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

	在個別情況下，可能需要等待異步操作執行完畢。
	等待`Future`紙型完畢可以使用`Await`單例，完整包路徑爲`scala.concurrent.Await`。

	`Await`單例提供了`result()`方法用於同步等待`Future`執行完畢，定義如下：

	```scala
	def result[T](awaitable: Awaitable[T], atMost: Duration): T
	```

	- `awaitable`參數爲`Awaitable`類型，用於表示一個可等待的操作，`Future`特質爲其子類，可支持傳入`Future`實例作爲參數。
	- `atMost`參數爲同步等待的時間。

	基本用法如下：

	```scala
	import scala.concurrent.Await
	import scala.concurrent.duration.Duration

	val result = Await.result(future, Duration.Inf)
	println(result)
	...
	```

 	- Duration (時間類型)

		時間參數類型爲`Duration`，爲抽象類，完整路徑爲`scala.concurrent.duration.Duration`。
		Duration的伴生對象內定義了`apply()`方法，聲明如下：

		```scala
		def apply(length: Long, unit: TimeUnit): FiniteDuration
		```

		- `length`參數爲時間數值。
		- `unit`參數爲時間單位。

		構建的時間對象爲`Duration`的子類，有限時間`FiniteDuration`。
		`Duration`中有兩個成員`Inf`、`MinusInf`分別用來表示**無限大/無限小**的時間。

		`TimeUnit`類型完整包路徑爲`java.util.concurrent.TimeUnit`，爲枚舉類型，包含以下枚舉成員：

		- `java.util.concurrent.TimeUnit.DAYS` 天
		- `java.util.concurrent.TimeUnit.HOURS` 小時
		- `java.util.concurrent.TimeUnit.MICROSECONDS` 微秒
		- `java.util.concurrent.TimeUnit.MILLISECONDS` 毫秒
		- `java.util.concurrent.TimeUnit.MINUTES` 分鐘
		- `java.util.concurrent.TimeUnit.NANOSECONDS` 納秒
		- `java.util.concurrent.TimeUnit.SECONDS` 秒

		在`import scala.concurrent.duration`包中定義了一系列隱式類`DurationInt/DurationLong/DurationDouble`。
		引用對應隱式類即可使用對應的DSL語法來構建時間對象`FiniteDuration`，如：

		- `1000 days`被轉換爲`Duration(1000, java.util.concurrent.TimeUnit.DAYS)`
		- `1000 minutes`被轉換爲`Duration(1000, java.util.concurrent.TimeUnit.SECONDS)`
		- ...

		諸如此類...
		在`scala.concurrent.duration.DurationConversions`特質中定義了完整的轉化語法。

- blocking (阻塞塊)

	`Future`是異步執行的，不會阻塞基礎的執行線程。但在某些情況下，阻塞是必要的，需要區別兩種形式的執行線程阻塞：

	- 從`Future`內部調用任意代碼阻塞線程。
	- 在`Future`外部等待一個`Future`完成。

	在`Future`外部主動阻塞等待應使用`Await`類，在`Future`內部阻塞則應使用`blocking`方法。
	`blocking`定義在包對象`scala.concurrent`中，是一個接收**傳名參數**的泛型方法，定義如下所示：

	```scala
	def future[T](body: =>T)(implicit @deprecatedName('execctx) executor: ExecutionContext): Future[T] = Future[T](body)
	```

	`blocking`塊的作用是向執行器(`ExecutionContext`)標記可能造成阻塞的代碼，並調整執行器的行爲。
	對於默認的執行器`scala.concurrent.ExecutionContext.Implicits.global`，在`Future`中包含`blocking`塊時，會新建線程來執行`Future`而不是等待複用已有的線程。

	示例：

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

	輸出結果：(Scala 2.11.8 && ArchLinux x64)

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

	打印執行結果的過程中，輸出流出現了幾次3秒的停頓。
	從結果中不難看出，執行器只開闢了`15`個處理線程，在所有處理線程都處於`sleep`狀態時，輸出流便停止。

	嘗試將`sleep()`函數寫在`blocking`中：

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

	輸出結果：(Scala 2.11.8 && ArchLinux x64)

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

	整個輸出過程中，僅有**一次**3秒的停頓。
	分析輸出結果，可以得知：

	1. 執行器開闢的工作線程的數量明顯大於沒有`blocking`時的數量(線程數目`> 50`)。
	即使用`blocking`改變了執行器的線程創建策略。
	1. 相同`Index`輸出的線程名稱相同，`blocking`包含的代碼、之後的代碼並沒有運行在獨立的線程。
	即一個獨立的`Future`運行在一個線程，**沒有**像`C#`中的`async`方法那樣被切分到不同的線程執行。

## Promise
`Promise`爲特質，完整包路徑爲`scala.concurrent.Promise`。

- `Future`提供了帶有**只讀佔位符**(`read-only placeholder`)的返回值，只有一個異步操作完全結束才能獲取其返回值。
- `Promise`則提供了可寫的、單一指派(`writable、single-assignment`)的分配容器。

使用`Promise`：

1. `Promise`特質的伴生對象中提供了空參的`apply()`方法用於構建默認的`Promise`實例(`DefaultPromise`類型)。
1. `Promise`實例提供了無參的`future`方法用於獲取自身的`Future`實例。
1. `Promise`實例可以通過`success()/failure()`方法標記自身`Future`實例的執行結果，使用`isCompleted`方法判斷`Future`實例的執行狀態。
1. `Promise`實例的`success()/failure()`方法只能選其一，且只能調用一次。`success()/failure()`方法一旦被調用，自身`Future`實例的執行結果便已確定，不可更改。
1. 多個`Future`可通過`Promise`共享數據。
1. `Promise`能使用`completeWith()`綁定一個其它的`Future`，讓自身同被綁定的`Future`擁有相同的執行狀態和**執行結果**。

實例，一個`Future`通過使用`Promise`獲取另一個`Future`中的執行狀態(**不是**執行結束的返回內容)，基本代碼如下：

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

## async/await
Scala也提供了`Async`庫用於簡化`Future`的使用。
`Async`完整包路徑爲`scala.async.Async`。

當前版本(`Scala 2.11.8`)中，`Async`庫尚未進入Scala標準庫。
對於使用`sbt`的工程，則需要在`build.sbt`配置文件中添加依賴：

```scala
libraryDependencies += "org.scala-lang.modules" %% "scala-async" % "版本號"
```

單例`Async`的定義如下：

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

- `async`用法類似`Future`的`apply()`方法，
接收傳名參數`body`作爲異步執行的內容，接收隱式參數`execContext`作爲執行器。
- `await`只能用在`async`代碼塊中，作用類似`Await.result()`方法。

`async`利用了Scala的宏機制，`await`本質上是`async`代碼塊中的一個關鍵字。
由於宏機制的一些限制，不能將`await`用在循環、異常捕捉代碼塊以及閉包中。

## synchronized
Java中提供了`synchronized`關鍵字用於多線程環境下的變量同步。
Scala中提供了類似的機制，但語法略有不同。

Scala中的`synchronized`不是語言級別的關鍵字，僅僅做爲**成員方法**存在，方法簽名爲：

```scala
def synchronized[T](t: T): T
```

所有類型都包含此方法。

調用語法爲：

```scala
變量名.synchronized(語句)
```

使用中綴表達式和塊語法：

```scala
變量名 synchronized {
  語句1
  語句2
  ...
}
```

在類中直接調用`synchronized()`方法，鎖定變量爲當前類實例。
在單例對象/伴生對象中直接調用`synchronized()`方法，鎖定變量爲單例對象、伴生對象實例。

Scala中的`synchronized`沒有Java中修飾方法的功能，但可以模擬出類似效果。
示例：

Java代碼：

```java
class TestSync {
	synchronized public void test() { ... }
	synchronized public static void staticTest() { ... }
}
```

等價Scala代碼：

```scala
class TestSync {
  def test() = synchronized[Unit] { ... }
}
object TestSync {
  def staticTest() = synchronized[Unit] { ... }
}
```



# Reflect (反射)
`Scala 2.10`之後提供了自身的反射相關API。

Java標準庫中的反射API不支持Scala的專有語言特性。
Scala自身提供的反射API能完整地支持所有Scala語言特性。

到目前版本(`Scala 2.12`)爲止，反射相關功能依然是`Expermental`(**實驗性**)的，相關API在後續版本中可能會有較大改動。

## 反射機制相關類型
反射API相關的類型定義在包路徑`scala.reflect.runtime.universe`中。

### Type
`Type`類型包含類型內的成員信息(定義的字段`fields`、方法`methods`、類型別名`type aliases`等)、類型繼承關係、基類信息等。

Type類型類似於Java反射機制中的`Class`類型，獲取Type實例是整個反射流程的起始步驟。
通過`typeOf[T]`方法可以獲取指定類型的Type實例。

Type類型可用於篩選出需要反射的成員的符號信息：

- `Type.decls` 獲取用戶定義的成員的Symbol
- `Type.members` 獲取類內所有成員的Symbol
- `Type.decl()/member()` 獲取指定`TermName`的成員Symbol

Type可用於類型比較：

- 通過操作符`=:=`比較是否相等
- 通過操作符`<:<`比較是否子類

### Symbol
`Symbol`類型包含實例/成員的完整信息。

Symbol提供了名稱與所指向的類型的綁定(`establish bindings between a name and the entity it refers to`)。
Symbol包含了類型(`class/trait/object`等)或成員(`val/var/def`等)的所有可用信息(`contain all available information about the declaration of an entity or a member`)。

根據包含信息的類別差異，Symbol類型存在以下子類：

- `TypeSymbol`

	`TypeSymbol`表示類型、類、特質的定義，以及類型參數(`TypeSymbol represents type, class, and trait declarations, as well as type parameters`)。

	存在以下子類：

	- `ClassSymbol`

		提供對包含在類、特質中所有信息的訪問(`Provides access to all information contained in a class or trait declaration`)。

	構建TypeSymbol/ClassSymbol：

	- `Type.typeSymbol` 通過Type實例獲取類型對應的TypeSymbol
	- `symbolOf[T]` 直接通過泛型參數構建TypeSymbol
	- `Mirror.staticClass()` 通過類型完整名稱得到ClassSymbol

- `TermSymbol`

	`TermSymbol`表示字段、方法、單例的定義，以及包、參數(`The type of term symbols representing val, var, def, and object declarations as well as packages and value parameters`)。

	存在以下子類：

	- `MethodSymbol`

		表示方法定義(`method symbols representing def declarations`)。
		支持查詢方法是否爲(主)構造器，或方法是否支持可變參數等(`It supports queries like checking whether a method is a (primary) constructor, or whether a method supports variable-length argument lists`)。

	- `ModuleSymbol`

		表示單例對象定義(`module symbols representing object declarations`)。

- `Mirror`

	所有反射提供的信息需要通過各類Mirror來獲取(`All information provided by reflection is made accessible through mirrors`)。

	Mirror及相關類型的定義爲：

	```scala
	trait JavaUniverse extends Universe { self =>
	  ...
	  override type Mirror >: Null <: JavaMirror

	  trait JavaMirror extends scala.reflect.api.Mirror[self.type] with RuntimeMirror {
	    ...
	  }
	  ...
	}

	abstract class Mirror[U <: Universe with Singleton] {
	  ...
	  def staticClass(fullName: String): U#ClassSymbol
	  def staticModule(fullName: String): U#ModuleSymbol
	  def staticPackage(fullName: String): U#ModuleSymbol
	  ...
	}

	trait Mirrors { self: Universe =>
	  ...
	  trait ReflectiveMirror extends scala.reflect.api.Mirror[Mirrors.this.type] {
	    def reflect[T: ClassTag](obj: T): InstanceMirror
	    def reflectClass(cls: ClassSymbol): ClassMirror
	    def reflectModule(mod: ModuleSymbol): ModuleMirror
	  }

	  trait RuntimeMirror extends ReflectiveMirror { self =>
	    ...
	  }
	  ...
	}
	```

	Mirror類型是JavaMirror的子類，JavaMirror混入了RuntimeMirror特質，RuntimeMirror又繼承自ReflectiveMirror。
	ReflectiveMirror提供了一系列reflect方法用於獲取不同的Mirror：

	- `ReflectiveMirror.reflect()` 獲取`InstanceMirror`，用於反射訪問/修改字段，調用方法
	- `ReflectiveMirror.reflectClass()` 獲取`ClassMirror`，可獲取類型構造方法反射構建實例
	- `ReflectiveMirror.reflectModule()` 獲取`ModuleMirror`，可獲取單例對象實例

	`scala.reflect.runtime`包對象中提供了`currentMirror`方法用於獲取當前環境下的Mirror實例：

	```scala
	package scala
	package reflect

	package object runtime {
	  ...
	  def currentMirror: universe.Mirror = macro ???
	  ...
	}
	```

	也可使用`runtimeMirror()`方法以`ClassLoader`爲參數手動構建Mirror實例：

	```scala
	trait JavaUniverse extends Universe { self =>
	  ...
	  def runtimeMirror(cl: ClassLoader): Mirror
	  ...
	}
	```

## 補充說明
反射API中一些細節的補充說明。

- 符號名稱

	Symbol類型的成員方法`Symbol.name`返回類型爲`NameType`。

	NameType不要直接與文本比較，應使用`toString`方法轉換爲文本進行比較。
	或者將`NameType`與`TermName`類型進行比較。

- 方法重載

	類內方法的MethodSymbol對應的TermName與方法名稱相同，一個方法的多個重載TermName相同。

	對於無重載的方法，使用`Type.decl()/member()`根據名稱查找到的Symbol可直接使用`Symbol.asMethod`方法轉化爲MethodSymbol；
	對於擁有重載的方法，使用`Type.decl()/member()`方法根據名稱查找獲取到的是包含重載信息的TermSymbol，
	該TermSymbol實例使用`Symbol.alternatives`方法可獲取包含所有同名重載方法信息的`List[MethodSymbol]`。
	通過分析每個MethodSymbol的信息選取正確的重載。

- 構造器

	獲取構造器的MethodSymbol可以通過ClassSymbol提供的`ClassSymbol.primaryConstructor`方法獲取主構造器的Symbol，
	使用`Symbol.asMethod`轉換爲MethodSymbol。

	在Java字節碼中，構造器的方法名稱爲`<init>`，還可使用`Type.decl()/member()`根據構造器名稱查找對應Symbol，
	使用`Symbol.asMethod`轉換爲MethodSymbol。

	對於存在多個構造器的類，若需獲取主構造器以外的構造器，僅通過構造器名稱查找的方式，同時還需要處理方法重載問題。

- 類型

	獲取類型Symbol最簡單的方式是使用`symbolOf[T]`方法，但symbolOf方法需要目標類型的結構做爲泛型參數；
	獲取當前環境下的`scala.reflect.api.Mirror`實例，使用`Mirror.staticClass()`通過類型的完整名稱獲取類型的ClassSymbol。

反射相關API使用示例：

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

  /*
    獲取反射所需的 Mirror 實例，也可以使用 runtimeMirror() 方法自行構建：
    runtimeMirror(getClass.getClassLoader)
  */
  val runtime = scala.reflect.runtime.currentMirror

  /*
    使用 Mirror.staticClass() 方法通過類型完整名稱獲取 ClassSymbol ，
    也可以直接使用 symbolOf 方法獲取：
    symbolOf[TestReflect].asClass
  */
  val classSymbol = runtime.staticClass("Main$TestReflect")

  /*
    構造器名稱爲 <init>，也通過可以查找 TremName 的方式從 Type 類型中獲取：
    typeOf[TestReflect].decl(TermName("<init>")).asMethod
  */
  val constructor = classSymbol.primaryConstructor.asMethod //獲取類型主構造器的MethodSymbol
  val instance = runtime //通過構造器的MethodSymbol反射構建實例
    .reflectClass(classSymbol)
    .reflectConstructor(constructor).apply(2333)

  // 遍歷篩選特定成員
  typeOf[TestReflect].decls foreach {
    case term: TermSymbol if term.name == TermName("field") =>
      println(s"Field name: ${term.name}, value: ${runtime.reflect(instance).reflectField(term).get}")
    case method: MethodSymbol if method.name == TermName("showField") =>
      println(s"Method name: ${method.name}, value: ${runtime.reflect(instance).reflectMethod(method).apply()}")
    case _ =>
  }

}
```

輸出結果：

```
Field name: field, value: 2333
Call method 'showField'
Method name: showField, value: 2333
```



# Annotation (註解)
Scala中的註解語法與Java中類似。
標準庫定義的註解相關內容在包`scala.annotation`中。

註解的基本語法爲：

```scala
@註解名稱(註解參數...)
```

與Java註解的用法類似，註解參數不是必須的，一個元素允許擁有多個註解。

## 自定義註解
`Scala 2.10`之前，Scala並未提供自定義註解功能，自定義註解需要在Java源碼中進行。
`Scala 2.10`開始，作爲`Reflect`功能的一部分，Scala提供了自定義註解支持。

與反射相關功能類似，到目前版本(`Scala 2.12`)爲止，註解相關功能依然是`Expermental`(**實驗性**)的，
註解相關API一直處於變化中。

Scala中的自定義註解不是**接口/特質**，而是**類**。
自定義註解需要從註解特質中繼承，Scala中提供了兩類註解特質：

- `scala.annotation.ClassfileAnnotation` 由Java編譯器生成註解
- `scala.annotation.StaticAnnotation` 由Scala編譯器生成註解

兩類註解特質都繼承自基類`scala.annotation.Annotation`。
定義註解類語法與普通類相同：

```scala
// 標記註解
class 註解名稱 extends StaticAnnotation/ClassfileAnnotation

// 有參註解
class 註解名稱(參數表...) extends StaticAnnotation/ClassfileAnnotation
```

兩類註解特質的基類相同，因此自定義註解類時**允許**同時混入兩類註解特質。
繼承自`ClassfileAnnotation`基類的註解在使用時參數應以`具名參數(named arguments)`形式傳入。
繼承自`StaticAnnotation`基類的註解無此限制。
示例：

```scala
import scala.annotation.{ClassfileAnnotation, StaticAnnotation}

class CustomStaticAnnotation(name: String) extends StaticAnnotation
class CustomClassfileAnnotation(name: String) extends ClassfileAnnotation

@CustomStaticAnnotation("2333") //正確
@CustomClassfileAnnotation("2333") //錯誤，Java註解需要以具名參數形式進行傳入
@CustomClassfileAnnotation(name = "2333") //正確
class Test
```

## 解析註解
通過反射機制獲取註解信息，相關API位於`scala.reflect.runtime.universe`包路徑下。

獲取註解：

- 獲取類的註解：

	1. 使用`typeOf()`方法，獲取`Type`類型的類信息。
	1. 通過`Type.typeSymbol`獲取`Symbol`。
	1. 通過`Symbol.annotations`獲取`List[Annotation]`(註解列表)。

- 獲取方法/成員字段的註解：

	1. 使用`typeOf()`方法，獲取`Type`類型的類信息。
	1. 通過`Type.decls/decl()`方法篩選出目標成員的`Symbol`。
	1. 通過`Symbol.annotations`獲取`List[Annotation]`(註解列表)。

- 獲取方法參數的註解：

	1. 使用`typeOf()`方法，獲取`Type`類型的類信息。
	1. 通過`Type.decls/decl()`方法篩選出目標方法的`MethodSymbol`。
	1. 通過`MethodSymbol.paramLists`方法獲取目標方法的參數表(`List[List[Symbol]]`類型，方法柯里化可能會有多個參數表)。
	1. 通過`Symbol.annotations`獲取`List[Annotation]`(註解列表)。

Scala註解類型爲`scala.reflect.runtime.universe.Annotation`。
在`Scala 2.11`之前，`Annotation`類型提供了`scalaArgs/javaArgs`等無參方法用於獲取註解信息，
但在`Scala 2.11`版本中，這些方法已被標記爲`deprecated`；
應使用`Annotation.tree`方法獲取註解語法樹，類型爲`scala.reflect.runtime.universe.Tree`。

示例：

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
    // 獲取類型註解
    val tpe: Type = typeOf[Test]
    val symbol: Symbol = tpe.typeSymbol //獲取類型符號信息
    val annotation: Annotation = symbol.annotations.head
    val tree: Tree = annotation.tree //獲取語法樹

    // 解析註解語法樹...
  }

  {
    // 獲取成員字段註解
    val tpe: Type = typeOf[Test]
    val symbol: Symbol = tpe.decl(TermName("ff ")) //獲取字段符號信息
    val annotation: Annotation = symbol.annotations.head
    val tree: Tree = annotation.tree

    // 解析註解語法樹...
  }

}
```

通過`scala.reflect.api.Printer.showRaw()`方法可以獲取語法樹的文本。
註解語法樹中包含了註解參數信息，可以通過模式匹配提取。

示例：

```scala
import scala.annotation.StaticAnnotation
import scala.reflect.runtime.universe._

class CustomAnnotation(name: String, num: Int) extends StaticAnnotation

@CustomAnnotation("Annotation for Class", 2333)
class Test

object Main extends App {

  // 獲取類型註解
  val tpe: Type = typeOf[Test]
  val symbol: Symbol = tpe.typeSymbol //獲取類型符號信息
  val annotation: Annotation = symbol.annotations.head
  val tree: Tree = annotation.tree //獲取語法樹

  println(showRaw(tree)) //打印語法樹
  val Apply(_, Literal(Constant(name: String)) :: Literal(Constant(num: Int)) :: Nil) = tree
  println(s"Annotation args: name -> $name, num -> $num")

}
```

輸出結果：(`Scala 2.12.2 && macOS 10.12.5`)

```
Apply(Select(New(TypeTree()), termNames.CONSTRUCTOR), List(Literal(Constant("Annotation for Class")), Literal(Constant(2333))))
Annotation args: name -> Annotation for Class, num -> 2333
```

注意事項：

- 解析註解參數需要基於語法樹結構，不要使用**參數默認值**特性，使用默認參數的註解生成的語法樹不包含註解信息的默認值。
- 類內字段會有多個`TermSymbol`，對應不同的`TermName`，包含註解信息的`TermName`爲`字段名稱 + 空格`。
- 樣例類的構造器參數作爲類的成員存在，但若在參數上添加註解，註解信息並未附加在字段信息中。
	提取樣例類構造器成員的註解信息需要以獲取方法參數註解的方式進行，查找構造器方法(`TermName("<init>")`)，獲取參數成員(`Method.paramLists`)。
- 使用`Annotation.tree`方法獲取註解語法樹(`Tree`類型)，再使用`Tree.tpe`方法獲取註解語法樹類型信息(`Type`類型)，與直接使用`typeOf[註解類型]`獲取的註解類型信息相同，可以用於比較篩選註解類型。

完整的註解解析實例：

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

  // 獲取指定類型的註解信息，通過 Annotation.tree.tpe 獲取註解的 Type 類型，以此進行篩選
  def getClassAnnotation[T: TypeTag, U: TypeTag] =
    symbolOf[T].annotations.find(_.tree.tpe =:= typeOf[U])

  // 通過字段名稱獲取指定類型的註解信息，注意查找字段名稱時添加空格
  def getMemberAnnotation[T: TypeTag, U: TypeTag](memberName: String) =
    typeOf[T].decl(TermName(s"$memberName ")).annotations.find(_.tree.tpe =:= typeOf[U])

  // 通過方法名稱和參數名稱獲取指定類型的註解信息
  def getArgAnnotation[T: TypeTag, U: TypeTag](methodName: String, argName: String) =
    typeOf[T].decl(TermName(methodName)).asMethod.paramLists.collect {
      case symbols => symbols.find(_.name == TermName(argName))
    }.headOption.fold(Option[Annotation](null))(_.get.annotations.find(_.tree.tpe =:= typeOf[U]))

  // 解析語法樹，獲取註解數據
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

輸出結果：(`Scala 2.12.2 && macOS 10.12.5`)

```
Annotation args: name -> Annotation for Class, num -> 2333
Annotation args: name -> Annotation for Member, num -> 6666
Annotation args: name -> Annotation for Arg, num -> 9999
```
