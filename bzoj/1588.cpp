#include <cstdio>
#include <algorithm>
inline int gi() {
	register int a; register char c,f=0;
	while(c=getchar(),c<'0')f|=c=='-';a=c-'0';
	while(c=getchar(),'-'<c)a=(a<<3)+(a<<1)+c-'0';
	return f?-a:a;
}
#define N 100005
#define inf 0x7f7f7f7f
int pred[N],succ[N],a[N],b[N],r[N];
inline int gf(int u,int*f) {
	int r=u;while(f[r]^r)r=f[r];
	for(int t;u^r;t=f[u],f[u]=r,u=t);
	return r;
}
inline void cmin(long long&a,const long long&b){if(b<a)a=b;}
inline bool cmp(const int&i,const int&j){return a[i]<a[j];}
int main() {
	int n=gi(),i,x;
	for(i=1;i<=n;++i)b[i]=a[i]=gi(),r[i]=i;
	std::sort(r+1,r+n+1,cmp);
	for(i=1;i<=n;++i) a[r[i]]=i;
	for(i=1;i<=n;++i) r[i]=a[i],a[i]=b[i];
	std::sort(a+1,a+n+1);
	for(i=1;i<=n;++i)pred[i]=i,succ[i]=i;
	succ[n+1]=n+1;
	long long ans=0,t;
	for(i=n;1<i;--i) {
		t=inf;
		x=gf(r[i]-1,pred);
		if(x)cmin(t,b[i]-a[x]);
		pred[r[i]]=r[i]-1;
		x=gf(r[i]+1,succ);
		if(x<=n)cmin(t,a[x]-b[i]);
		succ[r[i]]=r[i]+1;
		ans+=t;
	}
	ans+=b[1];
	printf("%lld\n",ans);
	return 0;
}
