import java.math.*;
import java.util.*;

public class Main {
    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);
        BigInteger x,y,a,b;
        while(in.hasNextBigInteger()){
            x=in.nextBigInteger();
            a=in.nextBigInteger();
            y=in.nextBigInteger();
            b=in.nextBigInteger();
            int t = x.multiply(b).compareTo(y.multiply(a));
            if(t<0){
                System.out.println("<");
            }else if(t==0){
                System.out.println("=");
            }else {
                System.out.println(">");
            }
        }
    }
}
