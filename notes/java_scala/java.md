[TOC]

## 基础类型
与主流语言不同，`Java`中仅仅提供了**有符号**数值类型，**没有**提供无符号的数值类型。

`Java`中的基础整型数值类型如下所示：

- `byte`，单字节，范围`-128 ~ 127`
- `short`，双字节，范围`-32768 ~ 32767`
- `int`，四字节，范围`-2147483648 ~ 2147483647`
- `long`，八字节，范围`-9223372036854775808 ~ 9223372036854775807`

浮点型数值类型如下所示：

- `float`，四字节，范围`-3.4028235E38 ~ 3.4028235E38`
- `double`，八字节，范围`-1.7976931348623157E308 ~  1.7976931348623157E308`

### *Literal number* (字面值)
在`Java`中，无任何修饰的整型数值字面值默认为`int`类型，无任何修饰的浮点型数值字面值默认为`double`类型。

字面值数值在进行赋值操作时数值的大小不能超过目标类型的上限，如下所示：

```java
byte num0 = 1;			//正确
byte num1 = 1000;		//错误，提示"从int转换到byte可能会有损失"
```

整型字面值默认为`int`型，即默认字面值范围应在`-2147483648 ~ 2147483647`之间，当整型字面值超出这个范围时，即使目标类型能够容纳数值，赋值操作时依然会报错，如下所示：

```java
long num = 6666666666;	//错误，提示"过大的整数: 6666666666"
```

此时，需要显式使用后缀指定字面值类型，如下所示：

```java
long num0 = 6666666666L;	//正确
long num1 = 6666666666l;	//正确
```

常用的字面值后缀：

| 后缀 | 含义 |
|:---:|:----:|
| L/l | long |
| F/f | float |
| D/d | double |

整型数值通过添加前缀可以指定数值以不同进制表示：

| 前缀 | 含义 |
|:----|:----:|
| 0B/0b | 二进制数值 |
| 0 | 八进制数值 |
| 0X/0x | 十六进制数值 |

### *char* (字符类型)
与其它语言不同，`Java`中采用`UTF-16`编码，一个字符占用**两个字节**，而非传统语言中的单个字节。

`char`类型无符号，范围为`0 ~ 65535`，字面值表示方式为`'\u0000' ~ '\uFFFF'`，如下所示：

```java
char c0 = \u0000;		//错误，字符需要加单引号
char c1 = '\U0000';		//错误，字符只能使用小写`\u`转义，大写`\U`无效
char c2 = '\u0000';		//正确
```

### 格式化
在`Java`中，使用`System.out.printf()`方法进行格式化输出，格式化语法类似`C`语言标准库中的`printf()`函数。

常用的格式化字符：

| 格式化字符 | 含义 | 样例 |
|:--------:|:----:|:---:|
| `%s` | 字符串类型 | `"abc"` |
| `%c` | 字符类型 | `'a'` |
| `%b` | 布尔类型 | `true` |
| `%d` | 整数类型(十进制) | `99` |
| `%x` | 整数类型(十六进制) | `FF` |
| `%o` | 整数类型(八进制) | `77` |
| `%f` | 浮点类型 | `99.990000` |
| `%a` | 十六进制浮点类型 | `0x1.8ff5c28f5c28fp6` |
| `%e` | 指数类型 | `9.999000e+01` |
| `%g` | 通用浮点类型(宽度较短) | `99.9900` |
| `%h` | 散列码 | / |
| `%%` | 百分比符号(在格式化语句中直接使用`%`会开始转义) | `%` |
| `%n` | 换行符(在格式化语句中使用`\n`换行转义无效) | / |

实例如下所示：

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

输出结果：

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

数值类型支持更丰富的格式化操作：

| 格式化字符 | 含义 | 样例 |
|:--------:|:----:|:---:|
| `%+d` | 为数值类型添加正负号 | `+99`/`-99` |
| `% 5d` | 指定输出数值的宽度，宽度不足时左边使用空格补齐 | `   99` |
| `%-5d` | 指定输出数值的宽度，宽度不足时右边使用空格补齐 | `99   ` |
| `%05d` | 指定输出数值的宽度，宽度不足时使用0补齐 | `00099` |
| `%,d` | 格式化数值时使用`,`对长数值进行分割 | `9,999` |
| `%<d` | 格式化数值，使用前一个数值做为格式化对象 | / |
| `%(d` | 格式化负数时采用括号标记负值(对正值无效) | `(99)` |
| `%#`/`%#x` | 格式化8/16进制数值时添加前缀`0`/`0x` | `0x63` |

### 有符号数转换无符号数
在`Java`中，没有内置的无符号类型，则在表示大于`2 ^ 位宽 - 1`的数值时，需要使用更高位宽的数值来表示。

以`byte`类型为例，有符号的`byte`类型范围在`-128 ~ 127`之间，当数值大于`127`时，则需要使用更高位宽的类型表示(如`short`)。  
`byte`类型为单字节，则将原始有符号数值转换位更高位宽的类型，再与`0xFF`进行`&`(逻辑与)操作(保留原始数值位，擦除其它内容)，得到对应的无符号值。

以`byte`类型负数`-11`为例，运算过程如下：
> `byte`类型数值`-11`，原码为：
>
> `10001011`
>
> 在计算机中以反码存储，反码表示为：
>
> `11110101`(对应无符号数值`245`(首位不视为符号位))
>
> `byte`类型数值`-11`提升到`short`型，编译器会保留数值含义(数值`-11`)不变，原码为：
>
> `1000000000000001`
>
> 在计算机中存储的反码为：
>
> `1111111110001011`
>
> 若保留原先的无符号值含义(数值`245`)，则原码/反码均应为：
>
> `0000000010001011`
>
> 对比可知**低8位**对应原先的数值，则应保留低8位数值，将高8位**置零**，与`0xFF`进行**逻辑或**操作可达到此效果。



## *Package*
在`Java`中，没有使用`package`的话，在`javac`编译`java`文件生成`class`字节码时，需要将所有用到的源码文件写在参数中，不在当前目录下的源码文件要写清路径。

若源码文件过多，则可以使用`package`关键字将其打包归类，然后在主类所在的文件中使用`import`关键字来将包导入使用。  
如果没有使用`package`关键字，则所有的内容被视为在一个包中。

### *import* 的基本用法
`import`的格式是：

```java
import [包路径].[类名];
```

如果需要包含内部类，则可以使用多级import，如：

```java
import [包路径].[类名]...[类名];
```

需要注意的是，import与代码文件的路径**无关**(但运行class文件时需要将class文件放在与其源码中package名称相同的对应目录下，否则会在执行时出错)。
另外，包名也可以是`*.*.*`的形式。

### 使用静态导入
`Java 5`中新加入了`import static`关键字，相比传统的`import`，`import static`关键字的包含目标是类中的静态方法，格式如下：

```java
import static [包路径].[类名].[静态方法名];
```

这样能够在使用对应类的静态方法时不必写出类名而是直接写出函数名即可。

### *package* 使用实例
有两个文件**A.java**和**B.java**。

文件B中的类被A中引用,则将B打包,代码中添加`package b`，并放在b目录下。  
文件A中引用B中的类。  

按照描述，两文件的位置：

- **文件A**路径为`~/A.java`。
- **文件B**路径为`~/b/B.java`。

实例代码(普通import)：

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

实例代码(import static)：

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

