#include <cstdio>
inline int geti() {
	register int a; register char c,f=0;
	while(c=getchar(),c<'0')f|=c=='-';a=c-'0';
	while(c=getchar(),'-'<c)a=(a<<3)+(a<<1)+c-'0';
	return f?-a:a;
}
#define N 35002
int a[N],f[N],d[N];
long long g[N],c1[N],c2[N];
struct E{int to;E*nt;}CD[N],*hd[N],*cd=CD;
template<class T>inline void cmin(T&a,T b){b<a?a=b:1;}
inline int ibs(int a){return a<0?-a:a;}
inline void adde(int a,int b){cd->to=b,cd->nt=hd[a],hd[a]=cd++;}
int main() {
	register int n=geti()+1,i,l,r,m,an,len=0;
	for(i=1;i<n;++i)a[i]=geti()-i,d[i]=0x7f7f7f7f;
	*a=-0x7f7f7f7f,a[n]=0x7f7f7f7f;
	*d=-0x7f7f7f7f,d[n]=0x7f7f7f7f;
	for(i=1;i<=n;++i) {
		for(l=1,r=len,an=0;l<=r;)
			if(a[i]>=d[m=l+r>>1])l=(an=m)+1;
			else r=m-1;
		if(len<++an)len=an;
		cmin(d[f[i]=an],a[i]);
	}
	for(i=n;~i;--i)adde(f[i],i),g[i]=1LL<<60;
	E*it; *g=0;
	for(i=1;i<=n;++i)
		for(it=hd[f[i]-1];it;it=it->nt) {
			if(i<(l=it->to))break;
			if(a[i]<a[l])continue;
			for(r=l;r<=i;++r)
				c1[r]=ibs(a[r]-a[l]),c2[r]=ibs(a[r]-a[i]);
			for(r=l+1;r<=i;++r)
				c1[r]+=c1[r-1],c2[r]+=c2[r-1];
			for(r=l;r<i;++r)
				cmin(g[i],g[l]+c1[r]-c1[l]+c2[i]-c2[r]);
		}
	return printf("%d\n%lld\n",n-f[n],g[n]),0;
}
