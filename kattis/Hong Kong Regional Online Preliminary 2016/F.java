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
public class F {
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
        public void solve(int testNumber, Scanner in, PrintWriter out) {
            int n = in.nextInt();
            int[] t = new int[n + 1];
            int[] c = new int[n + 1];

            for (int i = 1; i < n; ++i)
                c[i] = in.nextInt();
            for (int i = 0; i < n; ++i)
                t[i] = in.nextInt();

            int CurtenTime = 0;
            int CurtenLocation = 0;
            int MinCost = 1 << 30;
            long TotalCost = 0;
            while (CurtenLocation < n) {
                ++CurtenTime;
                ++CurtenLocation;
                TotalCost += c[CurtenLocation];
                MinCost = Math.min(MinCost, c[CurtenLocation]);
                long Round = (t[CurtenLocation] - CurtenTime + 1) / 2;
                if (Round > 0) {
                    TotalCost += Round * 2 * MinCost;
                    CurtenTime += Round * 2;
                }
            }
            out.println(TotalCost);
        }

    }
}

