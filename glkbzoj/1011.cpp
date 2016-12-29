#include <cmath>
#include <cstdio>
#define N 100005
#define eps 1e-9
#define t 100
double a,f[N];
int m[N],n;
int main() {
  int i,j,k,l,r;
  for(scanf("%d%lf",&n,&a),i=1;i<=n;++i) scanf("%d",m+i);
  for(i=1;i<101;++i) {
    for(j=1,f[i]=0.0,r=(int)(eps+floor(a*i));j<=r;++j)
      f[i]+=1.0*m[i]*m[j]/(i-j);
  }
  for(i=101;i<=n;++i) {
    l=(int)(eps+floor(a*(i-t))),r=(int)(eps+floor(a*i));
    for(f[i]=0.0,j=l+1;j<=r;++j) f[i]+=1.0*m[i]*m[j]/(i-j);
    f[i]+=1.0*m[i]*(f[i-t]/m[i-t]*(i-t-1.0*l/2)/(i-1.0*l/2));
  }
  for(i=1;i<=n;++i) printf("%.6lf\n",f[i]); return 0;
}
