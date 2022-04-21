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
    let m = next!(iter, i32);
    let mut k = next!(iter, i32);

    let modm = |x| {
        let x = x % m;
        if x < 0 {
            x + m
        } else {
            x
        }
    };

    let a: Vec<i32> = read!().map(|token| token.parse().unwrap()).collect();
    let mut da = vec![0; n];
    da[0] = modm(a[0] - a[n - 1]);
    for i in 1..n {
        da[i] = modm(a[i] - a[i - 1]);
    }
    drop(a);

    let a: Vec<i32> = read!().map(|token| token.parse().unwrap()).collect();
    let mut db = vec![0; n];
    db[0] = modm(-a[0] + a[n - 1]);
    for i in 1..n {
        db[i] = modm(-a[i] + a[i - 1]);
    }
    drop(a);

    let mut ring = vec![0; 3 * n + 1];
    ring[..n].copy_from_slice(&da);
    ring[n] = -1;
    ring[n + 1..2 * n + 1].copy_from_slice(&db);
    ring[2 * n + 1..3 * n + 1].copy_from_slice(&db);

    let mut z = vec![0; 3 * n + 1];
    let mut id = -1;
    let mut mx = -1;

    let num = (3 * n + 1) as i32;
    for i in 1..num {
        z[i as usize] = if i >= mx {
            0
        } else {
            (mx - i).min(z[(i - id) as usize])
        };

        while i + z[i as usize] < num
            && ring[(i + z[i as usize]) as usize] == ring[z[i as usize] as usize]
        {
            z[i as usize] += 1;
        }

        if i + z[i as usize] > mx {
            id = i;
            mx = i + z[i as usize];
        }
    }

    let mut mark = vec![false; n];
    for i in 0..n {
        mark[i] |= z[i + n + 1] == n as i32;
    }

    type Mat = [[i32; 2]; 2];
    const MOD: i32 = 10i32.pow(9) + 7;

    fn mul(a: &Mat, b: &Mat) -> Mat {
        let mut c = Mat::default();
        let n = c.len();
        for k in 0..n {
            for i in 0..n {
                for j in 0..n {
                    c[i][j] =
                        ((c[i][j] as i64 + a[i][k] as i64 * b[k][j] as i64) % MOD as i64) as i32;
                }
            }
        }
        c
    }

    let mut a = [[0, n as i32 - 1], [1, n as i32 - 2]];
    let mut ans = [[1, 0], [0, 1]];

    while k > 0 {
        if (k & 1) == 1 {
            ans = mul(&ans, &a);
        }
        a = mul(&a, &a);
        k >>= 1;
    }

    let mut sum = 0;
    mark.iter()
        .enumerate()
        .filter_map(|(i, m)| if *m { Some(i) } else { None })
        .for_each(|i| {
            sum += if i > 0 { ans[1][0] } else { ans[0][0] };
            if sum >= MOD {
                sum -= MOD;
            }
        });
    writeln!(output, "{}", sum).unwrap();
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
                "4 10 1
3 4 1 7
13 27 36 9",
                "1",
            ),
            (
                "5 10 2
3 4 1 7 6
4 7 1 2 5",
                "3",
            ),
            (
                "5 10 2
3 4 1 7 6
5 4 7 1 2",
                "4",
            ),
            (
                "6 21 3
10 58 23 31 37 2
45 17 9 24 38 30",
                "42",
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
