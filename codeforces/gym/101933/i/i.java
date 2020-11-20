// by cnissnzg
import java.math.*;
import java.util.*;

public class i {
  static class dat{
    public String name;
    public BigInteger b;
  }
  static dat[] dats = new dat[1050];
  static String[] names = new String[1050];
  public static void main(String[] args) {
    Scanner in = new Scanner(System.in);
    int n;
    BigInteger s;
    n=in.nextInt();
    s=in.nextBigInteger();
    for(int i = 0;i < n;i++){
      dats[i] = new dat();
      dats[i].name = in.next();
      dats[i].b = in.nextBigInteger();
    }
    Arrays.sort(dats,0,n, new Comparator<dat>() {
      @Override
      public int compare(dat o1, dat o2) {
        return o1.b.compareTo(o2.b);
      }
    });
    int ans = 0;
    for(int i = n-1;i>=0;i--){
      if(dats[i].b.compareTo(s)<=0){
        ans++;
        s=s.subtract(dats[i].b);
        names[ans] = dats[i].name;
      }
    }
    if(s.compareTo(BigInteger.ZERO)==0){
      System.out.println(ans);
      for(int j = 1;j <= ans;j++){
        System.out.println(names[j]);
      }
    }else{
      System.out.println(0);
    }
  }
}
