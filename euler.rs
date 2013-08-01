use std::uint::range;

fn problem1() {
	let mut result = 0;

	for std::uint::range(0, 1000) |i| {
		if i % 3 == 0 || i % 5 == 0 {
			result += i;
		}
	}

	println(fmt!("Result is %u", result));
}

fn problem2() {
	let mut a = 1;
	let mut b = 2;

	let mut result = 0;

	loop {
		if b % 2 == 0 {
			result += b;
		}

		let temp = b;
		b = a + b;
		a = temp;

		if b > 4000000 {
			break;
		}
	}

	println(fmt!("Result is %u", result));
}

fn main() {
	problem2();
}