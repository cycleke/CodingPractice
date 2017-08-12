import java.io.*;
import java.util.*;
import java.lang.*;
import java.math.*;

public class C {

     private static Reader in;
     private static PrintWriter out;
     public static void main(String[] args) throws Exception {
          in = new Reader( System.in );
          out = new PrintWriter( System.out );

          TaskSolution solver = new TaskSolution();
          solver.solve(in, out);

          out.close();
     }

     static class TaskSolution {

          public void solve(Reader in, PrintWriter out) throws Exception {
               int rows = in.nextInt();
               int cols = in.nextInt();
               int[][] h = new int[rows][cols];
               int[] maxRow = new int[rows];
               int[] maxCol = new int[cols];
               for (int i = 0; i < rows; ++i)
                    for (int j = 0; j < cols; ++j) {
                         h[i][j] = in.nextInt();
                         maxRow[i] = Math.max(maxRow[i], h[i][j]);
                         maxCol[j] = Math.max(maxCol[j], h[i][j]);
                    }
               int usedCells = 0;
               long res = 0;
               for (int i = 0; i < rows; ++i)
                    for (int j = 0; j < cols; ++j) {
                         res += h[i][j];
                         if (h[i][j] > 0) ++usedCells;
                    }
               int[] vals = new int[rows + cols];
               System.arraycopy(maxRow, 0, vals, 0, rows);
               System.arraycopy(maxCol, 0, vals, rows, cols);
               Arrays.sort(vals);
               int[] curR = new int[rows];
               int[] curC = new int[cols];
               for (int i = 0; i < vals.length; ++i) {
                    if (vals[i] == 0 || i > 0 && vals[i] == vals[i - 1]) continue;
                    int nr = 0;
                    int nc = 0;
                    for (int r = 0; r < rows; ++r)
                         if (maxRow[r] == vals[i])
                              curR[nr++] = r;
                    for (int c = 0; c < cols; ++c)
                         if (maxCol[c] == vals[i])
                              curC[nc++] = c;
                    boolean[][] g = new boolean[nr][nc];
                    for (int a = 0; a < nr; ++a)
                         for (int b = 0; b < nc; ++b)
                              g[a][b] = h[curR[a]][curC[b]] > 0;
                    int use = nr + nc - maxMatching(g, nr, nc);
                    usedCells -= use;
                    res -= use * (long) vals[i];
               }
               res -= usedCells;
               out.println(res);
          }

          private int maxMatching(boolean[][] g, int nr, int nc) {
               int res = 0;
               int[] match = new int[nc];
               Arrays.fill(match, -1);
               boolean[] mark = new boolean[nr];
               for (int i = 0; i < nr; ++i) {
                    if (dfs(i, g, match, mark)) {
                         ++res;
                         Arrays.fill(mark, false);
                    }
               }
               return res;
          }

          private boolean dfs(int at, boolean[][] g, int[] match, boolean[] mark) {
               mark[at] = true;
               for (int i = 0; i < match.length; ++i)
                    if (match[i] < 0 && g[at][i]) {
                         match[i] = at;
                         return true;
                    }
               for (int i = 0; i < match.length; ++i)
                    if (g[at][i] && !mark[match[i]]) {
                         if (dfs(match[i], g, match, mark)) {
                              match[i] = at;
                              return true;
                         }
                    }
               return false;
          }

     }

}

class Reader {

     static BufferedReader reader;
     static StringTokenizer tokenizer;

     Reader(InputStream input) {
          reader = new BufferedReader ( new InputStreamReader(input) );
          tokenizer = new StringTokenizer("");
     }

     static String next() throws Exception {
          while (!tokenizer.hasMoreTokens())
               tokenizer = new StringTokenizer(reader.readLine());
          return tokenizer.nextToken();
     }

     static int nextInt() throws Exception {
          return Integer.parseInt( next() );
     }

     static double nextDouble() throws Exception {
          return Double.parseDouble( next() );
     }

     static long nextLong() throws Exception {
          return Long.parseLong( next() );
     }

}
