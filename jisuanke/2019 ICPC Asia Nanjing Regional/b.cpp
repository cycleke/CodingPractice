#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<int, int> pii;

const int MOD = 1e9 + 7;
const int MAXN = 2e6 + 3;

int fac[MAXN], inv[MAXN], fac_inv[MAXN];

int main(int argc, char *argv[]) {
  ios::sync_with_stdio(false);
  cin.tie(nullptr), cout.tie(nullptr);
  cout << fixed << setprecision(10);

  fac[0] = fac[1] = 1;
  inv[1] = fac_inv[0] = fac_inv[1] = 1;
  for (int i = 2; i < MAXN; ++i) {
    fac[i] = 1ll * fac[i - 1] * i % MOD;
    inv[i] = 1ll * (MOD - MOD / i) * inv[MOD % i] % MOD;
    fac_inv[i] = 1ll * fac_inv[i - 1] * inv[i] % MOD;
  }

  int o_o, n, m;
  for (cin >> o_o; o_o; --o_o) {
    cin >> n >> m;
    if (n == 1 && m == 1) {
      cout << "1\n";
    } else if (n == 1 || m == 1) {
      cout << "2\n";
    } else {
      cout << 4ll * fac[n + m - 2] * fac_inv[n - 1] % MOD * fac_inv[m - 1] % MOD
           << "\n";
    }
  }

  return 0;
}
