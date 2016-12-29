#include <cstdio>
#include <cstring>
inline int geti() {
    register int a; register char c,f=0;
    while(c=getchar(),c<'0')f|=c=='-';a=c-'0';
    while(c=getchar(),'-'<c)a=(a<<3)+(a<<1)+c-'0';
    return f?-a:a;
}
#define max(a,b) (a<b?b:a)
double dp[2][1<<15];
int w[15],s[15];
int main() {
    register int k=geti(),n=geti(),i,j,idx=0,en=1<<n;
    for(i=0;i^n;++i) {
        w[i]=geti();
        for(j=geti();j;j=geti())s[i]|=1<<j-1;
    }
    while(k--)
        for(idx^=1,memset(dp[idx],0,sizeof dp[idx]),j=0;j^en;++j) {
            for(i=0;i^n;++i)
                if((j&s[i])^s[i])
                    dp[idx][j]+=dp[idx^1][j];
                else dp[idx][j]+=max(dp[idx^1][j],dp[idx^1][j|(1<<i)]+w[i]);
            dp[idx][j]/=n;
        }
    printf("%.6lf\n",dp[idx][0]);
    return 0;
}
