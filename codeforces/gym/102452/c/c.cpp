#include <bits/stdc++.h>
using namespace std;

// #define debug(...) fprintf(stderr, __VA_ARGS__)
#define debug(...)

typedef long long ll;
const int MAXN = 2e5 + 5;

template <typename T> void cmax(T &a, T b) { (a < b) && (a = b); }

bitset<MAXN> vis;
vector<int> adj[MAXN];
int a[MAXN], f[MAXN], sz[MAXN], root, n, all;
ll ans;

void getRoot(int u, int from) {
  sz[u] = 1, f[u] = 0;
  for (int v : adj[u]) {
    if (vis[v] || v == from) continue;
    getRoot(v, u);
    sz[u] += sz[v];
    cmax(f[u], sz[v]);
  }
  cmax(f[u], all - sz[u]);
  if (f[u] < f[root]) root = u;
}

int cnt;
pair<ll, int> segment[MAXN];
pair<int, int> single[MAXN];
void dfs(int u, int from, int max_value, ll sum) {
  single[++cnt].first = max_value;
  segment[cnt] = make_pair(sum, cnt);
  for (int v : adj[u]) {
    if (vis[v] || v == from) continue;
    dfs(v, u, max(max_value, a[v]), sum + a[v]);
  }
}

int tree[MAXN];
void add(int x) {
  for (; x <= cnt; x += x & -x) ++tree[x];
}
int ask(int x) {
  int res = 0;
  for (; x; x &= x - 1) res += tree[x];
  return res;
}

ll gao(int u, int val) {
  cnt = 0;
  dfs(u, 0, max(val, a[u]), val + a[u]);
  int head = val ? val : a[u];
  sort(segment + 1, segment + cnt + 1);
  for (int i = 1; i <= cnt; ++i) single[segment[i].second].second = i;
  sort(single + 1, single + cnt + 1);
  memset(tree + 1, 0, cnt * sizeof(int));
  ll res = 0;
  for (int i = 1; i <= cnt; ++i) {
    int left = 1, right = cnt, idx = 0;
    ll bound = 2ll * single[i].first - segment[single[i].second].first + head;
    while (left <= right) {
      int mid = (left + right) / 2;
      if (segment[mid].first <= bound) {
        idx = mid;
        left = mid + 1;
      } else {
        right = mid - 1;
      }
    }
    res += i - 1 - ask(idx);
    add(single[i].second);
  }
  debug("# %d %d %lld\n", u, val, res);
  return res;
}

void solve(int u) {
  all = f[0] = sz[u];
  getRoot(u, root = 0);
  vis[root] = true;
  ans += gao(root, 0);
  for (int v : adj[root]) {
    if (vis[v]) continue;
    ans -= gao(v, a[root]);
  }
  for (int v : adj[root]) {
    if (vis[v]) continue;
    solve(v);
  }
}

void solveCase() {
  cin >> n;
  for (int i = 1; i <= n; ++i) {
    cin >> a[i];
    adj[i].clear();
    vis[i] = false;
  }
  for (int i = 1, u, v; i < n; ++i) {
    cin >> u >> v;
    adj[u].push_back(v);
    adj[v].push_back(u);
  }
  for (int i = 1; i <= n; ++i) reverse(adj[i].begin(), adj[i].end());
  ans = 0, sz[1] = n;
  solve(1);
  cout << ans << "\n";
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr), cout.tie(nullptr);

  int o_o;
  for (cin >> o_o; o_o; --o_o) solveCase();

  return 0;
}
