#include <bits/stdc++.h>
using namespace std;

typedef pair<int, int> pii;
typedef long long ll;
typedef vector<int> vi;
typedef vector<long long> vll;

const int MOD = 1e9 + 7;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);

  int n, x, y;
  cin >> n >> x >> y;
  int a[n], b[n];
  int ans = 0;
  for (int i = 0; i < n; i++) {
    cin >> a[i] >> b[i];
    ans = (ans + ll(x) + ll(b[i] - a[i]) * y % MOD) % MOD;
  }
  sort(a, a + n);
  sort(b, b + n);
  bool vis[n];
  memset(vis, 0, sizeof(bool) * n);
  int len = x / y;
  for (int i = n - 1; ~i; i--) {
    int p = upper_bound(a, a + n, b[i]) - a;
    while (vis[p] && p < n && a[p] - b[i] <= len) {
      p++;
    }
    // cout << p << endl;
    if (p < n && a[p] - b[i] <= len) {
      // cout << "#" << a[p] << " " << b[i] << endl;
      vis[p] = true;
      ans = (ll(ans) + MOD - ll(x) + ll(a[p] - b[i]) * y % MOD) % MOD;
    }
  }
  cout << ans << endl;
  return 0;
}