其中**A.java**文件能够正常调用类B的方法`getNow()`。

一个`java`源码文件只能包含一个**公有类**，且源码文件的名称应该与包含的公有类的类名**一致**。

`package`打包的源码应当放在与包名相同的目录中，这样生成的字节码class文件才会在对应目录生成。  
若源码均置于同一级目录，则编译之后产生的`class`文件需要按照`package`关系放在与包名相同的目录下，否则执行`class`文件时会报错(找不到对应的class文件)。

### 引用自定义依赖
引用第三方的`jar`文件，则编译时应使用`-cp`参数，如下：

```
$ javac -cp [第三方库的路径] [源码文件]
```

编译生成的class文件无法直接被`java`指令执行(class文件使用了第三方库，库的位置不在系统环境变量内)，运行时需要显式地指定引用库的位置：

```
$ java -Djava.ext.dirs=[第三方库所在的目录] [编译生成的class文件]
```



## 容器类型
与常见的编程语言相同，Java中的常见的**容器类型**为`List`、`Set`、`Map`。

- `List`特点：元素**有序**，元素**可重复**。
- `Map`特点：元素按键值对存储，**无序**。
- `Set`特点：元素**无序**，元素**不可重复**(注意：元素虽然无放入顺序，但是元素在`Set`中的位置是有该元素的**HashCode**决定的，其位置其实是固定的)。

在Java中，这三种集合类型都是以接口形式存在的，不能直接使用，要使用这三种类型可以使用其实现类：

- `List`的实现类为`LinkedList`、`ArrayList`、`Vector`；。
- `Set`接口有两个实现类`HashSet`、`LinkedHashSet`。
- `Map`接口有三个实现类`HashMap`、`HashTable`、`LinkeHashMap`。

这些实现类各有优缺点：

- `ArrayList`是**非线程安全**的，效率**高**。
- `Vector`是基于**线程安全**的，效率**低**。
- `HashMap`**非线程安全**，高效，**支持**null。
- `HashTable`**线程安全**，低效，**不支持**null 。

语法：

```java
List<Type> list = new ArrayList<Type>();
list.add(type);
Map<Key, Type>  map = new HashMap<Key, Type>();
map.put(key, type);
```

Java支持泛型`<>`**菱形推断**，实例化时类型可以省略(`Java 1.7`新特性)，上面的语句实例化可以简写为：

```java
List<Type> list = new ArrayList<>();
Map map = new HashMap<>();
```

甚至，你还可以直接省略`<>`符号，完全让编译器推断(Java1.8新特性，一般编译器会隐式推断为`Object`类型)：

```java
List list = new ArrayList();
Map map = new HashMap();
```

`Set`和`List`都可以得到一个迭代器用于迭代：

```java
Iterator iteratorList = list.iterator();
Iterator iteratorSet = set.iterator();
```

`Map`的`Key`就是一个`Set`，可以得到`Key`的集合再迭代：

```java
Set set = map.keySet();
Iterator iteratorSet = set.iterator();
```

`Map`使用`get(key)`可以得到对应的键值，但是这个键值是`Object`型的，需要通过向下转型来恢复键值类型。  
`HashMap`之类的容器只能一个键对应**一个**键值，如果需要一个键绑定多个键值可以使用`IdentityHashMap`。



## 枚举
Java中使用`enum`关键字来定义一个枚举类。

基本的枚举与`C`语言中的语法类似：

```
enum Enum {
	ENUM_MEMBER_1,
	ENUM_MEMBER_2,
	ENUM_MEMBER_3,
	ENUM_MEMBER_4,
	...
}
```

枚举是`Java`中少数比`C++`更**复杂**的语法之一：

- `Java`枚举类中的**枚举成员**(类内普通成员除外)每一个都是枚举类的实例。
- 在枚举类与普通类相似，也可以在类内定义成员方法和成员变量。
- 要在枚举类内定义成员方法/变量，需要在最后一个枚举成员成员后添加**分号**以标志枚举成员列表结束。
- 在枚举类内定义的方法/变量每一个枚举成员都拥有。
- 在枚举类内自定义构造函数则枚举成员需要通过自定义的构造函数来构建，参数需要符合构造函数的参数表。
- 枚举类内的构造函数默认为`private`访问权限，且不可更改。
- 枚举类为抽象类`java.lang.Enum`的子类，而Java为单继承语言，因而枚举类不能再继承其它类，只能实现接口。

简单的自定义枚举类示例如下：

```java
enum Enum {

	// 定义枚举成员，以分号做为结束标志
	ENUM_MEMBER_1("member1") {
		// 枚举类成员内可以重写枚举类内定义的方法
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

		// 枚举类内可以定义新的方法，但该方法无法被访问，因而没有意义
		public int size() { return 4; }
	};

	// 自定义枚举类的构造函数
	Enum(String name) { this.name = name; }

	String getName() { return name; }

	int index() { return 0; }

	private String name;
}
```



## 浅复制与深复制
在Java中，**基础类型**如`int`、`double`等在复制时是拷贝了**整个值**，而对于**引用类型**，则默认拷贝的只是一个对象的**引用**(类似与C/C++中的**指针**)，对象本体**并未**被复制。

### 浅复制
要想让一个类能够被复制，则类需要实现`Cloneable`接口，并重写`clone()`方法。

如下代码所示：

```java
class TestClone implements Cloneable {

	StringBuffer str = new StringBuffer("str");

	//重写clone()方法
	@Override
	public TestClone clone() {
		TestClone clone = null;
		try {
			clone = (TestClone)super.clone();
		} catch (CloneNotSupportedException e) {
			e.printStackTrace();
		}
		return clone;
	}
}
```

虽然`clone()`方法来自于根类`Object`，但如果不实现`Cloneable`接口，则在调用`clone()`方法的时候会抛出`CloneNotSupportedException`异常。

编写代码测试：

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

输出结果：

```
strNew
```

可以发现调用`clone()`方法复制出的对象**testClone**在原对象**test**被修改后也发生了变化，并未真正的达到**复制**的效果。  
原因是**TestClone**类完成的仅仅是**浅复制**的过程，类中的引用类型`StringBuffer`并未被真正复制。

### 深复制
深复制一个对象，则需要将类中的每一个引用成员都进行**复制**，因此，**TestCode**的代码需要改成：

```java
class TestClone implements Cloneable {

	StringBuffer str = new StringBuffer("str");

	@Override
	public TestClone clone() {
		TestClone clone = null;
		try {
			clone = (TestClone)super.clone();
			clone.str = new StringBuffer(str);		//构建新的StringBuffer对象
		} catch (CloneNotSupportedException e) {
			e.printStackTrace();
		}
		return clone;
	}
}
```

在重写`clone()`方法的过程中，要实现**深复制**，就需要重新构造类中的每一个引用类型。  
重新构造对象优先使用该引用类型的`clone()`方法(如果该类型实现了`Cloneable`接口)。  
如果需要复制的引用类型没有实现`Cloneable`接口，则直接使用构造函数创建一个与当前实例中保存内容相同的对象。

需要注意的是，`String`类型是**特例**，虽然其为**引用类型**，但`String`内部重新实现了自身的`clone()`，在重写当前类的`clone()`方法的时候可以将其视为基本类型(即不必显式构建)。



