#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<int, int> pii;

const int MOD = 1e9 + 7;
const int MAXN = 2e5 + 3;
// mt19937 rnd(chrono::high_resolution_clock::now().time_since_epoch().count());

int n, a[MAXN];
ll dp[MAXN][3][2][2];

void cmax(ll &a, ll b) {
  if (a < b) a = b;
}

int main(int argc, char *argv[]) {
  ios::sync_with_stdio(false);
  cin.tie(nullptr), cout.tie(nullptr);
  cout << fixed << setprecision(10);

  cin >> n;
  for (int i = 1; i <= n; ++i) cin >> a[i];
  if (n == 1) {
    cout << a[1] << "\n";
    return 0;
  }

  memset(dp, 0xc0, sizeof(dp));
  dp[1][n % 3][0][0] = a[1];
  dp[1][(n + 1) % 3][0][1] = -a[1];
  for (int i = 1; i < n; ++i)
    for (int j = 0; j < 3; ++j)
      for (int k = 0; k < 2; ++k)
        for (int l = 0; l < 2; ++l) {
          if (dp[i][j][k][l] == 0xc0c0c0c0) continue;
          cmax(dp[i + 1][j][k || l == 0][0], dp[i][j][k][l] + a[i + 1]);
          cmax(dp[i + 1][(j + 1) % 3][k || l == 1][1],
               dp[i][j][k][l] - a[i + 1]);
        }

  cout << max(dp[n][1][1][0], dp[n][1][1][1]) << "\n";

  return 0;
}
