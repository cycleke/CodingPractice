#include <set>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

#define N 100005
typedef pair<int, int> pr;
typedef set<pr>::iterator sit;
set<pr> col[N], S;

struct edge {int t; edge *n;} me[N << 1 | 1], *g[N], *ce;
#define adde(a, b) (ce->t = b, ce->n = g[a], g[a] = ce++)
#define FOR(a, b) for(edge *a = g[b]; a; a = a->n)
int in[N], ou[N], _dfn, dep[N], tp[N], fa[N], son[N], c[N];
int dfs1(int u, int f) {
	int r = 1, t, mx = 0;
	son[u] = 0;
	fa[u] = f;
	dep[u] = dep[f] + 1;
	FOR(it, u)
		if (it->t ^ f){
			t = dfs1(it->t, u);
			if (t > mx) mx = t, son[u] = it->t;
			r += t;
		}
	return r;
}
void dfs2(int u, int anc) {
	in[u] = ++_dfn;
	tp[u] = anc;
	if (son[u]) dfs2(son[u], anc);
	FOR(it, u)
		if ((it->t ^ fa[u]) && (it->t ^ son[u])) dfs2(it->t, it->t);
	ou[u] = _dfn;
}
inline int Lca(int u, int v) {
	while (tp[u] ^ tp[v]) dep[tp[u]] < dep[tp[v]] ? v = fa[tp[v]] : u = fa[tp[u]];
	return dep[u] < dep[v] ? u : v;
}

//Segment_Tree
int C[N << 2 | 1];
#define ls u << 1
#define rs u << 1 | 1
#define rt 1, 1, n
void build(int u, int l, int r) {
	if (l ^ r) {
		int m = l + r >> 1;
		build(ls, l, m);
		build(rs, m + 1, r);
		C[u] = 0;
	} else C[u] = c[in[l]];
}
#define pd(u) ((C[u]) ? (C[ls] = C[rs] = C[u], C[u] = 0) : 0)
void update(int u, int l, int r, const int &x, const int &y, const int &v) {
	if (x <= l && r <= y) return (void)(C[u] = v);
	int m = l + r >> 1; pd(u);
	if (x <= m) update(ls, l, m, x, y, v);
	if (y >  m) update(rs, m + 1, r, x, y, v);
}
inline int query(const int &p) {
	static int l, r, m, u;
	for (l = 1, r = _dfn, u = 1; l ^ r; (m = l + r >> 1, p <= m) ? (u = ls, r = m) : (u = rs, l = m + 1)) pd(u);
	return C[u];
}

//BIT
int tr[N];
inline void add(int x, const int &delta) {
	for (; x <= _dfn; x += x & -x) tr[x] += delta;
}
inline int sum(int x) {
	static int r;
	for (r = 0; x; x -= x & -x) r += tr[x];
	return r;
}

inline int deeper(const sit &it, int x) {
	static sit _it;
	static int x1, x2;
	x1 = x2 = 0;
	if (it != col[c[x]].begin()) x1 = Lca((--(_it = it))->second, x);
	if ((++(_it = it)) != col[c[x]].end()) x2 = Lca((_it)->second, x);
	return (dep[x1] < dep[x2]) ? x2 : x1;
}

int main() {

	//freopen("t.in", "r", stdin);
	
	int _, __, n, m, op, x, y, i, _c, ans;
	sit it;
	pr t, _t;
	scanf("%d", &_);
	for (__ = 1; __ <= _; ++__) {
		printf("Case #%d:\n", __);
		scanf("%d", &n);
		ce = me, _dfn = 0;
		S.clear();
		for (i = 1; i <= n; ++i) {
			g[i] = NULL;
			col[i].clear();
			tr[i] = 0;
		}
		for (i = 1; i <  n; ++i) {
			scanf("%d%d", &x, &y);
			adde(x, y), adde(y, x);
		}
		dfs1(1, 0); dfs2(1, 1);
		for (i = 1; i <= n; ++i) {
			scanf("%d", c + i);
			t = make_pair(in[i], i);
			col[c[i]].insert(t);
			S.insert(t);
		}
		build(rt);
		for (i = 1, y = 0; i <= n; ++i, y = 0)
			for (it = col[i].begin(); it != col[i].end(); ++it) {
				add(it->first, 1);
				if (y) add(in[Lca(it->second, y)], -1);
				y = it->second;
			}
		scanf("%d", &m);
		while (m--) {
			scanf("%d%d", &op, &x);
			t = make_pair(in[x], x);
			if (op) {
				ans = sum(ou[x]) - sum(in[x] - 1);
				it = S.lower_bound(t);
				if (it == S.end()) ++ans;
				else if (it->second ^ x) {
					_c = query(in[x]);
					it = col[_c].lower_bound(t);
					if (it == col[_c].end() || it->first > ou[x]) ++ans;
				}
				printf("%d\n", ans);
			} else {
				scanf("%d", &y);
				while (true) {
					it = S.lower_bound(t);
					if (it == S.end() || it->first > ou[x]) break;
					i = it->second;
					it = col[c[i]].find(*it);
					_c = deeper(it, i);
					if (_c) add(in[_c], 1);
					add(in[i], -1);
					_t = *it;
					S.erase(_t);
					col[c[i]].erase(_t);
					c[i] = y;
				}
				c[x] = y;
				S.insert(t);
				col[y].insert(t);
				it = col[y].find(t);
				_c = deeper(it, x);
				if (_c) add(in[_c], -1);
				add(in[x], 1);
				update(rt, in[x], ou[x], y);
			}
		}
	}
}
