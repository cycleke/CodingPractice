#include <cmath>
#include <cstdio>
#include <algorithm>
inline int geti() {
	register int a; register char c;
	while(c=getchar(),c<'-');a=c-'0';
	while(c=getchar(),'-'<c)a=(a<<3)+(a<<1)+c-'0';
	return a;
}
struct pip{int u,v,w;}e[500000];
int x[1002],y[1002],f[1002];
bool operator < (const pip&a,const pip&b){return a.w<b.w;}
inline int gf(int u) {
	register int r;
	for(r=u;f[r]^r;r=f[r]);
	for(int t;u^r;t=f[u],f[u]=r,u=t);
	return r;
}
#define p2(a) ((a)*(a))
int main() {
	register int n=geti(),k=geti(),i,j;
	pip*en=e,*st=e;
	for(i=0;i<n;++i)x[i]=geti(),y[i]=geti(),f[i]=i;
	for(i=1;i<n;++i)for(j=0;j<i;++j) {
			en->u=i;en->v=j;
			en->w=p2(x[i]-x[j])+p2(y[i]-y[j]);
			++en;
		}
	std::sort(e,en);
	for(;st<en;++st)
		if((i=gf(st->u))^(j=gf(st->v))) {
			if(k^n)--n,f[i]=j;
			else break;
		}
	printf("%.2lf\n",sqrt(st->w));
	return 0;
}
