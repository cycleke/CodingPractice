#include <cstdio>
const long long mo=100003;
inline long long pow(long long b,long long n) {
	register long long r=1LL;
	for(;n;n>>=1,b=b*b%mo) if(n&1) r=r*b%mo;
	return r;
}
int main() {
	long long n,m,ans;
	scanf("%lld%lld",&m,&n);
	m%=mo;
	ans=pow(m,n);
	ans-=m*pow(m-1,n-1);
	ans%=mo;
	if(ans<0) ans+=mo;
	printf("%lld\n",ans);
	return 0;
}
