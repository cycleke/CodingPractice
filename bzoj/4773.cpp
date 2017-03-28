#include <cstdio>
#include <cstring>

int f[302][302], g[302][302];

inline void cmin(int &a, const int &b) {
    if (b < a) a = b;
}

struct edge {
    int to, cost;
    edge *nxt;
} e[302 * 302], *h[302];

int main() {

    int n, m, u, v, w;

    memset(f, 63, sizeof f);

    scanf("%d%d", &n, &m);

    for (register int i = 0; i < m; ++i) {
        scanf("%d%d%d", &u, &v, &w);
        e[i] = (edge) {v, w, h[u]};
        h[u] = e + i;
    }

    for (register int i = 1; i <= n; ++i)
        f[i][i] = 0;

    for (register int step = 1; step <= n; ++step) {
        memcpy(g, f, sizeof g);
        for (register int s = 1; s <= n; ++s)
            for (register int stop = 1; stop <= n; ++stop)
                for (edge *it = h[stop]; it; it = it->nxt)
                    cmin(g[s][it->to], f[s][stop] + it->cost);
        memcpy(f, g, sizeof f);
        for (register int i = 1; i <= n; ++i)
            if (f[i][i] < 0)
                return printf("%d\n", step), 0;
    }
    puts("0");
    return 0;
}
