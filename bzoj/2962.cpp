#include <cstdio>
#include <cstring>
 
const int mo = 19940417, N = 150009;
 
inline char gc() {
    static char buffer[1<<16], *s = buffer, *e = buffer;
    if (s == e) e = (s = buffer) + fread(buffer, 1, 1<<16, stdin);
    return *s++;
}
 
inline int gi() {
    static int a; static char c, f;
    for (f = 0; (c = gc()) < '0'; f |= c == '-');
    for (a = c - '0'; '-' < (c = gc()); a = (a << 3) + (a << 1) + c - '0');
    return f ? -a : a;
}
 
inline void mov(int &a, int b) {
    a += b;
    if (a >= mo) a -= mo;
}
 
int lazy[N], C[N][21], size[N], c[N][21];
bool rev[N];
 
inline void mul(int *a, int *x, const int *y) {
    static int i, j;
    for (i = 1; i < 21; ++i) {
        a[i] = 0;
        for (j = 1; j < i; ++j)
            mov(a[i], (long long)x[j] * y[i - j] % mo);
        mov(a[i], x[i]);
        mov(a[i], y[i]);
    }
}
 
inline void modify(const int &u, const int &val) {
    static int i, j, x, *a;
    mov(lazy[u], val);
    for (a = c[u], i = 20; i; --i) {
        for (x = val, j = i - 1; j; --j, x = (long long)x * val % mo)
            mov(a[i], (long long)x * a[j] % mo * C[size[u] - j][i - j] % mo);
        mov(a[i], (long long)x * C[size[u]][i] % mo);
    }
}
 
inline void Switch(const int &u) {
    static int i, *a;
    rev[u] ^= 1;
    if (lazy[u]) lazy[u] = mo - lazy[u];
    for (i = 19, a = c[u]; ~i; i -= 2)
        if (a[i]) a[i] = mo - a[i];
}
 
void build(int u, int l, int r) {
    size[u] = r - l + 1;
    if (l >= r) return (void)(c[u][1] = gi() % mo);
    int m = l + r >> 1;
    build(u << 1, l, m);
    build(u << 1 | 1, m + 1, r);
    mul(c[u], c[u << 1], c[u << 1 | 1]);
}
 
inline void pd(const int &u) {
    if (rev[u]) Switch(u << 1), Switch(u << 1 | 1), rev[u] = false;
    if (lazy[u]) modify(u << 1, lazy[u]), modify(u << 1 | 1, lazy[u]), lazy[u] = 0;
}
 
void range_add(int u, int l, int r, const int &x, const int &y, const int &delta) {
    if (x <= l && r <= y) return modify(u, delta);
    int m = l + r >> 1; pd(u);
    if (x <= m) range_add(u << 1, l, m, x, y, delta);
    if (y >  m) range_add(u << 1 | 1, m + 1, r, x, y, delta);
    mul(c[u], c[u << 1], c[u << 1 | 1]);
}
 
void range_rev(int u, int l, int r, const int &x, const int &y) {
    if (x <= l && r <= y) return Switch(u);
    int m = l + r >> 1; pd(u);
    if (x <= m) range_rev(u << 1, l, m, x, y);
    if (y >  m) range_rev(u << 1 | 1, m + 1, r, x, y);
    mul(c[u], c[u << 1], c[u << 1 | 1]);
}
 
void query(int u, int l, int r, const int &x, const int &y, int *res) {
    if (x <= l && r <= y) return (void)memcpy(res, c[u], sizeof c[0]);
    int m = l + r >> 1; pd(u);
    if (y <= m) return query(u << 1, l, m, x, y, res);
    if (x >  m) return query(u << 1 | 1, m + 1, r, x, y, res);
    int a[21], b[21], i, j;
    query(u << 1, l, m, x, y, a);
    query(u << 1 | 1, m + 1, r, x, y, b);
    for (i = 1; i < 21; ++i) {
        res[i] = a[i] + b[i];
        if (res[i] >= mo) res[i] -= mo;
        for (j = 1; j < i; ++j)
            mov(res[i], (long long)a[j] * b[i - j] % mo);
    }
}
 
int main() {
    int n = gi(), m = gi(), i, j, x, y, z, a[21];
    register char ch;
    for (i = 0; i <= n; ++i)
        for (C[i][0] = j = 1; j < 21 && j <= i; ++j)
            for (C[i][j] = C[i - 1][j] + C[i - 1][j - 1]; C[i][j] >= mo; C[i][j] -= mo);
    build(1, 1, n);
    while (m--) {
        do ch = gc(); while(ch < 'A' || ch > 'Z');
        x = gi(), y = gi();
        if (ch == 'I') {
            z = gi() % mo;
            if (z < 0) z += mo;
            range_add(1, 1, n, x, y, z);
        } else if (ch == 'R') range_rev(1, 1, n, x, y);
        else {
            z = gi();
            query(1, 1, n, x, y, a);
            printf("%d\n", a[z]);
        }
    }
    return 0;
}
