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

double dp[MAXN];

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr), cout.tie(nullptr);
  cout << fixed << setprecision(10);

  int n, a, b;
  cin >> n >> a >> b;

  int l = b - a + 1;
  double sum = 0;
  for (int i = n - 1; ~i; --i) {
    if (a > 0) {
      dp[i] = sum / l + 1;
      if (i + a - 1 < n) sum += dp[i + a - 1];
    } else {
      dp[i] = sum / (l - 1) + l / (l - 1.0);
      sum += dp[i];
    }
    if (i + b < n) sum -= dp[i + b];
  }
  cout << dp[0] << "\n";

  return 0;
}
