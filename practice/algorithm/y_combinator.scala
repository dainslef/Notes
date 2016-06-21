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