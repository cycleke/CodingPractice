#include <cstdio>
inline int geti() {
	register int a; register char c;
	while(c=getchar(),c<'0');a=c-'0';
	while(c=getchar(),'-'<c)a=(a<<3)+(a<<1)+c-'0';
	return a;
}
inline long long getll() {
	register long long a; register char c;
	while(c=getchar(),c<'0');a=c-'0';
	while(c=getchar(),'-'<c)a=(a<<3)+(a<<1)+c-'0';
	return a;
}
struct E{int to;long long v;E*nt;}CD[200002],*cd=CD,*hd[50002];
#define adde(a,b,c) (cd->to=b,cd->v=c,cd->nt=hd[a],hd[a]=cd++)
long long xv[50002],a[62];
bool vis[50002];
inline void addval(long long x) {
	for(register int i=60;(~i)&&x;--i)
		if(x>>i&1) (a[i])?(x^=a[i]):(a[i]=x,x=0);
}
void dfs(const int&u) {
	vis[u]=true;
	for(E*it=hd[u];it;it=it->nt)
		if(vis[it->to])addval(xv[u]^it->v^xv[it->to]);
		else {
			xv[it->to]=xv[u]^it->v;
			dfs(it->to);
		}
}
int main() {
	register int n=geti(),m=geti(),i,j;
	long long c;
	while(m--) {
		i=geti(),j=geti(),c=getll();
		adde(i,j,c);adde(j,i,c);
	}
	dfs(1);c=xv[n];
	for(i=60;~i;--i)if((c^a[i])>c)c^=a[i];
	printf("%lld\n",c);
	return 0;
}
