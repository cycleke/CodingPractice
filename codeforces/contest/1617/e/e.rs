use std::{
    collections::{BinaryHeap, HashMap},
    io::{stdin, stdout, BufRead, Write},
};

fn main() {
    let input = stdin();
    let output = stdout();
    solve(input.lock(), output.lock());
}

fn solve<R: BufRead, W: Write>(mut input: R, mut output: W) {
    let testcase = 1;
    for _ in 0..testcase {
        solve_case(&mut input, &mut output);
    }
}

fn solve_case<R: BufRead, W: Write>(input: &mut R, output: &mut W) {
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

    let mut heap = BinaryHeap::new();
    let mut nodes = HashMap::new();

    let mut iter = read!();
    for i in 0..n {
        let a = next!(iter, i32);
        heap.push(a);
        nodes.insert(a, (0, i + 1, -1, 0));
    }

    while let Some(x) = heap.pop() {
        if let Some(&y) = heap.peek() {
            if x == y {
                continue;
            }
        }

        if x == 1 {
            continue;
        }

        let next_x = next(x);
        heap.push(next_x);

        let &(mut dep1, id1, _, _) = nodes.get(&x).unwrap();
        dep1 += 1;

        let (next_dep1, next_id1, next_dep2, next_id2) =
            nodes.entry(next_x).or_insert((-1, 0, -1, 0));
        if (dep1, id1) > (*next_dep1, *next_id1) {
            *next_dep2 = *next_dep1;
            *next_id2 = *next_id1;

            *next_dep1 = dep1;
            *next_id1 = id1;
        } else if (dep1, id1) > (*next_dep2, *next_id2) {
            *next_dep2 = dep1;
            *next_id2 = id1;
        }
    }

    let mut x = 0;
    let mut y = 0;
    let mut m = -1;
    for &(dep1, id1, dep2, id2) in nodes.values() {
        if dep1 == -1 || dep2 == -1 {
            continue;
        }
        if m < dep1 + dep2 {
            m = dep1 + dep2;
            x = id1;
            y = id2;
        }
    }
    writeln!(output, "{} {} {}", x, y, m).unwrap();
}

fn next(x: i32) -> i32 {
    let mut k = 0;
    while (1 << k) < x {
        k += 1;
    }
    (1 << k) - x
}
