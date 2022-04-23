#include <bits/stdc++.h>
using namespace std;

using i64 = long long;
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

constexpr int kMod = 1e9 + 7;
constexpr int kMaxN = 3e5 + 3;
// mt19937 rnd(chrono::high_resolution_clock::now().time_since_epoch().count());

void solve() {
  int d, n, k;
  cin >> d >> n >> k;

  static pii events[kMaxN * 2];
  for (int i = 0; i < n; ++i) {
    int h, s, e;
    cin >> h >> s >> e;
    events[i * 2] = make_pair(s, h);
    events[i * 2 + 1] = make_pair(e + 1, -h);
  }
  sort(events, events + 2 * n);

  static multiset<int> topk;
  static multiset<int, greater<int>> rest;

  topk.clear();
  rest.clear();
  i64 sum = 0, ans = 0;
  auto add = [&](int x) {
    if (static_cast<int>(topk.size()) < k) {
      sum += x;
      topk.insert(x);
    } else if (x > *topk.begin()) {
      sum -= *topk.begin();
      rest.insert(*topk.begin());
      topk.erase(topk.begin());

      sum += x;
      topk.insert(x);
    } else {
      rest.insert(x);
    }
  };
  auto del = [&](int x) {
    auto iter = rest.find(x);
    if (iter != rest.end()) {
      rest.erase(iter);
      return;
    }

    iter = topk.find(x);
    topk.erase(iter);
    sum -= x;
    if (!rest.empty()) {
      sum += *rest.begin();
      topk.insert(*rest.begin());
      rest.erase(rest.begin());
    }
  };

  int n_2 = n * 2;
  for (int i = 1, j = 0; i <= d && j < n_2; ++i) {
    while (events[j].first == i) {
      if (events[j].second > 0) {
        add(events[j++].second);
      } else {
        del(-events[j++].second);
      }
    }

    ans = max(ans, sum);
  }
  cout << ans << "\n";
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr), cout.tie(nullptr);
  cout << fixed << setprecision(10);

  int o_o, v_v = 0;
  for (cin >> o_o; o_o; --o_o) {
    cout << "Case #" << ++v_v << ": ";
    solve();
  }
  return 0;
}
