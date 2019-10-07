// by OwenCreeper
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
#define MOD 998244353
#define N 1000000

using namespace std;
typedef long long LL;
LL fpow(LL a, LL n) {
    LL ans = 1, tmp = a;
    while (n) {
        if (n & 1) ans = ans * tmp % MOD;
        tmp = tmp * tmp % MOD;
        n >>= 1;
    }
    return ans;
}
LL r[N + 5], wn[N + 5], tmp[N + 5], a[N + 5], b[N + 5], f[N + 5];
void prework(int n) {
    for (int i = 1, id = 0; i <= n; i <<= 1, id++) wn[id] = fpow(3, (MOD - 1) / i);
    return;
}
void fft(int n, LL *x, bool flag) {
    for (int i = 0, j = 0; i != n; i++) {
        if (i > j) swap(x[i], x[j]);
        for (int l = n >> 1; (j ^= l) < l; l >>= 1) ;
    }
    int now = 0;
    for (int h = 2; h <= n; h <<= 1) {
        now++;
        for (int j = 0; j < n; j += h) {
            LL w = 1;
            for (int k = 0; k < (h >> 1); k++) {
                LL u = x[j + k], t = x[j + k + (h >> 1)] * w % MOD;
                x[j + (h >> 1) + k] = u - t;
                if (x[j + (h >> 1) + k] < 0) x[j + (h >> 1) + k] += MOD;
                x[j + k] = u + t;
                if (x[j + k] >= MOD) x[j + k] -= MOD;
                w = w * wn[now] % MOD;
            }
        }
    }
    if (flag) {
        for (int i = 1; i < (n >> 1); i++) swap(x[i], x[n - i]);
        LL inv = fpow(n, MOD - 2);
        for (int i = 0; i < n; i++) x[i] = x[i] * inv % MOD;
    }
    return;
}
void multi(int n, int m, LL *a, LL *b) {
    int l = 1;
    while (l <= (n + m + 1)) l <<= 1;
    prework(l);
    // for (int i = 0; i < n; i++) printf("%lld ", a[i]); puts("");
    // for (int i = 0; i < m; i++) printf("%lld ", b[i]); puts("");
    fft(l, a, 0), fft(l, b, 0);
    for (int i = 0; i < l; i++) a[i] = a[i] * b[i] % MOD;
    fft(l, a, 1);
    // for (int i = 0; i < n + m; i++) printf("%lld ", a[i]); puts("");
}
LL A[N + 5], B[N + 5], ans[N + 5];
int n, m;
char s1[N + 5], s2[N + 5];
int main() {
    scanf("%d%d", &n, &m);
    scanf("%s%s", s1, s2);
	memset(A, 0, sizeof(A));
	memset(B, 0, sizeof(B));
    for (int i = 0; i < n; i++) A[i] = s1[i] == 'R';
    for (int i = 0; i < m; i++) B[i] = s2[m - i - 1] == 'P';
    multi(n, m, A, B);
	for (int i = 0; i < n + m; i++) ans[i] += A[i];
	memset(A, 0, sizeof(A));
	memset(B, 0, sizeof(B));
    for (int i = 0; i < n; i++) A[i] = s1[i] == 'S';
    for (int i = 0; i < m; i++) B[i] = s2[m - i - 1] == 'R';
    multi(n, m, A, B);
	for (int i = 0; i < n + m; i++) ans[i] += A[i];
	memset(A, 0, sizeof(A));
	memset(B, 0, sizeof(B));
    for (int i = 0; i < n; i++) A[i] = s1[i] == 'P';
    for (int i = 0; i < m; i++) B[i] = s2[m - i - 1] == 'S';
    multi(n, m, A, B);
	LL mx = 0;
	for (int i = m - 1; i < n + m; i++) ans[i] += A[i], mx = max(mx, ans[i]);
	printf("%lld\n", mx);
    return 0;
}
