use std::io::stdin;

const MAX_N: usize = 1e8 as usize;

fn main() {
    let mut buf = String::new();
    stdin().read_line(&mut buf).unwrap();

    let mut sum = vec![0.0; MAX_N];
    for i in 1..MAX_N {
        sum[i] = sum[i - 1] + 1.0 / (i as f64);
    }

    let delta = sum[MAX_N - 1] - ((MAX_N - 1) as f64).ln();

    let test_case = buf.trim().parse().unwrap();
    for i in 1..=test_case {
        print!("Case #{}: ", i);
        solve(&mut buf, &sum, delta);
    }
}

fn solve(buf: &mut String, sum: &[f64], delta: f64) {
    macro_rules! read {
        () => {{
            buf.clear();
            stdin().read_line(buf).unwrap();
            buf.split_ascii_whitespace()
        }};
    }
    macro_rules! next {
        ($iter:expr) => {
            $iter.next().unwrap().parse().unwrap()
        };
        ($iter:expr, $type:ty) => {
            $iter.next().unwrap().parse::<$type>().unwrap()
        };
    }

    let mut iter = read!();
    let n = next!(iter, usize);

    if n < MAX_N {
        println!("{:.10}", sum[n]);
    } else {
        println!("{:.10}", (n as f64).ln() + delta);
    }
}
