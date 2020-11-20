#include <bits/stdc++.h>
using namespace std;

const int MOD = 1e9 + 7;
const int MAXN = 1e5 + 5;

int n, m, a[MAXN], b[MAXN];
int ca[MAXN], cb[MAXN], sum[MAXN],vis[MAXN], vis_c;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int case_count = 0;
  while (cin >> n >> m) {
    cout << "Case #" << ++case_count << ": ";
    for (int i = 0; i < n; ++i) cin >> a[i];
    for (int i = 0; i < m; ++i) cin >> b[i];
    memset(ca, 0, sizeof(int) * (n + 1));
    memset(cb, 0, sizeof(int) * (m + 1));
    memset(sum, 0, sizeof(int) * (n + 1));
    ++vis_c;
    for (int i = 0; i < n; ++i) {
      if (vis[i] == vis_c) continue;
      int x = i, c = 0;
      do { ++c, vis[x] = vis_c, x = a[x]; } while (x ^ i);
      ++ca[c];
    }
    ++vis_c;
    for (int i = 0; i < m; ++i) {
      if (vis[i] == vis_c) continue;
      int x = i, c = 0;
      do { ++c, vis[x] = vis_c, x = b[x]; } while (x ^ i);
      ++cb[c];
    }

    for (int i = 1; i <= m; ++i)
      for (int j = i; j <= n; j += i)
        sum[j] = (sum[j] + 1LL * i * cb[i]) % MOD;
    int ans = 1;
    for (int i = 1; i <= n; ++i)
      for (int j = 0; j < ca[i]; ++j)
        ans *= sum[i];
    cout << ans << '\n';
  }

  return 0;
}
