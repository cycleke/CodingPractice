use std::io::stdin;

fn main() {
    let mut buf = String::new();
    stdin().read_line(&mut buf).unwrap();
    let test_case = buf.trim().parse().unwrap();
    for i in 1..=test_case {
        print!("Case #{}: ", i);
        solve(&mut buf);
    }
}

fn solve(buf: &mut String) {
    // macro_rules! read {
    //     () => {{
    //         buf.clear();
    //         stdin().read_line(buf).unwrap();
    //         buf.split_ascii_whitespace()
    //     }};
    // }
    // macro_rules! next {
    //     ($iter:expr) => {
    //         $iter.next().unwrap().parse().unwrap()
    //     };
    //     ($iter:expr, $type:ty) => {
    //         $iter.next().unwrap().parse::<$type>().unwrap()
    //     };
    // }

    buf.clear();
    stdin().read_line(buf).unwrap();
    let mut str = buf.trim().to_string();
    let ori = str.clone();
    let ori = ori.as_bytes();
    unsafe {
        let str = str.as_bytes_mut();
        let n = str.len();
        for i in 0..n {
            if str[i] != ori[i] {
                continue;
            }
            let mut ok = false;
            for j in 0..n {
                if i == j {
                    continue;
                }
                if str[i] != ori[j] && str[j] != ori[i] {
                    str[i] ^= str[j];
                    str[j] ^= str[i];
                    str[i] ^= str[j];
                    ok = true;
                    break;
                }
            }
            if !ok {
                println!("IMPOSSIBLE");
                return;
            }
        }
    }
    println!("{}", str);
}
