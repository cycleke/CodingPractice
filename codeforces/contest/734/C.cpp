#include <bits/stdc++.h>
using namespace std;
const int M=2e5+5;
typedef long long ll;
ll a[M],b[M],c[M],d[M];
int main() {
	ll n,m,k,x,s;
	scanf("%I64d%I64d%I64d%I64d%I64d",&n,&m,&k,&x,&s);
	for(int i=1;i<=m;++i) scanf("%I64d",a+i);
	for(int i=1;i<=m;++i) scanf("%I64d",b+i);
	for(int i=1;i<=k;++i) scanf("%I64d",c+i);
	for(int i=1;i<=k;++i) scanf("%I64d",d+i);
	long long ans=1LL*x*n;
	a[0]=x;b[0]=0;
	for(int i=0,l,r,an,mi;i<=m;++i) {
		if(s<b[i]) continue;
		for(an=l=0,r=k;l<=r;)
			if((0LL+b[i]+d[mi=l+r>>1])<=s) l=(an=mi)+1;
			else r=mi-1;
		ans=min(ans,a[i]*(n-c[an]));
	}
    printf("%I64d\n",ans);
	return 0;
}
