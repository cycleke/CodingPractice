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

constexpr int MAXN = 50 + 3;

int p[MAXN];

void solve() {
  int n, k, pr;
  cin >> n >> k >> pr;
  if (k >= n - 1) {
    int ans = 1;
    for (int i = 1; i <= n; ++i) ans = 1ll * ans * i % pr;
    cout << ans << "\n";
  } else {
    p[0] = 1;
    for (int i = 1; i <= n; ++i) p[i] = 1ll * p[i - 1] * (k + 1) % pr;

    int ans = p[n - k];
    for (int i = 2; i <= n - k; ++i)
      ans = (ans + 1ll * (n - k - i + 1) * p[n - k - 1]) % pr;
    for (int i = 3; i <= n - k; ++i)
      ans = (ans + 1ll * (n - k - i + 1) * p[n - k - i + 1]) % pr;
    for (int i = 1; i <= k; ++i) ans = 1ll * ans * i % pr;
    cout << ans << "\n";
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr), cout.tie(nullptr);
  cout << fixed << setprecision(6);

  int v_v = 0, o_o;
  for (cin >> o_o; v_v < o_o; solve()) cout << "Case #" << ++v_v << ": ";

  return 0;
}
