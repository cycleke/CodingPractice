#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
//Input
int ina; char inc,inb[1<<16],*ine=inb,*ins=inb;
#define getc() ((ins==ine&&(ine=(ins=inb)+fread(inb,1,1<<16,stdin),ins==ine))?EOF:*ins++)
inline int geti() {
	while((inc=getc())<'0'||inc>'9'); ina=inc-'0';
	while((inc=getc())>='0'&&inc<='9') ina=(ina<<3)+(ina<<1)+inc-'0';
	return ina;
}
//Tree
#define N 300010
int son[N],fa[N],top[N],head[N],nxt[N<<1],to[N<<1],w[N<<1],tote,dep[N],dis[N],d[N];
#define FOR(a,b) for(int a=head[b];~a;a=nxt[a])
int dfs1(int u) {
	int ret=1,t,mx=0; son[u]=0;
	FOR(i,u) if(to[i]^fa[u]) {
		dep[to[i]]=dep[u]+1;
		dis[to[i]]=dis[u]+w[i];
		fa[to[i]]=u;
		ret +=(t=dfs1(to[i]));
		(mx<t)?mx=t,son[u]=to[i]:1;
	}
	return ret;
}
void dfs2(int u,int tp) {
	top[u]=tp; if(son[u]) dfs2(son[u],tp);
	FOR(i,u) if(to[i]!=fa[u]&&to[i]!=son[u])
		dfs2(to[i],to[i]);
}
int lca(int u,int v) {
	while(top[u]^top[v]) {
		if(dep[top[u]]<dep[top[v]]) u^=v^=u^=v;
		u=fa[top[u]];
	}
	return (dep[u]<dep[v])?u:v;
}
//Operator
int From[N],End[N],Len[N],Lca[N];
//main
int mxdis,mxedge,cntmor,val[N],n,m;

int rejudge(int u) {
	FOR(i,u) if(to[i]^fa[u]) d[u]+=rejudge(to[i]);
	(d[u]==cntmor&&mxedge<val[u])?mxedge=val[u]:1;
	return d[u];
}

bool check(int x) {
	mxdis=mxedge=cntmor=0;
	memset(d,0,sizeof d);
	for(int i=1;i<=m;++i) if(Len[i]>x) {
		(mxdis<Len[i])?mxdis=Len[i]:1;
		++d[From[i]],++d[End[i]];
		d[Lca[i]]-=2; ++cntmor;
	}
	rejudge(1);
	return mxdis-mxedge<=x;
}

int main() {
	int i,j,k,a,b,c,l,r=0,mid,ans;
	memset(head,-1,sizeof head);
	for(n=geti(),m=geti(),i=1;i<n;++i) {
		a=geti(),b=geti(),c=geti();
		to[tote]=b,nxt[tote]=head[a],w[tote]=c,head[a]=tote++;
		to[tote]=a,nxt[tote]=head[b],w[tote]=c,head[b]=tote++;
	}
	dfs1(1), dfs2(1,1);
	for(i=0;i<tote;i+=2) val[(dep[to[i]]<dep[to[i^1]])?to[i^1]:to[i]]=w[i];
	for(i=1;i<=m;++i) {
		From[i]=geti(),End[i]=geti();
		Len[i]=dis[From[i]]+dis[End[i]]-2*dis[Lca[i]=lca(From[i],End[i])];
		(r<Len[i])?r=Len[i]:1;
	}
	l=0;
	while(l<=r) {
		mid=l+r>>1;
		if(check(mid)) r=(ans=mid)-1;
		else l=mid+1;
	}
	return printf("%d\n",ans),0;
}
