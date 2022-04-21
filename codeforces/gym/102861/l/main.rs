use std::{
    collections::HashSet,
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
    let l = next!(iter);
    let c = next!(iter);
    let mut a = vec![vec![0; c]; l];
    for line in a.iter_mut() {
        buf.clear();
        input.read_line(&mut buf).unwrap();
        line.copy_from_slice(&buf.as_bytes()[..c]);
    }

    const MOD: u32 = 998244353;
    const PRIMES: [u32; 26] = [
        2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 97,
        101, 103,
    ];

    buf.clear();
    input.read_line(&mut buf).unwrap();
    let n = buf.trim_end().parse().unwrap();

    let mut max_len = 0;
    let mut dict = HashSet::with_capacity(n);
    for _ in 0..n {
        buf.clear();
        input.read_line(&mut buf).unwrap();

        let s = buf.trim_end().as_bytes();
        let mut h = 1;
        for &chr in s.iter() {
            h = (h as u64 * PRIMES[(chr - b'A') as usize] as u64 % MOD as u64) as u32;
        }

        max_len = max_len.max(s.len());
        dict.insert((s.len() as u32, h));
    }

    let mut count = vec![vec![HashSet::new(); c]; l];
    for i in 0..l {
        for j in 0..c {
            let mut h = 1;
            for k in 0..max_len.min(l - i) {
                let ni = i + k;
                h = (h as u64 * PRIMES[(a[ni][j] - b'A') as usize] as u64 % MOD as u64) as u32;
                if dict.contains(&(k as u32 + 1, h)) {
                    for o in 0..=k {
                        count[i + o][j].insert((k as u32, h));
                    }
                }
            }

            h = 1;
            for k in 0..max_len.min(c - j) {
                let nj = j + k;
                h = (h as u64 * PRIMES[(a[i][nj] - b'A') as usize] as u64 % MOD as u64) as u32;
                if dict.contains(&(k as u32 + 1, h)) {
                    for o in 0..=k {
                        count[i][j + o].insert((k as u32, h));
                    }
                }
            }

            h = 1;
            for k in 0..max_len.min(l - i).min(c - j) {
                let ni = i + k;
                let nj = j + k;
                h = (h as u64 * PRIMES[(a[ni][nj] - b'A') as usize] as u64 % MOD as u64) as u32;
                if dict.contains(&(k as u32 + 1, h)) {
                    for o in 0..=k {
                        count[i + o][j + o].insert((k as u32, h));
                    }
                }
            }

            h = 1;
            for k in 0..max_len.min(l - i).min(j + 1) {
                let ni = i + k;
                let nj = j - k;
                h = (h as u64 * PRIMES[(a[ni][nj] - b'A') as usize] as u64 % MOD as u64) as u32;
                if dict.contains(&(k as u32 + 1, h)) {
                    for o in 0..=k {
                        count[i + o][j - o].insert((k as u32, h));
                    }
                }
            }
        }
    }

    let ans = count
        .iter()
        .flat_map(|v| v.iter())
        .filter(|c| c.len() > 1)
        .count();
    writeln!(output, "{}", ans).unwrap();
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
                "4 5
XBOIC
DKIRA
ALBOA
BHGES
3
BOLA
CASA
BOI",
                "3",
            ),
            (
                "3 3
AAB
ABA
BAA
2
ABA
BBB",
                "3",
            ),
            (
                "2 4
AAAA
AAAA
2
AAA
BBB",
                "0",
            ),
        ];

        for (input, output) in samples {
            test(input, output);
        }
    }

    #[test]
    fn tests() {
        let tests = [
            (
                "5 5
OPYIL
LAAJS
NVYUK
MOUQH
NDGGR
20
WAHPB
GCF
NHTWA
UY
GKRAC
NGH
ZCRAJ
DH
FOIUW
TW
NW
TGDTK
IQ
FSPXU
FX
UFY
BWF
UP
QBE
EZ",
                "0",
            ),
            (
                "13 18
RWHYTHKARYWNNRQZLB
QIGWKIDCZDNSREQBEJ
IOMBPIQECHEPIUYQSK
YWMZZZRSFHTMTDCFFT
PVYRCCHMYFCQPCODCP
EVIJFDXYHAFOTUJTOO
VVCVCFMTJAWLSAHALM
FLMONRCGNMCBCXYETA
LHVVJRIBTPDHDJSRXF
KANYOPZSPAYKAKRWHC
PPELHHSKSMESROSGMI
YOANOYXQKQORUEHAPQ
KJACVGUMVOUJWSZYFN
20
EGJWUDTAMTP
DAEGVLCJ
RERPWRQEGRKMCJ
FCJRVBVZBAH
NJIVCOMULFKROBD
DMJLQV
MW
NXAUWNDFKITY
GEMZUP
WURGFIDKUZK
WMDVBIA
QVJSEPGDJ
IGQ
OXKRHG
TPOF
JGALRTHDLLSSQC
ZIH
WFNPOTF
IVPCFYEQRXZUJM
DFRUGBCHZ",
                "0",
            ),
        ];

        for (input, output) in tests {
            test(input, output);
        }
    }
}
