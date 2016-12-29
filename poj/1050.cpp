#include <cstdio>
#define N 105
int ina; char inc,insign;
inline int geti() {
	for(insign=false;(inc=getchar())<'0'||inc>'9';)insign|=inc=='-';
	for(ina=inc-'0';(inc=getchar())>='0'&&inc<='9';ina=(ina<<3)+(ina<<1)+inc-'0');
	return insign?-ina:ina;
}
int arry[N][N],dp[N][N],n;
#define max(a,b) ((a)<(b)?(b):(a))
int main() {
	int i,j,k,t,mx=-0x7f7f7f7f;
	for(n=geti(),i=1;i<=n;++i)
		for(j=1;j<=n;++j)
			arry[i][j]=geti();
	for(i=1;i<=n;++i)
		for(j=1;j<=n;++j) {
			for(k=j,t=0;k<=n;++k) {
				t+=arry[i][k];
				dp[j][k]=max(dp[j][k]+t,t);
				mx=max(mx,dp[j][k]);
			}
		}
	return printf("%d",mx),0;
}
