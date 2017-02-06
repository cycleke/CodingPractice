#include <queue>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
#define N 200005
struct edge { int u, v, d; } e[N];
struct E {int t, v; E *n;} me[N<<1|1], *g[N], *ce = me;
#define adde(a, b, c) (ce->t = b, ce->v = c, ce->n = g[a], g[a] = ce++)
inline void link(int a, int b, int c) {
	adde(a, b, c), adde(b, a, c);
}

int d[N], f[N], c[N];
#define pr pair<int, int>
priority_queue< pr, vector< pr >, greater< pr > >heap;
struct query{ int x, y, b, id; } q[N];
bool ans[N];

bool operator < (const edge &a, const edge &b) {
	return a.d < b.d;
}

bool operator < (const query &a, const query &b) {
	return a.b < b.b;
}

inline void dijstra() {
	memset(d, 63, sizeof d);
	for (int i = 1; i <= *c; ++i)
		heap.push(make_pair(d[c[i]] = 0, c[i]));
	int u, dis, v;
	E *it;
	while (!heap.empty()) {
		u = heap.top().second;
		dis = heap.top().first;
		heap.pop();
		if (dis ^ d[u]) continue;
		for(it = g[u]; it; it = it->n)
			if (d[v = it->t] > dis + it->v)
				heap.push(make_pair(d[v] = dis + it->v, v));
	}
}

inline int gf(int u) {
	static int r, t;
	for (r = u; f[r] ^ r; r = f[r]);
	while (u ^ r) t = f[u], f[u] = r, u = t;
	return r;
}

int main() {
	//freopen("t.in", "r", stdin);
	int n, m, i, j, x, y, z, _q;
	scanf("%d%d%d", &n, c, &m);
	
	for (i = 1; i <= *c; ++i)
		scanf("%d", c + i);
	
	for (i = 0; i <  m; ++i) {
		scanf("%d%d%d", &x, &y, &z);
		link(x, y, z);
		e[i] = (edge) {x, y, z};
	}
	
	dijstra();
	
	for (i = 1; i <= n; ++i) f[i] = i;
	
	for (i = 0; i <  m; ++i)
		e[i].d += d[e[i].u] + d[e[i].v];
	
	scanf("%d", &_q);
	
	for (i = 0; i < _q; ++i) {
		scanf("%d%d%d", &x, &y, &z);
		q[i] = (query) {x, y, z, i};
	}

	sort(q, q + _q);
	sort(e, e +  m);
	
	for (i = j = 0; i < _q; ++i) {
		while (j < m && e[j].d <= q[i].b) 
			f[gf(e[j].u)] = gf(e[j].v), ++j;
		ans[q[i].id] = gf(q[i].x) == gf(q[i].y);
	}
	
	for (i = 0; i < _q; ++i)
		puts(ans[i] ? "TAK" : "NIE");
	
	return 0;
}
