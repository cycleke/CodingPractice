#include <bits/stdc++.h>
using namespace std;

#define N 100005
struct edge {
    int t;
    edge *n;
}me[N<<1|1], *ce = me, *g[N];
#define adde(a, b) (*ce = (edge){b, g[a]}, g[a] = ce++)
#define FOR(a, b) for (edge *a = g[b]; a; a = a->n)
int fa[N], son[N], tp[N], dep[N], dq[N], dfn;
void d1(int u) {
    static int sz[N];
    sz[u] = 1;
    FOR(it, u) if (it->t ^ fa[u]) {
        fa[it->t] = u;
        dep[it->t] = dep[u] + 1;
        d1(it->t);
        if (sz[it->t] >= sz[son[u]]) son[u] = it->t;
        sz[u] += sz[it->t];
    }
}
void d2(int u, int anc) {
    tp[u] = anc;
	dq[++dfn] = u;
    if (son[u]) d2(son[u], anc);
    FOR(it, u) if (!tp[it->t]) d2(it->t, it->t);
}
inline int lca(int u, int v) {
	while (tp[u] ^ tp[v]) dep[tp[v]] < dep[tp[u]] ? u = fa[tp[u]] : v = fa[tp[v]];
	return dep[u] < dep[v] ? u : v;
}

//Trie
#define MS 1700005
struct node {
	int cnt, ch[2];
}C[MS];
int cnd, w[N], rt[N];

void insert(int x, int &y, const int &w, int level) {
	C[y = ++cnd] = C[x];
	++C[y].cnt;
	if (!level) return;
	if (w & level)
	  insert(C[x].ch[1], C[y].ch[1], w, level >> 1);
	else
	  insert(C[x].ch[0], C[y].ch[0], w, level >> 1);
}

int Query(int a, int b, int c, int d, const int &z) {
	static int ret, i, t;
	for (ret = 0, i = 1 << 15; i; i >>= 1) {
		t = (z & i) ? 0 : 1;
		if (C[C[a].ch[t]].cnt + C[C[b].ch[t]].cnt > C[C[c].ch[t]].cnt + C[C[d].ch[t]].cnt) {
			ret ^= i;
			a = C[a].ch[t];
			b = C[b].ch[t];
			c = C[c].ch[t];
			d = C[d].ch[t];
		} else {
			t ^= 1;
			a = C[a].ch[t];
			b = C[b].ch[t];
			c = C[c].ch[t];
			d = C[d].ch[t];
		}
	}
	return ret;
}

int main() {
	int n, q;
	while (scanf("%d%d", &n, &q) != EOF) {
		for (int i = 1; i <= n; ++i) {
		  scanf("%d", w + i);
		  g[i] = NULL;
		  tp[i] = son[i] = 0;
		}
		ce = me;
		for (int i = 1, u, v; i < n; ++i) {
			scanf("%d%d", &u, &v);
			adde(u, v);
			adde(v, u);
		}
		cnd = dfn = 0;
		d1(1);
		d2(1, 1);
		for (int i = 1; i <= n; ++i) 
		  insert(rt[fa[dq[i]]], rt[dq[i]], w[dq[i]], 1 << 15);
		for (int x, y, z, t; q; --q) {
			scanf("%d%d%d", &x, &y, &z);
			t = lca(x, y);
			printf("%d\n", Query(rt[x], rt[y], rt[t], rt[fa[t]], z));
		}
	}
	return 0;
}
