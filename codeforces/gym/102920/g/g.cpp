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

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr), cout.tie(nullptr);
  cout << fixed << setprecision(1);

  int n;
  ll a, d, ds = 0, imi = LLONG_MAX, imx = LLONG_MIN, dmi = LLONG_MAX,
           dmx = LLONG_MIN;
  cin >> n >> d;
  for (int i = 0; i < n; ++i, ds += d) {
    cin >> a;
    a -= ds;
    imi = min(imi, a), imx = max(imx, a);
    a += 2 * ds;
    dmi = min(dmi, a), dmx = max(dmx, a);
  }

  ll ans = min(dmx - dmi, imx - imi);
  cout << ans / 2 << ((ans & 1) ? ".5\n" : ".0\n");

  return 0;
}
