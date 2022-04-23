use std::io::stdin;

fn main() {
    let mut buf = String::new();
    stdin().read_line(&mut buf).unwrap();

    let testcase = buf.trim().parse().unwrap();

    stdin().read_line(&mut buf).unwrap();

    let mut exp = vec![vec![vec![vec![0.0; 61]; 61]; 61]; 4];
    let mut dec = vec![vec![vec![vec![' '; 61]; 61]; 61]; 4];
    prework(&mut exp[0], &mut dec[0], 1, 1);
    prework(&mut exp[1], &mut dec[1], 2, 1);
    prework(&mut exp[2], &mut dec[2], 10, 1);
    prework(&mut exp[3], &mut dec[3], 1, 0);

    for case in 1..=testcase {
        print!("Case #{}: ", case);

        buf.clear();
        stdin().read_line(&mut buf).unwrap();
        let args: Vec<i32> = buf.split_whitespace().map(|s| s.parse().unwrap()).collect();
        if args[1] == 0 {
            gao(&exp[3], &dec[3]);
        } else {
            match args[0] / args[1] {
                1 => gao(&exp[0], &dec[0]),
                2 => gao(&exp[1], &dec[1]),
                10 => gao(&exp[2], &dec[2]),
                _ => unreachable!(),
            }
        }
    }
}

fn gao(exp: &[Vec<Vec<f64>>], dec: &[Vec<Vec<char>>]) {
    let mut max = 0.0;
    let (mut r0, mut p0, mut s0) = (0, 0, 0);
    (0..=60).for_each(|r| {
        for p in 0..=(60 - r) {
            let s = 60 - r - p;
            if exp[r][p][s] > max {
                max = exp[r][p][s];
                r0 = r;
                p0 = p;
                s0 = s;
            }
        }
    });

    let mut sb = String::with_capacity(60);
    for _ in 0..60 {
        sb.push(dec[r0][p0][s0]);
        match dec[r0][p0][s0] {
            'R' => r0 -= 1,
            'P' => p0 -= 1,
            'S' => s0 -= 1,
            _ => unreachable!(),
        }
    }
    println!("{}", sb.chars().rev().collect::<String>());
}

fn prework(exp: &mut Vec<Vec<Vec<f64>>>, dec: &mut Vec<Vec<Vec<char>>>, w: i32, e: i32) {
    let w = w as f64;
    let e = e as f64;
    exp[0][0][1] = w / 3.0 + e / 3.0;
    exp[0][1][0] = w / 3.0 + e / 3.0;
    exp[1][0][0] = w / 3.0 + e / 3.0;
    dec[0][0][1] = 'S';
    dec[0][1][0] = 'P';
    dec[1][0][0] = 'R';

    for n in 2..61 {
        for r in 0..=n {
            for p in 0..=(n - r) {
                let s = n - r - p;
                if r > 0
                    && exp[r][p][s]
                        < exp[r - 1][p][s]
                            + w * p as f64 / (n - 1) as f64
                            + e * s as f64 / (n - 1) as f64
                {
                    exp[r][p][s] = exp[r - 1][p][s]
                        + w * p as f64 / (n - 1) as f64
                        + e * s as f64 / (n - 1) as f64;
                    dec[r][p][s] = 'R';
                }
                if p > 0
                    && exp[r][p][s]
                        < exp[r][p - 1][s]
                            + w * s as f64 / (n - 1) as f64
                            + e * r as f64 / (n - 1) as f64
                {
                    exp[r][p][s] = exp[r][p - 1][s]
                        + w * s as f64 / (n - 1) as f64
                        + e * r as f64 / (n - 1) as f64;
                    dec[r][p][s] = 'P';
                }
                if s > 0
                    && exp[r][p][s]
                        < exp[r][p][s - 1]
                            + w * r as f64 / (n - 1) as f64
                            + e * p as f64 / (n - 1) as f64
                {
                    exp[r][p][s] = exp[r][p][s - 1]
                        + w * r as f64 / (n - 1) as f64
                        + e * p as f64 / (n - 1) as f64;
                    dec[r][p][s] = 'S';
                }
            }
        }
    }
}
