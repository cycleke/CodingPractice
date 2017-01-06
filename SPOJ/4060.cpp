#include <cstdio>
#define N 1005
double f[N],g[N];
int main() {
	int _,n,i;
	double p,q,t;
	scanf("%d",&_);
	while(_--) {
		scanf("%d%lf%lf",&n,&p,&q);
		if(n>1000) n=1000;
		f[0]=0,g[0]=1;
		for(int i=1;i<=n;++i) {
			if(f[i-1]>g[i-1]) p=1-p,q=1-q;
			t=1-(1-p)*(1-q);
			f[i]=(p*g[i-1]+(1-p)*q*f[i-1])/t;
			g[i]=(q*f[i-1]+(1-q)*p*g[i-1])/t;
			if(f[i-1]>g[i-1]) p=1-p,q=1-q;
		}
		printf("%.8lf\n",f[n]);
	}
	return 0;
}
