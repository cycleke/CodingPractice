#include <cmath>
#include <cstdio>
#include <iostream>
#include <algorithm>
using namespace std;
inline int gi() {
	register int a; register char c;
	while(c=getchar(),c<'0');a=c-'0';
	while(c=getchar(),'-'<c)a=(a<<3)+(a<<1)+c-'0';
	return a;
}
//dp[i]=max{h[j]+ceil(sqrt(|i-j|))}-h[i]
#define N 500005
int h[N],n;
long double f[N],g[N];
inline long double cal(int j,int i){return h[j]+sqrt((long double)abs(i-j))-h[i];}
struct D{int l,r,q;}q[N];
inline int gf(const D&a,int x) {
	int l=a.l,r=a.r,md;
	while(l<=r)
		(md=l+r>>1,cal(a.q,md)>cal(x,md))?l=md+1:r=md-1;
	return l;
}
inline void work(long double*dp) {
	int i,l,r,t;
	l=1,r=0;
	for(i=1;i<=n;++i) {
		++q[l].l;
		if(l<=r&&q[l].l>q[l].r)++l;
		if(l>r||cal(i,n)>cal(q[r].q,n)) {
			while(l<=r&&cal(i,q[r].l)>cal(q[r].q,q[r].l))--r;
			if(l>r) q[++r]=(D){i,n,i};
			else t=gf(q[r],i),q[r].r=t-1,q[++r]=(D){t,n,i};
		}
		dp[i]=cal(q[l].q,i);
	}
}

int main() {
	n=gi();
	for(register int i=1;i<=n;++i)h[i]=gi();
	work(f);
	for(register int i=1,j=n;i<j;++i,--j)swap(h[i],h[j]);
	work(g);
	for(register int i=1;i<=n;++i) printf("%d\n",max(0,(int)ceil(max(f[i],g[n-i+1]))));
	return 0;
}
