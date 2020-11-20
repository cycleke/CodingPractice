#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1e5 + 3;
const int MOD = 998244353;

int mpow(int a, int b = MOD - 2) {
  int r = 1;
  for (; b; b >>= 1, a = 1ll * a * a % MOD)
    (b & 1) && (r = 1ll * r * a % MOD);
  return r;
}

int factor[MAXN];
bitset<MAXN> vis;
vector<int> prime, factors;

int p[18], e[18], tot;

void dfs(int step, int cur) {
  if (step == 0) {
    if (cur > 1) factors.push_back(cur);
  } else {
    for (int i = 0; i <= e[step]; ++i, cur *= p[step])
      dfs(step - 1, cur);
  }
}

void find_factors(int x) {
  factors.clear();
  tot = 0;
  while (x > 1) {
    ++tot;
    int f = p[tot] = factor[x];
    for (e[tot] = 0; factor[x] == f; x /= f) ++e[tot];
  }
  dfs(tot, 1);
}

int f[MAXN], g[MAXN], h[MAXN][18];

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr), cout.tie(nullptr);

  int n, k;
  cin >> n >> k;
  for (int i = 1; i <= n; ++i) cin >> g[i];

  for (int i = 2; i < MAXN; ++i) {
    if (!vis[i]) {
      factor[i] = i;
      prime.push_back(i);
    }
    for (int p : prime) {
      int t = i * p;
      if (t >= MAXN) break;
      vis[t] = 1;
      factor[t] = p;
      if (i % p == 0) break;
    }
  }

  int inv_k = mpow(k);
  f[1] = 1;
  cout << 1;
  for (int i = 2; i <= n; ++i) {
    int bound = min(17, k);
    find_factors(i);
    for (int d : factors) {
      for (int m = 2; m <= bound; ++m) {
        h[i][m] = (h[i][m] + 1ll * h[d][1] * h[i / d][m - 1]) % MOD;
      }
    }
    int C = k;
    int sum = 0;
    for (int m = 2; m <= bound; ++m) {
      C = 1ll * C * (k + 1 - m) % MOD * mpow(m) % MOD;
      sum = (sum + 1ll * C * h[i][m]) % MOD;
    }
    f[i] = g[i] - sum;
    if (f[i] < 0) f[i] += MOD;
    h[i][1] = f[i] = 1ll * f[i] * inv_k % MOD;
    cout << " " << f[i];
  }
  cout << "\n";
  
  return 0;
}

