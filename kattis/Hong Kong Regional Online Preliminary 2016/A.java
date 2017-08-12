import java.io.OutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.PrintWriter;
import java.util.Scanner;

/**
 * Built using CHelper plug-in
 * Actual solution is at the top
 *
 * @author cycleke
 */
public class A {
    public static void main(String[] args) {
        InputStream inputStream = System.in;
        OutputStream outputStream = System.out;
        Scanner in = new Scanner(inputStream);
        PrintWriter out = new PrintWriter(outputStream);
        TempTask solver = new TempTask();
        solver.solve(1, in, out);
        out.close();
    }

    static class TempTask {
        private final int BASE = 50000;
        private final int MAXN = 800040;

        public void solve(int testNumber, Scanner in, PrintWriter out) {
            int n = 0;
            int tot = in.nextInt();
            int[] a = new int[tot];
            long[] num = new long[MAXN];
            long[] cnt = new long[MAXN];

            int cnt0 = 0;
            int len1 = 0;
            for (int i = 0; i < tot; ++i) {
                int x = in.nextInt();
                if (x == 0) {
                    ++cnt0;
                    continue;
                }
                a[n] = x;
                ++num[x + BASE];
                ++cnt[x + BASE];
                ++n;
                len1 = Integer.max(len1, x + BASE + 1);
            }

            int len = 1, len_cnt = 0;
            while (len < (len1 << 1)) {
                len <<= 1;
                ++len_cnt;
            }

            Complex[] c1 = new Complex[len];
            for (int i = 0; i < len1; ++i) {
                c1[i] = new Complex((double) num[i], 0);
            }
            for (int i = len1; i < len; ++i) {
                c1[i] = new Complex(0, 0);
            }

            int[] rev = new int[len];
            for (int i = 1; i < len; ++i) {
                rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (len_cnt - 1));
            }
            fft(rev, c1, len, 1);
            for (int i = 0; i < len; ++i) {
                c1[i] = c1[i].Multiply(c1[i]);
            }
            fft(rev, c1, len, -1);
            for (int i = 0; i < len; ++i) {
                num[i] = (long) (c1[i].x + 0.5);
            }
            len = (len - BASE - 1) * 2;
            for (int i = 0; i < n; ++i) {
                --num[(a[i] + BASE) << 1];
            }
            long ans = num[BASE << 1] * cnt0;
            for (int i = 0; i < len; ++i) {
                if (cnt[i] > 0) {
                    ans += num[i + BASE] * cnt[i];
                }
            }
            if (cnt0 != 0) {
                if (cnt0 >= 3) {
                    long temp = cnt0;
                    temp *= cnt0 - 1;
                    temp *= cnt0 - 2;
                    ans += temp;
                }
                for (int i = 0; i < len1; ++i) {
                    if (cnt[i] >= 2) {
                        long temp = cnt0;
                        temp *= cnt[i];
                        temp *= cnt[i] - 1;
                        ans += temp * 2;
                    }
                }
            }
            out.println(ans);
        }

        public void fft(int[] rev, Complex[] a, int n, int type) {
            for (int i = 0; i < n; ++i) {
                if (i < rev[i]) {
                    Complex temp = a[rev[i]];
                    a[rev[i]] = a[i];
                    a[i] = temp;
                }
            }
            for (int j = 1; j < n; j <<= 1) {
                Complex wn = new Complex(Math.cos(Math.PI / j), type * Math.sin(Math.PI / j));
                for (int i = 0; i < n; i += (j << 1)) {
                    Complex w = new Complex(1, 0);
                    for (int k = 0; k < j; ++k) {
                        Complex t1 = a[i + k];
                        Complex t2 = w.Multiply(a[i + j + k]);
                        a[i + k] = t1.Add(t2);
                        a[i + j + k] = t1.Subtract(t2);
                        w = w.Multiply(wn);
                    }
                }
            }
            if (type == -1) {
                for (int i = 0; i < n; ++i) {
                    a[i] = new Complex(a[i].x / n, a[i].y / n);
                }
            }
        }

        public class Complex {
            public double x;
            public double y;

            public Complex() {
                x = 0;
                y = 0;
            }

            public Complex(double _x, double _y) {
                x = _x;
                y = _y;
            }

            public Complex Add(Complex other) {
                return new Complex(this.x + other.x, this.y + other.y);
            }

            public Complex Subtract(Complex other) {
                return new Complex(this.x - other.x, this.y - other.y);
            }

            public Complex Multiply(Complex other) {
                double _x = this.x * other.x - this.y * other.y;
                double _y = this.x * other.y + this.y * other.x;
                return new Complex(_x, _y);
            }

        }

    }
}
