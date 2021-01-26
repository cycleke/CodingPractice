#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<int, int> pii;

void debug_out() { cerr << endl; }

template <typename Head, typename... Tail> void debug_out(Head H, Tail... T) {
  cerr << " " << to_string(H);
  debug_out(T...);
}

#define debug(...) cerr << "[" << #__VA_ARGS__ << "]:", debug_out(__VA_ARGS__)

const int MOD = 1e9 + 7;
const int MAXN = 2e3 + 3;

int fpow(int a, int b) {
  int r = 1;
  for (; b; b >>= 1, a = 1ll * a * a % MOD) (b & 1) && (r = 1ll * r * a % MOD);
  return r;
}

bitset<MAXN> mark;
vector<pii> adj[MAXN];
vector<int> radj[MAXN];
int n, n3, m, q[MAXN], inv[MAXN * 3], fail[MAXN * 2], ans[MAXN * 3];

void solve() {
  cin >> n >> m;
  for (int i = 0, u, v, w; i < m; ++i) {
    cin >> u >> v >> w;
    adj[u].emplace_back(v, w);
    radj[v].push_back(u);
  }
  adj[1].emplace_back(1, 0);

  int *l = q, *r = q;
  *r++ = 1;
  mark[1] = 1;
  while (l < r) {
    int u = *l++;
    for (int v : radj[u]) {
      if (mark[v]) continue;
      mark[v] = 1;
      *r++ = v;
    }
  }

  n3 = n * 3;
  vector<int> nodes = {0};
  for (int step = 0; step < n3; ++step) {
    pair<int, vector<int>> cur(INT_MAX, {});
    for (int u : nodes)
      for (pii e : adj[u])
        if (mark[e.first]) {
          if (e.second < cur.first) {
            cur = {e.second, {e.first}};
          } else if (e.second == cur.first) {
            cur.second.push_back(e.first);
          }
        }
    ans[step] = cur.first;
    nodes = cur.second;
    sort(nodes.begin(), nodes.end());
    nodes.erase(unique(nodes.begin(), nodes.end()), nodes.end());
  }

  // for (int i = 0; i < n3; ++i) debug(ans[i]);

  int res = 0;
  for (int i = 0; i < n; ++i) res = (10ll * res + ans[i]) % MOD;
  res = 1ll * res * inv[n] % MOD;

  int n2 = n * 2, p = -1;
  fail[0] = -1;
  for (int i = 1; i < n2; ++i) {
    while (~p && ans[n + p + 1] != ans[n + i]) p = fail[p];
    fail[i] = ans[n + p + 1] == ans[n + i] ? ++p : p;
  }

  int cycle_len = n2 - fail[n2 - 1] - 1;
  int cycle = 0;
  for (int i = 0; i < cycle_len; ++i) cycle = (10ll * cycle + ans[i + n]) % MOD;
  cycle = 1ll * cycle * inv[cycle_len] % MOD *
          fpow(MOD + 1 - inv[cycle_len], MOD - 2) % MOD * inv[n] % MOD;
  cout << (res + cycle) % MOD << "\n";

  debug(res, cycle, cycle_len);

  for (int i = 0; i < n; ++i) {
    mark[i] = 0;
    adj[i].clear();
    radj[i].clear();
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr), cout.tie(nullptr);
  cout << fixed << setprecision(10);

  int inv_10 = fpow(10, MOD - 2);
  inv[0] = 1, inv[1] = inv_10;
  for (int i = 2; i < MAXN * 3; ++i) inv[i] = 1ll * inv[i - 1] * inv_10 % MOD;

  int o_o, omo = 1;
  for (cin >> o_o; omo <= o_o; ++omo, solve()) cout << "Case #" << omo << ": ";
  return 0;
}
