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
    let n = next!(iter);
    let m = next!(iter);

    let mut a = vec![0u128; n];
    for _ in 0..m {
        iter = read!();
        let x = next!(iter, usize) - 1;
        let y = next!(iter, usize) - 1;
        a[x] |= 1 << y;
        a[y] |= 1 << x;
    }

    for (i, x) in a.iter_mut().enumerate() {
        *x |= 1 << if x.count_ones() % 2 == 0 { n } else { i };
    }

    eprintln!("{:?}", a);

    macro_rules! a {
        ($i:expr,$j:expr) => {
            (a[$i] >> $j) & 1
        };
    }
    for i in 0..n {
        for j in i..n {
            if a!(j, i) == 1 {
                if j != i {
                    a.swap(i, j);
                }
                break;
            }
        }

        if a!(i, i) == 0 {
            continue;
        }
        for j in 0..n {
            if j != i && a!(j, i) == 1 {
                a[j] ^= a[i];
            }
        }
    }

    eprintln!("{:?}", a);

    for i in 0..n {
        if a!(i, i) == 0 && a!(i, n) == 1 {
            writeln!(output, "N").unwrap();
            return;
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
                "4 4
4 2
1 3
2 3
1 4",
                "Y",
            ),
            (
                "4 3
4 2
2 3
1 2",
                "Y",
            ),
            (
                "5 5
3 5
3 1
1 4
2 5
2 4",
                "N",
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
