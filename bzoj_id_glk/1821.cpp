#include <cstdio>
#include <cmath>
#include <algorithm>
#include <cstring>
using namespace std;
inline int geti() {
	register int a; register char c;
	while(c=getchar(),c<'-');a=c-'0';
	while(c=getchar(),'-'<c)a=(a<<3)+(a<<1)+c-'0';
	return a;
}
struct pip{int u,v,w;}edge[500002];
inline bool cmp(const pip&a,const pip&b){return a.w<b.w;}
int f[1002],X[1002],Y[1002];
inline int gf(int u) {
	register int en;
	for(en=u;f[en]^en;en=f[en]);
	for(int t;u^en;t=f[u],f[u]=en,u=t);
	return en;
}
#define sqr(a) ((a)*(a))
int main() {
	register int n=geti(),k=geti(),i,j;
	pip *ee=edge,*se=edge;
	for(i=1;i<=n;++i) {
		X[i]=geti(),Y[i]=geti();
		f[i]=i;
	}
	for(i=1;i^n;++i)
		for(j=i+1;j<=n;++j) {
			ee->u=i,ee->v=j;
			ee->w=sqr(X[i]-X[j])+sqr(Y[i]-Y[j]);
			++ee;
		}
	sort(edge,ee,cmp);
	for(;se<ee;++se)
		if((i=gf(se->u))^(j=gf(se->v))) {
			if(k^n) --n,f[i]=j;
			else break;
		}
	printf("%.2lf\n",sqrt(se->w));
	return 0;
}
