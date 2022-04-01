#include <bits/stdc++.h>
using namespace std;

using i64 = long long;
using pii = pair<int, int>;

void debug_out() { cerr << endl; }
template <typename T> string to_string(const vector<T> &vec) {
  string res = "[";
  bool first = true;
  for (const T &x : vec) {
    if (first) {
      first = false;
    } else {
      res += ",";
    }
    res += to_string(x);
  }
  return res + "]";
}
template <typename Head, typename... Tail> void debug_out(Head H, Tail... T) {
  cerr << " " << to_string(H);
  debug_out(T...);
}
#ifdef ONLINE_JUDGE
#define debug(...)
#else
#define debug(...) cerr << "[" << #__VA_ARGS__ << "]:", debug_out(__VA_ARGS__)
#endif

constexpr int MOD = 1e9 + 7;
constexpr int MAXN = 4e5 + 3;

int a[MAXN];
bool vis[MAXN];
vector<int> adj[MAXN];

void dfs(int u) {
  vis[u] = 1;
  for (int v : adj[u]) {
    if (vis[v]) { continue; }
    dfs(v);
  }
}

void solve() {
  int n;
  cin >> n;
  for (int i = 1; i <= n; ++i) {
    vis[i] = 0;
    adj[i].clear();
  }
  for (int i = 0; i < n; ++i) { cin >> a[i]; }
  for (int i = 0, b; i < n; ++i) {
    cin >> b;
    adj[a[i]].push_back(b);
  }

  int ans = 1;
  for (int i = 1; i <= n; ++i) {
    if (vis[i]) { continue; }
    dfs(i);
    ans += ans;
    if (ans >= MOD) { ans -= MOD; }
  }
  cout << ans << "\n";
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr), cout.tie(nullptr);
  cout << fixed << setprecision(10);

  int o_o;
  for (cin >> o_o; o_o; --o_o) solve();
  return 0;
}
