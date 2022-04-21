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
    let k = n.min(next!(iter));

    let mut c = vec![vec![0; n + 1]; n + 1];
    c[0][0] = 1;
    for i in 1..=n {
        c[i][0] = 1;
        c[i][i] = 1;
        for j in 1..i {
            c[i][j] = c[i - 1][j - 1] + c[i - 1][j];
        }
    }

    let mut ws: Vec<u64> = read!().map(|w| w.parse().unwrap()).collect();
    ws.sort_unstable();

    let gao = |mut cap: u64| {
        let mut j = 0;
        let mut res = 0u64;

        for i in (0..n).rev() {
            if cap >= ws[i] {
                res += c[i][k - j];
                cap -= ws[i];
                j += 1;
                if j == k {
                    res += 1;
                    break;
                }
            }
        }

        res
    };

    iter = read!();
    let a = next!(iter, u64);
    let b = next!(iter);

    writeln!(output, "{}", gao(b) - gao(a - 1)).unwrap();
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
                "3 2
10 1 3
4 13",
                "3",
            ),
            (
                "4 3
20 10 50 1
21 81",
                "4",
            ),
            (
                "6 3
14 70 3 1 6 31
10 74",
                "11",
            ),
        ];

        for (input, output) in samples {
            test(input, output);
        }
    }

    #[test]
    fn tests() {
        let tests = [
            ("25 30
16384 137438953472 8 4 35184372088832 256 549755813888 17592186044416 4294967296 32768 4398046511104 16777216 262144 512 128 33554432 2199023255552 8192 1024 1048576 8388608 4194304 140737488355328 562949953421312 8589934592
1706017086789550876 1885129957508953940","0")
        ];

        for (input, output) in tests {
            test(input, output);
        }
    }
}
