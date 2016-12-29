#include <cmath>
#include <cstdio>
inline int geti() {
	register int a; register char c;
	while(c=getchar(),c<'0');a=c-'0';
	while(c=getchar(),'-'<c)a=(a<<3)+(a<<1)+c-'0';
	return a;
}
int s[11][11];
double dp[11][11][11][11][11],ave;
//ANS =sqrt(sum{(submart-ave)^2/n}
inline void cmin(double&a,double b){b<a?a=b:1.0;}
int main() {
#ifndef ONLINE_JUDGE
	freopen("1048.in","r",stdin);
#endif
	register int a=geti(),b=geti(),n=geti(),l,r,u,d,i,j;
	for(i=1,j;i<=a;++i)
		for(j=1;j<=b;++j)
			s[i][j]=s[i-1][j]+s[i][j-1]-s[i-1][j-1]+geti();
	double ave=(double)s[a][b]/n;
	for(u=1;u<=a;++u)
		for(d=u;d<=a;++d)
			for(l=1;l<=b;++l)
				for(r=l;r<=b;++r)
					{
						double&t=dp[1][u][l][d][r]=s[d][r]+s[u-1][l-1]-s[u-1][r]-s[d][l-1];
						t=(t-ave)*(t-ave);
					}
	for(register int k=2;k<=n;++k) {
//		printf("Round %d:\n",k);
		for(u=1;u<=a;++u)
			for(d=u;d<=a;++d)
				for(l=1;l<=b;++l)
					for(r=l;r<=b;++r) {
						double &t=dp[k][u][l][d][r];t=1e20;
						if((r-l+1)*(d-u+1)<k)continue;
						for(i=l;i<r;++i)
							for(j=1;j<k;++j)
								cmin(t,dp[j][u][l][d][i]+dp[k-j][u][i+1][d][r]);
						for(i=u;i<d;++i)
							for(j=1;j<k;++j)
								cmin(t,dp[j][u][l][i][r]+dp[k-j][i+1][l][d][r]);
//						printf("%d %d %d %d %.2lf\n",u,l,d,r,t);
					}
	}
	printf("%.2lf\n",sqrt(dp[n][1][1][a][b]/n));
	return 0;
}
