<!-- TOC -->

- [REPL](#repl)
- [Enum](#enum)
	- [枚舉構造器和成員方法](#枚舉構造器和成員方法)
- [Class](#class)
	- [構造器參數](#構造器參數)
	- [data class](#data-class)
- [Function](#function)
	- [函數參數默認值](#函數參數默認值)
	- [參數默認值兼容Java重載（`@JvmOverloads`）](#參數默認值兼容java重載jvmoverloads)

<!-- /TOC -->



# REPL
Kotlin自帶REPL，但功能較弱，無法與Scala、Haskell等成熟語言相比。

Kotlin官方提供了對Jupyter Notebook的支持[kotlin-jupyter](https://github.com/Kotlin/kotlin-jupyter)。
使用pip可直接進行安裝：

```
$ pip install kotlin-jupyter-kernel
```

在macOS下，使用Xcode提供的Python3時，
kotlin-jupyter-kernel被安裝到路徑`~/Library/Python/3.8/share/jupyter/kernels/kotlin`下，
而該路徑並不被macOS版本的jupyter識別，在macOS下，需要安裝到以下路徑之一：

```
~/Library/Jupyter/kernels
/usr/local/share/jupyter/kernels
```

安裝kotlin-jupyter-kernel到正確的位置：

```
$ jupyter kernelspec install ~/Library/Python/3.8/share/jupyter/kernels/kotlin
```

執行安裝指令成功後，kernel會被安裝到`/usr/local/share/jupyter/kernels/kotlin`路徑下，
但啟動依舊會存在問題，kernel的配置文件`kernel.json`內容如下：

```json
{
    "display_name": "Kotlin",
    "language": "kotlin",
    "interrupt_mode": "message",
    "argv": [
        "python",
        "-m",
        "run_kotlin_kernel",
        "{connection_file}"
    ]
}
```

該文件中配置的啟動參數使用了python指令(第6行)，但在macOS下，python指令默認啟動Python2，
因此會出現異常，修改啟動參數為python3即可正常啟動



# Enum
Kotlin提供了類似Java的枚舉功能，使用`enum class Xxx`進行定義。
枚舉實例自帶兩個屬性，`name`用戶輸出枚舉的名稱，`ordinal`輸出枚舉實例在枚舉中的次序(從零開始)。

```kt
enum class Enum { A, B, C } // 定義枚舉
Enum.A.name // 值為 A
Enum.A.ordinal // 值為 0
```

Kotlin枚舉與Java枚舉兼容，與Java枚舉類似也不能繼承其它類型(可以實現接口)。

## 枚舉構造器和成員方法
與Java類似，Kotlin中的枚舉是**類**，因此枚舉類型可以定義構造器，以及自身的屬性/成員方法。

```kt
// 定義構造器，並帶有成員屬性和默認參數
enum class Enum(val description: String = "default") {
	A, // 枚舉成員使用默認參數
	B("description_b"), // 顯式調用構造器
	C("description_c")
}

Enum.A.description // 值為 "default"
Enum.B.description // 值為 "description_b"
Enum.C.description // 值為 "description_c"
```



# Class
Kotlin中Class的設計整體沿襲了Scala的Class語法，取消了Scala類中一些較為靈活的語法：

- 取消了Scala類內直接編初始化寫代碼的功能，Kotlin需要在類內的`init {}`塊中編寫。
- Scala中`case class`構造器字段自動作為屬性，而Kotlin中`data class`構造器成員字段依舊需要顯式使用val關鍵字標記。

## 構造器參數
與Scala類似，Kotlin允許使用val關鍵字在構造器中創建字段。
構造器參數可以創建默認值，但需要注意，創建默認值操作在構造函數中進行，
若默認值依賴其它字段，則需要保證依賴的字段在構造器調用階段已初始化。

對於使用Java反射機制的框架，通常需要類型提供無參的默認構造器，
Kotlin中類型中主構造器有参則默認不會再生成無參構造器，
此時要生成無参構造器需要為每個構造器參數提供默認值。

## data class
Kotlin中提供了類似Scala中case class的語法，名為`data class`，
相對於Scala中case class，Kotlin的data class有以下差異：

- 沒有提供模式匹配功能
- 即使所有構造器參數中均為成員字段，但依舊需要顯式使用val語法進行標記
- data class不能被任何類繼承，case class僅限制不能被同為case class的類繼承



# Function
與Java和Scala2不同，Kotlin中的函數可以獨立存在（可定義在頂層作用域）。

## 函數參數默認值
與C++、C#、Scala等語言相同，Kotlin支持參數默認值。
與Scala相同，Kotlin中的參數默認值無特殊限制，
支持使用**變量**和**表達式**作為默認值，
且使用表達式作為默認值時，會在每次調用時重新求值（與Scala行為相同）。

```kt
var n = 0
fun count() = ++n
fun showCount(v: Int = count()) = println(v)
fun showN(v: Int = n) = println(v)

showCount() // 輸出1
showN() // 輸出1
showCount() // 輸出2
showN() // 輸出2
showCount() // 輸出3
showN() // 輸出3
```

Scala中行為類似：

```scala
scala> var n = 0
var n: Int = 0

scala> def count() = { n += 1; n }
def count(): Int

scala> def showCount(v: Int = count()) = println(v)
def showCount(v: Int): Unit

scala> def showN(v: Int = n) = println(v)
def showN(v: Int): Unit

scala> showCount()
1

scala> showN()
1

scala> showCount()
2

scala> showN()
2

scala> showCount()
3

scala> showN()
3
```

## 參數默認值兼容Java重載（`@JvmOverloads`）
Kotlin中使用參數默認值特性，在生成字節碼時默認會生成一個以`$default`結尾的輔助函數。
輔助函數在參數表後增加了Int數值類型作為標記位，用於標記哪些參數使用了默認值；
以及一個Object對象。

示例：

```kt
fun kotlinOverload(test1: String = "test1", test2: Int = 999, test3: Float) { }
```

生成的Java代碼：

```java
public static final void kotlinOverload(@NotNull String test1, long test2, float test3) {
   Intrinsics.checkNotNullParameter(test1, "test1");
}

// $FF: synthetic method
public static void kotlinOverload$default(String var0, long var1, float var3, int var4, Object var5) {
   if ((var4 & 1) != 0) {
      var0 = "test1";
   }

   if ((var4 & 2) != 0) {
      var1 = 999L;
   }

   kotlinOverload(var0, var1, var3);
}
```

在Kotlin中調用重載，會自動調用輔助函數並填充標記位：

```kt
kotlinOverload(test3 = 1f)
```

對應Java代碼：

```java
kotlinOverload$default((String)null, 0L, 1.0F, 3, (Object)null);
```

在Java中直接使用重載則較為不便（需要自行計算標記位）。
可使用`@JvmOverloads`註解為函數生成Java風格的重載，
添加重載註解後生成的Java代碼：

```java
@JvmOverloads
public static final void kotlinOverload(@NotNull String test1, long test2, float test3) {
   Intrinsics.checkNotNullParameter(test1, "test1");
}

// $FF: synthetic method
public static void kotlinOverload$default(String var0, long var1, float var3, int var4, Object var5) {
   if ((var4 & 1) != 0) {
      var0 = "test1";
   }

   if ((var4 & 2) != 0) {
      var1 = 999L;
   }

   kotlinOverload(var0, var1, var3);
}

@JvmOverloads
public static final void kotlinOverload(@NotNull String test1, float test3) {
   kotlinOverload$default(test1, 0L, test3, 2, (Object)null);
}

@JvmOverloads
public static final void kotlinOverload(float test3) {
   kotlinOverload$default((String)null, 0L, test3, 3, (Object)null);
}
```