## 泛型方法
Java中的泛型同样支持独立于类的泛型方法。  
与`C++`、`C#`等语言不同，Java在泛型方法中的类型声明放在方法的修饰符(`public`、`static`、`final`、`abstract`等)之后，返回值声明之前。

Java中的泛型方法支持自动类型推导。  
也可手动显式指定泛型类型，手动指定泛型类型时，与`C++`、`C#`等语言不同，类型参数写在方法名称**之前**。

如下代码所示：

```java
public class Test {
	public static void main(String[] args) {
		Func t = new Func();
		System.out.println(t.getType(123));
		System.out.println(t.getType("Test"));
		System.out.println(t.<Double>getType(25.672));		//类型参数写在方法名称之前
	}
}

class Func {
	public <T> T getType(T t) {
		return t;
	}
}
```

输出结果：(Windows 10 && JDK 1.8)

```
java
123
Test
25.672
```



## *Nested Classes* (嵌套类)
嵌套类(`nested class`)是指定义在一个类内部的类，对应的，包含嵌套类的类被称为**外部类**(`enclosing class`)。

嵌套类有以下几种类型：

1. `member nested class`(成员嵌套类)：

	成员嵌套类是作为`enclosing class`的成员定义的，成员嵌套类有`enclosing class`属性。  
	成员嵌套类可以使用访问控制符，也可以用`static`、`final`关键字修饰。

1. `local nested class`(局部嵌套类)：

	局部嵌套类定义在方法里面，局部嵌套类有`enclosing class`属性和`enclosing method`。  
	局部嵌套类可以使用`final`关键字。

1. `anonymous nested class`(匿名嵌套类)：

	匿名嵌套类没有显示的定义一个类，直接通过`new`操作符构造。  
	匿名嵌套类不使用任何关键字和访问控制符。

普通嵌套类内部不能定义`static`关键字修饰的成员，只有**静态嵌套类**(`static nested class`)内部才能定义`static`成员。  
静态嵌套类之外的所有嵌套类又被称为**内部类**(`inner class`)。  
静态嵌套类只能访问外部类的静态成员。

如下代码所示：

```java
class EnclosingClass {

	// 成员嵌套类
	class MemberNestedClass {

		//static int a;			//错误，只有静态嵌套类才能在内部定义静态成员

	}

	// 使用static关键字修饰的成员嵌套类为静态嵌套类
	static class StaticMemberNestedClass {

		static int a;			//正确，可以正常定义静态成员

	}

	void showLocalNestedClass() {

		// 局部嵌套类
		class LocalNestedClass {
		}

	}

	// 匿名嵌套类
	XXX xxx = new XXX {
		@Override
		...
	};

}
```



## 并发编程
在Java，常见的并发技术有基本的`Thread`类，以及线程池`Executor`框架。

### *Thread* 和 *Runnable*
使用`Thread`创建线程的两种方式：

1. `Runnable`接口定义了`run()`方法，实现该接口，将需要并发执行的内容写在`run()`方法中。  
	将实现`Runnable`的实例作为参数构造`Thread`实例。
1. `Thread`类实现了`Runnable`接口，因此也可以直接继承`Thread`类重写其`run()`方法。

完成`Thread`对象的构建后，再调用其成员函数`start()`便会开启线程执行`run()`中的代码。

注意事项：

- 启动线程需要使用`start()`成员方法，调用`run()`无效，代码依然同步执行。
- `Thread`类只是**一个**线程的抽象，因此在线程启动后不能再次调用`start()`启动新线程，启动新线程需要构建新的`Thread`对象。

如下代码所示：

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

		//使用继承的线程类启动线程
		new TestThread().start();

		//使用Runnable实例构造Thread类启动线程
		new Thread(runnable).start();
	}

}
```

`Thread`类的常用方法：

```java
// 使用指定名称创建线程
public Thread(Runnable runable, String name);
// 获取线程对象
public static native Thread currentThread();
// 获取线程名称
public final String getName();
// 线程休眠指定毫秒
public static native void sleep(long millis) throws InterruptedException;
```

### *synchronized* 关键字
在多线程环境下，多个线程同时访问一个变量时，会产生线程同步问题，变量可能会被其它线程意外地修改。典型的解决方式是对共享变量进行**加锁**。

`Java 5`之后提供了`synchronized`关键字用于解决线程同步问题。
`synchronized`关键字有两种用法：

1. `synchronized`块

	基本语法如下：

	```java
	synchronized (object) {
		/* do something */
	}
	```

	其中，同步变量`object`可以是实例、`this`引用或是类型(`XXX.class`)。

	以相同`object`为同步对象的多个`synchronized`块在同一时刻只能有一个`synchronized`块被一个线程执行。  
	在该线程离开`synchronized`块之前，其余线程都会处于等待状态。

	- `object`为实例时：

		同步变量需要为**引用类型**(基础类型如`int`、`float`等不能使用`synchronized`关键字进行同步)。  
		同步变量**不能**为`null`。  
		同步变量为类的实例成员时，需要注意同一个类的不同实例的相同实例成员是不同的。  
		同步变量为类的静态成员时，一个类的所有实例共享静态成员，此时效果类似于同步类型(`XXX.class`)。

	- `object`为`this`引用时：

		同一实例中以`this`为同步变量的代码块同时只能被一个线程执行。  
		不同实例之间以`this`为同步对象的代码块无影响。

	- `object`为类型时，所有以此为同步变量的代码块都只能被一个线程执行。

1. `synchronized`方法

	`synchronized`关键字用于修饰方法，语法如下：

	```java
	synchronized Type methodName(Type args...) {
		/* do something */
	}
	```

	被`synchronized`修饰的方法同时只能被**一个**线程访问：

	- 修饰的方法为**实例方法**时：

		同一实例的`synchronized`方法同时只能有一个被执行。  
		等价于将整个方法体的内容写在`synchronized (this) { ... }`中。不同实例间不受影响。

	- 修饰的方法为**静态方法**时：

		所有该类中的静态`synchronized`方法同时只能有一个被执行。  
		等价于将整个方法体的内容写在`synchronized (类名.class) { ... }`中。

	一个类中被`synchronized`修饰的实例方法和被`synchronized`修饰的静态方法的同步变量不同，因而不会相互同步。

	如下代码所示：

	```java
	import static java.lang.Thread.sleep;

	class Example {

		public synchronized void showOne() {
			for (int i = 0; i < 5; i++) {
				String threadName = Thread.currentThread().getName();
				System.out.println(threadName + " showOne()");
				try {
					sleep(100);
				} catch (InterruptedException e) {
					e.printStackTrace();
				}
			}
		}

		public synchronized void showTwo() {
			for (int i = 0; i < 5; i++) {
				String threadName = Thread.currentThread().getName();
				System.out.println(threadName + " showTwo()");
				try {
					sleep(100);
				} catch (InterruptedException e) {
					e.printStackTrace();
				}
			}

		}

		public static synchronized void showStatic() {
			for (int i = 0; i < 5; i++) {
				String threadName = Thread.currentThread().getName();
				System.out.println(threadName + " showStatic()");
				try {
					sleep(100);
				} catch (InterruptedException e) {
					e.printStackTrace();
				}
			}
		}
	}

	public class Main {

		public static void main(String[] args) {

			Example example = new Example();

			new Thread(() -> example.showOne(), "Thread One").start();
			new Thread(() -> example.showTwo(), "Thread Two").start();
			new Thread(() -> example.showStatic(), "Thread Three").start();
		}
	}
	```

	输出结果：

	```
	Thread One showOne()
	Thread Three showStatic()
	Thread One showOne()
	Thread Three showStatic()
	Thread One showOne()
	Thread Three showStatic()
	Thread One showOne()
	Thread Three showStatic()
	Thread One showOne()
	Thread Three showStatic()
	Thread Two showTwo()
	Thread Two showTwo()
	Thread Two showTwo()
	Thread Two showTwo()
	Thread Two showTwo()
	```

	输出结果分析：

	`Example`类中的三个成员方法都使用了`synchronized`关键字进行修饰。  
	`showOne()`、`showTwo()`为实例方法，`showStatic()`为静态方法。

	来自同一个实例在不同线程中的两个实例方法**没有**并发执行：  
	`showTwo()`一直等到`showOne()`结束才开始执行。

	静态方法并发执行了：  
	`showOne()`与`showStatic()`交错打印输出。

### *Executor* 框架
`Thread`类功能简单，仅仅提供了原始的线程抽象，在实际的开发中，往往会使用更高层次的API。

`Java 5`之后提供了`Executor`框架，用于创建、管理与执行线程。  
`Executor`框架主要包含`Executor`、`Executors`、`ExecutorService`、`CompletionService`、`Future`、`Callable`等类型。

`Runnable`、`Callable`、`Future`接口是Java中对于异步操作的抽象。

`Runnbale`接口用于表示没有返回值的异步操作，定义如下：

```java
public interface Runnable {
	void run();
}
```

除了`Runnable`接口是Java早期版本就已包含的之外，其余的接口/类定义都在`java.util.concurrent`包中。

`Callable`接口用于表示带有返回值的异步操作。  
定义如下：

```java
public interface Callable<V> {
	V call() throws Exception;
}
```

`Future`接口用于表示一个异步操作的结果。  
定义如下：

```java
public interface Future<V> {

