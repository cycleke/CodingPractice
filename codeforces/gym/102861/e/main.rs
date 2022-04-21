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
    let mut a = vec![0; n];
    let mut adj = vec![vec![]; n];

    for i in 0..n {
        let mut iter = read!();
        a[i] = next!(iter);

        let b = next!(iter, usize);
        if i != 0 {
            adj[b - 1].push(i);
        }
    }

    let mut owners = vec![vec![]; n];
    for _ in 0..m {
        let mut iter = read!();
        let o = next!(iter, usize);
        let l = next!(iter, i32);
        let r = next!(iter, i32);

        owners[o - 1].push((l, r));
    }

    let mut delta = vec![vec![]; n];

    fn pre_dfs(
        u: usize,
        adj: &[Vec<usize>],
        owners: &[Vec<(i32, i32)>],
        a: &[i32],
        delta: &mut [Vec<i32>],
        stack: &mut Vec<usize>,
    ) {
        stack.push(u);

        for &(l, r) in owners[u].iter() {
            let mut left = 0;
            let mut right = stack.len() - 1;

            while left < right {
                let mid = (left + right) / 2;
                if a[stack[mid]] <= r {
                    right = mid;
                } else {
                    left = mid + 1;
                }
            }

            delta[stack[right]].push(l);
        }

        for &v in adj[u].iter() {
            pre_dfs(v, adj, owners, a, delta, stack);
        }

        stack.pop();
    }

    let mut stack = Vec::with_capacity(n);
    pre_dfs(0, &adj, &owners, &a, &mut delta, &mut stack);

    let mut ans = vec![0; n];
    let mut bit = vec![0; *a.iter().max().unwrap() as usize];
    fn dfs(
        u: usize,
        adj: &[Vec<usize>],
        a: &[i32],
        delta: &[Vec<i32>],
        bit: &mut Vec<i32>,
        ans: &mut Vec<i32>,
    ) {
        for &(mut l) in delta[u].iter() {
            while l <= bit.len() as i32 {
                bit[(l - 1) as usize] += 1;
                l += l & -l;
            }
        }

        let mut x = a[u];
        while x > 0 {
            ans[u] += bit[(x - 1) as usize];
            x &= x - 1;
        }

        for &v in adj[u].iter() {
            dfs(v, adj, a, delta, bit, ans);
        }

        for &(mut l) in delta[u].iter() {
            while l <= bit.len() as i32 {
                bit[(l - 1) as usize] -= 1;
                l += l & -l;
            }
        }
    }
    dfs(0, &adj, &a, &delta, &mut bit, &mut ans);

    write!(output, "{}", ans[0]).unwrap();
    for x in ans[1..].iter() {
        write!(output, " {}", x).unwrap();
    }
    writeln!(output);
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
        let samples = [(
            "10 3
8 1
3 5
5 1
2 3
4 1
3 3
1 2
7 1
2 2
3 2
3 5 9
5 3 8
3 2 6",
            "2 1 3 1 1 2 0 2 0 1",
        )];

        for (input, output) in samples {
            test(input, output);
        }
    }

    #[test]
    fn tests() {
        let tests = [
            (
                "10 10
10 1
3 4
7 1
5 9
6 3
2 9
8 1
5 9
6 1
3 2
6 1 7
9 6 10
2 1 6
8 4 6
8 1 7
10 1 8
9 1 9
3 1 10
7 3 8
1 1 10",
                "3 7 3 8 3 7 4 8 9 7",
            ),
            (
                "20 10
10 1
1 19
7 12
3 20
6 20
6 9
1 2
5 3
6 5
5 18
3 15
10 1
2 16
1 1
4 19
3 10
1 18
5 1
4 8
6 3
2 1 5
4 1 7
20 1 8
20 1 10
16 2 4
20 1 9
2 1 6
6 2 10
6 6 6
1 1 10",
                "3 7 6 6 7 7 7 8 7 3 8 3 4 2 8 4 2 3 8 7",
            ),
        ];

        for (input, output) in tests {
            test(input, output);
        }
    }
}
