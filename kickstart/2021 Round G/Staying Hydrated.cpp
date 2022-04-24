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

constexpr int kMaxN = 2e5;
// mt19937 rnd(chrono::high_resolution_clock::now().time_since_epoch().count());

void solve() {
  static int xs[kMaxN * 2], ys[kMaxN * 2];

  int n;
  cin >> n;
  for (int i = 0; i < n; ++i) {
    cin >> xs[i << 1] >> ys[i << 1] >> xs[i << 1 | 1] >> ys[i << 1 | 1];
  }

  nth_element(xs, xs + n - 1, xs + 2 * n);
  nth_element(ys, ys + n - 1, ys + 2 * n);
  cout << xs[n - 1] << " " << ys[n - 1] << "\n";
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
