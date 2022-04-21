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

    input.read_line(&mut buf).unwrap();
    let n = buf.trim_end().parse().unwrap();

    let mut adj = vec![vec![]; n];
    for (i, p) in read!().enumerate() {
        let p = p.parse::<usize>().unwrap() - 1;
        adj[p].push(i + 1);
    }

    let mut dp = vec![(-1, -1); n];

    const MOD: i64 = 1000000007;
    fn dfs(u: usize, dp: &mut Vec<(i32, i32)>, adj: &[Vec<usize>]) {
        if adj[u].is_empty() {
            dp[u] = (1, 1);
            return;
        }

        let mut f = Vec::with_capacity(adj[u].len());
        let mut g = Vec::with_capacity(adj[u].len());
        for &v in adj[u].iter() {
            dfs(v, dp, adj);
            f.push(dp[v].0);
            g.push(dp[v].1);
        }

        let mut pref = vec![1; adj[u].len() + 1];
        for (i, &x) in f.iter().enumerate() {
            pref[i + 1] = (pref[i] as i64 * x as i64 % MOD) as i32;
        }
        let mut suff = vec![1; adj[u].len() + 1];
        for i in (0..adj[u].len() - 1).rev() {
            suff[i] = (suff[i + 1] as i64 * f[i + 1] as i64 % MOD) as i32;
        }

        let mut sum = 0;
        for ((pref, val), suff) in pref.iter().zip(g.iter()).zip(suff.iter()) {
            let pref = *pref as i64;
            let val = *val as i64;
            let suff = *suff as i64;
            sum = (sum + pref * val % MOD * suff) % MOD;
        }
        dp[u] = (sum as i32, sum as i32);
        dp[u].0 += pref[adj[u].len()];
        if dp[u].0 >= MOD as i32 {
            dp[u].0 -= MOD as i32;
        }
    }

    dfs(0, &mut dp, &adj);
    writeln!(output, "{}", dp[0].0).unwrap();
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
1 1", "3",
            ),
            (
                "4
1 2 3", "4",
            ),
            (
                "5
1 2 2 2",
                "7",
            ),
        ];

        for (input, output) in samples {
            test(input, output);
        }
    }

    #[test]
    fn tests() {
        let tests = [(
            "5
1 2 3 4",
            "5",
        )];

        for (input, output) in tests {
            test(input, output);
        }
    }
}
