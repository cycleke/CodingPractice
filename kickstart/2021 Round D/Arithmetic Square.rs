use std::{collections::HashMap, io::stdin};

fn main() {
    let mut buf = String::new();
    stdin().read_line(&mut buf).unwrap();
    let test_case = buf.trim().parse().unwrap();

    let mut cnt = HashMap::with_capacity(4);
    for i in 1..=test_case {
        print!("Case #{}: ", i);
        solve(&mut buf, &mut cnt);
    }
}

fn solve(buf: &mut String, cnt: &mut HashMap<i32, i32>) {
    let mut a = [[0; 3]; 3];

    for i in 0..3 {
        buf.clear();
        stdin().read_line(buf).unwrap();
        let mut iter = buf.split_ascii_whitespace();
        for j in 0..3 {
            if i == 1 && j == 1 {
                continue;
            }
            a[i][j] = iter.next().unwrap().parse().unwrap();
        }
    }

    fn check(a: i32, b: i32, c: i32) -> i32 {
        if a + c == 2 * b {
            1
        } else {
            0
        }
    }

    let pre = check(a[0][0], a[0][1], a[0][2])
        + check(a[2][0], a[2][1], a[2][2])
        + check(a[0][0], a[1][0], a[2][0])
        + check(a[0][2], a[1][2], a[2][2]);

    cnt.clear();

    let it = cnt.entry(a[0][0] + a[2][2]).or_insert(0);
    *it += 1;
    let it = cnt.entry(a[2][0] + a[0][2]).or_insert(0);
    *it += 1;
    let it = cnt.entry(a[1][0] + a[1][2]).or_insert(0);
    *it += 1;
    let it = cnt.entry(a[0][1] + a[2][1]).or_insert(0);
    *it += 1;

    let suf = cnt
        .iter()
        .map(|(&k, &v)| if k % 2 == 0 { v } else { 0 })
        .max()
        .unwrap();

    println!("{}", pre + suf);
}
