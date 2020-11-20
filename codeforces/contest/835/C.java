import java.io.*;
import java.util.*;
import java.math.*;
import java.lang.*;

public class C {

    private static Reader in;
    private static PrintWriter out;

    public static void main(String[] args) throws IOException {
        in = new Reader();
        in.init(System.in);
        out = new PrintWriter(System.out);
        int n = in.nextInt(), q = in.nextInt(), c = in.nextInt() + 1;
        int[][][] sum = new int [c][101][101];
        for (int i = 0; i < n; ++i) {
            int x = in.nextInt();
            int y = in.nextInt();
            int z = in.nextInt();
            for (int j = 0; j < c; ++j)
                sum[j][x][y] += (z + j) % c;
        }
        for (int k = 0; k < c; ++k)
            for (int i = 1; i < 101; ++i)
                for (int j = 1; j < 101; ++j)
                    sum[k][i][j] += sum[k][i - 1][j] + sum[k][i][j - 1] - sum[k][i - 1][j - 1];
        for (int step = 0; step < q; ++step) {
            int s = in.nextInt() % c;
            int x1 = in.nextInt();
            int y1 = in.nextInt();
            int x2 = in.nextInt();
            int y2 = in.nextInt();
            int ans = sum[s][x2][y2] - sum[s][x1 - 1][y2] - sum[s][x2][y1 - 1] + sum[s][x1 - 1][y1 - 1];
            out.println(ans);
        }
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