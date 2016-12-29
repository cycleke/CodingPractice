#include <bits/stdc++.h>
using namespace std;
#define N 100005
int p[17][N],dep[N],cnt[N],n,m;
struct D{int deep,id,c;};
vector<int>g[N];
vector<D>ev[N];
int ans[N];
void dfs(int u) {
	int v,i;
	for(i=1;(1<<i)<=dep[u];++i)
		p[i][u]=p[i-1][p[i-1][u]];
	for(i=0;i<g[u].size();++i) {
		v=g[u][i]; dep[v]=dep[u]+1;
		dfs(v);
	}
}
void work(int u) {
	++cnt[dep[u]];
	for(int i=0;i<ev[u].size();++i)
		ev[u][i].c=cnt[ev[u][i].deep];
	for(int i=0;i<g[u].size();++i)
		work(g[u][i]);
	for(int i=0;i<ev[u].size();++i)
		ans[ev[u][i].id]=cnt[ev[u][i].deep]-ev[u][i].c;
}
int main() {
	scanf("%d",&n);
	for(int i=1;i<=n;++i) {
		scanf("%d",p[0]+i);
		g[p[0][i]].push_back(i);
	}dfs(0);
	scanf("%d",&m);
	int u,k,j; D t;
	for(int i=1;i<=m;++i) {
		scanf("%d%d",&u,&k);
		t.deep=dep[u],t.id=i;
		for(j=0;j<17;++j)
			if(k&(1<<j)) u=p[j][u];
		if(u) ev[u].push_back(t);
	}work(0);
	for(int i=1;i<=m;++i) printf("%d ",max(ans[i]-1,0));
	return 0;
}
