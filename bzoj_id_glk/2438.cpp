#include <vector>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
const int N = 1e5 + 10;

vector<int> g[N], G[N];

//tarjan
int Stack[N], top;
int anc[N], pre[N], dfs_Time, Siz[N], Bcnt;

int dfs(int u) {
	int low = pre[u] = ++dfs_Time; Stack[++top] = u;
	for (int i = 0; i < g[u].size(); ++i)
	  if (!pre[g[u][i]]) low = min(low, dfs(g[u][i]));
	  else if (!anc[g[u][i]]) low = min(low, pre[g[u][i]]);
	if (low == pre[u]) {
		int v; ++Bcnt;
		while (top) {
			v = Stack[top--];
			anc[v] = Bcnt; ++Siz[Bcnt];
			if (v == u) break;
		}
	}
	return low;
}

int in[N];

int main() {
	int n, m, a, b;
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= m; ++i) {
		scanf("%d%d", &a, &b); g[a].push_back(b);
	}
	for (int i = 1; i <= n; ++i) 
	  if (!pre[i]) dfs(i);

	for (int i = 1; i <= n; ++i)
	  for (int j = 0; j < g[i].size(); ++j)
		if (anc[i] ^ anc[g[i][j]]) G[anc[i]].push_back(anc[g[i][j]]), ++in[anc[g[i][j]]];

	int Need = 0;
	for (int i = 1; i <= Bcnt; ++i) if (!in[i]) ++Need;
	
	for (int i = 1; i <= Bcnt; ++i) 
	if (Siz[i] == 1 && !in[i]){
		bool flag = true;
		for (int j = 0; j < G[i].size() && flag; ++j)
		  if (in[G[i][j]] < 2) flag = false;
		if (flag) { --Need; break; }
	}
	printf("%.6lf\n", (double)(n - Need) / n);
	return 0;
}
