#include <bits/stdc++.h>
using namespace std;
const int N=300010;
vector<int>g[N];
int siz[N],son[N],fa[N];
void dfs(int u) {
	int t=u,mx=0;siz[u]=1,son[u]=u;
	for(int i=0;i<g[u].size();++i) {
		dfs(g[u][i]); siz[u]+=siz[g[u][i]];
		if(siz[g[u][i]]>mx) t=g[u][i],mx=siz[g[u][i]];
	}son[u]=son[t];
	while(son[u]!=u&&siz[u]>2*siz[son[u]])
	  son[u]=fa[son[u]];
}
int main() {
	int n,m,i;
	for(scanf("%d%d",&n,&m),i=2;i<=n;++i) {
		scanf("%d",fa+i); g[fa[i]].push_back(i);
	}dfs(1);
	while(m--) {
		scanf("%d",&i);
		printf("%d\n",son[i]);
	}return 0;
}
