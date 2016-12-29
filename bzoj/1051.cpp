#include <cstdio>
inline int geti() {
	register int a; register char c;
	while(c=getchar(),c<'0');a=c-'0';
	while(c=getchar(),'-'<c)a=(a<<3)+(a<<1)+c-'0';
	return a;
}
inline void cmin(int&a,int b){b<a?a=b:1;}
struct E{int to;E*nt;}CD[50000],*cd=CD,*hd[10001];
int dfn[10001],_clock,bel[10001],st[10001],tp,bc,sz[10001];
bool deg[10001];
int dfs(int u) {
	int low=dfn[u]=++_clock,v;
	st[++tp]=u;
	for(E*it=hd[u];it;it=it->nt)
		if(!dfn[v=it->to])cmin(low,dfs(v));
		else if(!bel[v])cmin(low,dfn[v]);
	if(low==dfn[u]) {
		++bc;
		do{
			v=st[tp--];
			bel[v]=bc;
			++sz[bc];
		}while(v^u);
	}return low;
}
int main() {
	register int n=geti(),m=geti(),i,j;
	E*it;
	while(m--) {
		i=geti(),j=geti();
		cd->to=j,cd->nt=hd[i];
		hd[i]=cd++;
	}
	for(i=1;i<=n;++i)if(!dfn[i])dfs(i);
	for(i=1;i<=n;++i)
		for(it=hd[i],j=bel[i];it;it=it->nt)
			if(j^bel[it->to]){deg[j]=1;break;}
	for(m=0,i=1;i<=bc;++i)
		if(!deg[i]) (m)?(m=0,i=bc+1):(m=sz[i]);
	printf("%d\n",m);
	return 0;
}
