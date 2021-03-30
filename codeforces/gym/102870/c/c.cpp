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

constexpr int MOD = 1e9 + 7;
constexpr int MAXM = 1e5 + 3;

set<int> pts;
int pos[MAXM];
priority_queue<tuple<int, int, int>> heap;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr), cout.tie(nullptr);
  cout << fixed << setprecision(10);

  int n, m;

  static auto add = [&](int l, int r) {
    if (l > r) return;
    if (l == 1 || r == n) {
      heap.emplace(r - l, -l, r);
    } else {
      heap.emplace((r - l) / 2, -l, r);
    }
  };

  static auto get = [&]() {
    while (!heap.empty()) {
      auto [dist, l, r] = heap.top();
      heap.pop();
      l = -l;
      auto it = pts.lower_bound(l);
      if (it == pts.end() || *it > r) return make_pair(l, r);
    }
    assert(0);
  };

  while (cin >> n >> m) {
    pts.clear();
    while (!heap.empty()) heap.pop();
    add(1, n);
    for (int i = 1, op, x; i <= m; ++i) {
      cin >> op;
      if (op == 1) {
        auto seg = get();
        if (seg.first == 1) {
          pos[i] = 1;
          add(2, seg.second);
        } else if (seg.second == n) {
          pos[i] = n;
          add(seg.first, n - 1);
        } else {
          pos[i] = x = (seg.first + seg.second) / 2;
          add(seg.first, x - 1), add(x + 1, seg.second);
        }
        pts.insert(pos[i]);
        cout << pos[i] << "\n";
      } else {
        cin >> x;
        x = pos[x];
        int l = x, r = x;
        auto it = pts.lower_bound(x);
        if (it != pts.begin()) l = (*--it) + 1, ++it;
        if (++it != pts.end()) r = (*it) - 1;
        add(l, r), pts.erase(x);
      }
    }
  }

  return 0;
}