	// 尝试取消任务的执行，参数mayInterruptIfRunning表示是否允许中断，返回是否取消了任务
	boolean cancel(boolean mayInterruptIfRunning);

	// 获取任务的取消/执行状态
	boolean isCancelled();
	boolean isDone();

	// 获取结果
	V get() throws InterruptedException, ExecutionException;
	V get(long timeout, TimeUnit unit)
		throws InterruptedException, ExecutionException, TimeoutException;
}
```

`Executor`接口是框架中最基础的部分，仅包含一个执行`Runnable`的`execute()`的抽象方法。  
定义如下：

```java
public interface Executor {
	void execute(Runnable command);
}
```

`Executor`接口没有直接子类，但拥有子接口`ExecutorService`。  
`ExecutorService`接口定义了一系列终止、提交、跟踪任务状态的抽象方法，是整个库的核心接口。  
定义如下：

```java
public interface ExecutorService extends Executor {

	// 关闭ExecutorService，调用后之前已接收的任务继续执行，但不再接收新的任务
	// 线程池使用完毕需要调用该方法关闭线程池
	void shutdown();

	// 尝试终止所有正在执行的任务，并终止等待执行的任务并返回这些任务的列表
	List<Runnable> shutdownNow();

	// 返回是否showdown
	boolean isShutdown();

	// 返回shutdown()后所有剩余任务是否执行完毕
	boolean isTerminated();

	// shutdown()后等待剩余任务执行一定时间，在指定时间结束后返回所有任务是否执行完毕
	boolean awaitTermination(long timeout, TimeUnit unit) throws InterruptedException;

	// 提交任务，返回该任务的Future，非阻塞
	<T> Future<T> submit(Callable<T> task);
	<T> Future<T> submit(Runnable task, T result);
	Future<?> submit(Runnable task);

	// 执行给定的任务集合，同步等待集合中所有的任务完成，并返回这些任务的Future
	<T> List<Future<T>> invokeAll(Collection<? extends Callable<T>> tasks) throws InterruptedException;
	/*
		执行给定的任务集合，等待指定时间，超过等待时间则终止尚未完成的任务。
		返回给定时间内已完成的任务的Future，若在等待时间结束前所有任务都已完成，则方法提前返回。
	*/
	<T> List<Future<T>> invokeAll(Collection<? extends Callable<T>> tasks,
		long timeout, TimeUnit unit) throws InterruptedException;

	// 执行给定的任务集合，同步等待，直到有任意任务完成时，方法返回该任务的执行结果，同时停止执行其它仍在执行的任务
	<T> T invokeAny(Collection<? extends Callable<T>> tasks)
		throws InterruptedException, ExecutionException;
	/*
		执行给定的任务集合，等待指定时间。
		在指定时间内有任意任务完成，则返回该任务的执行结果，同时停止其它正在执行的任务。
		若没有任何任务完成则抛出TimeoutException异常。
	*/
	<T> T invokeAny(Collection<? extends Callable<T>> tasks, long timeout, TimeUnit unit)
		throws InterruptedException, ExecutionException, TimeoutException;
}
```

`ExecutorService`接口的实例可以使用工厂类`Executors`中的静态方法进行创建，常用的一些方法如下：

```java
// 创建固定线程数目的ExecutorService，线程数目决定了同时并发执行的任务数目
public static ExecutorService newFixedThreadPool(int nThreads);

// 创建一个可根据需要创建新线程的ExecutorService，会重用以前可用的线程
public static ExecutorService newCachedThreadPool()；

// 创建一个使用单一工作线程的ExecutorService
public static ExecutorService newSingleThreadExecutor()；

// 创建周期性执行任务的ScheduledExecutorService
public static ScheduledExecutorService newScheduledThreadPool(int corePoolSize);
```

使用`ExecutorService`的基本代码如下：

```java
public class Main {

	public static void main(String[] args) {

		// 创建并发任务
		Callable<XXX> callable1 = () -> {
			/* do something... */
			return xxx;
		};
		Callable<XXX> callable2 = () -> {
			/* do something... */
			return xxx;
		};
		// create more tasks...

		// 创建线程池
		ExecutorService service = Executors.newCachedThreadPool();

		// 提交任务，获取结果Future
		List<Future<XXX>> results = new ArrayList();
		results.add(service.submit(callable1));
		results.add(service.submit(callable2));
		// add more tasks...

		// 处理任务结果
		for (Future<XXX> result : results) {
			XXX xxx = result.get();
			/* do something... */
		}

		// 关闭线程池，没有关闭线程池的操作main函数会一直不返回，程序也不会退出
		service.shutdown();
	}

}
```

使用`ExecutorService`在处理任务返回结果时，有以下缺陷：

- 直接使用`get()`从`Future`中同步获取返回值需要对任务的执行时间有大致的估算，否则可能造成在某一个执行耗时高的任务中阻塞较长时间。
- 使用`get(long timeout, TimeUnit unit)`限定了等待时间，但任务未必会在限定时间内完成，可能需要多次轮询才能获取到所有`Future`的结果。

处理多个任务返回结果应该使用`CompletionService`接口。  
`CompletionService`接口定义了将已完成的任务与新提交的任务分离的方法。  
定义如下：

```java
public interface CompletionService<V> {

	// 提交任务
	Future<V> submit(Callable<V> task);
	Future<V> submit(Runnable task, V result);

	// 获取下一个完成的任务的结果Future，若没有任务完成，则会同步等待直至有任务完成
	Future<V> take() throws InterruptedException;

