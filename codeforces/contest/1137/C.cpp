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

// mt19937 rdm(chrono::steady_clock::now().time_since_epoch().c());

const int MAXN = 100000;
const int MAXD = 50;
const int MAXS = MAXN * MAXD;

vi adj[MAXN], rev_adj[MAXN];
int px[MAXS], py[MAXS], qx[MAXS], qy[MAXS], cnt;
bool schedule[MAXN][MAXD], vis[MAXN][MAXD];
int scc[MAXN][MAXD], lst[MAXN], w[MAXS], dp[MAXS];
int n, m, d, c;

void dfs(int x, int y) {
  vis[x][y] = true;
  for (auto v : adj[x]) {
    if (!vis[v][(y + 1) % d]) {
      dfs(v, (y + 1) % d);
    }
  }
  px[cnt] = x;
  py[cnt] = y;
  ++cnt;
}

void rev_dfs(int x, int y) {
  scc[x][y] = c;
  if (schedule[x][y] && lst[x] != c) {
    lst[x] = c;
    ++w[c];
  }
  qx[cnt] = x;
  qy[cnt] = y;
  ++cnt;
  for (auto v : rev_adj[x]) {
    if (scc[v][(y - 1 + d) % d] == -1) {
      rev_dfs(v, (y - 1 + d) % d);
    }
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);

  cin >> n >> m >> d;
  while (m--) {
    int u, v;
    cin >> u >> v;
    --u;
    --v;
    adj[u].push_back(v);
    rev_adj[v].push_back(u);
  }

  for (int i = 0; i < n; ++i) {
    char s[d + 1];
    cin >> s;
    for (int j = 0; j < d; ++j) {
      schedule[i][j] = s[j] == '1';
    }
  }

  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < d; ++j) {
      if (!vis[i][j]) {
        dfs(i, j);
      }
      scc[i][j] = -1;
    }
    lst[i] = -1;
  }
  cnt = 0;
  for (int i = n * d - 1; ~i; --i) {
    int x = px[i];
    int y = py[i];
    if (scc[x][y] == -1) {
      rev_dfs(x, y);
      ++c;
    }
  }

  for (int i = n * d - 1; ~i; --i) {
    int x = qx[i];
    int y = qy[i];
    dp[scc[x][y]] = max(dp[scc[x][y]], w[scc[x][y]]);
    for (auto v : adj[x]) {
      if (scc[v][(y + 1) % d] > scc[x][y]) {
        dp[scc[x][y]] =
            max(dp[scc[x][y]], dp[scc[v][(y + 1) % d]] + w[scc[x][y]]);
      }
    }
  }
  cout << dp[scc[0][0]] << endl;
  return 0;
}
