import java.util.function.Function;

class Self implements Function<Self, Function<Integer, Integer>> {

	private Function<Self, Function<Integer, Integer>> in;

	public Self(Function<Self, Function<Integer, Integer>> in) { this.in = in; }

	public Function<Integer, Integer> apply(Self self) { return in.apply(self); }
}

class y_combinator {

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