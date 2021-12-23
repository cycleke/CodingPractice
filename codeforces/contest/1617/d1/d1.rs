use std::io::{stdin, stdout, BufRead, Write};

fn main() {
    let input = stdin();
    let output = stdout();
    solve(input.lock(), output.lock());
}

fn solve<R: BufRead, W: Write>(mut input: R, mut output: W) {
    let mut buf = String::new();
    input.read_line(&mut buf).unwrap();
    let testcase = buf.trim_end().parse().unwrap();
    for _ in 0..testcase {
        solve_case(&mut input, &mut output);
    }
}

fn query<R: BufRead, W: Write>(a: i32, b: i32, c: i32, input: &mut R, output: &mut W) -> i32 {
    writeln!(output, "? {} {} {}", a, b, c).unwrap();
    output.flush().unwrap();

    static mut BUFFER: std::string::String = String::new();
    unsafe {
        BUFFER.clear();
        input.read_line(&mut BUFFER).unwrap();
        BUFFER.trim_end().parse().unwrap()
    }
}

fn solve_case<R: BufRead, W: Write>(input: &mut R, output: &mut W) {
    let mut buf = String::new();
    input.read_line(&mut buf).unwrap();
    let n = buf.trim_end().parse::<i32>().unwrap();
    let mut a = vec![-1; n as usize + 1];
    for i in (1..=n - 2).step_by(3) {
        a[i as usize] = query(i, i + 1, i + 2, input, output);
    }

    let mut imp = -1;
    let mut crew = -1;
    let mut role = vec![-1; n as usize + 1];
    for i in (1..=n - 5).step_by(3) {
        if a[i as usize] != a[i as usize + 3] {
            a[i as usize + 1] = query(i + 1, i + 2, i + 3, input, output);
            a[i as usize + 2] = query(i + 2, i + 3, i + 4, input, output);
            for j in i..i + 3 {
                if a[j as usize] != a[j as usize + 1] {
                    if a[j as usize] == 1 {
                        imp = j + 3;
                        crew = j;
                        role[j as usize] = 1;
                        role[j as usize + 3] = 0;
                    } else {
                        imp = j;
                        crew = j + 3;
                        role[j as usize] = 0;
                        role[j as usize + 3] = 1;
                    }
                }
            }
            break;
        }
    }

    eprintln!("{} {}", imp, crew);
    for i in (1..=n - 2).step_by(3) {
        if i == imp || i + 1 == imp || i + 2 == imp || i == crew || i + 1 == crew || i + 2 == crew {
            for j in i..i + 3 {
                if role[j as usize] == -1 {
                    role[j as usize] = query(imp, crew, j, input, output);
                }
            }
        } else if a[i as usize] == 0 {
            if query(i, i + 1, crew, input, output) == 1 {
                if query(i, imp, crew, input, output) == 0 {
                    role[i as usize] = 0;
                    role[i as usize + 1] = 1;
                } else {
                    role[i as usize] = 1;
                    role[i as usize + 1] = 0;
                }
                role[i as usize + 2] = 0;
            } else {
                role[i as usize] = 0;
                role[i as usize + 1] = 0;
                role[i as usize + 2] = query(i + 2, imp, crew, input, output);
            }
        } else if query(i, i + 1, imp, input, output) == 0 {
            if query(i, imp, crew, input, output) == 0 {
                role[i as usize] = 0;
                role[i as usize + 1] = 1;
            } else {
                role[i as usize] = 1;
                role[i as usize + 1] = 0;
            }
            role[i as usize + 2] = 1;
        } else {
            role[i as usize] = 1;
            role[i as usize + 1] = 1;
            role[i as usize + 2] = query(i + 2, imp, crew, input, output);
        }
    }

    let a: Vec<i32> = (1..=n).filter(|&i| role[i as usize] == 0).collect();

    write!(output, "! {}", a.len()).unwrap();
    for x in a {
        write!(output, " {}", x).unwrap();
    }
    writeln!(output).unwrap();
}

#[cfg(test)]
mod test {
    use crate::solve;

    fn test(input: &str, output: &str) {
        let mut v: Vec<u8> = Vec::new();
        solve(input.as_bytes(), &mut v);
        assert_eq!(String::from_utf8(v).unwrap(), output);
    }
}
