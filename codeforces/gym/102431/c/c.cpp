#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

void debug_out() { cerr << endl; }

template <typename Head, typename... Tail> void debug_out(Head H, Tail... T) {
  cerr << " " << to_string(H);
  debug_out(T...);
}

#define debug(...) cerr << "[" << #__VA_ARGS__ << "]:", debug_out(__VA_ARGS__)

const int MOD = 1e9 + 7;
const int MAXN = 5e3 + 3;
const ll INF = 0x3f3f3f3f3f3f3f3fll;

void solve() {
  static ll dp[MAXN][MAXN];
  static int s[MAXN], lcs[MAXN][MAXN], pre[MAXN][MAXN];

  int n;
  ll x, y, z;
  cin >> n >> x >> y >> z;
  for (int i = 1; i <= n; ++i) cin >> s[i];
  for (int i = 1; i <= n; ++i)
    for (int j = 1; j <= i; ++j)
      lcs[i][j] = s[i] == s[j] ? lcs[i - 1][j - 1] + 1 : 0;
  for (int i = 1; i <= n; ++i) {
    memset(pre[i] + 1, -1, sizeof(int) * n);
    for (int j = 1; j < i; ++j) pre[i][min(i - j, lcs[i][j])] = j;
    for (int j = i - 1; j; --j) pre[i][j] = max(pre[i][j], pre[i][j + 1]);
  }

  for (int i = 0; i <= n; ++i) memset(dp[i], 0x3f, sizeof(ll) * (n + 1));
  dp[1][0] = x;
  for (int i = 2; i <= n; ++i) {
    dp[i][0] = dp[i - 1][0] + x;
    for (int j = 1; j <= i; ++j) {
      if (pre[i][j] == -1) continue;
      dp[i][j] = min({dp[i][j], dp[i - j][0] + y + z,
                      dp[pre[i][j]][j] + x * (i - j - pre[i][j]) + z});
      dp[i][0] = min(dp[i][0], dp[i][j]);
    }
  }
  cout << dp[n][0] << "\n";
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr), cout.tie(nullptr);
  cout << fixed << setprecision(10);

  int o_o, omo = 0;
  for (cin >> o_o; omo < o_o; solve()) cout << "Case #" << ++omo << ": ";
  return 0;
}
