#include <cstdio>
#include <algorithm>
inline int geti() {
	register int a; register char c;
	while(c=getchar(),c<'0');a=c-'0';
	while(c=getchar(),'-'<c)a=(a<<3)+(a<<1)+c-'0';
	return a;
}
int f[501];
inline int gf(int u) {
	int r;
	for(r=u;f[r]^r;r=f[r]);
	for(int t;u^r;t=f[u],f[u]=r,u=t);
	return r;
}
inline int gcd(int a,int b) {
	for(int t;b;t=a%b,a=b,b=t);
	return a;
}
struct E{int x,y,v;}e[5000];
inline bool operator < (const E&a,const E&b){return a.v<b.v;}
int main() {
#ifndef ONLINE_JUDGE
	freopen("1050.in","r",stdin);
#endif
	/*register*/ int n=geti(),m=geti(),i,j,s,t,a1=30000,a2=1;
	for(i=0;i<m;++i)e[i]=(E){geti(),geti(),geti()};
	s=geti(),t=geti();
	std::sort(e,e+m);
	for(j=1;j<=n;++j)f[j]=j;
	for(j=0;j<m;++j) {
		f[gf(e[j].x)]=gf(e[j].y);
		if(gf(s)==gf(t)) {
			if(e[j].v*a2<e[0].v*a1)a1=e[j].v,a2=e[0].v;
			break;
		}
		if(e[j].v*a2>=e[0].v*a1)break;
	}
	if(a1>=30000)return puts("IMPOSSIBLE"),0;
	for(i=1;i<m;++i) {
		for(j=1;j<=n;++j)f[j]=j;
		for(j=i;j<m;++j) {
			f[gf(e[j].x)]=gf(e[j].y);
			if(gf(s)==gf(t)) {
				if(e[j].v*a2<e[i].v*a1)a1=e[j].v,a2=e[i].v;
				break;
			}
			if(e[j].v*a2>=e[i].v*a1)break;
		}
	}
	i=gcd(a1,a2);
	if(a2^i)printf("%d/%d\n",a1/i,a2/i);
	else printf("%d\n",a1/a2);
	return 0;
}
