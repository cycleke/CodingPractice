import java.io.*;
import java.util.*;
import java.math.*;
import java.lang.*;

public class A {

    private static Reader in;
    private static PrintWriter out;

    public static void main(String[] args) throws IOException {
        in = new Reader(System.in);
        out = new PrintWriter(System.out);

        int n = in.nextInt();
        for (int round = 0; round < n; ++round) {
            long a = in.nextInt();
            long b = in.nextInt();
            long cbrt = (long) Math.cbrt(a * b);
            out.println( (cbrt * cbrt * cbrt == a * b && a % cbrt == 0 && b % cbrt == 0) ? "Yes" : "No" );
        }

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