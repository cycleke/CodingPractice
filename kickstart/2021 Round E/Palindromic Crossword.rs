use std::io::{stdin, stdout, Write};

const MAX_N: usize = 1e3 as usize;

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
    buf.clear();
    stdin().read_line(buf).unwrap();
    let mut iter = buf.split_ascii_whitespace();
    let n = iter.next().unwrap().parse().unwrap();
    let m = iter.next().unwrap().parse().unwrap();

    static mut GRID: [[u8; MAX_N]; MAX_N] = [[0; MAX_N]; MAX_N];
    static mut SET_CHAR: [[u8; MAX_N]; MAX_N] = [[0; MAX_N]; MAX_N];
    static mut PARENT: [[(usize, usize); MAX_N]; MAX_N] = [[(0, 0); MAX_N]; MAX_N];

    fn find((x, y): (usize, usize), pa: &mut [[(usize, usize); MAX_N]]) -> (usize, usize) {
        if pa[x][y] == (x, y) {
            (x, y)
        } else {
            pa[x][y] = find(pa[x][y], pa);
            pa[x][y]
        }
    }

    unsafe {
        for i in 0..n {
            buf.clear();
            stdin().read_line(buf).unwrap();
            for (j, b) in buf.bytes().enumerate().take(m) {
                GRID[i][j] = b;
                SET_CHAR[i][j] = if b == b'#' || b == b'.' { 0 } else { b };
                PARENT[i][j] = (i, j);
            }
        }

        for i in 0..n {
            let mut j = 0;
            while j < m {
                if GRID[i][j] == b'#' {
                    j += 1;
                    continue;
                }

                let mut k = j;
                while k + 1 < m && GRID[i][k + 1] != b'#' {
                    k += 1;
                }

                let mut left = j;
                let mut right = k;
                j = k + 1;

                while left < right {
                    let (plx, ply) = find((i, left), &mut PARENT);
                    let (prx, pry) = find((i, right), &mut PARENT);

                    if (plx, ply) != (prx, pry) {
                        PARENT[prx][pry] = (plx, ply);
                        SET_CHAR[plx][ply] |= SET_CHAR[prx][pry];
                    }

                    left += 1;
                    right -= 1;
                }
            }
        }

        for j in 0..m {
            let mut i = 0;
            while i < n {
                if GRID[i][j] == b'#' {
                    i += 1;
                    continue;
                }

                let mut k = i;
                while k + 1 < n && GRID[k + 1][j] != b'#' {
                    k += 1;
                }

                let mut left = i;
                let mut right = k;
                i = k + 1;

                while left < right {
                    let (plx, ply) = find((left, j), &mut PARENT);
                    let (prx, pry) = find((right, j), &mut PARENT);

                    if (plx, ply) != (prx, pry) {
                        PARENT[prx][pry] = (plx, ply);
                        SET_CHAR[plx][ply] |= SET_CHAR[prx][pry];
                    }

                    left += 1;
                    right -= 1;
                }
            }
        }

        let mut ans = 0;
        for i in 0..n {
            for j in 0..m {
                if GRID[i][j] == b'.' {
                    let (px, py) = find((i, j), &mut PARENT);
                    if SET_CHAR[px][py] != 0 {
                        ans += 1;
                        GRID[i][j] = SET_CHAR[px][py];
                    }
                }
            }
        }
        println!("{}", ans);
        for i in 0..n {
            stdout().write_all(&GRID[i][0..m]).unwrap();
            println!();
        }
    }
}
