#include <cstdio>
#include <cstring>
#define M 203
inline int geti() {
    register int a; register char c;
    while(c=getchar(),c<'-');a=c-'0';
    while(c=getchar(),'-'<c)a=(a<<3)+(a<<1)+c-'0';
    return a;
}
inline void cmin(int &a,int b) {b<a?a=b:1;}
int d[M][M],a[1005],dp[2][M][M],(*f)[M]=dp[0],(*g)[M]=dp[1],(*t)[M];
int main() {
    register int i,j,k,n=0,m=geti()+1,siz=sizeof dp[0],*x=a,p;
    for(i=1;i<m;++i) for(j=1;j<m;d[i][j++]=geti());
    while(scanf("%d",a+n)^EOF)++n;
    memset(f,63,siz);
    f[1][2]=d[3][*x];
    f[1][3]=d[2][*x];
    f[2][3]=d[1][*x];
    for(i=1;i<n;++i) {
        t=f,f=g,g=t; p=*x++;
        memset(f,63,siz);
        for(j=1;j<m;++j)
            for(k=j;k<m;++k) {
                cmin(f[j][k],g[j][k]+d[p][*x]);
                f[k][j]=f[j][k];
                cmin(f[j][p],g[j][k]+d[k][*x]);
                f[p][j]=f[j][p];
                cmin(f[p][k],g[j][k]+d[j][*x]);
                f[k][p]=f[p][k];
            }
    }
    i=0x3f3f3f3f;
    for(j=1;j<m;++j) for(k=j,x=f[j]+j;k<m;++k,++x) *x<i?i=*x:1;
    return printf("%d\n",i),0;
}
