use std::io::{stdin, stdout, BufRead, Write};

fn main() {
    let input = stdin();
    let output = stdout();
    solve(input.lock(), output.lock());
}

fn solve<R: BufRead, W: Write>(mut input: R, mut output: W) {
    let mut buf = String::new();
    input.read_line(&mut buf).unwrap();

    let n: usize = buf.trim_end().parse().unwrap();
    let mut edges = Vec::with_capacity(n - 1);

    let mut vs = [vec![], vec![]];
    writeln!(output, "? 1").unwrap();
    output.flush().unwrap();

    buf.clear();
    input.read_line(&mut buf).unwrap();
    let mut iter = buf.split_ascii_whitespace();
    for i in 1..=n {
        let d: usize = iter.next().unwrap().parse().unwrap();
        if d == 1 {
            edges.push((1, i));
        }
        vs[d & 1].push(i);
    }

    let vs = if vs[0].len() <= vs[1].len() {
        &vs[0]
    } else {
        &vs[1]
    };

    for &v in vs.iter().filter(|v| **v != 1) {
        writeln!(output, "? {}", v).unwrap();
        output.flush().unwrap();

        buf.clear();
        input.read_line(&mut buf).unwrap();
        let mut iter = buf.split_ascii_whitespace();
        for i in 1..=n {
            let d: i32 = iter.next().unwrap().parse().unwrap();
            if d == 1 {
                edges.push((v.min(i), v.max(i)));
            }
        }
    }

    edges.sort_unstable();
    edges.dedup();

    writeln!(output, "!").unwrap();
    for (u, v) in edges.iter() {
        writeln!(output, "{} {}", u, v).unwrap();
    }
}
