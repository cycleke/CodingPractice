#include <set>
#include <cstdio>
#include <cstring>

const int maxn(1e5 + 7);
typedef int arr[maxn];

struct edge {
	int to, cost;
	edge *nxt;
} edge_mset[maxn << 1], *g[maxn], *cedge = edge_mset;

inline void add_edge(int u, int v, int w) {
	*cedge = (edge) {v, w, g[u]};
	g[u] = cedge++;
}

int dfn;
long long dis[maxn];
arr son, fa, top, dq, size, dep, in;

void d1(int u) {
	int v;
	size[u] = 1;
	for (edge *it = g[u]; it; it = it->nxt)
		if ((v = it->to) ^ fa[u]) {
			fa[v] = u;
			dep[v] = dep[u] + 1;
			dis[v] = dis[u] + it->cost;
			d1(v);
			if (size[v] > size[son[u]])
				son[u] = v;
			size[u] += size[v];
		}
}

void d2(int u, int anc) {
	top[u] = anc;
	dq[in[u] = ++dfn] = u;
	if (son[u])  d2(son[u], anc);
	for (edge *it = g[u]; it; it = it->nxt)
		if (!top[it->to]) d2(it->to, it->to);
}

inline int lca(int u, int v) {
	while (top[u] ^ top[v]) dep[top[u]] < dep[top[v]] ? v = fa[top[v]] : u = fa[top[u]];
	return dep[u] < dep[v] ? u : v;
}

inline long long disc(int u, int v) {
	return dis[u] + dis[v] - (dis[lca(u, v)] << 1);
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("3991.in", "r", stdin);
#endif
	int n, m, u, v, w;
	scanf("%d%d", &n, &m);
	for (register int i = 1; i < n; ++i) {
		scanf("%d%d%d", &u, &v, &w);
		add_edge(u, v, w);
		add_edge(v, u, w);
	}
	d1(1);
	d2(1, 1);
	while (m--) {
		static long long ans = 0;
		static bool status[maxn];
		static std::set<int> s;
		static std::set<int>::iterator it, pre, nxt;
		scanf("%d", &u);
		if (status[u]) {
			status[u] = false;
			u = in[u];
			it = s.find(u);
			if (s.size() > 1) {
				pre = nxt = it;
				if (pre == s.begin()) pre = s.end();
				--pre;
				if (++nxt == s.end()) nxt = s.begin();
				ans = ans - disc(dq[u], dq[*pre]) - disc(dq[u], dq[*nxt]) + disc(dq[*pre], dq[*nxt]);
			}
			s.erase(it);
		} else {
			status[u] = true;
			u = in[u];
			it = (s.insert(u)).first;
			if (s.size() > 1) {
				pre = nxt = it;
				if (pre == s.begin()) pre = s.end();
				--pre;
				if (++nxt == s.end()) nxt = s.begin();
				ans = ans + disc(dq[u], dq[*pre]) + disc(dq[u], dq[*nxt]) - disc(dq[*pre], dq[*nxt]);
			}
		}
		printf("%lld\n", ans);
	}
	return 0;
}
