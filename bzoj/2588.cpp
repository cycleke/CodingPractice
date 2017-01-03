#include <cstdio>
#include <algorithm>
inline int gi() {
	static int a; static char c,f;
	for(f=0;(c=getchar())<'0';f|=c=='-');a=c-'0';
	while(c=getchar(),'-'<c)a=(a<<3)+(a<<1)+c-'0';
	return f?-a:a;
}
#define N 100005
#define M 4000005
int a[N],rk[N],mp[N],S[M],rt[N],tnd,p[20][N],ls[M],rs[M],n,cnt,dep[N];
bool cmp(const int&i,const int&j) {return a[i]<a[j];}
struct edge{int to;edge*nt;}MED[N<<1],*cedge=MED,*hd[N];
inline void adde(int a,int b){cedge->to=b,cedge->nt=hd[a],hd[a]=cedge++;}
void insert(const int&la,int&cu,int l,int r,const int &val) {
	cu=++tnd;
	ls[cu]=ls[la],rs[cu]=rs[la],S[cu]=S[la]+1;
	if(l==r) return; int m=l+r>>1;
	if(val<=m) insert(ls[la],ls[cu],l,m,val);
	else insert(rs[la],rs[cu],m+1,r,val);
}
void dfs(int u) {
	int v; dep[u]=dep[p[0][u]]+1;
	for(v=1;v<20;++v) if(!(p[v][u]=p[v-1][p[v-1][u]])) break;
	insert(rt[p[0][u]],rt[u],1,cnt,a[u]);
	for(edge*it=hd[u];it;it=it->nt)
		if((v=it->to)^p[0][u]) p[0][v]=u,dfs(v);
}
inline int findkth(int a,int b,int c,int d,int k) {
	int l=1,r=cnt,m,t;
	while(l^r) {
		m=l+r>>1;
		t=S[ls[a]]+S[ls[b]]-S[ls[c]]-S[ls[d]];
		if(k<=t) a=ls[a],b=ls[b],c=ls[c],d=ls[d],r=m;
		else a=rs[a],b=rs[b],c=rs[c],d=rs[d],l=m+1,k-=t;
	}return l;
}
inline int lca(int u,int v) {
	if(dep[u]<dep[v])u^=v^=u^=v;
	int i,t=dep[u]-dep[v];
	for(i=0;i<20&&t;++i)
		if(t>>i&1) u=p[i][u];
	if(u==v)return u;
	for(i=19;~i;--i)
		if(p[i][u]^p[i][v])u=p[i][u],v=p[i][v];
	return p[0][u];
}
int main() {
	int i,ans=0,u,v,k,anc,fanc,t,q;
	n=gi(),q=gi();
	for(i=1;i<=n;++i)a[i]=gi(),rk[i]=i;
	std::sort(rk+1,rk+n+1,cmp);
	mp[1]=u=a[rk[1]]; a[rk[1]]=cnt=1;
	for(i=2;i<=n;++i) {
		if(u^a[v=rk[i]])mp[++cnt]=u=a[v];
		a[v]=cnt;
	}
	for(i=1;i<n;++i)adde(u=gi(),v=gi()),adde(v,u);
	dfs(1);
	while(q--) {
		u=gi()^ans,v=gi(),k=gi();
		anc=lca(u,v); fanc=p[0][anc];
		t=findkth(rt[u],rt[v],rt[anc],rt[fanc],k);
		ans=mp[t];
		printf("%d",ans);
		if(q)puts("");
	}
	return 0;
}
