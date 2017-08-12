import java.io.*;
import java.util.*;
import java.math.*;
import java.lang.*;

public class F {

    private static Reader in;
    private static PrintWriter out;

    private static long ans;
    private static Edge[] edge;
    private static int dfs_clock, cnt;
    private static int[] a, b, c, fa, pos;
    private static long[] f, u1, u2, v1, v2;
    private static boolean[] marked;

    public static void main(String[] args) throws IOException {
        in = new Reader(System.in);
        out = new PrintWriter(System.out);

        int n = in.nextInt();
        int Array_Size = n + 3;

        edge = new Edge[Array_Size];
        a = new int[Array_Size];
        b = new int[Array_Size];
        c = new int[Array_Size];
        fa = new int[Array_Size];
        pos = new int[Array_Size];
        f = new long[Array_Size];
        u1 = new long[Array_Size];
        u2 = new long[Array_Size];
        v1 = new long[Array_Size];
        v2 = new long[Array_Size];
        marked = new boolean[Array_Size];

        for (int i = 0; i < n; ++i) {
            int x = in.nextInt();
            int y = in.nextInt();
            int z = in.nextInt();
            new Edge(x, y, z);
            new Edge(y, x, z);
        }

        cnt = 0;
        ans = 0;
        dfs(1);
        for (int i = 1; i <= cnt; ++i) dp(a[i], 0);
        long sum = 0, mx = 0;
        for (int i = 1; i <= cnt; ++i) {
            sum += b[i - 1];
            u1[i] = Math.max(u1[i - 1], f[a[i]] + sum);
            v1[i] = Math.max(v1[i - 1], f[a[i]] + sum + mx);
            mx = Math.max(mx, f[a[i]] - sum);
        }
        long tmp = (long) b[cnt];
        mx = 0;
        sum = 0;
        b[cnt] = 0;
        for (int i = cnt; i > 0; --i) {
            sum += b[i];
            u2[i] = Math.max(u2[i + 1], f[a[i]] + sum);
            v2[i] = Math.max(v2[i + 1], f[a[i]] + sum + mx);
            mx = Math.max(mx, f[a[i]] - sum);
        }
        long mi = v1[cnt];
        for (int i = 1; i <= cnt; ++i)
            mi = Math.min(mi, Math.max(Math.max(v1[i], v2[i + 1]), u1[i] + u2[i + 1] + tmp));
        out.println(Math.max(ans, mi));
        out.close();
    }

    private static void dfs(int u) {
        ++dfs_clock;
        pos[u] = dfs_clock;
        for (Edge it = edge[u]; it != null; it = it.next) {
            int v = it.to;
            if (v == fa[u]) continue;
            if (pos[v] == 0) {
                fa[v] = u;
                c[v] = it.cost;
                dfs(v);
            } else if (pos[u] < pos[v]) {
                while (v != u) {
                    ++cnt;
                    marked[v] = true;
                    a[cnt] = v;
                    b[cnt] = c[v];
                    v = fa[v];
                }
                ++cnt;
                marked[u] = true;
                a[cnt] = u;
                b[cnt] = it.cost;
            }
        }
    }

    private static void dp(int u, int from) {
        for (Edge it = edge[u]; it != null; it = it.next) {
            int v = it.to;
            if (!marked[v] && v != from) {
                dp(v, u);
                ans = Math.max(ans, f[u] + f[v] + it.cost);
                f[u] = Math.max(f[u], f[v] + it.cost);
            }
        }
    }

    static class Edge {

        int to, cost;
        Edge next;

        Edge(int from, int to, int cost) {
            this.to = to;
            this.cost = cost;
            this.next = edge[from];
            edge[from] = this;
        }
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