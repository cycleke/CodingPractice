#include <cstdio>
int n,m,idx,t[5002];
double dp[2][5002],p[5002];
int main() {
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;++i)
		scanf("%lf%d",p+i,t+i);
	for(int i=n;i;--i) {
		double pw=1,tmp=0;
		p[i]/=100;
		for(int j=1;j<t[i];++j)pw*=1-p[i];
		for(int j=m-1;~j;--j) {
			tmp=(1-p[i])*tmp+p[i]*(1+dp[idx][j+1]);
			if(j+t[i]<=m)
				dp[idx^1][j]=(tmp-=pw*p[i]*(1+dp[idx][j+t[i]]))+pw*(1+dp[idx][j+t[i]]);
			else dp[idx^1][j]=tmp;
		}
		idx^=1;
	}
	printf("%.9lf",dp[idx][0]);
	return 0;
}
