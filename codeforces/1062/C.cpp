#include <bits/stdc++.h>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  int n, q;
  string s;
  cin >> n >> q >> s;
  vector<int> sum(n + 1, 0);
  for (int i = 0; i < n; i++) {
    sum[i + 1] = sum[i] + s.at(i) - '0';
  }

  const int MOD = int(1e9 + 7);
  auto ModPow = [MOD](int a, int b) {
    int res = 1;
    while (b) {
      if (b & 1) {
        res = (long long)res * a % MOD;
      }
      a = (long long)a * a % MOD;
      b >>= 1;
    }
    return res;
  };
  while (q--) {
    int l, r;
    cin >> l >> r;
    int a = r - l + 1, b = sum[r] - sum[l - 1];
    cout << ((long long)ModPow(2, b) - 1 + MOD) % MOD * ModPow(2, a - b) % MOD
         << endl;
  }
  return 0;
}
