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

constexpr int MAXN = 300 + 3;

int a[MAXN][MAXN];

void solve() {
  int n, m;
  cin >> n >> m;
  priority_queue<tuple<int, int, int>> heap;
  for (int i = 0; i < n; ++i)
    for (int j = 0; j < m; ++j) {
      cin >> a[i][j];
      heap.emplace(a[i][j], i, j);
    }
  ll cnt = 0;
  int val, x, y;
  while (!heap.empty()) {
    tie(val, x, y) = heap.top();
    heap.pop();

    if (a[x][y] != val) continue;
    static const int dx[] = {1, -1, 0, 0};
    static const int dy[] = {0, 0, 1, -1};
    for (int i = 0; i < 4; ++i) {
      int x_ = x + dx[i], y_ = y + dy[i];
      if (x_ < 0 || x_ >= n || y_ < 0 || y_ >= m) continue;
      if (a[x_][y_] >= val - 1) continue;
      cnt += val - 1 - a[x_][y_];
      a[x_][y_] = val - 1;
      heap.emplace(val - 1, x_, y_);
    }
  }
  cout << cnt << "\n";
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr), cout.tie(nullptr);
  cout << fixed << setprecision(10);

  int o_o, v_v = 1;
  for (cin >> o_o; v_v <= o_o; ++v_v) {
    cout << "Case #" << v_v << ": ";
    solve();
  }
  return 0;
}
