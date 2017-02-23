#include <cstdio>
#include <cstring>

#define MaxN 500003

struct edge {
	int from, to, cost;
	edge *nxt;
	edge() {}
	edge(int from, int to, int cost, edge *nxt) :
		from(from), to(to), cost(cost), nxt(nxt) {}
} edge_mset[MaxN << 1], *curten_edge = edge_mset, *g[MaxN], *from[MaxN];

inline void add_edge(int a, int b, int c) {
	*curten_edge = edge(a, b, c, g[a]);
	g[a] = curten_edge++;
}

bool vis[MaxN], mark[MaxN];
int que[MaxN << 1], home[MaxN];
long long d[MaxN], d0[MaxN], d1[MaxN];

inline void bfs(int s, long long *dis, bool fg) {
	int *l = que, *r = que, u, v;
	memset(vis, 0, sizeof vis);
	*r++ = s;
	dis[s] = 0;
	vis[s] = true;
	while (l < r) {
		int u = *l++;
		for (edge *it = g[u]; it; it = it->nxt) {
			v = it->to;
			if (vis[v])
				continue;
			vis[v] = true;
			dis[v] = dis[u] + it->cost;
			*r++ = v;
			if (fg)
				from[v] = it;
		}
	}
}

inline void spfa(const int &n) {
	int *l = que, *r = que, u, v;
	memset(d, 63, sizeof d);
	memset(vis, 0, sizeof vis);
	for (u = 1; u <= n; ++u)
		if (mark[u]) {
			*r++ = u;
			vis[u] = true;
			d[u] = 0;
		}
	while (l < r) {
		u = *l++;
		vis[u] = false;
		for (edge *it = g[u]; it; it = it->nxt) {
			v = it->to;
			if (d[v] <= d[u] + it->cost)
				continue;
			d[v] = d[u] + it->cost;
			if (!vis[v]) {
				vis[v] = true;
				*r++ = v;
			}
		}
	}
}

#define max(a, b) (a < b ? b : a)

int main() {
	int n, k, i, j, a, b, c, u;
	long long sum = 0LL;
	scanf("%d%d", &n, &k);
	for (i = 1; i < n; ++i) {
		scanf("%d%d%d", &a, &b, &c);
		add_edge(a, b, c);
		add_edge(b, a, c);
	}
	for (i = 0; i < k; ++i)
		scanf("%d", home + i);
	bfs(*home, d0, true);

	mark[*home] = true;

	for (i = 1; i < k; ++i)
		for (u = home[i]; !mark[u]; u = from[u]->from)
			sum += from[u]->cost, mark[u] = true;
	
	spfa(n);

	u = *home;
	for (i = 1; i < k; ++i)
		if (d0[u] < d0[home[i]])
			u = home[i];

	bfs(u, d1, false);

	u = *home;
	for (i = 1; i < k; ++i)
		if (d1[u] < d1[home[i]])
			u = home[i];

	bfs(u, d0, false);
	
	sum <<= 1;
	for (i = 1; i <= n; ++i)
		printf("%lld\n", sum - max(d0[i], d1[i]) + (mark[i] ? 0 : (d[i] << 1)));
		
	return 0;
}
