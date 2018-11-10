import java.io.*;
import java.util.*;
import java.math.*;

public class DigitStringDiv1 {
    public long count(String S, int X) {
        String T = String.valueOf(X);
        int n = S.length();
        long[][] f = new long[50][3];
        f[0][1] = 1;
        for (char c : S.toCharArray()) {
            for (int i = 48; i >= 0; i--) {
                if (i == 0 && c == '0')
                    continue;
                if (i >= T.length()) {
                    f[i + 1][0] += f[i][0] + f[i][1] + f[i][2];
                } else {
                    f[i + 1][0] += f[i][0];
                    if (T.charAt(i) < c) f[i + 1][0] += f[i][1];
                    if (T.charAt(i) == c) f[i + 1][1] += f[i][1];
                    if (T.charAt(i) > c) f[i + 1][2] += f[i][1];
                    f[i + 1][2] += f[i][2];
                }
            }
        }
        long result = 0;
        for (int i = T.length(); i < 50; i++)
            result += f[i][0];
        return result;
    }

    // CUT begin
    public static void main(String[] args){
        System.err.println("DigitStringDiv1 (250 Points)");
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

            String S = Reader.nextLine();
            int X = Integer.parseInt(Reader.nextLine());
            Reader.nextLine();
            long __answer = Long.parseLong(Reader.nextLine());

            cases++;
            if (caseSet.size() > 0 && !caseSet.contains(cases - 1))
                continue;
            System.err.print(String.format("  Testcase #%d ... ", cases - 1));

            if (doTest(S, X, __answer))
                passed++;
        }
        if (caseSet.size() > 0) cases = caseSet.size();
        System.err.println(String.format("%nPassed : %d/%d cases", passed, cases));

        int T = (int)(System.currentTimeMillis() / 1000) - 1541839061;
        double PT = T / 60.0, TT = 75.0;
        System.err.println(String.format("Time   : %d minutes %d secs%nScore  : %.2f points", T / 60, T % 60, 250 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT))));
    }

    static boolean doTest(String S, int X, long __expected) {
        S = new String(S);
        long startTime = System.currentTimeMillis();
        Throwable exception = null;
        DigitStringDiv1 instance = new DigitStringDiv1();
        long __result = 0;
        try {
            __result = instance.count(S, X);
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
        private static final String dataFileName = "DigitStringDiv1.sample";
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
