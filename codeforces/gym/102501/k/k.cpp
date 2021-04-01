#include <bits/stdc++.h>
using namespace std;

using ll = long long;
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

constexpr int MAXN = 1e5 + 3;

bitset<MAXN> target;
vector<int> radj[MAXN], link[MAXN];

bool check(vector<int> &lk, int u) {
  if (lk.size() >= 2) return true;
  for (int x : lk)
    if (u == x) return true;
  lk.push_back(u);
  return false;
}

void dfs(int u, int anc) {
  if (check(link[u], anc)) return;
  for (int v : radj[u]) dfs(v, anc);
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr), cout.tie(nullptr);

  int n, m, t;
  cin >> n >> m >> t;
  for (int i = 0, u, v; i < m; ++i) {
    cin >> u >> v;
    if (v == t) {
      target[u] = 1;
    } else {
      radj[v].push_back(u);
    }
  }

  for (int i = 0; i < n; ++i) {
    if (!target[i]) continue;
    dfs(i, i);
  }
  int cnt = 0;
  for (int i = 0; i < n; ++i) cnt += target[i] && link[i].size() == 1;
  cout << cnt << "\n";
  for (int i = 0; i < n; ++i)
    if (target[i] && link[i].size() == 1) cout << i << "\n";

  return 0;
}
