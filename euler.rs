
fn problem1() {
	let mut result = 0;
	let mut i = 1;
	loop {
		if i % 3 == 0 || i % 5 == 0 {
			result += i;
		}

		i += 1;
		if(i == 10000) {
			break;
		}
	}

	println(fmt!("Result is %u", result));
}

fn main() {
	problem1();
}