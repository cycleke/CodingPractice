#include <bits/stdc++.h>

#define N 80005
#define MS 20002000

struct edge {int t; edge *n;} me[N<<1|1], *g[N], *ce = me;
#define adde(a, b) (*ce = (edge){b, g[a]}, g[a] = ce++)
int fa[17][N], dep[N], sz[N], uf[N];
int gf(int u) {
	return (uf[u] ^ u) ? uf[u] = gf(uf[u]) : u;
}

int ha[N], hacnt, val[N];
int idx(const int &x) {
	return std::lower_bound(ha + 1, ha + hacnt + 1, x) - ha;
}

struct SegNode {
	int sum;
	SegNode *ls, *rs;
} SegMst[MS], *SegIt = SegMst, *rt[N];

void Insert(SegNode *x, SegNode * &y, int l, int r, const int &v) {
	*(y = SegIt++) = *x;
	++y->sum;
	if (l >= r)
	  return;
	int m = l + r >> 1;
	if (v <= m)
	  Insert(x->ls, y->ls, l, m, v);
	else
	  Insert(x->rs, y->rs, m + 1, r, v);
}

#define swp(a, b) (a ^= b ^= a ^= b)

int Lca(int u, int v) {
	if (dep[u] < dep[v])
	  swp(u, v);
	int delta = dep[u] - dep[v];
	for (int i = 0; delta; ++i, delta >>= 1)
	  if (delta & 1) u = fa[i][u];
	if (u == v)
	  return u;
	for (int i = 16; ~i; --i)
	  if (fa[i][u] ^ fa[i][v])
		u = fa[i][u], v = fa[i][v];
	return fa[0][u];
}

int Query(int u, int v, int k) {
	int tmp, l = 1, r = hacnt, m;
	tmp = Lca(u, v);
	SegNode *x = rt[u], *y = rt[v], *z = rt[tmp], *d = rt[fa[0][tmp]];
	while (l ^ r) {
		m = l + r >> 1;
		tmp = x->ls->sum + y->ls->sum - z->ls->sum - d->ls->sum;
		if (k <= tmp) {
			x = x->ls;
			y = y->ls;
			z = z->ls;
			d = d->ls;
			r = m;
		} else {
			x = x->rs;
			y = y->rs;
			z = z->rs;
			d = d->rs;
			l = m + 1;
			k -= tmp;
		}
	}
	return ha[l];
}

int que[N], *l, *r;
void bfs(int u) {
	l = r = que;
	*r++ = u;
	static int v, i;
	while (l < r) {
		u = *l++;
		for (edge *it = g[u]; it; it = it->n)
		  if ((v = it->t) ^ fa[0][u]) {
			  fa[0][v] = u;
			  dep[v] = dep[u] + 1;
			  *r++ = v;
		  }
	}
	for (l = que; l < r; ++l) {
		Insert(rt[fa[0][*l]], rt[*l], 1, hacnt, val[*l]);
	}
	for (i = 1; i < 17; ++i)
	  for (l = que; l < r; ++l)
		fa[i][*l] = fa[i - 1][fa[i - 1][*l]];
}

void Union(int u, int v) {
	int fu = gf(u), fv = gf(v);
	if (sz[fu] > sz[fv])
	  swp(u, v), swp(fu, fv);
	fa[0][u] = v;
	dep[u] = dep[v] + 1;
	bfs(u);
	uf[fu] = fv;
	sz[fv] += sz[fv];
	adde(u, v);
	adde(v, u);
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("forest.in", "r", stdin);
	freopen("forest.out", "w", stdout);
#endif
	int n, m, t, u, v, k, lastans;
	char ops[5];
	scanf("%*d%d%d%d", &n, &m, &t);
	for (int i = 1; i <= n; ++i) {
		scanf("%d", val + i);
		ha[++hacnt] = val[i];
	}
	std::sort(ha + 1, ha + hacnt + 1);
	hacnt = std::unique(ha + 1, ha + hacnt + 1) - ha - 1;
	*rt = SegIt++;
	**rt = (SegNode) {0, *rt, *rt};
	for (int i = 1; i <= n; ++i)
		val[i] = idx(val[i]);
	while (m--) {
		scanf("%d%d", &u, &v);
		adde(u, v);
		adde(v, u);
	}
	for (int i = 1; i <= n; ++i)
	  if (!fa[0][i]) {
		  bfs(i);
		  for (l = que; l < r; ++l)
			uf[*l] = i;
		  sz[i] = r - que;
	  }
	while (t--) {
		scanf("%s%d%d", ops, &u, &v);
		u ^= lastans, v ^= lastans;
		if (*ops == 'Q') {
			scanf("%d", &k);
			k ^= lastans;
			printf("%d\n", lastans = Query(u, v, k));
		} else Union(u, v);
	}
	return 0;
}
