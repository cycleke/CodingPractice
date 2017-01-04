#include <cstdio>
#include <cstring>
double dp[4][4004],p[4][4004];
int main() {
	int _,a,b,n;
	scanf("%d",&_);
	while(_--) {
		scanf("%d%d%d",&n,&a,&b);
		for(int i=1;i<=n;++i)
			for(int j=0;j<4;++j)
				scanf("%lf",p[j]+i);
		for(int i=n+1;i<=n+a;++i)
			for(int j=0;j<4;++j)
				p[j][i]=j==3;
		memset(dp,0,sizeof dp);
		dp[3][0]=1;
		for(int i=0;i<=n;++i) {
			double p1=1,p2=1,p3=1;
			for(int j=a;j<=b;++j) {
				dp[2][i+j]+=dp[1][i]*p1*p[2][i+j];
				dp[3][i+j]+=dp[1][i]*p1*p[3][i+j];
				p1*=p[0][i+j]+p[1][i+j];
				dp[1][i+j]+=dp[2][i]*p2*p[1][i+j];
				dp[3][i+j]+=dp[2][i]*p2*p[3][i+j];
				p2*=p[0][i+j]+p[2][i+j];
				dp[1][i+j]+=dp[3][i]*p3*p[1][i+j];
				dp[2][i+j]+=dp[3][i]*p3*p[2][i+j];
				dp[3][i+j]+=dp[3][i]*p3*p[3][i+j];
				p3*=p[0][i+j];
			}
		}
		double ans=0;
		for(int i=0;i<4;++i)
			for(int j=1;j<=n+a;++j)
				ans+=dp[i][j];
		printf("%.8lf\n",ans);
	}
	return 0;
}
