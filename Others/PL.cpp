#include <cstdio>
#include <cstring>
#define mod 1000000007
#define N 1005
int dp[N][N],n,sum[N],ans;
char ts[N];
int main() {
	while(scanf("%s",ts+1)^EOF){
		n=strlen(ts+1)+1;
		dp[1][1]=1;
		for(int i=2;i<=n;++i) {
			for(int j=1;j<i;++j)
				sum[j]=(sum[j-1]+dp[i-1][j])%mod;
			for(int j=1;j<=i;++j)
				if(ts[i-1]=='I') dp[i][j]=sum[j-1];	
				else if(ts[i-1]=='D') dp[i][j]=sum[i-1]-sum[j-1];
				else dp[i][j]=sum[i-1];
			for(int j=1;j<=i;++j)
				dp[i][j]=(dp[i][j]%mod+mod)%mod;
		}
		ans=0;
		for(int i=1;i<=n;++i) ans=(ans+dp[n][i])%mod;
		printf("%d\n",ans);
	}
	return 0;
}
