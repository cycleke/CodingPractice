use std::{
    collections::VecDeque,
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
    let n = next!(iter, usize);
    let m = next!(iter, usize);

    let mut node_cnt = 0;
    let mut idx = Vec::with_capacity(n);

    for _ in 0..n {
        buf.clear();
        input.read_line(&mut buf).unwrap();
        let mut line = vec![usize::MAX; m];
        for (i, ch) in buf.bytes().enumerate() {
            if ch == b'#' {
                line[i] = node_cnt;
                node_cnt += 1;
            }
        }
        idx.push(line);
    }
    let mut a: Vec<i32> = read!().map(|s| s.parse().unwrap()).collect();

    let mut last = vec![usize::MAX; m];
    let mut adj = vec![vec![]; node_cnt];
    for i in 0..n {
        for j in (0..m).filter(|&j| idx[i][j] != usize::MAX) {
            if i > 0 && idx[i - 1][j] != usize::MAX {
                adj[idx[i][j]].push(idx[i - 1][j]);
            }

            if last[j] != usize::MAX {
                adj[last[j]].push(idx[i][j]);
            }
            last[j] = idx[i][j];

            let mut left = false;
            let mut right = false;
            let mut k = i;
            while k < n && (!left || !right) && (idx[k][j] == usize::MAX || k == i) {
                if j > 0 && !left && idx[k][j - 1] != usize::MAX {
                    left = true;
                    adj[idx[i][j]].push(idx[k][j - 1]);
                }
                if j + 1 < m && !right && idx[k][j + 1] != usize::MAX {
                    right = true;
                    adj[idx[i][j] as usize].push(idx[k][j + 1]);
                }
                k += 1;
            }
        }
    }

    let mut tarjan = Tarjan::new(node_cnt, &adj);
    for i in 0..node_cnt {
        if tarjan.idx[i] == usize::MAX {
            tarjan.dfs(i);
        }
    }

    // eprintln!("{:?}", tarjan);

    let bel = tarjan.bel;
    let comps = tarjan.comps;
    let mut scc_adj = Vec::with_capacity(comps.len());

    for (i, comp) in comps.iter().enumerate() {
        let mut nadj = vec![];
        for &u in comp.iter() {
            for &v in adj[u].iter() {
                if bel[v] != i {
                    nadj.push(bel[v]);
                }
            }
        }
        nadj.sort_unstable();
        nadj.dedup();
        scc_adj.push(nadj);
    }

    // eprintln!("{:?}", scc_adj);

    let mut spec = vec![];
    let mut left_spec = vec![usize::MAX; comps.len()];
    for j in 0..m {
        for i in (0..n).rev() {
            if idx[i][j] != usize::MAX {
                a[j] -= 1;
                if a[j] == 0 {
                    spec.push(bel[idx[i][j]]);
                    left_spec[bel[idx[i][j]]] = left_spec[bel[idx[i][j]]].min(j);
                }
            }
        }
    }
    spec.sort_unstable();
    spec.dedup();

    // eprintln!("{:?} {:?}", spec, left_spec);

    let mut marked = vec![false; comps.len()];
    let mut queue = VecDeque::with_capacity(comps.len());
    for &u in spec.iter() {
        if marked[u] {
            continue;
        }

        queue.push_back(u);
        while let Some(u) = queue.pop_front() {
            for &v in scc_adj[u].iter() {
                if !marked[v] {
                    marked[v] = true;
                    queue.push_back(v);
                }
            }
        }
    }

    let mut compress = vec![];
    for &u in spec.iter().filter(|&&u| !marked[u]) {
        compress.push(left_spec[u]);
    }
    compress.sort_unstable();
    compress.dedup();

    // eprintln!("{:?}", compress);

    let mut dp = vec![(-1, -1); node_cnt];
    for &u in spec.iter().filter(|&&u| !marked[u]) {
        let mut left = 0;
        let mut right = compress.len();
        while left < right {
            let mid = left + (right - left) / 2;
            if left_spec[u] <= compress[mid] {
                right = mid;
            } else {
                left = mid + 1;
            }
        }
        dp[u] = (left as i32, left as i32);
    }

    // eprintln!("{:?}", dp);

    fn gao(u: usize, dp: &mut [(i32, i32)], scc_adj: &[Vec<usize>], marked: &[bool]) -> (i32, i32) {
        if dp[u].0 != -1 {
            return dp[u];
        }
        dp[u] = (i32::MAX, i32::MIN);
        for &v in scc_adj[u].iter() {
            if marked[v] {
                continue;
            }
            let (l, r) = gao(v, dp, scc_adj, marked);
            dp[u] = (dp[u].0.min(l), dp[u].1.max(r));
        }
        dp[u]
    }

    let mut trans = vec![0; comps.len()];
    for i in (0..comps.len()).filter(|&i| !marked[i]) {
        let (l, r) = gao(i, &mut dp, &scc_adj, &marked);
        if l != i32::MAX {
            trans[l as usize] = trans[l as usize].max(r);
        }
    }
    // eprintln!("{:?} {:?} {:?}", dp, trans, marked);

    for i in 1..compress.len() {
        trans[i] = trans[i].max(trans[i - 1]);
    }

    let mut cur = 0;
    let mut ans = 0;
    while cur < compress.len() {
        ans += 1;
        cur = trans[cur] as usize + 1;
    }
    writeln!(output, "{}", ans).unwrap();
}

