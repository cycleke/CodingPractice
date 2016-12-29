#include <cmath>
#include <cstdio>
#include <algorithm>
int n; double a[11][11],p[11];
inline void guass() {
	register int i,j,k,id; register double mx,t;
	for(i=0;i<n;++i) {
		mx=-1;
		for(j=i;j<n;++j) if(mx<fabs(a[j][i]))mx=a[id=j][i];
		if(i^id)for(j=i;j<=n;++j)std::swap(a[i][j],a[id][j]);
		t=a[i][i];
		for(j=i;j<=n;++j) a[i][j]/=t;
		for(j=0;j<n;++j)
			if(i^j)for(t=a[j][i],k=1;k<=n;++k)
					   a[j][k]-=t*a[i][k];
	}
}
int main() {
	register int i,j;
	double t;
	scanf("%d",&n);
	for(i=0;i<n;++i)scanf("%lf",p+i);
	for(i=0;i<n;++i)
	for(j=0;j<n;++j) {
		scanf("%lf",&t);
		a[i][j]=2*(t-p[j]);
		a[i][n]+=t*t-p[j]*p[j];
	}
	guass();
	for(i=0;i<n;++i)printf("%.3lf%c",a[i][n],"\n "[i+1<n]);
	return 0;
}
