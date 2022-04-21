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

    input.read_line(&mut buf).unwrap();
    let n = buf.trim_end().parse().unwrap();

    let mut max_pref = 100;
    let mut pref_sum = 100;
    for _ in 0..n {
        buf.clear();
        input.read_line(&mut buf).unwrap();
        let x: i32 = buf.trim_end().parse().unwrap();
        pref_sum += x;
        max_pref = max_pref.max(pref_sum);
    }

    writeln!(output, "{}", max_pref).unwrap();
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
            (
                "4
-1
-2
-3
-4",
                "100",
            ),
            (
                "5
-10
20
-30
40
-50",
                "120",
            ),
        ];

        for (input, output) in samples {
            test(input, output);
        }
    }

    #[test]
    fn tests() {
        let tests = [];

        for (input, output) in tests {
            test(input, output);
        }
    }
}
