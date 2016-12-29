#include <cstdio>
int ans[505];
bool dp[505][505];
int main() {
	int i,j,n,k,cnt=0,c;
	dp[0][0]=true;
	for(scanf("%d%d",&n,&k);n;--n) {
		scanf("%d",&c);
		for(i=k;~i;--i)
		  for(j=i;~j;--j) {
			  (i>=c)?dp[i][j]|=dp[i-c][j]:true;
			  (j>=c)?dp[i][j]|=dp[i-c][j-c]:true;
		  }
	}
	for(i=0;i<=k;++i)
	  (dp[k][i])?ans[cnt++]=i:1;
	for(printf("%d\n",cnt),i=0;i<cnt;++i)
	  printf("%d ",ans[i]);
	return 0;
}
