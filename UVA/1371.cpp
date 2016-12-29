#include <cstdio>
#include <cstring>

int dp[5005][55],n,m;
char x[5005],y[55];

inline int min(int a,int b) {return a<b?a:b;}
inline void cmin(int &a,int b) {b<a?a=b:1;}
bool check(int v) {
	memset(dp,63,sizeof dp);
	dp[0][0]=0;
	for (int i=0;i<=n;++i) {
		if (dp[i][m]<=v)
		  dp[i][0] = 0;
		for (int j=0;j<=m;++j)
		  if(dp[i][j]<=v) {
			cmin(dp[i+1][j+1],dp[i][j]+(x[i+1]!=y[j+1]));
			cmin(dp[i][j+1],dp[i][j]+1);
			cmin(dp[i+1][j],dp[i][j]+1);
		  }
	}
	return dp[n][m]<=v;
} 

int main() {
	int T,l,r,ans,mid; scanf("%d",&T);
	while (T--) {
		scanf("%s%s",y+1,x+1);
		n=strlen(x+1); m=strlen(y+1);
		l=0,ans=r=m;
		while(l<=r) {
			mid=l+r>>1;
			if(check(mid)) r=(ans=mid)-1;
			else l=mid+1;
		}
		printf("%d\n",ans);
	}
	return 0;
}
