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
constexpr int MAXN = 1e6 + 3;

int inv[MAXN], c[MAXN], num[MAXN], cnt[MAXN];

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr), cout.tie(nullptr);
  cout << fixed << setprecision(10);

  int n, m;
  cin >> n;
  m = n + 1;
  c[1] = inv[1] = 1;
  for (int i = 2; i <= m; ++i)
    inv[i] = 1ll * (MOD - MOD / i) * inv[MOD % i] % MOD;
  for (int i = 2; i <= n; ++i)
    c[i] = 1ll * c[i - 1] * (4 * i - 2) % MOD * inv[i + 1] % MOD;

  int ans = 1, top = 0;
  for (int x; n; --n) {
    cin >> x;
    while (top && num[top - 1] > x) ans = 1ll * ans * c[cnt[--top]] % MOD;

    if (top && num[top - 1] == x) {
      ++cnt[top - 1];
    } else {
      num[top] = x, cnt[top++] = 1;
    }
  }
  while (top) ans = 1ll * ans * c[cnt[--top]] % MOD;
  cout << ans << "\n";

  return 0;
}
