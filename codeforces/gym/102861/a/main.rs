use std::io::{stdin, stdout, BufRead, Write};

fn main() {
    let input = stdin();
    let output = stdout();
    solve(input.lock(), output.lock());
}

fn solve<R: BufRead, W: Write>(mut input: R, mut output: W) {
    let mut buf = String::new();
    macro_rules! read {
        () => {{
            buf.clear();
            input.read_line(&mut buf).unwrap();
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
    let a = next!(iter, usize);
    let b = next!(iter, usize);

    let mut sum = 0.0;
    let d = b - a + 1;
    let mut dp = vec![0.0; n];

    if a > 0 {
        let r = 1.0 / d as f64;
        for i in (0..n).rev() {
            dp[i] = sum * r + 1.0;
            if i + a - 1 < n {
                sum += dp[i + a - 1];

                if i + b < n {
                    sum -= dp[i + b];
                }
            }
        }
    } else {
        let r = 1.0 / (d - 1) as f64;
        let c = d as f64 * r;
        for i in (0..n).rev() {
            dp[i] = sum * r + c;
            sum += dp[i];

            if i + b < n {
                sum -= dp[i + b];
            }
        }
    }
    writeln!(output, "{:.5}", dp[0]).unwrap();
}

#[cfg(test)]
mod test {
    use crate::solve;

    fn test(input: &str, answer: &str) {
        let mut v: Vec<u8> = Vec::new();
        solve(input.as_bytes(), &mut v);
        let output = String::from_utf8(v)
            .unwrap()
            .lines()
            .map(|s| s.trim_end().to_string())
            .collect::<Vec<_>>();
        let answer = answer
            .lines()
            .map(|s| s.trim_end().to_string())
            .collect::<Vec<_>>();
        assert_eq!(output, answer);
    }

    #[test]
    fn sample() {
        let samples = [
            ("40 0 2", "40.33333"),
            ("100 1 10", "18.72727"),
            ("30 3 3", "10.00000"),
            ("314 5 8", "48.74556"),
        ];

        for (input, output) in samples {
            test(input, output);
        }
    }
}
