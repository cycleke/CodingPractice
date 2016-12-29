#include <cstdio>
int dp[33],n;
int main() {
	dp[1]=2,dp[2]=4,dp[3]=7;
	for(n=4;n<33;++n) dp[n]=dp[n-1]+dp[n-2]+dp[n-3];
	while(scanf("%d",&n)!=EOF&&n) printf("%d\n",(1<<n)-dp[n]);
	return 0;
}
