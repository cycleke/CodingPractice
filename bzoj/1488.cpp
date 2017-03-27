#include <cstdio>
#include <algorithm>

const int mod(997), maxn(66);
typedef int arr[maxn];

arr fac, x, y;
int n, cnt, ans;

inline int gcd(int a, int b) {
  for (static int t; b; t = a % b, a = b, b = t);
  return a;
}

inline int qp(int a, int b) {
  static int r;
  for (r = 1; b; b >>= 1, a = a * a % mod)
    if (b & 1) r = r * a % mod;
  return r;
}

void dfs(int nx, int left) {
  if (!left) {
    static int a, b;
    a = 0, b = 1;
    for (register int i = 1; i <= cnt; ++i) {
      a += x[i] * (x[i] - 1) / 2 * y[i] + y[i] / 2 * x[i];
      for (register int j = i + 1; j <= cnt; ++j)
        a += x[i] * x[j] * gcd(y[i], y[j]);
    }
    for (register int i = 1; i <= cnt; ++i)
      b = b * qp(y[i], x[i]) * fac[x[i]] % mod;
    b = qp(b, mod - 2) * fac[n] % mod;
    ans = (ans + qp(2, a) * b) % mod;
  }
  if (nx > left) return;
  dfs(nx + 1, left);
  for (register int i = 1; i * nx <= left; ++i) {
    ++cnt;
    x[cnt] = i;
    y[cnt] = nx;
    dfs(nx + 1, left - i * nx);
    --cnt;
  }
}

int main() {
  scanf("%d", &n);
  fac[0] = 1;
  for (register int i = 1; i <= n; ++i) fac[i] = fac[i - 1] * i % mod;
  dfs(1, n);
  ans = ans * qp(fac[n], mod - 2) % mod;
  printf("%d\n", ans);
  return 0;
}
