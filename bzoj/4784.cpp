#include <cstdio>
#include <cstring>

const int maxn(5e5 + 7), maxm(2e6 + 7), mod(998244353);

struct edge {
    int to;
    edge *nxt;
} edge_mset[maxm], *g[maxn], *cedge;

inline void add_edge(int u, int v) {
    *cedge = (edge) {v, g[u]};
    g[u] = cedge++;
}

int f[maxn], d[maxn], dfn[maxn], fa[maxn], vis[maxn], _dfn;

bool dfs(int u) {
    dfn[u] = ++_dfn;
    for (edge *it = g[u]; it; it = it->nxt)
        if (!dfn[it->to]) {
            fa[it->to] = u;
            if (dfs(it->to))
                return true;
        } else if (dfn[it->to] > dfn[u]) {
            d[u] -= 2;
            for (int v = it->to; u ^ v; d[v] -= 2, vis[v] = 1, v = fa[v])
                if (vis[v]) return true;
        }
    return false;
}

int main() {
    int o_o, n, m, ans, u, v;
    scanf("%d", &o_o);
    f[0] = f[1] = 1;
    for (register int i = 2; i < maxn; ++i) f[i] = ((i - 1ll) * f[i - 2] + f[i - 1]) % mod;
    while (o_o--) {
        scanf("%d%d", &n, &m);
        for (register int i = 1; i <= n; ++i)
            g[i] = NULL, d[i] = dfn[i] = fa[i] = vis[i] = 0;

        cedge = edge_mset;

        while (m--) {
            scanf("%d%d", &u, &v);
            add_edge(u, v), add_edge(v, u);
            ++d[u];
            ++d[v];
        }
        _dfn = 0;
        if (dfs(1))
            puts("0");
        else {
            ans = 1;
            for (register int i = 1; i <= n; ++i)
                ans = 1ll * ans * f[d[i]] % mod;
            printf("%d\n", ans);
        }

    }
    return 0;
}
