import java.io.*;
import java.util.*;
import java.math.*;
import java.lang.*;

public class C {

    private static Reader in;
    private static PrintWriter out;

    private static int n;
    private static int[] upper, lower, f;

    public static void main(String[] args) throws IOException {
        in = new Reader(System.in);
        out = new PrintWriter(System.out);

        upper = new int[20];
        lower = new int[20];
        int l1 = to_digit(in.nextLong(), lower);
        int l2 = to_digit(in.nextLong(), upper);

        n = l2;
        f = new int[20];
        out.println( dfs(0, n) );

        out.close();
    }

    private static int to_digit(long x, int[] a) {
        int n = 0;
        while (x != 0) {
            ++n;
            a[n] = (int) (x % 10);
            x /= 10;
        }
        return n;
    }

    private static int dfs(int step, int range) {
        if (step == 9) {
            f[step] = range;
            /*
              for (int i = n; i > 0; --i)
              out.print(f[i] + " ");
              out.println();
            */
            return check(n, true, true) ? 1 : 0;
        }
        int res = 0;
        for (int i = 0; i <= range; ++i) {
            f[step] = i;
            res += dfs(step + 1, range - i);
        }
        return res;
    }

    private static boolean check(int step, boolean left_flag, boolean right_flag) {
        if (step == 0) return true;
        if (!left_flag && !right_flag) return true;

        //out.println(step + " " + left_flag + " " + right_flag);

        int left = left_flag ? lower[step] : 0;
        int right = right_flag ? upper[step] : 9;

        //out.println(step + " " + left + " " + right);
        for (int i = left; i <= right; ++i)
            if (f[i] != 0) {
                --f[i];
                boolean res = check(step - 1, left_flag && i == left, right_flag && i == right);
                ++f[i];
                if (res) return true;
            }
        return false;
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

    static long nextLong() throws IOException {
        return Long.parseLong( next() );
    }

}