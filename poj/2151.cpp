#include <cstdio>

int n,t,m;
double dp[35];

int main() {
	while(scanf("%d%d%d",&m,&t,&n)!=EOF) {
		if(!m&&!t&&!n)break;
		double p1=1,tp,p=1;
		for(int i=1;i<=t;++i) {
			for(int j=1;j<=m;++j)dp[j]=0;
			dp[0]=1;
			for(int j=1;j<=m;++j) {
				scanf("%lf",&tp);
				for(int k=m;k;--k)dp[k]=dp[k]*(1-tp)+dp[k-1]*tp;
				dp[0]*=(1-tp);
			}
			tp=0;
			for(int j=1;j<=m;++j)tp+=dp[j];
			p1*=tp; tp=0;
			for(int j=1;j< n;++j)tp+=dp[j];
			p*=tp;
		}
		printf("%.3lf\n",p1-p);
	}
	return 0;
}
