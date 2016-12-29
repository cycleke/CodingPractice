#include <cstdio>
#define ll unsigned long long
int f[1000005],n,m,T,i,j;
ll a,b;
int main() {
	for(scanf("%d",&T);T;--T) {
		scanf("%llu%llu%d",&a,&b,&n);
		if(n<=1||!a) {puts("0");continue;}
		for(f[1]=f[2]=1,i=3,j=n*n+5;i<j;++i) {
			f[i]=f[i-1]+f[i-2]; while(f[i]>=n) f[i]-=n;
			if(f[i]==f[2]&&f[i-1]==f[1]) {m=i-2;break;}
		}
		for(j=1,a=a%(ll)m;b;b>>=1) {
			if(b&1) j=j*a%m;
			a=a*a%m;
		}
		printf("%d\n",f[j]);
	}
	return 0;
}
