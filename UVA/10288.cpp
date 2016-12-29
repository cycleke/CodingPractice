#include <cstdio>
#define ll long long
ll gcd(ll a,ll b) {
	for(ll t;b;) t=a%b,a=b,b=t;
	return a;
}
int len(ll a) {
	if (!a) return 1;
	int ret=0; for(;a;a/=10) ++ret;
	return ret;
}
int main() {
	int n,i,j; ll a,b,c,g,t;
	while(scanf("%d",&n)^EOF) {
		a=b=0LL,c=1LL;
		for(i=1;i<=n;++i) {
			t=b*i+c*n; c*=i;
			a+=t/c; t%=c;
			g=gcd(t,c);
			t/=g,c/=g;
			b=t;
		}
		if(b==0) {printf("%lld\n",a);continue;}
		for(i=0,j=len(a);i<=j;++i) putchar(' ');
		printf("%lld\n%lld ",b,a);
		for(i=0,j=len(c);i<j;++i) putchar('-');
		for(i=0,j=len(a),puts("");i<=j;++i) putchar(' ');
		printf("%lld\n",c);
	}
	return 0;
}
