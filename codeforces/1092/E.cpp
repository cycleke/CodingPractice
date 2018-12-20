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

const int MAXN = 1000;

vi g[MAXN], cur;
int dist1[MAXN], dist2[MAXN];
bool visited[MAXN];

void dfs(int u, int pa) {
  visited[u] = true;
  cur.push_back(u);
  for (int &v : g[u]) {
    if (v == pa)
      continue;
    dfs(v, u);
  }
}

int bfs(int s, int d[MAXN]) {
  d[s] = 0;
  queue<int> que;
  que.push(s);
  int lst = s;
  while (!que.empty()) {
    int u = que.front();
    que.pop();
    lst = u;
    for (int &v : g[u]) {
      if (d[v] <= d[u] + 1)
        continue;
      d[v] = d[u] + 1;
      que.push(v);
    }
  }
  return lst;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);

  int n, m;
  cin >> n >> m;
  for (int i = 0; i < m; i++) {
    int u, v;
    cin >> u >> v;
    g[u - 1].push_back(v - 1);
    g[v - 1].push_back(u - 1);
  }

  vector<pii> trees;

  memset(dist1, 63, MAXN * sizeof(int));
  memset(dist2, 63, MAXN * sizeof(int));

  for (int i = 0; i < n; i++) {
    if (visited[i])
      continue;
    dfs(i, i);
    int x = bfs(i, dist1);
    int y = bfs(x, dist2);
    for (int &u : cur)
      dist1[u] = INF;
    bfs(y, dist1);
    int center, d = dist2[y];
    for (int &u : cur) {
      if (dist1[u] == d / 2 && dist2[u] == d - d / 2) {
        center = u;
        break;
      }
    }
    cur.clear();
    trees.emplace_back(d, center);
  }

  pii mx = trees.back();
  for (pii &p : trees)
    mx = max(mx, p);
  vector<pii> ans;
  for (pii &p : trees) {
    if (p == mx) continue;
    g[p.second].push_back(mx.second);
    g[mx.second].push_back(p.second);
    ans.emplace_back(p.second, mx.second);
  }

  memset(dist1, 63, MAXN * sizeof(int));
  memset(dist2, 63, MAXN * sizeof(int));

  int x = bfs(1, dist1);
  int y = bfs(x, dist2);
  cout << dist2[y] << endl;
  for (pii &p:ans) {
    cout << p.first + 1 << " " << p.second + 1 << endl;
  }
  
  return 0;
}
