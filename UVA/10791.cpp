#include <cmath>
#include <cstdio>
#define ll long long
ll f[110],cnt;
void init(ll n) {
	cnt=0;
	for(ll i=2,e=(ll)sqrt(n),t;i<=e&&n>1;++i)
	  if(n%i==0) {
		  t=1LL;
		  while(n%i==0&&n>1) t*=i,n/=i;
		  f[cnt++]=t;
	  }
	if(n>1)f[cnt++]=n;
}
int main() {
	ll n,ans; int ca=0,i;
	while(scanf("%lld",&n)!=EOF&&n) {
		init(n);
		if(cnt<2) ans=n+1;
		else for(i=0,ans=0;i<cnt;++i)
		  ans+=f[i];
		printf("Case %d: %lld\n",++ca,ans);
	}
	return 0;
}
