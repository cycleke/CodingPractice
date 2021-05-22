use std::io::stdin;

fn read_integers(buf: &mut String) -> Vec<i32> {
    buf.clear();
    stdin().read_line(buf).unwrap();
    buf.split_whitespace().map(|x| x.parse().unwrap()).collect()
}

fn main() {
    let mut buf = String::new();
    let args = read_integers(&mut buf);
    for case in 1..=args[0] {
        print!("Case #{}: ", case);
        solve(&mut buf);
    }
}

fn solve(buf: &mut String) {
    let n = read_integers(buf)[0] as usize;
    let mut a = read_integers(buf);
    if n <= 3 {
        println!("{}", n);
        return;
    }

    for i in (1..n).rev() {
        a[i] -= a[i - 1];
    }

    let mut res = 0;
    let mut f = [0; 4];
    let mut g = [0; 4];
    for i in 0..n {
        let idx = i % 4;
        f[idx] = 2.min(i + 1);
        g[idx] = 3.min(i + 1);
        if i >= 2 && a[i] == a[i - 1] {
            f[idx] = f[(i - 1) % 4] + 1;
            g[idx] = g[(i - 1) % 4] + 1;
        }
        if i >= 3 && a[i] + a[i - 1] == 2 * a[i - 2] {
            res = res.max(f[(i - 2) % 4] + 2);
        }
        if i >= 3 && 2 * a[i] == a[i - 1] + a[i - 2] {
            g[idx] = g[idx].max(4);
            if i >= 4 && a[i] == a[i - 3] {
                g[idx] = g[idx].max(f[(i - 3) % 4] + 3);
            }
        }
        res = res.max(f[idx] + 1).max(g[idx]);
    }

    println!("{}", res.min(n));
}
