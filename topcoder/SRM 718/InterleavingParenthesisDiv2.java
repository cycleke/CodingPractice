import java.io.*;
import java.util.*;

public class InterleavingParenthesisDiv2 {
    final static int MOD = (int) (1e9 + 7);
	public int countWays(String s1, String s2) {
        int n = s1.length(), m = s2.length();
        int[] c1 = new int[n + 1];
        int[] c2 = new int[m + 1];
        for (int i = 0; i < n; ++i)
            c1[i + 1] = c1[i] + (s1.charAt(i) == '(' ? 1 : -1);
        for (int i = 0; i < m; ++i)
            c2[i + 1] = c2[i] + (s2.charAt(i) == '(' ? 1 : -1);
        int[][] c = new int[n + 1][m + 1];
        if (c1[n] + c2[m] != 0) return 0;
        c[0][0] = 1;
        for (int i = 0; i <= n; ++i) {
            for (int j = 0; j <= m; ++j) {
                if (c1[i] + c2[j] < 0) continue;
                c[i][j] = (c[i][j] + (i > 0 ? c[i - 1][j] : 0) + (j > 0 ? c[i][j - 1] : 0)) % MOD;
            }
        }
        return c[n][m];
	}

// CUT begin
	public static void main(String[] args){
		System.err.println("InterleavingParenthesisDiv2 (500 Points)");
		System.err.println();
		HashSet<Integer> cases = new HashSet<Integer>();
        for (int i = 0; i < args.length; ++i) cases.add(Integer.parseInt(args[i]));
        runTest(cases);
	}

	static void runTest(HashSet<Integer> caseSet) {
	    int cases = 0, passed = 0;
	    while (true) {
	    	String label = Reader.nextLine();
	    	if (label == null || !label.startsWith("--"))
	    		break;

            String s1 = Reader.nextLine();
            String s2 = Reader.nextLine();
            Reader.nextLine();
            int __answer = Integer.parseInt(Reader.nextLine());

            cases++;
            if (caseSet.size() > 0 && !caseSet.contains(cases - 1))
                continue;
    		System.err.print(String.format("  Testcase #%d ... ", cases - 1));

            if (doTest(s1, s2, __answer))
                passed++;
	    }
	    if (caseSet.size() > 0) cases = caseSet.size();
        System.err.println(String.format("%nPassed : %d/%d cases", passed, cases));

        int T = (int)(System.currentTimeMillis() / 1000) - 1502426749;
        double PT = T / 60.0, TT = 75.0;
        System.err.println(String.format("Time   : %d minutes %d secs%nScore  : %.2f points", T / 60, T % 60, 500 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT))));
	}

	static boolean doTest(String s1, String s2, int __expected) {
        s1 = new String(s1);
        s2 = new String(s2);
		long startTime = System.currentTimeMillis();
		Throwable exception = null;
		InterleavingParenthesisDiv2 instance = new InterleavingParenthesisDiv2();
		int __result = 0;
		try {
			__result = instance.countWays(s1, s2);
		}
		catch (Throwable e) { exception = e; }
		double elapsed = (System.currentTimeMillis() - startTime) / 1000.0;

		if (exception != null) {
			System.err.println("RUNTIME ERROR!");
			exception.printStackTrace();
			return false;
		}
		else if (__result == __expected) {
			System.err.println("PASSED! " + String.format("(%.2f seconds)", elapsed));
			return true;
		}
		else {
			System.err.println("FAILED! " + String.format("(%.2f seconds)", elapsed));
			System.err.println("           Expected: " + __expected);
			System.err.println("           Received: " + __result);
			return false;
		}
	}

	static class Reader {
        private static final String dataFileName = "InterleavingParenthesisDiv2.sample";
	    private static BufferedReader reader;

	    public static String nextLine() {
	        try {
                if (reader == null) {
                    reader = new BufferedReader(new InputStreamReader(new FileInputStream(dataFileName)));
                }
                return reader.readLine();
	        }
	        catch (IOException e) {
	            System.err.println("FATAL!! IOException");
	            e.printStackTrace();
	            System.exit(1);
	        }
	        return "";
	    }
	}
// CUT end
}
