#include <cmath>
#include <cstdio>
#include <algorithm>
#define ni (c<'0'|'9'<c)
inline int geti() {
	register int a; register char c;
	while(c=getchar(),ni);a=c-'0';
	while(c=getchar(),!ni)a=(a<<3)+(a<<1)+c-'0';
	return a;
}
#define getv(v,t) (sqrt(2.0*(t)*c+1.0*(v)*(v)))
int V[100005];
int main() {
	int T,n,c,t,i,q;
	for(T=geti();T;--T) {
		n=geti(),c=geti();
		for(i=1;i<=n;++i) (V[i]=geti()),geti(),geti();
		std::sort(V+1,V+n+1);
		for(q=geti();q;--q) {
			t=geti(),i=geti();
			printf("%.3lf\n",getv(V[i],t));
		}
	}
	return 0;
}
