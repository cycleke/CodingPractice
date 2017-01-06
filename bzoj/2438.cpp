#include <cstdio>
#include <vector>
using namespace std;
#define N 100005
#define M 300005
inline int gi() {
	static int a; static char c;
	while(c=getchar(),c<'0');a=c-'0';
	while(c=getchar(),'-'<c)a=(a<<3)+(a<<1)+c-'0';
	return a;
}
int Stack[N],dfn[N],stp,bcnt,bel[N],siz[N],_clock,deg[N];
struct edge{int to;edge*nt;}ME[M],*ce=ME,*he[N];
vector<int>g[N];
inline void adde(int a,int b){ce->to=b,ce->nt=he[a],he[a]=ce++;}
inline void cmin(int&a,const int&b){if(b<a)a=b;}
int tarjan(int u) {
	Stack[++stp]=u;
	int low=dfn[u]=++_clock,v;
	for(edge*it=he[u];it;it=it->nt)
		if(dfn[v=it->to]) {if(!bel[v])cmin(low,dfn[v]);}
		else cmin(low,tarjan(v));
	if(low==dfn[u]) {
		++bcnt;
		do {
			v=Stack[stp--];
			bel[v]=bcnt;
			++siz[bcnt];
		} while(u^v);
	}
	return low;
}
int main() {
	int n=gi(),m=gi(),i,a,b;
	edge*it;
	while(m--) a=gi(),b=gi(),adde(a,b);
	for(i=1;i<=n;++i)
		if(!dfn[i])tarjan(i);
	for(i=1;i<=n;++i)
		for(a=bel[i],it=he[i];it;it=it->nt)
			if(a^(b=bel[it->to]))++deg[b],g[a].push_back(b);
	a=0;
	for(i=1;i<=bcnt;++i)if(!deg[i])++a;
	for(i=1;i<=bcnt;++i)
		if(siz[i]<2&&!deg[i]) {
			m=1;
			for(b=0;b<g[i].size();++b)
				if(deg[g[i][b]]<2){m=0;break;}
			if(m){--a;break;}
		}
	printf("%.6lf",(double)(n-a)/n);
	return 0;
}
