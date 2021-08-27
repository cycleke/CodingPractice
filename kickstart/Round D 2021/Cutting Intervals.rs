use std::{
    collections::{BTreeMap, BinaryHeap},
    io::stdin,
};

fn main() {
    let mut buf = String::new();
    let mut heap = BinaryHeap::new();
    let mut delta = BTreeMap::new();
    stdin().read_line(&mut buf).unwrap();
    let test_case = buf.trim().parse().unwrap();
    for i in 1..=test_case {
        print!("Case #{}: ", i);
        solve(&mut buf, &mut heap, &mut delta);
    }
}

fn solve(buf: &mut String, heap: &mut BinaryHeap<(i32, i64)>, delta: &mut BTreeMap<i64, i32>) {
    buf.clear();
    stdin().read_line(buf).unwrap();
    let mut iter = buf.split_ascii_whitespace();
    let n = iter.next().unwrap().parse().unwrap();
    let mut c = iter.next().unwrap().parse().unwrap();

    delta.clear();
    for _ in 0..n {
        buf.clear();
        stdin().read_line(buf).unwrap();
        let mut iter = buf.split_ascii_whitespace();
        let left: i64 = iter.next().unwrap().parse().unwrap();
        let right = iter.next().unwrap().parse().unwrap();

        let it = delta.entry(left + 1).or_insert(0);
        *it += 1;
        let it = delta.entry(right).or_insert(0);
        *it -= 1;
    }

    let mut pre = 0;
    let mut sum = 0;
    heap.clear();
    for (&k, &v) in delta.iter() {
        heap.push((sum, k - pre));
        sum += v;
        pre = k;
    }

    let mut ans = n;
    while let Some((k, v)) = heap.pop() {
        let v = v.min(c);
        c -= v;
        ans += k as i64 * v;
        if c == 0 {
            break;
        }
    }
    println!("{}", ans);
}
