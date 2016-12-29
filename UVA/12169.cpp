#include <cstdio>
#define ll long long
#define mod 10001
void exgcd(ll a,ll b,ll &d,ll &x,ll &y) {
	if(!b) {d=a,x=1,y=0;} 
	else {
		exgcd(b,a%b,d,y,x);
		y -= x*(a/b);
	}
}
ll x[205],T,a,b,i,j,k,d,g,t;
bool flag;
int main() {
	for(scanf("%lld",&T),i=1,j=T<<1;i<j;i+=2) scanf("%lld",x+i);
	for(a=0;;++a) {
		t=(x[3]-a*a*x[1]);
		exgcd(mod,a+1,d,k,b);
		if(t%d) continue;
		b=b*t/d;flag=true;
		for(i=2,j=(T<<1)+1;i<j&&flag;++i)
			if(i&1) flag&=(x[i]==(a*x[i-1]+b)%mod);
			else x[i]=(a*x[i-1]+b)%mod;
		if(flag) {
			for(i=2;i<j;i+=2) printf("%lld\n",x[i]);
			break;
		}
	}
	return 0;
}
