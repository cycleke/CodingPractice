#include <cstdio>
#include <cstring>
inline int geti() {
	register int a; register char c,f=0;
	while(c=getchar(),c<'0')f|=c=='-';a=c-'0';
	while(c=getchar(),'-'<c)a=(a<<3)+(a<<1)+c-'0';
	return f?-a:a;
}
inline void swap(int&a,int&b){int t=b;b=a,a=t;}
inline void cmax(int&a,int b){a<b?a=b:1;}
#define N 300005
int Max[N<<1],seg,Sum[N<<1];
inline int qm(int st,int en) {
	int r=-0x7f7f7f7f;
	for(st+=seg-1,en+=seg+1;st^en^1;st>>=1,en>>=1) {
		if(~st&1)cmax(r,Max[st^1]);
		if( en&1)cmax(r,Max[en^1]);
	}return r;
}
inline int qs(int st,int en) {
	int r=0;
	for(st+=seg-1,en+=seg+1;st^en^1;st>>=1,en>>=1) {
		if(~st&1)r+=Sum[st^1];
		if( en&1)r+=Sum[en^1];
	}return r;
}
inline void upd(int x,int v) {
	x+=seg;Max[x]=Sum[x]=v;
	for(x>>=1;x;x>>=1) {
		Sum[x]=Sum[x<<1]+Sum[x<<1|1];
		Max[x]=Max[x<<1]<Max[x<<1|1]?Max[x<<1|1]:Max[x<<1];
	}
}
struct E{int to;E*nt;}CD[N<<1],*cd=CD,*hd[N];
#define adde(a,b) (cd->to=b,cd->nt=hd[a],hd[a]=cd++)
int fa[N],p[N],tp[N],dep[N],_clock,son[N];
int dfs1(int u) {
	int v,r=1,t,mx=0;
	for(E*it=hd[u];it;it=it->nt)
		if(!dep[v=it->to]) {
			fa[v]=u;dep[v]=dep[u]+1;
			t=dfs1(v);r+=t;
			if(mx<t)son[u]=v,mx=t;
		}return r;
}
void dfs2(int u,int top) {
	p[u]=++_clock;tp[u]=top;
	if(son[u])dfs2(son[u],top);
	for(E*it=hd[u];it;it=it->nt)
		if(!tp[it->to])dfs2(it->to,it->to);
}
inline int qmax(int u,int v) {
	int r=-0x7f7f7f7f;
	while(tp[u]^tp[v]) {
		if(dep[tp[u]]<dep[tp[v]])swap(u,v);
		cmax(r,qm(p[tp[u]],p[u]));
		u=fa[tp[u]];
	}
	if(dep[u]<dep[v])swap(u,v);
	cmax(r,qm(p[v],p[u]));
	return r;
}
inline int qsum(int u,int v) {
	int r=0;
	while(tp[u]^tp[v]) {
		if(dep[tp[u]]<dep[tp[v]])swap(u,v);
		r+=qs(p[tp[u]],p[u]);
		u=fa[tp[u]];
	}
	if(dep[u]<dep[v])swap(u,v);
	return r+qs(p[v],p[u]);
}
int main() {
#ifndef ONLINE_JUDGE
	freopen("1036.in","r",stdin);
	freopen("1036.out","w",stdout);
#endif
	register int n,x,y,q;
	char ts[10];
	for(n=geti(),seg=1;seg<=n;seg<<=1);
	for(q=1;q<n;++q) {
		x=geti(),y=geti();
		adde(x,y),adde(y,x);
	}
	dep[1]=1;dfs1(1);dfs2(1,1);
	for(x=1;x<=n;++x)Sum[seg+p[x]]=Max[seg+p[x]]=geti();
	for(x=seg;x;--x) {
		Sum[x]=Sum[x<<1]+Sum[x<<1|1];
		Max[x]=Max[x<<1]<Max[x<<1|1]?Max[x<<1|1]:Max[x<<1];
	}
	for(q=geti();q;--q) {
		scanf("%s",ts);
		x=geti(),y=geti();
		if(*ts=='Q') {
			if(ts[1]=='M') printf("%d\n",qmax(x,y));
			else printf("%d\n",qsum(x,y));
		} else upd(p[x],y);
	}
	return 0;
}
