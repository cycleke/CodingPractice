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

    const MAX_N: usize = 10;
    let mut a = [0u16; MAX_N];
    for _ in 0..n {
        let mut iter = read!();
        let d = next!(iter, i32);
        let l = next!(iter, usize);
        let r = next!(iter, usize) - 1;
        let c = next!(iter, usize) - 1;

        if d == 0 {
            for i in c..c + l {
                if i >= MAX_N || (a[r] >> i & 1) == 1 {
                    writeln!(output, "N").unwrap();
                    return;
                }
                a[r] |= 1 << i;
            }
        } else {
            for i in r..r + l {
                if i >= MAX_N || (a[i] >> c & 1) == 1 {
                    writeln!(output, "N").unwrap();
                    return;
                }
                a[i] |= 1 << c;
            }
        }
    }
    writeln!(output, "Y").unwrap();
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
                "3
0 5 1 1
1 5 2 2
0 1 3 3",
                "Y",
            ),
            (
                "2
0 2 1 1
1 1 1 2",
                "N",
            ),
            (
                "1
0 2 10 10",
                "N",
            ),
            (
                "7
0 3 2 2
1 5 2 9
1 2 3 6
1 1 4 2
0 1 6 6
0 4 8 4
0 2 10 1",
                "Y",
            ),
        ];

        for (input, output) in samples {
            test(input, output);
        }
    }
}
