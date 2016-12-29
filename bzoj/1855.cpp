#include <cstdio>
#include <cstring>
inline int gi() {
	register int a; register char c;
	while(c=getchar(),c<'0');a=c-'0';
	while(c=getchar(),'-'<c)a=(a<<3)+(a<<1)+c-'0';
	return a;
}
#define N 2005
int ap,bp,as,bs,dp[N][N],q[N];
inline void cmax(int&a,const int&b){if(a<b)a=b;}
/*
  I:nothing
  dp[i][j]=dp[i-1][j]
  II:selling
  dp[i][j]=max{dp[i-w-1][k]+(k-j)*bp[i]|k<=max(j+bs[i],mp)}
  III:buying
  dp[i][j]=max{dp[i-w-1][k]-(j-k)*ap[i]|k>=j-as[i]}
 */
int main() {
	int n=gi(),mp=gi(),w=gi();
	register int i,j,*l,*r;
	memset(dp,-63,sizeof dp);
	dp[0][0]=0;
	for(i=1;i<=n;++i) {
		ap=gi(),bp=gi(),as=gi(),bs=gi();
		for(j=0;j<=as;++j)dp[i][j]=-j*ap;
		for(j=0;j<=mp;++j)cmax(dp[i][j],dp[i-1][j]);
		if(w<i) {
			l=r=q;
			for(j=mp;~j;--j) {
				while(l<r&&*l>j+bs)++l;
				while(l<r&&dp[i-w-1][j]+j*bp>=dp[i-w-1][*(r-1)]+*(r-1)*bp)--r;
				*r++=j;cmax(dp[i][j],dp[i-w-1][*l]+(*l-j)*bp);
			}
			l=r=q;
			for(j=0;j<=mp;++j) {
				while(l<r&&*l<j-as)++l;
				while(l<r&&dp[i-w-1][j]+j*ap>=dp[i-w-1][*(r-1)]+*(r-1)*ap)--r;
				*r++=j;cmax(dp[i][j],dp[i-w-1][*l]-(j-*l)*ap);
			}
		}
	}
	int ans=0;
	for(i=0;i<=mp;++i)cmax(ans,dp[n][i]);
	printf("%d\n",ans);
	return 0;
}
