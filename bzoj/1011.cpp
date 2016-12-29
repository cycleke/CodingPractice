#include <cmath>
#include <cstdio>
inline int geti() {
    register int a; register char c;
    while(c=getchar(),c<'0');a=c-'0';
    while(c=getchar(),'-'<c)a=(a<<3)+(a<<1)+c-'0';
    return a;
}
#define N 100002
#define t 20
int m[N]; double f[N];
int main() {
    register int i,j,l,r,n=geti();
    double a; scanf("%lf",&a);
    for(i=1;i<=n;++i)m[i]=geti(),f[i]=0.0;
    for(i=1;i<=t;++i)
        for(j=1,r=floor(a*i);j<=r;++j)
            f[i]+=1.0*m[i]*m[j]/(i-j);
    for(i=t+1;i<=n;++i) {
        l=floor(a*(i-t)),r=floor(a*i);
        for(j=l+1;j<=r;++j) f[i]+=1.0*m[i]*m[j]/(i-j);
        f[i]+=m[i]*f[i-t]/m[i-t]*(i-t-1.0*l/2)/(i-1.0*l/2);
    }
    for(i=1;i<=n;++i) printf("%.6lf\n",f[i]);
    return 0;
}
