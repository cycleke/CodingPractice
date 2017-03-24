#include <cstdio>
#include <cstring>

const int maxn(1e5 + 7);

struct edge {
	int to;
	edge *nxt;
}edge_mset[maxn << 1], *graph[maxn], *cedge = edge_mset;

inline void add_edge(int u, int v) {
	*cedge = (edge) {v, graph[u]};
	graph[u] = cedge++;
}

int dep[maxn], longest[maxn];
long long *g[maxn], *f[maxn];
long long mset[maxn * 5], *end(mset + 1), ans;

void d1(int u, int from) {
	longest[u] = u;
	for (edge *it = graph[u]; it; it = it->nxt)
		if (it->to ^ from) {
			dep[it->to] = dep[u] + 1;
			d1(it->to, u);
			if (dep[longest[it->to]] > dep[longest[u]])
				longest[u] = longest[it->to];
		}
	for (edge *it = graph[u]; it; it = it->nxt)
		if ((it->to ^ from) && ((longest[it->to] ^ longest[u]) || (u == 1))) {
			int v = longest[it->to];
			end += dep[v] - dep[u] + 1;
			f[v] = end;
			g[v] = ++end;
			end += (dep[v] - dep[u]) * 2 + 1;
		}
}

void d2(int u, int from) {
	int v;
	for (edge *it = graph[u]; it; it = it->nxt)
		if ((v = it->to) ^ from) {
			d2(v, u);
			if (longest[u] == longest[v])
				f[u] = f[v] - 1, g[u] = g[v] + 1;
		}
	ans += g[u][0];
	f[u][0] = 1;
	for (edge *it = graph[u]; it; it = it->nxt)
		if (((v = it->to) ^ from) && (longest[u] ^ longest[v])) {
			for (register int i = 0; i < dep[longest[v]] - dep[u] + 1; ++i)
				ans += f[u][i - 1] * g[v][i] + f[v][i] * g[u][i + 1];
			for (register int i = 0; i < dep[longest[v]] - dep[u] + 1; ++i) {
				g[u][i - 1] += g[v][i];
				g[u][i + 1] += f[u][i + 1] * f[v][i];
				f[u][i + 1] += f[v][i];
			}
		}
}

int main() {
	int n, u, v;
	scanf("%d", &n);
	for (register int i = 1; i < n; ++i) {
		scanf("%d%d", &u, &v);
		add_edge(u, v);
		add_edge(v, u);
	}
	d1(1, 0);
	d2(1, 0);
	printf("%lld\n", ans);
	return 0;
}
