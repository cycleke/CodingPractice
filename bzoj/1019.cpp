#include <cstdio>
char vis[3],g[3][32];
long long f[3][32];
int main() {
    register char n,i,j,x,y;
    while(j=getchar(),j<'0');n=j-'0';
    while(j=getchar(),'-'<j)n=(n<<3)+(n<<1)+j-'0';
    for(i=0;i^6;++i) {
        while(j=getchar(),j<'A');
        x=j-'A',y=getchar()-'A';
        if(!vis[x])vis[x]=1,g[x][1]=y,f[x][1]=1LL;
    }
    for(i=2;i<=n;++i)
        for(j=0;j^3;++j) {
            y=g[j][i-1],x=3-y-j;
            if(x^g[y][i-1])
                f[j][i]=(f[j][i-1]<<1)+f[y][i-1]+2,g[j][i]=y;
            else
                f[j][i]=f[j][i-1]+f[y][i-1]+1,g[j][i]=x;
        }
    printf("%lld",f[0][n]);
    return 0;
}
