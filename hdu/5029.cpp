#include <bits/stdc++.h>
using namespace std;
#define N 100007
typedef int arr[N];
typedef pair<int, int> Seg;
//Tree
struct edge {
	int t;
	edge *n;
} me[N * 2], *g[N], *ce;
#define adde(a, b) (*ce = (edge){b, g[a]}, g[a] = ce++)
#define FOR(u) for (edge *it = g[u]; it; it = it->n)
arr tp, fa, son, in, dq, sz, dep, ans;
int dfn, n, m;
void d1(int u) {
	sz[u] = 1;
	son[u] = tp[u] = 0;
	FOR(u) if (fa[u] ^ it->t) {
		fa[it->t] = u;
		dep[it->t] = dep[u] + 1;
		d1(it->t);
		sz[u] += sz[it->t];
		if (sz[it->t] > sz[son[u]]) son[u] = it->t;
	}
}
void d2(int u, int anc) {
	dq[in[u] = ++dfn] = u;
	tp[u] = anc;
	if (son[u]) d2(son[u], anc);
	FOR(u) if (!tp[it->t]) d2(it->t, it->t);
}
vector<int> Q[N];
#define ls u << 1
#define rs u << 1 | 1
Seg C[N << 2];
inline void pu(const int &u) {
	if (C[ls].first < C[rs].first)
	  C[u] = C[rs];
	else
	  C[u] = C[ls];
}
void Build(int u, int l, int r) {
	C[u] = pair<int, int>(0, l);
	if (l ^ r) {
		int mid = (l + r) >> 1;
		Build(ls, l, mid);
		Build(rs, mid + 1, r);
	}
}
void update(int u, int l, int r, const int &pos, const int &delta) {
	if (l >= r)
	  return (void)(C[u].first += delta);
	int mid = (l + r) >> 1;
	if (pos <= mid)
	  update(ls, l, mid, pos, delta);
	else
	  update(rs, mid + 1, r, pos, delta);
	pu(u);
}
void pb(const int &u, const int &v, const int &z) {
	Q[u].push_back(z);
	Q[v + 1].push_back(-z);
}
void modify(int u, int v, const int &z) {
	while (tp[u] ^ tp[v]) {
		if (dep[tp[u]] < dep[tp[v]])
		  swap(u, v);
		pb(in[tp[u]], in[u], z);
		u = fa[tp[u]];
	}
	if (dep[u] < dep[v])
	  swap(u, v);
	pb(in[v], in[u], z);
}
bool Init() {
	ce = me;
	dfn = 0;
	memset(g, 0, sizeof g);
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n + 1; ++i)
	  Q[i].clear();
	return n || m;
}
void Work() {
	int i, u, v, z, mx = 1;
	for (int i = 1; i < n; ++i) {
		scanf("%d%d", &u, &v);
		adde(u, v);
		adde(v, u);
	}
	d1(1);
	d2(1, 1);
	while (m--) {
		scanf("%d%d%d", &u, &v, &z);
		modify(u, v, z);
		if (mx < z) mx = z;
	}
	Build(1, 1, mx);
	for (i = 1; i <= n; ++i) {
		sort(Q[i].begin(), Q[i].end());
		for (vector<int>::iterator it = Q[i].begin(); it != Q[i].end(); ++it) 
		  (*it < 0) ? update(1, 1, mx, -*it, -1) : update(1, 1, mx, *it, 1);
		ans[dq[i]] = C[1].first ? C[1].second : 0;
	}
	for (i = 1; i <= n; ++i)
	  printf("%d\n", ans[i]);
}
int main() {
	while (Init())
	  Work();
	return 0;
}