	// 获取下一个完成的任务的结果Future，若没有任务完成，则返回null
	Future<V> poll();

	// 获取下一个完成的任务的结果Future，若没有任务，则等待指定时间，指定时间结束后仍没有任务完成则返回null
	Future<V> poll(long timeout, TimeUnit unit) throws InterruptedException;
}
```

`CompletionService`接口常用的实现类是`ExecutorCompletionService`，可以使用`Executor`实例构建：

```java
public ExecutorCompletionService(Executor executor);
```

使用`ExecutorCompletionService`的基本代码如下：

```java
public class Main {

	public static void main(String[] args) {

		// 创建并发任务
		Callable<XXX> callable1 = () -> {
			/* do something... */
			return xxx;
		};
		Callable<XXX> callable2 = () -> {
			/* do something... */
			return xxx;
		};
		// create more tasks...

		// 创建线程池
		ExecutorService service = Executors.newCachedThreadPool();

		// 使用ExecutorService构建CompletionService实例
		ExecutorCompletionService<XXX> completionService = new ExecutorCompletionService(service);

		// 提交任务
		completionService.submit(callable1);
		completionService.submit(callable2);
		// add more tasks...

		// 处理任务结果
		for (int i = 0; i < 任务数量; i++) {
			/*
				使用take()/pull()等方法获取下一个执行完毕任务结果。
				使用take()方法获取结果时只要服务中提交的任意任务完成方法就会返回，不必担心在某一个任务上等待时间过长。
			*/
			XXX xxx = completionService.take().get();
			/* do something... */
		}

		// 关闭线程池，CompletionService一样需要通过ExecutorService关闭线程池
		service.shutdown();
	}

}
```



## *Annotation* (注解)
注解(元数据)是`JDK 1.5`之后引入的机制，可以声明在**包**、**类**、**字段**、**方法**、**局部变量**、**方法参数**等的前面，用来对这些元素进行说明和注释。  
注解的相关内容在包`java.lang.annotation`中。

注解的基本语法为：

```java
@注解名称(注解参数...)
```

其中，注解的参数不是必须的，没有注解参数的注解称为**标记注解**。一个元素可以拥有**多个**注解。

### 内置注解
Java中提供了一系列**内置注解**，常用的有：

- `@Override`为**标记注解**，用于标记**重写**的方法，若被标记的方法没有发生重写行为，则编译时会得到错误警告。
- `@Deprecated`为**标记注解**，用于标记**废弃**的内容，作用与JavaDOC提供的`@deprecated`注解类似。
- `@SuppressWarnings`用于控制编译时的输出警告信息，该注解有多个参数，但都带有默认值。

### 元注解
**元注解**专门用来修饰其它注解，在**自定义注解**时会用到。

**元注解**有以下4类：

1. `@Target`用于限制注解的范围，参数为注解范围的数组(可以同时设定多个注解范围，用花括号包裹)，取值如下所示：

	- `ElementType.CONSTRUCTOR` 描述构造器
	- `ElementType.FIELD` 描述域
	- `ElementType.LOCAL_VARIABLE` 描述局部变量
	- `ElementType.METHOD` 描述方法
	- `ElementType.PACKAGE` 描述包
	- `ElementType.PARAMETER` 描述参数
	- `ElementType.TYPE` 描述类、接口(包括注解类型)或`enum`声明

1. `@Retention`设置注解的**生命周期**，取值如下所示：

	- `RetentionPolicy.SOURCE`

		注解在编译阶段丢弃。  
		被修饰的注解在编译结束之后就不再有任何意义，不会写入字节码。  
		`@Override`、`@SuppressWarnings`属于此类注解。

	- `RetentionPolicy.CLASS`

		在类加载的时候丢弃注解信息。  
		在字节码文件的处理中有用。注解**默认使用**这种方式。

	- `RetentionPolicy.RUNTIME`
	
		不丢弃注解信息。  
		运行期也保留该注解，可以使用反射机制读取该注解的信息。  
		**自定义注解**通常使用这种方式。

1. `@Inherited`为**标记注解**，用于设置注解的继承性：

	被改注解修饰的注解用在类中是**可继承的**，但类不从它所实现的接口继承注解，方法并不从它所重载的方法继承注解。  
	对于设置了`@Inherited`和`@Retention`元注解的注解，并且声明周期设为`RetentionPolicy.RUNTIME`时，则使用`反射`机制来获取元素注解，且检查不到该注解时，会一直沿着继承树向上搜索，直到查找到了该注解或到达类继承结构的顶层。

1. `@Documented`设置在使用`javadoc`生成API时记录注解信息。  
	默认情况下，`javadoc`**不会**记录注解信息。

### 自定义注解
`Java`中的注解实际上是**接口**(`interface`)。

- 使用`@interface`自定义注解，自定义注解继承了`java.lang.annotation.Annotation`接口。
- 定义注解时，**不能**继承其他的注解或接口。
- 定义注解时，每一个方法实际上是定义了一个配置参数。  
方法的名称就是参数的名称，返回值类型就是参数的类型。可以通过`default`关键字来设置参数**默认值**。
- 定义注解时，使用`value`做为注解参数名称，则使用注解时参数名称可省略。
- 定义注解时，参数的访问权限只能为`public`或**默认**权限。
- 注解参数支持的数据类型：
	1. 所有基本数据类型(`int`、`float`、`boolean`、`byte`、`double`、`char`、`long`、`short`)。
	1. `String`类型。
	1. `Class`类型。
	1. `enum`类型。
	1. `Annotation`类型。
	1. 上述类型的**一维**数组。

如下代码所示：

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
		//注解无需实例，可直接通过Class类获得
		Test test = TestAnnotation.class.getAnnotation(Test.class);
		System.out.println(test.value() + ": " + test.test() + " " + test.numbers()[0]);
	}
}
```

输出结果：

```
TestValue: Schwarzes marken 6
```



## *Reflection* (反射)
在`Java`中，**反射**机制提供了一系列**运行时**功能：

- 判断任意一个对象所属的类。
- 构造任意一个类的对象。
- 判断任意一个类所具有的成员变量和方法。
- 调用任意一个对象的方法。
- 获取目标的注解信息。
- 生成**动态代理**。

反射在Java各类框架中都有着大量的应用，如`Spring`中的`IOC`。

### 反射机制的相关类型
在`Java`中，反射相关的类型定义在包`java.lang.reflect`中，主要有以下类型：

- `Class` 表示一个类、接口
- `Field` 表示类的成员变量(字段)
- `Method` 表示类的成员方法
- `Constructor` 表示类的构造方法

### *Class* 类型
`Class`类定义了类型的反射操作，获取目标类型的`Class`实例是使用反射功能的起始步骤。

获取`Class`实例可以通过以下方式：

- `Xxx.class` 通过类型的`class`成员获得
- `Class.forName("class_path")` 通过类型名称获得(传入的类型字符串需要为完整路径)
- `instance.getClass()` 通过目标实例的`getClass()`方法获得

### 反射获取成员信息
`Java`中反射获取类型成员信息的相关`API`遵循以下命名规则：

- `getXxx()`用于获取**指定成员**，搜索范围为**公有成员**，包括继承的成员。
- `getDeclaredXxx()`用于获取**指定成员**，搜索范围为**所有访问权限成员**，不包括继承的成员。
- `getXxxs()`用于获取**所有成员**，搜索范围为**公有成员**，包括继承的成员。
- `getDeclaredXxxs()`用于获取**所有成员**，搜索范围为**所有访问权限成员**，不包括继承的成员。

