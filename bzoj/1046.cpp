#include <cstdio>
inline int geti() {
	register int a; register char c,f=0;
	while(c=getchar(),c<'0')f|=c=='-';a=c-'0';
	while(c=getchar(),'-'<c)a=(a<<3)+(a<<1)+c-'0';
	return f?-a:a;
}
#define N 10005
#define swap(a,b) (a^=b^=a^=b)
int a[N],d[N],dp[N];
int main() {
#ifndef ONLINE_JUDGE
	freopen("1046.in","r",stdin);
	freopen("1046.out","w",stdout);
#endif
	register int n=geti(),i,l,r,m,an,len;
	for(i=n;i;--i)a[i]=geti(),d[i]=-0x7f7f7f7f;
	len=dp[1]=1;*d=0x7f7f7f7f,d[1]=a[1];
	for(i=2;i<=n;++i) {
		for(l=0,r=len+1;l<=r;)
			if(a[i]<d[m=l+r>>1])l=(an=m)+1;
			else r=m-1;
		if(len<(dp[i]=++an))len=dp[i];
		d[an]<a[i]?d[an]=a[i]:1;
	}
	for(l=1,r=n;l<r;++l,--r)
		swap(a[l],a[r]),swap(dp[l],dp[r]);
	for(m=geti();m;--m) {
		if(len<(l=geti())){puts("Impossible");continue;}
		for(i=1,r=-0x7f7f7f7f;i<=n&&l;++i)
			if(dp[i]>=l&&a[i]>r)printf("%d%c",r=a[i],(--l)?' ':'\n');
	}return 0;
}
