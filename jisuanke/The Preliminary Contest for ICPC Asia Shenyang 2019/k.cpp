#include <bits/stdc++.h>
using namespace std;

const int MOD = 1e9 + 7;
const int MAXK = 75;

inline int mod_pow(int a, int b) {
  int res = 1;
  for (; b; b >>= 1, a = 1LL * a * a % MOD)
    if (b & 1) res = 1LL * res * a % MOD;
  return res;
}
inline int inv(int x) { return mod_pow(x, MOD - 2); }

typedef int Mat[MAXK][MAXK];

int k, m, f[MAXK * 2], a[MAXK][MAXK], p[MAXK];

void gauss() {
  int i, j, k, r;
  for (k = 1; k <= m; ++k) {
    if (!a[k][k]) {
      for (i = k + 1; i <= m; ++i)
        if (a[i][k]) {
          r = i;
          break;
        }
      for (int i = k; i <= m; ++i) swap(a[k][i], a[r][i]);
      swap(p[k], p[r]);
    }

    r = inv(a[k][k]);
    p[k] = 1LL * p[k] * r % MOD;
    for (i = k + 1; i <= m; ++i) a[k][i] = 1LL * a[k][i] * r % MOD;
    a[k][k] = 1;

    for (i = k + 1; i <= m; ++i) {
      if (!a[i][k]) continue;
      p[i] = (p[i] - 1LL * a[i][k] * p[k] % MOD + MOD) % MOD;
      for (j = k + 1; j <= m; ++j)
        a[i][j] = (a[i][j] - 1LL * a[k][j] * a[i][k] % MOD + MOD) % MOD;
      a[i][k] = 0;
    }
  }

  for (k = m; k; --k) {
    for (i = 1; i < k; ++i) {
      p[i] = (p[i] - 1LL * p[k] * a[i][k] % MOD + MOD) % MOD;
      for (j = k + 1; j <= m; ++j)
        a[i][j] = (a[i][j] - 1LL * a[k][j] * a[i][k] % MOD + MOD) % MOD;
      a[i][k] = 0;
    }
  }
}

void mul(Mat &a, const Mat &b) {
  static Mat c;
  for (int i = 1; i <= m; ++i)
    for (int j = 1; j <= m; ++j) {
      c[i][j] = 0;
      for (int k = 1; k <= m; ++k)
        c[i][j] = (c[i][j] + 1LL * a[i][k] * b[k][j]) % MOD;
    }
  for (int i = 1; i <= m; ++i)
    for (int j = 1; j <= m; ++j) a[i][j] = c[i][j];
}

Mat A, B;

void solve() {
  long long n;
  cin >> k >> n;
  for (int i = 1; i <= k * 2; ++i) cin >> f[i];
  if (n <= 2 * k) {
    int ans = 0;
    for (int i = 1; i <= n; ++i) ans = (ans + f[i]) % MOD;
    cout << ans << '\n';
    return;
  }
  for (int i = 1; i <= k; ++i) {
    p[i] = f[k + i];
    for (int j = 1; j <= k; ++j) a[i][j] = f[k + i - j];
  }
  m = k;
  gauss();
  // for (int i = 1; i <= k; ++i) cout << p[i] << ' ';
  // cout << '\n';
  m = k + 1;
  memset(A, 0, sizeof(A));
  memset(B, 0, sizeof(B));
  for (int i = 1; i <= m; ++i) A[i][i] = 1;
  for (int i = 1; i <= k; ++i) B[1][i] = B[m][i] = p[i];
  B[m][m] = 1;
  for (int i = 2; i <= k; ++i) B[i][i - 1] = 1;

  int sk = 0;
  for (int i = 1; i <= k; ++i) sk = (sk + f[i]) % MOD;
  for (n -= k; n; n >>= 1, mul(B, B))
    if (n & 1) mul(A, B);
  int ans = 0;
  for (int i = 1; i <= k; ++i) ans = (ans + 1LL * A[m][i] * f[k - i + 1]) % MOD;
  ans = (ans + 1LL * A[m][m] * sk) % MOD;
  cout << ans << '\n';
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int o_o;
  for (cin >> o_o; o_o; --o_o) solve();
  return 0;
}
