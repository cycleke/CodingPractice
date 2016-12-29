#include <cstdio>
#include <cstring>
inline int geti() {
    register int a; register char c,f=0;
    while(c=getchar(),c<'0')f|=c=='-';a=c-'0';
    while(c=getchar(),'-'<c)a=(a<<3)+(a<<1)+c-'0';
    return f?-a:a;
}
inline double max(double a,double b){return a<b?b:a;}
int s[15],w[15];
double dp[2][1<<15];
int main() {
    register int k=geti(),n=geti(),i,j,en=1<<n,d=0;
    for(i=0;i^n;++i) {
        w[i]=geti();
        while(j=geti())s[i]|=1<<j-1;
    }
    while(k--)
        for(d^=1,memset(dp[d],0,sizeof dp[d]),j=0;j^en;++j) {
            for(i=0;i^n;++i)
                if((j&s[i])^s[i]) dp[d][j]+=dp[d^1][j];
                else dp[d][j]+=max(dp[d^1][j],dp[d^1][j|(1<<i)]+w[i]);
            dp[d][j]/=n;
        }
    printf("%.6lf\n",*dp[d]);
    return 0;
}
