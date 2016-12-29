#include <cstdio>
#include <cstring>
inline int geti() {
	register int a; register char c;
	while(c=getchar(),c<'0');a=c-'0';
	while(c=getchar(),'-'<c)a=(a<<3)+(a<<1)+c-'0';
	return a;
}
int dp[22][22][22],change[100][61],vis[61],vis_clock,d[61];
int sr,sb,sg,n,p;
#define inc(a,b) for((a)+=(b);(a)>=p;(a)-=p)
inline int Cal(int*a) {
	memset(dp,0,sizeof dp);
	register int s=0,i,j,k,t;
	++vis_clock;
	for(i=1;i<=n;++i)
		if(vis[i]^vis_clock) {
			d[s]=0;
			for(j=i;vis[j]^vis_clock;j=a[j])
				vis[j]=vis_clock,++d[s];
			++s;
		}
	dp[0][0][0]=1;
	for(--s;~s;--s)
		for(t=d[s],i=sr;~i;--i)
			for(j=sb;~j;--j)
				for(k=sg;~k;--k) {
					if(i>=t) inc(dp[i][j][k],dp[i-t][j][k]);
					if(j>=t) inc(dp[i][j][k],dp[i][j-t][k]);
					if(k>=t) inc(dp[i][j][k],dp[i][j][k-t]);
				}
	return dp[sr][sb][sg];
}
int main() {
	sr=geti(),sb=geti(),sg=geti();
	register int m=geti(),i,j; p=geti();
	n=sr+sb+sg;
	for(i=0;i<m;++i) for(j=1;j<=n;++j) change[i][j]=geti();
	for(i=1;i<=n;++i) change[m][i]=i;
	++m;
	int ans=0;
	for(i=0;i<m;++i)
		for(ans+=Cal(change[i]);ans>=p;ans-=p);
	for(i=m,j=p-2;j;j>>=1,i=i*i%p)if(j&1)ans=ans*i%p;
	printf("%d\n",ans);
	return 0;
}