1. 获取类型**完整路径**：

	`Class`类型的`getName()`方法返回类型的完整路径：

	```java
	Xxx.class.getName();
	```

1. 获取类型的**成员变量**：

	获取所有成员字段信息：

	```java
	public Field[] getFields() throws SecurityException;
	public Field[] getDeclaredFields() throws SecurityException;
	```

	通过字段名称获取指定字段的成员信息：

	```java
	public Field getField(String name) throws NoSuchFieldException, SecurityException;
	public Field getDeclaredField(String name) throws NoSuchFieldException, SecurityException;
	```

1. 获取类型的**成员方法**：

	获取所有成员方法信息：

	```java
	public Method[] getMethods() throws SecurityException;
	public Method[] getDeclaredMethods() throws SecurityException;
	```

	获取指定参数的方法信息，`name`参数为方法名称，`parameterTypes`参数为方法参数类型(变长参数)：

	```java
	public Method getMethod(String name, Class<?>... parameterTypes)
			throws NoSuchMethodException, SecurityException;
	public Method getDeclaredMethod(String name, Class<?>... parameterTypes)
			throws NoSuchMethodException, SecurityException;
	```

1. 获取类型的**构造方法**

	获取所有的构造方法信息：

	```java
	// 构造方法不存在继承关系，getConstructors()/getgetDeclaredConstructors()区别仅在于获取构造方法的访问权限不同
	public Constructor<?>[] getConstructors() throws SecurityException;
	public Constructor<?>[] getDeclaredConstructors() throws SecurityException;
	```

	获取指定参数的构造方法信息，`parameterTypes`参数为方法参数类型(变长参数)：

	```java
	public Constructor<T> getConstructor(Class<?>... parameterTypes)
			throws NoSuchMethodException, SecurityException;
	public Constructor<T> getDeclaredConstructor(Class<?>... parameterTypes)
			throws NoSuchMethodException, SecurityException;
	```

	内部类获取外部类的构造方法(非内部类返回`null`)：

	```java
	public Constructor<?> getEnclosingConstructor() throws SecurityException;
	```

示例代码如下所示：

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

		// 获取到了继承的方法
		System.out.println("\n\nPublic Methods:");
		for (Method method : classTest.getMethods())
			System.out.print(method.getName() + " ");

		// 获取内容不包括继承方法，但包含定义的保护/私有方法
		System.out.println("\n\nAll Methods:");
		for (Method method : classTest.getDeclaredMethods())
			System.out.print(method.getName() + " ");

		// 构造方法不存在继承的概念，因而只获取到当前类公有构造器
		System.out.println("\n\nPublic Constructor:");
		for (Constructor constructor : classTest.getConstructors())
			System.out.print(constructor.getName() + " ");

		System.out.println("\n\nAll Constructor:");
		for (Constructor constructor : classTest.getDeclaredConstructors())
			System.out.print(constructor.getName() + " ");

		// 对于非内部类，获取外部类的构造函数返回null
		System.out.println("\n\nEnclosing Constructor:");
		System.out.println(classTest.getEnclosingConstructor());
	}
}
```

运行输出结果：

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

### 反射构建类实例
如果一个类定义了空参的构造函数，则可以直接通过`Class`类中的成员方法来构造对象。

```java
public T newInstance() throws InstantiationException, IllegalAccessException;
```

`Class`类中没有直接提供通过**有参构造函数**反射构建实例的方式。  
若需要反射调用类的有参构造方法，则需要先获取其有参构造器(`Constructor`类型)，之后通过`Constructor`类的相关方法构造实例。

通过反射可以实现使用**非公有构造函数**构建对象。

```java
public Constructor<?>[] getDeclaredConstructors() throws SecurityException;
public Constructor<T> getDeclaredConstructor(Class<?>... parameterTypes)
		throws NoSuchMethodException, SecurityException;
```

实例如下代码所示：

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

		// 直接通过Class类调用无参构造函数
		Test.class.newInstance().showNum();

		// 获取构造器对象
		Constructor<Test> constructor = Test.class.getDeclaredConstructor(int.class);
		constructor.setAccessible(true);	//对于私有构造器默认是无法访问的，需要设置权限才能正常调用
		constructor.newInstance(200).showNum();
	}
}
```

输出结果：

```
0
200
```

### 反射调用对象方法
通过反射可以实现调用任意方法(包括**私有方法**)，方式与调用构造函数基本类似。

首先获取目标方法的`Method`对象，之后通过`Method`类的`invoke()`方法执行，第一个参数为类的实例，之后的参数为方法签名中的参数。

```java
public Object invoke(Object var1, Object... var2)
		throws IllegalAccessException, IllegalArgumentException, InvocationTargetException;
```

与`Constructor`类似，如果获取到的`Method`对象代表的是非公有成员方法，则需要使用`setAccessible()`方法设置属性为可访问才能正常调用。

