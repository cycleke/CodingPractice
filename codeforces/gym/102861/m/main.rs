use std::io::{stdin, stdout, BufRead, Write};

fn main() {
    let input = stdin();
    let output = stdout();
    solve(input.lock(), output.lock());
}

const BASE: u32 = 5782344;
const MOD: u32 = 10_0000_0007;

fn add(a: u32, b: u32) -> u32 {
    if a + b >= MOD {
        a + b - MOD
    } else {
        a + b
    }
}

fn mul(a: u32, b: u32) -> u32 {
    let a = a as u64 * b as u64;
    if a >= MOD as u64 {
        (a % MOD as u64) as u32
    } else {
        a as u32
    }
}

type Point = (i64, i64);

struct SegTree {
    n: usize,
    offset: usize,
    data: Vec<Vec<(usize, u32)>>,
}

impl SegTree {
    fn new(pts: &[Point], xs: &[i64], ys: &[i64]) -> SegTree {
        let n = xs.len();
        let mut offset = 1;
        while offset <= n {
            offset <<= 1;
        }

        let mut data = vec![vec![]; 2 * offset + 2];
        for (id, (x, y)) in pts.iter().enumerate() {
            let x = xs.binary_search(x).unwrap();
            let y = ys.binary_search(y).unwrap();
            data[offset + x + 1].push((y, id as u32 + 1));
        }
        for i in 1..=n {
            data[offset + i].sort_unstable();
        }

        for i in (1..=offset).rev() {
            let lv = &data[i << 1];
            let rv = &data[i << 1 | 1];
            let mut comb = Vec::with_capacity(lv.len() + rv.len());

            let mut li = 0;
            let mut ri = 0;
            while li < lv.len() && ri < rv.len() {
                if lv[li] < rv[ri] {
                    comb.push(lv[li]);
                    li += 1;
                } else {
                    comb.push(rv[ri]);
                    ri += 1;
                }
            }
            while li < lv.len() {
                comb.push(lv[li]);
                li += 1;
            }
            while ri < rv.len() {
                comb.push(rv[ri]);
                ri += 1;
            }

            data[i] = comb;
        }

        SegTree { n, offset, data }
    }

    fn query(&self, x: usize, y: usize, ids: &mut Vec<u32>) {
        let mut s = x + 1 + self.offset - 1;
        let mut t = self.n + self.offset + 1;
        while (s ^ t) != 1 {
            if (s & 1) == 0 {
                for &(ny, id) in self.data[s ^ 1].iter().rev() {
                    if ny < y {
                        break;
                    }
                    ids.push(id);
                }
            }
            if (t & 1) == 1 {
                for &(ny, id) in self.data[t ^ 1].iter().rev() {
                    if ny < y {
                        break;
                    }
                    ids.push(id);
                }
            }
            s >>= 1;
            t >>= 1;
        }
    }
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
    let q = next!(iter);

    let mut xs = Vec::with_capacity(n);
    let mut ys = Vec::with_capacity(n);
    let mut pts = Vec::with_capacity(n);
    for _ in 0..n {
        iter = read!();
        let x = next!(iter, i64);
        let y = next!(iter, i64);
        let (x, y) = (x - 2 * y, x + 2 * y);
        xs.push(x);
        ys.push(y);
        pts.push((x, y));
    }

    xs.sort_unstable();
    xs.dedup();
    ys.sort_unstable();
    ys.dedup();

    let seg_tree = SegTree::new(&pts, &xs, &ys);
    let mut p = 0;
    let mut ids = vec![];
    for _ in 0..q {
        iter = read!();
        let x = -1 - add(next!(iter), p) as i64;
        let y = add(next!(iter), p) as i64;

        let (x, y) = (x - 2 * y, x + 2 * y);

        let x = match xs.binary_search(&x) {
            Ok(x) => x,
            Err(x) => x,
        };
        let y = match ys.binary_search(&y) {
            Ok(x) => x,
            Err(x) => x,
        };

        p = 0;
        let mut exp = 1;
        if x < xs.len() && y < ys.len() {
            ids.clear();
            seg_tree.query(x, y, &mut ids);

            ids.sort_unstable();
            for &id in ids.iter() {
                p = add(p, mul(exp, id));
                exp = mul(exp, BASE);
            }
        }

        writeln!(output, "{}", p).unwrap();
    }
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
            "7 2
2 8
5 7
1 6
4 5
1 3
2 2
4 1
2 3
373785639 373785644",
            "626214369
981053491",
        )];

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
