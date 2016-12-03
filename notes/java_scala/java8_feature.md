[TOC]

## 接口默认方法
在**Java8**中，接口允许拥有带有方法实现的默认方法，在方法前使用关键字`default`来区别于普通的抽象方法。

一个接口可以有多个默认方法，也可以只有默认方法而不含有传统的抽象方法，同时，默认方法不强制子类重写，并且可以像类的成员方法一样被继承。
例如：

```java
interface Test<T> {
	default T abcd(T a) {
		return a;
	}
	default T abc(T a) {
		return a;
	}
}
```

当一个类实现了多个带有相同函数签名的默认方法的接口，需要重写引发冲突的默认方法。
例如：

```java
//接口Test1中含有默认方法"T abc(T a)"
interface Test1<T> {
	default T abc(T a) {
		return a;
	}
}

//接口Test2中也含有默认方法"T abc(T a)
interface Test2<T> {
	default T abc(T a) {
		return a;
	}
}

//类Test同时实现接口test1和test2
class Test<T> implements Test1<T>, Test2<T> {
	@Override
	public T abc(T a) {
		......
		return ...
	}
}
```

如果你想在重写的方法中直接使用原先接口中的某个默认方法实现，可以使用`super`关键字。
例如：

```java
//类中的"T abc(T a)"方法用Test1接口中的默认方法实现
class Test<T> implements Test1<T>, Test2<T> {
	@Override
	public T abc(T a) {
		//如果重写的是返回值为void的函数，则直接使用"test1.super.abc(a);"，作用是执行test1的对应默认方法。
		return Test1.super.abc(a);
	}
}
```

一个类实现多个带有默认方法的接口，在一定程度上类似于C++中的**多重继承**。



## *Lambda*
**Java 8**中加入的另一个重要的特性即为**Lambda表达式**。

### 使用Lambda表达式表示函数接口
**Lambda表达式**用于实现**函数接口**，函数接口是**有且只有一个**抽象方法的接口。

函数接口可以使用`@FunctionalInterface`注解，被其标注的接口中若含有**多个**抽象方法则无法通过编译。
例如：

```java
// 编译报错
@FunctionalInterface
interface Test<T> {
	T getT(T a);
	T getT1();
}
```

编译报错，提示：

```
Error: java: Unexpected @FunctionalInterface annotation
	Test is not a functional interface
		multiple non-overriding abstract methods found in interface Test
```

对于**函数接口**，只能带有一个**抽象方法**，但可以带有任意数量的**默认方法**。
例如：

```java
// 以下接口定义符合函数接口要求
@FunctionalInterface
interface Test<T> {
	T getT(T a);
	default T abc(T a) {
		return a;
	}
	default T abcd(T a) {
		return a;
	}
}
```

在Java8之前，要实例化一个接口，一般使用**匿名类**。
例如：

```java
@FunctionalInterface
interface Test<T> {
	T getT(T a);
}

Test<Integer> t = new Test<Integer>() {
	@Override
	public Integer getT(Integer a) {
		return a;
	}
};
```

在**Java8**之后，即可以使用新特性**Lambda表达式**来表示**函数接口**。
例如：

```java
Test<Integer> t = (Integer a) -> a;
```

### Lambda表达式的一般用法
对于一个如下定义的函数：

```java
int function(参数列表) {
	// 函数内容
	return 返回值;
}
```

对应的Lambda表达式格式为：

```java
(参数列表) -> {
	// 函数内容
	return 返回值;
}
```

如果函数体只有一句表达式，则可以省略大括号，简写成：

```java
(参数表) -> 表达式;
```

比如有以下函数定义：

```java
int get2(int a) {
	return 2 * a;
}
```

使用Lambda表达式可以写成：

```java
(a) -> { return 2 * a; };
(a) -> 2 * a;		//省略大括号
```

特别的，在参数只有一个时，可以省略括号直接写成：

```java
a -> 2 * a;
```

Lambda表达式能够**访问**外部作用域中的变量。
在Java中，Lambda捕获的外部作用域变量会自动带有`final`属性，因而在Lambda中不能对引用的外部作用域变量进行更改(变量若为类实例，则类内成员**不受**影响)。
在其它支持Lambda表达式的主流语言中，`C#`中的Lambda可以修改外部作用域的变量，`C++`可以控制外部变量的捕获方式，对于**引用捕获**的变量，可以修改其值。

### 方法引用
对于函数接口，还可以将当前类的某个符合方法签名的方法作为引用实例化函数接口对象。
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

使用操作符`::`将符合签名的方法作为重写内容构造出接口对象。
需要注意的是，接口的成员方法为公有成员，但如果使用方法引用实现接口时，不必考虑被引用方法的访问限制，即使是本类的私有成员，一样可以作为引用来实现接口，但如果是重写接口则必须访问权限为`public`(重写权限必须大于等于原有权限)。
只要**方法签名**相同(返回值类型可以不同)，你甚至可以使用抽象方法来作为引用来实现一个函数接口。

### 使用类库中的函数接口
在**Java 8**中，`java.util.function`包中预定义了一系列的泛型函数接口。

- `Function<T, R>`可以接收两个泛型类型，`T`表示参数类型，`R`表示返回值类型，类似于**C#**中的Function类。
- 由于Java泛型的限制，`Function<T, R>`不能接受基础类型如`int`和`double`等作为泛型参数，如果需要使用基础类型作为参数，可以使用`IntFunction<R>`，该接口返回泛型类型`R`，参数类型则为`int`。
- 如果需要在参数使用中使用其它基础类型，可以使用`java.util.function`包中定义的其它预定义接口如`DoubleFunction<R>`(接收参数`double`型)、`LongFunction<R>`(接收参数`long`型)。
- 如果需要在函数接口中使用更多数量的参数，`java.util.function`包中还定义了`BiFunction<T, U, R>`(可接收两个参数)，当参数数量大于两个时，需要自行定义。
- 对于无需返回值的方法，可以使用`Consumer<T>`以及相关接口，`Consumer`相关接口的定义的方法返回类型皆为`void`，类似于**C#**中的`Action`类。

需要注意的是，`java.util.function`包中预定义的一系列函数接口只是简化了函数接口的定义，而**Java8**中的函数接口并不能做到类似**C#**中的**委托**那样直接以函数的形式进行调用。
**Java8**中的Lambda表达式只是简化了实现单方法函数接口的过程，**仅此而已**。

如下所示：

```java
import java.util.function.*;

public class Main {
	public static void main(String[] args) {

		// 实例化函数接口对象
		Function<Integer, Integer> function = in -> 2 * in;
		IntFunction<Integer> intFunction = in -> 2 * in;
		Consumer<Integer> consumer = in -> System.out.println(in);

		/*
			使用函数接口对象，仍然需要明确调用函数接口中的方法
			Function系列的有返回值的接口调用方法apply()
			Consumer系列的无返回值的接口调用方法accept()
		*/
		System.out.println(function.apply(100));
		consumer.accept(200);
	}
}
```
