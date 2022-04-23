use std::io::stdin;

fn main() {
    let mut buf = String::new();
    stdin().read_line(&mut buf).unwrap();
    let test_case = buf.trim().parse().unwrap();
    for i in 1..=test_case {
        print!("Case #{}:", i);
        solve(&mut buf);
    }
}

fn ask(mut idx: i32, tree: &[i32]) -> i32 {
    let mut res = 0;
    while idx > 0 {
        res += tree[idx as usize];
        idx &= idx - 1;
    }
    res
}

fn add(mut idx: i32, n: i32, delta: i32, tree: &mut [i32]) {
    while idx <= n {
        tree[idx as usize] += delta;
        idx += idx & -idx;
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
    let n = next!(iter);
    let q = next!(iter);
    let prime = next!(iter);

    const MAX_N: usize = 5e5 as usize + 5;
    static mut A: [i64; MAX_N] = [0; MAX_N];
    static mut DIV_V_SUM: [i32; MAX_N] = [0; MAX_N];
    static mut UNDIV_COUNT: [i32; MAX_N] = [0; MAX_N];
    static mut UNDIV_MIN_V_SUM: [i32; MAX_N] = [0; MAX_N];
    static mut UNDIV_ADD_V_SUM: [i32; MAX_N] = [0; MAX_N];

    unsafe {
        for i in 0..=(n as usize) {
            DIV_V_SUM[i] = 0;
            UNDIV_COUNT[i] = 0;
            UNDIV_MIN_V_SUM[i] = 0;
        }
        if prime == 2 {
            for i in 0..=(n as usize) {
                UNDIV_ADD_V_SUM[i] = 0;
            }
        }

        iter = read!();
        for i in 1..=(n as usize) {
            A[i] = next!(iter);
            // println!("{} {}", A[i], degree(A[i], prime));
            if A[i] < prime {
                continue;
            }
            let r = A[i] % prime;
            if r == 0 {
                add(i as i32, n, degree(A[i], prime), &mut DIV_V_SUM);
            } else {
                add(i as i32, n, 1, &mut UNDIV_COUNT);
                add(i as i32, n, degree(A[i] - r, prime), &mut UNDIV_MIN_V_SUM);
                if prime == 2 {
                    add(i as i32, n, degree(A[i] + r, prime), &mut UNDIV_ADD_V_SUM);
                }
            }
        }

        for _ in 0..q {
            let mut iter = read!();
            let oper: i32 = next!(iter);
            if oper == 1 {
                let pos: usize = next!(iter);
                let val = next!(iter);

                let ori = A[pos];
                if ori >= prime {
                    let r = ori % prime;
                    if r == 0 {
                        add(pos as i32, n, -degree(ori, prime), &mut DIV_V_SUM);
                    } else {
                        add(pos as i32, n, -1, &mut UNDIV_COUNT);
                        add(pos as i32, n, -degree(ori - r, prime), &mut UNDIV_MIN_V_SUM);
                        if prime == 2 {
                            add(pos as i32, n, -degree(ori + r, prime), &mut UNDIV_ADD_V_SUM);
                        }
                    }
                }
                A[pos] = val;
                let r = val % prime;
                if val >= prime {
                    if r == 0 {
                        add(pos as i32, n, degree(val, prime), &mut DIV_V_SUM);
                    } else {
                        add(pos as i32, n, 1, &mut UNDIV_COUNT);
                        add(pos as i32, n, degree(val - r, prime), &mut UNDIV_MIN_V_SUM);
                        if prime == 2 {
                            add(pos as i32, n, degree(val + r, prime), &mut UNDIV_ADD_V_SUM);
                        }
                    }
                }
            } else {
                let s = next!(iter);
                let left = next!(iter, i32) - 1;
                let right = next!(iter);

                let div_ans = (ask(right, &DIV_V_SUM) - ask(left, &DIV_V_SUM)) as i64 * s;
                let undiv_ans = if prime != 2 || s % 2 == 1 {
                    ask(right, &UNDIV_MIN_V_SUM) - ask(left, &UNDIV_MIN_V_SUM)
                        + (ask(right, &UNDIV_COUNT) - ask(left, &UNDIV_COUNT)) * degree(s, prime)
                } else {
                    ask(right, &UNDIV_MIN_V_SUM) - ask(left, &UNDIV_MIN_V_SUM)
                        + (ask(right, &UNDIV_ADD_V_SUM) - ask(left, &UNDIV_ADD_V_SUM))
                        + (ask(right, &UNDIV_COUNT) - ask(left, &UNDIV_COUNT))
                            * (degree(s, prime) - 1)
                };

                // println!("{} {} {} {}", left, right, div_ans, undiv_ans);

                print!(" {}", div_ans + undiv_ans as i64);
            }
        }
    }
    println!()
}

fn degree(mut x: i64, prime: i64) -> i32 {
    let mut res = 0;
    while x > 0 && x % prime == 0 {
        res += 1;
        x /= prime;
    }
    res
}