实例代码如下，访问一个全部成员**私有**的类：

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
		constructor.setAccessible(true); //设置私有构造器可访问

		Test test = constructor.newInstance(200); //通过私有构造器构造对象，并传入初值

		Method method = Test.class.getDeclaredMethod("showNum", int.class);
		method.setAccessible(true); //设置方法的访问权限
		method.invoke(test, 100); //调用私有方法showNum()
	}
}
```

输出结果：

```
300
```

### 反射修改字段
通过反射亦可访问、修改类的非公有成员字段，方式类似。

通过`Field`类的相关的`set()`、`get()`方法设置、获取字段内容：

```java
public void set(Object var1, Object var2) throws IllegalArgumentException, IllegalAccessException;
public Object get(Object var1) throws IllegalArgumentException, IllegalAccessException;
```

- `set()`方法中参数`var1`为要设置字段所属的对象，参数`var2`为设置的内容。  
- `get()`方法同名参数作用相同。  
- `set()/get()`方法接收的参数为`Object`类型。

对于基本类型，`Field`类中预先定义了一套方法(`setInt()/getInt()/setBoolean()/getBoolean()`等)，基本类型可直接使用这些方法以避免不必要的强制类型转换。

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

### 反射判定继承关系
使用`Class`类中的`isAssignableFrom()`成员方法可以判定当前类型是否可以由目标类型转换得到：

```java
public native boolean isAssignableFrom(Class<?> cls);
```

`isAssignableFrom()`方法对于接口和类都有效，只要类型满足转换关系即可，如下所示：

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

输出结果：

```
true
true
true
```

### *ClassLoader* (类加载器)
在Java中有三种类加载器。

1. `Bootstrap ClassLoader`引导类加载器，用于加载`Java`核心类。
1. `Extension ClassLoader`扩展类加载器，它负责加载`JRE`的扩展目录(`JAVA_HOME/jre/lib/ext`或`java.ext.dirs`系统属性指定)类包。
1. `App ClassLoader`应用类加载器，通常类都由此加载器加载(包括`java.class.path`)。

获取一个类的加载器使用`getClassLoader()`方法。

展示一般应用类加载器：

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

输出结果：

```
sun.misc.Launcher$AppClassLoader
sun.misc.Launcher$AppClassLoader
```



## 动态代理
**动态代理**是反射机制的一种应用，能够动态地产生代理实例，避免为每一个接口方法编写大量的重复代理代码。

### 代理模式
**代理模式**是常见的设计模式，主要作用是通过创建**代理类**为其他对象提供一种代理，并以控制对这个对象的访问。

代理模式常见的应用场景有：

1. `Remote Proxy`远程代理，为一个位于不同的地址空间的对象提供一个本地的代理对象。这个不同的地址空间可以是在同一台主机中，也可是在另一台主机中。
1. `Virtual Proxy`虚拟代理，根据需要创建开销很大的对象。如果需要创建一个资源消耗较大的对象，先创建一个消耗相对较小的对象来表示，真实对象只在需要时才会被真正创建。
1. `Protection Proxy`保护代理，控制对原始对象的访问。保护代理用于对象应该有不同的访问权限的时候。
1. `Smart Reference`智能指引，取代了简单的指针，它在访问对象时执行一些附加操作，扩充原有对象的功能。
1. `Copy-on-Write`写时复制，它是虚拟代理的一种，把复制操作延迟到只有在客户端真正需要时才执行。

在`Java`中代理模式的典型方式是使用接口定义功能，实现类实现接口功能，而代理类控制/扩充实现类功能。  
代理类与实现类都`implements`接口，但代理类本身不直接实现具体功能，而是调用被其代理的实现类的方法。

### 动态代理实例
假设有一个文件接口`File`，定义了支持的文件操作：

```java
interface File {
	String getName();
	int getSize();
}
```

`FileImpl`类实现文件接口：

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

使用静态代理，则应创建一个**代理类**用于控制之前的实现。  
代理类同样需要实现基础接口，但代理类不同于实现类，代理类使用别的接口实现类的实现而不是自身实现功能。  
代理类在调用实现类功能的同时，也可以加入自身的扩充功能。

实现类以接口的形式被传入代理类，当一个接口有多种实现的时候，代理类能够针对每一种实现类都添加相同的功能。  
这就是所谓的`AOP`(面向切面编程)，代理类可以被视为是一个切面。

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

代理类`FileProxy`能够在调用实现具体代码的同时加入扩充的功能。

随着接口功能的扩充，代理类的代理方法数量也会增加，但代理类中很多方法的扩充代码可能相同的或是根本没有扩充代码，因而没有必要针对每一个方法编写代理方法，此时使用**动态代理**能够很方便地控制代码规模。

动态代理使用`java.lang.reflect.Proxy`类中的`newProxyInstance`方法构建代理类实例：

```java
public static Object newProxyInstance(ClassLoader loader,
		Class<?>[] interfaces, InvocationHandler h) throws IllegalArgumentException;
```

- `loader`参数为动态代理类的类加载器。
- `interfaces`参数为代理类实现的接口的数组。
- `h`参数为动态代理的具体内容。

`h`参数的类型为`InvocationHand`接口，定义如下：

```java
public interface InvocationHandler {
	Object invoke(Object proxy, Method method, Object[] args) throws Throwable;
}
```

- `proxy`参数为代理类。
- `method`参数为调用的方法。
- `args`参数为对调用方法传入的参数。

需要自行实现`InvocationHandler`接口，来实现动态代理的具体内容。  
以上文的`FileImpl`类为例，使用动态代理实现如下：

```java
class InvocationHandlerImpl implements InvocationHandler {

	File file = null;

	public InvocationHandlerImpl(File file) {
		this.file = file;
	}

	// 多个接口方法的代理扩展代码全部写在一个invoke()方法中
	@Override
	public Object invoke(Object proxy, Method method, Object[] args) throws Throwable {

		/*
			do something before...
		*/

		// 判断是否为静态方法，并使用不同的调用方式
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

		//类实现
		File fileImpl = new FileImpl();

		//代理规则
		InvocationHandler invocationHandler = new InvocationHandlerImpl(fileImpl);

		//生成动态代理对象
		File file = (File)Proxy.newProxyInstance(fileImpl.getClass().getClassLoader(),
			new Class[] { File.class }, invocationHandler);

		//通过动态代理对象调用方法
		file.getName();
		file.getSize();
	}

}
```



## *JDBC*
`JDBC`为`Java`定义了一套公用的数据库`API`，`JDBC`屏蔽了不同数据库之间的差异。  
对于支持`JDBC`的数据库，只要导入对应的`JDBC Driver`即可使用相同的`JDBC API`进行操作。

### 连接数据库
`JDBC API`相关类型位于`java.sql`包中：

- `DriverManager` JDBC驱动集合
- `Connection` 数据库连接
- `Statement` 数据库交互对象，用于执行各类SQL语句
- `PreparedStatement/CallableStatement` 包含扩展功能的数据库交互对象
- `ResultSet` 包含查询结果的集合

基本的访问数据库流程：

```java
String connectUrl = "jdbc:数据库类型://连接地址...";

try {
	Connection connection = DriverManager.getConnection(connectUrl);		//获取数据库连接
	Statement statement = connection.createStatement()
} catch (SQLException ex) {
	...
}
```

### 数据库操作
`Statement`类性提供了执行SQL语句的方法：

```java
// 执行查询语句并返回查询结果集
ResultSet executeQuery(String sql) throws SQLException;
// 执行更新语句并返回更新的数目
int executeUpdate(String sql) throws SQLException;
```

查询结果返回的结果集`ResultSet`，常用方法：

```java
// 将光标移动到正好位于第一行之前
public void beforeFirst() throws SQLException;
// 将光标移动到刚刚结束的最后一行
public void afterLast() throws SQLException;
// 将光标移动到第一行
public boolean first() throws SQLException;
// 将光标移动到最后一行
public void last() throws SQLException;
// 将光标移动到指定的行
public boolean absolute(int row) throws SQLException;
// 从它目前所指向向前或向后移动光标行的给定数量
public boolean relative(int row) throws SQLException;
// 将光标移动到上一行，上一行关闭的结果集此方法返回false
public boolean previous() throws SQLException;
// 将光标移动到下一行，如果没有更多的行结果集中的此方法返回false
public boolean next() throws SQLException;
// 返回的行号，该光标指向的行
public int getRow() throws SQLException;
// 将光标移动到一个特殊的行，可以用来插入新行插入到数据库中的结果集，当前光标位置被记住
public void moveToInsertRow() throws SQLException;
// 移动光标返回到当前行，如果光标在当前插入行，否则，这个方法不执行任何操作
public void moveToCurrentRow() throws SQLException;
```

基本操作如下所示：

```java
ResultSet resultSet = statement.executeQuery("SQL查询语句...");
while (resultSet.next()) {		// 使用 next() 方法将当前游标移动到下一行
	resultSet.getInt(...);		// 获取数据，支持使用列号/列名进行获取
	resultSet.getString(...);
}
```

### 获取时间
`ResultSet`类型提供了以下方法用于获取时间类型(如`MySQL`中的`DateTime`)信息：

- `getDate()` 获取日期信息
- `getTime()` 获取时间信息
- `getTimestamp()` 获取完整时间信息

对于时间类型的数据，使用`getDate()`、`getTime()`等方法获取到的时间信息不完整：

- `getDate()`获取到的仅为日期信息，小时、分钟、秒等信息被置为默认(`00:00:00`)。
- `getTime()`获取到的时间信息不包含日期，日期部分被置为默认(`1970-1-1`)

使用`getTimestamp()`方法才能获取到完整的时间信息。

### 与 *Access* 数据库交互
`JDK 1.7`之前，可以使用`JDBC-ODBC`桥接`Access`数据库。  
在`JDK 1.8`之后，`JDBC-ODBC`桥被移除，只能使用专有的`Access`驱动来连接`Access`数据库(驱动名称：`Access_JDBC40.jar`)。

连接Access数据库：

```java
// 这样写是相对路径
String connectUrl = "jdbc:Access:///***.accdb";

