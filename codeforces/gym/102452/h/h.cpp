#include <bits/stdc++.h>
using namespace std;

const int MAXN = 5e5 + 3;
const int MAXM = 1e6 + 3;
const int INF = 0x3f3f3f3f;

vector<int> stks[MAXM * 4];
vector<tuple<int, int, int>> qs[MAXN];
int n, m, h[MAXN], v[MAXN], ans[MAXM], heights[MAXM];

void clear_tree(int u, int l, int r) {
  stks[u].clear();
  if (l == r) return;
  int mid = (l + r) / 2;
  clear_tree(u << 1, l, mid);
  clear_tree(u << 1 | 1, mid + 1, r);
}

void insert(int u, int l, int r, int x) {
  auto &stk = stks[u];
  while (stk.size() && v[stk.back()] >= v[x]) stk.pop_back();
  stk.push_back(x);
  if (l == r) return;
  int mid = (l + r) / 2;
  if (h[x] <= mid) {
    insert(u << 1, l, mid, x);
  } else {
    insert(u << 1 | 1, mid + 1, r, x);
  }
}

bool check(const vector<int> &stk, int left, int time) {
  for (int l = 0, r = stk.size() - 1; l <= r;) {
    int mid = (l + r) / 2;
    if (stk[mid] >= left && v[stk[mid]] <= time) return true;
    stk[mid] >= left ? r = mid - 1 : l = mid + 1;
  }
  return false;
}

int q_max(int u, int l, int r, int left, int height, int time) {
  auto &stk = stks[u];
  if (stk.empty() || v[stk[0]] > time) return -1;
  if (l == r) return l <= height && check(stk, left, time) ? l : -1;
  if (r <= height && !check(stk, left, time)) return -1;
  int mid = (l + r) / 2;
  if (height > mid) {
    int temp = q_max(u << 1 | 1, mid + 1, r, left, height, time);
    if (~temp) return temp;
  }
  return q_max(u << 1, l, mid, left, height, time);
}

int q_min(int u, int l, int r, int left, int height, int time) {
  auto &stk = stks[u];
  if (stk.empty() || v[stk[0]] > time) return -1;
  if (l == r) return l >= height && check(stk, left, time) ? l : -1;
  if (l >= height && !check(stk, left, time)) return -1;
  int mid = (l + r) / 2;
  if (height <= mid) {
    int temp = q_min(u << 1, l, mid, left, height, time);
    if (~temp) return temp;
  }
  return q_min(u << 1 | 1, mid + 1, r, left, height, time);
}

void solve() {
  int tot = 0;
  cin >> n >> m;
  memset(h + 1, 0, sizeof(int) * n);
  memset(ans, 0x3f, sizeof(int) * m);

  for (int i = 0, opt, a, b, c; i < m; ++i) {
    cin >> opt >> a >> b;
    if (opt) {
      cin >> c;
      heights[tot++] = c;
      qs[b].emplace_back(a, c, i);
    } else {
      heights[tot++] = b;
      h[a] = b, v[a] = i;
    }
  }

  sort(heights, heights + tot);
  tot = unique(heights, heights + tot) - heights;

  static auto gid = [&](int x) {
    return lower_bound(heights, heights + tot, x) - heights;
  };

  clear_tree(1, 0, tot - 1);
  for (int r = 1; r <= n; ++r) {
    if (h[r]) h[r] = gid(h[r]), insert(1, 0, tot - 1, r);
    for (auto tp : qs[r]) {
      int l, height, id, temp;
      tie(l, height, id) = tp;
      height = gid(height);
      // cerr << "# " << height << "\n";
      temp = q_max(1, 0, tot - 1, l, height, id);
      // cerr << "# " << temp << "\n";
      if (~temp) ans[id] = heights[height] - heights[temp];
      temp = q_min(1, 0, tot - 1, l, height, id);
      // cerr << "# " << temp << "\n";
      if (~temp) ans[id] = min(ans[id], heights[temp] - heights[height]);
      if (ans[id] == INF) ans[id] = -1;
    }
    qs[r].clear();
  }

  for (int i = 0; i < m; ++i) {
    if (ans[i] == INF) continue;
    cout << ans[i] << "\n";
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr), cout.tie(nullptr);

  int o_o;
  for (cin >> o_o; o_o; --o_o) solve();
  return 0;
}
