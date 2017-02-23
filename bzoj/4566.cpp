#include <cstdio>
#include <cstring>
#include <algorithm>
#define rep(i, n) for (i = 0; i < (n); ++i)
#define Rep(i, n) for (i = 1; i < (n); ++i)
#define rrp(i, n) for (i = n - 1; ~i; --i)
const int MaxN = 400010;
typedef int arr[MaxN], _;
_ n, len[2];
char ts[MaxN];
long long ans;
arr sa, ws, wv, ta, tb, rk, hi, fa, st, en, a, s;
#define rx(a) ((a) >= n ? -1 : r[a])
inline bool cmp(int *r, int i, int j, int l) {
    return r[i] == r[j] && rx(i + l) == rx(j + l);
}
inline void da() {
    _ i, j, p, *x = ta, *y = tb, *t, m = 28;
    rep(i, m) ws[i] = 0;
    rep(i, n) ++ws[x[i] = s[i]];
    Rep(i, m) ws[i] += ws[i - 1];
    rrp(i, n) sa[--ws[x[i]]] = i;
    for (p = j = 1; p < n; j <<= 1, m = p) {
        for (p = 0, i = n - j; i < n; ++i) y[p++] = i;
        rep(i, n) if (sa[i] >= j) y[p++] = sa[i] - j;
        rep(i, m) ws[i] = 0;
        rep(i, n) ++ws[wv[i] = x[y[i]]];
        Rep(i, m) ws[i] += ws[i - 1];
        rrp(i, n) sa[--ws[wv[i]]] = y[i];
        for (t = x, x = y, y = t, p = i = 1, x[sa[0]] = 0; i < n; ++i)
            x[sa[i]] = cmp(y, sa[i], sa[i - 1], j) ? p - 1 : p++;
    }
}
inline void calcheight() {
    _ i, j, k;
    rep(i, n) rk[sa[i]] = i;
    for (i = k = 0; i < n; hi[rk[i++]] = k) {
        if (!rk[i]) continue;
        k ? --k : 0;
        for (j = sa[rk[i] - 1]; s[i + k] == s[j + k]; ++k);
    }
}
int gf(_ u) {
    return fa[u] == u ? u : fa[u] = gf(fa[u]);
}
inline void calc(const _ &x) {
    if (!x) return;
    _ r1 = gf(x), r2 = gf(x - 1);
    ans += (long long)(st[r1] * en[r2] + st[r2] * en[r1]) * hi[x];
    st[r1] += st[r2], en[r1] += en[r2], fa[r2] = r1;
}
inline bool _cmp(const _ &a, const _ &b) {
    return hi[a] > hi[b];
}
int main() {
    _ i;
    scanf("%s", ts);
    len[0] = strlen(ts);
    rep(i, len[0]) s[i] = ts[i] - 'a' + 1;
    s[len[0]] = 27;
    scanf("%s", ts);
    len[1] = strlen(ts);
    rep(i, len[1]) s[i + len[0] + 1] = ts[i] - 'a' + 1;
    n = len[0] + len[1] + 1;
    da();
    calcheight();
    rep(i, n) {
        a[i] = fa[i] = i;
        st[i] = (sa[i] < len[0]);
        en[i] = st[i] ^ 1;
    }
    std::sort(a, a + n, _cmp);
    rep(i, n) calc(a[i]);
    printf("%lld\n", ans);
    return 0;
}
