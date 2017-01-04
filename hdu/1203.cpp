#include <cstdio>
inline void cmin(double&a,const double&b){if(b<a)a=b;}
double dp[10005];
int main() {
	int n,m,a; double b;
	while(scanf("%d%d",&n,&m)!=EOF&&(n+m)) {
		for(int i=0;i<=n;++i)dp[i]=1;
		while(m--) {
			scanf("%d%lf",&a,&b); b=1-b;
			for(int i=n;i>=a;--i)cmin(dp[i],dp[i-a]*b);
		}
		printf("%.1lf%%\n",(1-dp[n])*100);
	}
	return 0;
}
