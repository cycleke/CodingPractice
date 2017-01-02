#include <cstdio>
#include <algorithm>
using namespace std;
inline int gi() {
	static int a; static char c;
	while(c=getchar(),c<'0');a=c-'0';
	while(c=getchar(),'-'<c)a=(a<<3)+(a<<1)+c-'0';
	return a;
}
#define N 100010
int fa[N],ch[2][N],s[N],rt;
bool flag[N]; pair<int,int>a[N];
inline void reverse(const int&u) {flag[u]^=1; swap(ch[0][u],ch[1][u]);}
inline void down(const int&u) {
	if(!flag[u])return;
	flag[u]=false;
	if(ch[0][u])reverse(ch[0][u]);
	if(ch[1][u])reverse(ch[1][u]);
}
inline void up(const int&u) {s[u]=1+s[ch[0][u]]+s[ch[1][u]];}
inline void rot(const int&u) {
	static int f,d,t;
	f=fa[u],d=u==ch[1][f];
	down(f),down(u);
	(t=ch[d][f]=ch[d^1][u])?fa[t]=f:0;
	(t=fa[u]=fa[f])?ch[f==ch[1][t]][t]=u:0;
	fa[f]=u,ch[d^1][u]=f;
	up(f),up(u);
}
inline void splay(int u,const int&target) {
	for(int t;fa[u]^target;rot(u))
		if(fa[t=fa[u]]^target) ((u==ch[1][t])^(t==ch[1][fa[t]]))?rot(u):rot(t);
	if(!target) rt=u;
}
inline void del(int u) {
	splay(u,0); down(u);
	if(!ch[0][u]||!ch[1][u])fa[rt=ch[0][u]+ch[1][u]]=0;
	else {
		int t=ch[0][u];
		for(down(t);ch[1][t];down(t))t=ch[1][t];
		splay(t,u);
		fa[ch[1][t]=ch[1][u]]=t;
		fa[t]=0; rt=t;
		up(t);
	}
}
int build(int l,int r) {
	if(l>r) return 0;
	int m=l+r>>1;
	s[m]=r-l+1;
	if(ch[0][m]=build(l,m-1))fa[ch[0][m]]=m;
	if(ch[1][m]=build(m+1,r))fa[ch[1][m]]=m;
	return m;
}
int main() {
	register int n=gi(),i;
	for(i=1;i<=n;++i)a[i].first=gi(),a[i].second=i;
	sort(a+1,a+n+1);
	rt=build(1,n);
	for(i=1;i<=n;++i) {
		splay(a[i].second,0);
		reverse(ch[0][rt]);
		printf("%d ",s[ch[0][rt]]+i);
		del(rt);
	}
	return 0;
}
