use std::{
    cmp::Reverse,
    collections::BinaryHeap,
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

    input.read_line(&mut buf).unwrap();
    let n = buf.trim_end().parse().unwrap();
    let mut potatos = Vec::with_capacity(n);
    for _ in 0..n {
        let mut iter = read!();
        let x = next!(iter, i64);
        let y = next!(iter, i64);
        potatos.push((x + y, x - y));
    }
    potatos.sort_unstable();

    let mut ans = 0;
    let mut heap_a = BinaryHeap::new();
    let mut heap_b = BinaryHeap::new();

    heap_a.push(0);
    heap_b.push(Reverse(0));
    for (y, x) in potatos {
        ans += (*heap_a.peek().unwrap() - (x + y))
            .max((x - y) - heap_b.peek().unwrap().0)
            .max(0);

        if heap_a.is_empty() || heap_b.peek().unwrap().0 + y > x {
            heap_a.push(x + y);
            heap_a.push(x + y);
            heap_b.push(Reverse(*heap_a.peek().unwrap() - 2 * y));
            heap_a.pop();
        } else {
            heap_b.push(Reverse(x - y));
            heap_b.push(Reverse(x - y));
            heap_a.push(heap_b.peek().unwrap().0 + 2 * y);
            heap_b.pop();
        }
    }

    writeln!(output, "{}", ans / 2).unwrap();
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
                "2
1 1
2 2",
                "0",
            ),
            (
                "2
1 1
2 0",
                "1",
            ),
            (
                "3
5 5
7 7
4 9",
                "2",
            ),
            (
                "10
5 1
4 0
9 6
0 2
10 1
9 10
3 10
0 10
8 9
1 5",
                "19",
            ),
            (
                "10
1 1
2 2
2 0
4 2
4 0
2 0
0 2
4 0
4 2
5 1",
                "6",
            ),
        ];

        for (input, output) in samples {
            test(input, output);
        }
    }
}
