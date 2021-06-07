use std::io::stdin;

fn main() {
    let mut buf = String::with_capacity(15);
    stdin().read_line(&mut buf).unwrap();

    let testcase = buf.trim().parse().unwrap();
    for case in 1..=testcase {
        print!("Case #{}: ", case);

        buf.clear();
        stdin().read_line(&mut buf).unwrap();
        solve(buf.trim().parse().unwrap());
    }
}

fn solve(g: i64) {
    let g = 2 * g;
    let mut i = 1;
    let mut ans = 0;

    // eprintln!("DEBUG {}", g);
    while i * i < g {
        if g % i == 0 {
            let d = g / i;
            // eprintln!("DEBUG {} {}", i, d);
            if ((i & 1) ^ (d & 1)) == 1 {
                ans += 1;
            }
        }
        i += 1;
    }
    println!("{}", ans);
}
