use std::io::stdin;

fn main() {
    let mut buf = String::new();
    stdin().read_line(&mut buf).unwrap();
    let testcase = buf.trim().parse().unwrap();
    for case in 1..=testcase {
        print!("Case #{}: ", case);
        solve(&mut buf);
    }
}

fn solve(buf: &mut String) {
    buf.clear();
    stdin().read_line(buf).unwrap();
    let z: i64 = buf.trim().parse().unwrap();
    let z_sqrt = (z as f64).sqrt().floor() as i64;

    // eprintln!("[DEBUG] {}", z_sqrt);
    let mut ps = Vec::with_capacity(4);
    for x in (2..z_sqrt).rev() {
        if is_prime(x) {
            ps.push(x);
            if ps.len() == 2 {
                break;
            }
        }
    }
    // eprintln!("[DEBUG] {} {:?}", z_sqrt, ps);
    ps.reverse();
    for x in z_sqrt.. {
        if is_prime(x) {
            ps.push(x);
            if ps.len() == 4 {
                break;
            }
        }
    }
    // eprintln!("[DEBUG] {} {:?}", z_sqrt, ps);

    let mut ans = 1;

    for i in 0..3 {
        let temp = ps[i] * ps[i + 1];
        if temp <= z && ans < temp {
            ans = temp;
        }
    }

    println!("{}", ans);
}

fn pow(mut a: i64, mut b: i64, p: i64) -> i64 {
    let mut res = 1;
    while b > 0 {
        if (b & 1) == 1 {
            res = (res as i128 * a as i128 % p as i128) as i64;
        }
        b >>= 1;
        a = (a as i128 * a as i128 % p as i128) as i64;
    }
    res
}

fn check(x: i64, p: i64) -> bool {
    if x % p == 0 || pow(p % x, x - 1, x) != 1 {
        return false;
    }
    let mut k = x - 1;
    while k % 2 == 0 {
        k >>= 1;
        let temp = pow(p % x, k, x);
        if temp != 1 && temp != x - 1 {
            return false;
        }
        if temp == x - 1 {
            return true;
        }
    }
    true
}

fn is_prime(n: i64) -> bool {
    const PRIMES: [i64; 12] = [2, 3, 5, 7, 11, 13, 17, 19, 61, 2333, 4567, 24251];
    for &p in PRIMES.iter() {
        if n == p {
            return true;
        }
        if !check(n, p) {
            return false;
        }
    }
    true
}
