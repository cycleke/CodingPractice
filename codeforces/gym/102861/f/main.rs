use std::io::{stdin, stdout, BufRead, Write};

fn main() {
    let input = stdin();
    let output = stdout();
    solve(input.lock(), output.lock());
}

fn solve<R: BufRead, W: Write>(mut input: R, mut output: W) {
    let mut buf = String::new();
    input.read_line(&mut buf).unwrap();

    let mut player = 0;
    let mut p = [0, 0];
    let mut g = [0, 0];
    for chr in buf.trim_end().bytes() {
        match chr {
            b'S' => {
                p[player] += 1;
            }
            b'R' => {
                player ^= 1;
                p[player] += 1;
            }
            b'Q' => {
                if g[0] == 2 {
                    writeln!(output, "{} (winner) - {}", g[0], g[1]).unwrap();
                } else if g[1] == 2 {
                    writeln!(output, "{} - {} (winner)", g[0], g[1]).unwrap();
                } else if player == 0 {
                    writeln!(output, "{} ({}*) - {} ({})", g[0], p[0], g[1], p[1]).unwrap();
                } else {
                    writeln!(output, "{} ({}) - {} ({}*)", g[0], p[0], g[1], p[1]).unwrap();
                }
                continue;
            }
            _ => unreachable!(),
        }

        if (p[player] >= 5 && p[player] - p[player ^ 1] >= 2) || p[player] == 10 {
            g[player] += 1;
            p = [0, 0];
        }
    }
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
                "SRSSQSSSSQRRSS",
                "0 (1) - 0 (3*)
0 (0) - 1 (2*)",
            ),
            (
                "SRSSQSSSSQRRSSQ",
                "0 (1) - 0 (3*)
0 (0) - 1 (2*)
0 - 2 (winner)",
            ),
            ("RSRSSRRRRRRRRRRSSSSRRSQ", "2 (winner) - 0"),
        ];

        for (input, output) in samples {
            test(input, output);
        }
    }

    #[test]
    fn tests() {
        let tests = [];

        for (input, output) in tests {
            test(input, output);
        }
    }
}
