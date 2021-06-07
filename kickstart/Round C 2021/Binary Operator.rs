use std::{collections::HashMap, io::stdin};

fn main() {
    let mut buf = String::new();
    stdin().read_line(&mut buf).unwrap();

    let testcase = buf.trim().parse().unwrap();
    let mut rnd = rand::XoShiro256SS::new(None);
    for case in 1..=testcase {
        print!("Case #{}:", case);
        solve(&mut buf, &mut rnd);
    }
}

fn solve(buf: &mut String, rnd: &mut rand::XoShiro256SS) {
    buf.clear();
    stdin().read_line(buf).unwrap();
    let n = buf.trim().parse().unwrap();

    let mut exps = vec![String::new(); n];
    let mut idn = vec![0; n];
    let mut cnt = 0;
    for i in 0..n {
        let mut id = 0;
        stdin().read_line(&mut exps[i]).unwrap();
        // eprintln!("{}", exps[i]);
        for j in 0..i {
            if equal(&exps[i], &exps[j], rnd) {
                id = idn[j];
                break;
            }
        }
        if id == 0 {
            cnt += 1;
            id = cnt;
        }
        idn[i] = id;
    }

    for x in idn {
        print!(" {}", x);
    }
    println!();
}

fn equal(lhs: &str, rhs: &str, rnd: &mut rand::XoShiro256SS) -> bool {
    const PRIMES: [u64; 4] = [1e9 as u64 + 7, 1e9 as u64 + 9, 998244353, 1610612741];

    let mut ops = HashMap::new();
    for &prime in PRIMES.iter() {
        ops.clear();
        if eval(lhs, &mut ops, prime, rnd) != eval(rhs, &mut ops, prime, rnd) {
            return false;
        }
    }
    true
}

fn eval(
    exp: &str,
    ops: &mut HashMap<(u64, u64), u64>,
    prime: u64,
    rnd: &mut rand::XoShiro256SS,
) -> u64 {
    let mut curr = None;
    let mut nums = Vec::new();
    let mut opers = Vec::new();

    for chr in exp.bytes() {
        match chr as char {
            '+' | '*' | '#' => {
                opers.push(chr as char);
                if let Some(x) = curr {
                    nums.push(x);
                    curr = None;
                }
            }
            '(' | '\n' => {
                continue;
            }
            ')' => {
                if let Some(x) = curr {
                    nums.push(x);
                    curr = None;
                }
                let l = nums.pop().unwrap();
                let r = nums.pop().unwrap();
                match opers.pop() {
                    Some('+') => {
                        nums.push((l + r) % prime);
                    }
                    Some('*') => {
                        nums.push((l * r) % prime);
                    }
                    Some('#') => {
                        nums.push(*ops.entry((l, r)).or_insert(rnd.next() % prime));
                    }
                    _ => unreachable!(),
                }
            }
            _ => {
                if let Some(x) = curr {
                    curr = Some((x * 10 + (chr - b'0') as u64) % prime);
                } else {
                    curr = Some((chr - b'0') as u64);
                }
            }
        }
    }

    if let Some(x) = curr {
        nums.push(x);
    }

    assert_eq!(nums.len(), 1);

    nums[0]
}

mod rand {
    use std::time;

    #[derive(Debug)]
    pub struct XoShiro256SS {
        state: [u64; 4],
    }

    impl XoShiro256SS {
        pub fn new(seed: Option<u64>) -> Self {
            let seed: u64 = match seed {
                Some(x) => x,
                None => {
                    match time::SystemTime::now().duration_since(time::SystemTime::UNIX_EPOCH) {
                        Ok(n) => n.as_secs(),
                        Err(_) => 0,
                    }
                }
            };

            let mut splitmix64 = SplitMix64 { state: seed };
            let mut state = [0; 4];

            let tmp = splitmix64.next();
            state[0] = tmp;
            state[1] = tmp >> 32;

            let tmp = splitmix64.next();
            state[2] = tmp;
            state[3] = tmp >> 32;
            Self { state }
        }

        fn rol64(x: u64, k: i32) -> u64 {
            (x << k) | (x >> (64 - k))
        }

        pub fn next(&mut self) -> u64 {
            let result = XoShiro256SS::rol64(self.state[1].wrapping_mul(5), 7).wrapping_mul(9);
            let t = self.state[1] << 17;

            self.state[2] ^= self.state[0];
            self.state[3] ^= self.state[1];
            self.state[1] ^= self.state[2];
            self.state[0] ^= self.state[3];

            self.state[2] ^= t;
            self.state[3] = XoShiro256SS::rol64(self.state[3], 45);

            result
        }
    }

    struct SplitMix64 {
        state: u64,
    }

    impl SplitMix64 {
        fn next(&mut self) -> u64 {
            let mut result: u64 = self.state;
            self.state = result.wrapping_add(0x9E3779B97f4A7C15);
            result = (result ^ (result >> 30)).wrapping_mul(0xBF58476D1CE4E5B9);
            result = (result ^ (result >> 27)).wrapping_mul(0x94D049BB133111EB);
            result ^ (result >> 31)
        }
    }
}
