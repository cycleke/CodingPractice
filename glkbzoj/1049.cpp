#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
using namespace std;
#define ni(a) (a<'0'||'9'<a)
inline int geti() {
	register int a; register char c,f=0;;
	while(c=getchar(),ni(c))f|=c=='-';a=c-'0';
	while(c=getchar(),!ni(c))a=(a<<3)+(a<<1)+c-'0';
	return f?-a:a;
}
#define N 35005
#define ll long long
int a[N],d[N],f[N],n,to[N],nxt[N],head[N],totc;
ll g[N],c1[N],c2[N];
template<class T>
inline void cmin(T&a,T b){a<b?1:a=b;}
int main() {
	int i,j,k,l,r,mid,anp,len;
	n=geti();
	for(i=1;i<=n;++i) a[i]=geti()-i;
	a[0]=-1<<30;a[++n]=1<<30;
	memset(d,127,sizeof d); 
	d[0]=-1<<30; len=0;
	for(i=1;i<=n;++i) {
		l=1,r=len,anp=0;
		while(l<=r) {
			if(a[i]>=d[mid=l+r>>1]) anp=mid,l=mid+1;
			else r=mid-1;
		}len<anp+1?len=anp+1:1;
		f[i]=anp+1; cmin(d[anp+1],a[i]);
	}memset(head,-1,sizeof head);
	for(i=n;~i;--i) {
		nxt[totc]=head[f[i]],to[totc]=i;
		head[f[i]]=totc++; g[i]=1LL<<60;
	}g[0]=0;
	for(i=1;i<=n;++i)
		for(j=head[f[i]-1];~j;j=nxt[j]) {
			l=to[j]; if(l>i) break;
			if(a[i]<a[l]) continue;
			for(r=l;r<=i;++r)
				c1[r]=abs(a[l]-a[r]),c2[r]=abs(a[i]-a[r]);
			for(r=l+1;r<=i;++r)
				c1[r]+=c1[r-1],c2[r]+=c2[r-1];
			for(r=l;r<i;++r)
				cmin(g[i],g[l]+c1[r]-c1[l]+c2[i]-c2[r]);
		}
	printf("%d\n%lld\n",n-f[n],g[n]);
	return 0;
}
