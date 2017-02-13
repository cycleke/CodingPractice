#include <bits/stdc++.h>
using namespace std;
#define N 200003
#define wlp while
#define rep(i, l, r) for (register int i = l; i <= r; ++i)
 
template<class integer>
inline void gi(integer &a) {
    static char c;
    wlp (c = getchar(), c < '0'); a = c - '0';
    wlp (c = getchar(), '-' < c) a = (a << 3) + (a << 1) + c - '0';
}
 
typedef int arr[N];
arr tp, fa, son, dep, in, ou, tr, ans;
int dfn;
 
struct node {
    int a, b, v, lca;
}a[N];
 
struct opt {
    int type, x, id;
}q[N], tq[N];
 
struct edge {
    int t;
    edge *n;
}me[N<<1|1], *ce = me, *g[N];
#define adde(a, b) (*ce = (edge){b, g[a]}, g[a] = ce++)
#define FOR(a, b) for (edge *a = g[b]; a; a = a->n)
void d1(int u) {
    static int sz[N];
    sz[u] = 1;
    FOR(it, u) if (it->t ^ fa[u]) {
        fa[it->t] = u;
        dep[it->t] = dep[u] + 1;
        d1(it->t);
        if (sz[it->t] > sz[son[u]]) son[u] = it->t;
        sz[u] += sz[it->t];
    }
}
void d2(int u, int anc) {
    in[u] = ++dfn;
    tp[u] = anc;
    if (son[u]) d2(son[u], anc);
    FOR(it, u) if (!tp[it->t]) d2(it->t, it->t);
    ou[u] = dfn;
}
 
inline int Lca(int u, int v) {
    wlp (tp[u] ^ tp[v]) dep[tp[u]] < dep[tp[v]] ? v = fa[tp[v]] : u = fa[tp[u]];
    return dep[u] < dep[v] ? u : v;
}
 
inline void add(int x, const int &delta) {
    for (; x <= dfn; x += x & -x)
        tr[x] += delta;
}
 
inline int sum(int x) {
    static int r;
    for (r = 0; 0 < x; x ^= x & -x)
        r += tr[x];
    return r;
}
 
inline int quy(const int &u) {
    return sum(ou[u]) - sum(in[u] - 1);
}
 
inline void modify(const int &id, const int &delta) {
    add(in[a[id].a], delta);
    add(in[a[id].b], delta);
    add(in[a[id].lca], -delta);
    if (fa[a[id].lca]) add(in[fa[a[id].lca]], -delta);
}
 
void divide(int l, int r, int L, int R) {
    if (L >= R || l > r) {
        rep(i, l, r) 
            if (q[i].type == 2) ans[q[i].id] = L;
        return;
    }
    int mid = L + R >> 1, it = l - 1, cnt = 0, _t = 0, t;
    rep(i, l, r) 
        if (q[i].type == 2) (quy(q[i].x) ^ _t) ? tq[++cnt] = q[i] : q[++it] = q[i];
        else {
            t = q[i].type ? -1 : 1;
            if (a[q[i].x].v <= mid) q[++it] = q[i];
            else {
                tq[++cnt] = q[i];
                _t += t;
                modify(q[i].x, t);
            }
        }
    rep(i, 1, cnt) {
        if (tq[i].type ^ 2) {
            t = tq[i].type ? 1 : -1;
            modify(tq[i].x, t);
        }
        q[i + it] = tq[i];
    }
    divide(l, it, L, mid);
    divide(it + 1, r, mid + 1, R);
}
 
int main() {
    int n, m, u, v, mx = -1;
    gi(n), gi(m);
    rep(i, 2, n) {
        gi(u), gi(v);
        adde(u, v);
        adde(v, u);
    }
    d1(1);
    d2(1, 1);
    rep(i, 1, m) {
        gi(q[i].type);
        q[i].id = i;
        if (q[i].type) gi(q[i].x);
        else {
            gi(a[i].a), gi(a[i].b), gi(a[i].v);
            a[i].lca = Lca(a[i].a, a[i].b);
            q[i].x = i;
            if (mx < a[i].v) mx = a[i].v;
        }
        ans[i] = -2;
    }
    divide(1, m, -1, mx);
    rep(i, 1, m) 
        if (ans[i] ^ -2) printf("%d\n", ans[i]);
    return 0;
}
