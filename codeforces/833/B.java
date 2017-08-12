import java.io.*;
import java.util.*;
import java.math.*;
import java.lang.*;

public class Main {

    private static Reader in;
    private static PrintWriter out;

    private static int[][] dp, choice;
    private static int[] pre, pos, a, w;

    public static void main(String[] args) throws IOException {
        in = new Reader(System.in);
        out = new PrintWriter(System.out);

        int n = in.nextInt();
        int k = in.nextInt();
        a = new int[n + 1];
        w = new int[n + 1];
        pre = new int[n + 1];
        pos = new int[n + 1];
        dp = new int[n + 1][k + 1];
        choice = new int[n + 1][k + 2];

        for (int i = 1; i <= n; ++i){
            a[i] = in.nextInt();
            pre[i] = pos[a[i]];
            pos[a[i]] = i;
            choice[i][Math.min(i, k) + 1] = i - 1;
        }

        for (int i = 1; i <= n; ++i) {
            for (int j = pre[i] + 1; j <= i; ++j) ++w[j];
            dp[i][1] = w[1];
            for (int j = Math.min(i, k); j > 1; --j) {
                int ChosenPos = j - 1;
                for (int o = choice[i - 1][j]; o <= choice[i][j + 1]; ++o)
                    if (dp[o][j - 1] + w[o + 1] >= dp[ChosenPos][j - 1] + w[ChosenPos + 1])
                        ChosenPos = o;
                choice[i][j] = ChosenPos;
                dp[i][j] = dp[ChosenPos][j - 1] + w[ChosenPos + 1];
                //out.println(i + " " + j + " " + dp[i][j]);
            }
        }
        out.println(dp[n][k]);

        out.close();
    }

}

/** Class for buffered reading int and double values */
class Reader {
    static BufferedReader reader;
    static StringTokenizer tokenizer;

    Reader(InputStream input) {
        init(input);
    }

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