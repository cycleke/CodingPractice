#include <cmath>
#include <cstdio>
#include <algorithm>
using namespace std;
#define N 12
int n; double a[N][N],p[N];
inline void gauss() {
	int i,j,k,id; double mx,t;
	for(i=1;i<=n;++i) {
		mx=-1.0;
		for(j=i;j<=n;++j) if(fabs(a[j][i])>mx) mx=a[id=j][i];
		if(id^i) for(j=1;j<=n+1;++j) swap(a[i][j],a[id][j]);
		t=a[i][i];
		for(j=i+1;j<=n+1;++j) a[i][j]/=t;
		for(j=1;j<=n;++j)
			if(i^j) for(t=a[j][i],k=1;k<=n+1;++k)
						a[j][k]-=t*a[i][k];
	}
}
int main() {
	int i,j; double t;
	scanf("%d",&n);
	for(i=1;i<=n;++i) scanf("%lf",p+i);
	for(i=1;i<=n;++i)
		for(j=1;j<=n;++j) {
			scanf("%lf",&t);
			a[i][j]=2*(t-p[j]);
			a[i][n+1]+=t*t-p[j]*p[j];
		}
	gauss();
	for(i=1;i<n;++i) printf("%.3lf ",a[i][n+1]);
	return printf("%.3lf\n",a[n][n+1]),0;
}
