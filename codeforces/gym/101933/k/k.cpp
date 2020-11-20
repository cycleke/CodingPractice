#include <bits/stdc++.h>
using namespace std;

const int MAXN = 2500 + 5;
const int MOD = 1000000007;

int C[MAXN][MAXN], inv[MAXN];

void init() {
  inv[1] = 1;
  C[1][0] = C[1][1] = 1;
  for (int i = 2; i < MAXN; ++i) {
    inv[i] = 1LL * (MOD - MOD / i) * inv[MOD % i] % MOD;
    C[i][0] = 1;
    for (int j = 1; j <= i; ++j)
      C[i][j] = (C[i - 1][j] + C[i - 1][j - 1]) % MOD;
  }
}

int n, k, dp[MAXN][MAXN], g[MAXN];
vector<int> adj[MAXN];

void dfs(int u) {
  for (int i = 1; i <= k; ++i) dp[u][i] = i;
  if (adj[u].empty()) return;

  for (int v : adj[u]) {
    dfs(v);
    for (int i = 1; i <= k; ++i)
      dp[u][i] = 1LL * dp[u][i] * dp[v][i] % MOD * inv[i] % MOD * (i - 1) % MOD;
  }

  // cout << "u: " << u << '\n';
  // for (int i = 1; i <= k; ++i) cout << dp[u][i] << ' ';
  // cout << '\n';
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  init();

  cin >> n >> k;
  if (n == 1) {
    cout << "1\n";
    return 0;
  }
  if (k == 2) {
    cout << "2\n";
    return 0;
  }
  for (int i = 1, p; i < n; ++i) {
    cin >> p;
    adj[p].push_back(i);
  }
  dfs(0);

  g[1] = dp[0][1];
  g[2] = dp[0][2];
  for (int i = 3; i <= k; ++i) {
    int &res = g[i];
    res = dp[0][i];
    for (int j = 1; j < i; ++j)
      res = (res + MOD - 1LL * C[i][j] * g[j] % MOD) % MOD;
    // cout << g[i] << ' ';
  }
  cout << g[k] << '\n';

  return 0;
}
