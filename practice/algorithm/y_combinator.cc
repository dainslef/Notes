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
				{ return n == 0 ? 1 : n * x(n - 1); }; };

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