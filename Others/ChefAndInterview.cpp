#include <cmath>
#include <cstdio>
#define ll long long
ll cal(ll n) {
	if(n==1) return 1LL;
	ll ret=0,e,i;
	for(e=sqrt(n),i=1;i<=e;++i) 
	  if(n%i==0) ret=ret+i+n/i;
	if(e*e==n) ret-=e;
	return ret;
}
int main() {
	ll n; int T; scanf("%d",&T);
	while(T--) {
		scanf("%lld",&n);
		printf("%lld\n",cal(n));
	}
	return 0;
}
