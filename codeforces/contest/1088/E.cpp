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

vi a;
vvi g;
vll f;
ll maxp, k;

void dfs(int u, int fa, function<void(ll &val)> foo) {
  f[u] = a[u];
  for (int v : g[u]) {
    if (v == fa)
      continue;
    dfs(v, u, foo);
    f[u] += max(0ll, f[v]);
  }
  foo(f[u]);
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);

  int n;
  cin >> n;
  a = vi(n);
  f = vll(n);
  g = vvi(n);

  for (int i = 0; i < n; i++) {
    cin >> a[i];
  }
  for (int i = 1; i < n; i++) {
    int u, v;
    cin >> u >> v;
    g[u - 1].push_back(v - 1);
    g[v - 1].push_back(u - 1);
  }
  maxp = -(1ll << 62);
  k = 0;

  auto getMax = [&](ll &val) { maxp = max(maxp, val); };
  auto countMax = [&](ll &val) {
    if (val == maxp) {
      k++;
      val = 0;
    }
  };

  dfs(0, -1, getMax);
  dfs(0, -1, countMax);

  cout << maxp * k << " " << k << endl;
  return 0;
}
