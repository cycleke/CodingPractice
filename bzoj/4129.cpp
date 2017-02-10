#include <bits/stdc++.h>
#define N 50003
#define wlp while
#define rep(i, l, r) for (i = l; i <= r; ++i)
#define FOR(i, u) for (edge *i = g[u]; i; i = i->n)
struct edge {int t; edge *n;} me[N<<1|1], *g[N], *ce = me;
#define adde(a, b) (*ce = (edge) {b, g[a]}, g[a] = ce++)
struct quy{int l, r, t, id, lca;} Q[N];
struct chg{int x, y, pre;} P[N];
int bel[N<<1|1], que[N<<1|1], in[N], ou[N], fa[N], son[N], tp[N], dep[N], dfn;
int n, cnt[N], L[225], full[225], now[225], blo[N], a[N], _a[N];
bool sta[N];
bool operator < (const quy &a, const quy &b) {
	if (bel[a.l] ^ bel[b.l]) return bel[a.l] < bel[b.l];
	if (bel[a.r] ^ bel[b.r]) return bel[a.r] < bel[b.r];
	return a.t < b.t;
}

int d1(int u, int f) {
	int r = 1, mx = -1, t;
	dep[u] = dep[f] + 1;
	fa[u] = f;
	FOR(it, u) if (it->t ^ f) {
		t = d1(it->t, u);
		if (t > mx) mx = t, son[u] = it->t;
		r += t;
	}
	return r;
}
void d2(int u, int anc) {
	que[in[u] = ++dfn] = u;
	tp[u] = anc;
	if (son[u]) d2(son[u], anc);
	FOR(it, u) if (!tp[it->t]) d2(it->t, it->t);
	que[ou[u] = ++dfn] = u;
}
inline int LCA(int u, int v) {
	wlp (tp[u] ^ tp[v]) dep[tp[u]] < dep[tp[v]] ? v = fa[tp[v]] : u = fa[tp[u]];
	return dep[u] < dep[v] ? u : v;
}

inline int mex() {
	static int i;
	for (i = 0;!(full[i] ^ now[i]); ++i);
	for (i = L[i]; cnt[i]; ++i);
	return i;
}
inline void rev(const int &u) {
	if (a[u] <= n) {
		if (sta[u]) (--cnt[a[u]]) ? 0 : --now[blo[a[u]]];
		else (cnt[a[u]]++) ? 0 : ++now[blo[a[u]]];
	}
	sta[u] ^= 1;
}
inline void upd(int x, int y) {
	if (sta[x]) rev(x), a[x] = y, rev(x);
	else a[x] = y;
}
inline void timetravel(int &ct, const int &goal) {
	while (ct < goal)  ++ct, upd(P[ct].x, P[ct].y);
	while (goal < ct) upd(P[ct].x, P[ct].pre), --ct;
}
int main() {

	//freopen("t.in", "r", stdin);
	
	int m, i, u, v, block, t, ct, _P = 0, _Q = 0, l, r, _l, _r;
	
	scanf("%d%d", &n, &m);
	rep(i, 1, n) scanf("%d", a + i), _a[i] = a[i];
	
	rep(i, 2, n) {
		scanf("%d%d", &u, &v);
		adde(u, v); adde(v, u);
	}
	
	d1(1, 0); d2(1, 1);
	
	rep(i, 1, m) {
		scanf("%d%d%d", &block, &u, &v);
		if (block) {
			ct = LCA(u, v);
			if (in[v] < in[u]) std::swap(u, v);
			if (ct ^ u) Q[_Q] = (quy) {ou[u], in[v], _P, _Q, ct};
			else Q[_Q] = (quy) {in[u], in[v], _P, _Q, 0};
			++_Q;
		} else P[++_P] = (chg){u, v, _a[u]}, _a[u] = v;
	}

	for (block = 1; block * block < n; ++block);

	rep(i, 0, n) blo[i] = i / block;
	
	for (i = 0; i <= n; i += block) L[blo[i]] = i, full[blo[i]] = block;
	
	for (block = 1; block * block * block < dfn; ++block);
	block *= block;
	rep(i, 1, dfn) bel[i] = (i - 1) / block;
	
	std::sort(Q, Q + _Q);
	l = 1, r = 0, ct = 0;
	for (i = 0; i < _Q; ++i) {
		_l = Q[i].l, _r = Q[i].r;
		timetravel(ct, Q[i].t);
		wlp (l < _l) rev(que[l++]);
		wlp (l > _l) rev(que[--l]);
		wlp (r < _r) rev(que[++r]);
		wlp (r > _r) rev(que[r--]);
		if (Q[i].lca) rev(Q[i].lca);
		_a[Q[i].id] = mex();
		if (Q[i].lca) rev(Q[i].lca);
	}
	for (i = 0; i < _Q; ++i)
		printf("%d\n", _a[i]);
	return 0;
}
