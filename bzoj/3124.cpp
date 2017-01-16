#include <cstdio>
inline int gi() {
    static int a; static char c;
    while ((c = getchar()) < '0'); a = c - '0';
    while ('-' < (c = getchar())) a = (a << 3) + (a << 1) + c - '0';
    return a;
}
const int N = 200003;
struct edge {int t, w; edge *n;}me[N<<1|1], *ce = me, *hd[N], *fe[N];
inline void adde(const int &a, const int &b, const int &c) {
    ce->t = b, ce->w = c, ce->n = hd[a], hd[a] = ce++;
}
#define FOR(a,b) for (edge *a = hd[b]; a; a = a->n)
long long mxd;
int p, from[N];
bool mark[N];
void d1(int u, int fa, long long d) {
    if (mxd < d) mxd = d, p = u;
    FOR(it, u) if ((it->t) ^ fa) d1(it->t, u, d + it->w);
}
void d2(int u, int fa, long long d) {
    if (mxd < d) mxd = d, p = u;
    FOR(it, u) if ((it->t) ^ fa) {
        from[it->t] = u, fe[it->t] = it;
        d2(it->t, u, d + it->w);
    }
}
void d3(int u, int fa, long long d) {
    if (mxd < d) mxd = d;
    FOR(it, u) if ((it->t) ^ fa && !mark[it->t]) 
        d3(it->t, u, d + it->w);
}
int main() {
    int n = gi(), i, a, b, c;
    long long nd = 0, t;
    for (i = 1; i < n; ++i) {
        a = gi(), b = gi(), c = gi();
        adde(a, b, c), adde(b, a, c);
    }
    mxd = -1LL;
    d1(1, 0, 0LL);
    mxd = -1LL;
    a = p;
    d2(a, 0, 0LL);
    printf("%lld\n", mxd);
    t = mxd;
    mark[a] = mark[p] = 1;
    for (edge *it = fe[p]; it; it = fe[from[it->t]])
        mark[it->t] = 1;
    a = c = 0;
    for (edge *it = fe[p]; it; it = fe[from[it->t]]) {
        ++c;
        mxd = -1LL;
        d3(from[it->t], 0, 0);
        nd += it->w;
        if (nd == mxd) a = c;
        if (nd + mxd == t) break;
    }
    a = c - a;
    printf("%d\n", a);
    return 0;
}
