#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1e5 + 5;
const int MAXW = 1e8 + 5;

int dp[MAXW];

struct Frog {
  int l, w, h;
} f[MAXN];

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n, d, ans = 0;
  cin >> n >> d;
  for (int i = 0; i < n; ++i) cin >> f[i].l >> f[i].w >> f[i].h;

  sort(f, f + n, [&](const Frog &a, const Frog &b) { return a.w > b.w; });
  for (int i = 0; i < n; ++i) {
    if (dp[f[i].w] + f[i].l > d) ++ans;
    for (int j = f[i].w, end = min(2 * f[i].w, MAXW); j < end; ++j)
      dp[j - f[i].w] = max(dp[j - f[i].w], dp[j] + f[i].h);
  }
  cout << ans << '\n';
  return 0;
}
