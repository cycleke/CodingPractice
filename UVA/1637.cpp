#include <cstdio>
#include <cstring>
double dp[1953200];
char vis[1953200],card[9][5][3];
double dfs(int sta) {
	if(sta==0) return 1.;
	if(vis[sta]) return dp[sta];
	vis[sta]=1; int a[10],i,j,cnt=0,t,k;
	double tot=0.;
	for(i=0,j=sta;i<9;++i) {
		a[i]=j%5; j/=5;
	}
	for(i=0;i<9;++i)
	  for(j=i+1;j<9;++j)
		if(a[i]&&a[j]&&card[i][a[i]][0]==card[j][a[j]][0]) {
			for(k=8,t=0;~k;--k)
			  (k==i||k==j)?(t=t*5+a[k]-1):(t=t*5+a[k]);
			tot+=dfs(t); ++cnt;
		}
	if(cnt) tot=tot/cnt;
	return dp[sta]=tot;
}
int main() {
	int i,j;
	while(scanf("%s",card[0][1])^EOF) {
		for(i=2;i<5;++i) scanf("%s",card[0][i]);
		for(i=1;i<9;++i)
		  for(j=1;j<5;++j)
			scanf("%s",card[i][j]);
		memset(vis,0,sizeof vis);
		printf("%.6lf\n",dfs(1953124));
	}
	return 0;
}
