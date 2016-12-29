#include <cmath>
#include <cstdio>
#define ld long double
ld fac[200005];
int main() {
	int n,ca=0,i,k; ld p,res,q,c,poss;
	for(n=2;n<200005;++n) fac[n]=log((ld)n);
	for(n=2;n<200005;++n) fac[n]+=fac[n-1];
	while(scanf("%d%Lf",&n,&p)^EOF) {
		if(p<1e-9||(q=1.0-p)<1e-9) {printf("Case %d: %d.000000\n",++ca,n); continue;}
		res=0.0,k=n<<1,p=log(p),q=log(q);
		for(i=1;i<=n;++i) {
			c=fac[k-i]-fac[n]-fac[k-i-n];
			poss=exp(c+(n+1)*p+(n-i)*q)+exp(c+(n+1)*q+(n-i)*p);
			res+=poss*i;
		}
		printf("Case %d: %.6Lf\n",++ca,res);
	}return 0;
}
