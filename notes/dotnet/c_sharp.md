<!-- TOC -->

- [入口函數](#入口函數)
- [數據類型](#數據類型)
	- [Value Type (值類型)](#value-type-值類型)
	- [Reference Type (引用類型)](#reference-type-引用類型)
	- [struct (結構類型)](#struct-結構類型)
	- [可空類型與 ?、?? 操作符](#可空類型與--操作符)
	- [Type alias (類型別名)](#type-alias-類型別名)
- [字符轉換](#字符轉換)
	- [byte[] 與 string 轉換](#byte-與-string-轉換)
- [Property (屬性)](#property-屬性)
	- [自動成員屬性](#自動成員屬性)
	- [成員屬性初始化](#成員屬性初始化)
	- [屬性表達式](#屬性表達式)
- [static 關鍵字](#static-關鍵字)
	- [靜態方法](#靜態方法)
	- [靜態字段](#靜態字段)
	- [靜態構造函數](#靜態構造函數)
	- [靜態類](#靜態類)
- [Extension Methods (擴展方法)](#extension-methods-擴展方法)
	- [在 Scala 中模擬擴展方法](#在-scala-中模擬擴展方法)
	- [擴展方法的應用場景](#擴展方法的應用場景)
- [Generic (泛型)](#generic-泛型)
	- [泛型約束](#泛型約束)
	- [Variance (型變/變性)](#variance-型變變性)
	- [泛型類的靜態成員](#泛型類的靜態成員)
- [delegate (委託) 和 event (事件)](#delegate-委託-和-event-事件)
	- [delegate (委託)](#delegate-委託)
	- [event (事件)](#event-事件)
	- [自定義添加/刪除操作的事件](#自定義添加刪除操作的事件)
- [Lambda](#lambda)
	- [實現委託](#實現委託)
	- [函數對象](#函數對象)
	- [變量捕獲](#變量捕獲)
	- [定義成員函數](#定義成員函數)
- [Pattern Matching (模式匹配)](#pattern-matching-模式匹配)
	- [is 表達式](#is-表達式)
	- [switch 模式匹配](#switch-模式匹配)
- [併發編程](#併發編程)
	- [Thread](#thread)
	- [Async Delegate (異步委託)](#async-delegate-異步委託)
	- [Task](#task)
	- [async/await 關鍵字](#asyncawait-關鍵字)
	- [lock 關鍵字](#lock-關鍵字)
- [Reflection (反射)](#reflection-反射)
	- [反射機制的相關類型](#反射機制的相關類型)
	- [Type/TypeInfo 類型](#typetypeinfo-類型)
	- [反射獲取成員信息](#反射獲取成員信息)
- [Attribute (特性)](#attribute-特性)
	- [使用特性](#使用特性)
	- [自定義特性](#自定義特性)
- [動態代理](#動態代理)
- [FTP](#ftp)
	- [創建 FTP 請求](#創建-ftp-請求)
	- [下載](#下載)
	- [上傳](#上傳)
- [WinForm 開發註記](#winform-開發註記)
	- [常見控件類型](#常見控件類型)
	- [容器控件](#容器控件)
	- [佈局與樣式](#佈局與樣式)
	- [控件事件](#控件事件)
	- [接收Windows消息](#接收windows消息)
- [調用 C/C++ 動態鏈接庫](#調用-cc-動態鏈接庫)
- [特殊關鍵字](#特殊關鍵字)
	- [internal 關鍵字](#internal-關鍵字)
	- [readonly 關鍵字](#readonly-關鍵字)
	- [partial 關鍵字](#partial-關鍵字)
	- [params 關鍵字](#params-關鍵字)
- [常見問題](#常見問題)
	- [處理`\0`結尾字符串](#處理\0結尾字符串)
	- [MySQL 中 TINYINT 類型](#mysql-中-tinyint-類型)
	- [DEBUG 宏](#debug-宏)
	- [輸出代碼文件名、行號](#輸出代碼文件名行號)

<!-- /TOC -->



# 入口函數
`C#`中允許以下4種形式的入口函數：

```cs
static void Main();
static void Main(string[] args);
static int Main();
static int Main(string[] args);
```

`C#`允許多種入口函數形式，一般採用第二種(默認)。

與`Java`不同，`C#`並不強制要求主類的類名與主類所在文件的文件名相同。
實際上，`C#`由於支持`部分類`特性，也不可能要求類名與源碼文件名相同。



# 數據類型
C#的數據類型分爲兩類：值類型和引用類型。
一般而言，值類型用於**存儲數據**，引用類型用於**定義行爲**。

## Value Type (值類型)
值類型具體包括**預定義值類型**、**自定義值類型**和**枚舉類型**。
所有值類型隱式派生於`System.ValueType`類。

例如，系統預定義的值類型`int`是`System`命名空間中`System.Int32`結構體的別名。
`System.Int32`結構的定義爲：

```cs
public struct Int32 : IComparable, IFormattable, IConvertible, IComparable<int>, IEquatable<int>
{
	...
}
```

其它的預定義值類型也是類似的`結構類型(Struct)`的別名：

| 別名 | 實際類型 |
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
| decimal | System.Decimal(一般用於財務計算) |
| bool | System.Boolean |
| enum | System.Enum(枚舉類型) |

用戶定義的結構體，從`System.ValueType`類中繼承：

```cs
public abstract class ValueType {};
```

值類型實例通常分配在線程的**棧(stack)**上，並且不包含任何指向實例數據的指針，因爲變量本身就包含了其實例數據。
值類型在複製時是**值傳遞(pass by value)**，會複製當前值類型變量包含的內容。

## Reference Type (引用類型)
引用類型包括：

- 數組(派生於`System.Array`)
- 字符串`string`(`System.String`類的別名)
- 自定義類(派生於`System.Object`)
- 委託類型(派生於`System.Delegate`)
- `object`類型(`System.Object`)的別名

引用類型與值類型比較：

- 值類型和引用類型都可以**實現接口**，但值類型**不能**再派生出新的子類型。
- 引用類型可以爲`null`，但值類型不行(除了**可空類型**)。
- 引用類型複製是傳遞引用，值類型複製是拷貝整個對象。
- 值類型分配內存在線程棧上，出棧自動釋放；引用類型分配內存在託管堆上，由`GC`負責內存回收。

## struct (結構類型)
與`C++`完全不同，`C#`中的`結構體`與`類`有**很大區別**：

- C#中的結構體爲**值類型**，在**棧(stack)**中分配內存，而引用類型則僅在棧中保存**引用(reference)**，類型實體內存分配在**堆(heap)**中。
- 由於結構體爲值類型，複製結構體時是完全複製出一個新的結構體實例，而非引用類型的引用傳遞。
- C#中結構體的默認訪問權限是`private`，且結構體成員變量**不能**直接賦初值(需要通過有參構造函數賦初值)。
- C#中結構類型全部繼承自`System.ValueType`類，但結構體是隱式**密封(sealed)**的，**不能**被繼承。
- C#中結構體可以用來實現接口。用來實現接口的結構體雖然本身爲值類型，但如果發生**向上轉型**重新變爲父類接口對象則值類型的特性也將隨之消失。
- C#中結構體不能被繼承，因而結構體定義時不能使用`sealed`和`abstract`關鍵字，結構體成員定義時也不能使用`protected`和`internal`等關鍵字。
- C#中結構體帶有默認的無參構造函數，且該默認構造函數一直存在(無論你是否創建了有參構造函數)，默認的無參構造函數**不能**被自定義(改寫)。
- 創建有參構造函數時，必須在該構造函數中初始化所有的成員變量，否則無法通過編譯。
- 創建結構體時可以不使用`new`操作符，不使用`new`操作符創建的結構體對象中的結構體成員全部處於未初始化狀態，需要經過初始化操作(手動訪問賦值)之後方可使用。
- 如果需要使用結構體提供的有參構造函數，則必須使用`new`操作符進行對象創建，語法類似於`class`。
- 在C#中結構體成員可以使用`static`修飾，結構體也可以創建靜態構造函數。
- 在C#中結構體中可以正常使用泛型。

## 可空類型與 ?、?? 操作符
在`C#`中，值類型不能爲`null`，對值類型賦值`null`會得到錯誤，如下所示：

```cs
int num = null; //錯誤信息："Cannot convert null to 'int' because it is a non-nullable value type"
```

在傳統的值類型後添加`?`符號，即成爲對應的**可空類型**。
可空類型的實際類型爲`System.Nullable<T>`結構體：

```cs
public struct Nullable<T> where T : struct
{
	...
}
```

假設有值類型`T`，對應的可空類型聲明可以爲：

```cs
T? variable;
System.Nullable<T> variable;
```

可空類型提供以下**只讀屬性**用於檢查/獲取保存的實際值：

- `HasValue`屬性類型爲`bool`類型，當變量包含非`null`值時，返回`true`。
- `Value`屬性類型爲可空類型對應的值類型，當可空類型保存的值**不爲**`null`時，返回保存的值，否則拋出`InvalidOperationException`異常。

- `??`操作符

	`??`運算符用於在可空類型/引用類型值爲`null`時返回默認值，如下所示：

	```cs
	int? num0 = null;
	num0 ?? 1; //可空變量爲null時返回指定的默認值1
	int? num1 = 0;
	num1 ?? 1; //可空變量不爲null時返回保存的值0
	string str = null;
	str ?? "test" //??操作符同樣可以用在普通引用類型上
	```

- `?`操作符

	`?`操作符可用於在訪問引用類型/可空類型前對目標對象進行檢查，訪問的實例爲`null`則不執行操作。
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
			test?.Show(); //實例爲null，不調用方法
			int? num = test?.GetNum(); //返回可空類型，實例爲null時返回值爲null
			Console.WriteLine(num); //打印結果爲空(null)
			Console.WriteLine("Second Call:");
			test = new Test();
			test?.Show(); //實例不爲null，正常調用方法
			num = test?.GetNum();
			Console.WriteLine(num); //打印結果爲1
		}
	}
	```

	輸出結果：

	```
	First Call:

	Second Call:
	Called Show()
	1
	```

	使用`?`運算符的語句帶有可空類型/引用類型的返回值，當受檢對象未通過`null`檢查，後續語句不執行，同時整個語句返回`null`。
	利用此特性可搭配`??`運算符組合使用：

	```cs
	int? num = null;
	Console.WriteLine(num?.ToString() ?? "Empty"); //打印 "Empty"
	num = 2333;
	Console.WriteLine(num?.ToString() ?? "Empty"); //打印 "2333"
	```

	`?`運算符還可結合索引運算符`[]`使用：

	```cs
	int?[] nums = { null, 2333, null, 666 };

	Console.WriteLine(nums?[0]?.ToString() ?? "Error"); //打印 "Error"
	Console.WriteLine(nums?[1]?.ToString() ?? "Error"); //打印 "2333"
	```

## Type alias (類型別名)
C#中使用`using`關鍵字爲已有類型創建**別名**，基本用法與`C++11`中添加的新`using`語法相似。
如下所示：

```cs
namespace Np
{
	using Fvoid = Action; //普通類型別名
	using FInt = Func<int>; //泛型類型需要指定具體類型

	// C#不支持高階類型
	using FInInt<In> = Func<In, int>; //錯誤
	using Ft<R> = Func<R>; //錯誤
}
```

`C#`中的類型別名有較多**限制**：

- 不支持定義**高階類型**，`C++11`中的`using`支持此功能。
- 不能在命名空間之外的區域定義類型別名(全局區域、類體、函數體內皆不可定義別名)，`C++11`的`using`無此限制。



# 字符轉換
`System.Text.Encoding`抽象類定義了一系列的編碼轉換方法。

## byte[] 與 string 轉換
- 使用`string System.Text.Encoding.ASCII.GetString(byte[] bytes)`獲取byte數組的對應string字符串。
- 使用`byte[] System.Text.Encoding.ASCII.GetBytes(string s)`獲取string字符串對應的byte數組。



# Property (屬性)
`C#`類中成員有一種被稱爲`屬性`。

- 屬性的訪問方式與成員變量類似；通過定義`set`和`get`塊的內容，能夠通過屬性給成員變量賦值或是獲取成員變量的值。
- `set`和`get`可以分別設置**訪問權限**，不加關鍵字時訪問權限與所在的屬性相同。
- `set`塊中使用局部關鍵字`value`來代表給屬性的賦值。`get`塊必須返回一個與屬性類型相符的值。
- `set`塊和`get`塊**不是**必須同時存在的，只有`set/get`塊的屬性被稱爲`只讀/只寫屬性`。
- 屬性前允許使用`static`修飾，表示定義靜態屬性，與靜態變量類似。

如下代碼所示：

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

輸出結果：

```
0
100
```

對類`A`中屬性`Num`的賦值通過屬性的`set`塊中的局部關鍵字`value`傳給了`A`類私有成員`num`，通過`Num`屬性的`get`塊獲取了私有成員`num`的值。

## 自動成員屬性
在`C# 3.0`之後，可以使用**自動屬性**。
自動屬性只需直接使用`set`、`get`關鍵字，**不必**定義屬性相關的私有變量並編寫`set`、`get`塊代碼。
編譯器會爲自動屬性生成私有變量保存屬性的內容。

上述例子中成員屬性`Num`可以簡寫爲：

```cs
public int Num { get; set; }
```

同時，不用定義私有變量`num`來存儲屬性的內容，編譯器會自動生成一個變量。

## 成員屬性初始化
在`C# 6.0`中，開始支持對自動成員屬性進行**類內初始化**，可以直接在類中對自動成員屬性**賦初值**：

```cs
public int Num { get; set; } = 0;
```

該特性也同樣支持**只讀屬性**：

```cs
public int Num { get; } = 0;
```

## 屬性表達式
在`C# 6.0`中，對於**只讀屬性**，可以使用簡化的語法進行定義。
有如下只讀屬性：

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

在`C# 6.0`中可以使用基於表達式的簡化語法：

```cs
private int num = 0;
public int Num => num;
```

在`C# 7.0`中，對於普通屬性也提供了表達式語法。
有如下屬性：

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

在`C# 7.0`中可以使用簡化語法：

```cs
private int num = 0;
public int Num
{
	get => num;
	set => num = value;
}
```



# static 關鍵字
在`C#`中，`static`關鍵字用於定義**靜態類**、**靜態方法**、**靜態屬性**、**靜態字段**。

## 靜態方法
靜態方法與實例無關，只能直接通過類名進行訪問：

- 在傳統的`OOP`語言如`C++`、`Java`中，並不限制通過實例訪問靜態方法，作用與通過類名訪問靜態方法相同。
- 在`C#`中，**不允許**通過實例訪問靜態方法，調用靜態方法只能通過**類名**。

通過實例訪問靜態方法會在編譯時得到錯誤：

```
error CS0176: Member 'xxx.xxx()' cannot be accessed with an instance reference; qualify it with a type name instead`
```

## 靜態字段
靜態字段的概念與其它傳統`OOP`語言如`C++`、`Java`類似，一個類的靜態字段全局唯一。
與靜態方法類似，使用實例訪問靜態字段會在編譯時報錯，在`C#`中，只能通過類名訪問靜態字段。

- 字段初始化

	在`C#`中，成員字段初始化時不能引用非靜態成員。
	如下代碼所示：

	```cs
	class Test
	{
		int num = 0;
		int num1 = num; //編譯報錯
	}
	```

	在`Java`、`C++`、`Scala`中，則允許成員字段初始化時引用其它字段。

- 靜態字段初始化

	在`C#`中，靜態字段初始化時能夠引用其它靜態成員，但需要注意成員定義的**先後順序**。
	若引用的靜態字段定義在當前靜態字段之後，則當前靜態不會被初始化。
	如下所示：

	```cs
	class Test
	{
		static int num = num1; //字段num1定義在num之後，num不會被初始化，值爲0(默認值)
		static int num1 = 100;
	}
	```

## 靜態構造函數
靜態構造函數是`C#`中特有的概念，用於在類首次被使用前進行靜態成員的初始化。

- 靜態構造函數與普通構造函數一樣在類中定義。
- 靜態構造函數不能帶有參數和訪問權限。
- 一個類/結構體只能定義一個靜態構造函數。
- 靜態構造函數與類的無參構造函數雖然參數表相同，但不會衝突。
- 靜態構造函數只能初始化靜態成員，若類中有靜態成員賦了初值(類內初始化)，則.NET會自動爲其創建默認的靜態構造函數。
- 靜態構造函數不需要手動調用，在首次使用創建類實例或是方位類的靜態成員時會由.NET自動調用，靜態構造函數在全局只會被**調用一次**。

## 靜態類
在`C#`中，類定義前可以使用`static`關鍵字表示定義一個**靜態類**。

- 靜態類只能包含靜態成員，且是密封(`sealed`)的，不能被實例化和繼承。
- 靜態類不能從普通類中派生，而靜態類本身不可被繼承，因而實際上所有靜態類都從`object`中派生。
- 靜態類不能定義普通構造函數，但能夠定義靜態構造函數。
- 靜態類在首次被引用前加載，初始化其成員字段並調用該類的靜態構造函數。
- 一個類的靜態構造函數僅被調用一次，在程序駐留的應用程序域的生存期內，靜態類一直保留在內存中。
- 擴展方法只能定義在靜態類中。
- `const`常量自帶靜態特性，可以定義在靜態類中。



# Extension Methods (擴展方法)
擴展方法能夠在不改變現有類結構的前提下，向已存在的類型添加方法，並讓這些方法像普通成員方法一樣地被調用。

- 擴展方法本質上是一種特殊的**靜態方法**，且必須定義在**靜態類**中。
- 擴展方法被定義爲靜態方法，但調用時的語法與實例方法相同。
- 擴展方法的第一個參數必須帶有`this`關鍵字，且類型必須是需要被擴展的類型(即第一個參數接收被擴展類型的實例)。
- 擴展方法本質上是一個語法糖，並不是真正向已有的類中添加了成員方法，因此擴展方法無法訪問被擴展類的**私有成員**。
- 擴展方法在編譯成**IL**中間代碼時會被轉換爲對靜態方法的調用。

如下代碼所示：

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
		//實際等價於 Console.WriteLine(ExtensionMethod.IsNull(obj));
	}
}
```

輸出結果：

```
True
```

## 在 Scala 中模擬擴展方法
在`Scala`中，可以利用**隱式類**特性來獲得與C#中擴展方法類似的效果。

上述例子在`Scala`中可以寫成：

```scala
object Test extends App {

  implicit class ExtensionMethod(obj: Any) {
    def isNull = if (obj == null) true else false
  }

  val obj: Any = null
  println(obj.isNull)

}
```

輸出結果：

```
true
```

## 擴展方法的應用場景
擴展方法主要用於向一些不方便改動的類型添加額外的方法，並讓添加的方法能夠以常規語法調用。

在`C#`標準庫中，典型的擴展案例爲`System.Linq.Enumerable`類。
該類爲`System.Collections.Generic.IEnumerable<T>`類型添加了大量`LINQ`風格的擴展方法定義。

使用擴展方法時需要節制，濫用擴展方法會造成代碼難以理解。



# Generic (泛型)
值類型轉變爲引用類型會經過`裝箱(boxing)`操作，而引用類型轉變爲值類型則要經過`拆箱(unboxing)`操作。

一個容器需要接收多種類型時，可能就需要將接受參數的類型設置爲`object`型(即所有類型的父類)。
值類型在轉化到`object`型時就需要進行裝箱操作，頻繁地裝箱與拆箱會有較高的開銷。
`object`類型並不安全(可能同時接收到不同的類型)，因而可以使用**泛型**來**顯式指定**需要接收的類型(編譯器會檢查接收類型是否符合指定泛型)。
對於值類型而言，使用泛型還可以避免重複的裝箱與拆箱操作。

## 泛型約束
C#中泛型可以使用`where`關鍵字進行泛型約束，例如：

```cs
class A<T> where T : XXX
{
	S Get<S>() where S : XXXX { }
}
```

擁有多個泛型參數時，使用多個`where`語句限制多個泛型參數：

```cs
// 泛型參數T必須從XXX類型派生，泛型參數V必須從XXXX類型派生
class B<T, V> where T : XXX where V : XXXX { }
```

在C#中，泛型約束支持以下形式：

- `T : struct` 限制類型參數爲結構類型，存在多個泛型約束條件時，該條件需要置於首位
- `T : class` 限制類型參數爲引用類型，存在多個泛型約束條件時，該條件需要置於首位
- `T : new()` 類型參數必須具有可訪問的無參構造函數，存在多個泛型約束條件時，該條件需要置於末尾
- `T : 接口名稱` 類型參數必須實現了指定接口
- `T : 類名稱` 類型參數必須爲指定類型或其子類
- `T : V` 類型參數`T`必須爲類型參數`V`的派生類型(裸類型約束)

一個泛型參數可以使用多個條件進行約束，例如：

```cs
// 泛型參數T必須爲引用類型，同時從類型V派生
class C<T, V> where T : class, T : V { }
```

## Variance (型變/變性)
泛型類型在使用不同類型參數時默認**不存在**繼承關係。
如下所示：

```cs
csharp> class Child : Base { };
csharp> List<Base> list = new List<Child>(); //泛型參數的繼承關係無法作用於範型自身
(1,20): error CS0029: Cannot implicitly convert type `System.Collections.Generic.List<Child>' to `System.Collections.Generic.List<Base>'
csharp> List<Base> list = new List<Child>() as List<Base>; //不可進行強制類型轉換
(1,38): error CS0039: Cannot convert type `System.Collections.Generic.List<Child>' to `System.Collections.Generic.List<Base>' via a built-in conversion
```

使用variances特性可使類型參數的繼承關係擴展到承載類型參數的泛型類型自身。
variances特性分爲`covariance`(協變)和`contravariance`(逆變)。
在泛型參數前使用`int/out`關鍵字表示該泛型參數**變性**，如下所示：

```cs
csharp> interface ICovariance<in T> {}; //逆變
csharp> interface IContravariance<out T> {}; //協變
```

與`Scala`、`Kotlin`不同，在C#中，`variances`僅支持`interface`和`delegate`。
`class`和`struct`無法使用`variances`特性，如下所示：

```cs
csharp> class Test<out T> {};
(1,17): error CS1960: Variant type parameters can only be used with interfaces and delegates
csharp> struct Test<in T> {};
(1,17): error CS1960: Variant type parameters can only be used with interfaces and delegates
```

- `Covariance` (協變)

	類型參數聲明爲`covariance`(協變)時，泛型類型的繼承關係與類型參數相同。
	如下所示：

	```cs
	csharp> interface ICovariance<out T> {};
	csharp> class Covariance<T> : ICovariance<T> {};
	csharp> ICovariance<Base> covariance = new Covariance<Child>(); //協變
	```

- `Contravariance` (逆變)

	類型參數聲明爲`contravariance`(逆變)時，泛型類型的繼承關係與類型參數相反。
	如下所示：

	```cs
	csharp> interface IContravariance<in T> {};
	csharp> class Contravariance<T> : IContravariance<T> {};
	csharp> IContravariance<Child> contravariance = new Contravariance<Base>(); //逆變
	```

## 泛型類的靜態成員
不同於Java中`Type Erasure`形式的泛型實現，`.Net`中採用類似C++的實現，同一泛型類使用不同泛型參數時會獨立生成代碼。
C#中，同一泛型類使用不同類型參數時，各自的靜態成員是相互獨立的。
靜態成員共享僅在使用相同類型參數的泛型類之間。

如下代碼所示：

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
		Test<uint>.a = 200; //兩個a並不是同一個
		Console.WriteLine(Test<int>.a);
	}
}
```

輸出結果：

```
100
```



# delegate (委託) 和 event (事件)
**委託**讓C#擁有了函數對象的概念，使一個方法可以作爲參數被傳遞。
**事件**讓C#擁有了語言級別的消息通信機制。

## delegate (委託)
委託是C#特有的概念，委託的作用類似於C/C++中的函數指針，但委託是類型安全的。

在`C#`中，委託實際上是一個類，因而使用方式與`class`類似。
委託支持加減運算符操作，一個委託實例能夠通過加法運算綁定多個**簽名相同**的函數。

定義委託：

```cs
delegate 返回值類型 委託名(參數表);
```

委託的定義可以在全局、命名空間或是作爲某個類的成員，但委託的定義不能放在方法體內部。

委託前可以使用訪問權限關鍵字(`public`、`private`、`protected`等)進行限制，但委託定義不能使用`static`關鍵字(委託實例作爲一個**類的成員**存在時纔可以使用`static`關鍵字)。
委託可以綁定`static`或是非`static`成員函數，委託同樣可以綁定當前類之外的符合簽名要求的其它類的可見成員函數(`public`、`internal`成員)。

`delegate`關鍵字還可以用來定義**匿名函數**，實例化委託或是增加委託實例綁定時都可以使用委託匿名函數。

委託實例化：

```cs
委託名 委託實例名; //與事件相同，委託也可以只定義不初始化
委託名 委託實例名 = new 委託名(符合委託簽名的函數名);
委託名 委託實例名 = 符合委託簽名的當前類成員函數名; //可以省略使用構造函數
委託名 委託實例名 = 類實例/類名.符合委託簽名的公有非static/static成員函數名; //委託同樣可以綁定到其他類的可見成員函數
委託名 委託實例名 = delegate(符合委託簽名的參數表) //匿名委託
{
	函數內容;
};
```

增加/刪除委託綁定函數：

```cs
委託實例名 += 符合委託簽名的函數名;
委託實例名 -= 已綁定到委託的函數名;
委託實例名 += delegate(符合委託簽名的參數表)
{
	函數內容;
};
```

一個委託可以同加減運算符動態地更改綁定的函數個數。
委託在使用時類似一個普通的函數，調用委託：

```cs
委託實例名(符合委託簽名的參數表);
```

調用委託會把委託綁定的所有函數按照綁定的先後次序**依次執行**。
若綁定的方法擁有返回值，則將**最後一個**綁定方法的返回值作爲整個委託實例的返回值。
委託類型作爲函數的形參時，傳入實參時可以直接使用符合委託簽名的函數名，無需手動使用`new`操作符構建委託對象。

## event (事件)
事件是委託的擴展概念，事件本質上是一類特殊的委託實例(不是委託類型)，創建事件前需要先定義一個委託，然後才能將事件與委託綁定。

定義事件：

```cs
event 委託名 事件名;
event 委託名 事件名 = new 委託名(符合委託簽名的函數名); //事件也可以在定義時就初始化
event 委託名 事件名 = 符合委託函數簽名的函數名; //可以省略使用構造函數
event 委託名 事件名 = delegate(符合委託簽名的參數表) //匿名委託
{
	函數內容;
};
```

給事件添加/刪除處理函數：

```cs
事件名 += 符合委託簽名的函數名;
事件名 -= 已綁定到事件的函數名;
事件名 += delegate(符合委託簽名的參數表)
{
	函數內容;
};
```

觸發事件：

```cs
事件名(符合委託簽名的參數表);
```

事件是一種特殊的**委託實例**：

- 與委託不同，不能在全局區域和命名空間中定義事件，只能將事件作爲某個類的成員來進行定義。
- 事件與普通的成員類似，受到類的訪問權限控制。
- 事件的訪問權限不能高於用於定義事件的委託。
- 調用事件與調用委託實例的方式完全相同。

事件機制是其他`C#`高級技術的基礎。

實例代碼：

```cs
using System;

delegate void Delegate(string str); // 委託可以定義在全局區域或是命名空間

class Program
{
	static event Delegate Event; // 定義事件

	static void Main(string[] args)
	{
		Event += str => Console.WriteLine(str); // 爲事件綁定方法
		Event("Test Event!"); // 觸發事件
	}
}
```

輸出結果：

```
Test Event!
```

## 自定義添加/刪除操作的事件
在定義事件時，可以選擇自行實現事件的`+=`、`-=`操作符，語法類似**屬性**：

- 使用`add`、`remove`關鍵字標誌代碼塊來對應`+=`、`-=`操作符的行爲。
- 與**屬性**定義中的`set`代碼塊類似，事件定義中的`add`、`remove`代碼塊中包含**隱含參數**`value`，
`value`代表操作符的參數，即符合事件委託簽名的方法。
- `add`、`remove`代碼塊不包含其它參數，同時代碼塊也沒有返回值(返回`void`)。

示例：

```cs
using System;

delegate void Delegate(string str);

class Program
{
	static event Delegate Event //定義事件
	{
		add //對應事件的"+="操作符
		{
			XXXX += value //隱含參數value表示傳入的方法
			//do something...
		}
		remove //對應事件的"-="操作符
		{
			XXXX -= value
			//do something...
		}
	}
}
```

自定義`+=`、`-=`運算符行爲的事件**不能**像普通事件那樣直接以函數的語法調用，調用時編譯器會報錯：

```
error CS0079: The event XXX can only appear on the left hand side of += or -= operator
```

自定義運算符事件的真正用途是爲其它事件提供**包裝**，示例：

```cs
using System;

delegate void Delegate(string str); //委託可以定義在全局區域或是命名空間

class Program
{
	private static Delegate _event; //真正用於綁定方法的事件

	// 自定義事件，在添加、移除方法時在終端輸出信息
	static event Delegate Event
	{
		add //對應事件的"+="操作符
		{
			Console.WriteLine("Add Method!"); //在終端打印"Add Method!"
			_event += value; //將傳入的方法綁定到_event上
		}
		remove //對應事件的"-="操作符
		{
			Console.WriteLine("Remove Method!"); //在終端打印"Remove Method!"
			_event -= value; //將傳入的方法與_event解綁
		}
	}

	static void Main(string[] args)
	{
		Delegate del = str => Console.WriteLine(str);

		Event += del; //事件綁定委託

		//Event("Test Event!"); //使用Event()觸發事件會在編譯時報錯
		_event("Test Event!"); //觸發事件還是需要使用真正被包裝的事件

		Event -= del; //事件與委託解綁
	}
}
```

輸出結果：

```
Add Method!
Test Event!
Remove Method!
```



# Lambda
在`C#3.0`之後，引入了`Lambda表達式`的概念，基本語法：

```cs
() => 單一表達式;
(參數表) => 單一表達式;
單個參數 => 單一表達式;
(參數表) => { 多行表達式; };
```

- 當參數表中只有一個參數時，參數表外的括號可以省略，但有多個參數或是無參數時括號不可省略。
- 參數表中可以不顯式指定參數類型，在表達式只有一條語句時，該語句如有返回值，則被作爲整個`Lambda`的返回值。
- 如果表達式有多條語句(使用花括號)時，需要顯式使用`return`關鍵字指定返回值。
- 參數表可以不指定參數類型交由編譯器隱式推導，也可以顯式指定參數類型，顯式指定與隱式指定不可混用，
一旦有參數使用了顯式指定或隱式指定，其餘的參數必須使用相同的指定方式。

## 實現委託
在C#中，`Lambda`概念與委託相通，可以使用`Lambda`以更簡潔的方式代替匿名委託實現委託實例。
示例：

```cs
delegate int GetDouble(double num1, double num2);

GetDouble getDouble1 = delegate(double num1, double num2) { return (int)(num1 + num2); };
GetDouble getDouble2 = (num1, num2) => (int)(num1 + num2);
GetDouble getDouble3 = (double num1, double num2) => { return (int)(num1 + num2); };		//三種形式效果完全相同
```

需要注意的是，使用`Lambda`代替匿名委託雖然能夠減少代碼量，但這並不代表`Lambda`能夠完全取代匿名委託。
`Lambda`中參數不能帶有關鍵字`ref`、`out`，如果需要使用**引用參數**則依然需要使用匿名委託。

## 函數對象
C#中定義了一系列類型用來表示委託和Lambda對象。

- 使用`Action`表示不帶參數且返回值爲`void`類型的`Lambda`，注意，不需要也**不能**畫蛇添足地寫成`Action<>`形式。
- 使用`Action<T1, T2...>`表示帶參數的`void`型返回值的`Lambda`。
- 使用`Func<T1, T2..., R>`表示返回值類型不爲空的`Lambda`(**最後一個**泛型參數爲函數返回值的類型)。
- `Action<>`、`Func<>`等泛型類型至多接收`8`個參數。
- `C#`中的`Lambda`**不能**直接加括號執行，而是需要創建一個函數對象或顯式指明類型才能執行(即不能直接`(() => {})();`來執行`Lambda`)。
- 與`Java`的**殘廢**`Lambda`不同，`C#`的`Lambda`可以捕獲並**修改**外部作用域變量，而`Java`中外部作用域變量在`Lambda`中帶有`final`屬性，只能讀取不能更改。

## 變量捕獲
在`C#`中，`Lambda`能夠訪問到在`Lambda`被定義的作用域中的所有成員。
如果`Lambda`表達式在類中被定義，則`Lambda`表達式能夠訪問到類的成員。
如同函數一樣，`Lambda`有自己的作用域，`Lambda`內部定義的變量在外部作用域**不可訪問**。

示例代碼-1：

```cs
using System;

class Test
{
	static int num = 100;
	static Action setNum200 = () => num = 200;

	static void SetNum(int newNum) {
		/*
			不能直接執行Lambda，需要創建函數對象或顯式類型轉換才能執行。
			另一種寫法： ((Action<int>)(n => num = n))(newNum);
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

輸出結果：(Mono 4.0.2 && ArchLinux x64)

```
100
200
500
```

## 定義成員函數
在`C# 6.0`中，開始支持使用Lambda語法直接定義**單行**的成員函數。
**示例代碼-1**使用新的語法可以使用如下格式書寫：

示例代碼-2：

```cs
using System;

class Test
{
	static int num = 100;
	static Action setNum200 = () => num = 200;

	static void SetNum(int newNum) =>
		new Action<int>(n => num = n)(newNum); //直接使用Lambda實現成員函數

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

在`C# 6.0`中，表達式語法以下限制：

- 不能應用於**構造方法**、**析構方法**和**屬性訪問器**。
- 單行表達式不能爲`throw`語句(不能在表達式中拋出異常)。

在`C# 7.0`中，表達式語法更加完善，在以上場景可以使用。



# Pattern Matching (模式匹配)
`C# 7.0`中加入了**模式匹配**特性，支持根據對象類型提供不同的行爲。
在`C# 7.0`中，支持模式匹配的新特性包括：

- `is`表達式。
- `switch`聲明更新。

## is 表達式
`is`表達式具有比較對象類型的功能，在早期版本的`C#`中，比較變量類型並進行轉換：

```cs
object obj = 100;

int num;
if (obj is int)
	num = (int)obj;
```

在`C# 7.0`中，可以在比較對象類型相同時直接創建變量：

```cs
object obj = 100;

int num;
if (obj is int i)
	num = i;
```

## switch 模式匹配
在`C# 7.0`中，`switch`表達式的`case`標籤中支持根據對象類型進行跳轉：

```cs
object xxx = ...;

switch (xxx)
{
	// 匹配 int 類型
	case int num:
		...
		break;
	// 匹配 double 類型
	case double num:
		...
		break;
	default:
		...
		break;
}
```

若不需要在匹配類型後使用變量，則可使用下劃線`_`代替變量名稱：

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

`case`標籤可以帶有`when`子句，用於添加額外的匹配條件，類似於`Scala`中的**守衛**語法：

```cs
object xxx = ...;

switch (xxx)
{
	// 匹配 int 類型，且需要匹配的數值大於100
	case int num when num > 100:
		...
		break;
	// 匹配 string 類型，且需要匹配的字符串長度大於5
	case string str when str.Length > 5:
		...
		break;
	default:
		...
		break;
}
```



# 併發編程
在`C#`中，除了常見的`Thread`類，主要的併發技術有**異步委託**、`Task`類、`async/await`等。

## Thread
與常規的**OOP**語言類似，C#中也可以使用`Thread`類來進行併發編程，`Thread`類完整路徑爲`System.Threading.Thread`。

- 創建與啓動線程

	`Thread`類擁有四種構造函數，可以分別以`ThreadStart`或`ParameterizedThreadStart`委託實例做爲參數構建一個線程對象。
	兩種委託的區別是前者不能帶有參數，後者帶有一個`Object`類型的參數，兩種委託返回值都爲`void`。
	`Thread`類在構造時還可以接收一個`int`型參數用於指定線程的最大堆棧大小。

	使用`Thread.Start()`方法可以啓動線程，如下代碼所示：

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

	運行結果：

	```
	This is thread!
	The arg is: test args.
	```

- 等待線程結束

	使用成員方法`Thread.Join()`能夠等待指定線程結束，在等待的線程結束前，該方法會一直阻塞**當前**線程。

- 獲取線程ID

	每個線程都有獨立的線程ID。
	`Thread.CurrentThread.ManagedThreadId`屬性保存了當前線程的ID，可以通過比較線程ID來判斷代碼是否在相同的線程執行。

## Async Delegate (異步委託)
委託實例執行操作默認**同步**執行，但委託實例同樣可以**異步**執行操作。

- 使用`BeginInvoke()`進行異步回調

	`BeginInvoke()`除了接收原有委託簽名的參數之外，參數表尾部額外帶有兩個參數，分別爲`AsyncCallback`委託類型和`object`類型：

	1. `AsyncCallback`委託在回調委託運行結束之後觸發，`AsyncCallback`委託接收一個`IAsyncResult`類型的參數。
	1. `object`類型用於傳遞一些參數給`AsyncCallback`委託。

	`BeginInvoke()`的最後兩個參數可以爲`null`。
	`BeginInvoke()`返回`IAsyncResult`類型：

	1. 使用`IAsyncResult.IsCompleted`屬性可以判斷回調委託的執行狀態。
	1. 使用`IAsyncResult.AsyncState`屬性獲取`BeginInvoke()`參數表中的最後一個`object`類型的傳入參數。

- 使用`EndInvoke()`等待異步委託返回

	若需等待異步執行的委託結束，可以使用`EndInvoke()`成員函數。

	- `EndInvoke()`接受一個`IAsyncResult`類型的參數(即`BeginInvoke()`的返回值)。
	- `EndInvoke()`的返回值即爲異步委託的返回值。
	- 在異步委託執行完畢之前，`EndInvoke()`會一直阻塞當前線程，直到異步委託結束。

	如下代碼所示：

	```cs
	using System;
	using System.Threading;

	delegate int Delegate();

	class Program
	{
		static void Main(string[] args)
		{
			//用於回調的委託
			Delegate del = () =>
			{
				Thread.Sleep(1000);
				Console.WriteLine("Thread is running!");
				return 100;
			};

			//使用BeginInvoke()進行異步委託回調
			IAsyncResult result = del.BeginInvoke(ar =>
			{
				//異步委託結束時執行該Lambda，打印傳入參數
				Console.WriteLine("The object arg is: {0}", (int) ar.AsyncState);
			}, 200);

			Console.WriteLine("Program start...");
			Console.WriteLine("The return value is: {0}", del.EndInvoke(result));

			//使用IAsyncResult.IsCompleted屬性判斷委託是否執行完畢
			Console.WriteLine("The thread status is: {0}", result.IsCompleted);
		}
	}
	```

	運行結果：

	```
	Program start...
	Thread is running!
	The return value is: 100
	The thread status is: True
	The object arg is: 200
	```

	委託實例`del`雖然先被調用，但由於是異步調用，`Sleep()`了1000毫秒之後再輸出的字符位於主線程之後。

- 使用`WaitOne()`等待異步委託返回

	`BeginInvoke()`的返回值`IAsyncResult`類型的`AsyncWaitHandle`屬性會返回一個`WaitHandle`類型的等待句柄：

	- `WaitHandle.WaitOne()`接受`int`型參數作爲超時時間，使用此方法可以實現等待指定時間(單位爲**毫秒**)的效果。
	- `WaitHandle.WaitOne()`的返回值爲`bool`類型，用於表示異步委託是否結束。

	示例：

	```cs
	using System;
	using System.Threading;

	delegate int Delegate();

	class Program
	{
		static void Main(string[] args)
		{
			//用於回調的委託
			Delegate del = () =>
			{
				Thread.Sleep(1000);
				Console.WriteLine("Thread is running!");
				return 100;
			};

			//使用BeginInvoke()進行異步委託回調
			IAsyncResult result = del.BeginInvoke(ar =>
					Console.WriteLine("The object arg is: {0}", (int) ar.AsyncState), 200);

			Console.WriteLine("Program start...");
			if (result.AsyncWaitHandle.WaitOne(1000))
				Console.WriteLine("The return value is: {0}", del.EndInvoke(result));

			//使用IAsyncResult.IsCompleted屬性判斷委託是否執行完畢
			Console.WriteLine("The thread status is: {0}", result.IsCompleted);
		}
	}
	```

	執行結果：

	```
	Program start...
	The thread status is: False
	```

	超時時間設爲1000毫秒，由輸出結果可知，此時異步委託尚未執行完畢，因而`IAsyncResult.IsCompleted`屬性爲`false`。

## Task
`Task`類是`.NET 4.0`之後提供的異步操作抽象，完整路徑爲`System.Threading.Tasks.Task`。

`Task`類用於表示無返回值的異步操作，對於帶有返回值的異步操作應使用`Task`類的子類`Task<TResult>`。
`Task`類創建的任務會加入線程池中。

`Task/Task<TResult>`類的主要構造函數如下：

```cs
// 接收Action類型作爲異步操作的執行內容
public Task(Action action);
// 首參數爲帶有一個參數的Action<Object>類型，第二參數爲要傳入的內容
public Task(Action<object> action, object state);
// TaskCreationOptions類型爲枚舉，並設定TaskScheduler的執行策略
public Task(Action action, TaskCreationOptions creationOptions);

// 在Task<TResult>類中接收Func<TResult>類型作爲異步執行的內容
public Task(Func<TResult> function);
public Task(Func<object, TResult> function, object state);
```

創建完畢的`Task`可以使用`Start()`方法開始執行：

```cs
// 將任務添加到當前的TaskScheduler(任務調度器)中，任務調度器選擇合適的時機執行
public void Start();
// 將任務添加到特定的TaskScheduler中
public void Start(TaskScheduler scheduler);
```

在實際開發中，更多情況下使用`Task`類的靜態方法`Run()`或者工廠類`TaskFactory`的成員方法`StartNew()`來創建和啓動新的任務。

`Task`類中的一些常用方法：

```cs
// 將參數中的異步操作在當前調度器中排隊，並返回Task對象
public static Task Run(Action action);
public static Task<TResult> Run<TResult>(Func<TResult> function);

// 等待Task完成
public void Wait(); //等待當前任務完成
public static void WaitAll(params Task[] tasks); //等待任務數組中的所有任務完成
public static bool WaitAll(Task[] tasks, int millisecondsTimeout;) //等待指定時間
```

## async/await 關鍵字
`C# 5.0`之後引入了`async`和`await`關鍵字，在語言層面給予了併發更好的支持。

1. `async`用於標記**異步方法**：

	- `async`關鍵字是**上下文關鍵字**，只有在修飾方法與Lambda時纔會被當作關鍵字處理，在其它區域將被作爲標識符處理。
	- `async`關鍵字可以標記靜態方法，但不能標記**入口點**(`Main()`方法)。
	- `async`標記的方法返回值必須爲`Task`、`Task<TResult>`、`void`其中之一。

1. `await`用於等待異步方法的結果：

	- `await`關鍵字同樣是**上下文關鍵字**，只有在`async`標記的方法中才被視爲關鍵字。
	- `await`關鍵字可以用在`async`方法和`Task`、`Task<TResult>`之前，用於等待異步任務執行結束。

一個簡單的`async`方法結構如下：

```cs
async Task testAsync()
{
	... //順序執行的內容

	return await Task.Run(() =>
	{
		... //異步執行的內容
	});
}
```

並不是方法使用`async`關鍵字標記了就是異步方法，直接出現在`async`方法內部的語句也是同步執行的，**異步執行的內容**需要使用`Task`類執行。
事實上，一個不包含任何`await`語句的`async`方法將是同步執行的，此時編譯器會給出警告。

簡單示例，使用`async/await`在屏幕併發輸出內容：

```cs
using System;
using System.Threading;
using System.Threading.Tasks;

class Program
{
	// Task.Run()方法中的Function是真正異步執行的內容
	static async Task<int> Async() =>
		await Task.Run<int>(() =>
		{
			// 線程ID與Handler()方法不同
			Console.WriteLine("Async() Thread ID: [{0}]", Thread.CurrentThread.ManagedThreadId);

			for (int i = 0; i < 5; i++)
			{
				Thread.Sleep(100);
				Console.WriteLine("Async: Run{0}", i);
			}

			Console.WriteLine("Over");
			return 666;
		});

	// 返回值爲void的async方法AsyncHandler()僅僅是包裝器
	static async void AsyncHandler()
	{
		// 方法體中的內容實際爲同步執行，與Main()函數線程ID相同
		Console.WriteLine("Handler() Thread ID: [{0}]", Thread.CurrentThread.ManagedThreadId);

		// 調用異步方法Async()不會阻塞，Async()方法開始異步執行
		Task<int> task = Async();

		// 每隔0.1s打印輸出，此時異步方法Async()也在另一線程中執行，同步打印輸出
		for (int i = 0; i < 3; i++)
		{
			Thread.Sleep(100);
			Console.WriteLine("Handler: Run{0}", i);
		}

		// 在使用await之前的代碼都運行在與Main()函數相同的線程
		Console.WriteLine("Handler()-1 Thread ID: [{0}]", Thread.CurrentThread.ManagedThreadId);

		// AsyncHandler()中的循環執行3次，此時異步方法Async()尚未執行完畢，使用await關鍵字會阻塞函數
		// 在Main()函數中，從調用await開始，AsyncHandler()就已返回了
		Console.WriteLine(await task);

		// 使用await之後的代碼運行在Async()方法所處的線程
		Console.WriteLine("Handler()-2 Thread ID: [{0}]", Thread.CurrentThread.ManagedThreadId);

		// 打印AsyncHandler()函數真正執行完畢信息
		Console.WriteLine("Handler Really Finished!");
	}

	// Main方法不能標記爲異步
	static void Main(string[] args)
	{
		Console.WriteLine("Main() Thread ID: [{0}]", Thread.CurrentThread.ManagedThreadId);
		AsyncHandler();

		// 打印AsyncHandler()函數在Main()中已經執行完畢的信息
		Console.WriteLine("Handler Finished in Main!");

		// AsyncHandler()在實際執行完成之前就返回了，需要阻塞主線程等待AsyncHandler()真正執行完畢
		Console.ReadLine();
	}
}
```

輸出結果：(`Mono 4.4.0 && ArchLinux x64`)

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

由上述程序中不難看出，在`async`關鍵字標記的異步方法中，使用`await`之前的代碼都是同步執行的，在調用了`await`之後，剩餘的代碼便異步運行在獨立的線程。

## lock 關鍵字
`C#`語言提供了與`Java`中`synchronized`類似的`lock`關鍵字，基本語法如下：

```cs
lock (object)
{
	/* do something */
}
```

`lock`塊開始時鎖定`object`，在lock代碼塊結束後釋放鎖。
鎖定相同`object`的`lock`代碼塊同一時刻只能被一個線程執行。

- 基本用法

	`lock`關鍵字用法基本與`Java`中`synchronized`關鍵字類似：

	- 被鎖定的`object`可以是引用類型實例、`this`引用、以及類型(`typeof(XXX)`)。
	- `lock`關鍵字**不能**用於修飾方法。
	- lock塊中不能使用`await`關鍵字。

	`Java`筆記中的例子使用`C#`可以改寫爲：

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

	輸出結果：(`Mono 4.4.1 && ArchLinux x64`)

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

- lock實現

	`lock`塊在實現上使用了`Monitor`類。
	`lock (object) { ... }`實際相當於：

	```
	Monitor.Enter(object);
	...
	Monitor.Exit(object);
	```

 在進入lock塊時調用`Monitor.Enter()`，離開時調用`Monitor.Exit()`。

- 死鎖問題

	在`MSDN`中提到了應避免鎖定`public`訪問權限的內容，在實際編碼中，常見的三類lock行爲都可能引發死鎖：

	- 若實例可被公共訪問，則`lock(this)`可能死鎖。
	- 若類型`XXX`可被公共訪問，則`lock(typeof(XXX))`可能死鎖。
	- 使用`lock("XXX")`時，同一進程中使用鎖定相同字符串的代碼塊都將共享同一個鎖。

	定義示例類`Example`：

	```cs
	class Example
	{
		public void Lock()
		{
			// 鎖定this
			lock (this)
			{
				Console.WriteLine("Lock!");
			}
		}

		public static void StaticLock()
		{
			// 鎖定類型
			lock (typeof(Example))
			{
				Console.WriteLine("StaticLock!");
			}
		}

		public void StringLock()
		{
			// 鎖定字符串
			lock ("Lock")
			{
				Console.WriteLine("StringLock!");
			}
		}
	}
	```

	分別針對三種情況編寫主函數測試。

	鎖定`this`：

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

	鎖定類型：

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

	鎖定相同字符串：

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

	三段代碼執行後均無輸出，且程序不退出，均死鎖。

	需要注意的是，`lock`鎖定對象是基於**線程**的，在同一線程內的代碼不受影響。
	如下代碼**不會**發生死鎖：

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
				// 雖然實例example與Lock()方法內部鎖定的this相同，但代碼運行在同一線程，不會死鎖。
				example.Lock();
			}
		}
	}
	```

	鎖定類型、字符串時類似。



# Reflection (反射)
`C#`中的**反射**機制與`Java`等高級語言類似，反射機制的主要作用：

- 獲取類型的成員信息，包括私有成員。
- 通過成員信息訪問/修改字段、屬性，調用成員方法。
- 判斷類型的繼承關係。
- 動態生成類型實例。
- 獲取類型特性(`Attribute`)信息。

在`C#`中，反射相關API在命名空間`System.Reflection`中。

## 反射機制的相關類型
`C#`語言相比`Java`，類內的成員種類更多，用於描述成員信息反射類型結構也與`Java`不盡相同。

- `System.Type`

	表示一個類型(類、結構體、接口)。

- `System.Reflection.XxxInfo`

	表示類內的成員信息，主要包含：

	1. `ConstructorInfo` 構造器信息
	1. `FieldInfo` 成員變量(字段)信息
	1. `EventInfo` 事件信息
	1. `MethodInfo` 方法信息
	1. `PropertyInfo` 屬性信息
	1. `TypeInfo` 類型信息

	繼承樹如下所示：

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

	`PropertyInfo`、`MethodInfo`等描述類成員信息的類型均直接或間接從抽象基類`MemberInfo`中繼承。

## Type/TypeInfo 類型
`C#`中的`Type`類型作用近似於`Java`反射機制中的`Class`類型，`Type`類定義了類型的反射操作。
獲取目標類型的`Type`實例是使用反射功能的起始步驟。

獲取`Type`實例可以通過以下方式：

- `typeof(T)` 通過`typeof`操作符直接由類型獲取
- `instance.GetType()` 通過目標實例的`GetType()`方法獲取
- `Type.GetType("Xxx")` 通過`Type`類型的靜態方法`Type.GetType(string)`以類型名稱字符串獲取

`TypeInfo`類型爲`Type`類型的子類，在`Type`類型的基礎上額外提供了以下內容：

- 用於訪問各類成員信息集合的**屬性**(`DeclaredMethods`、`DeclaredFields`等)。
- 用於獲取由該類型定義的成員信息的**方法**(`GetDeclaredMethod()`、`GetDeclaredField()`等)。

## 反射獲取成員信息
`Type`類型提供了與Java中`Class`類型類似的接口。
反射獲取類型成員信息的相關`API`遵循以下命名規則：

- `GetXxx(string)` 獲取**指定公有成員**
- `GetXxxs()` 獲取**所有公有成員**
- `GetXxx(string, BindingFlags)` 獲取滿足`BindingFlags`的**指定成員**
- `GetXxxs(BindingFlags)` 獲取滿足`BindingFlags`的**所有成員**

在`C#`中，`GetXxx()/GetXxxs()`方法包含多個重載版本。

- 默認的的無參`GetXxx()/GetXxxs()`方法只能獲取公有成員。
- 通過`BindingFlags`枚舉可設定反射的搜索範圍(**是否搜索非公有成員**/**是否搜索繼承而來的成員**/...)，多個`BindingFlags`可使用**邏輯或**操作符相連。

`BindingFlags`枚舉完整路徑爲`System.Reflection.BindingFlags`，定義如下：

```cs
namespace System.Reflection
{
	// 指定控制綁定和由反射執行的成員和類型搜索方法的標誌。
	[ComVisible(true)]
	[Flags]
	public enum BindingFlags
	{
		// 不指定綁定標誌。
		Default = 0,
		// 指定當綁定時不應考慮成員名的大小寫。
		IgnoreCase = 1,
		// 指定只應考慮在所提供類型的層次結構級別上聲明的成員。不考慮繼承成員。
		DeclaredOnly = 2,
		// 指定實例成員將包括在搜索中。
		Instance = 4,
		// 指定靜態成員將包括在搜索中。
		Static = 8,
		// 指定公共成員將包括在搜索中。
		Public = 16,
		// 指定非公共成員將包括在搜索中。
		NonPublic = 32,
		// 指定應返回層次結構上的公共靜態成員和受保護的靜態成員。不返回繼承類中的私有靜態成員。靜態成員包括字段、方法、事件和屬性。不返回嵌套類型。
		FlattenHierarchy = 64,
		// 指定要調用一個方法。它不能是構造函數或類型初始值設定項。
		InvokeMethod = 256,
		// 指定“反射”應該創建指定類型的實例。調用與給定參數匹配的構造函數。忽略提供的成員名。如果未指定查找類型，將應用 (Instance |Public)。調用類型初始值設定項是不可能的。
		CreateInstance = 512,
		// 指定應返回指定字段的值。
		GetField = 1024,
		// 指定應設置指定字段的值。
		SetField = 2048,
		// 指定應返回指定屬性的值。
		GetProperty = 4096,
		// 指定應設置指定屬性的值。對於 COM 屬性，指定此綁定標誌與指定 PutDispProperty 和 PutRefDispProperty 是等效的。
		SetProperty = 8192,
		// 指定應調用 COM 對象的 PROPPUT 成員。PROPPUT 指定使用值的屬性設置函數。如果屬性同時具有 PROPPUT 和 PROPPUTREF，而且需要區分調用哪一個，請使用 PutDispProperty。
		PutDispProperty = 16384,
		// 指定應調用 COM 對象的 PROPPUTREF 成員。PROPPUTREF 指定使用引用而不是值的屬性設置函數。如果屬性同時具有 PROPPUT 和 PROPPUTREF，而且需要區分調用哪一個，請使用 PutRefDispProperty。
		PutRefDispProperty = 32768,
		// 指定提供參數的類型必須與對應形參的類型完全匹配。如果調用方提供一個非空 Binder 對象，則“反射”將引發異常，因爲這意味着調用方正在提供的 BindToXXX 實現將選取適當的方法。
		ExactBinding = 65536,
		// 未實現。
		SuppressChangeType = 131072,
		// 返回其參數計數與提供參數的數目匹配的成員集。此綁定標誌用於所帶參數具有默認值的方法和帶變量參數 (varargs) 的方法。此標誌應只與 System.Type.InvokeMember(System.String,System.Reflection.BindingFlags,System.Reflection.Binder,System.Object,System.Object[],System.Reflection.ParameterModifier[],System.Globalization.CultureInfo,System.String[]) 一起使用。
		OptionalParamBinding = 262144,
		// 在 COM 互操作中用於指定可以忽略成員的返回值。
		IgnoreReturn = 16777216
	}
}
```

- 反射獲取類型的**完整路徑**

	`Type`類型的`FullName`成員屬性保存了類型的**完整路徑**：

	```cs
	typeof(Xxx).FullName;
	```

- 反射獲取類型的**成員變量**/**成員屬性**

	獲取所有成員字段/屬性信息：

	```cs
	// 獲取所有公有成員字段
	public FieldInfo[] GetFields();
	// 獲取bindingAttr範圍內的所有成員字段
	public abstract FieldInfo[] GetFields(BindingFlags bindingAttr);
	// 獲取成員屬性的API類似
	public PropertyInfo[] GetProperties();
	public abstract PropertyInfo[] GetProperties(BindingFlags bindingAttr);
	```

	獲取指定成員字段/屬性信息：

	```cs
	// 獲取指定名稱的字段
	public FieldInfo GetField(string name);
	// 以bindingAttr爲搜索標誌，獲取指定名稱的字段
	public abstract FieldInfo GetField(string name, BindingFlags bindingAttr);
	// 獲取指定名稱的屬性
	public PropertyInfo GetProperty(string name);
	// 通過名稱與返回值類型獲取屬性
	public PropertyInfo GetProperty(string name, Type returnType);
	// 通過名稱與參數類型獲取屬性(索引屬性)
	public PropertyInfo GetProperty(string name, Type[] types);
	// 以bindingAttr爲搜索標誌，獲取指定名稱的屬性
	public PropertyInfo GetProperty(string name, BindingFlags bindingAttr);
	public PropertyInfo GetProperty(string name, Type returnType, Type[] types);
	public PropertyInfo GetProperty(string name, Type returnType,
			Type[] types, ParameterModifier[] modifiers);
	public PropertyInfo GetProperty(string name, BindingFlags bindingAttr,
			Binder binder, Type returnType, Type[] types, ParameterModifier[] modifiers);
	```

- 反射獲取類型的**成員方法**/**構造方法**

	獲取所有成員方法/構造方法：

	```cs
	public MethodInfo[] GetMethods();
	public abstract MethodInfo[] GetMethods(BindingFlags bindingAttr);
	public ConstructorInfo[] GetConstructors();
	public abstract ConstructorInfo[] GetConstructors(BindingFlags bindingAttr);
	```

	獲取指定簽名的成員方法：

	```cs
	// 查找指定名稱的成員方法(適用於不存在方法重載的情形，若查找到多個方法會拋出異常)
	public MethodInfo GetMethod(string name);
	// 查找指定名稱的成員方法，使用簽名參數獲取方法
	public MethodInfo GetMethod(string name, BindingFlags bindingAttr,
			Binder binder, Type[] types, ParameterModifier[] modifiers);
	// 構造方法與類名相同，不存在使用名稱獲取的方式，應使用簽名參數類型獲取指定構造方法
	public ConstructorInfo GetConstructor(BindingFlags bindingAttr,
			Binder binder, Type[] types, ParameterModifier[] modifiers);
	...
	```

	- `binder`參數用於設定綁定相關信息，一般使用默認默認綁定`Type.DefaultBinder`。
	- `modifiers`參數用於設定簽名參數的附加修飾符，一般可置爲`null`，默認的聯編程序不處理此參數。



# Attribute (特性)
.Net平臺中的**特性**類似於`JVM`平臺中的**註解**，作用都是向特定的元素添加元數據。

MSDN中關於**特性**的介紹：

```
特性提供功能強大的方法，用以將元數據或聲明信息與代碼(程序集、類型、方法、屬性等)相關聯。
特性與程序實體關聯後，即可在運行時使用名爲“反射”的技術查詢特性。
```

在Java中，註解是**接口**，在C#中，特性是**類**。

## 使用特性
特性的基本語法爲：

```cs
[特性名稱(特性參數...)] 被修飾的元素
```

特性參數可以是定位參數、未命名參數或命名參數，定位參數部分需要匹配特性的構造器，
命名參數是**可選**的，由特性類的公有屬性和公有字段決定。

- 使用**多個**特性

	被多個特性修飾時，可以使用以下語法：

	```cs
	[特性名稱1(特性1參數...)]
	[特性名稱2(特性2參數...)]
	被修飾的元素
	```

	或將多個特性合併在一行中：

	```cs
	[特性名稱1(特性1參數...), 特性名稱2(特性2參數...)]
	被修飾的元素
	```

## 自定義特性
在C#中，所有特性都從基類`System.Attribute`中繼承。

- 特性名稱

	根據約定，所有特性類名稱都以單詞`Attribute`結束，以便將它們與`.NET Framework`中的其他項區分。
	使用特性時，不需要追加`Attribute`後綴(使用帶有`Attribute`後綴的全稱也不會報錯)。

- 特性類字段類型

	特性類可以提供一些字段和屬性，不應提供公共方法，事件等。
	在定義特性類的構造方法，字段和屬性時，對數據類型有嚴格的要求。
	類型只能爲：`Boolean, Char, Byte, Sbyte, Int16, UInt16, Int32, Int64, Single, Double, String, Type, Object, Enum`，可以使用這些類型對應的數組類型。

- 定位參數與命名參數

	特性類可以具有定位參數和命名參數。
	特性類的每個公共實例構造函數爲該屬性類定義一個有效的定位參數序列。
	特性類的每個非靜態公共讀寫字段和屬性爲該屬性類定義一個命名參數。

- 構造函數

	特性類的構造函數決定了在使用特性時應傳入怎樣的特性參數(特性的定位參數需要與構造函數參數表相匹配)。
	一個特性類可以擁有多個構造函數，使用特性時特性的定位參數只需與其中任意一個構造函數匹配即可。
	定義了空參構造函數的特性在使用時只需要寫出特性名稱即可(特性參數的小括號省略)。

- 配置自定義特性

	使用`System.AttributeUsage`特性可以指定其它特性的使用方式。
	`AttributeUsage`類的定義如下所示：

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

	- `AllowMultiple`屬性用於設置一個特性可否被多次添加到一個元素上。
	- `Inherited`屬性用於設定特性是否可被繼承。
	- `ValidOn`屬性用於設定特性的可作用對象(類型爲`AttributeTargets`枚舉，多個標識位使用邏輯或操作符`|`連接)。

	`AttributeTargets`枚舉定義如下：

	```cs
	using System.Runtime.InteropServices;

	namespace System
	{
		[ComVisible(true)]
		[Flags]
		public enum AttributeTargets
		{
			Assembly = 1, //可以對程序集應用特性
			Module = 2, //可以對模塊應用特性
			Class = 4, //可以對類應用特性
			Struct = 8, //可以對結構應用屬性
			Enum = 16, //可以對枚舉應用特性
			Constructor = 32, //可以對構造函數應用特性
			Method = 64, //可以對方法應用特性
			Property = 128, //可以對屬性應用特性
			Field = 256, //可以對字段應用特性
			Event = 512, //可以對事件應用特性
			Interface = 1024, //可以對接口應用特性
			Parameter = 2048, //可以對參數應用特性
			Delegate = 4096, //可以對委託應用特性
			ReturnValue = 8192, //可以對返回值應用特性
			GenericParameter = 16384, //可以對泛型參數應用特性
			All = 32767 //可以對任何應用程序元素應用特性
		}
	}
	```

- 獲取特性

	使用**反射**機制可以從指定元素提取特性。
	例如`Attribute.GetCustomAttribute()`、`MemberInfo.GetCustomAttributes()`等相關方法可獲取元素中的特性信息。

自定義特性示例：

```cs
using System;

// 特性Test1可作用於所有元素，不允許多次應用到一個元素，不可被繼承
[AttributeUsage(AttributeTargets.All, AllowMultiple = false, Inherited = false)]
class Test1Attribute : Attribute
{
	public string Info = "";
	public int Id = 0;

	public Test1Attribute(int id) { Id = id; }

	public void ShowAttribute() => Console.WriteLine("Id: {0}, Info: {1}", Id, Info);
}

// 特性Test2可作用於類、屬性、字段等元素，允許多次應用到一個元素，不可被繼承
[AttributeUsage(AttributeTargets.Class | AttributeTargets.Property | AttributeTargets.Field,
		AllowMultiple = true, Inherited = false)]
class Test2Attribute : Attribute
{
	public string Name { get; set; } = "Null";

	public void ShowAttribute() => Console.WriteLine("Name: {0}", Name);
}

[Test1(1, Info = "Test1")] //使用特性時，可簡化名稱，Attribute後綴可省略
[Test2, Test2(Name = "Test2")] //AllowMultiple爲true的特性可多次修飾一個元素，且多個特性可合併在一個語句中
class Test
{
	[Test1Attribute(2, Info = "Test1Attribute")] //使用特性也可以不省略Attribute後綴
	public string Property { get; set; } = "";
}

class Program
{
	static void Main(string[] args)
	{
		Console.WriteLine("Find attribute at class Test:");
		// 獲取Test類上的特性
		foreach (var attr in typeof(Test).GetCustomAttributes(false))
		{
			if (attr as Test1Attribute != null)
				(attr as Test1Attribute).ShowAttribute();
			else if (attr as Test2Attribute != null)
				(attr as Test2Attribute).ShowAttribute();
		}

		Console.WriteLine();

		Console.WriteLine("Find attribute at property Test.Property:");
		// 獲取Test類Name屬性的特性
		foreach (var attr in typeof(Test).GetProperty("Property").GetCustomAttributes(false))
		{
			if (attr as Test1Attribute != null)
				(attr as Test1Attribute).ShowAttribute();
		}
	}
}
```

輸出結果：

```
Find attribute at class Test:
Id: 1, Info: Test1
Name: Null
Name: Test2

Find attribute at property Test.Property:
Id: 2, Info: Test1Attribute
```



# 動態代理
在`C#`中，提供了類似`Java`中的**動態代理**機制。

`C#`中實現動態代理需要以下內容：

- 代理規則類需要從基類`System.Runtime.Remoting.Proxies.RealProxy`中派生。
- 被代理的類需要從基類`System.MarshalByRefObject`中派生。

與`Java`不同，在`C#`中，要使一個類能被代理需要該類從抽象基類`System.MarshalByRefObject`中繼承。

如下所示：

```cs
using System;

class Xxx : MarshalByRefObject
{
	...
}
```

編寫代理規則需要繼承抽象基類`System.Runtime.Remoting.Proxies.RealProxy`，並實現其中的`Invoke()`抽象方法。

一個基本的`RealProxy`泛型封裝如下所示：

```cs
// 限定泛型參數爲MarshalByRefObject子類
class Proxy<T> : RealProxy where T : MarshalByRefObject
{
	// 保存被代理類的實例以及代理方法執行前後的操作
	private T t = null;
	private Action beforeAction = null;
	private Action afterAction = null;

	// 使用代理類Type做爲基類MarshalByRefObject的構造方法參數
	public Proxy(T t, Action before = null, Action after = null) : base(typeof(T))
	{
		this.t = t;
		beforeAction = before;
		afterAction = after;
	}

	// 編寫代理規則
	public override IMessage Invoke(IMessage msg)
	{
		// 將消息接口轉換爲方法調用消息接口
		IMethodCallMessage method = msg as IMethodCallMessage;

		// 執行實例方法調用前的代理操作
		beforeAction?.Invoke();

		// 通過方法消息執行真正的方法體
		object result = method.MethodBase.Invoke(t, method.Args);

		// 執行實例方法調用後的代理操作
		afterAction?.Invoke();

		// 構建方法返回信息
		return new ReturnMessage(result, null, 0, method.LogicalCallContext, method);
	}

	// 封裝獲取代理的接口
	public T GetProxy() => GetTransparentProxy() as T;
}
```

- `RealProxy`類中定義了`GetTransparentProxy()`方法，使用該方法可獲取應用了代理規則之後的實例。
- 需要使用被代理類的`Type`類型做爲基類`RealProxy`的構造函數參數，否則獲取的代理實例爲空指針。

簡單的動態代理完整實例如下所示：

```cs
using System;
using System.Runtime.Remoting.Messaging;
using System.Runtime.Remoting.Proxies;

// 被代理的類，需要繼承自基類MarshalByRefObject
class Example : MarshalByRefObject
{
	public string GetName() => "Example";
	public void Print(string str) => Console.WriteLine(str);
}

// 代理規則類，需要繼承自基類RealProxy
class ExampleProxy : RealProxy
{
	private Example example = null;

	// 使用被代理類的Type類型做爲基類構造器參數
	public ExampleProxy(Example example) : base(typeof(Example)) { this.example = example; }

	// 實現代理規則
	public override IMessage Invoke(IMessage msg)
	{
		IMethodCallMessage callMsg = msg as IMethodCallMessage;

		// 打印調用方法的名稱
		Console.WriteLine("Call method: {0}", callMsg.MethodName);

		object result = callMsg.MethodBase.Invoke(example, callMsg.Args);

		// 打印調用方法的結果
		Console.WriteLine("Method result: {0}\n", result);

		return new ReturnMessage(result, null, 0, callMsg.LogicalCallContext, callMsg);
	}
}

class Program
{
	static void Main(string[] args)
	{
		// 構建原始實例
		Example example = new Example();
		// 獲取應用了代理規則後的實例
		Example exampleProxy = new ExampleProxy(example).GetTransparentProxy() as Example;

		// 調用方法
		exampleProxy.GetName();
		exampleProxy.Print("Test Proxy!");

		Console.ReadLine();
	}
}
```

輸出結果：

```
Call method: GetName
Method result: Example

Call method: Print
Test Proxy!
Method result:

```

由輸出結果可知，在訪問被代理實例的成員方法時觸發了定義的代理操作。



# FTP
在`.Net`平臺中，標準庫內置了對`FTP`協議的支持。

`FTP`相關的類均位於`System.Net`命名空間，常見的有：

- `WebRequest` 表示對`URI`(統一資源標識符)的請求，是未實現的抽象類
- `WebResponse` 表示對`URI`(統一資源標識符)的迴應，是未實現的抽象類
- `FtpWebRequest` 表示`FTP`協議的客戶端請求，是`WebRequest`的子類實現
- `FtpWebResponse` 表示`FTP`協議的服務端迴應，是`WebResponse`的子類實現
- `WebRequestMethods` 定義了各類協議的具體請求方法字符串，`FTP`協議的方法定義位於其內部類`WebRequestMethods.Ftp`中

## 創建 FTP 請求
`WebRequest`類的靜態成員方法`WebRequest.Create(string)`，以`FTP`路徑字符串爲參數即可構建一個未設定操作的`FTP`請求：

```cs
string ftpUri = $"ftp://ip地址/路徑...";
FtpWebRequest ftpRequest = WebRequest.Create(ftpUri) as FtpWebRequest;
```

對於需要賬戶的`FTP`服務端，需要在請求中設定賬戶和密碼：

```cs
string ftpUserName = "...", ftpUserPassword = "...";
ftpRequest.Credentials = new NetworkCredential(ftpUserName, ftpUserPassword);
```

## 下載
在一個未設定操作的`FTP`請求創建完畢後，設置請求對象的`Method`屬性爲`RETR`(`FTP`協議中規定的下載指令)。

```cs
ftpRequest.Method = "RETR";
```

`WebRequestMethods.Ftp`中定義了各類`FTP`操作的指令文本，下載操作可以使用：

```cs
ftpRequest.Method = WebRequestMethods.Ftp.DownloadFile;
```

下載請求設定完畢後，執行以下操作：

1. 使用`WebRequest`類成員方法`WebRequest.GetResponse()`獲取服務端迴應，並向下轉型爲`FtpWebResponse`迴應。
1. 使用`FtpWebResponse`類成員方法`FtpWebResponse.GetResponseStream()`獲取迴應中包含的文件流(`Stream`類)，並將其寫入本地文件。

完整實例代碼：

```cs
/// <summary>
/// 下載文件，保存到指定路徑
/// </summary>
/// <param name="ftpUri">FTP目標路徑</param>
/// <param name="savePath">保存到本地的路徑</param>
/// <param name="ftpUserName">FTP用戶名</param>
/// <param name="ftpUserPassword">FTP用戶密碼</param>
/// <returns>下載是否成功</returns>
public bool DownloadFile(string ftpUri, string savePath, string ftpUserName, string ftpUserPassword)
{
	bool result = false;

	try
	{
		FtpWebRequest request = WebRequest.Create(ftpUri) as FtpWebRequest;

		// 設定下載請求，填充FTP用戶名/密碼
		request.Method = WebRequestMethods.Ftp.DownloadFile;
		request.Credentials = new NetworkCredential(ftpUserName, ftpUserPassword);

		// 對於請求迴應、文件流等資源，需要使用using語句或顯式關閉資源
		using (FtpWebResponse response = request.GetResponse() as FtpWebResponse)
		{
			// 複製迴應數據流到文件流中
			using (FileStream file = new FileStream(savePath, FileMode.Create))
				response.GetResponseStream().CopyTo(file);

			// 驗證操作狀態，打印操作結果
			Console.WriteLine($"Operate status: {response.StatusDescription}");
			if (response.StatusCode == FtpStatusCode.ClosingData) result = true;
		}
	}
	catch (Exception ex) { Console.WriteLine(ex.StackTrace); }

	return result;
}
```

## 上傳
上傳操作與下載略有不同，首先對未設定操作的`FTP`請求設置操作：

```cs
ftpRequest.Method = WebRequestMethods.Ftp.UploadFile;
```

若使用了**網絡代理**(如翻牆工具等)，則還需要將請求的`Proxy`屬性置爲`null`，
否則會產生`用 HTTP 代理時不支持請求的 FTP 命令。`異常。

```cs
ftpRequest.Proxy = null;
```

之後執行以下操作：

1. 設定請求的`ContentLength`屬性，表示上傳文件的大小。
1. 使用`FtpWebRequest`類成員方法`FtpWebRequest.GetRequestStream()`獲取請求文件流。
1. 將本地待上傳文件複製到請求文件流中。
1. 使用`FtpWebResponse`類成員方法`FtpWebResponse.GetResponse()`獲取操作迴應。

完整實例代碼：

```cs
/// <summary>
/// 上傳文件到指定FTP路徑
/// </summary>
/// <param name="ftpUri">FTP目標路徑</param>
/// <param name="localPath">待上傳的本地文件路徑</param>
/// <param name="ftpUserName">FTP用戶名</param>
/// <param name="ftpUserPassword">FTP用戶密碼</param>
/// <returns>上傳是否成功</returns>
public bool UploadFile(string ftpUri, string localPath, string ftpUserName, string ftpUserPassword)
{
	bool result = false;

	try
	{
		FtpWebRequest request = WebRequest.Create(ftpUri) as FtpWebRequest;

		// 設定下載請求，填充FTP用戶名/密碼
		request.Proxy = null;
		request.Method = WebRequestMethods.Ftp.UploadFile;
		request.Credentials = new NetworkCredential(ftpUserName, ftpUserPassword);

		using (FileStream file = new FileStream(localPath, FileMode.Open))
		{
			// 設定待上傳的文件大小，複製文件數據流到請求文件流中
			request.ContentLength = file.Length;
			using (Stream upStream = request.GetRequestStream()) file.CopyTo(upStream);
		}
		using (FtpWebResponse response = request.GetResponse() as FtpWebResponse)
		{
			// 驗證操作狀態，打印操作結果
			Console.WriteLine($"Operate status: {response.StatusDescription}");
			if (response.StatusCode == FtpStatusCode.ClosingData) result = true;
		}
	}
	catch (Exception ex) { Console.WriteLine(ex.StackTrace); }

	return result;
}
```



# WinForm 開發註記
`C#`對應的**GUI**庫爲基於`.NET Framework`的`Windows Form`。

## 常見控件類型
在`Windows Form`中，控件相關的類大多派生於`System.Windows.Forms.Control`。
控件的名稱也與其它的GUI庫類似：

- `Form` 窗體，類似於Qt中的**QFrame**
- `Label` 標籤文本，類似於Qt中的**QLabel**
- `Button` 按鈕，類似於Qt中的**QPushButton**
- `RadioButton` 單選框，類似於Qt中的**QRadioButton**
- `CheckBox` 複選框，類似於Qt中的**QCheckBox**
- `CheckedListBox` 多行復選框
- `ListBox` 列表框，類似於Qt中的**QListWidget**
- `TextBox` 簡單文本框，類似於Qt中的**QLineEdit**
- `RichTextBox` 富文本框，類似於Qt中的**QTextEdit**
- `TreeView` 樹形控件，類似於Qt中的**QTreeWidget**

## 容器控件
在`Windows From`中，常見的容器控件有：

- `Panel` 最基本的面板容器
- `GroupBox` 控件組面板，類似於Qt中的**QGroupBox**

部分容器自帶佈局，放入其中的控件會按照其佈局排列：

- `FlowLayoutPanel` 流佈局面板
- `TableLayoutPanel` 表格佈局面板

## 佈局與樣式
在`Windows From`中，控件的大小與位置一般是固定的。
若需要控件大小自動變化，則應使用`AutoSize`屬性。
一般情況下，控件的位置不會隨着窗口大小的變化而自動排列位置，需要通過設置`Archor`屬性來指定擴展的方向。
控件還可以通過設置`Dock`屬性指定需要停靠的邊框。

## 控件事件
一個標準的`Windows Form`控件中定義了多種事件，通過將指定的事件處理函數綁定到事件上，當滿足事件觸發的條件時，綁定的函數便會被回調。
一個事件可以綁定多個事件處理函數，一個事件處理函數也可以被多個事件綁定。

普通的事件簽名沒有限制，但`.NET Framework`類庫中的所有事件均基於`EventHandler`委託，定義如下：

```cs
public delegate void EventHandler(object sender, EventArgs e);
```

`sender`參數指明瞭事件的發出者，而`e`參數攜帶了事件的具體信息，`EventArgs`是所有`.NET Framework`類庫中事件的基類，
實際的事件類型只有符合`EventHandler`委託簽名的函數才能被綁定到`Windows Form`的控件事件上。

常用的`Windows Form`控件事件有：

- `Load` 載入窗體時觸發，一般可用於初始化一些UI設置(`Form`類)
- `Click` 點按控件時觸發
- `MouseDown` 鼠標按下時觸發
- `MouseUp` 鼠標擡起時觸發
- `KeyDown` 按鍵按下時觸發
- `KeyUp` 按鍵擡起時觸發
- `GotFocus` 接收焦點時觸發

## 接收Windows消息
在`Windows Form`中，所有從`System.Windows.Forms.Control`派生的類都包含以下方法：

```cs
protected override void WndProc(ref Message m);
```

重寫其即可處理**Windows消息**。

`Message`類完整路徑爲`System.Windows.Forms.Message`，該類包裝了Windows消息，包含以下屬性：

- `HWnd` 獲取或設置消息的窗口句柄
- `LParam` 指定消息的**LParam**字段
- `Msg` 獲取或設置消息的**ID**號
- `Result` 指定爲響應消息處理而向**Windows**返回的值
- `WParam` 獲取或設置消息的**WParam**字段



# 調用 C/C++ 動態鏈接庫
C#支持調用`C/C++`語言編寫的`dll`。

使用`DLLImport`特性修飾一個方法。
加載動態鏈接庫需要指定dll的路徑以及符號名稱：

```cs
[DLLImport("DLL Library", EntryPoint = "Symbol Name")]
public/protected/private extern Type Func(Type args...);
```

聲明方法的名稱可以與dll中導出符號名稱不同，只需在標註的`EntryPoint`中寫明對應的符號名稱。
聲明的方法參數表必須與dll中的參數表**完全匹配**。

C#中的常見類型與C++中類型之間的轉換關係：

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



# 特殊關鍵字
介紹一些在其它語言中不常見的關鍵字。

## internal 關鍵字
類和類成員前可以使用`internal`關鍵字。

- `internal`關鍵字修飾類

	`internal`關鍵字用在類、接口前表示只能在當前項目中訪問該類、接口。
	`internel`關鍵字修飾的類不能被`public`類繼承。
	默認不添加關鍵字的情況下，類和接口的訪問屬性即爲`internal`。

- `internal`關鍵字修飾成員

	`internal`關鍵字用在類內成員之前表示只能在當前項目中訪問該成員。
	在對類內成員使用時，`internal`關鍵字可以搭配`protected`關鍵字使用，即定義一個只能被當前項目的子類訪問的成員。

需要注意的是，`internal`修飾的類不能作爲`public`成員出現在其它類中。

## readonly 關鍵字
`readonly`關鍵字用於修飾**運行時只讀**變量。
`readonly`變量的賦值操作只能發生在以下情形：

- 在變量定義時。
- 在變量所屬類的構造函數中。

與`const`關鍵字的異同：

- `const`修飾的變量被視爲**編譯時常量**，`readonly`修飾的變量被視爲**運行時常量**。
- `const`關鍵字修飾的變量須在**定義時**立即初始化。
- `const`僅能修飾**值類型**/`string`類型/`null`，`readonly`可以修飾任意類型，
- `const`修飾的變量自動帶有`static`特性：

	`const`關鍵字與`static`關鍵字不能共同修飾相同變量。
	`const`修飾的變量**可以**被定義在靜態類中。

- `readonly`修飾的變量默認**不帶有**`static`屬性：

	`readonly`與`static`關鍵字可一同使用表示**靜態只讀**變量。

對於引用類型，不能使用`const`關鍵字修飾，要限制其修改只能使用`readonly`關鍵字。

## partial 關鍵字
`partial`關鍵字用於定義`部分類`(局部類型)，局部類型允許我們將一個類、結構或接口分成幾個部分，分別實現在幾個不同的源碼文件中。

在`Windows From`中，窗口類代碼便使用了部分類特性。
對於同一個窗口類，由VS窗體編輯器生成的GUI代碼在文件**GUI類名.Designer.cs**文件中，而由用戶編寫的界面控制代碼放在**GUI類名.cs**文件中。
兩個文件中的代碼本質上屬於同一個類，`部分類`特性巧妙地隔離開了**由IDE產生的代碼**與**用戶自行編寫的代碼**，使代碼結構更清晰。

## params 關鍵字
`params`用在方法的參數之前，用於標記可變參數。一個方法只能擁有一個`params`參數，且被`params`標記的參數必須爲最後一個參數，並且是數組類型。

在調用含有`params`參數的方法時，方法末尾可以追加**任意數量**的類型相符的變量，例如：

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
		Print(1, 2, 3, 4, 5); //多個int型參數都被添加到params關鍵字標記的數組中
}
```



# 常見問題

## 處理`\0`結尾字符串
在C#中，以`\0`結尾的`string`類型尾部的`\0`並不會被自動忽略，在輸出是，中文環境下會顯示`口口...`，刪除字符串中的`\0`可以使用`string`類的`Replace()`成員方法進行字符串替換：

```cs
string test = "aaa\0\0\0";
Console.WriteLine(test); //輸出 "aaa口口口"
string testNew = test.Replace("\0", ""); //將 \0 替換爲空
Console.WriteLine(testNew); //輸出 "aaa"
```

## MySQL 中 TINYINT 類型
在`MySQL`中沒有內置的`bool`類型，`bool`類型常常使用最小的整型數據類型`TINYINT`表示。

在C#中，會將`TINYINT(1)`視爲`bool`類型處理，對於類型爲`TINYINT(1)`的列，使用`ToString()`方法轉換得到的是文本`true/false`而非字面意義數值。
要使`TINYINT`不被視爲`bool`類型，需要調整數據列的顯示寬度，即類型設爲`TINYINT(2)`或是其它大於`1`的值。

## DEBUG 宏
在C#中，可使用類似C/C++的宏針對`DEBUG/RELEASE`模式下進行額外的操作，語法如下：

```cs
#if DEBUG
// do something...
#else
// do something...
#endif
```

## 輸出代碼文件名、行號
在輸出日誌時，常常需要輸出打印日誌的代碼位置以便跟蹤查看。

- 使用`StackStrace`獲取調試信息

	使用`StackStrace`類通過反射可以得到函數調用者的棧信息，並從中獲取代碼信息。
	使用`StackTrace`的`GetFrame(int index)`成員方法獲取指定的堆棧幀(`StackFrame`類型)。

	- 索引`0`爲當前函數堆棧的信息。
	- 索引`1`爲函數調用者的堆棧信息，以此類推，可獲取多級調用者信息。
	- 使用`StackFrame`類可以獲得堆棧所在的方法名稱、源碼文件名稱，代碼行號等，還可進一步獲得類型信息。

- `.Net 4.5`新增特性

	在`.Net 4.5`中引入了三種`Attribute`用於獲取方法的調用成員名稱、調用文件、調用代碼行號：

	- `System.Runtime.CompilerServices.CallerMemberNameAttribute` 成員名稱
	- `System.Runtime.CompilerServices.CallerFilePathAttribute` 調用文件
	- `System.Runtime.CompilerServices.CallerLineNumberAttribute` 調用行號

	三種特性用於修飾日誌函數的參數(參數需要有默認值)，編譯器會自動爲參數補充對應的調用信息，如下所示：

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
