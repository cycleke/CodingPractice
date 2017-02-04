#include <cmath>
#include <cstdio>
#include <algorithm>
 
inline char gc() {
    static char b[1 << 16], *s = b, *e = b;
    if (s == e) e = (s = b) + fread(b, 1, 1 << 16, stdin);
    return (s == e) ? EOF : *s++;
}
 
inline void gi(int &a) {
    static char c;
    while (c = gc(), c < '0'); a = c - '0';
    while (c = gc(), '-' < c) a = (a << 3) + (a << 1) + c - '0';
}
 
#define N 20005
#define SIZE 145
 
int C[SIZE][N], rk[N], h[N], n;
inline void Add(int *tr, int x, const int &val) {
    for (; x <= ::n; x += x & -x)
        tr[x] += val;
}
inline int Sum(int *tr, int x) {
    static int ret;
    for (ret = 0; x; x -= x & -x)
        ret += tr[x];
    return ret;
}
 
inline bool cmp(const int &a, const int &b) {
    return ::h[a] < ::h[b];
}
 
#define belong(pos) ((pos - 1) / block)
 
int main() {
    int m, block, i, j, last, tot = 0, idx, idy, x, y;
    gi(::n);
    block = sqrt(::n) + 0.5;
    for (i = 1; i <= ::n; ++i)
        gi(::h[i]), ::rk[i] = i;
    std::sort(::rk + 1, ::rk + ::n + 1, cmp);
    last = ::h[::rk[1]];
    ::h[::rk[1]] = j = 1;
    ::rk[1] = 0;
    for (i = 2; i <= ::n; ++i) {
        if (::h[::rk[i]] ^ last) last = ::h[::rk[i]], ++j;
        ::h[::rk[i]] = j;
        ::rk[i] = 0;
    }
 
    i = ::n;
    ::n = j;
     
    for (; i; --i) {
        tot += Sum(::rk, ::h[i] - 1);
        Add(::rk, ::h[i], 1);
        Add(::C[belong(i)], ::h[i], 1);
    }
     
    printf("%d\n", tot);
     
    gi(m);
    while (m--) {
        gi(x); gi(y);
        if (x > y) x ^= y ^= x ^= y;
        idx = belong(x) + 1, idy = belong(y) - 1;
        if (idx <= idy) {
            for (i = idx; i <= idy; ++i) {
                tot -= Sum(::C[i], ::h[x] - 1);
                tot += Sum(::C[i], ::n) - Sum(::C[i], ::h[x]);
                tot += Sum(::C[i], ::h[y] - 1);
                tot -= Sum(::C[i], ::n) - Sum(::C[i], ::h[y]);
            }
            for (i = x + 1, j = idx * block + 1; i < j; ++i) {
                tot -= ::h[i] < ::h[x];
                tot += ::h[i] > ::h[x];
                tot += ::h[i] < ::h[y];
                tot -= ::h[i] > ::h[y];
            }
            for (i = (idy + 1) * block + 1; i < y; ++i) {
                tot -= ::h[i] < ::h[x];
                tot += ::h[i] > ::h[x];
                tot += ::h[i] < ::h[y];
                tot -= ::h[i] > ::h[y];
            }
        } else {
            for (i = x + 1; i < y; ++i) {
                tot -= ::h[i] < ::h[x];
                tot += ::h[i] > ::h[x];
                tot += ::h[i] < ::h[y];
                tot -= ::h[i] > ::h[y];
            }
        }
        if (::h[x] < ::h[y]) ++tot;
        else if (::h[x] > ::h[y]) --tot;
        --idx, ++idy;
        Add(::C[idx], ::h[x], -1);
        Add(::C[idy], ::h[y], -1);
        ::h[x] ^= ::h[y] ^= ::h[x] ^= ::h[y];
        Add(::C[idx], ::h[x], 1);
        Add(::C[idy], ::h[y], 1);
 
        printf("%d\n", tot);
    }
    return 0;
}
