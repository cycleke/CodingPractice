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

constexpr int MAXN = 1e5 + 3;

ll sw[MAXN];
int h[MAXN], lhs[MAXN], rhs[MAXN], stk[MAXN];

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr), cout.tie(nullptr);

  int n;
  cin >> n;
  for (int i = 1, w; i <= n; ++i) {
    cin >> h[i] >> w;
    sw[i] = sw[i - 1] + w;
  }

  int top = 0;
  for (int i = 1; i <= n; ++i) {
    while (top && h[stk[top - 1]] > h[i]) rhs[stk[--top]] = i - 1;
    stk[top++] = i;
  }
  while (top) rhs[stk[--top]] = n;

  top = 0;
  for (int i = n; i; --i) {
    while (top && h[stk[top - 1]] > h[i]) lhs[stk[--top]] = i + 1;
    stk[top++] = i;
  }
  while (top) lhs[stk[--top]] = 1;

  ll ans = 0;
  for (int i = 1; i <= n; ++i) {
    debug(i, h[i], lhs[i], rhs[i]);
    ans = max(ans, (sw[rhs[i]] - sw[lhs[i] - 1]) * h[i]);
  }
  cout << ans << "\n";

  return 0;
}
