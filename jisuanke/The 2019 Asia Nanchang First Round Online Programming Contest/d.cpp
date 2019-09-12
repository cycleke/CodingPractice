#include <algorithm>
#include <cstdio>
using namespace std;

typedef long long ll;
const int MOD = 100003;
const int MAXN = 2e5 + 5;

ll f[20][MAXN], M[3], ans[MAXN];
int n, a, R[MAXN], m, val[MAXN];
ll quickpow(ll num, ll x, ll p) {
  ll base = num % p;
  ll ans = 1;
  while (x) {
    if (x & 1) ans = ans * base % p;
    x >>= 1;
    base = base * base % p;
  }
  return ans;
}
void NTT(ll a[MAXN], int n, int opt, ll p) {
  for (int i = 0; i < n; i++)
    if (i > R[i]) swap(a[i], a[R[i]]);
  for (int i = 1; i < n; i <<= 1) {
    ll wn = quickpow(3, (p - 1) / (i << 1), p);
    for (int p1 = i << 1, j = 0; j < n; j += p1) {
      ll w = 1;
      for (int k = 0; k < i; k++, w = w * wn % p) {
        ll x = a[j + k], y = w * a[j + k + i] % p;
        a[j + k] = (x + y) % p;
        a[j + k + i] = (x - y + p) % p;
      }
    }
  }
  if (opt == -1) reverse(a + 1, a + n);
}
ll mul(ll num, ll x, ll p) {
  ll ans = 0;
  ll base = num;
  while (x) {
    if (x & 1) ans = (ans + base) % p;
    x >>= 1;
    base = (base + base) % p;
  }
  return ans;
}
ll china(ll a1, ll a2) {
  ll MM = M[1] * M[2];
  ll x = quickpow(M[2], M[1] - 2, M[1]), x1 = quickpow(M[1], M[2] - 2, M[2]);
  ll A =
      (mul(a1 * M[2] % MM, x % MM, MM) + mul(a2 * M[1] % MM, x1 % MM, MM)) % MM;
  return A % MOD;
}
void solve(int l, int r, int x) {
  if (l == r) {
    f[x][0] = 1;
    f[x][1] = quickpow(a, val[l], MOD);
    return;
  }
  int mid = (l + r) / 2;
  int len = r - l + 1;
  int L = 0, n1 = 1;
  for (n1 = 1; n1 <= len; n1 <<= 1) L++;
  solve(l, mid, x + 1);
  ll a[n1 + 10], b[n1 + 10], a1[n1 + 10], b1[n1 + 10];
  for (int i = 0; i <= mid - l + 1; i++) a[i] = a1[i] = f[x + 1][i];
  for (int i = mid - l + 2; i <= n1; i++) a[i] = 0, a1[i] = 0;
  solve(mid + 1, r, x + 1);
  for (int i = 0; i <= r - mid; i++) b[i] = b1[i] = f[x + 1][i];
  for (int i = r - mid + 1; i <= n1; i++) b[i] = 0, b1[i] = 0;

  for (int i = 0; i <= n1; i++) R[i] = (R[i >> 1] >> 1) | ((i & 1) << (L - 1));
  NTT(a, n1, 1, M[1]);
  NTT(b, n1, 1, M[1]);
  for (int i = 0; i < n1; i++) a[i] = a[i] * b[i] % M[1];
  NTT(a, n1, -1, M[1]);
  ll inv = quickpow(n1, M[1] - 2, M[1]);
  for (int i = 0; i <= len; i++) a[i] = a[i] * inv % M[1];
  NTT(a1, n1, 1, M[2]);
  NTT(b1, n1, 1, M[2]);
  for (int i = 0; i <= n1; i++) a1[i] = a1[i] * b1[i] % M[2];
  NTT(a1, n1, -1, M[2]);
  inv = quickpow(n1, M[2] - 2, M[2]);
  for (int i = 0; i <= len; i++) a1[i] = a1[i] * inv % M[2];
  for (int i = 0; i <= len; i++) f[x][i] = china(a[i], a1[i]);
}
int main() {
  scanf("%d%d%d", &n, &a, &m);
  M[1] = 998244353, M[2] = 1004535809;
  for (int i = 1; i <= n; i++) scanf("%d", &val[i]);
  solve(1, n, 1);
  for (int i = 1; i <= m; i++) {
    int x;
    scanf("%d", &x);
    printf("%lld\n", f[1][n - x]);
  }
}
