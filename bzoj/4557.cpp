#include <cstdio>
#include <cstring>
const int MaxN = 500003, MaxD = 22, BUF = 1 << 16 | (127);
//Fast Input
inline char gc() {
	static char b[BUF], *s = b, *e = b;
	if (s == e) {
		e = (s = b) + fread(b, 1, BUF, stdin);
		if (s == e) return EOF;
	}
	return *s++;
}
inline void gi(int &a) {
	static char c;
	do c = gc(); while (c < '0');
	for (a = c - 48; 47 < (c = gc()); a = (a << 3) + (a << 1) + c - 48);
}
struct edge {
	int to;
	edge *nxt;
} edge_mset[MaxN << 1], *cedge = edge_mset, *G[MaxN];
#define overedge edge *it = G[u]; it; it = it->nxt
inline void add_edge(int a, int b) {
	*cedge = (edge) {b, G[a]};
	G[a] = cedge++;
}
bool vis[MaxN];
int n, m, d, f[MaxN][MaxD], g[MaxN][MaxD], w[MaxN];
#define rep(i, l, r) for (int i = l; i <= r; ++i)
inline void cmin(int &a, const int &b) {
	if (b < a) a = b;
}
inline int min(const int &a, const int &b) {
	return a < b ? a : b;
}
void dfs(int u, int fa) {
	int v;
	g[u][0] = f[u][0] = vis[u] ? w[u] : 0;
	rep(i, 1, d) g[u][i] = w[u];
	g[u][d + 1] = 0x3f3f3f3f;
	for (overedge) {
		v = it->to;
		if (!(v ^ fa)) continue;
		dfs(v, u);
		rep(i, 0, d) g[u][i] = min(g[u][i] + f[v][i], f[u][i + 1] + g[v][i + 1]);
		for (int i = d; ~i; --i) cmin(g[u][i], g[u][i + 1]);
		f[u][0] = g[u][0];
		rep (i, 1, d) 
			f[u][i] = min(f[u][i - 1], f[u][i] + f[v][i - 1]);
	}
}
int main() {
	int x, y;
	gi(n), gi(d);
	rep(i, 1, n) gi(w[i]);
	gi(m);
	rep(i, 1, m) {
		gi(x);
		vis[x] = true;
	}
	rep(i, 2, n) {
		gi(x), gi(y);
		//printf("%d %d\n", x, y);
		add_edge(x, y);
		add_edge(y, x);
	}
	dfs(1, 0);
	printf("%d\n", f[1][0]);
	return 0;
}
