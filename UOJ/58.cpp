#include <bits/stdc++.h>
#define N 100003
#define wlp while
#define rep(i, l, r) for (int i = l; i <= r; ++i)
#define FOR(a, b) for (edge *a = g[b]; a; a = a->n)
inline void gi(int &x) {
	static char c;
	wlp (c = getchar(), c < '0'); x = c - '0';
	wlp (c = getchar(), '-' < c) x = (x << 3) + (x << 1) + c - '0';
}
struct edge {int t; edge *n;} me[N<<1|1], *g[N], *ce = me;
#define adde(a, b) (ce->t = b, ce->n = g[a], g[a] = ce++)
struct quy{int x, y, t, id, lca;} Q[N];
struct chg{int x, y, pre;} P[N];
int in[N], ou[N], son[N], fa[N], tp[N], dep[N], dfn, _Q, _P, bel[N<<1|1], block, que[N<<1|1];
int V[N], W[N], C[N], col[N], cnt[N]; long long ANS[N], ans;
bool mark[N];
bool operator < (const quy &a, const quy &b) {
	
	if (bel[a.x] ^ bel[b.x]) return bel[a.x] < bel[b.x];
	if (bel[a.y] ^ bel[b.y]) return bel[a.y] < bel[b.y];
	return a.t < b.t;
	
	//return bel[a.x]==bel[b.x]?(bel[a.y]==bel[b.y]?a.t<b.t:bel[a.y]<bel[b.y]):bel[a.x]<bel[b.x];
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
inline void rev(const int &u) {
	if (mark[u]) ans -= (long long)V[C[u]] * W[cnt[C[u]]--];
	else ans += (long long)V[C[u]] * W[++cnt[C[u]]];
	mark[u] ^= 1;
}
inline void upd(const int &u, const int &nc) {
	if (mark[u]) rev(u), C[u] = nc, rev(u);
	else C[u] = nc;
}
inline void timetravel(int &ct, const int &target) {
	wlp (ct < target) ++ct, upd(P[ct].x, P[ct].y);
	wlp (target < ct) upd(P[ct].x, P[ct].pre), --ct;
}
int main() {
	//freopen("58.in", "r", stdin);
	//freopen("58.out", "w", stdout);
	int n, m, q, x, y, ct, type, l, r, _l, _r;
	gi(n), gi(m), gi(q);
	rep(i, 1, m) gi(V[i]);
	rep(i, 1, n) gi(W[i]);
	rep(i, 2, n) {
		gi(x), gi(y);
		adde(x, y);
		adde(y, x);
	}
	rep(i, 1, n) gi(C[i]), col[i] = C[i];
	d1(n, 0); d2(n, n);
	block = pow(dfn, 2.0 / 3) * 0.5 + 1e-3;
	if (!block) block = 1;
	rep(i, 1, dfn) bel[i] = (i - 1) / block;
	rep(i, 1, q)
		if (gi(type), gi(x), gi(y), type) {
			ct = LCA(x, y);
			if (in[y] < in[x]) std::swap(x, y);
			if (ct ^ x) Q[_Q] = (quy) {ou[x], in[y], _P, _Q, ct};
			else Q[_Q] = (quy) {in[x], in[y], _P, _Q, 0};
			++_Q;
		} else {
			P[++_P] = (chg) {x, y, col[x]};
			col[x] = y;
		}
	std::sort(Q, Q + _Q);
	l = 1, r = 0, ct = 0;
	for (int i = 0; i < _Q; ++i) {
		_l = Q[i].x, _r = Q[i].y;
		timetravel(ct, Q[i].t);
		wlp (l < _l) rev(que[l++]);
		wlp (l > _l) rev(que[--l]);
		wlp (r < _r) rev(que[++r]);
		wlp (r > _r) rev(que[r--]);
		if (Q[i].lca) rev(Q[i].lca);
		ANS[Q[i].id] = ans;
		if (Q[i].lca) rev(Q[i].lca);
	}
	for (int i = 0; i < _Q; ++i) printf("%lld\n", ANS[i]);
	return 0;
}
