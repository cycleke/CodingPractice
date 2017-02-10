#include <bits/stdc++.h>
#define N 200001
#define M 1000001
struct edge {int t; edge *n;} me[M], *g[N], *ce = me;
#define adde(a, b) (ce->t = b, ce->n = g[a], g[a] = ce++)
int f[N], size[N], a[N];
inline int gf(int u) {
	static int r, t;
	for (r = u; f[r] ^ r; r = f[r]);
	while (u ^ r) t = f[u], f[u] = r, u = t;
	return r;
}
inline void uni(int u, int v) {
	if (size[u] < size[v]) std::swap(u, v);
	f[v] = u, size[u] += size[v];
}
void dfs(const int &u) {
	for (edge *it = g[u]; it; it = it->n)
		if (!~a[it->t]) a[it->t] = a[u] ^ 1, dfs(it->t);
}
int main() {
	int n, m, i, x, y;
	scanf("%d%d", &n, &m);
	for (i = 1; i <= n; ++i)
		f[i] = i, size[i] = 1;
	while (m--) {
		scanf("%d%d", &x, &y);
		adde(x, y), adde(y, x);
		if (gf(x) ^ gf(y)) uni(f[x], f[y]);
	}
	for (i = 1; i <= n; ++i)
		if (size[gf(i)] < 2) return puts("NIE"), 0;
	puts("TAK");

	memset(a, -1, sizeof a);
	
	for (i = 1; i <= n; ++i)
		if (f[i] == i) a[i] = 0, dfs(i);

	for (i = 1; i <= n; ++i)
		puts(a[i] ? "K" : "S");
	
	return 0;
}
