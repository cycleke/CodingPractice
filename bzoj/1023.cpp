#include <vector>
#include <cstdio>

inline int max(const int &a, const int &b) {
	return a < b ? b : a;
}
inline int min(const int &a, const int &b) {
	return a < b ? a : b;
}

const int maxn(50005);

std::vector<int> g[maxn];
int ans, f[maxn], dep[maxn], fa[maxn];
inline void circle(int u, int v) {
	static int tot, q[maxn * 2], a[maxn * 2], *l, *r;
	tot = dep[v] - dep[u] + 1;
	for (int i = v; i ^ u; i = fa[i]) a[tot--] = f[i];
	a[tot] = f[u];
	tot = dep[v] - dep[u] + 1;
	for (int i = 1; i <= tot; ++i) a[tot + i] = a[i];
	l = r = q;
	for (int i = 2; i <= (tot << 1); ++i) {
		if (l < r && i - *l > (tot >> 1)) ++l;
		if (l < r) ans = max(ans, i - *l + a[i] + a[*l]);
		while (l < r && a[r[-1]] - r[-1] < a[i] - i) --r;
		*r++ = i;
	}
	for (int i = 2; i <= tot; ++i) f[u] = max(f[u], a[i] + min(i - 1, tot - i + 1));
}

void dfs(int u) {
	static int dfn[maxn], low[maxn], _dfn = 0;
	int v;
	dfn[u] = low[u] = ++_dfn;
	for (size_t i = 0; i < g[u].size(); ++i) {
		v = g[u][i];
		if (v == fa[u]) continue;
		if (!dfn[v]) {
			fa[v] = u;
			dep[v] = dep[u] + 1;
			dfs(v);
			low[u] = min(low[u], low[v]);
		} else
			low[u] = min(low[u], dfn[v]);
		if (dfn[u] < low[v]) {
			ans = max(ans, f[u] + f[v] + 1);
			f[u] = max(f[u], f[v] + 1);
		}
	}
	for (size_t i = 0; i < g[u].size(); ++i) {
		v = g[u][i];
		if (fa[v] != u && dfn[u] < dfn[v])
			circle(u, v);
	}
}
int main() {
	int n, m, u, v, k;
	scanf("%d%d", &n, &m);
	while (m--) {
		scanf("%d%d", &k, &u);
		while (--k) {
			scanf("%d", &v);
			g[u].push_back(v);
			g[v].push_back(u);
			u = v;
		}
	}
	dfs(1);
	printf("%d\n", ans);
	return 0;
}
