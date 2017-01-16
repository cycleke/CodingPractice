#include <cstdio>
#include <cstring>
#include <algorithm>
#define T 601
typedef int edge[100003];
const int inf = 0x3f3f3f3f, N = 605;
int n, m, take[61][10], ans;
int d[N], q[N], g[N], vis[N], _vis, ce;
edge to, nt, w, c;
inline void adde(int x, int y, int z, int v) {
	to[ce] = y, nt[ce] = g[x];
	c[ce] = z, w[ce] = v;
	g[x] = ce++;
}
inline void ins(int x, int y, int z, int v) {
	adde(x, y, z, v); adde(y, x, 0, -v);
}
inline bool SPFA() {
	for (int i = 0; i < T; ++i) d[i] = inf;
	int l = 0, r = 1;
	d[T] = 0, vis[T] = ++_vis, q[0] = T;
	while (l ^ r) {
		int u = q[l++], v; if (l >= T) l = 0;
		for (int i = g[u]; ~i; i = nt[i])
			if (c[i ^ 1] && d[v = to[i]] > d[u] + w[i ^ 1]) {
				d[v] = d[u] + w[i ^ 1];
				if (vis[v] ^ _vis) {
					vis[q[r++] = v] = _vis;
					if (r >= T) r = 0;
				}
			}
		vis[u] = 0;
	}
	return d[0] ^ inf;
}
int dfs(int u, int flow) {
	if (u == T) return (vis[u] = _vis), flow;
	int ret = 0, t, v;
	vis[u] = _vis;
	if (!flow) return 0;
	for (int i = g[u]; ~i; i = nt[i])
		if ((vis[v = to[i]] ^ _vis) && c[i] && d[u] + w[i ^ 1] == d[v]) {
			t = dfs(v, std::min(flow, c[i]));
			ans += t * w[i];
			flow -= t, ret += t;
			c[i] -= t, c[i^1] += t;
			if (!flow) return ret;
		}
	return ret;
}
inline void zkw() {
	while (SPFA()) {
		vis[T] = ++_vis;
		while (!(vis[T] ^ _vis)) {
			++_vis;
			dfs(0, inf);
		}
	}
}
int main() {
	int i, j, k;
	scanf("%d%d", &n, &m);
	memset(g, -1, sizeof g);
	for (i = 1; i <= m; ++i)
		for (j = 1; j <= n; ++j)
			scanf("%d", take[i] + j);
	for (i = 1; i <= n * m; ++i)
		ins(0, i, 1, 0);
	for (i = n * m + 1; i <= n * m + m; ++i)
		ins(i, T, 1, 0);
	for (i = 1; i <= n; ++i)
		for (j = 1; j <= m; ++j)
			for (k = 1; k <= m; ++k)
				ins((i - 1) * m + j, n * m + k, 1, take[k][i] * j);
	zkw();
	printf("%.2lf", (double)ans / m);
	return 0;
}
