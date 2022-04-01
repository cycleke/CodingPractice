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

constexpr int MAXN = 4e5 + 3;

int a[MAXN];

void solve() {
  int n;
  i64 ans = 0;
  cin >> n;
  for (int i = 1; i <= n; ++i) {
    cin >> a[i];
    ans += abs(a[i] - a[i - 1]);
  }
  ans += a[n];
  a[n + 1] = 0;
  for (int i = 1; i <= n; ++i) {
    if (a[i] <= a[i - 1] || a[i] <= a[i + 1]) { continue; }
    ans -= a[i] - max(a[i - 1], a[i + 1]);
  }
  cout << ans << "\n";
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr), cout.tie(nullptr);
  cout << fixed << setprecision(10);

  int o_o;
  for (cin >> o_o; o_o; --o_o) solve();
  return 0;
}
