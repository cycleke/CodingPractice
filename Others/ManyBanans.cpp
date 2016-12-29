#include <cstdio>
#define ll long long
ll C[100005],stx[310],all;
void add(int x,ll val) {
	for(;x<100005;x+=x&-x) C[x]+=val;
}
ll Sum(int x) {
	ll ret=0;
	for(;0<x;x-=x&-x) ret+=C[x];
	return ret;
}
void Insert(int x,ll y) {
	if(x<305) stx[x]+=y;
	else {
		all+=y;
		for(int i=x;i<100005;i+=x)
		  add(i,-x*y);
	}
}
ll query(ll x) {
	ll ret=0;
	for(int i=1;i<305;++i) ret+=x%i*stx[i];
	return ret+all*x+Sum(x);
}
int main() {
	int n,i,j,q,x,y; char op[2];
	for(scanf("%d",&n),i=1;i<=n;++i) {
		scanf("%d%d",&x,&y);
		Insert(x,y);
	}for(scanf("%d",&q);q;--q) {
		scanf("%s%d",op,&x);
		if(*op=='?') printf("%lld\n",query(x));
		else Insert(x,*op=='+'?1:-1);
	}return 0;
}
