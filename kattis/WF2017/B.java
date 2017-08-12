import java.io.*;
import java.util.*;
import java.lang.*;

class FastReader {
    static BufferedReader reader;
    static StringTokenizer tokenizer;

    static void init(InputStream input) {
        reader = new BufferedReader(new InputStreamReader(input));
        tokenizer = new StringTokenizer("");
    }

    static String next() throws IOException {
        while (!tokenizer.hasMoreTokens()) tokenizer = new StringTokenizer(reader.readLine());
        return tokenizer.nextToken();
    }

    static int nextInt() throws IOException {
        return Integer.parseInt(next());
    }

    static double nextDouble() throws IOException {
        return Double.parseDouble(next());
    }

}

public class B {

    private static int[] who;
    private static int[] kind;
    private static int[] UnknownByKind;
    private static int[] FiveByKind;
    private static int[][] answers;
    private static int[][] suggestions;
    private static int[] remaining;
    private static boolean[] canBe;

    public static void main(String[] args) throws IOException {
        FastReader in = new FastReader();
        in.init(System.in);
        int n = in.nextInt();
        who = new int[21];
        kind = new int[21];
        canBe = new boolean[21];
        Arrays.fill(kind, 2);
        for (int i = 0; i < 6; ++i) kind[i] = 0;
        for (int i = 6; i < 12; ++i) kind[i] = 1;
        UnknownByKind = new int[3];
        for (int x : kind) ++UnknownByKind[x];
        FiveByKind = new int[3];
        for (int i = 0; i < 5; ++i) {
            int a = in.next().charAt(0) - 'A';
            who[a] = 1;
            --UnknownByKind[kind[a]];
        }
        answers = new int[n][];
        suggestions = new int[n][3];
        for (int step = 0; step < n; ++step) {
            for (int i = 0; i < 3; ++i)
                suggestions[step][i] = in.next().charAt(0) - 'A';
            int len = 0;
            int[] cur = new int[3];
            for (int i = 0; i < 3; ++i) {
                String a = in.next();
                ++len;
                if (a.equals("-")) {
                    cur[i] = -1;
                    continue;
                }
                cur[i] = a.equals("*") ? -2 : a.charAt(0) - 'A';
                break;
            }
            answers[step] = Arrays.copyOf(cur, len);
        }
        remaining = new int[]{0, 0, 5, 4, 4, 3};
        rec(0);
        char[] Result = new char[]{findOne(0, 6), findOne(6, 12), findOne(12, 21)};
        System.out.println(Result);
    }

    private static char findOne(int left, int right) {
        int r = -1;
        for (int i = left; i < right; ++i)
            if (canBe[i])
                r = (r == -1) ? i : -2;
        if (r == -1) throw new RuntimeException();
        return (r == -2) ? '?' : (char) ('A' + r);
    }

    private static void rec(int p) {
        if (p >= answers.length) {
            for (int i = 0; i < 21; ++i)
                if (who[i] == 5 || (who[i] == 0 && FiveByKind[kind[i]] == 0))
                    canBe[i] = true;
        } else {
            for (int i = 0; i < 3; ++i) {
                int x = suggestions[p][i];
                if (who[x] == 0) {
                    for (int u = 2; u < 6; ++u)
                        if (remaining[u] > 0) {
                            who[x] = u;
                            --remaining[u];
                            --UnknownByKind[kind[x]];
                            if (u == 5) ++FiveByKind[kind[x]];
                            if (FiveByKind[kind[x]] == 1 || (FiveByKind[kind[x]] == 0 && UnknownByKind[kind[x]] > 0))
                                rec(p);
                            who[x] = 0;
                            ++remaining[u];
                            ++UnknownByKind[kind[x]];
                            if (u == 5) --FiveByKind[kind[x]];
                        }
                    return;
                }
            }
            for (int i = 0; i < answers[p].length; ++i) {
                int w = (p + i + 1) % 4 + 1;
                int a = answers[p][i];
                if (a == -1) {
                    for (int x : suggestions[p])
                        if (who[x] == w) return;
                } else if (a == -2) {
                    boolean any = false;
                    for (int x : suggestions[p])
                        if (who[x] == w) {
                            any = true;
                            break;
                        }
                    if (!any) return;
                } else {
                    if (who[a] != w) return;
                }
            }
            rec(p + 1);
        }
    }
}