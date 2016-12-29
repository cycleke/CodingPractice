#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;
const int N=45;
double dp[N][N][N],p[N];
const double pi=acos(-1.);
inline double get_dist(int a,int b) {
	double t = p[b]-p[a];
	return 2. * sin(t*pi);
}
inline double get_area(int a,int b,int c) {
	double x=get_dist(a,b);
	double y=get_dist(b,c);
	double z=get_dist(a,c);
	double p=(x+y+z)/2.;
	return sqrt(p*(p-z)*(p-y)*(p-x));
}

int main() {
	double ans; int n,m;
	while(scanf("%d%d",&n,&m)^EOF) {
		if(!(n|m)) break;
		for(int i=1;i<=n;++i)
		  scanf("%lf",p+i);
		ans=0.;
		memset(dp,0,sizeof dp);
		for(int x=1;x<=n;++x) {
			int t=min(x,m);
			for(int i=3;i<=t;++i)
			  for(int j=1;j<x;++j)
				for(int k=j+1;k<x;++k) {
					double area=get_area(j,k,x);
					dp[i][j][x]=max(dp[i][j][x],dp[i-1][j][k]+area);
					if (i==m)
					  ans=max(ans,dp[i][j][x]);
				}
		}
		printf("%.6lf\n",ans);
	}
	return 0;
}
