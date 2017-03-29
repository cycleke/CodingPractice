#include <cstdio>

const int maxr(325), maxn(1e5 + 7);
typedef int arr[maxn];

inline int rd() {
    static int r = 19260817;
    return r = (r * 69069LL + 1) & (~0U >> 1);
}

struct bitset {
    int max;
    unsigned long long a[469];
    inline void clear() {
        for (register int i = 0; i <= max; ++i)
            a[i] = 0ULL;
        max = 0;
    }
    inline void operator |= (const bitset &lambda) {
        if (lambda.max > max)
            max = lambda.max;
        for (register int i = 0; i <= max; ++i)
            a[i] |= lambda.a[i];
    }
    inline void operator |= (const int &lambda) {
        a[lambda >> 6] |= 1ULL << (lambda & 63);
        if ((lambda >> 6) > max)
            max = lambda >> 6;
    }
    inline int count(unsigned long long x) const {
        int ret = 0;
        for (; x; x &= x - 1)
            ++ret;
        return ret;
    }
    inline int count() const {
        int ret = 0;
        for (register int i = 0; i <= max; ++i)
            ret += count(a[i]);
        return ret;
    }
    inline int mex() const {
        for (register int i = 0; i <= max; ++i)
            if (count(a[i]) < 64) {
                for (register int j = 0; j < 64; ++j)
                    if (~a[i] >> j & 1)
                        return (i << 6) | j;
            }
        return (max + 1) << 6;
    }
} temp, pre[maxr][maxr];

struct edge {
    int to;
    edge *nxt;
} *g[maxn];

inline void add_edge(int u, int v) {
    static edge edge_mest[maxn * 2], *cedge = edge_mest;
    *cedge = (edge) {v, g[u]};
    g[u] = cedge++;
}

arr dep, top, fa, son, size;

void d1(int u) {
    size[u] = 1;
    for (edge *it = g[u]; it; it = it->nxt)
        if (it->to ^ fa[u]) {
            fa[it->to] = u;
            dep[it->to] = dep[u] + 1;
            d1(it->to);
            if (size[it->to] > size[son[u]])
                son[u] = it->to;
            size[u] += size[it->to];
        }
}

void d2(int u, int anc) {
    top[u] = anc;
    if (son[u]) d2(son[u], anc);
    for (edge *it = g[u]; it; it = it->nxt)
        if (!top[it->to]) d2(it->to, it->to);
}

inline int lca(int u, int v) {
    while (top[u] ^ top[v]) dep[top[u]] < dep[top[v]] ? v = fa[top[v]] : u = fa[top[u]];
    return dep[u] < dep[v] ? u : v;
}

inline void swap(int &a, int &b) {
    a ^= b ^= a ^= b;
}

arr val, tag, rand_arr, up;

int main() {

#ifndef ONLINE_JUDGE
    freopen("xuehui.in", "r", stdin);
#endif

    int n, m, f, lastans = 0, u, v, t, rand_num, a, anc;
    scanf("%d%d%d", &n, &m, &f);

    for (register int i = 1; i <= n; ++i)
        scanf("%d", val + i);

    for (register int i = 1; i <  n; ++i) {
        scanf("%d%d", &u, &v);
        add_edge(u, v);
        add_edge(v, u);
    }


    dep[1] = 1;
    d1(1);
    d2(1, 1);

    for (register int i = 1; i <= n; ++i) rand_arr[i] = i;
    for (rand_num = 1; rand_num * rand_num <= n; ++rand_num);
    for (register int i = 1; i <= n; ++i) swap(rand_arr[rd() % n + 1], rand_arr[rd() % n + 1]);
    for (register int i = 1; i <= rand_num; ++i) tag[rand_arr[i]] = i;

    for (register int i = 1; i <= rand_num; ++i) {
        u = rand_arr[i];
        temp.clear();
        while (u) {
            temp |= val[u];
            if (u != rand_arr[i] && tag[u]) {
                pre[i][tag[u]] = temp;
                if (!up[rand_arr[i]])
                    up[rand_arr[i]] = u;
            }
            u = fa[u];
        }
    }

    while (m--) {
        scanf("%d", &a);
        temp.clear();
        while (a--) {
            scanf("%d%d", &u, &v);
            if (f) u ^= lastans, v ^= lastans;
            anc = lca(u, v);
            temp |= val[anc];
            for (; !tag[u] && u != anc; u = fa[u])
                temp |= val[u];
            t = u;
            while (dep[up[u]] >= dep[anc])
                u = up[u];
            temp |= pre[tag[t]][tag[u]];
            for (; u != anc; u = fa[u])
                temp |= val[u];

            for (; !tag[v] && v != anc; v = fa[v])
                temp |= val[v];
            t = v;
            while (dep[up[v]] >= dep[anc])
                v = up[v];
            temp |= pre[tag[t]][tag[v]];
            for (; v != anc; v = fa[v])
                temp |= val[v];

            //t = temp.count();
            //lastans = temp.mex();
            //printf("%d %d\n", t, lastans);
            //lastans += t;
        }
        t = temp.count();
        lastans = temp.mex();
        printf("%d %d\n", t, lastans);
        lastans += t;
    }

    return 0;
}