#[derive(Debug)]
struct Tarjan<'a> {
    dfn: usize,
    idx: Vec<usize>,
    bel: Vec<usize>,
    comps: Vec<Vec<usize>>,
    stack: Vec<usize>,
    in_stack: Vec<bool>,
    adj: &'a [Vec<usize>],
}

impl<'a> Tarjan<'a> {
    fn new(n: usize, adj: &'a [Vec<usize>]) -> Tarjan<'a> {
        Tarjan {
            dfn: 0,
            idx: vec![usize::MAX; n],
            bel: vec![usize::MAX; n],
            comps: vec![],
            stack: vec![],
            in_stack: vec![false; n],
            adj,
        }
    }

    fn dfs(&mut self, u: usize) -> usize {
        self.idx[u] = self.dfn;
        let mut low = self.dfn;
        self.dfn += 1;

        self.stack.push(u);
        self.in_stack[u] = true;
        for &v in self.adj[u].iter() {
            if self.idx[v] == usize::MAX {
                low = low.min(self.dfs(v));
            } else if self.in_stack[v] {
                low = low.min(self.idx[v]);
            }
        }

        if low == self.idx[u] {
            let mut comp = vec![];
            while let Some(x) = self.stack.pop() {
                self.bel[x] = self.comps.len();
                self.in_stack[x] = false;
                comp.push(x);
                if x == u {
                    break;
                }
            }
            self.comps.push(comp);
        }

        low
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
                "7 5
.#..#
#....
..##.
..##.
..###
..#..
#.##.
0 0 2 4 2",
                "1",
            ),
        ];

        for (input, output) in samples {
            test(input, output);
        }
    }

    #[test]
    fn tests() {
        let tests = [
            (
                "3 10
#..###..##
...#..###.
.###..##..
1 1 1 3 1 1 1 2 1 1",
                "1",
            ),
            (
                "3 6
..#..#
......
#####.
1 1 2 1 1 1",
                "2",
            ),
            (
                "5 5
.#...
.....
.....
#.#.#
...#.
0 0 1 1 1",
                "2",
            ),
            (
                "7 8
.#.#...#
.#.###..
...#...#
##...#..
........
........
...#.#..
0 1 0 0 1 0 0 1",
                "3",
            ),
        ];

        for (input, output) in tests {
            test(input, output);
        }
    }
}
