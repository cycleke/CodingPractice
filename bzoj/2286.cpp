#include <cstdio>
#include <cstring>
#include <algorithm>

const int maxn(250005);
typedef int arr[maxn];

struct edge {
	int to, cost;
	edge *nxt;
} edge_mset[maxn << 1], *g[maxn], *cedge = edge_mset;

inline void add_edge(int u, int v, int w = 0) {
	*cedge = (edge) {v, w, g[u]};
	g[u] = cedge++;
}

int n, m, _clock;
bool mark[maxn];
long long dp[maxn], minw[maxn];
arr size, dep, son, fa, top, stk, h, in;

void d1(int u) {
	int v;
	size[u] = 1;
	for (edge *it = g[u]; it; it = it->nxt)
		if ((v = it->to) ^ fa[u]) {
			fa[v] = u;
			dep[v] = dep[u] + 1;
			minw[v] = std::min(minw[u], (long long)it->cost);
			d1(v);
			if (size[son[u]] < size[v])
				son[u] = v;
			size[u] += size[v];
		}
}

void d2(int u, int anc) {
	top[u] = anc;
	in[u] = ++_clock;
	if (son[u]) d2(son[u], anc);
	for (edge *it = g[u]; it; it = it->nxt)
		if (!top[it->to]) d2(it->to, it->to);
}

inline int lca(int u, int v) {
	while (top[u] ^ top[v]) (dep[top[u]] < dep[top[v]]) ? v = fa[top[v]] : u = fa[top[u]];
	return dep[u] < dep[v] ? u : v;
}

inline bool cmp(const int &a, const int &b) {
	return in[a] < in[b];
}

void dfs(int u) {
	if (mark[u]) {
		dp[u] = minw[u];
		for (edge *it = g[u]; it; it = it->nxt)
			dfs(it->to);
	} else {
		long long t(0);
		for (edge *it = g[u]; it; it = it->nxt) {
			dfs(it->to);
			t += dp[it->to];
		}
		dp[u] = t < minw[u] ? t : minw[u];
	}
	g[u] = NULL;
}

inline void solve() {
	scanf("%d", &m);
	for (register int i = 1; i <= m; ++i) {
		scanf("%d", h + i);
		mark[h[i]] = true;
	}
	cedge = edge_mset;
	std::sort(h + 1, h + m + 1, cmp);
	int top = 0;
	for (register int i = 1; i <= m; ++i)
		if (top) {
			for (int u = h[i], x = lca(u, stk[top]); in[x] < in[stk[top]]; )
				if (in[x] >= in[stk[top - 1]]) {
					add_edge(x, stk[top--]);
					if (stk[top] ^ x) stk[++top] = x;
					break;
				} else
					add_edge(stk[top - 1], stk[top]), --top;
			stk[++top] = h[i];
		} else
			stk[++top] = h[i];
	while (top > 1)
		add_edge(stk[top - 1], stk[top]), --top;
	dfs(stk[1]);
	for (register int i = 1; i <= m; ++i)
		mark[h[i]] = false;
	printf("%lld\n", dp[stk[1]]);
}

int main() {
	int u, v, w;
	scanf("%d", &n);
	for (register int i = 1; i < n; ++i) {
		scanf("%d%d%d", &u, &v, &w);
		add_edge(u, v, w);
		add_edge(v, u, w);
	}
	minw[1] = 1LL << 61;
	d1(1), d2(1, 1);
	scanf("%d", &w);
	memset(g, 0, sizeof g);
	while (w--) solve();
	return 0;
}
