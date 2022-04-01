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
    let m = next!(iter, usize);

    let mut node_cnt = 0;
    let mut idx = vec![vec![-1; m]; n];

    for i in 0..n {
        buf.clear();
        input.read_line(&mut buf).unwrap();
        for (j, ch) in buf.bytes().enumerate() {
            if ch == b'#' {
                idx[i][j] = node_cnt;
                node_cnt += 1;
            }
        }
    }

    let mut last = vec![-1; m];
    let mut adj = vec![vec![]; node_cnt as usize];
    for i in 0..n {
        for j in (0..m).filter(|j| idx[i][*j] != -1) {
            if i > 0 && idx[i - 1][j] != -1 {
                adj[idx[i][j] as usize].push(idx[i - 1][j]);
            }

            if last[j] != -1 {
                adj[last[j] as usize].push(idx[i][j]);
            }
            last[j] = idx[i][j];

            let mut left = false;
            let mut right = false;
            let mut k = i;
            while k < n && (!left || !right) && (idx[k][j] == -1 || k == i) {
                if j > 0 && !left && idx[k][j - 1] != -1 {
                    left = true;
                    adj[idx[i][j] as usize].push(idx[k][j - 1]);
                }
                if j + 1 < m && !right && idx[k][j + 1] != -1 {
                    right = true;
                    adj[idx[i][j] as usize].push(idx[k][j + 1]);
                }
                k += 1;
            }
        }
    }

    let mut tarjan = Tarjan::new(node_cnt as usize);
    for i in 0..node_cnt {
        if tarjan.idx[i as usize] == -1 {
            tarjan.dfs(&adj, i);
        }
    }

    let mut deg = vec![0; tarjan.components.len()];
    for (i, component) in tarjan.components.iter().enumerate() {
        for &u in component.iter() {
            for &v in adj[u as usize].iter() {
                if tarjan.belong[v as usize] != i as i32 {
                    deg[tarjan.belong[v as usize] as usize] += 1;
                }
            }
        }
    }

    let ans = deg.iter().filter(|deg| **deg == 0).count();
    writeln!(output, "{}", ans).unwrap();
}

#[derive(Debug)]
struct Tarjan {
    dfs_clk: i32,
    idx: Vec<i32>,
    belong: Vec<i32>,
    components: Vec<Vec<i32>>,
    stack: Vec<i32>,
    in_stack: Vec<bool>,
}

impl Tarjan {
    fn new(n: usize) -> Tarjan {
        Tarjan {
            dfs_clk: 0,
            idx: vec![-1; n],
            belong: vec![-1; n],
            components: vec![],
            stack: vec![],
            in_stack: vec![false; n],
        }
    }

    fn dfs(&mut self, adj: &[Vec<i32>], u: i32) -> i32 {
        let uu = u as usize;

        let mut low = self.dfs_clk;
        self.idx[uu] = low;
        self.dfs_clk += 1;

        self.stack.push(u);
        self.in_stack[uu] = true;
        for &v in adj[uu].iter() {
            let vv = v as usize;
            if self.idx[vv] == -1 {
                low = low.min(self.dfs(adj, v));
            } else if self.in_stack[vv] {
                low = low.min(self.idx[vv]);
            }
        }

        if low == self.idx[uu] {
            let mut component = vec![];
            while let Some(x) = self.stack.pop() {
                self.belong[x as usize] = self.components.len() as i32;
                self.in_stack[x as usize] = false;
                component.push(x);
                if x == u {
                    break;
                }
            }
            self.components.push(component);
        }

        low
    }
}

#[cfg(test)]
mod test {
    use crate::solve;

    fn test(input: &str, output: &str) {
        let mut v: Vec<u8> = Vec::new();
        solve(input.as_bytes(), &mut v);
        assert_eq!(String::from_utf8(v).unwrap().trim_end(), output.trim_end());
    }

    #[test]
    fn sample() {
        let samples = [
            (
                "5 7
#....#.
.#.#...
#....#.
#....##
#.#....
4 1 1 1 0 3 1",
                "3",
            ),
            (
                "3 3
#.#
#..
##.
3 1 1",
                "1",
            ),
            (
                "3 10
#..###..##
...#..###.
.###..##..
1 1 1 3 1 1 2 2 2 1
",
                "1",
            ),
            (
                "3 6
..#..#
......
#####.
1 1 2 1 1 1
",
                "2",
            ),
        ];

        for (input, output) in samples {
            test(input, output);
        }
    }
}
