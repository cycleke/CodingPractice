#include <cstdio>
#include <cstring>
inline int geti() {
	register int a; register char c;
	while(c=getchar(),c<'-');a=c-'0';
	while(c=getchar(),'-'<c)a=(a<<3)+(a<<1)+c-'0';
	return a;
}
#define N 100003
#define ll long long
struct E{int to;E*nxt;}CD[N<<1],*cd=CD,*h1[N],*h2[N];
#define adde1(a,b) (cd->to=b,cd->nxt=h1[a],h1[a]=cd++)
#define adde2(a,b) (cd->to=b,cd->nxt=h2[a],h2[a]=cd++)
inline void cmin(int&a,int b){b<a?a=b:1;}
inline void cmax(int&a,int b){a<b?a=b:1;}
int bel[N],bsiz[N],bc,dfs_clock,dfn[N],deg[N],sta[N],tp,d[N];
int tarjan(int u) {
	int low=dfn[u]=++dfs_clock,v;
	sta[++tp]=u;
	for(E*it=h1[u];it;it=it->nxt)
		if(!dfn[v=it->to]) cmin(low,tarjan(v));
		else if(!bel[v]) cmin(low,dfn[v]);
	if(low==dfn[u]) {
		++bc;
		do {
			v=sta[tp--];
			bel[v]=bc;
			++bsiz[bc];
		}while(v^u);
	}
	return low;
}
struct e{int to,v;e*nxt;}CE[N<<1],*ce=CE,*head[N];
inline void build_new_graph(int n) {
	for(int i=1,v;i<=n;++i) {
		for(E*it=h1[i];it;it=it->nxt)
			if((v=bel[it->to])^bel[i]) {
				ce->to=v;ce->v=0;
				ce->nxt=head[bel[i]];
				head[bel[i]]=ce++;
				++deg[v];
			}
		for(E*it=h2[i];it;it=it->nxt)
			if((v=bel[it->to])^bel[i]) {
				ce->to=v;ce->v=1;
				ce->nxt=head[bel[i]];
				head[bel[i]]=ce++;
				++deg[v];
			}
	}
}
inline bool judge(int n) {
	int cn=n,u,v; tp=0;
	for(int i=1;i<=n;++i)
		if(!deg[i]) sta[++tp]=i;
	while(tp) {
		u=sta[tp--]; --cn;
		for(E*it=h2[u];it;it=it->nxt)
			if(!(--deg[it->to])) sta[++tp]=it->to;
	}
	if(cn) return false;
	else return true;
}
inline ll toposort() {
	int u,v,x=bc;
	tp=0;
	for(int i=1;i<=bc;++i)
		if(!deg[i]) sta[++tp]=i,d[i]=1;
		else d[i]=0;
	while(tp) {
		u=sta[tp--]; --x;
		for(e*it=head[u];it;it=it->nxt) {
			v=it->to;
			cmax(d[v],d[u]+it->v);
			if(!(--deg[v])) sta[++tp]=v;
		}
	}
    if(x>0) return -1LL;
	long long ret=0;
	for(int i=1;i<=bc;++i)
		ret+=(ll)bsiz[i]*d[i];
	return ret;
}
int main() {
	register int n=geti(),k=geti(),i,a,b;
	while(k--) {
		i=geti(),a=geti(),b=geti();
		if(i==1) adde1(a,b),adde1(b,a);
		else if(i==2) adde2(a,b),++deg[b];
		else if(i==3) adde1(b,a);
		else if(i==4) adde2(b,a),++deg[a];
		else adde1(a,b);
	}
	for(i=1;i<=n;++i) if(!dfn[i]) tarjan(i);
	if(!judge(n)) return puts("-1"),0;
	build_new_graph(n);
	printf("%lld\n",toposort());
	return 0;
}
