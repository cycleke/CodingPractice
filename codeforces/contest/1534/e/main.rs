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
    let n = next!(iter, i32);
    let k = next!(iter, i32);

    let mut from = vec![0; (2 * n + 1) as usize];
    let mut dist = vec![0; (2 * n + 1) as usize];
    dist[0] = 1;
    from[0] = -1;

    let mut queue = VecDeque::new();
    queue.push_back(0);

    while let Some(x) = queue.pop_front() {
        for i in 0.max(k - x)..=k.min(n - x) {
            let y = x + i - (k - i);
            if dist[y as usize] == 0 {
                dist[y as usize] = dist[x as usize] + 1;
                from[y as usize] = x;
                queue.push_back(y);
            }
        }
    }

    if dist[n as usize] == 0 {
        writeln!(output, "-1").unwrap();
        return;
    }

    let dist_n = dist[n as usize] as usize;
    let mut path = Vec::with_capacity(dist_n);
    let mut x = n;
    while x != -1 {
        path.push(x);
        x = from[x as usize];
    }
    path.reverse();

    let mut selected = Vec::with_capacity(n as usize);
    let mut unselected: Vec<_> = (1..=n).collect();

    let mut ans = 0;
    for i in 0..dist_n - 1 {
        let a = path[i];
        let b = path[i + 1];
        let d = b - a;
        let sel = (d + k) / 2;
        let unsel = k - sel;

        let mut sels = Vec::with_capacity(sel as usize);
        let mut unsels = Vec::with_capacity(unsel as usize);

        write!(output, "?").unwrap();
        for _ in 0..sel {
            let x = unselected.pop().unwrap();
            sels.push(x);
            write!(output, " {}", x).unwrap();
        }
        for _ in 0..unsel {
            let x = selected.pop().unwrap();
            unsels.push(x);
            write!(output, " {}", x).unwrap();
        }
        writeln!(output).unwrap();
        output.flush().unwrap();

        selected.append(&mut sels);
        unselected.append(&mut unsels);

        buf.clear();
        input.read_line(&mut buf).unwrap();
        ans ^= buf.trim_end().parse::<i32>().unwrap();
    }
    writeln!(output, "! {}", ans).unwrap();
}

#[cfg(test)]
mod test {
    use crate::solve;

    fn test(input: &str, output: &str) {
        let mut v: Vec<u8> = Vec::new();
        solve(input.as_bytes(), &mut v);
        assert_eq!(String::from_utf8(v).unwrap(), output);
    }

    #[test]
    fn sample() {
        test(
            "3 2
", "-1
",
        );
        test(
            "5 3
4
3
0
",
            "? 5 4 3
? 2 3 4
? 4 3 1
! 7
",
        );
    }
}
