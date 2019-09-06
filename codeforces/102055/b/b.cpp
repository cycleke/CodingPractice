#include <bits/stdc++.h>
using namespace std;

typedef pair<int, int> pii;
typedef tuple<int, int, int> tiii;
typedef tuple<int, int, int, int> tiiii;

const int MAXN = 2e5 + 5;

vector<int> adj[MAXN];
bool imposs;
int n, m, a[MAXN][2], mx, mi, color[MAXN], vis[MAXN], vis_c;
pii b[MAXN][2];

void dfs(int u, int c) {
  color[u] = c;
  vis[u] = vis_c;
  mx = max(mx, a[u][c]);
  mi = min(mi, a[u][c]);
  for (int v : adj[u]) {
    if (vis[v] ^ vis_c) {
      dfs(v, c ^ 1);
      if (imposs) return;
    } else {
      if (color[v] == c) {
        imposs = true;
        return;
      }
    }
  }
}

tiii l[MAXN * 2];
set<tiiii> s;
multiset<int> mxv;

void solve(int case_num) {
  cout << "Case " << case_num << ": ";

  cin >> n >> m;
  for (int i = 1; i <= n; ++i) adj[i].clear(), color[i] = -1;
  for (int u, v; m; --m) {
    cin >> u >> v;
    adj[u].push_back(v);
    adj[v].push_back(u);
  }
  for (int i = 1; i <= n; ++i) cin >> a[i][0] >> a[i][1];

  if (n == 1) {
    cout << "0\n";
    return;
  }

  imposs = false;
  int cnt = 0;
  s.clear();
  mxv.clear();
  for (int i = 1; i <= n; ++i) {
    if (~color[i]) continue;
    ++vis_c;
    mx = INT_MIN, mi = INT_MAX;
    dfs(i, 0);
    b[cnt][0] = make_pair(mi, mx);
    l[cnt << 1] = {mi, cnt, 0};
    if (imposs) break;
    ++vis_c;
    mx = INT_MIN, mi = INT_MAX;
    dfs(i, 1);
    b[cnt][1] = make_pair(mi, mx);
    l[cnt << 1 | 1] = {mi, cnt, 1};

    if (b[cnt][0].second < b[cnt][1].second) {
      s.emplace(b[cnt][0].first, b[cnt][0].second, cnt, 0);
      mxv.insert(b[cnt][0].second);
    } else {
      s.emplace(b[cnt][1].first, b[cnt][1].second, cnt, 1);
      mxv.insert(b[cnt][1].second);
    }

    ++cnt;
  }
  if (imposs) {
    cout << "IMPOSSIBLE\n";
    return;
  }

  sort(l, l + cnt * 2);
  int lcnt = unique(l, l + cnt * 2) - l;

  int ans = INT_MAX;
  for (int _ = 0; _ < lcnt; ++_) {
    int mii, id, type;
    tie(mii, id, type) = l[_];

    for (auto it = s.begin(); it != s.end() && get<0>(*it) < mii; it = s.begin()) {
      int id = get<2>(*it);
      int type = get<3>(*it);

      // for (auto it = mxv.begin(); it != mxv.end(); ++it) cerr << *it << ' ';
      // cerr << '\n';

      mxv.erase(mxv.find(get<1>(*it)));
      s.erase(it);
      if (b[id][type ^ 1].first >= mii) {
        s.emplace(b[id][type ^ 1].first, b[id][type ^ 1].second, id, type ^ 1);
        mxv.insert(b[id][type ^ 1].second);
      }
    }

    if (int(s.size()) < cnt) break;

    ans = min(ans, *mxv.rbegin() - mii);

  }
  cout << ans << '\n';
}

int main() {
  // freopen("in1.txt", "r", stdin);
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int o_o;
  cin >> o_o;
  for (int i = 1; i <= o_o; ++i) solve(i);
  return 0;
}
