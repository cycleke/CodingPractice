#include <cstdio>
#include <cstring>
#define max(a,b) ((a)<(b)?(b):(a))
#define min(a,b) ((a)<(b)?(a):(b))
#define N 105
int dp[2][N],n,m,d1[N],d2[N];
bool check(int tim) {
	int i,j,k,t,en;
	memset(dp,-1,sizeof dp); dp[1][0]=0;
	for(i=0;i<n;++i)
		for(j=0;j<=m;++j)
			for(k=0,en=min(tim/d1[i],j);k<=en;++k)
				if(~dp[~i&1][j-k]) {
					t=(tim-k*d1[i])/d2[i];
					dp[i&1][j]=max(dp[i&1][j],dp[~i&1][j-k]+t);
				}
	return dp[~n&1][m]>=m;
}
int main() {
	freopen("time.in","r",stdin); freopen("time.out","w",stdout);
	int i,j,l,r,mid,ans;
	scanf("%d%d",&n,&m);
	for(i=0;i<n;++i) scanf("%d%d",d1+i,d2+i);
	for(l=0,r=2000;l<=r;) {
		if(check(mid=l+r>>1)) r=(ans=mid)-1;
		else l=mid+1;
	}return printf("%d",ans),0;
}
