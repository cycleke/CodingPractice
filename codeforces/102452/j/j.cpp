
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 5000 + 3;
const int MAXM = 60;
const int MOD = 1e9 + 7;

int f[MAXN][MAXM][MAXM], mark[MAXN][MAXM][MAXM], clk, dig[MAXN], p[MAXN], m;

int gao(int pos, int sum, int delta, bool limit) {
  if (pos < 0) return delta == 0;
  if (!limit && mark[pos][sum][delta] == clk) return f[pos][sum][delta];
  int res = 0, bound = limit ? dig[pos] : 9;
  for (int i = 0; i <= bound; ++i) {
    int sum_ = (sum + i) % m;
    int delta_ = (delta + i * p[pos] - i * sum) % m;
    if (delta_ < 0) delta_ += m;
    res += gao(pos - 1, sum_, delta_, limit && i == bound);
    if (res >= MOD) res -= MOD;
  }
  if (!limit) f[pos][sum][delta] = res, mark[pos][sum][delta] = clk;
  return res;
}

char L[MAXN], R[MAXN];

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr), cout.tie(nullptr);

  int o_o;
  for (cin >> o_o; o_o; --o_o) {
    ++clk;
    cin >> L >> R >> m;
    int n = strlen(R);
    for (int i = p[0] = 1; i < n; ++i) p[i] = p[i - 1] * 10 % m;

    for (int i = 0; i < n; ++i) dig[i] = R[n - 1 - i] - '0';
    int ans = gao(n - 1, 0, 0, true);
    // cerr << "# " << ans << "\n";

    n = strlen(L);
    for (int i = 0; i < n; ++i) dig[i] = L[n - 1 - i] - '0';
    --dig[0];
    for (int i = 0; dig[i] < 0; ++i) { --dig[i + 1], dig[i] += 10; }
    while (!dig[n - 1]) --n;
    ans -= gao(n - 1, 0, 0, true);
    // cerr << "# " << ans << "\n";
    if (ans < 0) ans += MOD;
    cout << ans << "\n";
  }

  return 0;
}
