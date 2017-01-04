#include <cstdio>
#include <algorithm>
inline int gi() {
	static int a; static char c;
	while(c=getchar(),c<'0');a=c-'0';
	while(c=getchar(),'-'<c)a=(a<<3)+(a<<1)+c-'0';
	return a;
}
#define N 200005
struct opt {int type,id,s,t,c;}p[N];
bool operator < (const opt&a,const opt&b) {
	return (a.c^b.c)?a.c<b.c:a.type<b.type;
}
int C[N],dfn,st[N],ed[N],fa[N],son[N],tp[N],dep[N],ans[2][N];
inline void add(int x,int v) {for(;x<=dfn;x+=x&-x)C[x]+=v;}
inline int sum(int x) {static int r;for(r=0;x;x-=x&-x)r+=C[x];return r;}
struct edge{int to;edge*nt;}ME[N],*ce=ME,*hd[N];
inline void adde(int a,int b) {ce->to=b,ce->nt=hd[a],hd[a]=ce++;}
int dfs1(int u) {
	int s=1,mx=-1,t;
	for(edge*it=hd[u];it;it=it->nt)
		if(dep[it->to]=dep[u]+1,s+=(t=dfs1(it->to)),mx<t)
			son[u]=it->to,mx=t;
	return s;
}
void dfs2(int u,int top) {
	st[u]=++dfn; tp[u]=top;
	if(son[u])dfs2(son[u],top);
	for(edge*it=hd[u];it;it=it->nt)
		if(it->to^son[u])dfs2(it->to,it->to);
	ed[u]=dfn;
}
inline int lca(int a,int b) {
	for(; tp[a] ^ tp[b]; a=fa[tp[a]])
		if(dep[tp[a]]<dep[tp[b]])a^=b^=a^=b;
	return dep[a]<dep[b]?a:b;
}
int main() {
	int n=gi(),rt,q,i,j,cnt=0,s,t,f,ff;
	for(i=1;i<=n;++i)
		if(fa[i]=gi())adde(fa[i],i);
		else rt=i;
	dep[rt]=1; dfs1(rt); dfs2(rt,rt);
	for(i=1,q=gi();i<=q;++i)
		if((p[i].type=gi())<2) p[i].s=gi(),p[i].t=gi(),p[i].c=i-gi(),p[i].id=++cnt;
		else p[i].s=gi(),p[i].c=i;
	std::sort(p+1,p+q+1);
	for(i=1;i<=q;++i)
		if(p[i].type<2) {
			f=lca(s=p[i].s,t=p[i].t),ff=fa[f];
			ans[0][p[i].id]=dep[s]+dep[t]-dep[f]-dep[ff];
			ans[1][p[i].id]=sum(st[s])+sum(st[t])-sum(st[f])-sum(st[ff]);
		} else add(st[s=p[i].s],1),add(ed[s]+1,-1);
	for(i=1;i<=cnt;++i)printf("%d %d\n",ans[0][i],ans[1][i]);
	return 0;
}
