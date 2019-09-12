<!-- TOC -->

- [Fixed-Point (不動點)](#fixed-point-不動點)
- [Fixed-Point Combinator (不動點組合子)](#fixed-point-combinator-不動點組合子)
- [Y組合子實例](#y組合子實例)
	- [展開Y組合子](#展開y組合子)
	- [調用自身](#調用自身)
	- [單步遞歸函數](#單步遞歸函數)
	- [實現Y組合子](#實現y組合子)
	- [各語言完整源碼](#各語言完整源碼)

<!-- /TOC -->



# Fixed-Point (不動點)
不動點的定義是`被這個函數映射到其自身一個點`。

函數`f`的不動點是一個值`x`使得`f(x) == x`。
若`f`爲高階函數，則`f`的不動點是一個函數`g`滿足`f(g) == g`。



# Fixed-Point Combinator (不動點組合子)
不動點組合子是用於計算一個函數的不動點的高階函數。
對於任意函數`f`，不動點組合子`Fix`滿足`f(Fix(f)) == Fix(f)`。
不動點組合子有多種，最常見的是`Y組合子`。

Y組合子的數學定義爲`Y = λf.(λx.f(x x))(λx.f(x x))`。
由普通`Y`組合子的部分的`η-`展開則可得到`Z`組合子：`Z = λf.(λx.f(λy.x x y))(λx.f(λy.x x y))`

使用不動點組合子能夠使Lambda遞歸地調用自身。
使用各種語言實現Y組合子參考`http://rosettacode.org/wiki/Y_combinator`。



# Y組合子實例
使用Y組合子來實現階乘和斐波那契數列。

## 展開Y組合子
在Lambda演算中，函數接受另一個函數作爲參數，在求值策略爲**立即求值**的編程語言中，
直接使用Y組合子編寫代碼能夠通過編譯，但在運行階段會無限遞歸直至棧溢出。

爲了正確地適應求值策略，應當對Y組合子進行部分`η-`展開，以下兩種展開方式都能正確地在傳值調用情況下使用：

- `λf.(λx.f(x x))(λx.f(λy.x x y))`
- `λf.(λx.f(x x))(λx.λy.f(x x)y)`

或者直接使用`Z組合子`。

## 調用自身
不動點組合子`Y`的數學表示爲`Y = λf.(λx.f(x x))(λx.f(x x))`，其中`x`和`λx.f(x x)`的類型是一個具備調用自身邏輯的高階函數。
在**顯式類型**的編程語言中，需要首先確定這個高階函數的實際類型。

在`C#`中，可以簡單地使用一個**泛型委託**來表示：

```csharp
delegate T Self<T>(Self<T> self);
```

對應到階乘函數，則泛型參數應爲`Func<int, int>`。
這個委託接受自身作爲參數，返回真正的被調函數。

在`Scala`語言中，可以使用一個`泛型樣例類`或是`泛型隱式類`來表示：

```scala
// 使用樣例類表示
case Self[T](in: Self[T] => T) {
	def apply(self: Self[T]) = in(self)
}

// 使用隱式類表示
implicit class ImSelf[T](in: ImSelf[T] => T) {
	def apply(self: ImSelf[T]) = in(self)
}
```

定義的樣例類和隱式類內部實現了`apply()`方法，使得該類實例可以像函數一樣調用。
對應到階乘函數，則泛型參數爲`Int => Int`。

在`Java`語言中，可以參考`Scala`中的實現方式，實現`Function`接口：

```java
class Self<T> implements Function<Self<T>, T> {

	private Function<Self<T>, T> in;

	public Self(Function<Self<T>, T> in) { this.in = in; }

	public T apply(Self<T> self) { return in.apply(self); }
}
```

對應到階乘和斐波那契數列，則泛型參數應爲`Function<Integer, Integer>`。

## 單步遞歸函數
階乘和斐波那契運算使用遞歸方式的單步函數，使用`C#`可以寫成：

```csharp
// 階乘
Func<Func<int, int>, Func<int, int>> fac = x => n => n < 2 ? 1 : n * x(n - 1);
// 斐波那契數列
Func<Func<int, int>, Func<int, int>> fib = x => n => n < 2 ? n : x(n - 1) + x(n - 2);
```

使用`Scala`可以寫成：

```scala
// 階乘
val fac = (x: Int => Int) => (n: Int) => if (n < 2) 1 else n * x(n - 1)
// 斐波那契數列
val fib = (x: Int => Int) => (n: Int) => if (n < 2) n else x(n - 1) + x(n - 2)
```

Java中的函數接口不能真正地使用函數語法調用，使用Java語言需要寫成：

```java
// 階乘
Function<Function<Integer, Integer>, Function<Integer, Integer>> fac =
	x -> n -> n < 2 ? 1 : n * x.apply(n - 1);
// 斐波那契數列
Function<Function<Integer, Integer>, Function<Integer, Integer>> fib =
	x -> n -> n < 2 ? n : x.apply(n - 1) + x.apply(n - 2);
```

## 實現Y組合子
Y組合子的兩種展開形式，用C#可以表示爲：

```csharp
// λf.(λx.f(x x))(λx.f(λy.x x y))
Func<Func<Func<int, int>, Func<int, int>>, Func<int, int>> Y0 =
	f => ((Self<Func<int, int>>)(x => f(x(x))))((Self<Func<int, int>>)(x => f(y => x(x)(y))));
// λf.(λx.f(x x))(λx.λy.f(x x)y)
Func<Func<Func<int, int>, Func<int, int>>, Func<int, int>> Y1 =
	f => ((Self<Func<int, int>>)(x => f(x(x))))((Self<Func<int, int>>)(x => y => f(x(x))(y)));
```

使用Scala可以表示爲：

```scala
// λf.(λx.f(x x))(λx.f(λy.x x y)) 使用樣例類
val Y0 = (f: (Int => Int) => Int => Int) =>
	((x: Self[Int => Int]) => f(x(x)))(Self[Int => Int](x => f(y => x(x)(y))))
// λf.(λx.f(x x))(λx.λy.f(x x)y) 使用隱式類
val Y1 = (f: (Int => Int) => Int => Int) =>
	((x: ImSelf[Int => Int]) => f(x(x)))((x: ImSelf[Int => Int]) => (y: Int) => f(x(x))(y))
```

使用Java可以表示爲：

```java
// λf.(λx.f(x x))(λx.f(λy.x x y))
Function<Function<Function<Integer, Integer>, Function<Integer, Integer>>, Function<Integer, Integer>> Y0 =
	f -> (new Self<Function<Integer, Integer>>(x -> x.apply(x)))
		.apply(new Self<Function<Integer, Integer>>(x -> f.apply(y -> x.apply(x).apply(y))));
// λf.(λx.f(x x))(λx.λy.f(x x)y)
Function<Function<Function<Integer, Integer>, Function<Integer, Integer>>, Function<Integer, Integer>> Y1 =
	f -> (new Self<Function<Integer, Integer>>(x -> x.apply(x)))
		.apply(new Self<Function<Integer, Integer>>(x -> y -> f.apply(x.apply(x)).apply(y)));
```

在**隱式類型**的語言中，實現Y組合子則無需確定自身調用邏輯的高階函數的實際類型，如使用`Python`表示爲：

```py
# λf.(λx.f(x x))(λx.f(λy.x x y))
Y0 = lambda f: (lambda x: f(x(x)))(lambda x: f(lambda y: x(x)(y)))
# λf.(λx.f(x x))(λx.λy.f(x x)y)
Y1 = lambda f: (lambda x: f(x(x)))(lambda x: lambda y: f(x(x))(y))
```

使用得到的Y組合子將單步遞歸函數作爲參數即可得到最終的目標函數。

在`C++14`之後，C++可以使用**泛型Lambda**，使用`C++14`實現Y組合子同樣無需確定調用自身邏輯的高階函數具體類型，可以使用`auto`關鍵字讓模版類型自動推斷，使用`C++14`表示Y組合子：

```cpp
// λf.(λx.f(x x))(λx.f(λy.x x y))
auto Y0 =
	[](auto f)
		{ return [&](auto x) { return f(x(x)); }
			([&](auto x) -> std::function<int(int)>
				{ return f([&](auto n) { return x(x)(n); }); }); };

// λf.(λx.f(x x))(λx.λy.f(x x)y)
auto Y1 =
	[](auto f)
		{ return [&](auto x) { return f(x(x)); }
			([&](auto x) -> std::function<int(int)>
				{ return [&](auto n) { return f(x(x))(n); }; }); };
```

## 各語言完整源碼
使用`Scala`、`Python`、`C#`、`C++`等語言使用Y組合子計算斐波那契數列和階乘的結果。

`Scala`(Scala 2.11.8)

```scala
object Main extends App {

	implicit class Self(in: Self => Int => Int) {
		def apply(self: Self) = in(self)
	}

	val fac = (x: Int => Int) => (n: Int) => if (n < 2) n else n * x(n - 1)
	val fib = (x: Int => Int) => (n: Int) => if (n < 2) n else x(n - 1) + x(n - 2)

	val Y0 = (f: (Int => Int) => Int => Int) => ((x: Self) => f(x(x)))((x: Self) => f(n => x(x)(n)))
	val Y1 = (f: (Int => Int) => Int => Int) => ((x: Self) => f(x(x)))((x: Self) => (n: Int) => f(x(x))(n))

	println("Factorial(5): " + Y0(fac)(5))
	println("Fibonacci(5): " + Y0(fib)(5))

	println("Factorial(10): " + Y1(fac)(10))
	println("Fibonacci(10): " + Y1(fib)(10))
}
```

`C#`(Mono 4.4.0.0 && ArchLinux x64)

```cs
using System;

delegate Func<int, int> Self(Self self);

class Y
{
	static void Main(string[] args)
	{
		Func<Func<Func<int, int>, Func<int, int>>, Func<int, int>> Y0 = f =>
			((Self)(x => f(x(x))))((Self)(x => n => f(x(x))(n)));
		Func<Func<Func<int, int>, Func<int, int>>, Func<int, int>> Y1 = f =>
			((Self)(x => f(x(x))))((Self)(x => f(n => x(x)(n))));

		Func<Func<int, int>, Func<int, int>> fac = x => n => n < 2 ? n : n * x(n - 1);
		Func<Func<int, int>, Func<int, int>> fib = x => n => n < 2 ? n : x(n - 1) + x(n - 2);

		Console.WriteLine("Factorial(5): " + Y0(fac)(5));
		Console.WriteLine("Fibonacci(5): " + Y1(fib)(5));

		Console.WriteLine("Factorial(10): " + Y1(fac)(10));
		Console.WriteLine("Fibonacci(10): " + Y1(fib)(10));
	}
}
```

`Java`(OpenJDK 1.8.0_92 && ArchLinux x64)

```java
import java.util.function.Function;

class Self implements Function<Self, Function<Integer, Integer>> {

	private Function<Self, Function<Integer, Integer>> in;

	public Self(Function<Self, Function<Integer, Integer>> in) { this.in = in; }

	public Function<Integer, Integer> apply(Self self) { return in.apply(self); }
}

class Main {

	public static void main(String[] args) {

		Function<Function<Integer, Integer>, Function<Integer, Integer>> fac =
			x -> n -> n < 2 ? 1 : n * x.apply(n - 1);
		Function<Function<Integer, Integer>, Function<Integer, Integer>> fib =
			x -> n -> n < 2 ? n : x.apply(n - 1) + x.apply(n - 2);

		Function<Function<Function<Integer, Integer>, Function<Integer, Integer>>, Function<Integer, Integer>> Y0 =
			f -> (new Self(x -> x.apply(x))).apply(new Self(x -> f.apply(n -> x.apply(x).apply(n))));
		Function<Function<Function<Integer, Integer>, Function<Integer, Integer>>, Function<Integer, Integer>> Y1 =
			f -> (new Self(x -> x.apply(x))).apply(new Self(x -> n -> f.apply(x.apply(x)).apply(n)));

		System.out.println("Factorial(5): " + Y0.apply(fac).apply(5));
		System.out.println("Fibonacci(5): " + Y0.apply(fib).apply(5));

		System.out.println("Factorial(10): " + Y1.apply(fac).apply(10));
		System.out.println("Fibonacci(10): " + Y1.apply(fib).apply(10));
	}
}
```

`C++`(GCC 6.1.1 && ArchLinux x64)

```cpp
#include <iostream>
#include <functional>

int main(void)
{
	auto Y0 =
		[](auto f)
			{ return [f](auto x) { return f(x(x)); }
				([f](auto x) -> std::function<int(int)>
					{ return [&](auto n) { return f(x(x))(n); }; }); };
	auto Y1 =
		[](auto f)
			{ return [f](auto x) { return f(x(x)); }
				([f](auto x) -> std::function<int(int)>
					{ return f([x](auto n) { return x(x)(n); }); }); };

	auto fac =
		[](auto x)
			{ return [x](auto n)
				{ return n < 2 ? n : n * x(n - 1); }; };
	auto fib =
		[](auto x)
			{ return [x](auto n)
				{ return n < 2 ? n : x(n - 1) + x(n - 2); }; };

	std::cout << "Factorial(5): " << Y0(fac)(5) << std::endl;
	std::cout << "Fibonacci(5): " << Y0(fib)(5) << std::endl;

	std::cout << "Factorial(10): " << Y1(fac)(10) << std::endl;
	std::cout << "Fibonacci(10): " << Y1(fib)(10) << std::endl;

	return 0;
}
```

`Python`(Python 3.5.1)

```py
Y0 = lambda f: (lambda x: f(x(x)))(lambda x: f(lambda y: x(x)(y)))
Y1 = lambda f: (lambda x: f(x(x)))(lambda x: lambda y: f(x(x))(y))

fac = lambda x: lambda n: n < 2 and n or n * x(n - 1)
fib = lambda x: lambda n: n if n < 2 else x(n - 1) + x(n - 2)

print("Factorial(5): %d" % Y0(fac)(5))
print("Fibonacci(5): %d" % Y0(fib)(5))

print("Factorial(10): %d" % Y1(fac)(10))
print("Fibonacci(10): %d" % Y1(fib)(10))
```

輸出結果：

```
Factorial(5): 120
Fibonacci(5): 5
Factorial(10): 3628800
Fibonacci(10): 55
```
