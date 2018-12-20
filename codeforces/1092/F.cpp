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
const int MOD = 1e9 + 7;
const ll HASH_KEY = 6151;
const ll HASH_MOD = 1610612741;

mt19937 rdm(chrono::steady_clock::now().time_since_epoch().count());

const int MAXN = 200000;

vi g[MAXN];
int a[MAXN];
ll dp[MAXN], sum[MAXN];

void dfs1(int u, int fa) {
  ll &s = sum[u], &d = dp[u];
  s = a[u];
  d = 0;
  for (int &v : g[u]) {
    if (v == fa)
      continue;
    dfs1(v, u);
    s += sum[v];
    d += dp[v] + sum[v];
  }
}

ll dfs2(int u, int fa, ll extra) {
  extra += sum[0] - 2 * sum[u];
  ll res = extra;
  for (int &v : g[u]) {
    if (v == fa)
      continue;
    res = max(res, dfs2(v, u, extra));
  }
  return res;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);

  int n;
  cin >> n;
  for (int i = 0; i < n; i++) {
    cin >> a[i];
  }
  for (int i = 1; i < n; i++) {
    int u, v;
    cin >> u >> v;
    g[u - 1].push_back(v - 1);
    g[v - 1].push_back(u - 1);
  }
  dfs1(0, -1);
  // for (int i = 0; i < n; i++) {
  //   cout << sum[i] << " " << dp[i] << endl;
  // }
  cout << dfs2(0, -1, dp[0] + sum[0]);
  return 0;
}
