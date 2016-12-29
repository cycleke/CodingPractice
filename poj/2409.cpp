#include <cstdio>
typedef long long ll;
ll pow(ll a,int b) {
	ll ret=1;
	for(;b;b>>=1,a*=a) (b&1)?ret*=a:1LL;
	return ret;
}
int gcd(int a,int b) {
	for(int t;b;t=a%b,a=b,b=t);return a;
}
int main() {
	int n,k,i; ll ans;
	while(scanf("%d%d",&k,&n)&&(n|k)) {
		if(n&1) ans=pow(k,(n>>1)+1)*n;
		else ans=pow(k,(n>>1)+1)*(n>>1)+pow(k,n>>1)*(n>>1);
		for(i=1;i<=n;++i) ans+=pow(k,gcd(n,i));
		printf("%lld\n",ans/(n*2));
	}return 0;
}
