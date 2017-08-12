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
public class J {
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
        final long MOD = (long) (1e9 + 7);
        final long INV = (long) (5e8 + 4);

        public void solve(int testNumber, Scanner in, PrintWriter out) {
            String s = in.next();
            int n = s.length();
            int[] pow = new int[n + 1];
            pow[0] = 1;
            for (int i = 1; i <= n; ++i) {
                pow[i] = pow[i - 1] << 1;
                if (pow[i] >= MOD) {
                    pow[i] -= MOD;
                }
            }
            int cnt = 0;
            for (int i = 0; i < n; ++i)
                if (s.charAt(i) == '?') ++cnt;
            int res = 0, a = 0, b = 0;
            for (int i = n - 1; i >= 0; --i) {
                char c = s.charAt(i);
                if (c == '0') ++a;
                if (c == '?') --cnt;
                if (c == '?' || c == '1') {
                    res = (int) (((long) res + pow[cnt + b] * (a + (long) b * INV % MOD)) % MOD);
                }
                if (c == '?') ++b;
            }
            out.println(res);
        }

    }
}

