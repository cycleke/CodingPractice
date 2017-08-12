import java.io.OutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.PrintWriter;
import java.util.Scanner;

public class K {
    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);
        PrintWriter out = new PrintWriter(System.out);
        int x = in.nextInt();
        out.println(((x & 1) == 1) ? "Alice" : "Bob");
        in.close();
        out.close();
    }
}