#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef pair<int, int> pii;
typedef tuple<int, int, int> tiii;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef vector<long long> vll;

const int INF = 0x3ffffff;
const int MOD = 998244353;
const ll HASH_KEY = 6151;
const ll HASH_MOD = 1610612741;

mt19937 rdm(chrono::steady_clock::now().time_since_epoch().count());

vvi g, dp;

void dfs(int u, int fa) {
  vi &f = dp[u];
  f[0] = 1;
  for (auto v : g[u]) {
    if (v == fa)
      continue;
    dfs(v, u);
    vi t(3), &g = dp[v];
    t[0] = ll(f[0]) * (g[0] + g[2]) % MOD;
    t[1] = (ll(f[0]) * g[2] + f[1] * (g[0] + 2ll * g[2])) % MOD;
    t[2] = (ll(f[0] + f[1]) * (g[0] + g[1]) + f[2] * (g[0] + 2ll * g[2])) % MOD;
    f = t;
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);

  int n;
  cin >> n;

  g = vvi(n);
  dp = vvi(n, vi(3, 0));

  for (int i = 1; i < n; i++) {
    int u, v;
    cin >> u >> v;
    g[u - 1].push_back(v - 1);
    g[v - 1].push_back(u - 1);
  }
  dfs(0, -1);
  cout << (dp[0][0] + dp[0][2]) % MOD << endl;
  return 0;
}
