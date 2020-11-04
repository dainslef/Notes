<!-- TOC -->

- [基礎類型](#基礎類型)
	- [Literal number (字面值)](#literal-number-字面值)
	- [char (字符類型)](#char-字符類型)
	- [格式化](#格式化)
	- [有符號數轉換無符號數](#有符號數轉換無符號數)
	- [字符串、數值轉換](#字符串數值轉換)
- [Package](#package)
	- [import 關鍵字](#import-關鍵字)
	- [import static 語法](#import-static-語法)
	- [實例](#實例)
	- [引用依賴](#引用依賴)
- [Container (容器)](#container-容器)
- [Enum (枚舉)](#enum-枚舉)
- [對象相等性](#對象相等性)
	- [equals() 方法](#equals-方法)
	- [hashCode() 方法](#hashcode-方法)
- [淺複製與深複製](#淺複製與深複製)
	- [淺複製](#淺複製)
	- [深複製](#深複製)
- [泛型](#泛型)
	- [類型擦除](#類型擦除)
	- [泛型方法](#泛型方法)
- [Nested Classes (嵌套類)](#nested-classes-嵌套類)
- [併發編程](#併發編程)
	- [Thread / Runnable](#thread--runnable)
		- [Daemon Thread](#daemon-thread)
	- [synchronized & Monitors](#synchronized--monitors)
		- [synchronized語法](#synchronized語法)
	- [Executor 框架](#executor-框架)
- [Annotation (註解)](#annotation-註解)
	- [內置註解](#內置註解)
	- [元註解](#元註解)
	- [自定義註解](#自定義註解)
- [Reflection (反射)](#reflection-反射)
	- [反射機制的相關類型](#反射機制的相關類型)
	- [Class 類型](#class-類型)
	- [反射獲取成員信息](#反射獲取成員信息)
	- [反射構建實例](#反射構建實例)
	- [反射調用對象方法](#反射調用對象方法)
	- [反射修改字段](#反射修改字段)
	- [反射判定繼承關係](#反射判定繼承關係)
	- [ClassLoader (類加載器)](#classloader-類加載器)
- [動態代理](#動態代理)
	- [代理模式](#代理模式)
	- [實例](#實例-1)
- [Default Method (接口默認方法)](#default-method-接口默認方法)
- [Lambda](#lambda)
	- [實現函數式接口](#實現函數式接口)
	- [一般用法](#一般用法)
	- [Method Reference (方法引用)](#method-reference-方法引用)
	- [標準庫中的函數式接口 (java.util.function)](#標準庫中的函數式接口-javautilfunction)
- [Process API](#process-api)
- [DateTime API](#datetime-api)
	- [java.util.Date](#javautildate)
	- [java.time.LocalDateTime](#javatimelocaldatetime)
		- [LocalDateTime處理日期](#localdatetime處理日期)
		- [關於 Oracle JDK 8 在 yyyyMMddHHmmssSSS 時間格式下的 DateTimeParseException](#關於-oracle-jdk-8-在-yyyymmddhhmmsssss-時間格式下的-datetimeparseexception)
	- [java.time.Instant](#javatimeinstant)
		- [Caused by: java.time.DateTimeException: Unable to obtain LocalDate from TemporalAccessor: 2020-05-14T03:08:24.322080Z of type java.time.Instant](#caused-by-javatimedatetimeexception-unable-to-obtain-localdate-from-temporalaccessor-2020-05-14t030824322080z-of-type-javatimeinstant)
		- [Caused by: java.time.temporal.UnsupportedTemporalTypeException: Unsupported field: InstantSeconds](#caused-by-javatimetemporalunsupportedtemporaltypeexception-unsupported-field-instantseconds)
- [定時任務](#定時任務)
	- [Timer API](#timer-api)
		- [Timer任務調度](#timer任務調度)
		- [java.lang.IllegalStateException: Timer already cancelled.](#javalangillegalstateexception-timer-already-cancelled)
- [JDBC](#jdbc)
	- [連接數據庫](#連接數據庫)
	- [數據庫操作](#數據庫操作)
	- [獲取時間](#獲取時間)
	- [與 Access 數據庫交互](#與-access-數據庫交互)
	- [com.mysql.jdbc.MysqlDataTruncation: Data truncation: Data too long for column 'column_name'](#commysqljdbcmysqldatatruncation-data-truncation-data-too-long-for-column-column_name)
- [Eclipse 使用註記](#eclipse-使用註記)
	- [Marketplace](#marketplace)
	- [查看源碼](#查看源碼)
	- [編輯器自動換行](#編輯器自動換行)
- [IntelliJ IDEA 使用註記](#intellij-idea-使用註記)
	- [顯示行號和不可見空白](#顯示行號和不可見空白)
	- [字段類型推斷、參數名稱提示](#字段類型推斷參數名稱提示)
	- [列邊界提示](#列邊界提示)
	- [縮進](#縮進)
	- [包路徑摺疊](#包路徑摺疊)
	- [其它常用選項](#其它常用選項)
	- [項目打包](#項目打包)
	- [多模塊項目](#多模塊項目)
- [常見問題記錄](#常見問題記錄)
	- [String.split()](#stringsplit)
	- [String.format()](#stringformat)
	- [String.getProperty()](#stringgetproperty)
	- [java.lang.UnsatisfiedLinkError: */jre/lib/amd64/libawt_xawt.so: libXrender.so.1: cannot open shared object file: No such file or directory](#javalangunsatisfiedlinkerror-jrelibamd64libawt_xawtso-libxrenderso1-cannot-open-shared-object-file-no-such-file-or-directory)
	- [java.lang.UnsatisfiedLinkError: */jre/lib/amd64/libawt_xawt.so: libXtst.so.6: cannot open shared object file: No such file or directory](#javalangunsatisfiedlinkerror-jrelibamd64libawt_xawtso-libxtstso6-cannot-open-shared-object-file-no-such-file-or-directory)

<!-- /TOC -->



# 基礎類型
與主流語言不同，Java中僅僅提供了**有符號**數值類型，**沒有**提供無符號的數值類型。

基礎整型數值類型如下所示：

- `byte`，單字節，範圍`-128 ~ 127`
- `short`，雙字節，範圍`-32768 ~ 32767`
- `int`，四字節，範圍`-2147483648 ~ 2147483647`
- `long`，八字節，範圍`-9223372036854775808 ~ 9223372036854775807`

浮點型數值類型如下所示：

- `float`，四字節，範圍`-3.4028235E38 ~ 3.4028235E38`
- `double`，八字節，範圍`-1.7976931348623157E308 ~  1.7976931348623157E308`

## Literal number (字面值)
在Java中，無任何修飾的整型數值字面值默認爲`int`類型，無任何修飾的浮點型數值字面值默認爲`double`類型。

字面值數值在進行賦值操作時數值的大小不能超過目標類型的上限。
示例：

```java
byte num0 = 1; //正確
byte num1 = 1000; //錯誤，提示"從int轉換到byte可能會有損失"
```

整型字面值默認爲`int`型，即默認字面值範圍應在`-2147483648 ~ 2147483647`之間，
當整型字面值超出這個範圍時，即使目標類型能夠容納數值，賦值操作時依然會報錯。
示例：

```java
long num = 6666666666; //錯誤，提示"過大的整數: 6666666666"
```

此時，需要顯式使用後綴指定字面值類型，如下所示：

```java
long num0 = 6666666666L; //正確
long num1 = 6666666666l; //正確
```

常用的字面值後綴：

| 後綴 | 含義 |
| :-: | :-: |
| L/l | long |
| F/f | float |
| D/d | double |

整型數值通過添加前綴可以指定數值以不同進製表示：

| 前綴 | 含義 |
| :-: | :-: |
| 0B/0b | 二進制數值 |
| 0 | 八進制數值 |
| 0X/0x | 十六進制數值 |

## char (字符類型)
與其它語言不同，`Java`中採用`UTF-16`編碼，一個字符佔用**兩個字節**，而非傳統語言中的單個字節。

`char`類型無符號，範圍爲`0 ~ 65535`，字面值表示方式爲`'\u0000' ~ '\uFFFF'`，如下所示：

```java
char c0 = \u0000; //錯誤，字符需要加單引號
char c1 = '\U0000'; //錯誤，字符只能使用小寫`\u`轉義，大寫`\U`無效
char c2 = '\u0000'; //正確
```

## 格式化
在Java中，使用`System.out.printf()`方法進行格式化輸出，格式化語法類似C語言標準庫中的`printf()`函數。

常用的格式化字符：

| 格式化字符 | 含義 | 樣例 |
| :-: | :-: | :-: |
| %s | 字符串類型 | `"abc"` |
| %c | 字符類型 | `'a'` |
| %b | 布爾類型 | `true` |
| %d | 整數類型(十進制) | `99` |
| %x | 整數類型(十六進制) | `FF` |
| %o | 整數類型(八進制) | `77` |
| %f | 浮點類型 | `99.990000` |
| %a | 十六進制浮點類型 | `0x1.8ff5c28f5c28fp6` |
| %e | 指數類型 | `9.999000e+01` |
| %g | 通用浮點類型(寬度較短) | `99.9900` |
| %h | 散列碼 | / |
| %% | 百分比符號(在格式化語句中直接使用`%`會開始轉義) | `%` |
| %n | 換行符(在格式化語句中使用`\n`換行轉義無效) | / |

實例如下所示：

```java
public class Main {

	public static void main(String[] args) {

		System.out.println("99:");
		System.out.printf("%%s: %s %n", 99);
		System.out.printf("%%c: %c %n", 99);
		System.out.printf("%%b: %b %n", 99);
		System.out.printf("%%d: %d %n", 99);
		System.out.printf("%%x: %x %n", 99);
		System.out.printf("%%o: %o %n", 99);
		System.out.printf("%%h: %h %n", 99);

		System.out.println("\n99.99:");
		System.out.printf("%%f: %f %n", 99.99);
		System.out.printf("%%a: %a %n", 99.99);
		System.out.printf("%%e: %e %n", 99.99);
		System.out.printf("%%g: %g %n", 99.99);
	}

}
```

輸出結果：

```
99:
%s: 99
%c: c
%b: true
%d: 99
%x: 63
%o: 143
%h: 63

99.99:
%f: 99.990000
%a: 0x1.8ff5c28f5c28fp6
%e: 9.999000e+01
%g: 99.9900
```

數值類型支持更豐富的格式化操作：

| 格式化字符 | 含義 | 樣例 |
| :-: | :-: | :-: |
| `%+d` | 爲數值類型添加正負號 | `+99`/`-99` |
| `% 5d` | 指定輸出數值的寬度，寬度不足時左邊使用空格補齊 | `   99` |
| `%-5d` | 指定輸出數值的寬度，寬度不足時右邊使用空格補齊 | `99   ` |
| `%05d` | 指定輸出數值的寬度，寬度不足時使用0補齊 | `00099` |
| `%,d` | 格式化數值時使用`,`對長數值進行分割 | `9,999` |
| `%<d` | 格式化數值，使用前一個數值做爲格式化對象 | / |
| `%(d` | 格式化負數時採用括號標記負值(對正值無效) | `(99)` |
| `%#`/`%#x` | 格式化8/16進制數值時添加前綴`0`/`0x` | `0x63` |

## 有符號數轉換無符號數
在`Java`中，沒有內置的無符號類型，則在表示大於`2 ^ 位寬 - 1`的數值時，需要使用更高位寬的數值來表示。

以`byte`類型爲例，有符號的`byte`類型範圍在`-128 ~ 127`之間，當數值大於`127`時，則需要使用更高位寬的類型表示(如`short`)。
`byte`類型爲單字節，則將原始有符號數值轉換位更高位寬的類型，
再與`0xFF`進行`&`(邏輯與)操作(保留原始數值位，擦除其它內容)，得到對應的無符號值。

以`byte`類型負數`-11`爲例，運算過程如下：

1. `byte`類型數值`-11`，原碼爲：

	`10001011`

	計算機內部數值以反碼存儲，反碼錶示爲：

	`11110101`(對應無符號數值`245`(首位不視爲符號位))

1. `byte`類型數值`-11`提升到`short`型，編譯器會保留數值含義(數值`-11`)不變，原碼爲：

	`1000000000001011`

	在計算機中存儲的補碼爲：

	`1111111111110101`

	若保留原先的無符號值含義(數值`245`)，則原碼/補碼均應爲：

	`0000000011110101`

	對比可知**低8位**對應原先的數值，則應保留低8位數值，將高8位**置零**，與`0xFF`進行**邏輯與**操作可達到此效果。

## 字符串、數值轉換
基礎數值類型存在`OOP`的封裝，用於在泛型中使用。
示例：

| 基礎數值類型 | 封裝數值類型 |
| :-: | :-: |
| byte | Byte |
| short | Short |
| int | Integer |
| long | Long |
| float | Float |
| double | Double |

引用數值類型提供了一系列的靜態方法用於字符串到數值之間的轉換。
以`Integer`類型爲例，將字符串形式的數值轉換爲基礎數值類型：

```scala
scala> Integer.parseInt("2333") // 默認文本數值視爲10進制
res1: Int = 2333
```

使用無進制參數版本的轉換方法時，默認將文本數值視爲十進制。
對於非十進制的數值，需要使用帶有進制參數的重載版本：

```scala
scala> Integer.parseInt("d9") // 16進制數值文本會拋出異常
java.lang.NumberFormatException: For input string: "d9"
  at java.lang.NumberFormatException.forInputString(NumberFormatException.java:65)
  at java.lang.Integer.parseInt(Integer.java:580)
  at java.lang.Integer.parseInt(Integer.java:615)
  ... 27 elided

scala> Integer.parseInt("d9", 16) // 使用進制參數後正常轉換
res2: Int = 217

scala> Integer.parseInt("2333", 8) // 文本數值設爲8進制
res3: Int = 1243
```

String類型則提供了`valueOf()`方法用於將數值轉爲字符串形式：

```scala
scala> String.valueOf(2333) // 轉換10進制數值
res4: String = 2333

scala> String.valueOf(0xd9) // 轉換16進制數值
res5: String = 217
```



# Package
`Package`是`Java`的命名空間隔離機制。
使用`package`關鍵字將類層次化區分，使用`import`關鍵字來導入使用。
未使用`package`關鍵字的類則位於**默認包**中。

## import 關鍵字
`import`語法：

```java
import 包路徑.類名;
```

引入**內部類**，語法類似：

```java
import 包路徑.類名.內部類名稱;
```

`import`與源碼的路徑**無關**。
執行字節碼時需要將**class文件**放在與其源碼中`package`路徑的對應目錄下，否則會在執行時出錯。
另外，包名也可以是`*.*.*`的形式。

## import static 語法
`Java 5`中新加入了`import static`用法。
`import static`可以包含目標類中的靜態方法，如下所示：

```java
import static [包路徑].[類名].[靜態方法名];
```

使用靜態導入的靜態方法使用時不必寫出類名，直接使用方法名稱即可。

## 實例
有兩個文件**A.java**和**B.java**。

文件B中的類被A中引用,則將B打包,代碼中添加`package b`，並放在b目錄下。
文件A中引用B中的類。

按照描述，兩文件的位置：

- **文件A**路徑爲`~/A.java`。
- **文件B**路徑爲`~/b/B.java`。

實例代碼(`import`)：

A.java:

```java
import b.B;

public class A {
	public static void main(String[] args) {
		B.getNow();
	}
}
```

B.java:

```java
package b;

public class B {
	public static void getNow() {
		System.out.println("Success!");
	}
}
```

實例代碼(`import static`)：

A.java:

```java
import static b.B.getNow;

public class A {
	public static void main(String[] args) {
		getNow();
	}
}
```

B.java:

```java
package b;

public class B {
	public static void getNow() {
		System.out.println("Success!");
	}
}
```

其中**A.java**文件能夠正常調用類B的方法`getNow()`。

一個`java`源碼文件只能包含一個**公有類**，且源碼文件的名稱應該與包含的公有類的類名**一致**。

`package`打包的源碼應當放在與包名相同的目錄中，這樣生成的字節碼class文件纔會在對應目錄生成。
若源碼均置於同一級目錄，則編譯之後產生的`class`文件需要按照`package`關係放在與包名相同的目錄下，否則執行`class`文件時會報錯(找不到對應的class文件)。

## 引用依賴
引用第三方的`jar`文件，則編譯時應使用`-cp`參數，如下：

```
$ javac -cp [第三方庫的路徑] [源碼文件]
```

編譯生成的class文件無法直接被`java`指令執行(class文件使用了第三方庫，庫的位置不在系統環境變量內)，運行時需要顯式地指定引用庫的位置：

```
$ java -Djava.ext.dirs=[第三方庫所在的目錄] [編譯生成的class文件]
```



# Container (容器)
與常見的編程語言相同，Java中的常見的**容器類型**爲`List`、`Set`、`Map`。

| 容器 | 特點 |
| :- | :- |
| List | 元素**有序**，元素**可重複** |
| Map | 元素按鍵值對存儲，**無序** |
| Set | 元素**無序**，元素**不可重複**(注意：元素雖然無放入順序，但是元素在`Set`中的位置是有該元素的**HashCode**決定的，其位置其實是固定的) |

在Java中，這三種集合類型都是以接口形式存在的，不能直接使用，要使用這三種類型可以使用其實現類：

| 接口 | 實現類 |
| :- | :- |
| List | LinkedList、ArrayList、Vector |
| Set | HashSet、LinkedHashSet |
| Map | HashMap、HashTable、LinkeHashMap |

這些實現類各有優缺點：

- `ArrayList`**非線程安全**，效率**高**。
- `Vector`**線程安全**，效率**低**。
- `HashMap`**非線程安全**，高效，**支持**null。
- `HashTable`**線程安全**，低效，**不支持**null 。

語法：

```java
List<Type> list = new ArrayList<Type>();
list.add(type);
Map<Key, Type>  map = new HashMap<Key, Type>();
map.put(key, type);
```

Java支持泛型`<>`**菱形推斷**，實例化時類型可以省略(`Java 1.7`新特性)，上面的語句實例化可以簡寫爲：

```java
List<Type> list = new ArrayList<>();
Map<Type, Value> map = new HashMap<>();
```

不使用菱形推斷時，集合庫會使用Object類型做爲類型參數：

```java
List list = new ArrayList(); //List<Object>
Map map = new HashMap(); //Map<Object, Object>
```

`Set`和`List`都可以得到一個迭代器用於迭代：

```java
Iterator iteratorList = list.iterator();
Iterator iteratorSet = set.iterator();
```

`Map`的`Key`就是一個`Set`，可以得到`Key`的集合再迭代：

```java
Set set = map.keySet();
Iterator iteratorSet = set.iterator();
```

`Map`使用`get(key)`可以得到對應Key的Value。
`HashMap`之類的容器只能一個鍵對應**一個**鍵值，如果需要一個鍵綁定多個鍵值可以使用`IdentityHashMap`。



# Enum (枚舉)
Java中使用`enum`關鍵字來定義一個枚舉類。

基本的枚舉與`C`語言中的語法類似：

```
enum Enum {
	ENUM_MEMBER_1,
	ENUM_MEMBER_2,
	ENUM_MEMBER_3,
	ENUM_MEMBER_4,
	...
}
```

枚舉是`Java`中少數比`C++`更**複雜**的語法之一：

- `Java`枚舉類中的**枚舉成員**(類內普通成員除外)每一個都是枚舉類的實例。
- 在枚舉類與普通類相似，也可以在類內定義成員方法和成員變量。
- 要在枚舉類內定義成員方法/變量，需要在最後一個枚舉成員成員後添加**分號**以標誌枚舉成員列表結束。
- 在枚舉類內定義的方法/變量每一個枚舉成員都擁有。
- 在枚舉類內自定義構造函數則枚舉成員需要通過自定義的構造函數來構建，參數需要符合構造函數的參數表。
- 枚舉類內的構造函數默認爲`private`訪問權限，且不可更改。
- 枚舉類爲抽象類`java.lang.Enum`的子類，而Java爲單繼承語言，因而枚舉類不能再繼承其它類，只能實現接口。

簡單的自定義枚舉類示例如下：

```java
enum Enum {

	// 定義枚舉成員，以分號做爲結束標誌
	ENUM_MEMBER_1("member1") {
		// 枚舉類成員內可以重寫枚舉類內定義的方法
		@Override
		int index() { return 1; }
	},
	ENUM_MEMBER_2("member2") {
		@Override
		int index() { return 2; }
	},
	ENUM_MEMBER_3("member3") {
		@Override
		int index() { return 3; }
	},
	ENUM_MEMBER_4("member4") {

		@Override
		int index() { return 4; }

		// 枚舉類內可以定義新的方法，但該方法無法被訪問，因而沒有意義
		public int size() { return 4; }
	};

	// 自定義枚舉類的構造函數
	Enum(String name) { this.name = name; }

	String getName() { return name; }

	int index() { return 0; }

	private String name;
}
```



# 對象相等性
Java**不支持**操作符重載，Java中相等性比較運算符`==`的含義如下：

- 對於**原始類型**、`String`類型，==操作符語義爲比較兩個原始類型值是否相等。
- 對於**引用類型**，==操作符用於比較兩個引用指向的實例是否相同。

## equals() 方法
對於引用類型而言，比較兩個對象是否相等應使用`equals()`方法。
equals()方法定義在Object類型中，默認實現默認語義與==操作符相同(引用比較)，需要實現值比較語義的類型應自行重寫equals()方法。

以一個包含3個成員的自定義類型爲例：

```java
public class TestEquals {

	public int num;
	public String str;
	public Xxx xxx;

	@Override
	public boolean equals(Object obj) {
		if (obj == this) return true;
		if (obj != null && obj instanceof TestEquals) {
			TestEquals o = (TestEquals) obj;
			return num == o.num &&
				str == o.str &&
				xxx.equals(o.xxx);
		}
		return false;
	}

}
```

## hashCode() 方法
部分數據結構(如`HashMap`、`HashSet`等)出於性能考慮，會使用對象提供的`hashCode()`方法，根據Hash是否相等判斷對象的異同。
對於重寫了`equals()`方法重寫了比較策略的類型而言，也應重寫`hashCode()`方法。

自定義Hash值的生成規則，確保對象內容相同時得到的Hash值也相同：

```java
public class TestEquals {

	public int num;
	public String str;
	public Xxx xxx;

	...

	@Override
	public int hashCode() {
		return 31 * num +
				(str != null ? str.hashCode() : 0) +
				(xxx != null ? xxx.hashCode() : 0);
	}

}
```

在`Java 7`之後，可直接使用`java.util.Objects`工具類中提供的`hash()`方法：

```java
public class TestEquals {

	public int num;
	public String str;
	public Xxx xxx;

	...

	@Override
	public int hashCode() {
		return Objects.hash(num, str, xxx);
	}

}
```



# 淺複製與深複製
Java中**基礎類型**如`int`、`double`等在複製時進行**值拷貝**，而對於**引用類型**，
則默認拷貝的只是一個對象的**引用**(類似與C/C++中的**指針**)，對象本體**並未**被複制。

## 淺複製
要想讓一個類能夠被複制，則類需要實現`Cloneable`接口，並重寫`clone()`方法。

如下代碼所示：

```java
class TestClone implements Cloneable {

	StringBuffer str = new StringBuffer("str");

	//重寫clone()方法
	@Override
	public TestClone clone() {
		TestClone clone = null;
		try {
			clone = (TestClone) super.clone();
		} catch (CloneNotSupportedException e) {
			e.printStackTrace();
		}
		return clone;
	}
}
```

雖然`clone()`方法來自於根類`Object`，但如果不實現`Cloneable`接口，則在調用`clone()`方法的時候會拋出`CloneNotSupportedException`異常。

編寫代碼測試：

```java
public class Main {
	public static void main(String[] args) {
		TestClone test = new TestClone();
		TestClone testClone = test.clone();
		test.str.append("New");
		System.out.println(testClone.str);
	}
}
```

輸出結果：

```
strNew
```

可以發現調用`clone()`方法複製出的對象**testClone**在原對象**test**被修改後也發生了變化，並未真正的達到**複製**效果。
原因是**TestClone**類完成的僅僅是**淺複製**的過程，類中的引用類型`StringBuffer`並未被真正複製。

## 深複製
深複製一個對象，則需要將類中的每一個引用成員都進行**複製**，因此，**TestCode**的代碼需要改成：

```java
class TestClone implements Cloneable {

	StringBuffer str = new StringBuffer("str");

	@Override
	public TestClone clone() {
		TestClone clone = null;
		try {
			clone = (TestClone) super.clone();
			clone.str = new StringBuffer(str); //構建新的StringBuffer對象
		} catch (CloneNotSupportedException e) {
			e.printStackTrace();
		}
		return clone;
	}
}
```

在重寫`clone()`方法的過程中，要實現**深複製**，就需要重新構造類中的每一個引用類型。
重新構造對象優先使用該引用類型的`clone()`方法(如果該類型實現了`Cloneable`接口)。
如果需要複製的引用類型沒有實現`Cloneable`接口，則直接使用構造函數創建一個與當前實例中保存內容相同的對象。

需要注意的是，`String`類型是**特例**，雖然其爲**引用類型**，但`String`內部重新實現了自身的`clone()`，
在重寫當前類的`clone()`方法的時候可以將其視爲基本類型(即不必顯式構建)。



# 泛型
`Java 1.5`開始引入了汎型機制，定義類型時可為類型添加汎型參數，
擁有汎型參數的類型在初始化時除了提供常規的構造器參數外還需要確定汎型類型。

## 類型擦除
Java語言爲了保證Java Runtime的前向兼容性，采用了類型擦除的方式實現了汎型功能，
Java中的泛型與.Net提供的汎型以及C++的Template機制有本質區別，編譯器不會為使用不同參數汎型類生成不同的代碼。

在編譯成字節碼后汎型會被直接擦除，變爲所有類型的基礎類型`java.lang.Object`類型。
如`List<String>`在運行時汎型類型擦除后會變爲`List<Object>`，等價於Java 1.5之前的無汎型的List。

類型擦除機制實現的泛型導致JVM在運行期間並不能僅通過泛型參數得到該泛型參數對應的類型信息
(例如不能憑藉泛型參數構建對應類型的實例，即無法`new T(...)`)，
額外的泛型參數信息需要顯式地通過參數傳入(`Class<T>`類型)。
其它基於JVM的靜態類型語言針對Java泛型機制的缺陷，都給出了對應的解決方案，
如Scala的`implicit parameters + TypeTag`、Kotlin的`reified`。

基於類型擦除機制實現的泛型還一定程度上限制了其它JVM語言的功能，
如Scala的`Pattern Match`特性(對於類型相同，僅有泛型參數不同的類型不能做到正確匹配)。

## 泛型方法
Java中的泛型同樣支持獨立於類的泛型方法。與`C++`、`C#`等語言不同，
Java在泛型方法中的類型聲明放在方法的修飾符(`public`、`static`、`final`、`abstract`等)之後，返回值聲明之前。

Java中的泛型方法支持自動類型推導。
也可手動顯式指定泛型類型，手動指定泛型類型時，與`C++`、`C#`等語言不同，類型參數寫在方法名稱**之前**。

如下代碼所示：

```java
public class Test {
	public static void main(String[] args) {
		Func t = new Func();
		System.out.println(t.getType(123));
		System.out.println(t.getType("Test"));
		System.out.println(t.<Double>getType(25.672)); //類型參數寫在方法名稱之前
	}
}

class Func {
	public <T> T getType(T t) {
		return t;
	}
}
```

輸出結果：(Windows 10 && JDK 1.8)

```
java
123
Test
25.672
```



# Nested Classes (嵌套類)
嵌套類(`nested class`)是指定義在一個類內部的類，對應的，包含嵌套類的類被稱爲**外部類**(`enclosing class`)。

嵌套類有以下幾種類型：

1. `member nested class`(成員嵌套類)：

	成員嵌套類是作爲`enclosing class`的成員定義的，成員嵌套類有`enclosing class`屬性。
	成員嵌套類可以使用訪問控制符，也可以用`static`、`final`關鍵字修飾。

1. `local nested class`(局部嵌套類)：

	局部嵌套類定義在方法裏面，局部嵌套類有`enclosing class`屬性和`enclosing method`。
	局部嵌套類可以使用`final`關鍵字。

1. `anonymous nested class`(匿名嵌套類)：

	匿名嵌套類沒有顯示的定義一個類，直接通過`new`操作符構造。
	匿名嵌套類不使用任何關鍵字和訪問控制符。

普通嵌套類內部不能定義`static`關鍵字修飾的成員，只有**靜態嵌套類**(`static nested class`)內部才能定義`static`成員。
靜態嵌套類之外的所有嵌套類又被稱爲**內部類**(`inner class`)。
靜態嵌套類只能訪問外部類的靜態成員。

如下代碼所示：

```java
class EnclosingClass {

	// 成員嵌套類
	class MemberNestedClass {

		//static int a; //錯誤，只有靜態嵌套類才能在內部定義靜態成員

	}

	// 使用static關鍵字修飾的成員嵌套類爲靜態嵌套類
	static class StaticMemberNestedClass {

		static int a; //正確，可以正常定義靜態成員

	}

	void showLocalNestedClass() {

		// 局部嵌套類
		class LocalNestedClass {
		}

	}

	// 匿名嵌套類
	XXX xxx = new XXX {
		@Override
		...
	};

}
```



# 併發編程
在Java，常見的併發技術有基本的`Thread`類，以及線程池`Executor`框架。

## Thread / Runnable
使用`Thread`創建線程的兩種方式：

1. `Runnable`接口定義了`run()`方法，實現該接口，將需要併發執行的內容寫在`run()`方法中。
	將實現`Runnable`的實例作爲參數構造`Thread`實例。
1. `Thread`類實現了`Runnable`接口，因此也可以直接繼承`Thread`類重寫其`run()`方法。

完成`Thread`對象的構建後，再調用其成員函數`start()`便會開啓線程執行`run()`中的代碼。

注意事項：

- 啓動線程需要使用`start()`成員方法，調用`run()`無效，代碼依然同步執行。
- `Thread`類只是**一個**線程的抽象，因此在線程啓動後不能再次調用`start()`啓動新線程，啓動新線程需要構建新的`Thread`對象。

示例：

```java
class TestThread extends Thread {
	@Override
	public void run() {
		/* do something */
	}
}

public class Main {

	public static void main(String[] args) {

		Runnable runnable = () -> {
			/* do something */
		}

		// 使用繼承的線程類啓動線程
		new TestThread().start();

		// 使用Runnable實例構造Thread類啓動線程
		new Thread(runnable).start();
	}

}
```

`Thread`類的常用方法：

```java
// 使用指定名稱創建線程
public Thread(Runnable runable, String name);
// 獲取線程對象
public static native Thread currentThread();
// 獲取線程名稱
public final String getName();
// 線程休眠指定毫秒
public static native void sleep(long millis) throws InterruptedException;
```

### Daemon Thread
**守護線程**(Daemon Thread)是一類優先級較低的線程，用於在後台執行一些諸如垃圾收集(GC)等。

相比普通線程，守護線程具有以下特徵：

- 守護線程具有非常低的優先級(an utmost low priority thread)。
- 當所有的用戶線程執行完畢後，守護線程不會阻止JVM退出。
- 當所有的普通線程執行完畢後，JVM會終止；在JVM終止前，若JVM查找到了正在執行的守護線程，
則會終止守護線程，之後終止自身，無論守護線程是否正在執行。

在創建線程時，daemon特性默認關閉，可在構造函數中指定啟用該特性，並可通過Bean方法查看該屬性。
相關定義如下：

```java
public
class Thread implements Runnable {
	...
	/* Whether or not the thread is a daemon thread. */
	private boolean     daemon = false;
	...

	/**
	 * Marks this thread as either a {@linkplain #isDaemon daemon} thread
	 * or a user thread. The Java Virtual Machine exits when the only
	 * threads running are all daemon threads.
	 *
	 * <p> This method must be invoked before the thread is started.
	 *
	 * @param  on
	 *         if {@code true}, marks this thread as a daemon thread
	 *
	 * @throws  IllegalThreadStateException
	 *          if this thread is {@linkplain #isAlive alive}
	 *
	 * @throws  SecurityException
	 *          if {@link #checkAccess} determines that the current
	 *          thread cannot modify this thread
	 */
	public final void setDaemon(boolean on) { ... }

	/**
	 * Tests if this thread is a daemon thread.
	 *
	 * @return  <code>true</code> if this thread is a daemon thread;
	 *          <code>false</code> otherwise.
	 * @see     #setDaemon(boolean)
	 */
	public final boolean isDaemon() {
		return daemon;
	}
	...
}
```

## synchronized & Monitors
`Java 5`之後提供了`synchronized`關鍵字用於解決線程同步問題。

### synchronized語法
`synchronized`關鍵字有兩種用法：

1. `synchronized`塊

	基本語法如下：

	```java
	synchronized (object) {
		/* do something */
	}
	```

	其中，同步變量object可以是實例、this引用或是類型(`XXX.class`)。

	以相同object爲同步對象的多個synchronized塊在同一時刻只能有一個synchronized塊被一個線程執行。
	在該線程離開synchronized塊之前，其餘線程都會處於等待狀態。

	- `object`爲實例時：

		同步變量需要爲**引用類型**(基礎類型如`int`、`float`等不能使用synchronized關鍵字進行同步)。
		同步變量**不能**爲`null`。
		同步變量爲類的實例成員時，需要注意同一個類的不同實例的相同實例成員是不同的。
		同步變量爲類的靜態成員時，一個類的所有實例共享靜態成員，此時效果類似於同步類型(`XXX.class`)。

	- `object`爲`this`引用時：

		同一實例中以`this`爲同步變量的代碼塊同時只能被一個線程執行。
		不同實例之間以`this`爲同步對象的代碼塊無影響。

	- `object`爲類型時，所有以此爲同步變量的代碼塊都只能被一個線程執行。

1. `synchronized`方法

	`synchronized`關鍵字用於修飾方法，語法如下：

	```java
	synchronized Type methodName(Type args...) {
		/* do something */
	}
	```

	被`synchronized`修飾的方法不可重入(同時只能被**一個**線程訪問)：

	- 修飾的方法爲**實例方法**時：

		同一實例的synchronized方法同時只能有一個被執行(不同實例則互不影響)。
		等價於將整個方法體的內容寫在`synchronized (this) { ... }`中。

	- 修飾的方法爲**靜態方法**時：

		所有該類中的靜態synchronized方法同時只能有一個被執行。
		等價於將整個方法體的內容寫在`synchronized (類名.class) { ... }`中。

	一個類中被synchronized修飾的**實例方法**和被synchronized修飾的**靜態方法**的同步對象不同，因而不會相互同步。

	示例：

	```java
	import static java.lang.Thread.sleep;

	class Example {

		private static void show(String name) {
			for (int i = 0; i < 5; i++) {
				String threadName = Thread.currentThread().getName();
				System.out.println(threadName + ": " + name);
				try {
					sleep(100);
				} catch (InterruptedException e) {
					e.printStackTrace();
				}
			}
		}

		public synchronized void showOne() {
			show("showOne()");
		}

		public synchronized void showTwo() {
			show("showTwo()");
		}

		public static synchronized void showStatic() {
			show("showStatic()");
		}
	}

	public class Main {

		public static void main(String[] args) {

			Example example = new Example();

			new Thread(() -> example.showOne(), "Thread One").start();
			new Thread(() -> example.showTwo(), "Thread Two").start();
			new Thread(() -> Example.showStatic(), "Thread Three").start();
		}

	}
	```

	輸出結果：

	```
	Thread One: showOne()
	Thread Three: showStatic()
	Thread One: showOne()
	Thread Three: showStatic()
	Thread One: showOne()
	Thread Three: showStatic()
	Thread Three: showStatic()
	Thread One: showOne()
	Thread One: showOne()
	Thread Three: showStatic()
	Thread Two: showTwo()
	Thread Two: showTwo()
	Thread Two: showTwo()
	Thread Two: showTwo()
	Thread Two: showTwo()
	```

	輸出結果分析：

	`Example`類中的三個成員方法都使用了`synchronized`關鍵字進行修飾。
	`showOne()`、`showTwo()`爲實例方法，`showStatic()`爲靜態方法。

	來自同一個實例在不同線程中的兩個實例方法**沒有**併發執行：`showTwo()`一直等到`showOne()`結束纔開始執行。
	靜態方法與實例方法同步對象不同，正常併發執行：`showOne()`與`showStatic()`交錯打印輸出。

## Executor 框架
`Thread`類功能簡單，僅僅提供了原始的線程抽象，在實際的開發中，往往會使用更高層次的API。

`Java 5`之後提供了`Executor`框架，用於創建、管理與執行線程。
`Executor`框架主要包含`Executor`、`Executors`、`ExecutorService`、`CompletionService`、`Future`、`Callable`等類型。

`Runnable`、`Callable`、`Future`接口是Java中對於異步操作的抽象。

`Runnbale`接口用於表示沒有返回值的異步操作，定義如下：

```java
public interface Runnable {
	void run();
}
```

除了`Runnable`接口是Java早期版本就已包含的之外，其餘的接口/類定義都在`java.util.concurrent`包中。

`Callable`接口用於表示帶有返回值的異步操作。
定義如下：

```java
public interface Callable<V> {
	V call() throws Exception;
}
```

`Future`接口用於表示一個異步操作的結果。
定義如下：

```java
public interface Future<V> {

	// 嘗試取消任務的執行，參數mayInterruptIfRunning表示是否允許中斷，返回是否取消了任務
	boolean cancel(boolean mayInterruptIfRunning);

	// 獲取任務的取消/執行狀態
	boolean isCancelled();
	boolean isDone();

	// 獲取結果
	V get() throws InterruptedException, ExecutionException;
	V get(long timeout, TimeUnit unit)
		throws InterruptedException, ExecutionException, TimeoutException;
}
```

`Executor`接口是框架中最基礎的部分，僅包含一個執行`Runnable`的`execute()`的抽象方法。
定義如下：

```java
public interface Executor {
	void execute(Runnable command);
}
```

`Executor`接口沒有直接子類，但擁有子接口`ExecutorService`。
`ExecutorService`接口定義了一系列終止、提交、跟蹤任務狀態的抽象方法，是整個庫的核心接口。
定義如下：

```java
public interface ExecutorService extends Executor {

	// 關閉ExecutorService，調用後之前已接收的任務繼續執行，但不再接收新的任務
	// 線程池使用完畢需要調用該方法關閉線程池
	void shutdown();

	// 嘗試終止所有正在執行的任務，並終止等待執行的任務並返回這些任務的列表
	List<Runnable> shutdownNow();

	// 返回是否showdown
	boolean isShutdown();

	// 返回shutdown()後所有剩餘任務是否執行完畢
	boolean isTerminated();

	// shutdown()後等待剩餘任務執行一定時間，在指定時間結束後返回所有任務是否執行完畢
	boolean awaitTermination(long timeout, TimeUnit unit) throws InterruptedException;

	// 提交任務，返回該任務的Future，非阻塞
	<T> Future<T> submit(Callable<T> task);
	<T> Future<T> submit(Runnable task, T result);
	Future<?> submit(Runnable task);

	// 執行給定的任務集合，同步等待集合中所有的任務完成，並返回這些任務的Future
	<T> List<Future<T>> invokeAll(Collection<? extends Callable<T>> tasks) throws InterruptedException;
	/*
		執行給定的任務集合，等待指定時間，超過等待時間則終止尚未完成的任務。
		返回給定時間內已完成的任務的Future，若在等待時間結束前所有任務都已完成，則方法提前返回。
	*/
	<T> List<Future<T>> invokeAll(Collection<? extends Callable<T>> tasks,
		long timeout, TimeUnit unit) throws InterruptedException;

	// 執行給定的任務集合，同步等待，直到有任意任務完成時，方法返回該任務的執行結果，同時停止執行其它仍在執行的任務
	<T> T invokeAny(Collection<? extends Callable<T>> tasks)
		throws InterruptedException, ExecutionException;
	/*
		執行給定的任務集合，等待指定時間。
		在指定時間內有任意任務完成，則返回該任務的執行結果，同時停止其它正在執行的任務。
		若沒有任何任務完成則拋出TimeoutException異常。
	*/
	<T> T invokeAny(Collection<? extends Callable<T>> tasks, long timeout, TimeUnit unit)
		throws InterruptedException, ExecutionException, TimeoutException;
}
```

`ExecutorService`接口的實例可以使用工廠類`Executors`中的靜態方法進行創建，常用的一些方法如下：

```java
// 創建固定線程數目的ExecutorService，線程數目決定了同時併發執行的任務數目
public static ExecutorService newFixedThreadPool(int nThreads);

// 創建一個可根據需要創建新線程的ExecutorService，會重用以前可用的線程
public static ExecutorService newCachedThreadPool()；

// 創建一個使用單一工作線程的ExecutorService
public static ExecutorService newSingleThreadExecutor()；

// 創建週期性執行任務的ScheduledExecutorService
public static ScheduledExecutorService newScheduledThreadPool(int corePoolSize);
```

使用`ExecutorService`的基本代碼如下：

```java
public class Main {

	public static void main(String[] args) {

		// 創建併發任務
		Callable<XXX> callable1 = () -> {
			/* do something... */
			return xxx;
		};
		Callable<XXX> callable2 = () -> {
			/* do something... */
			return xxx;
		};
		// create more tasks...

		// 創建線程池
		ExecutorService service = Executors.newCachedThreadPool();

		// 提交任務，獲取結果Future
		List<Future<XXX>> results = new ArrayList();
		results.add(service.submit(callable1));
		results.add(service.submit(callable2));
		// add more tasks...

		// 處理任務結果
		for (Future<XXX> result : results) {
			XXX xxx = result.get();
			/* do something... */
		}

		// 關閉線程池，沒有關閉線程池的操作main函數會一直不返回，程序也不會退出
		service.shutdown();
	}

}
```

使用`ExecutorService`在處理任務返回結果時，有以下缺陷：

- 直接使用`get()`從`Future`中同步獲取返回值需要對任務的執行時間有大致的估算，否則可能造成在某一個執行耗時高的任務中阻塞較長時間。
- 使用`get(long timeout, TimeUnit unit)`限定了等待時間，但任務未必會在限定時間內完成，可能需要多次輪詢才能獲取到所有`Future`的結果。

處理多個任務返回結果應該使用`CompletionService`接口。
`CompletionService`接口定義了將已完成的任務與新提交的任務分離的方法。
定義如下：

```java
public interface CompletionService<V> {

	// 提交任務
	Future<V> submit(Callable<V> task);
	Future<V> submit(Runnable task, V result);

	// 獲取下一個完成的任務的結果Future，若沒有任務完成，則會同步等待直至有任務完成
	Future<V> take() throws InterruptedException;

	// 獲取下一個完成的任務的結果Future，若沒有任務完成，則返回null
	Future<V> poll();

	// 獲取下一個完成的任務的結果Future，若沒有任務，則等待指定時間，指定時間結束後仍沒有任務完成則返回null
	Future<V> poll(long timeout, TimeUnit unit) throws InterruptedException;
}
```

`CompletionService`接口常用的實現類是`ExecutorCompletionService`，可以使用`Executor`實例構建：

```java
public ExecutorCompletionService(Executor executor);
```

使用`ExecutorCompletionService`的基本代碼如下：

```java
public class Main {

	public static void main(String[] args) {

		// 創建併發任務
		Callable<XXX> callable1 = () -> {
			/* do something... */
			return xxx;
		};
		Callable<XXX> callable2 = () -> {
			/* do something... */
			return xxx;
		};
		// create more tasks...

		// 創建線程池
		ExecutorService service = Executors.newCachedThreadPool();

		// 使用ExecutorService構建CompletionService實例
		CompletionService<XXX> completionService = new ExecutorCompletionService(service);

		// 提交任務
		completionService.submit(callable1);
		completionService.submit(callable2);
		// add more tasks...

		// 處理任務結果
		for (int i = 0; i < 任務數量; i++) {
			/*
				使用take()/pull()等方法獲取下一個執行完畢任務結果。
				使用take()方法獲取結果時只要服務中提交的任意任務完成方法就會返回，不必擔心在某一個任務上等待時間過長。
			*/
			XXX xxx = completionService.take().get();
			/* do something... */
		}

		// 關閉線程池，CompletionService一樣需要通過ExecutorService關閉線程池
		service.shutdown();
	}

}
```



# Annotation (註解)
註解(元數據)是`Java 5`之後引入的機制，從`Java 6`開始支持**自定義註解**。

註解可以聲明在**包**、**類**、**字段**、**方法**、**局部變量**、**方法參數**等之前，用來對這些元素進行說明和註釋。
註解的相關內容在包`java.lang.annotation`中。

註解的基本語法爲：

```java
@註解名稱(註解參數...)
```

其中，註解的參數不是必須的，沒有註解參數的註解稱爲**標記註解**。一個元素可以擁有**多個**註解。

## 內置註解
Java中提供了一系列**內置註解**，常用的有：

- `@Override`爲**標記註解**，用於標記**重寫**的方法，若被標記的方法沒有發生重寫行爲，則編譯時會得到錯誤警告。
- `@Deprecated`爲**標記註解**，用於標記**廢棄**的內容，作用與JavaDOC提供的`@deprecated`註解類似。
- `@SuppressWarnings`用於控制編譯時的輸出警告信息，該註解有多個參數，但都帶有默認值。

## 元註解
**元註解**專門用來修飾其它註解，用於**自定義註解**。
**元註解**有以下4類：

1. `@Target`用於限制註解的範圍，參數爲註解範圍的數組(可以同時設定多個註解範圍，用花括號包裹)，取值如下所示：

	- `ElementType.CONSTRUCTOR` 描述構造器
	- `ElementType.FIELD` 描述域
	- `ElementType.LOCAL_VARIABLE` 描述局部變量
	- `ElementType.METHOD` 描述方法
	- `ElementType.PACKAGE` 描述包
	- `ElementType.PARAMETER` 描述參數
	- `ElementType.TYPE` 描述類、接口(包括註解類型)或`enum`聲明

1. `@Retention`設置註解的**生命週期**，取值如下所示：

	- `RetentionPolicy.SOURCE`

		註解在編譯階段丟棄。
		被修飾的註解在編譯結束之後就不再有任何意義，不會寫入字節碼。
		`@Override`、`@SuppressWarnings`屬於此類註解。

	- `RetentionPolicy.CLASS`

		在類加載的時候丟棄註解信息。
		在字節碼文件的處理中有用。註解**默認使用**這種方式。

	- `RetentionPolicy.RUNTIME`

		不丟棄註解信息。
		運行期也保留該註解，可以使用反射機制讀取該註解的信息。
		**自定義註解**通常使用這種方式。

1. `@Inherited`爲**標記註解**，用於設置註解的繼承性：

	被改註解修飾的註解用在類中是**可繼承的**，但類不從它所實現的接口繼承註解，方法並不從它所重載的方法繼承註解。
	對於設置了`@Inherited`和`@Retention`元註解的註解，並且聲明週期設爲`RetentionPolicy.RUNTIME`時，則使用`反射`機制來獲取元素註解，且檢查不到該註解時，會一直沿着繼承樹向上搜索，直到查找到了該註解或到達類繼承結構的頂層。

1. `@Documented`設置在使用`javadoc`生成API時記錄註解信息。
	默認情況下，`javadoc`**不會**記錄註解信息。

## 自定義註解
`Java`中的註解實際上是**接口**(`interface`)。

- 使用`@interface`自定義註解，自定義註解繼承了`java.lang.annotation.Annotation`接口。
- 定義註解時，**不能**繼承其他的註解或接口。
- 定義註解時，每一個方法實際上是定義了一個配置參數。
	方法的名稱就是參數的名稱，返回值類型就是參數的類型。可以通過`default`關鍵字來設置參數**默認值**。
- 定義註解時，使用`value`做爲註解參數名稱，則使用註解時參數名稱可省略。
- 定義註解時，參數的訪問權限只能爲`public`或**默認**權限。
- 註解參數支持的數據類型：
	1. 所有基本數據類型(`int`、`float`、`boolean`、`byte`、`double`、`char`、`long`、`short`)。
	1. `String`類型。
	1. `Class`類型。
	1. `enum`類型。
	1. `Annotation`類型。
	1. 上述類型的**一維**數組。

示例：

```java
import java.lang.annotation.*;

@Inherited
@Target({ ElementType.METHOD, ElementType.TYPE })
@Retention(RetentionPolicy.RUNTIME)
@interface Test {
	String value();
	String test() default "Test";
	int[] numbers() default { 0, 0, 0 };
}

@Test(value = "TestValue", test = "Schwarzes marken", numbers = { 6, 6, 6 })
class A {}

class TestAnnotation extends A {}

public class Main {

	public static void main(String[] args) {
		//註解無需實例，可直接通過Class類獲得
		Test test = TestAnnotation.class.getAnnotation(Test.class);
		System.out.println(test.value() + ": " + test.test() + " " + test.numbers()[0]);
	}

}
```

輸出結果：

```
TestValue: Schwarzes marken 6
```



# Reflection (反射)
在`Java`中，**反射**機制提供了一系列**運行時**功能：

- 判斷任意一個對象所屬的類。
- 構造任意一個類的對象。
- 判斷任意一個類所具有的成員變量和方法。
- 調用任意一個對象的方法。
- 獲取目標的註解信息。
- 生成**動態代理**。

反射在Java各類框架中都有着大量的應用，如`Spring`中的`IOC`。

## 反射機制的相關類型
在`Java`中，反射相關的類型定義在包`java.lang.reflect`中，主要有以下類型：

- `Class` 表示一個類、接口
- `Field` 表示類的成員變量(字段)
- `Method` 表示類的成員方法
- `Constructor` 表示類的構造方法

## Class 類型
`Class`類定義了類型的反射操作，獲取目標類型的`Class`實例是使用反射功能的起始步驟。

獲取`Class`實例可以通過以下方式：

- `Xxx.class` 通過類型的`class`成員獲得
- `Class.forName("class_path")` 通過類型名稱獲得(傳入的類型字符串需要爲完整路徑)
- `instance.getClass()` 通過目標實例的`getClass()`方法獲得

## 反射獲取成員信息
`Java`中反射獲取類型成員信息的相關`API`遵循以下命名規則：

- `getXxx()`用於獲取**指定成員**，搜索範圍爲**公有成員**，包括繼承的成員。
- `getDeclaredXxx()`用於獲取**指定成員**，搜索範圍爲**所有訪問權限成員**，不包括繼承的成員。
- `getXxxs()`用於獲取**所有成員**，搜索範圍爲**公有成員**，包括繼承的成員。
- `getDeclaredXxxs()`用於獲取**所有成員**，搜索範圍爲**所有訪問權限成員**，不包括繼承的成員。

1. 獲取類型**完整路徑**：

	`Class`類型的`getName()`方法返回類型的完整路徑：

	```java
	Xxx.class.getName();
	```

1. 獲取類型的**成員變量**：

	獲取所有成員字段信息：

	```java
	public Field[] getFields() throws SecurityException;
	public Field[] getDeclaredFields() throws SecurityException;
	```

	通過字段名稱獲取指定字段的成員信息：

	```java
	public Field getField(String name) throws NoSuchFieldException, SecurityException;
	public Field getDeclaredField(String name) throws NoSuchFieldException, SecurityException;
	```

1. 獲取類型的**成員方法**：

	獲取所有成員方法信息：

	```java
	public Method[] getMethods() throws SecurityException;
	public Method[] getDeclaredMethods() throws SecurityException;
	```

	獲取指定參數的方法信息，`name`參數爲方法名稱，`parameterTypes`參數爲方法參數類型(變長參數)：

	```java
	public Method getMethod(String name, Class<?>... parameterTypes)
			throws NoSuchMethodException, SecurityException;
	public Method getDeclaredMethod(String name, Class<?>... parameterTypes)
			throws NoSuchMethodException, SecurityException;
	```

1. 獲取類型的**構造方法**

	獲取所有的構造方法信息：

	```java
	// 構造方法不存在繼承關係，getConstructors()/getgetDeclaredConstructors()區別僅在於獲取構造方法的訪問權限不同
	public Constructor<?>[] getConstructors() throws SecurityException;
	public Constructor<?>[] getDeclaredConstructors() throws SecurityException;
	```

	獲取指定參數的構造方法信息，`parameterTypes`參數爲方法參數類型(變長參數)：

	```java
	public Constructor<T> getConstructor(Class<?>... parameterTypes)
			throws NoSuchMethodException, SecurityException;
	public Constructor<T> getDeclaredConstructor(Class<?>... parameterTypes)
			throws NoSuchMethodException, SecurityException;
	```

	內部類獲取外部類的構造方法(非內部類返回`null`)：

	```java
	public Constructor<?> getEnclosingConstructor() throws SecurityException;
	```

示例：

```java
package com.dainslef;

import java.lang.reflect.Constructor;
import java.lang.reflect.Field;
import java.lang.reflect.Method;

class Base {

	public int num = 666;

	public Base() {}

	public int getNum() {
		return num;
	}

}

class Test extends Base {

	public int num0 = 0;
	protected int num1 = 1;
	private int num2 = 2;

	public Test() {}

	private Test(int num0, int num1, int num2) {
		this.num0 = num0;
		this.num1 = num1;
		this.num2 = num2;
	}

	public int getNum0() {
		return num0;
	}

	protected int getNum1() {
		return num1;
	}

	private int getNum2() {
		return num2;
	}

	private void getNum2(int num1, int num2) {
		System.out.println(num1 + " " + num2);
	}
}

public class Main {

	public static void main(String[] args) throws ClassNotFoundException {

		Class classTest = Class.forName("com.dainslef.Test");

		System.out.println("Class Full Name:");
		System.out.print(classTest.getName());

		System.out.println("\n\nPublic Fileds:");
		for (Field field : classTest.getFields())
			System.out.print(field.getName() + " ");

		System.out.println("\n\nAll Fileds: ");
		for (Field field : classTest.getDeclaredFields())
			System.out.print(field.getName() + " ");

		// 獲取到了繼承的方法
		System.out.println("\n\nPublic Methods:");
		for (Method method : classTest.getMethods())
			System.out.print(method.getName() + " ");

		// 獲取內容不包括繼承方法，但包含定義的保護/私有方法
		System.out.println("\n\nAll Methods:");
		for (Method method : classTest.getDeclaredMethods())
			System.out.print(method.getName() + " ");

		// 構造方法不存在繼承的概念，因而只獲取到當前類公有構造器
		System.out.println("\n\nPublic Constructor:");
		for (Constructor constructor : classTest.getConstructors())
			System.out.print(constructor.getName() + " ");

		System.out.println("\n\nAll Constructor:");
		for (Constructor constructor : classTest.getDeclaredConstructors())
			System.out.print(constructor.getName() + " ");

		// 對於非內部類，獲取外部類的構造函數返回null
		System.out.println("\n\nEnclosing Constructor:");
		System.out.println(classTest.getEnclosingConstructor());
	}
}
```

運行輸出結果：

```
Class Full Name:
com.dainslef.Test

Public Fileds:
num0 num

All Fileds:
num0 num1 num2

Public Methods:
getNum0 getNum wait wait wait equals toString hashCode getClass notify notifyAll

All Methods:
getNum0 getNum1 getNum2 getNum2

Public Constructor:
com.dainslef.Test

All Constructor:
com.dainslef.Test com.dainslef.Test

Enclosing Constructor:
null
```

## 反射構建實例
若一個類定義了空參的構造函數，則可以直接通過`Class`類中的成員方法來構造對象。

```java
public T newInstance() throws InstantiationException, IllegalAccessException;
```

`Class`類中沒有直接提供通過**有參構造函數**反射構建實例的方式。
若需要反射調用類的有參構造方法，則需要先獲取其有參構造器(`Constructor`類型)，之後通過`Constructor`類的相關方法構造實例。

通過反射可以實現使用**非公有構造函數**構建對象。

```java
public Constructor<?>[] getDeclaredConstructors() throws SecurityException;
public Constructor<T> getDeclaredConstructor(Class<?>... parameterTypes)
		throws NoSuchMethodException, SecurityException;
```

實例如下代碼所示：

```java
package com.dainslef;

import java.lang.reflect.Constructor;
import java.lang.reflect.InvocationTargetException;

class Test {

	int num = 0;

	public Test() {}

	private Test(int num) {
		this.num = num;
	}

	public void showNum() {
		System.out.println(num);
	}

}

public class Main {

	public static void main(String[] args) throws
			IllegalAccessException,
			InstantiationException,
			NoSuchMethodException,
			InvocationTargetException {

		// 直接通過Class類調用無參構造函數
		Test.class.newInstance().showNum();

		// 獲取構造器對象
		Constructor<Test> constructor = Test.class.getDeclaredConstructor(int.class);
		constructor.setAccessible(true); //對於私有構造器默認是無法訪問的，需要設置權限才能正常調用
		constructor.newInstance(200).showNum();
	}
}
```

輸出結果：

```
0
200
```

## 反射調用對象方法
通過反射可以實現調用任意方法(包括**私有方法**)，方式與調用構造函數基本類似。

首先獲取目標方法的`Method`對象，之後通過Method類的`invoke()`方法執行，第一個參數爲類的實例，之後的參數爲方法簽名中的參數。

```java
public Object invoke(Object var1, Object... var2)
		throws IllegalAccessException, IllegalArgumentException, InvocationTargetException;
```

與`Constructor`類似，如果獲取到的`Method`對象代表的是非公有成員方法，則需要使用`setAccessible()`方法設置屬性爲可訪問才能正常調用。

訪問一個全部成員**私有**的類，如下所示：

```java
package com.dainslef;

import java.lang.reflect.Constructor;
import java.lang.reflect.InvocationTargetException;
import java.lang.reflect.Method;

class Test {

	private int num = 0;

	private Test(int num) {
		this.num = num;
	}

	private void showNum(int num) {
		System.out.println(this.num + num);
	}

}

public class Main {

	public static void main(String[] args) throws
			IllegalAccessException,
			InstantiationException,
			NoSuchMethodException,
			InvocationTargetException {

		Constructor<Test> constructor = Test.class.getDeclaredConstructor(int.class);
		constructor.setAccessible(true); //設置私有構造器可訪問

		Test test = constructor.newInstance(200); //通過私有構造器構造對象，並傳入初值

		Method method = Test.class.getDeclaredMethod("showNum", int.class);
		method.setAccessible(true); //設置方法的訪問權限
		method.invoke(test, 100); //調用私有方法showNum()
	}
}
```

輸出結果：

```
300
```

## 反射修改字段
通過反射亦可訪問、修改類的非公有成員字段，方式類似。

通過`Field`類的相關的`set()`、`get()`方法設置、獲取字段內容：

```java
public void set(Object var1, Object var2) throws IllegalArgumentException, IllegalAccessException;
public Object get(Object var1) throws IllegalArgumentException, IllegalAccessException;
```

- `set()`方法中參數`var1`爲要設置字段所屬的對象，參數`var2`爲設置的內容。
- `get()`方法同名參數作用相同。
- `set()/get()`方法接收的參數爲`Object`類型。

對於基本類型，`Field`類中預先定義了一套方法(`setInt()/getInt()/setBoolean()/getBoolean()`等)，
基本類型可直接使用這些方法以避免不必要的強制類型轉換。

```java
package com.dainslef;

import java.lang.reflect.Constructor;
import java.lang.reflect.Field;
import java.lang.reflect.InvocationTargetException;

class Test {

	private int num = 0;

	private Test(int num) {
		this.num = num;
	}

	private void showNum(int num) {
		System.out.println(this.num + num);
	}

}

public class Main {

	public static void main(String[] args) throws
			IllegalAccessException,
			InstantiationException,
			NoSuchMethodException,
			InvocationTargetException,
			NoSuchFieldException {

		Constructor<Test> constructor = Test.class.getDeclaredConstructor(int.class);
		constructor.setAccessible(true);
		Test test = constructor.newInstance(200);

		Field field = Test.class.getDeclaredField("num");
		field.setAccessible(true);
		System.out.println(field.getInt(test));
		field.set(test, 300);
		System.out.println(field.getInt(test));
	}

}
```

## 反射判定繼承關係
使用`Class`類中的`isAssignableFrom()`成員方法可以判定當前類型是否可以由目標類型轉換得到：

```java
public native boolean isAssignableFrom(Class<?> cls);
```

`isAssignableFrom()`方法對於接口和類都有效，只要類型滿足轉換關係即可，如下所示：

```java
interface A { }

class B implements A { }

class C extends B { }

class Main {
	public static void main(String[] args) {
		System.out.println(A.class.isAssignableFrom(B.class));
		System.out.println(A.class.isAssignableFrom(C.class));
		System.out.println(B.class.isAssignableFrom(C.class));
	}
}
```

輸出結果：

```
true
true
true
```

## ClassLoader (類加載器)
在Java中有三種類加載器。

1. `Bootstrap ClassLoader`引導類加載器，用於加載`Java`核心類。
1. `Extension ClassLoader`擴展類加載器，
它負責加載`JRE`的擴展目錄(`JAVA_HOME/jre/lib/ext`或`java.ext.dirs`系統屬性指定)類包。
1. `App ClassLoader`應用類加載器，通常類都由此加載器加載(包括`java.class.path`)。

獲取一個類的加載器使用`getClassLoader()`方法。

展示一般應用類加載器：

```java
package com.dainslef;

import java.lang.reflect.InvocationTargetException;

class Test {
}

public class Main {

	public static void main(String[] args) throws
			IllegalAccessException,
			InstantiationException,
			NoSuchMethodException,
			InvocationTargetException,
			NoSuchFieldException,
			ClassNotFoundException {

		System.out.println(Main.class.getClassLoader().getClass().getName());
		System.out.println(Class.forName("com.dainslef.Test").getClassLoader().getClass().getName());

	}
}
```

輸出結果：

```
sun.misc.Launcher$AppClassLoader
sun.misc.Launcher$AppClassLoader
```



# 動態代理
**動態代理**是反射機制的一種應用，能夠動態地產生代理實例，避免爲每一個接口方法編寫大量的重複代理代碼。

## 代理模式
**代理模式**是常見的設計模式，主要作用是通過創建**代理類**爲其他對象提供一種代理，並以控制對這個對象的訪問。

代理模式常見的應用場景有：

1. `Remote Proxy`遠程代理，爲一個位於不同的地址空間的對象提供一個本地的代理對象。
這個不同的地址空間可以是在同一臺主機中，也可是在另一臺主機中。
1. `Virtual Proxy`虛擬代理，根據需要創建開銷很大的對象。
若需要創建一個資源消耗較大的對象，先創建一個消耗相對較小的對象來表示，真實對象只在需要時纔會被真正創建。
1. `Protection Proxy`保護代理，控制對原始對象的訪問。保護代理用於對象應該有不同的訪問權限的時候。
1. `Smart Reference`智能指引，取代了簡單的指針，它在訪問對象時執行一些附加操作，擴充原有對象的功能。
1. `Copy-on-Write`寫時複製，它是虛擬代理的一種，把複製操作延遲到只有在客戶端真正需要時才執行。

在Java中代理模式的典型方式是使用接口定義功能，實現類實現接口功能，而代理類控制/擴充實現類功能。
代理類與實現類都實現接口，但代理類本身不直接實現具體功能，而是調用被其代理的實現類的方法。

## 實例
假設有一個文件接口`File`，定義了支持的文件操作：

```java
interface File {
	String getName();
	int getSize();
}
```

`FileImpl`類實現文件接口：

```java
class FileImpl implements File {

	@Override
	public String getName() {
		/*
			Implements code...
		*/
	}

	@Override
	public int getSize() {
		/*
			Implements code...
		*/
	}
}
```

使用靜態代理，則應創建一個**代理類**用於控制之前的實現。
代理類同樣需要實現基礎接口，但代理類不同於實現類，代理類使用別的接口實現類的實現而不是自身實現功能。
代理類在調用實現類功能的同時，也可以加入自身的擴充功能。

實現類以接口的形式被傳入代理類，當一個接口有多種實現的時候，代理類能夠針對每一種實現類都添加相同的功能。
這就是所謂的`AOP`(面向切面編程)，代理類可以被視爲是一個切面。

```java
class FileProxy implements File {

	File file = null;

	public FileProxy(File file) {
		this.file = file;
	}

	@Override
	public String getName() {
		/*
			do something before...
		*/
		String name = file.getName();
		/*
			do something after...
		*/
		return name;
	}

	@Override
	public int getSize() {
		/*
			do something before...
		*/
		int size = file.getName();
		/*
			do something after...
		*/
		return size;
	}
}
```

代理類`FileProxy`能夠在調用實現具體代碼的同時加入擴充的功能。

隨着接口功能的擴充，代理類的代理方法數量也會增加，但代理類中很多方法的擴充代碼可能相同的或是根本沒有擴充代碼，
因而沒有必要針對每一個方法編寫代理方法，此時使用**動態代理**能夠很方便地控制代碼規模。

動態代理使用`java.lang.reflect.Proxy`類中的`newProxyInstance`方法構建代理類實例：

```java
public static Object newProxyInstance(ClassLoader loader,
		Class<?>[] interfaces, InvocationHandler h) throws IllegalArgumentException;
```

- `loader`參數爲動態代理類的類加載器。
- `interfaces`參數爲代理類實現的接口的數組。
- `h`參數爲動態代理的具體內容。

`h`參數的類型爲`InvocationHand`接口，定義如下：

```java
public interface InvocationHandler {
	Object invoke(Object proxy, Method method, Object[] args) throws Throwable;
}
```

- `proxy`參數爲代理類。
- `method`參數爲調用的方法。
- `args`參數爲對調用方法傳入的參數。

需要自行實現`InvocationHandler`接口，來實現動態代理的具體內容。
以上文的`FileImpl`類爲例，使用動態代理實現如下：

```java
class InvocationHandlerImpl implements InvocationHandler {

	File file = null;

	public InvocationHandlerImpl(File file) {
		this.file = file;
	}

	// 多個接口方法的代理擴展代碼全部寫在一個invoke()方法中
	@Override
	public Object invoke(Object proxy, Method method, Object[] args) throws Throwable {

		/*
			do something before...
		*/

		// 判斷是否爲靜態方法，並使用不同的調用方式
		Object object = Modifier.isStatic(method.getModifiers()) ?
				method.invoke(args) : method.invoke(file, args);

		/*
			do something after...
		*/

		return object;
	}
}

public class Main {

	public static void main(String[] args) {

		//類實現
		File fileImpl = new FileImpl();

		//代理規則
		InvocationHandler invocationHandler = new InvocationHandlerImpl(fileImpl);

		//生成動態代理對象
		File file = (File)Proxy.newProxyInstance(fileImpl.getClass().getClassLoader(),
			new Class[] { File.class }, invocationHandler);

		//通過動態代理對象調用方法
		file.getName();
		file.getSize();
	}

}
```



# Default Method (接口默認方法)
從`Java 8`開始，接口中允許定義帶有方法實現的默認方法，在方法前使用關鍵字`default`來區別於普通的抽象方法。

- 一個接口可以定義**多個**默認方法。
- 一個接口也可以只包含**默認方法**而不含有抽象方法。
- 默認方法**不是**靜態方法，可被重寫，不可通過接口名稱直接訪問。
- 默認方法不會強制子類重寫，並且可以像類的成員方法一樣被繼承。

例如：

```java
interface A {
	default void show() { System.out.println("A"); }
	default void showA() { System.out.println("showA"); }
}

class B implements A {
	@Override
	public void show() { System.out.println("B"); }
}

class Main {
	public static void main(String[] args) {
		// A.show(); //編譯錯誤
		B b = new B();
		b.show();
		A a = b;
		a.show();
	}
}
```

輸出結果：

```
B
B
```

由輸出可知，向上轉型後的實例對象調用的是被重寫之後的方法。

當一個類實現了多個帶有相同函數簽名的默認方法的接口，需要重寫引發衝突的默認方法。
示例：

```java
// 接口 Test1 中含有默認方法 int test(int a)
interface Test1 {
	default int test(int a) {
		return a;
	}
}

// 接口 Test2 中也含有默認方法 int test(int a)
interface Test2 {
	default int test(int a) {
		return a;
	}
}

// 類 Test 同時實現接口 Test1 和 Test2
class Test implements Test1, Test2 {
	@Override
	public int abc(int a) {
		......
		return ...
	}
}
```

若需要在重寫的方法中直接使用原接口中某個默認方法的實現，可以使用`父接口名稱.super`關鍵字。
示例：

```java
// 類中的 int test(int a) 方法採用 Test1 接口中的默認方法實現
class Test implements Test1, Test2 {

	@Override
	public int test(int a) {
		return Test1.super.test(a);
	}

}
```

一個類實現多個帶有默認方法的接口，在一定程度上類似於`C++`中的**多重繼承**。



# Lambda
`Java 8`中加入的一個重要的特性爲**Lambda表達式**。

## 實現函數式接口
**Lambda表達式**用於實現**函數式接口**，函數接口是**有且只有一個**抽象方法的接口。

函數式接口可以使用`@FunctionalInterface`註解，被其標註的接口中若含有**多個**抽象方法則無法通過編譯。
示例：

```java
// 編譯報錯
@FunctionalInterface
interface Test {
	void test1();
	int test2(int a);
}
```

編譯報錯，提示：

```
Error: java: Unexpected @FunctionalInterface annotation
	Test is not a functional interface
		multiple non-overriding abstract methods found in interface Test
```

對於**函數接口**，只能帶有一個**抽象方法**，但可以帶有任意數量的**默認方法**。
示例：

```java
// 以下接口定義符合函數接口要求
@FunctionalInterface
interface Test {

	int test1(int a);

	default int test2(int a) {
		return a;
	}

	default int test3(int a) {
		return a;
	}

}
```

Java8之前，實現一個接口，通常使用**匿名類**語法：

```java
@FunctionalInterface
interface Test {
	int test(int a);
}

Test t = new Test() {
	@Override
	public int test(int a) {
		return a;
	}
};
```

Java8之後，可使用Lambda實現函數接口：

```java
Test t = (int a) -> a;
```

## 一般用法
對於一個如下定義的函數：

```java
返回類型 函數名(參數列表) {
	// 函數內容
	return 返回值;
}
```

對應的Lambda表達式格式爲：

```java
(參數列表) -> {
	// 函數內容
	return 返回值;
}
```

如果函數體只有一句表達式，則可以省略大括號，簡寫成：

```java
(參數表) -> 表達式;
```

比如有以下函數定義：

```java
int test(int a) {
	return 2 * a;
}
```

使用Lambda表達式可以寫成：

```java
(a) -> { return 2 * a; };
(a) -> 2 * a; //省略大括號
```

特別的，在參數只有一個時，可以省略括號直接寫成：

```java
a -> 2 * a;
```

Lambda表達式能夠**訪問**外部作用域中的變量。
Java中的Lambda捕獲外部作用域變量時會自動帶有`final`屬性，
因而在Lambda中不能對引用的外部作用域變量進行更改(變量若爲類實例，則類內成員**不受**影響)。

在其它支持Lambda表達式的主流語言中，C#/Scala的Lambda可以修改外部作用域的變量，
C++可以控制外部變量的捕獲方式，對於**引用捕獲**的變量，可以修改其值。

## Method Reference (方法引用)
對於函數接口，還可以將當前類的某個符合方法簽名的方法作爲引用實例化函數接口對象。
例如：

```java
@FunctionalInterface
interface A {
	void get();
}

class B {

	A a = this::test;

	private int test() {
		System.out.println("Test!");
		return 0;
	}

}
```

使用操作符`::`將符合簽名的方法作爲重寫內容構造出接口對象。
接口的成員方法爲公有成員，但若使用方法引用實現接口時，不必考慮被引用方法的訪問限制，
即使是本類的私有成員，一樣可以作爲引用來實現接口，
但如果是重寫接口則必須訪問權限爲`public`(重寫權限必須大於等於原有權限)。
只要**方法簽名**相同(返回值類型可以不同)，可使用抽象方法來作爲引用實現函數接口。

## 標準庫中的函數式接口 (java.util.function)
在`Java 8`中，`java.util.function`包中預定義了一系列的泛型函數接口。

- `*Function`

	Function系列的函數接口表示帶有返回值的函數，類似於**C#**中的`Func`類：

	- `Function<T, R>` 接收兩個泛型參數，`T`表示參數類型，`R`表示返回值類型
	- `BiFunction<T, U, R>` 接收三個泛型參數，`T`、`U`表示參數類型，`R`表示返回值類型

- `*Consumer`

	Consumer系列的函數接口表示無返回值(`void`)的函數，類似於**C#**中的`Action`類型：

	- `Consumer<T>` 接收參數類型作爲泛型參數
	- `BiConsumer<T, U>` 接收兩個泛型參數，均爲參數類型

預定義的函數接口僅包含**單個參數**、**兩個參數**的情形，若需要**三個或以上**參數的函數接口則需自行定義。

由於Java泛型機制的限制，泛型參數不能使用基礎類型(如`int`、`double`等，需要使用對應的包裝類型`Integer`、`Double`)。
爲避免基礎類型裝箱，`java.util.function`包爲基礎類型作爲方法參數的情形提供了對應的預定義接口，如`IntFunction<R>`、`DoubleConsumer`等。

`java.util.function`包中預定義的一系列函數接口只是簡化了函數接口的定義，
Java8中的函數接口**不能**做到類似C#中`Delegate/Func/Action`或Scala中`Function*`那樣直接以函數的語法進行調用。
Java8中的Lambda語法僅僅簡化了實現函數接口的過程，調用函數接口內的方法時仍然需要顯式使用接口中的方法名稱。

示例：

```java
import java.util.function.*;

public class Main {

	public static void main(String[] args) {

		// 實例化函數接口對象
		// 使用 IntFunction<Integer> 代替 Function<Integer, Integer>
		Function<Integer, Integer> function = in -> 2 * in;
		IntFunction<Integer> intFunction = in -> 2 * in;

		// 使用 IntConsumer 代替 Consumer<Integer>
		Consumer<Integer> consumer = in -> System.out.println(in);
		IntConsumer intConsumer = in -> System.out.println(in);

		/*
			使用函數接口對象，仍然需要明確調用函數接口中的方法。
			Function系列的有返回值的接口調用方法apply()
			Consumer系列的無返回值的接口調用方法accept()
		*/
		System.out.println(function.apply(100));
		consumer.accept(200);
	}

}
```



# Process API
Java提供了`java.util.Process`類作爲對進程模型的抽象。
創建進程最簡單的方式是通過`Runtime.getRuntime()`獲取Runtime實例，使用`exec()`相關方法。
相關API如下：

```java
public class Runtime {
	...
	// 執行給定指令
	public Process exec(String command) throws IOException;
	// 在給定的環境變量參數下執行給定指令
	public Process exec(String command, String[] envp) throws IOException;
	// 在給定的環境變量和工作路徑下執行指令
	public Process exec(String command, String[] envp, File dir);
	...
}
```

`Java 5`后還提供了`java.util.ProcessBuilder`類，提供了更加完善的進程參數設定API。

Process類型為抽象類，包含基本進程相關方法：

```java
public abstract class Process {
	...
	// 獲取進程的標準輸出、標準輸入、錯誤輸出
	public abstract OutputStream getOutputStream();
	public abstract InputStream getInputStream();
	public abstract InputStream getErrorStream();

	// 等待進程結束
	public abstract int waitFor() throws InterruptedException;
	// 等待進程指定時間
	public boolean waitFor(long timeout, TimeUnit unit) throws InterruptedException;

	// 獲取進程結束返回值
	public abstract int exitValue();
	// 銷毀進程
	public abstract void destroy();
	// 檢查進程是否存活
	public boolean isAlive();
	...
}
```

JVM啓動進程需要藉助對應平臺的shell：

- Widnows平臺下，使用`cmd.exe`啓動進程：

	```scala
	scala> Runtime.getRuntime().exec("cmd /c xxx")
	res1: Process = java.lang.ProcessImpl@e3c36d
	```

- Linux/macOS平臺下使用`bash`或其他已安裝的shell啓動進程：

	```scala
	scala> Runtime.getRuntime().exec("bash -c xxx")
	res2: Process = java.lang.ProcessImpl@2fca282c
	```

JVM啓動的子進程后不會阻塞當前環境，子進程的運行與父進程無關。
需要注意，默認配置下，子進程啓動后會將標準輸出寫入輸出流，輸出流中的内容需要及時取出，
否則當輸出流的緩衝區被填滿后會造成子進程**阻塞**。

亦可在啓動進程時通過重定向標準輸出，以此避免標準/錯誤輸出内容被寫入輸出流中：

```scala
scala> Runtime.getRuntime().exec("cmd /c xxx > xxx.txt")
res1: Process = java.lang.ProcessImpl@e3c36d
```



# DateTime API
Java語言中提供了兩組時間相關API：

| API | 精確度 | 說明 |
| :- | :- | :- | :- |
| java.util.Date | 毫秒 | `JDK 1.1`時代就引入的時間API，功能簡單，缺點眾多，並且非線程安全 |
| java.time.LocalDateTime | 納秒 | `Java8`中引入的新一代時間API，功能強大，改進了舊API的諸多缺點，線程安全 |

## java.util.Date
舊的Date API簡單用法示例：

```java
import java.text.DateFormat;
import java.text.SimpleDateFormat;
import java.util.Date;

// 定義時間格式
DateFormat dateFormat = new SimpleDateFormat("Date Pattern...");

// 從文本轉化為時間
Date time = dateFormat.parse("Time String...");

// 將時間格式化為可讀文本
String timeString = dateFormat.format(time);

// 時間比較
Date time1 = ..., time2 = ...;
time1.before(time2); // boolean
time1.after(time2); // boolean
time1.compareTo(time2); // 返回值：0 => 時間相等，1 => 時間1 大於 時間2，-1 => 時間1小於時間2
```

## java.time.LocalDateTime
DateTime API的基本用法類似Date API，示例：

```java
import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;

// 定義時間格式
DateTimeFormatter dateTimeFormatter = DateTimeFormatter.ofPattern("Date Pattern...");

// 從文本轉換為時間
LocalDateTime time = LocalDateTime.parse("Time String...", dateTimeFormatter);

// 從時間轉換為文本
String timeString = time.format(dateTimeFormatter);

// 時間比較
LocalDateTime time1 = ..., time2 = ...;
time1.isAfter(time2);
time1.isBefore(time2);
time1.isEqual(time2);
```

使用Duration API可以獲取兩個時間的差值：

```java
import java.time.Duration;
import java.time.LocalDateTime;

LocalDateTime time1 = ..., time2 = ...;
Duration duration = Duration.between(time1, time2);
duration.getSeconds(); // 獲取時間間隔的秒部分
duration.getNano(); // 獲取時間間隔的納秒部分

// 將時間間隔轉換為其它單位
duration.toDays();
duration.toHours();
duration.toMinutes();
duration.toMillis();

import java.time.temporal.ChronoUnit;

// 需要特定格式的時間差值亦可直接使用 ChronoUnit 枚舉中提供的對應實例
ChronoUnit.MILLIS.between(time1, time2);
ChronoUnit.SECONDS.between(time1, time2);
ChronoUnit.MINUTES.between(time1, time2);
... // 其它單位如 HOURS、DAYS 等類似
```

### LocalDateTime處理日期
在Date Pattern為日期的情況下，直接使用LocalDateTime進行parse會得到異常信息：

```java
DateTimeFormatter formatter = DateTimeFormatter.ofPattern("yyyyMMdd");
LocalDateTime time = LocalDateTime.parse("20140218", formatter);

// exception stack info
Exception in thread "main" java.time.format.DateTimeParseException:
Text '20140218' could not be parsed:
Unable to obtain LocalDateTime from TemporalAccessor:
{},ISO resolved to 2014-02-18 of type java.time.format.Parsed
	at java.time.format.DateTimeFormatter.createError(DateTimeFormatter.java:1918)
	at java.time.format.DateTimeFormatter.parse(DateTimeFormatter.java:1853)
	at java.time.LocalDateTime.parse(LocalDateTime.java:492)
```

原因是LocalDateTime類型不能接收一個純日期時間，正確的做法是使用LocalDate類型處理日期，之後在轉換為LocalDateTime：

```java
DateTimeFormatter formatter = DateTimeFormatter.ofPattern("yyyyMMdd");
LocalDateTime time = LocalDate.parse("20140218", formatter).atStartOfDay();
```

類似問題可參考[StackOverflow](https://stackoverflow.com/questions/27454025/unable-to-obtain-localdatetime-from-temporalaccessor-when-parsing-localdatetime)上的相關討論。

### 關於 Oracle JDK 8 在 yyyyMMddHHmmssSSS 時間格式下的 DateTimeParseException
在`Oracle JDK 8`中，若使用的時間格式化文本為`yyyyMMddHHmmssSSS`，則會得到異常信息：

```java
DateTimeFormatter.ofPattern("yyyyMMddHHmmssSSS").parse("20180301050630663");

// exception stack info
Exception in thread "main" java.time.format.DateTimeParseException: Text '20180301050630663' could not be parsed at index 0
	at java.time.format.DateTimeFormatter.parseResolved0(DateTimeFormatter.java:1947)
	at java.time.format.DateTimeFormatter.parse(DateTimeFormatter.java:1849)
	at java.time.LocalDateTime.parse(LocalDateTime.java:492)
	...
```

該BUG是Oracle JDK 8自身的BUG，收錄在[甲骨文官方BUG數據庫(JDK-8031085)](https://bugs.java.com/bugdatabase/view_bug.do?bug_id=JDK-8031085)中，
在`Oracle JDK 9`中已經得到修復。

在不切換JDK版本的前提下繞開此BUG可以採用自定義DateTimeFormatter的方式，
手動使用`DateTimeFormatterBuilder`構建DateTimeFormatter：

```java
new DateTimeFormatterBuilder()
	.appendPattern("yyyyMMddHHmmss")
	.appendValue(ChronoField.MILLI_OF_SECOND, 3)
	.toFormatter();
```

## java.time.Instant
`Instant`類型提供了時間戳與Java新老時間API(LocalDateTime/Date)相關類型的轉換。
該類型可作為新老時間API轉換的中間類型。

`java.util.Date`類型與Instant類型相互轉換：

```java
Date date = ...;
Instant instant = date.toInstant();
Date newDate = Date.from(instant);
```

`java.time.LocalDateTime`類型與Instant類型相互轉換：

```java
LocalDateTime dateTime = ...;
Instant instant = dateTime.toInstant(ZoneOffset...); // 使用對應時區的偏移量
Instant instant = Instant.from(dateTime); // 要求DateTime時間帶有時區信息
LocalDateTime dateTime = LocalDateTime.ofInstant(Instant.now(), ZoneId.systemDefault());
```

通過Instant類型與時間戳相互轉換：

```java
// 從各類時間戳轉換到Instant
Instant instant = Instant.ofEpochSecond(epochSecond...); // 從Unix時間戳(秒)轉換到Instant
Instant instant = Instant.ofEpochMilli(epochMilli...); // 從Java Date時間戳(微秒)轉換到Instant
```

### Caused by: java.time.DateTimeException: Unable to obtain LocalDate from TemporalAccessor: 2020-05-14T03:08:24.322080Z of type java.time.Instant#
使用`LocalDateTime.from()`方法從Instant類型構建LocalDateTime時間時得到該異常信息：

```scala
scala> LocalDateTime.from(Instant.now)
java.time.DateTimeException: Unable to obtain LocalDateTime from TemporalAccessor: 2020-05-14T03:16:35.676532Z of type java.time.Instant
  at java.base/java.time.LocalDateTime.from(LocalDateTime.java:461)
  ... 28 elided
Caused by: java.time.DateTimeException: Unable to obtain LocalDate from TemporalAccessor: 2020-05-14T03:16:35.676532Z of type java.time.Instant
  at java.base/java.time.LocalDate.from(LocalDate.java:396)
  at java.base/java.time.LocalDateTime.from(LocalDateTime.java:456)
  ... 28 more
```

通過查閱源碼得知，雖然Instant類型實現了TemporalAccessor接口，但該方法本身只提供了*DateTime相關類型的轉換功能，
並不能轉換所有實現TemporalAccessor的類型。

相關源碼段如下：(摘取自 OpenJDK 1.8.0_242)

```java
public final class LocalDateTime
		implements Temporal, TemporalAdjuster, ChronoLocalDateTime<LocalDate>, Serializable {
	...
	public static LocalDateTime from(TemporalAccessor temporal) {
		if (temporal instanceof LocalDateTime) {
			return (LocalDateTime) temporal;
		} else if (temporal instanceof ZonedDateTime) {
			return ((ZonedDateTime) temporal).toLocalDateTime();
		} else if (temporal instanceof OffsetDateTime) {
			return ((OffsetDateTime) temporal).toLocalDateTime();
		}
		try {
			LocalDate date = LocalDate.from(temporal);
			LocalTime time = LocalTime.from(temporal);
			return new LocalDateTime(date, time);
		} catch (DateTimeException ex) {
			throw new DateTimeException("Unable to obtain LocalDateTime from TemporalAccessor: " +
					temporal + " of type " + temporal.getClass().getName(), ex);
		}
	}
	...
}
```

### Caused by: java.time.temporal.UnsupportedTemporalTypeException: Unsupported field: InstantSeconds
使用`Instant.from()`方法轉換LocalDateTime時要求對應的LocalDateTime時間帶有時區信息，否則會得到該異常：

```scala
scala> Instant.from(LocalDateTime.now)
java.time.DateTimeException: Unable to obtain Instant from TemporalAccessor: 2020-05-14T10:29:06.130812 of type java.time.LocalDateTime
  at java.base/java.time.Instant.from(Instant.java:378)
  ... 28 elided
Caused by: java.time.temporal.UnsupportedTemporalTypeException: Unsupported field: InstantSeconds
  at java.base/java.time.LocalDate.get0(LocalDate.java:708)
  at java.base/java.time.LocalDate.getLong(LocalDate.java:687)
  at java.base/java.time.LocalDateTime.getLong(LocalDateTime.java:720)
  at java.base/java.time.Instant.from(Instant.java:373)
  ... 28 more
```

為時間附加時區信息：

```java
LocalDateTime dateTime = ...;
Instant instant = Instant.from(dateTime.atZone(ZoneId.systemDefault()));
```

若時間由格式化得到，則可在構建DateTimeFormatter時添加時區信息：

```java
DateTimeFormatter formatter = DateTimeFormatter.ofPattern(...).withZone(ZoneId.systemDefault());
Instant instant = Instant.from(formatter.parse(...));
```

類似問題可參考[Stack Overflow](https://stackoverflow.com/questions/35610597/parse-string-timestamp-to-instant-throws-unsupported-field-instantseconds)中的對應提問。



# 定時任務
Java中內置了基於線程的任務調度API，包括早期的`java.util.Timer`，
以及`Java 5 (JDK 1.5)`之後引入的基於Executor的`java.util.concurrent.ScheduledThreadPoolExecutor`。

## Timer API
`java.util`包中提供了Timer相關API，用於在一個後端線程中調度任務，支持任務的定時執行、重複執行等功能。

Timer API包括兩個類：

- `java.util.Timer` 提供任務調度功能
- `java.util.TimerTask` 用於封裝被調度的任務邏輯

相關內容可參考[Baeldung博客](https://www.baeldung.com/java-timer-and-timertask)
或[Oracle官方文檔](https://docs.oracle.com/javase/7/docs/api/java/util/Timer.html)。

### Timer任務調度
在Timer API中任務使用`java.util.TimerTask`類型表示，TimerTask定義如下：

```java
public abstract class TimerTask implements Runnable {
	...
	// 需要被重寫的抽象方法
	public abstract void run();

	// 取消本定時任務，對於僅執行一次的定時任務無需調用此方法
	// 重複執行的定時任務在調用此方法後該任務不再會被執行
	public boolean cancel() { ... }
	...
}
```

TimerTask是**抽象類**，主要API包括抽象方法`run()`(用於重寫提供自訂義的任務行為)；
以及`cancel()`(用於在任務執行完畢後取消調度)。

調度器由`java.util.Timer`類型提供，Timer定義如下：

```java
public class Timer {

	// 定時任務隊列，定時任務線程共享該數據結構，
	// Timer通過各類調度方法添加任務到隊列中，再由定時任務執行線程執行
	private final TaskQueue queue = new TaskQueue();

	// 定時任務執行線程
	private final TimerThread thread = new TimerThread(queue);
	...
	// 構造定時器時可設置執行線程的一些屬性
	public Timer(boolean isDaemon) { ... }
	...
	// 調度任務，在指定延遲時間後執行一次
	public void schedule(TimerTask task, long delay) { ... }
	// 調度任務，在指定延遲後以指定間隔循環執行
	public void schedule(TimerTask task, long delay, long period) { ... }
	// 調度任務，保證重複任務的執行速率
	public void scheduleAtFixedRate(TimerTask task, long delay, long period) { ... }
	...
}
```

Timer類在內部維護一個任務隊列`TaskQueue`和任務線程`TimerThread`，
使用調度`schedule()/scheduleAtFixedRate()`相關方法啟動調度任務，
使用`purge()`清理執行完成隊列任務，使用`cancel()`停止整個定時器。

Timer API的使用例子：

```kt
import java.util.*
import kotlin.concurrent.timerTask

import org.junit.Test

class TestTimer {

	@Test
	fun testTimer() {

		// 創建Timer
		val timer = Timer(true)

		// 重寫run()方法，創建TimerTask
		val timerTask1 = object: TimerTask() {
			var executeCount = 0
			override fun run() {
				println("Timer Task 1 ...")
				executeCount += 1
				if (executeCount >= 3) cancel() // 取消Task的執行
			}
		}
		// Kotlin提供了對TimerTask的封裝函數
		val timerTask2 = timerTask {
			println("Timer Task 2 ...")
		}

		// 調度任務
		timer.scheduleAtFixedRate(timerTask1, 0, 1000) // 重複執行
		timer.schedule(timerTask2, 1000) // 僅調度一次

		readLine()
		timer.cancel() // 取消定時器
	}

}
```

執行結果：

```
Timer Task 1 ...
Timer Task 1 ...
Timer Task 2 ...
Timer Task 1 ...
```

### java.lang.IllegalStateException: Timer already cancelled.
Timer調度器是**單線程**的，實際上僅存在**一個**任務執行線程(TimerThread)。
當執行的TimerTask中拋出InterruptedException以外的異常，
會導致任務執行線程崩潰，進而使得整個Timer無法正常工作。

相關源碼參見(摘取自JDK 1.8)：

```java
/**
 * TimerThread類繼承自線程類Thread，在一個獨立的線程中，從任務隊列中等待、提取任務；
 * 在設定的時間執行任務，重新調度重複任務，從隊列中移除被取消和非重複的任務
 */
class TimerThread extends Thread {

	// 標記是否存在剩餘未被執行的任務
	boolean newTasksMayBeScheduled = true;

	// Timer的任務隊列
	private TaskQueue queue;

	TimerThread(TaskQueue queue) {
		this.queue = queue;
	}

	public void run() {
		try {
			mainLoop();
		} finally {
			// 因為某些原因線程被殺死時，表現為Timer被取消
			synchronized(queue) {
				newTasksMayBeScheduled = false;
				queue.clear();  // 清除廢棄的引用
			}
		}
	}

	// 主循環
	private void mainLoop() {
		while (true) {
			try {
				TimerTask task;
				boolean taskFired;
				synchronized(queue) {
					// 等待隊列變為非空
					while (queue.isEmpty() && newTasksMayBeScheduled)
						queue.wait();
					if (queue.isEmpty())
						break; // 任務隊列為空則說明會導致死循環
					... // 任務調度時間相關計算邏輯，省略
				}
				if (taskFired)  // 任務到達執行時間，在不持有鎖的情況下執行任務
					task.run();
			} catch(InterruptedException e) {
			}
		}
	}
}
```

由源碼可知，主循環mainLoop()方法中在TimerTask執行時僅捕獲了InterruptedException這一種異常，
其它任意種類的TimerTask異常均會造成mainLoop()方法的崩潰退出。
在TimerThread的run()方法中，mainLoop()方法中斷後將Timer按照取消處理。



# JDBC
`JDBC`爲Java定義了一套公用的數據庫API，JDBC屏蔽了不同數據庫之間的差異。
對於支持JDBC的數據庫，只要導入對應的`JDBC Driver`即可使用相同的`JDBC API`進行操作。

## 連接數據庫
`JDBC API`相關類型位於`java.sql`包中：

- `DriverManager` JDBC驅動集合
- `Connection` 數據庫連接
- `Statement` 數據庫交互對象，用於執行各類SQL語句
- `PreparedStatement/CallableStatement` 包含擴展功能的數據庫交互對象
- `ResultSet` 包含查詢結果的集合

基本的訪問數據庫流程：

```java
String connectUrl = "jdbc:數據庫類型://連接地址...";

try {
	Connection connection = DriverManager.getConnection(connectUrl); //獲取數據庫連接
	Statement statement = connection.createStatement()
} catch (SQLException ex) {
	...
}
```

## 數據庫操作
`Statement`類性提供了執行SQL語句的方法：

```java
// 執行查詢語句並返回查詢結果集
ResultSet executeQuery(String sql) throws SQLException;
// 執行更新語句並返回更新的數目
int executeUpdate(String sql) throws SQLException;
```

查詢結果返回的結果集`ResultSet`，常用方法：

```java
// 將光標移動到正好位於第一行之前
public void beforeFirst() throws SQLException;
// 將光標移動到剛剛結束的最後一行
public void afterLast() throws SQLException;
// 將光標移動到第一行
public boolean first() throws SQLException;
// 將光標移動到最後一行
public void last() throws SQLException;
// 將光標移動到指定的行
public boolean absolute(int row) throws SQLException;
// 從它目前所指向向前或向後移動光標行的給定數量
public boolean relative(int row) throws SQLException;
// 將光標移動到上一行，上一行關閉的結果集此方法返回false
public boolean previous() throws SQLException;
// 將光標移動到下一行，如果沒有更多的行結果集中的此方法返回false
public boolean next() throws SQLException;
// 返回的行號，該光標指向的行
public int getRow() throws SQLException;
// 將光標移動到一個特殊的行，可以用來插入新行插入到數據庫中的結果集，當前光標位置被記住
public void moveToInsertRow() throws SQLException;
// 移動光標返回到當前行，如果光標在當前插入行，否則，這個方法不執行任何操作
public void moveToCurrentRow() throws SQLException;
```

基本操作如下所示：

```java
ResultSet resultSet = statement.executeQuery("SQL查詢語句...");
while (resultSet.next()) { // 使用 next() 方法將當前遊標移動到下一行
	resultSet.getInt(...); // 獲取數據，支持使用列號/列名進行獲取
	resultSet.getString(...);
}
```

## 獲取時間
`ResultSet`類型提供了以下方法用於獲取時間類型(如`MySQL`中的`DateTime`)信息：

- `getDate()` 獲取日期信息
- `getTime()` 獲取時間信息
- `getTimestamp()` 獲取完整時間信息

對於時間類型的數據，使用`getDate()`、`getTime()`等方法獲取到的時間信息不完整：

- `getDate()`獲取到的僅爲日期信息，小時、分鐘、秒等信息被置爲默認(`00:00:00`)。
- `getTime()`獲取到的時間信息不包含日期，日期部分被置爲默認(`1970-1-1`)

使用`getTimestamp()`方法才能獲取到完整的時間信息。

## 與 Access 數據庫交互
`JDK 1.7`之前，可以使用`JDBC-ODBC`橋接`Access`數據庫。
在`JDK 1.8`之後，`JDBC-ODBC`橋被移除，只能使用專有的Access驅動來連接Access數據庫(驅動名稱：`Access_JDBC40.jar`)。

連接Access數據庫：

```java
// 使用相對路徑
String connectUrl = "jdbc:Access:///***.accdb";

// 使用絕對路徑
// String connectUrl = "jdbc:Access:///c:/a/b/***.accdb";

// 註冊驅動
Class.forName("com.hxtt.sql.access.AccessDriver");
// 創建連接
Connection connection = DriverManager.getConnection(connectUrl);
Statement statement = connection
	.createStatement(
		ResultSet.TYPE_SCROLL_INSENSITIVE,
		ResultSet.CONCUR_READ_ONLY);
		//後兩個參數是爲了得到resultSet集能夠進行last()操作
```

Access數據庫的一些小常識：

- 表單的高級字段設置在`開始 - 視圖 - 設計視圖`中。
- 配置自增屬性需要將字段類型設爲`自動編號`。
- 默認情況下，創建的數據類型`數字`的字段大小爲`長整型`。
長整型不支持**小數輸入**，小數輸入會自動被去尾。
需要將字段大小設置爲`單精度浮點型/雙精度浮點型`才能支持小數位。
- 如果需要某個字段的內容唯一不可重複，可以將改字段的索引設置爲`有(無重複)`即可。

## com.mysql.jdbc.MysqlDataTruncation: Data truncation: Data too long for column 'column_name'
MySQL的JDBC驅動默認開啟了`jdbcCompliantTruncation`功能，
該特性會使得在數據被要求截斷(truncate)時拋出`com.mysql.jdbc.MysqlDataTruncation`異常。

在JDBC連接字符串中添加`jdbcCompliantTruncation=false`可關閉該功能，
但若MySQL服務端配置中啟用了sqlmode特性`STRICT_TRANS_TABLES`，則該JDBC功能無效。

更多MySQL JDBC Driver的連接參數，可參考[官方文檔](https://dev.mysql.com/doc/connector-j/8.0/en/connector-j-reference-configuration-properties.html)。



# Eclipse 使用註記
`Eclipse`是Java開發中最常用的IDE，Eclipse通過插件擴展可以進行多種語言的開發。

## Marketplace
`Eclipse Marketplace`是Eclipse新增的應用商店，
可以從中直接安裝`e(fx)clipse`、`GoClipse`、`ScalaIDE`、`PyDev`等由第三方社區維護的插件。

在部分Eclipse版本中，Marketplace沒有默認安裝，手動添加：

`Help` =>
`Install New Software` =>
`General Purpose Tools` =>
`Marketplace Client`

## 查看源碼
與**NetBeans**不同，Eclipse默認無法直接查看JDK中類庫源碼，需要手動指定源碼的位置。
通常JDK源碼位於JDK的安裝目錄下的`src.zip`文件中。

在Eclipse中按以下步驟添加源碼路徑：

`Window` =>
`Preferences` =>
`Java` =>
`Installed JREs` =>
選中使用的`JRE` =>
`Edit` =>
選中`../xxx/rt.jar` =>
`Source Attachment Configuration` =>
`Exernal location` =>
選中`src.zip` =>
`OK` =>
`Finish`

## 編輯器自動換行
Eclipse的編輯器沒有自動換行的功能，該功能需要通過第三方插件進行實現。
在Eclipse中按以下步驟安裝`Word Wrap`插件使編輯器能夠自動換行：

`Help` =>
`Install New Software` =>
`Add Repository` =>
輸入倉庫地址`http://ahtik.com/eclipse-update` =>
安裝`WordWrap`插件 =>
安裝完成之後重啓IDE =>
編輯器中點右鍵，激活`Word Warp`選項 =>
`Finish`



# IntelliJ IDEA 使用註記
`IntelliJ IDEA`相比`Eclipse`而言，有着更精美的UI，更智能的代碼提示，且對`Scala`、`Golang`等冷門語言有着更好的支持。

## 顯示行號和不可見空白
選擇選項：

`File` => `Settings` => `Editor` => `General` => `Appearance`

| 選項名稱 | 含義 |
| :- | :- |
| Show whitespaces | 顯示空白 |
| Show line numbers | 顯示行號 |
| Show method separators | 顯示方法分界線 |

## 字段類型推斷、參數名稱提示
選擇選項：

`File` => `Settings` => `Editor` => `General` => `Appearance`

| 選項名稱 | 含義 |
| :- | :- |
| Show external annotations inline | 顯示Java/Kotlin的參數名稱提示 |
| Show inferred annotations inline | 顯示Java/Kotlin的變量類型推斷 |
| Show function return type hints (Scala) | 顯示Scala方法返回類型推斷 |
| Show property type hints (Scala) | 顯示Scala字段類型推斷 |
| Show local variable type hints (Scala) | 顯示Scala本地變量 |

## 列邊界提示
列寬邊界線用於提示代碼單行長度是否超過界限。
選擇選項：

`File` => `Settings` => `Editor` => `Code Style` => `Default Options` => `Right margin (columns)`

默認列邊界線爲`120`列，而大部分編碼規範要求一行不能超過`80/100`列。

## 縮進
默認情況下，IDEA使用的是**空格**做爲縮進，如果需要使用**tab縮進**，則按以下菜單路徑設置：

`File` => `Settings` => `Editor` => `Code Style` => `[目標語言]` => `Tabs and Indents`

- 選中`Use tab charactor`。
- 勾選`Smart tabs`則會在**行尾**使用tab鍵時使用**空格**代替`Tab`。
- 勾選`Keep indents on empyt lines`則會在**空行**中**保持縮進**。

## 包路徑摺疊
默認側邊欄`Project`導航中的包內無源碼且僅包含一個子包時，包路徑會摺疊顯示。
摺疊顯示包路徑更加簡潔，但不能在包路徑中添加其它包。

關閉摺疊顯示可點擊`Project`導航中的設置按鈕，取消選中`Flatten Packages`選項。

## 其它常用選項
通用編輯器選項 `File` => `Settings` => `Editor` => `General`：

| 選項名稱 | 含義 |
| :- | :- |
| Code Folding | 代碼摺疊 |
| Soft Wraps | 代碼自動換行 |
| Appearance => Show right margin | 設置代碼邊界指示線 |
| Virtual Space | 虛空格(空白處的點按邏輯) |
| Other => Show quick documentation on mouse move | 光標懸停顯示變量/方法信息 |

代碼風格選項 `File` => `Settings` => `Editor` => `Code Style`：

| 選項名稱 | 含義 |
| :- | :- |
| Java => Spaces => After type cast | Java強制類型轉換前是否空格 |
| Scala => Other => Enfore procedure syntax for methods with Unit return type | Scala函數是否自動補全空返回類型 |
| Scala => Wrappings and Braces => Class definition => Place self type on new line | Scala自身類型參數在類定義中是否另起一行 |
| [目標語言] => Wrappings and Braces => Method parenttheses => Align when multiline | 函數多行參數是否自動對齊到函數名 |
| [目標語言] => Blank Lines => Minimum Blank Lines | 方法、字段前空行數量 |

設置是否開啓拼寫檢查 `File` => `Settings` => `Project` => `Inspections` => `Spelling`

關閉代碼重複性檢測 `File` => `Settings` => `Project` => `Inspections` => `Genernal` => `Duplicated code fragment`

設置JavaScript支持ES6語法 `File` => `Settings` => `Languages & Frameworks` => `JavaScript` => `JavaScript language version` => `ECMAScript 6`

## 項目打包
將Java項目打包成`jar`、`war`等分發格式，按以下菜單路徑設置：

`File` => `Project Structure` => `Project Settings` => `Artifacts`

選擇界面中的`+`符號添加打包配置，根據項目類型打包成不同的目標格式。

## 多模塊項目
Idea中一個項目被稱爲`Project`，項目中可包含多個子模塊(`Module`)。
當一個項目中需要包含多個子項目時，可以創建多個Module。
每個Module管理獨立的源碼，Module擁有獨立的依賴關係，並可以依賴其它Module。

Idea中的`Project`類似於Eclipse中的`WorkSpace`，Idea中的`Module`類似於Eclipse中的`Project`。

創建新的`Module`時，新的源碼目錄會被默認添加至主模塊中，會導致修改子模塊的依賴關係時出現錯誤：

```
Module "xxx" must not contain source root "xxx". The root already belongs to module "xxx".
```

解決此錯誤需要修改項目主模塊配置，路徑爲`項目路徑/.idea/modules/項目名稱.iml`，如下所示：

```xml
<?xml version="1.0" encoding="UTF-8"?>
<module external.linked.project.id="Xxx" external.linked.project.path="$MODULE_DIR$/../.." external.root.project.path="$MODULE_DIR$/../.." external.system.id="SBT" type="JAVA_MODULE" version="4">
	<component name="NewModuleRootManager" LANGUAGE_LEVEL="JDK_1_8">

		<output url="file://$MODULE_DIR$/../../target/scala-2.12/classes" />
		<output-test url="file://$MODULE_DIR$/../../target/scala-2.12/test-classes" />
		<exclude-output />
		<content url="file://$MODULE_DIR$/../..">

		<!-- 子模塊源碼目錄被包含 -->
		<sourceFolder url="file://$MODULE_DIR$/../../Common/src" isTestSource="false" />
		<sourceFolder url="file://$MODULE_DIR$/../../ExcelConverter/src" isTestSource="false" />
		<sourceFolder url="file://$MODULE_DIR$/../../ReportGenerator/src" isTestSource="false" />

		...

		<sourceFolder url="file://$MODULE_DIR$/../../src/main/java" isTestSource="false" />
		<sourceFolder url="file://$MODULE_DIR$/../../src/main/scala" isTestSource="false" />
		<sourceFolder url="file://$MODULE_DIR$/../../src/main/scala-2.12" isTestSource="false" />
		<sourceFolder url="file://$MODULE_DIR$/../../src/test/java" isTestSource="true" />
		<sourceFolder url="file://$MODULE_DIR$/../../src/test/scala" isTestSource="true" />
		<sourceFolder url="file://$MODULE_DIR$/../../src/test/scala-2.12" isTestSource="true" />

		...

		</content>
		<orderEntry type="inheritedJdk" />
		<orderEntry type="sourceFolder" forTests="false" />

	</component>
</module>
```

移除工程配置中子源碼被包含的`<sourceFolder/>`標籤即可。



# 常見問題記錄

## String.split()
函數的定義爲：

```java
public String[] split(String regex);
```

`String`類中提供的文本切片函數`String.split()`接收的參數是**正則表達式**(Regex)。
以一些**特殊符號**(`.`、`+`等)作爲分隔符時，不能直接使用符號本身，而是需要使用轉義符號，如以**小數點**作爲分隔符切片需要寫成：

```java
String[] nums = "123.456.789".split("\\.");
```

其它文本處理方法如`String.replace()`、`String.join()`等也有以正則表達式爲匹配參數的重載版本，使用方式類似。

## String.format()
函數的定義爲：

```java
public static String format(String var0, Object... var1);
public static String format(Locale var0, String var1, Object... var2);
```

String類的`format()`方法提供類似C語言中`sprintf()`函數類似的文本格式化方式，格式化字段的語法類似。

## String.getProperty()
使用`System.getProperty()`方法可以獲取**操作系統**以及**Java虛擬機**的各類狀態信息：

```java
public static String getProperty(String key);
```

參數`key`爲需要獲取信息的類型，常用系統信息的key如下：

| Key | 含義 |
| :- | :- |
| line.separator | 行分隔符(UNIX中是`/n`，Win中是`/r/n`) |
| os.name | 操作系統的名稱 |
| os.arch | 操作系統的架構 |
| os.version | 操作系統的版本 |
| user.name | 用戶的賬戶名稱 |
| user.home | 用戶的主目錄 |
| user.dir | 用戶的當前工作目錄 |
| java.io.tmpdir | 操作系統的TEMP目錄 |

## java.lang.UnsatisfiedLinkError: */jre/lib/amd64/libawt_xawt.so: libXrender.so.1: cannot open shared object file: No such file or directory
錯誤原因：<br>
Linux環境下，系統缺失動態鏈接庫`libXrender.so`。

解決方法：<br>
使用發行版對應包管理器安裝缺失的庫。
以`Debian`、`Ubuntu`爲例：

```
# apt install libxrender-dev
```

## java.lang.UnsatisfiedLinkError: */jre/lib/amd64/libawt_xawt.so: libXtst.so.6: cannot open shared object file: No such file or directory
錯誤原因：<br>
Linux環境下，系統缺失動態鏈接庫`libXtst.so`。

解決方法：<br>
使用發行版對應包管理器安裝缺失的庫：
以`Debian`、`Ubuntu`爲例：

```
# apt install libxtst-dev
```
