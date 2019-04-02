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

// mt19937 rdm(chrono::steady_clock::now().time_since_epoch().count());

const int MAXN = 2e5 + 3;

pii edges[MAXN];
vector<int> adj[MAXN];
bool mark[MAXN], flag, vis[MAXN];

void dfs(int u) {
  vis[u] = true;
  for (int &v : adj[u]) {
    if (vis[v]) {
      flag &= mark[u] ^ mark[v];
    } else {
      mark[v] = !mark[u];
      dfs(v);
    }
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);

  int n, m;
  cin >> n >> m;
  for (int i = 0; i < m; ++i) {
    int u, v;
    cin >> u >> v;
    adj[u].push_back(v);
    adj[v].push_back(u);
    edges[i] = pii(u, v);
  }

  flag = true;
  mark[1] = false;
  dfs(1);
  if (flag) {
    cout << "YES\n";
    for (int i = 0; i < m; ++i) {
      cout << (mark[edges[i].first] ? 1 : 0);
    }
    cout << "\n";
  } else {
    cout << "NO\n";
  }
  return 0;
}
