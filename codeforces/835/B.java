import java.io.*;
import java.util.*;
import java.math.*;
import java.lang.*;

public class B {

    private static Reader in;

    public static void main(String[] args) throws IOException {
        in = new Reader();
        in.init(System.in);
        int k = in.nextInt();
        char[] s = in.next().toCharArray();
        int sum = 0;
        for (char c : s) sum += c - '0';
        if (sum >= k) {
            System.out.println("0");
            return;
        }
        int[] cnt = new int[10];
        for (char c : s) ++cnt[c - '0'];

        int ans = 0;
        int res = k - sum;
        for (int i = 0; i < 9; ++i)
            if (cnt[i] > 0) {
                if ((9 - i) * cnt[i] >= res) {
                    int temp = res / (9 - i);
                    if (temp * (9 - i) < res) ++temp;
                    ans += temp;
                    break;
                } else {
                    ans += cnt[i];
                    res -= (9 - i) * cnt[i];
                }
            }
        System.out.println(ans);
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