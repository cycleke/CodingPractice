#include <cstdio>
#include <algorithm>
using namespace std;
inline int gi() {
	static int a; static char c;
	while(c=getchar(),c<'0');a=c-'0';
	while(c=getchar(),'-'<c)a=(a<<3)+(a<<1)+c-'0';
	return a;
}
const int N=200005,M=500005,MS=2000000;
int val[N],ch[2][N],p[17][N],st[N],en[N],n,a[N],mpa[N],f[N],mcnt;
int ls[MS],rs[MS],sum[MS],rt[N],cnd,exd,_dfn;
pair< int,pair<int,int> >edge[M]; bool vis[N];
inline int g(const int&x){return lower_bound(mpa+1,mpa+mcnt+1,x)-mpa;}
inline int gf(int u) {
	int r=u;
	while(f[r]^r)r=f[r];
	for(int t;u^r;t=f[u],f[u]=r,u=t);
	return r;
}
void insert(int x,int&y,int l,int r,const int&v) {
	y=++cnd; ls[y]=ls[x],rs[y]=rs[x],sum[y]=sum[x]+1;
	if(l>=r) return;
	int m=l+r>>1;
	if(v<=m)insert(ls[x],ls[y],l,m,v);
	else insert(rs[x],rs[y],m+1,r,v);
}
void dfs(int u) {
	st[u]=++_dfn; vis[u]=true;
	if(u>n)rt[_dfn]=rt[_dfn-1];
	else insert(rt[_dfn-1],rt[_dfn],1,mcnt,a[u]);
	if(ch[0][u])dfs(ch[0][u]),dfs(ch[1][u]);
	en[u]=_dfn;
}
inline int ganc(int u,int x) {
	for(int i=16;~i;--i)if(p[i][u]&&val[p[i][u]]<=x)u=p[i][u];
	return u;
}
inline int query(int x,int y,int k) {
	int l=1,r=mcnt,md,t;
	while(l^r) {
		md=l+r>>1;
		t=sum[ls[y]]-sum[ls[x]];
		if(k<=t)x=ls[x],y=ls[y],r=md;
		else x=rs[x],y=rs[y],l=md+1,k-=t;
	}return mpa[l];
}
int main() {
//	freopen("peaks.in","r",stdin);
	int m,q,i,u,v,x,k,ans=0;
	n=gi(),m=gi(),q=gi();
	for(i=1;i<=n;++i)a[i]=mpa[i]=gi();
	sort(mpa+1,mpa+n+1);
	mcnt=unique(mpa+1,mpa+n+1)-mpa-1;
	for(i=1;i<=n;++i)a[i]=g(a[i]);
	for(i=0;i<m;++i) {
		u=gi(),v=gi(),x=gi();
		edge[i]=make_pair(x,make_pair(u,v));
	}
	for(i=n*2;i;--i)f[i]=i;
	sort(edge,edge+m);
	exd=n;
	for(i=0;i<m;++i) 
		if(u=gf(edge[i].second.first),v=gf(edge[i].second.second),u^v) {
			f[u]=f[v]=++exd;
			ch[0][exd]=u,ch[1][exd]=v;
			p[0][u]=p[0][v]=exd;
			val[exd]=edge[i].first;
		}
	for(i=1;i<=n;++i)
		if(!vis[i])dfs(gf(i));
	for(i=1;i<17;++i)for(v=1;v<=exd;++v)p[i][v]=p[i-1][p[i-1][v]];
	while(q--) {
		u=gi()^ans,x=gi()^ans,k=gi()^ans;
		v=ganc(u,x);
		i=sum[rt[en[v]]]-sum[rt[st[v]-1]];
		if(i<k)puts("-1"),ans=0;
		else printf("%d\n",ans=query(rt[st[v]-1],rt[en[v]],i-k+1));
	}return 0;
}
