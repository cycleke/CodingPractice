#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1e6 + 5;
const int MOD = 1e9 + 7;

int f[MAXN], inv[MAXN], inv_f[MAXN];

inline int C(int n, int m) {
  if (n < m) return 0;
  return 1LL * f[n] * inv_f[m] % MOD * inv_f[n - m] % MOD;
}

int n, pos;
struct Data {
  int l, r, id;
  bool operator<(const Data &a) const { return (l ^ a.l) ? l < a.l : r > a.r; }
} p[MAXN];

int gao(int l, int r) {
  // cerr << l << ' ' << r << '\n';
  if (l > r) return 1;
  if (l != p[pos].l || r != p[pos].r) return 0;
  if (l == r) return ++pos, 1;
  int x = p[pos++].id;
  return 1LL * gao(l, x - 1) * gao(x + 1, r) % MOD * C(r - l, x - l) % MOD;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  f[0] = inv_f[0] = 1;
  f[1] = inv[1] = inv_f[1] = 1;
  for (int i = 2; i < MAXN; ++i) {
    f[i] = 1LL * f[i - 1] * i % MOD;
    inv[i] = 1LL * (MOD - MOD / i) * inv[MOD % i] % MOD;
    inv_f[i] = 1LL * inv_f[i - 1] * inv[i] % MOD;
  }

  int case_count = 0;
  while (cin >> n) {
    cout << "Case #" << ++case_count << ": ";
    for (int i = 0; i < n; ++i) p[i].id = i + 1;
    for (int i = 0; i < n; ++i) cin >> p[i].l;
    for (int i = 0; i < n; ++i) cin >> p[i].r;
    sort(p, p + n);
    pos = 0;
    cout << gao(1, n) << '\n';
  }

  return 0;
}
