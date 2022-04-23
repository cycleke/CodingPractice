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
constexpr int kMaxN = 5e5 + 3;
// mt19937 rnd(chrono::high_resolution_clock::now().time_since_epoch().count());

int dist[kMaxN];
char bins[kMaxN];
void solve() {
  int n, pre = INT_MIN / 2;
  cin >> n >> bins;
  for (int i = 0; i < n; ++i) {
    if (bins[i] == '1') {
      pre = i;
    }
    dist[i] = i - pre;
  }

  i64 ans = 0;
  pre = INT_MAX / 2;
  for (int i = n - 1; ~i; --i) {
    if (bins[i] == '1') {
      pre = i;
    }
    ans += min(pre - i, dist[i]);
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
