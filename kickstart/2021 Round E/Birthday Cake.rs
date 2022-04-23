use std::io::stdin;

fn main() {
    let mut buf = String::new();
    stdin().read_line(&mut buf).unwrap();

    let test_case = buf.trim().parse().unwrap();
    for i in 1..=test_case {
        print!("Case #{}: ", i);
        solve(&mut buf);
    }
}

fn solve(buf: &mut String) {
    macro_rules! read {
        () => {{
            buf.clear();
            stdin().read_line(buf).unwrap();
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
    let r = next!(iter, i64);
    let c = next!(iter, i64);
    let k = next!(iter, i64);
    iter = read!();
    let r1 = next!(iter);
    let c1 = next!(iter);
    let r2 = next!(iter);
    let c2 = next!(iter);

    let trace = |x1: i64, y1: i64, x2: i64, y2: i64, dir| match dir {
        0 => {
            if x1 == 1 {
                0
            } else {
                (y1 - y2).abs() / k + 1
            }
        }
        1 => {
            if y1 == c {
                0
            } else {
                (x1 - x2).abs() / k + 1
            }
        }
        2 => {
            if x1 == r {
                0
            } else {
                (y1 - y2).abs() / k + 1
            }
        }
        3 => {
            if y1 == 1 {
                0
            } else {
                (x1 - x2).abs() / k + 1
            }
        }
        _ => unreachable!(),
    };

    fn small(n: i64, m: i64) -> i64 {
        (n - 1 + n * (m - 1)).min(m - 1 + m * (n - 1))
    }

    let mut ans = (trace(r1, 1, r1, c2, 0)
        + trace(r1, c2, r2, c2, 1)
        + trace(r2, c2, r2, c1, 2)
        + trace(r2, c1, r1, c1, 3))
    .min(
        trace(1, c2, r2, c2, 1)
            + trace(r2, c2, r2, c1, 2)
            + trace(r2, c1, r1, c1, 3)
            + trace(r1, c1, r1, c2, 0),
    )
    .min(
        trace(r2, c, r2, c1, 2)
            + trace(r2, c1, r1, c1, 3)
            + trace(r1, c1, r1, c2, 0)
            + trace(r1, c2, r2, c2, 1),
    )
    .min(
        trace(r, c1, r1, c1, 3)
            + trace(r1, c1, r1, c2, 0)
            + trace(r1, c2, r2, c2, 1)
            + trace(r2, c2, r2, c1, 2),
    );

    let dr = r2 - r1 + 1;
    let dc = c2 - c1 + 1;
    ans += ((dr - 1) / k + 1) * ((dc - 1) / k) + ((dc - 1) / k + 1) * ((dr - 1) / k);
    ans += (dr / k) * (dc / k) * small(k, k);

    if dr % k != 0 {
        ans += (dc / k) * small(dr % k, k);
    }
    if dc % k != 0 {
        ans += (dr / k) * small(dc % k, k);
    }
    if dr % k != 0 && dc % k != 0 {
        ans += small(dr % k, dc % k);
    }

    println!("{}", ans);
}
