import java.io.*;
import java.util.*;
import java.math.*;
import java.lang.*;

public class A {

    private static Reader in;

    public static void main(String[] args) throws IOException {
        in = new Reader();
        in.init(System.in);
        int s = in.nextInt();
        int v1 = in.nextInt(), v2 = in.nextInt();
        int t1 = in.nextInt(), t2 = in.nextInt();
        int cost1 = s * v1 + t1 * 2;
        int cost2 = s * v2 + t2 * 2;
        if (cost1 < cost2) System.out.println("First");
        else if (cost1 > cost2) System.out.println("Second");
        else System.out.println("Friendship");
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