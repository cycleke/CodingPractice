#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<int, int> pii;

// #define debug(...) fprintf(stderr, __VA_ARGS__)
#define debug(...)

const int MAXN = 1e3 + 3;

vector<int> adj[MAXN];
bitset<MAXN> instk, cut;
int bridges, dfs_clk, top, bc, n, m, d;
int dfn[MAXN], stk[MAXN], bel[MAXN], cnts[MAXN];

int dfs(int u, int from) {
  debug("#%d -> %d\n", from, u);
  int low = dfn[u] = ++dfs_clk;
  stk[top++] = u, instk[u] = 1;

  int son = 0;
  for (int v : adj[u]) {
    if (v == from) continue;
    if (!dfn[v]) {
      ++son;
      int low_v = dfs(v, u);
      (low_v < low) && (low = low_v);
      (low_v > dfn[u]) && (++bridges);
      (u != from && low_v >= dfn[u]) && (cut[u] = 1);
    } else if (instk[v] && low > dfn[v]) {
      low = dfn[v];
    }
  }
  (u == from && son > 1) && (cut[u] = 1);

  if (low == dfn[u]) {
    int v, sz = 0;
    cnts[++bc] = 0;
    do {
      ++sz;
      v = stk[--top];
      instk[v] = 0, bel[v] = bc;
    } while (u ^ v);
    (sz == 1) && (++d);
  }

  return low;
}

void solve() {
  cin >> n >> m;
  for (int i = 1; i <= n; ++i) {
    adj[i].clear();
    instk[i] = cut[i] = dfn[i] = 0;
  }

  for (int i = 0, u, v; i < m; ++i) {
    cin >> u >> v;
    adj[u].push_back(v);
    adj[v].push_back(u);
  }

  d = bridges = dfs_clk = top = bc = 0;
  dfs(1, 1);

  int cuts = 0, mx = 2;
  for (int i = 1; i <= n; ++i) {
    debug("#%d %d %d\n", i, (int)cut[i], bel[i]);
    cuts += (int)cut[i];
    for (int v : adj[i]) (bel[i] == bel[v]) && (++cnts[bel[i]]);
  }
  for (int i = 1; i <= bc; ++i) mx = max(mx, cnts[i]);
  cout << cuts << " " << bridges << " ";
  int p = bc + bridges - d, q = mx / 2, g = __gcd(p, q);
  cout << p / g << " " << q / g << "\n";
}

int main(int argc, char *argv[]) {
  ios::sync_with_stdio(false);
  cin.tie(nullptr), cout.tie(nullptr);
  cout << fixed << setprecision(10);

  int o_o;
  for (cin >> o_o; o_o; --o_o) solve();

  return 0;
}