// 这样写是绝对路径
//String connectUrl = "jdbc:Access:///c:/a/b/***.accdb";

// 注册驱动
Class.forName("com.hxtt.sql.access.AccessDriver");
// 创建连接
Connection connection = DriverManager.getConnection(connectUrl);
Statement statement = connection
	.createStatement(
		ResultSet.TYPE_SCROLL_INSENSITIVE,
		ResultSet.CONCUR_READ_ONLY);
		//后两个参数是为了得到resultSet集能够进行last()操作
```

Access数据库的一些小常识：
- 表单的高级字段设置在`开始 - 视图 - 设计视图`中。
- 配置自增属性需要将字段类型设为`自动编号`。
- 默认情况下，创建的数据类型`数字`的字段大小为`长整型`。  
	长整型不支持**小数输入**，小数输入会自动被去尾。  
	需要将字段大小设置为`单精度浮点型/双精度浮点型`才能支持小数位。
- 如果需要某个字段的内容唯一不可重复，可以将改字段的索引设置为`有(无重复)`即可。



## *Eclipse* 使用注记
`Eclipse`是Java开发中最常用的IDE，`Eclipse`通过插件扩展可以进行多种语言的开发。

### 添加 *Marketplace*
`Eclipse Marketplace`是`Eclipse`新增的应用商店，可以从中直接安装`e(fx)clipse`、`GoClipse`、`ScalaIDE`、`PyDev`等由第三方社区维护的插件。

在部分`Eclipse`版本中，`Marketplace`没有默认安装，手动添加：

`Help` =>
`Install New Software` =>
`General Purpose Tools` =>
`Marketplace Client`

### 在Eclipse中查看JDK类源码
与**NetBeans**不同，在Eclipse中默认是无法直接查看JDK中类库的源码的，需要手动指定源码的位置。  
一般情况下，JDK源码位于JDK的安装目录下的`src.zip`文件中。

在Eclipse中按以下步骤添加源码路径：

`Window` =>
`Preferences` =>
`Java` =>
`Installed JREs` =>
选中使用的`JRE` =>
`Edit` =>
选中`../xxx/rt.jar` =>
`Source Attachment Configuration` =>
`Exernal location` =>
选中`src.zip` =>
`OK` =>
`Finish`

### 设置Eclipse编辑器自动换行
Eclipse的编辑器没有自动换行的功能，该功能需要通过第三方插件进行实现。  
在Eclipse中按以下步骤安装`Word Wrap`插件使编辑器能够自动换行：

`Help` => 
`Install New Software` => 
`Add Repository` =>
输入仓库地址`http://ahtik.com/eclipse-update` =>
安装`WordWrap`插件 =>
安装完成之后重启IDE =>
编辑器中点右键，激活`Word Warp`选项 =>
`Finish`



## *IntelliJ IDEA* 使用注记
`IntelliJ IDEA`相比`Eclipse`而言，有着更精美的UI，且对`Scala`、`Golang`等冷门语言有着更好的支持。

### 设置显示行号和不可见空白
选择选项：

`File`=>`Settings`=>`Editor`=>`General`=>`Appearance`=> ...

- 勾选`Show whitespaces(显示空白)`和`Show line numbers(显示行号)`选项。
- 勾选`Show menthod separators`则会在方法定义之间出现横线做为分隔符。

### 设置缩进
默认情况下，IDEA使用的是**空格**做为缩进，如果需要使用**tab缩进**，则按以下菜单路径设置：

`File` => `Settings` => `Editor` => `Code Style` => `[目标语言]` => `Tabs and Indents`

- 选中`Use tab charactor`。
- 勾选`Smart tabs`则会在**行尾**使用tab键时使用**空格**代替`Tab`。
- 勾选`Keep indents on empyt lines`则会在**空行**中**保持缩进**。

### 其它常用选项
`File` => `Settings` => `Editor` => `General`：

- `Code Folding` 代码折叠
- `Soft Wraps` 代码自动换行
- `Appearance` => `Show right margin` 设置代码边界指示线
- `Virtual Space` 虚空格(空白处的点按逻辑)
- `Other` => `Show quick documentation on mouse move` 光标悬停显示变量/方法信息

`File` => `Settings` => `Editor` => `Code Style`：

- `Java` => `Spaces` => `After type cast` Java强制类型转换前是否空格
- `Scala` => `Other` => `Enfore procedure syntax for methods with Unit return type`  
	Scala函数是否自动补全空返回类型
- `Scala` => `Wrappings and Braces` => `Class definition` => `Place self type on new line`  
	Scala自身类型参数在类定义中是否另起一行
- `[目标语言]` => `Wrappings and Braces` => `Method parenttheses` => `Align when multiline`  
	函数多行参数是否自动对齐到函数名
- `[目标语言]` => `Blank Lines` => `Minimum Blank Lines` 方法、字段前空行数量

`File` => `Settings` => `Project` => `Inspections` => `Spelling` 设置是否开启拼写检查

`File` => `Settings` => `Languages & Frameworks` => `JavaScript` => `JavaScript language version` => `ECMAScript 6`  
设置`JavaScript`支持`ECMAScript 6`语法

### 项目打包
将`Java`项目打包成`jar`、`war`等分发格式，按以下菜单路径设置：

`File` => `Project Structure` => `Project Settings` => `Artifacts`

选择界面中的`+`符号添加打包配置，根据项目类型打包成不同的目标格式。



## 常见问题记录

### *String.split()* 方法
函数的定义为：

```java
public String[] split(String regex);
```

`String`类中提供的文本切片函数`String.split()`接收的参数是**正则表达式**(Regex)。  
以一些**特殊符号**(`.`、`+`等)作为分隔符时，不能直接使用符号本身，而是需要使用转义符号，如以**小数点**作为分隔符切片需要写成：

```java
String[] nums = "123.456.789".split("\\.");
```

其它文本处理方法如`String.replace()`、`String.join()`等也有以正则表达式为匹配参数的重载版本，使用方式类似。

### *String.format()* 方法
函数的定义为：

```java
public static String format(String var0, Object... var1);
public static String format(Locale var0, String var1, Object... var2);
```

`String`类的`format()`方法提供类似C语言中`sprintf()`函数类似的文本格式化方式，格式化字段的语法类似。

### 查询 *OS* 信息
使用`System`类中的`getProperty()`方法可以获取**操作系统**以及**Java虚拟机**的各类状态信息：

```java
public static String getProperty(String key);
```

其中，参数`key`为需要获取信息的类型。

常用系统信息的`key`如下：

| key | 信息内容 |
|:----|:--------|
| line.separator | 行分隔符(UNIX中是`/n`，Win中是`/r/n`) |
| os.name | 操作系统的名称 |
| os.arch | 操作系统的架构 |
| os.version | 操作系统的版本 |
| user.name | 用户的账户名称 |
| user.home | 用户的主目录 |
| user.dir | 用户的当前工作目录 |
