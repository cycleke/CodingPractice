use std::{io::stdin, str::SplitAsciiWhitespace, usize};

const MAX_N: usize = 5e4 as usize;
const MAX_Q: usize = 1e5 as usize;

struct Graph {
    adj: Vec<Vec<usize>>,
    pa: [usize; MAX_N],
    son: [usize; MAX_N],
    top: [usize; MAX_N],
    dfn: [usize; MAX_N],
    dfs_clk: usize,
    depth: [i32; MAX_N],
    size: [i32; MAX_N],
    ans: [i64; MAX_Q],
}

struct Zkw {
    pre: usize,
    arr: [i64; MAX_N * 4],
}

impl Zkw {
    pub fn init(&mut self, n: usize) {
        self.pre = 1;
        while self.pre <= n {
            self.pre <<= 1;
        }
        for i in 0..(self.pre * 2) {
            self.arr[i] = 0;
        }
    }

    pub fn update(&mut self, mut pos: usize, val: i64) {
        pos += self.pre;
        self.arr[pos] = val;
        pos >>= 1;
        while pos > 0 {
            self.arr[pos] = gcd(self.arr[pos << 1], self.arr[pos << 1 | 1]);
            pos >>= 1;
        }
    }

    pub fn query(&self, mut s: usize, mut t: usize) -> i64 {
        let mut res = 0;
        s += self.pre - 1;
        t += self.pre + 1;
        while (s ^ t ^ 1) != 0 {
            if s % 2 == 0 {
                res = gcd(res, self.arr[s ^ 1]);
            }
            if t % 2 == 1 {
                res = gcd(res, self.arr[t ^ 1]);
            }
            s >>= 1;
            t >>= 1;
        }
        res
    }
}

fn line_iter(buf: &mut String) -> SplitAsciiWhitespace {
    buf.clear();
    stdin().read_line(buf).unwrap();
    buf.split_ascii_whitespace()
}

fn main() {
    let mut graph = Graph {
        adj: vec![vec![]; MAX_N],
        pa: [0; MAX_N],
        son: [0; MAX_N],
        dfn: [0; MAX_N],
        dfs_clk: 0,
        top: [0; MAX_N],
        depth: [0; MAX_N],
        size: [0; MAX_N],
        ans: [0; MAX_Q],
    };
    let mut zwk = Zkw {
        pre: 0,
        arr: [0; MAX_N * 4],
    };

    let mut buf = String::new();
    stdin().read_line(&mut buf).unwrap();
    let testcase = buf.trim().parse().unwrap();
    for case in 1..=testcase {
        print!("Case #{}:", case);
        solve(&mut buf, &mut graph, &mut zwk);
    }
}

fn solve(buf: &mut String, graph: &mut Graph, zkw: &mut Zkw) {
    let mut iter = line_iter(buf);
    let ns = iter.next().unwrap().parse::<usize>().unwrap();
    let qs = iter.next().unwrap().parse::<usize>().unwrap();

    for i in 0..ns {
        graph.adj[i].clear();
    }

    let mut edges = Vec::with_capacity(ns - 1);
    for _ in 1..ns {
        iter = line_iter(buf);
        let u = iter.next().unwrap().parse::<usize>().unwrap() - 1;
        let v = iter.next().unwrap().parse::<usize>().unwrap() - 1;
        let l = iter.next().unwrap().parse::<i32>().unwrap();
        let a = iter.next().unwrap().parse::<i64>().unwrap();
        graph.adj[u].push(v);
        graph.adj[v].push(u);
        edges.push((u, v, l, a));
    }
    edges.sort_by(|a, b| a.2.cmp(&b.2));

    let mut queries = Vec::with_capacity(qs);
    for i in 0..qs {
        iter = line_iter(buf);
        let c = iter.next().unwrap().parse::<usize>().unwrap() - 1;
        let w: i32 = iter.next().unwrap().parse().unwrap();
        queries.push((c, w, i));
    }
    queries.sort_by(|a, b| a.1.cmp(&b.1));

    dfs1(0, graph);
    graph.dfs_clk = 0;
    dfs2(0, 0, graph);

    zkw.init(ns);
    let mut iter = 0;
    for (mut c, w, id) in queries {
        while iter < ns - 1 && edges[iter].2 <= w {
            let (mut u, v, _, a) = edges[iter];
            if graph.depth[u] < graph.depth[v] {
                u = v;
            }
            zkw.update(graph.dfn[u], a);
            iter += 1;
        }

        let mut res = 0;
        while c > 0 {
            // eprintln!(
            //     "DEBUG {} {} {}",
            //     graph.top[c],
            //     c,
            //     zkw.query(graph.dfn[graph.top[c]], graph.dfn[c])
            // );
            res = gcd(res, zkw.query(graph.dfn[graph.top[c]], graph.dfn[c]));
            c = graph.pa[graph.top[c]];
        }
        graph.ans[id] = res;
    }

    for i in 0..qs {
        print!(" {}", graph.ans[i]);
    }
    println!();
}

fn dfs1(u: usize, graph: &mut Graph) {
    let mut son = 0;
    let len = graph.adj[u].len();
    graph.size[u] = 1;
    for i in 0..len {
        let v = graph.adj[u][i];
        if v == graph.pa[u] {
            continue;
        }
        graph.pa[v] = u;
        graph.depth[v] = graph.depth[u] + 1;
        dfs1(v, graph);
        graph.size[u] += graph.size[v];
        if son == 0 || graph.size[v] > graph.size[son] {
            son = v;
        }
    }
    graph.son[u] = son;
}

fn dfs2(u: usize, top: usize, graph: &mut Graph) {
    graph.top[u] = top;
    graph.dfs_clk += 1;
    graph.dfn[u] = graph.dfs_clk;
    let son = graph.son[u];
    if son > 0 {
        dfs2(son, top, graph);
        let len = graph.adj[u].len();
        for i in 0..len {
            let v = graph.adj[u][i];
            if v == graph.pa[u] || v == son {
                continue;
            }
            dfs2(v, v, graph);
        }
    }
}

fn gcd(a: i64, b: i64) -> i64 {
    if b == 0 {
        a
    } else {
        gcd(b, a % b)
    }
}
