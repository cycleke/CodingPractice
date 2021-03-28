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

constexpr int MAXN = 1e6 + 3;

int h[MAXN], lhs[MAXN], rhs[MAXN], lc, rc, n;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr), cout.tie(nullptr);
  cout << fixed << setprecision(10);

  cin >> n;
  for (int i = 0; i < n; ++i) {
    cin >> h[i];
    while (rc && h[rhs[rc - 1]] <= h[i]) --rc;
    rhs[rc++] = i;
  }

  for (int i = n - 1; ~i; --i) {
    while (lc && h[lhs[lc - 1]] <= h[i]) --lc;
    lhs[lc++] = i;
  }
  reverse(lhs, lhs + lc);

  static auto calc = [&](int l, int r) {
    return 1ll * (h[lhs[l]] + h[rhs[r]]) * (rhs[r] - lhs[l]);
  };

  ll ans = 0;
  static function<void(int, int, int, int)> gao = [&](int a, int b, int c,
                                                      int d) {
    if (a > b) return;
    int m = (a + b) / 2, p = d;
    ll res = calc(m, d);
    for (int i = c; i < d; ++i) {
      ll temp = calc(m, i);
      if (temp > res) res = temp, p = i;
    }
    gao(a, m - 1, c, p);
    gao(m + 1, b, p, d);
    if (res > ans) ans = res;
  };

  gao(0, lc, 0, rc);
  cout << ans << "\n";

  return 0;
}
