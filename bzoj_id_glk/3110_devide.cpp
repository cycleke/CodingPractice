#include <cstdio>
int Ina; char Inc; bool InSign;
inline int geti() {
    InSign = false;
    while (Inc = getchar(), Inc < '0' || Inc > '9') InSign |= Inc == '-';
    Ina = Inc - '0';
    while (Inc = getchar(), Inc >= '0' && Inc <= '9') Ina = (Ina << 3) + (Ina << 1) + Inc - '0';
    if (InSign) Ina = -Ina;
    return Ina;
}
typedef long long LL;
const int Maxn = 50000 + 5;
LL C1[2][Maxn], C2[2][Maxn], c[Maxn];
int type[Maxn], a[Maxn], b[Maxn], t1[Maxn], t2[Maxn], t[Maxn], ans[Maxn], Tim;
void Add(LL tt[2][Maxn], int x, LL val) {
    while (x < Maxn) {
        if (tt[0][x] ^ Tim) tt[0][x] = Tim, tt[1][x] = val;
        else tt[1][x] += val;
        x += x & -x;
    }
}
void Add(int x, LL val) { Add(C1, x, val); Add(C2, x, x * val); }
void Update(int l, int r, LL val) { Add(l, val); Add(r + 1, -val); }
 
LL Sum(LL tt[2][Maxn], int x) {
    LL ret = 0;
    while (x) {
        if (tt[0][x] >= Tim) ret += tt[1][x];
        x -= x & -x;
    }
    return ret;
}
LL Sum(const int &x) { return (x + 1)  * Sum(C1, x) - Sum(C2, x);}
LL Query(const int &l, const int &r) { return Sum(r) - Sum(l - 1); }
 
void Solve(int x, int y, int l, int r) {
    if (x > y) return;
    if (l == r) {
        for (int i = x; i <= y; ++i)
            if (type[t[i]] > 1) ans[t[i]] = l;
        return;
    }
    int mid = (l + r) >> 1; ++Tim; LL tmp;
    t1[0] = t2[0] = 0;
    for (int i = x; i <= y; ++i)
        if (type[t[i]] == 1) {
            if (c[t[i]] <= mid) t1[++t1[0]] = t[i];
            else t2[++t2[0]] = t[i], Update(a[t[i]], b[t[i]], 1);
        } else {
            if ((tmp = Query(a[t[i]], b[t[i]])) < c[t[i]]) c[t[i]] -= tmp, t1[++t1[0]] = t[i];
            else t2[++t2[0]] = t[i];
        }
    int midd = x + t1[0] - 1;
    for (int i = x; i <= midd; ++i) t[i] = t1[i - x + 1];
    for (int i = midd + 1; i <= y; ++i) t[i] = t2[i - midd];
    Solve(x, midd, l, mid); Solve(midd+1, y, mid + 1, r);
}
 
int main() {
    int n = geti(), m= geti();
    for (int i = 1; i <= m; ++i) {
        type[i] = geti(), a[i] = geti(), b[i] = geti(), c[i] = geti(); t[i] = i;
    }
    Solve(1, m, 1, n);
    for (int i = 1; i <= m; ++i)
        if (type[i] > 1) printf("%d\n", ans[i]);
    return 0;
}
