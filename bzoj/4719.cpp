#include <cstdio>
#include <cstring>
inline int gi() {
	static int a; static char c;
	while(c=getchar(),c<'0');a=c-'0';
	while(c=getchar(),'-'<c)a=(a<<3)+(a<<1)+c-'0';
	return a;
}
#define N 300000
struct edge{int to;edge*nt;}ME[N<<1],*ce=ME,*hd[N];
inline void adde(int a,int b) {ce->to=b,ce->nt=hd[a],hd[a]=ce++;}
struct LcaQuery{int id;LcaQuery*nt;}MQ[N<<1],*cq=MQ,*hq[N];
inline void AddLcaQuery(int a,int b) {cq->id=b,cq->nt=hq[a],hq[a]=cq++;}
struct Operator{int to;Operator*nt;}MO[N<<1],*co=MO,*h1[N],*h2[N];
inline void AddOperator(int a,int b,Operator**ho) {co->to=b,co->nt=ho[a],ho[a]=co++;}
typedef int arr[N];
arr f,w,s,t,lca,dep,ans,val,dis;
int count[N<<1],n,m;
bool vis[N];
inline int gf(int u) {
	int r=u;
	while(f[r]^r)r=f[r];
	for(int t;u^r;t=f[u],f[u]=r,u=t);
	return r;
}
void tarjan(int u) {
	f[u]=u; vis[u]=true;
	for(LcaQuery*it=hq[u];it;it=it->nt) {
		int id=it->id;
		if(u==s[id]&&vis[t[id]])lca[id]=gf(t[id]);
		if(u==t[id]&&vis[s[id]])lca[id]=gf(s[id]);
	}
	for(edge*it=hd[u];it;it=it->nt)
		if(!vis[it->to]) dep[it->to]=dep[u]+1,tarjan(it->to),f[it->to]=u;
}
void dfs1(int u,int fa) {
	int t1=w[u]+dep[u],t2=count[t1];
	for(edge*it=hd[u];it;it=it->nt)
		if(it->to^fa)dfs1(it->to,u);
	count[dep[u]]+=val[u];
	ans[u]=count[t1]-t2;
	for(Operator*it=h1[u];it;it=it->nt)--count[it->to];
}
void dfs2(int u,int fa) {
	int t1=dep[u]-w[u]+N,t2=count[t1];
	for(edge*it=hd[u];it;it=it->nt)
		if(it->to^fa)dfs2(it->to,u);
	for(Operator*it=h1[u];it;it=it->nt)++count[N+it->to];
	ans[u]+=count[t1]-t2;
	for(Operator*it=h2[u];it;it=it->nt)--count[N+it->to];
}
int main() {
	int i,j,u,v;
	n=gi(),m=gi();
	for(i=1;i<n;++i) adde(u=gi(),v=gi()),adde(v,u);
	for(i=1;i<=n;++i)w[i]=gi();
	for(i=1;i<=m;++i) {
		s[i]=gi(),t[i]=gi();
		AddLcaQuery(s[i],i);
		AddLcaQuery(t[i],i);
	}
	dep[1]=1;
	tarjan(1);
	for(i=1;i<=m;++i) {
		++val[s[i]];
		dis[i]=dep[s[i]]+dep[t[i]]-2*dep[lca[i]];
		AddOperator(lca[i],dep[s[i]],h1);
	}
	dfs1(1,0);
	memset(count,0,sizeof count);
	memset(h1,0,sizeof h1);
	co=MO;
	for(i=1;i<=m;++i) {
		AddOperator(t[i],dep[t[i]]-dis[i],h1);
		AddOperator(lca[i],dep[t[i]]-dis[i],h2);
	}
	dfs2(1,0);
	for(i=1;i<=m;++i)if(dep[s[i]]-dep[lca[i]]==w[lca[i]])--ans[lca[i]];
	printf("%d",ans[1]);
	for(i=2;i<=n;++i)printf(" %d",ans[i]);
	return 0;
}
