#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
inline bool nn(const char &a) {return a < '0' || '9' < a;}
inline int gi() {
    static int a; static char c, f;
    for (f = 0; nn(c = getchar()); f|= c == '-');
    for (a = c - '0'; !nn(c = getchar()); a = (a << 3) + (a << 1) + c - '0');
    return f ? -a : a;
}
typedef int arr[500009];
arr pre, ch[2], key, sum, size, lx, rx, mx, trash, a;
bool same[500009], rev[500009];
int rt, tot, cnttrash;
int newnode(int v, int fa) {
    static int r;
    if (cnttrash) r = trash[cnttrash--];
    else r = ++tot;
    pre[r] = fa;
    ch[0][r] = ch[1][r] = 0;
    lx[r] = rx[r] = max(0,v);
    mx[r] = key[r] = sum[r] = v;
    same[r] = rev[r] = 0;
    size[r] = 1;
    return r;
}
void pushup(int u) {
    static int ls, rs;
    ls = ch[0][u], rs = ch[1][u];
    sum[u] = sum[ls] + sum[rs] + key[u];
    size[u] = size[ls] + size[rs] + 1;
    lx[u] = max(lx[ls], sum[ls] + key[u] + lx[rs]);
    rx[u] = max(rx[rs], sum[rs] + key[u] + rx[ls]);
    mx[u] = rx[ls] + key[u] + lx[rs];
    if (ls) mx[u] = max(mx[u], mx[ls]);
    if (rs) mx[u] = max(mx[u], mx[rs]);
}
void change_value(int u, int v) {
    key[u] = v;
    sum[u] = size[u] * v;
    mx[u] = max(v, sum[u]);
    lx[u] = rx[u] = max(0,sum[u]);
    same[u] = 1;
}
void make_rev(int u) {
    swap(ch[0][u], ch[1][u]);
    swap(lx[u], rx[u]);
    rev[u] ^= 1;
}
void pushdown(int u) {
    if (same[u]) {
        if (ch[0][u]) change_value(ch[0][u], key[u]);
        if (ch[1][u]) change_value(ch[1][u], key[u]);
        same[u] = 0;
    }
    if (rev[u]) {
        if (ch[0][u]) make_rev(ch[0][u]);
        if (ch[1][u]) make_rev(ch[1][u]);
        rev[u] = 0;
    }
}
bool type(int u) {return ch[1][pre[u]] == u;}
void rot(int u) {
    static int o, d;
    pushdown(o); pushdown(u);
    o = pre[u], d = type(u);
    if (ch[d][o] = ch[d^1][u]) pre[ch[d][o]] = o;
    if (pre[u] = pre[o]) ch[type(o)][pre[o]] = u;
    pre[o] = u, ch[d^1][u] = o;
    pushup(o); pushup(u);
}
void splay(int u, int target) {
    static int f;
    for (; pre[u] ^ target; rot(u))
        if (pre[f = pre[u]] ^ target) rot((type(u)^type(f))?u:f);
    if (!target) rt = u;
}
int kth(int k) {
    static int u, t;
    for (u = rt; u;) {
        pushdown(u);
        t = size[ch[0][u]] + 1;
        if (t < k) k -= t, u = ch[1][u];
        else if (k < t) u = ch[0][u];
        else return u;
    }
}
void build(int &u, int l, int r, int fa) {
    if (l > r) return;
    int m = l + r >> 1;
    u = newnode(a[m], fa);
    build(ch[0][u], l, m - 1, u);
    build(ch[1][u], m + 1, r, u);
    pushup(u);
}
void erase(int u) {
    if (!u) return;
    erase(ch[0][u]);
    erase(ch[1][u]);
    trash[++cnttrash] = u;
}
void grange(int l, int r) {
    splay(kth(l), 0); splay(kth(r), rt);
}
void PRINT(int u) {
    if (!u) return;
    pushdown(u);
    printf("u = %3d sum = %3d key = %3d mx = %3d ls = %3d rs = %3d lx = %3d rx = %3d\n", u, sum[u], key[u], mx[u], ch[0][u], ch[1][u], lx[u], rx[u]);
    PRINT(ch[0][u]);
    PRINT(ch[1][u]);
}
int main() {
//    freopen("t.in", "r", stdin);
//    freopen("t.out", "w", stdout);
    int n, m, i, pos, tot;
    char op[20];
    n = gi(), m = gi();
    for (i = 1; i <= n; ++i) a[i] = gi();
    build(rt, 0, n + 1, 0);
    while (m--) {
        scanf("%s", op);
        if (*op == 'I') {
            pos = gi(), tot = gi();
            grange(pos + 1, pos + 2);
            for (i = 0; i < tot; ++i) a[i] = gi();
            build(ch[0][ch[1][rt]], 0, tot - 1, ch[1][rt]);
            pushup(ch[1][rt]); pushup(rt);
        } else if (*op == 'D' ) {
            pos = gi(), tot = gi();
            grange(pos, pos + tot + 1);
            erase(ch[0][ch[1][rt]]);
            ch[0][ch[1][rt]] = 0;
            pushup(ch[1][rt]); pushup(rt);
        } else if (*op == 'M') {
            if (op[2] == 'K') {
                pos = gi(), tot = gi();
                grange(pos, pos + tot + 1);
                change_value(ch[0][ch[1][rt]], gi());
                pushup(ch[1][rt]); pushup(rt);
            } else {
                grange(1, size[rt]);
                printf("%d\n", mx[ch[0][ch[1][rt]]]);
            }
        } else if (*op == 'R') {
            pos = gi(), tot = gi();
            grange(pos, pos + tot + 1);
            make_rev(ch[0][ch[1][rt]]);
            pushup(ch[1][rt]); pushup(rt);
        } else {
            pos = gi(), tot = gi();
            grange(pos, pos + tot + 1);
            printf("%d\n", sum[ch[0][ch[1][rt]]]);
        }
        //puts("\n-----------------");
        //PRINT(rt); puts("");
    }
    return 0;
}
