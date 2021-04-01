#include <cstdio>
#include <iostream>
#include <cstring>
#include <queue>
#include <vector>
using namespace std;

const int N = 1e5 + 10;

vector<int> G[N];

int n, m, R[N], SA[N], g[N];

priority_queue< pair<int, int> >pq;

void Build() {
	memset(R, -1, sizeof R); memset(g, 0, sizeof g);
	for (int i = 1; i <= n; ++i) pq.push(make_pair(0, i));
	for (int i = n; i > 0;) {
		int id = pq.top().second;
		pq.pop();
		if (~R[id]) continue;
		SA[i] = id; R[id] = i--;
		for (int j = 0; j < G[id].size(); ++j) {
			int v = G[id][j];
			if (~R[v]) continue;
			++g[v];
			pq.push(make_pair(g[v], v));
		}
	}
}

void F(int u) {
	for (int i = 0; i < G[u].size(); ++i) {
		int v = G[u][i];
		if (g[v] == -1) continue;
		R[g[v]] = u;
	}
	for (int i = 1; g[u] == -1; ++i) if (R[i] ^ u) g[u] = i;
}

int Cal() {
	memset(g, -1, sizeof g);
	memset(R, -1, sizeof R);
	for (int i = n; i; --i) F(SA[i]);
	int ret = 0;
	for (int i = n; i; --i) ret = max(ret, g[i]);
	return ret;
}

int main() {
	scanf("%d%d", &n, &m);
	int a, b;
	for (int i = 1; i <= n; ++i) G[i].clear();
	for (int i = 1; i <= m; ++i) {
		scanf("%d%d", &a, &b);
		G[a].push_back(b);
		G[b].push_back(a);
	}
	Build();
	printf("%d\n", Cal());
	return 0;
}
