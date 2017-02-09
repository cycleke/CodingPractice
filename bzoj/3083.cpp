#include <cstdio>
#include <cstring>
#define N 100005
int p[19][N], dep[N], C[N<<2|1], ly[N<<2|2], son[N], in[N], ou[N], dfn, tp[N];
struct edge {int t; edge *n;} me[N<<1|1], *g[N], *ce = me;
#define adde(a, b) (ce->t = b, ce->n = g[a], g[a] = ce++)
#define FOR(a, b) for (edge *a = g[b]; a; a = a->n)
int dfs1(int u, int f) {
	int r = 1, t, mx =  0;
	p[0][u] = f;
	dep[u] = dep[f] + 1;
	FOR(it, u) if (it->t ^ f) {
		t = dfs1(it->t, u);
		if (t > mx) mx = t, son[u] = it->t;
		r += t;
	}
	return r;
}
void dfs2(int u, int anc) {
	tp[u] = anc;
	in[u] = ++dfn;
	if (son[u]) dfs2(son[u], anc);
	FOR(it, u) if (!tp[it->t]) dfs2(it->t, it->t);
	ou[u] = dfn;
}
#define pd(u) ((ly[u]) ? (C[u << 1] = C[u << 1 | 1] = ly[u << 1] = ly[u << 1 | 1] = ly[u], ly[u] = 0) : 0)
#define min(a, b) (a < b ? a : b)
void upd(int u, int l, int r, const int &x, const int &y, const int &v) {
	if (x <= l && r <= y)
		return (void)(C[u] = ly[u] = v);
	int m = l + r >> 1; pd(u);
	if (x <= m) upd(u << 1, l, m, x, y, v);
	if (y > m) upd(u << 1 | 1, m + 1, r, x, y, v);
	C[u] = min(C[u << 1], C[u << 1 | 1]);
}
void quy(int u, int l, int r, const int &x, const int &y, int &v) {
	if (x <= l && r <= y) return (void)(C[u] < v ? v = C[u] : 0);
	int m = l + r >> 1; pd(u);
	if (x <= m) quy(u << 1, l, m, x, y, v);
	if (y > m)  quy(u << 1 | 1, m + 1, r, x, y, v);
}
int Walk(int u, int x) {
	static int i;
	for (i = 0; x; ++i, x >>= 1)
		if (x & 1) u = p[i][u];
	return u;
}
int main() {
	///freopen("3083.in", "r", stdin);
	///freopen("3083.out", "w", stdout);
	int n, m, u, v, i, rt, x, y, z;
	scanf("%d%d", &n, &m);
	for (i = 1; i < n; ++i) {
		scanf("%d%d", &u, &v);
		adde(u, v), adde(v, u);
	}
	dfs1(1, 0); dfs2(1, 1);
	//memset(ly, -1, sizeof ly);
	for (i = 1; i <= n; ++i) {
		scanf("%d", &u);
		upd(1, 1, n, in[i], in[i], u);
	}
	for (i = 1; (1 << i) < n; ++i)
		for (u = 1; u <= n; ++u)
			p[i][u] = p[i - 1][p[i - 1][u]];
	scanf("%d", &rt);
	while (m--) {
		scanf("%d", &i);
		if (i & 1) scanf("%d", &x);
		else scanf("%d%d%d", &x, &y, &z);
		if (i < 2) rt = x;
		else if (i & 1) {
			if (x == rt) printf("%d\n", C[1]);
			else {
				z = 0x3fffffff;
				if (in[rt] < in[x] || ou[rt] > ou[x]) quy(1, 1, n, in[x], ou[x], z);
				else {
					u = Walk(rt, dep[rt] - dep[x] - 1);
					if (in[u] > 1) quy(1, 1, n, 1, in[u] - 1, z);
					if (ou[u] < n) quy(1, 1, n, ou[u] + 1, n, z);
				}
				printf("%d\n", z);
			}
		} else {
			while (tp[x] ^ tp[y]) {
				if (dep[tp[x]] < dep[tp[y]]) x ^= y ^= x ^= y;
				upd(1, 1, n, in[tp[x]], in[x], z);
				x = p[0][tp[x]];
			}
			if (dep[x] < dep[y]) x ^= y ^= x ^= y;
			upd(1, 1, n, in[y], in[x], z);
		}
	}
	return 0;
}
