#include <cstdio>
#define ld long double
ld f[35];
int main() {
	int n,i; ld t,p,c;
	while(scanf("%d%Lf",&n,&t)!=EOF&&(n||t)) {
		f[n]=1<<n;
		for(i=n-1;~i;--i) {
			p=(1<<i)/f[i+1];
			(p<t)?p=t:1;
			c=(p-t)/(1-t);
			f[i]=(1<<i)*c+(1+p)/2.*f[i+1]*(1-c);
		}
		printf("%.3Lf\n",*f);
	}
}
