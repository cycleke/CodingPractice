#include <cmath>
#include <cstdio>
#include <cstring>
const double eps=1e-9;
double a[211][211];
int idx[22][22];
inline int max(int a,int b){return a<b?b:a;}
template<class T>
inline void swap(T&a,T&b){T t=b;b=a,a=t;}
inline void init(const double&p) {
	memset(a,0,sizeof a);
	register int x,y,t;
	for(y=0;y<20;++y) {
		for(x=0;x<y;++x) {
			t=idx[y][x];
			a[t][t]=a[t][210]=1;
			a[t][idx[y][max(0,x-2)]]-=1-p;
			a[t][idx[y][x+1]]-=p;
		}
		t=idx[y][y];
		a[t][t]=a[t][210]=1;
		a[t][idx[y][max(0,x-2)]]-=1-p;
		a[t][idx[x+1][x]]-=p;
	}
}
const int n=210;
inline double guass() {
	register int i,j,k;
	double t;
	for(i=0;i<n;++i) {
		for(k=i;k<210&&fabs(a[k][i])<eps;++k);
		if(i^k)for(j=0;j<=n;++j)swap(a[i][j],a[k][j]);
		for(t=a[i][i],j=i;j<=n;++j)a[i][j]/=t;
		for(j=0;j<n;++j)
			if((i^j)&&fabs(a[j][i])>eps)for(t=a[j][i],k=0;k<=n;++k)
											a[j][k]-=t*a[i][k];
	}
	return a[0][n];
}
int main() {
	int t=0; double p;
	for(register int i=0,j;i<21;++i)
		for(j=0;j<=i;++j)idx[i][j]=t++;
	while(scanf("%lf",&p)^EOF)
	{
		init(p);
		printf("%.6lf\n",guass());
	}
	return 0;
}
