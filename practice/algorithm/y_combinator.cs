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