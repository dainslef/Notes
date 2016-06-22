## 不动点(Fixed-point)
不动点的定义是`被这个函数映射到其自身一个点`。

函数`f`的不动点是一个值`x`使得`f(x) == x`。
若`f`为高阶函数，则`f`的不动点是一个函数`g`满足`f(g) == g`。



## 不动点组合子(Fixed-point combinator)
不动点组合子是用于计算一个函数的不动点的高阶函数。
对于任意函数`f`，不动点组合子`Fix`满足`f(Fix(f)) == Fix(f)`。
不动点组合子有多种，最常见的是`Y组合子`。

Y组合子的数学定义为`Y = λf.(λx.f(x x))(λx.f(x x))`。

由普通`Y`组合子的部分的`η-`展开则可得到`Z`组合子：
`Z = λf.(λx.f(λy.x x y))(λx.f(λy.x x y))`

使用不动点组合子能够使Lambda递归地调用自身。
使用各种语言实现Y组合子参考`http://rosettacode.org/wiki/Y_combinator`。



## Y组合子实例
使用Y组合子来实现阶乘和斐波那契数列。

### 展开Y组合子
在Lambda演算中，函数接受另一个函数作为参数，而在编程语言中是`传值调用`的，直接使用Y组合子编写代码能够通过编译，但在运行阶段会无限递归直至栈溢出。

为了正确地使用传值调用，应当对Y组合子进行部分`η-`展开，以下两种展开方式都能正确地在传值调用情况下使用：

- `λf.(λx.f(x x))(λx.f(λy.x x y))`
- `λf.(λx.f(x x))(λx.λy.f(x x)y)`

或者直接使用`Z组合子`。

### 调用自身
不动点组合子`Y`的数学表示为`Y = λf.(λx.f(x x))(λx.f(x x))`，其中`x`和`λx.f(x x)`的类型是一个具备调用自身逻辑的高阶函数。在**显式类型**的编程语言中，需要首先确定这个高阶函数的实际类型。

在`C#`中，可以简单地使用一个**泛型委托**来表示：

```csharp
delegate T Self<T>(Self<T> self);
```

对应到阶乘函数，则泛型参数应为`Func<int, int>`。
这个委托接受自身作为参数，返回真正的被调函数。

在`Scala`语言中，可以使用一个`泛型样例类`或是`泛型隐式类`来表示：

```scala
// 使用样例类表示
case Self[T](in: Self[T] => T) {
	def apply(self: Self[T]) = in(self)
}

// 使用隐式类表示
implicit class ImSelf[T](in: ImSelf[T] => T) {
	def apply(self: ImSelf[T]) = in(self)
}
```

定义的样例类和隐式类内部实现了`apply()`方法，使得该类实例可以像函数一样调用。
对应到阶乘函数，则泛型参数为`Int => Int`。

### 单步递归函数
阶乘和斐波那契运算使用递归方式的单步函数，使用`C#`可以写成：

```csharp
// 阶乘
Func<Func<int, int>, Func<int, int>> far = x => n => n < 2 ? 1 : n * x(n - 1);
// 斐波那契数列
Func<Func<int, int>, Func<int, int>> fib = x => n => n < 2 ? n : x(n - 1) + x(n - 2);
```

使用`Scala`可以写成：

```scala
// 阶乘
val far = (x: Int => Int) => (n: Int) => if (n < 2) 1 else n * x(n - 1)
// 斐波那契数列
val fib = (x: Int => Int) => (n: Int) => if (n < 2) n else x(n - 1) + x(n - 2)
```

### 实现Y组合子
Y组合子的两种展开形式，用`C#`可以表示为：

```csharp
// λf.(λx.f(x x))(λx.f(λy.x x y))
Func<Func<Func<int, int>, Func<int, int>>, Func<int, int>> Y0 =
	f => ((Self<Func<int, int>)(x => f(x(x))))((Self<Func<int, int>>)(x => f(y => x(x)(y))));
// λf.(λx.f(x x))(λx.λy.f(x x)y)
Func<Func<Func<int, int>, Func<int, int>>, Func<int, int>> Y1 =
	f => ((Self<Func<int, int>)(x => f(x(x))))((Self<Func<int, int>>)(x => y => f(x(x))(y)));
```

使用`Scala`可以表示为：

```scala
// λf.(λx.f(x x))(λx.f(λy.x x y)) 使用样例类
val Y0 = (f: (Int => Int) => Int => Int) =>
	((x: Self[Int => Int]) => f(x(x)))(Self[Int => Int](x => f(y => x(x)(y))))
// λf.(λx.f(x x))(λx.λy.f(x x)y) 使用隐式类
val Y1 = (f: (Int => Int) => Int => Int) =>
	((x: ImSelf[Int => Int]) => f(x(x)))((x: ImSelf[Int => Int]) => (y: Int) => f(x(x))(y))
```

在**隐式类型**的语言中，实现Y组合子则无需确定自身调用逻辑的高阶函数的实际类型，如使用`Python`表示为：

```py
# λf.(λx.f(x x))(λx.f(λy.x x y))
Y0 = lambda f: (lambda x: f(x(x)))(lambda x: f(lambda y: x(x)(y)))
# λf.(λx.f(x x))(λx.λy.f(x x)y)
Y1 = lambda f: (lambda x: f(x(x)))(lambda x: lambda y: f(x(x))(y))
```

使用得到的Y组合子将单步递归函数作为参数即可得到最终的目标函数。

在`C++14`之后，C++可以使用**泛型Lambda**，使用`C++14`实现Y组合子同样无需确定调用自身逻辑的高阶函数具体类型，可以使用`auto`关键字让模版类型自动推断，使用`C++14`表示Y组合子：

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

### 各语言完整源码
使用`Scala`、`Python`、`C#`、`C++`等语言使用Y组合子计算斐波那契数列和阶乘的结果。

- `Scala`(Scala 2.11.8)
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
- `C#`(Mono 4.4.0.0 && ArchLinux x64)
	```csharp
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
- `C++`(GCC 6.1.1 && ArchLinux x64)
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
- `Python`(Python 3.5.1)
	```py
	Y0 = lambda f: (lambda x: f(x(x)))(lambda x: f(lambda y: x(x)(y)))
	Y1 = lambda f: (lambda x: f(x(x)))(lambda x: lambda y: f(x(x))(y))

	fac = lambda x: lambda n: n < 2 and n or n * x(n - 1)
	fib = lambda x: lambda n: n if n < 2 else x(n - 1) + x(n - 2)

	print("Factorial(5): %d" % Y0(fac)(5));
	print("Fibonacci(5): %d" % Y0(fib)(5));

	print("Factorial(10): %d" % Y1(fac)(10));
	print("Fibonacci(10): %d" % Y1(fib)(10));
	```

输出结果：

```
Factorial(5): 120
Fibonacci(5): 5
Factorial(10): 3628800
Fibonacci(10): 55
```