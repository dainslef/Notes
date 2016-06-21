Y0 = lambda f: (lambda x: f(x(x)))(lambda x: f(lambda y: x(x)(y)))
Y1 = lambda f: (lambda x: f(x(x)))(lambda x: lambda y: f(x(x))(y))

fac = lambda x: lambda n: n < 2 and n or n * x(n - 1)
fib = lambda x: lambda n: n if n < 2 else x(n - 1) + x(n - 2)

print("Factorial(5): %d" % Y0(fac)(5));
print("Fibonacci(5): %d" % Y0(fib)(5));

print("Factorial(10): %d" % Y1(fac)(10));
print("Fibonacci(10): %d" % Y1(fib)(10));