import java.io.*;
import java.util.*;
import java.math.*;
import java.lang.*;

public class D{

    private static Reader in;
    private static PrintWriter out;

    public static void main(String[] args) throws IOException {
        in = new Reader();
        in.init(System.in);
        out = new PrintWriter(System.out);

        char[] s = in.next().toCharArray();

        int n = s.length;
        int[] ans = new int[n + 1];
        int[][] dp = new int[n][n];

        ans[1] = n;
        for (int i = 0; i < n; ++i) {
            dp[i][i] = 1;
            for (int left = i - 1, right = i + 1; left >= 0 && right < n && s[left] == s[right]; --left, ++right) dp[left][right] = 1;
            for (int left = i, right = i + 1; left >= 0 && right < n && s[left] == s[right]; --left, ++right) dp[left][right] = 1;
        }
        for (int d = 2; d <= n; ++d) {
            int half = d / 2;
            for (int left =  n - d; left >= 0; --left) {
                int right = left + d - 1;
                if (dp[left][right] == 0) continue;
                dp[left][right] = Math.max(dp[left][right], Math.min(dp[left][left + half - 1], dp[right - half + 1][right]) + 1);
                ++ans[dp[left][right]];
            }
        }
        for (int i = n - 1; i > 0; --i) ans[i] += ans[i + 1];
        for (int i = 1; i <= n; ++i) out.print(ans[i] + " ");
        out.close();
    }
}

/** Class for buffered reading int and double values */
class Reader {
    static BufferedReader reader;
    static StringTokenizer tokenizer;

    /** call this method to initialize reader for InputStream */
    static void init(InputStream input) {
        reader = new BufferedReader(
            new InputStreamReader(input) );
        tokenizer = new StringTokenizer("");
    }

    /** get next word */
    static String next() throws IOException {
        while ( ! tokenizer.hasMoreTokens() ) {
            //TODO add check for eof if necessary
            tokenizer = new StringTokenizer(
                reader.readLine() );
        }
        return tokenizer.nextToken();
    }

    static int nextInt() throws IOException {
        return Integer.parseInt( next() );
    }

    static double nextDouble() throws IOException {
        return Double.parseDouble( next() );
    }
}