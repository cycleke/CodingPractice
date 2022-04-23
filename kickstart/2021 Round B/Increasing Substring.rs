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
        print!("Case #{}:", case);
        solve(&mut buf);
    }
}

fn solve(buf: &mut String) {
    let n = read_integers(buf)[0] as usize;

    buf.clear();
    stdin().read_line(buf).unwrap();

    let mut len = 0;
    let mut pref = std::u8::MAX;
    for &curr in buf.as_bytes()[..n].iter() {
        if curr > pref {
            len += 1;
        } else {
            len = 1;
        }
        pref = curr;
        print!(" {}", len);
    }

    println!()
}
