// by OwenCreeper
#include "bits/stdc++.h"
#define N 2000
using namespace std;
void update(int &X, int Y) { if (X == -1 || X > Y) X = Y; }
struct Edge {
	int next, to;
} ed[2 * N + 5];
int x, n, m, T, dp[N + 5][N + 5], t[N + 5], p[N + 5], last[N + 5], ecnt = 0;
void addEdge(int u, int v) {
	ed[++ecnt].to = v, ed[ecnt].next = last[u], last[u] = ecnt;
	ed[++ecnt].to = u, ed[ecnt].next = last[v], last[v] = ecnt;
}
int main(int argc, char const *argv[]) {
	scanf("%d", &x);
	scanf("%d%d%d", &n, &m, &T);
	for (int i = 1; i <= m; i++) {
		int u, v;
		scanf("%d%d", &u, &v);
		addEdge(u, v);
	}
	for (int i = 1; i <= n; i++) scanf("%d%d", t + i, p + i);
	if (2 * t[1] > x) { puts("It is a trap."); return 0; }
	memset(dp, -1, sizeof(dp));
	dp[1][t[1]] = p[1];
	for (int j = t[1]; j < x; j++)
	  for (int u = 1; u <= n; u++)
			if (~dp[u][j]) {
				if (j + t[u] <= x) update(dp[u][j + t[u]], dp[u][j] + p[u]);
				for (int i = last[u]; i; i = ed[i].next) {
					int v = ed[i].to;
					if (j + T + t[v] <= x) update(dp[v][j + T + t[v]], dp[u][j] + p[v]);
				}
			}
	if (~dp[1][x]) printf("%d\n", dp[1][x]); else puts("It is a trap.");
	return 0;
}
