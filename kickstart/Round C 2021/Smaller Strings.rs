use std::io::stdin;

const MAX_N: usize = 1e5 as usize;
const MOD: i32 = 1e9 as i32 + 7;

fn main() {
    let mut buf = String::with_capacity(MAX_N);
    stdin().read_line(&mut buf).unwrap();

    let mut dig = [0; MAX_N];

    let testcase = buf.trim().parse().unwrap();
    for case in 1..=testcase {
        print!("Case #{}: ", case);
        solve(&mut buf, &mut dig);
    }
}

fn solve(buf: &mut String, dig: &mut [i32]) {
    buf.clear();
    stdin().read_line(buf).unwrap();
    let args: Vec<i32> = buf.split_whitespace().map(|x| x.parse().unwrap()).collect();
    let n = args[0] as usize;
    let k = args[1];

    buf.clear();
    stdin().read_line(buf).unwrap();
    let bytes = buf.as_bytes();
    for i in 0..n {
        dig[i] = ((bytes[i] - b'a') as i32).min(k - 1);
    }

    let half = (n + 1) / 2;
    let mut suff = mod_pow(k, half as i32 - 1);
    let inv_k = mod_pow(k, MOD - 2);
    let mut ans = 0;

    for &chr in dig[0..half].iter() {
        ans = ((ans as i64 + chr as i64 * suff as i64) % (MOD as i64)) as i32;
        suff = ((suff as i64 * inv_k as i64) % (MOD as i64)) as i32;
    }

    if n > 1 {
        for (lhs, rhs) in dig[half..].iter().zip(dig[..=n - 1 - half].iter().rev()) {
            match lhs.cmp(rhs) {
                std::cmp::Ordering::Greater => {
                    ans += 1;
                    if ans >= MOD {
                        ans -= MOD;
                    }
                    break;
                }
                std::cmp::Ordering::Equal => continue,
                std::cmp::Ordering::Less => break,
            }
        }
    }
    println!("{}", ans);
}

fn mod_pow(x: i32, mut exp: i32) -> i32 {
    let mut x = x as i64;
    let mut res = 1;

    while exp > 0 {
        if exp % 2 == 1 {
            res = res * x % (MOD as i64);
        }
        x = x * x % (MOD as i64);
        exp >>= 1;
    }

    res as i32
}
