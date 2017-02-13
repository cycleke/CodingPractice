#include <bits/stdc++.h>
using namespace std;
#define N 100003
#define wlp while
#define rep(i, l, r) for (register int i = l; i <= r; ++i)
 
template<class integer>
inline void gi(integer &a) {
    static char c;
    wlp (c = getchar(), c < '0'); a = c - '0';
    wlp (c = getchar(), '-' < c) a = (a << 3) + (a << 1) + c - '0';
}
 
struct heap {
    priority_queue<int> a, b;
    void erase(const int &x) {
        b.push(x);
    }
    int top() {
        wlp (!b.empty() && a.top() == b.top()) {
            a.pop();
            b.pop();
        }
        return a.top();
    }
    void push(const int &x) {
        a.push(x);
    }
    heap() {
        a.push(-1);
    }
}hp[N<<2|1];
 
struct event {
    int a, b, v;
}a[N];
 
struct edge {
    int t;
    edge *n;
}me[N<<1|1], *ce = me, *g[N];
#define adde(a, b) (*ce = (edge){b, g[a]}, g[a] = ce++)
#define FOR(a, b) for (edge *a = g[b]; a; a = a->n)
int fa[N], son[N], tp[N], dep[N], dfn[N], _dfn;
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
    dfn[u] = ++_dfn;
    tp[u] = anc;
    if (son[u]) d2(son[u], anc);
    FOR(it, u) if (!tp[it->t]) d2(it->t, it->t);
}
 
#define ls u<<1
#define rs u<<1|1
void upd(int u, int l, int r, const int &x, const int &y, const int &v, const bool &flag) {
    if (x <= l && r <= y) 
        return flag ? hp[u].push(v) : hp[u].erase(v);
    int m = l + r >> 1;
    if (x <= m) upd(ls, l, m, x, y, v, flag);
    if (y >  m) upd(rs, m + 1, r, x, y, v, flag);
}
 
int quy(const int &p) {
    static int u, l, r, v, t, m;
    for (u = 1, l = 1, r = _dfn, v = -1; l ^ r; ) {
        if (v < (t = hp[u].top())) v = t;
        m = l + r >> 1;
        if (p <= m) u = ls, r = m;
        else u = rs, l = m + 1;
    }
    if (v < (t = hp[u].top())) v = t;
    return v;
}
 
pair<int, int>sg[N];
inline void modify(int u, int v, const int &val, const bool &flag) {
    static int cnt, i, l, r, pre;
    for (cnt = 0; tp[u] ^ tp[v];)
        if (dep[tp[u]] < dep[tp[v]]) {
            sg[cnt++] = pair<int, int>(dfn[tp[v]], dfn[v]);
            v = fa[tp[v]];
        } else {
            sg[cnt++] = pair<int, int>(dfn[tp[u]], dfn[u]);
            u = fa[tp[u]];
        }
    if (dep[u] < dep[v]) u ^= v ^= u ^= v;
    sg[cnt++] = pair<int, int>(dfn[v], dfn[u]);
    sort(sg, sg + cnt);
    pre = 0;
    for (i = 0; i < cnt; ++i) {
        l = pre + 1;
        r = sg[i].first - 1;
        pre = sg[i].second;
        if (l <= r) upd(1, 1, _dfn, l, r, val, flag);
    }
    if (pre ^ _dfn) upd(1, 1, _dfn, pre + 1, _dfn, val, flag);
}
 
int main() {
    int n, m, u, v, type, x;
    gi(n), gi(m);
    rep(i, 2, n) {
        gi(u), gi(v);
        adde(u, v);
        adde(v, u);
    }
    d1(1); d2(1, 1);
    rep(i, 1, m) {
        gi(type);
        if (!type) {
            gi(u), gi(v), gi(x);
            a[i] = (event) {u, v, x};
            modify(u, v, x, true);
        } else if (type & 1) {
            gi(x);
            modify(a[x].a, a[x].b, a[x].v, false);
        } else gi(x), printf("%d\n", quy(dfn[x]));
    }
    return 0;
}
