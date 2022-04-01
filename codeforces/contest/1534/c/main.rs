use std::io::{stdin, stdout, BufRead, Write};

fn main() {
    let input = stdin();
    let output = stdout();
    solve(input.lock(), output.lock());
}

fn solve<R: BufRead, W: Write>(mut input: R, mut output: W) {
    let mut buf = String::new();
    input.read_line(&mut buf).unwrap();
    let testcase = buf.trim_end().parse().unwrap();
    for _ in 0..testcase {
        solve_case(&mut input, &mut output);
    }
}

fn solve_case<R: BufRead, W: Write>(input: &mut R, output: &mut W) {
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

    const MOD: i32 = 10i32.pow(9) + 7;

    input.read_line(&mut buf).unwrap();
    let n = buf.trim_end().parse().unwrap();
    let a: Vec<_> = read!().map(|x| x.parse::<usize>().unwrap()).collect();
    let mut next = vec![0; n];

    let mut iter = read!();
    for i in 0..n {
        let b = next!(iter, usize);
        next[a[i] - 1] = b - 1;
    }

    let mut ans = 1;
    for i in 0..n {
        if next[i] == n {
            continue;
        }
        let mut x = i;
        while next[x] != n {
            let y = next[x];
            next[x] = n;
            x = y;
        }

        ans += ans;
        if ans >= MOD {
            ans -= MOD;
        }
    }
    writeln!(output, "{}", ans).unwrap();
}

#[cfg(test)]
mod test {
    use crate::solve;

    fn test(input: &str, output: &str) {
        let mut v: Vec<u8> = Vec::new();
        solve(input.as_bytes(), &mut v);
        assert_eq!(String::from_utf8(v).unwrap(), output);
    }

    #[test]
    fn samples() {
        test(
            "2
4
1 4 2 3
3 2 1 4
8
2 6 5 1 4 3 7 8
3 8 7 5 1 2 4 6
",
            "2
8
",
        );
    }
}
