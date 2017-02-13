#include <bits/stdc++.h>
inline void gi(int &a) {
    static char c;
    while (c = getchar(), c < '0'); a = c - '0';
    while (c = getchar(), '-' < c) a = (a << 3) + (a << 1) + c - '0';
}
 
#define N 50003
#define M 100003
int fa[N], sz[N], ma[N], mb[N];
inline int gf(int u) {
    while (fa[u] ^ u) u = fa[u];
    return u;
}
bool ans[N];
struct Data {
    int u, v, a, b, id;
    void Input(const int &i) {
        gi(u), gi(v), gi(a), gi(b), id = i;
    }
}edge[M], qu[N], tq[N];
bool cpa(const Data &a, const Data &b) {
    return (a.a ^ b.a) ? a.a < b.a : a.b < b.b;
}
bool operator < (const Data &a, const Data &b) {
    return (a.b ^ b.b) ? a.b < b.b : a.a < b.a;
}
struct Opt {
    int u, v, sz, ma, mb;
}stk[M], *tp = stk;
 
inline void cmax(int &a, const int &b) {
    if (a < b) a = b;
}
 
inline void merge(int u, int v, int a, int b) {
    u = gf(u), v = gf(v);
    if (sz[v] < sz[u]) std::swap(u, v);
    *++tp = (Opt) {u, v, sz[v], ma[v], mb[v]};
    if (u ^ v) {
        fa[u] = v;
        sz[v] += sz[u];
        cmax(ma[v], std::max(a, ma[u]));
        cmax(mb[v], std::max(b, mb[u]));
    } else cmax(ma[v], a), cmax(mb[v], b);
}
 
inline void undo() {
    for (; stk < tp; --tp) {
        fa[tp->u] = tp->u;
        sz[tp->v] = tp->sz;
        ma[tp->v] = tp->ma;
        mb[tp->v] = tp->mb;
    }
}
 
int main() {
    int n, m, rm, q, i, j, k, p, tot, u, v;
    gi(n), gi(m); rm = sqrt(m);
 
    for (i = 1; i <= m; ++i)
        edge[i].Input(i);
    std::sort(edge + 1, edge + m + 1, cpa);
 
    gi(q);
    for (i = 1; i <= q; ++i)
        qu[i].Input(i);
    std::sort(qu + 1, qu + q + 1);
 
    for (i = 1; i <= m; i += rm) {
        tot = 0;
        for (j = 1; j <= q; ++j)
            if (edge[i].a <= qu[j].a && (i + rm > m || qu[j].a < edge[i + rm].a))
                tq[++tot] = qu[j];
        std::sort(edge + 1, edge + i);
        for (j = 1; j <= n; ++j)
            fa[j] = j, sz[j] = 1, ma[j] = mb[j] = -1;
        for (j = k = 1; j <= tot; ++j) {
            for (; k < i && edge[k].b <= tq[j].b; ++k)
                merge(edge[k].u, edge[k].v, edge[k].a, edge[k].b);
            tp = stk;
            for (p = i; p < i + rm && p <= m; ++p)
                if (edge[p].a <= tq[j].a && edge[p].b <= tq[j].b)
                    merge(edge[p].u, edge[p].v, edge[p].a, edge[p].b);
            u = gf(tq[j].u), v = gf(tq[j].v);
            ans[tq[j].id] = (u == v && ma[u] == tq[j].a && mb[u] == tq[j].b);
            undo();
        }
    }
    for (i = 1; i <= q; ++i)
        puts(ans[i] ? "Yes" : "No");
    return 0;
}
