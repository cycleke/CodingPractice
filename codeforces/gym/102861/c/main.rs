use std::{
    collections::{HashMap, HashSet},
    io::{stdin, stdout, BufRead, Write},
};

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

    let mut a_teams = Vec::with_capacity(n);
    for _ in 0..n {
        loop {
            if let Some(token) = iter.next() {
                a_teams.push(token.as_bytes().to_vec());
                break;
            }
            iter = read!();
        }
    }

    let mut b_teams = Vec::with_capacity(m);
    for _ in 0..m {
        loop {
            if let Some(token) = iter.next() {
                b_teams.push(token.as_bytes().to_vec());
                break;
            }
            iter = read!();
        }
    }

    a_teams.sort_by_key(|s| s.len());
    b_teams.sort_by_key(|s| s.len());

    const KEY: u64 = 100019u64;
    const MOD: u64 = 4611686018427387847u64;

    fn mul(a: u64, b: u64) -> u64 {
        (a as u128 * b as u128 % MOD as u128) as u64
    }

    fn gen_hashtbl(s: &[u8]) -> Vec<u64> {
        let mut hash = vec![0; s.len() + 1];
        for (i, &chr) in s.iter().enumerate() {
            hash[i + 1] = (mul(hash[i], KEY) + chr as u64) % MOD;
        }
        hash
    }

    let p = {
        let max_len = a_teams[n - 1].len().max(b_teams[m - 1].len());
        let mut p = vec![0; max_len + 1];
        p[0] = 1;
        for i in 1..=max_len {
            p[i] = mul(p[i - 1], KEY);
        }
        p
    };

    let get_range = |l: usize, r: usize, hash: &Vec<u64>| {
        let val = hash[r] + MOD - mul(hash[l - 1], p[r - l + 1]);
        if val < MOD {
            val
        } else {
            val - MOD
        }
    };

    let mut a_tbl = Vec::with_capacity(n);
    let mut a_idx = HashMap::with_capacity(n);
    let mut a_mid = HashSet::new();
    for (i, s) in a_teams.iter().enumerate() {
        let tbl = gen_hashtbl(s);
        a_idx.insert(tbl[s.len()], i);
        for len in 1..s.len() {
            if a_idx.contains_key(&tbl[len]) {
                a_mid.insert(get_range(len + 1, s.len(), &tbl));
            }
        }
        a_tbl.push(tbl);
    }

    let mut b_tbl = Vec::with_capacity(m);
    let mut b_idx = HashMap::with_capacity(m);
    let mut b_mid = HashSet::new();
    for (i, s) in b_teams.iter().enumerate() {
        let tbl = gen_hashtbl(s);
        b_idx.insert(tbl[s.len()], i);
        for len in 1..s.len() {
            if b_idx.contains_key(&get_range(len + 1, s.len(), &tbl)) {
                b_mid.insert(tbl[len]);
            }
        }
        b_tbl.push(tbl);
    }

    let mut a_mark = vec![1; n];
    for (i, (s, tbl)) in (a_teams.iter().zip(a_tbl.iter())).enumerate() {
        for len in 1..s.len() {
            if let Some(&j) = a_idx.get(&tbl[len]) {
                if b_mid.contains(&get_range(len + 1, s.len(), tbl)) {
                    a_mark[i] = 0;
                    a_mark[j] = 0;
                }
            }
        }
    }

    let mut b_mark = vec![1; m];
    for (i, (s, tbl)) in (b_teams.iter().zip(b_tbl.iter())).enumerate() {
        for len in 1..s.len() {
            if let Some(&j) = b_idx.get(&get_range(len + 1, s.len(), tbl)) {
                if a_mid.contains(&tbl[len]) {
                    b_mark[i] = 0;
                    b_mark[j] = 0;
                }
            }
        }
    }

    writeln!(
        output,
        "{} {}",
        a_mark.iter().sum::<i32>(),
        b_mark.iter().sum::<i32>()
    )
    .unwrap();
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
                "2 2
buen kilo
pan flauta",
                "2 2",
            ),
            (
                "2 3
xx xxy
z yz xx",
                "0 1",
            ),
        ];

        for (input, output) in samples {
            test(input, output);
        }
    }

    #[test]
    fn test1() {
        let mut input = String::new();
        input += "612 612\n";
        for i in 1..=612 {
            for _ in 0..i {
                input.push('a');
            }
            if i != 612 {
                input.push(' ');
            }
        }
        input.push('\n');
        for i in 1..=612 {
            for _ in 0..i {
                input.push('a');
            }
            if i != 612 {
                input.push(' ');
            }
        }

        test(&input, "0 0");
    }

    #[test]
    fn test2() {
        let mut input = String::new();
        input += "613 612\n";
        for i in 1..=612 {
            for _ in 0..i {
                input.push('a');
            }
            input.push(' ');
        }
        for _ in 0..1000 {
            input.push('b');
        }
        input.push('\n');
        for i in 1..=612 {
            for _ in 0..i {
                input.push('b');
            }
            if i != 612 {
                input.push(' ');
            }
        }

        test(&input, "613 612");
    }
}
