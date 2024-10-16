<!-- TOC -->

- [REPL](#repl)
- [編譯器配置](#編譯器配置)
- [Enum](#enum)
	- [枚舉構造器和成員方法](#枚舉構造器和成員方法)
- [Class](#class)
	- [構造器參數](#構造器參數)
	- [data class](#data-class)
- [Function](#function)
	- [函數參數默認值](#函數參數默認值)
	- [參數默認值兼容Java重載（`@JvmOverloads`）](#參數默認值兼容java重載jvmoverloads)
- [特色語法](#特色語法)
	- [Lambda Receiver](#lambda-receiver)
	- [Scope Functions（作用域函數）](#scope-functions作用域函數)
	- [其它輔助擴展函數](#其它輔助擴展函數)

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



# 編譯器配置
在Maven中使用Kotlin需要配置編譯器插件`kotlin-maven-plugin`：

```xml
<project>
    ...
    <build>
        <plugins>
            <!-- Compiler plugin for Kotlin. -->
            <plugin>
                <groupId>org.jetbrains.kotlin</groupId>
                <artifactId>kotlin-maven-plugin</artifactId>
                <version>${kotlin.version}</version>
                <configuration>
                    <!-- Set up the byte code target JVM version. -->
                    <jvmTarget>${maven.compiler.release}</jvmTarget>
                    <!-- Used to enable the Java 8 default method feature when generating byte code. -->
                    <args>-Xjvm-default=all</args>
                    <compilerPlugins>
                        <plugin>spring</plugin> <!-- Spring support for Kotlin. -->
                        <plugin>jpa</plugin> <!-- JPA support for Kotlin. -->
                    </compilerPlugins>
                </configuration>
                <dependencies>
                    <dependency>
                        <!-- For Kotlin Spring Plugin. -->
                        <groupId>org.jetbrains.kotlin</groupId>
                        <artifactId>kotlin-maven-allopen</artifactId>
                        <version>${kotlin.version}</version>
                    </dependency>
                    <dependency>
                        <!-- For Kotlin JPA Plugin. -->
                        <groupId>org.jetbrains.kotlin</groupId>
                        <artifactId>kotlin-maven-noarg</artifactId>
                        <version>${kotlin.version}</version>
                    </dependency>
                </dependencies>
            </plugin>
        </plugins>
    </build>
    ...
</project>
```

編譯器參數相關：

- `<jvmTarget/>`用於設置生成字節碼的目標JVM版本，可使優化編譯器生成的字節碼。
- `<args/>`用於設置編譯器使用的命令行編譯參數，
`-Xjvm-default=all`參數用於告知編譯器在生成接口默認方法時直接使用Java8的Default Method特性
（默認Kotlin在生成字節碼時會考慮兼容性而採用輔助工具類的實現方式）。

編譯器插件相關：

- 針對Spring項目kotlin-maven-plugin插件提供了`spring`插件，
啟用後對於Spring相關註解修飾的類可自動設置為open類（類似存在一定限制的`kotlin-maven-allopen`插件）。
- 針對JPA項目kotlin-maven-plugin插件提供了`jpa`插件。
- spring與jpa插件均需要引用對應的Kotlin編譯器插件依賴，否則構建時會產生編譯錯誤。



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



# 特色語法
Kotlin整體語言設計來自Scala2（子集），但依舊提供了一些特色功能。

## Lambda Receiver
Kotlin的Lambda簽名中可以限定Lambda的執行者類型，
稱為[`Lambda Receiver`](https://kotlinlang.org/docs/lambdas.html#function-literals-with-receiver)，
語法如下：

```kt
lamdba: Type.(ArgTypes...) -> ReturnType
```

使用此語法定義的Lambda只能用於在Receiver類型的對象上執行，
同時Lambda內的this指針會被替換為Receiver對象。

示例：

```kt
val lambda: StringBuilder.(String) -> String = {
    // 作用域內this指針類型為StringBuilder
    appendln() // 可直接調用StringBuilder的成員方法(僅可訪問共有成員)
    appendln("One")
    appendln("Two")
    appendln("Three")
    appendln(it)
    toString()
}
StringBuilder("Start:").lambda("End.")
```

輸出內容：

```
Start:
One
Two
Three
End.
```

Lambda Receiver使得Kotlin擁有比Scala更強的DSL能力，
是Kotlin中少數相比Scala設計更加優秀的特性。

Scala3採用**隱式參數**的方式提供了近似Lambda Receiver的DSL能力，
但從結構設計來看，概念和語法更加複雜，使用亦較為不便，不如Kotlin的Lambda Receiver簡潔直觀。

## Scope Functions（作用域函數）
基於Extension Functions和Lambda Receiver特性，Kotlin標準庫中進一步提供了一系列
[Scope Functions（作用域函數）](https://kotlinlang.org/docs/scope-functions.html)。

相關函數定義：

```kt
public inline fun <T, R> with(receiver: T, block: T.() -> R): R { ... }
public inline fun <T> T.apply(block: T.() -> Unit): T { ... }
public inline fun <T> T.also(block: (T) -> Unit): T { ... }
public inline fun <T, R> T.run(block: T.() -> R): R { ... }
public inline fun <T, R> T.let(block: (T) -> R): R { ... }
```

作用域函數主要分為三組:

- `apply()/also()`

	apply()以及also()函數返回調用者本體。

	apply()的參數Lambda表達式中，調用者作為Lambda Receiver傳入；
	also()的參數Lambda表達式中，調用者以普通參數傳入。

- `run()/let()`

	run()以及let()函數返回Lambda的執行結果。

	run()的參數Lambda表達式中，調用者作為Lambda Receiver傳入；
	let()的參數Lambda表達式中，調用者以普通參數傳入。

- `with()`

	with()函數則復刻了JavaScript中
	[`with`](https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Statements/with)
	關鍵字的用法。

作用域函數提升了Kotlin語法的表現力，使用作用域函數，可使得代碼更加簡潔、緊湊。

## 其它輔助擴展函數
Kotlin標準庫還提供了替代try with resource語法的`use()`擴展函數：

```kt
inline fun <T : Closeable?, R> T.use(block: (T) -> R): R
```

以及簡化鎖使用的lock()系列函數：

```kt
// 類似C++的RAII，在Scope內持有鎖，出作用域釋放
inline fun <T> Lock.withLock(action: () -> T): T

// 簡化讀寫鎖操作
fun <T> ReentrantReadWriteLock.read(action: () -> T): T
fun <T> ReentrantReadWriteLock.write(action: () -> T): T
```
