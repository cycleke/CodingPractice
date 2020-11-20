import java.io.*;
import java.util.*;
import java.math.*;
import java.lang.*;

public class E {

    private static Reader in;

    private static int[] a;
    private static int n, x, y;

    public static void main(String[] args) throws IOException {
        in = new Reader(System.in);

        n = in.nextInt();
        x = in.nextInt();
        y = in.nextInt();
        int xy = 0;
        a = new int[1030];
        for (int i = 9; i >= 0; --i)
            if (rec(i, -1)) xy |= 1 << i;

        for (int i = 9; i >= 0; --i)
            if (((xy >> i) & 1) != 0) {
                int xx = 0;
                for (int j = 9; j >= 0; --j)
                    if (j != i && rec(j, i)) xx |= 1 << j;
                xy ^= xx;
                if (xx > xy) {
                    xx ^= xy;
                    xy ^= xx;
                    xx ^= xy;
                }
                System.out.println("! " + (xx + 1) + " " + (xy + 1));
                System.out.flush();
                return;
            }
    }

    private static boolean rec(int p, int f) throws IOException {
        int ans = 0;
        a[0] = 0;
        for (int i = 0; i < 1024; ++i)
            if ((((i >> p) & 1) != 0) && ((f == -1) || (((i >> f) & 1) == 0)))
                if (i + 1 <= n) {
                    ++a[0];
                    a[a[0]] = i + 1;
                } else ans ^= x;

        if (a[0] > 0) {
            System.out.print("? " + a[0]);
            for (int i = 1; i <= a[0]; ++i)
                System.out.print(" " + a[i]);
            System.out.println();
            System.out.flush();
            int temp = in.nextInt();
            if (temp == -1) throw new RuntimeException();
            ans ^= temp;
        }

        return ans != 0;
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