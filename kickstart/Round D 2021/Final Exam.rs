use std::ops::Bound::{Excluded, Included, Unbounded};
use std::{collections::BTreeSet, io::stdin};

fn main() {
    let mut buf = String::new();
    let mut segs = BTreeSet::new();
    stdin().read_line(&mut buf).unwrap();
    let test_case = buf.trim().parse().unwrap();
    for i in 1..=test_case {
        print!("Case #{}:", i);
        solve(&mut buf, &mut segs);
    }
}

fn solve(buf: &mut String, segs: &mut BTreeSet<(i64, i64)>) {
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
    }

    let mut iter = read!();
    let n = next!(iter);
    let m = next!(iter);

    segs.clear();
    for _ in 0..n {
        let mut iter = read!();
        let a = next!(iter);
        let b = next!(iter);
        segs.insert((a, b));
    }

    iter = read!();
    for _ in 0..m {
        let s = next!(iter);
        let mut pref = std::i64::MAX;
        let mut succ = std::i64::MAX;
        let mut pref_seg = (pref, pref);
        let mut succ_seg = (succ, succ);

        let mut iter = segs.range((Unbounded, Included(&(s, s))));
        if let Some(&(l, r)) = iter.next_back() {
            if l <= s && s <= r {
                print!(" {}", s);
                segs.remove(&(l, r));
                if l < s {
                    segs.insert((l, s - 1));
                }
                if s < r {
                    segs.insert((s + 1, r));
                }
                continue;
            }
            pref = s - r;
            pref_seg = (l, r);
        }

        let mut iter = segs.range((Excluded(&(s, s)), Unbounded));
        if let Some(&(l, r)) = iter.next() {
            succ = l - s;
            succ_seg = (l, r);
        }

        if pref <= succ {
            print!(" {}", pref_seg.1);
            segs.remove(&pref_seg);
            if pref_seg.0 < pref_seg.1 {
                segs.insert((pref_seg.0, pref_seg.1 - 1));
            }
        } else {
            print!(" {}", succ_seg.0);
            segs.remove(&succ_seg);
            if succ_seg.0 < succ_seg.1 {
                segs.insert((succ_seg.0 + 1, succ_seg.1));
            }
        }
    }
    println!();
}
