#include <bits/stdc++.h>
using namespace std;

const int MaxN = 100005;
typedef int arr[MaxN];
typedef pair<int, int> query;

query q[MaxN];
int dfn;
arr in, ou, top, fa, son, sz, dep;

struct edge {
	int to;
	edge *nxt;
}edge_mset[MaxN << 1], *cedge = edge_mset, *g[MaxN];
#define overedge edge *it = g[u]; it; it = it->nxt
inline void add_edge(int a, int b) {
	*cedge = (edge) {b, g[a]};
	g[a] = cedge++;
}

struct segnode {
	int sum;
	segnode *ls, *rs;
} node_mset[MaxN * 38], *root[MaxN], *cnode = node_mset;

void Insert(segnode *x, segnode * &y, int l, int r, const int &p, const int &val) {
	*(y = ++cnode) = *x;
	y->sum += val;
	if (l >= r) return;
	int mid = (l + r) >> 1;
	if (p <= mid) Insert(x->ls, y->ls, l, mid, p, val);
	else Insert(x->rs, y->rs, mid + 1, r, p, val);
}

int Query(segnode *a, segnode *b, segnode *c, segnode *d, int l, int r, const int &x, const int &y) {
	if (x <= l && r <= y) 
	  return a->sum + b->sum - c->sum - d->sum;
	int mid = (l + r) >> 1, ret = 0;
	if (x <= mid)
	  ret += Query(a->ls, b->ls, c->ls, d->ls, l, mid, x, y);
	if (y >  mid)
	  ret += Query(a->rs, b->rs, c->rs, d->rs, mid + 1, r, x, y);
	return ret;
}

void d1(int u) {
	sz[u] = 1;
	in[u] = ++dfn;
	for (overedge) if (it->to ^ fa[u]) {
		fa[it->to] = u;
		dep[it->to] = dep[u] + 1;
		d1(it->to);
		if (sz[it->to] > sz[son[u]])
		  son[u] = it->to;
		sz[u] += sz[it->to];
	}
	ou[u] = ++dfn;
}

vector<int> a[MaxN];

void d2(int u, int anc) {
	root[u] = root[fa[u]];
	top[u] = anc;
	for (vector<int>::iterator it = a[u].begin(); it != a[u].end(); ++it) {
		Insert(root[u], root[u], 1, dfn, in[*it], 1);
		Insert(root[u], root[u], 1, dfn, ou[*it], -1);
	}
	if (son[u]) d2(son[u], anc);
	for (overedge) if (!top[it->to]) d2(it->to, it->to);
}

inline int Lca(int u, int v) {
	while (top[u] ^ top[v]) dep[top[u]] < dep[top[v]] ? v = fa[top[v]] : u = fa[top[u]];
	return dep[u] < dep[v] ? u : v;
}

#define RG root[u], root[v], root[lca], root[fa[lca]]

int main() {
#ifndef ONLINE_JUDGE
	freopen("t.in", "r", stdin);
#endif
	int n, m, u, v, i, j, lca;
	long long ans = 0LL, tot, tmp;
	scanf("%d%d", &n,&m);
	for (i = 1; i < n; ++i) {
		scanf("%d%d", &u, &v);
		add_edge(u, v);
		add_edge(v, u);
	}
	for (i = 0; i < m; ++i) {
		scanf("%d%d", &u, &v);
		a[u].push_back(v);
		q[i] = make_pair(u, v);
	}
	*cnode = {0, cnode, cnode};
	*root = cnode;
	d1(1);
	d2(1, 1);
	for (i = 0; i < m; ++i) {
		u = q[i].first;
		v = q[i].second;
		lca = Lca(u, v);
		ans += Query(RG, 1, dfn, in[lca], in[u]);
		ans += Query(RG, 1, dfn, in[lca], in[v]);
		ans -= Query(RG, 1, dfn, in[lca], in[lca]);
	}
	ans -= m;
	sort(q, q + m);

	tot = (long long)m * (m - 1) >> 1;
	tmp = __gcd(ans, tot);
	printf("%lld/%lld\n", ans / tmp, tot / tmp);
	return 0;
}
