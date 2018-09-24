#include <cstdio>
#include <algorithm>

const int maxn(3e5 + 7);

typedef int arr[maxn];
typedef std::pair<int, int> pii;

struct edge {
	int to;
	edge *nxt;
} edge_mset[maxn << 1], *cedge = edge_mset, *g[maxn];


inline void add_edge(int u, int v) {
	*cedge = (edge) {v, g[u]};
	g[u] = cedge++;
}

pii ner[maxn];
int n, m, _clock, tot, p[maxn][20];
arr dep, dfn, size, pos, h, t, stk, fa, w, dis, ans;

inline bool cmp(const int &a, const int &b) {
	return dfn[a] < dfn[b];
}

inline int find_vert(int x, int d) {
	for (register int i = 0, _d = dep[x] - d; _d; ++i, _d >>= 1)
		if (_d & 1) x = p[x][i];
	return x;
}

inline int lca(int u, int v) {
	if (dep[u] < dep[v]) std::swap(u, v);
	int d = dep[u] - dep[v];
	for (register int i = 0; d; ++i, d >>= 1)
		if (d & 1) u = p[u][i];
	if (u == v) return u;
	for (register int i = 19; ~i; --i)
		if (p[u][i] ^ p[v][i])
			u = p[u][i], v = p[v][i];
	return p[u][0];
}

void dfs(int u) {
	size[u] = 1;
	dfn[u] = ++_clock;
	for (register int i = 1; p[u][i] = p[p[u][i - 1]][i - 1]; ++i);
	for (edge *it = g[u]; it; it = it->nxt)
		if (it->to ^ p[u][0]) {
			p[it->to][0] = u;
			dep[it->to] = dep[u] + 1;
			dfs(it->to);
			size[u] += size[it->to];
		}
}

inline void build_vt() {
	static int *top, x;

	top = stk;
	std::sort(h + 1, h + m + 1, cmp);
	for (register int i = 1; i <= m; ++i) {
		if (top == stk) fa[*++top = h[i]] = 0;
		else {
			for (x = lca(*top, h[i]); dep[*top] > dep[x]; --top)
				if (dep[top[-1]] <= dep[x]) fa[*top] = x;
			if (*top ^ x) {
				fa[x] = *top;
				t[++tot] = *++top = x;
				ner[x] = std::make_pair(0x3f3f3f3f, 0);
			}
			fa[*++top = h[i]] = x;
		}
	}
}

inline void solve() {
	tot = 0;
	scanf("%d", &m);
	for (register int i = 1; i <= m; ++i) {
		scanf("%d", h + i);
		t[++tot] = pos[i] = h[i];
		ans[h[i]] = 0;
		ner[h[i]] = std::make_pair(0, h[i]);
	}
	build_vt();
	std::sort(t + 1, t + tot + 1, cmp);
	w[t[1]] = size[t[1]];
	for (register int i = 2; i <= tot; ++i)
		w[t[i]] = size[t[i]], dis[t[i]] = dep[t[i]] - dep[fa[t[i]]];
	for (register int i = tot, x; i > 1; --i)
		x = t[i], ner[fa[x]] = std::min(ner[fa[x]], std::make_pair(ner[x].first + dis[x], ner[x].second));
	for (register int i = 2, x; i <= tot; ++i)
		x = t[i], ner[x] = std::min(ner[x], std::make_pair(ner[fa[x]].first + dis[x], ner[fa[x]].second));
	ans[ner[t[1]].second] = n - size[t[1]];
	for (register int i = 2, x; i <= tot; ++i) {
		static int rt, sum;
		x  = t[i];
		rt = find_vert(x, dep[fa[x]] + 1);
		sum = size[rt] - size[x];
		w[fa[x]] -= size[rt];
		if (ner[fa[x]].second == ner[x].second) ans[ner[x].second] += sum;
		else {
			static int mid, tmp;
			mid = dep[x] - (ner[fa[x]].first - ner[x].first + dis[x]) / 2;
			if (!((ner[fa[x]].first + ner[x].first + dis[x]) & 1) && ner[fa[x]].second < ner[x].second)
				++mid;
			tmp = size[find_vert(x, mid)] - size[x];
			ans[ner[fa[x]].second] += sum - tmp;
			ans[ner[x].second] += tmp;
		}
	}
	for (register int i = 1; i <= tot; ++i) ans[ner[t[i]].second] += w[t[i]];
	for (register int i = 1; i <= m; ++i) printf("%d ", ans[pos[i]]);
	puts("");
}
int main() {

	//freopen("3572.in", "r", stdin);

	int u, v, q;
	scanf("%d", &n);
	for (register int i = 1; i < n; ++i) {
		scanf("%d%d", &u, &v);
		add_edge(u, v), add_edge(v, u);
	}
	dep[1] = 1;
	dfs(1);
	scanf("%d", &q);
	while (q--) solve();
	return 0;
}
