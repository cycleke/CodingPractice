#include <bits/stdc++.h>
using namespace std;

#define debug(...) fprintf(stderr, __VA_ARGS__)

const int MAXN = 1e5 + 3;

int h[MAXN];
pair<long long, int> f[MAXN], p[MAXN];

int main(int argc, char *argv[]) {
  ios::sync_with_stdio(false);
  cin.tie(nullptr), cout.tie(nullptr);
  cout << fixed << setprecision(10);

  int n, k;
  cin >> n >> k;
  int max_d = 0;
  for (int i = 0; i <= n; ++i) cin >> h[i];
  for (int i = 1; i <= n; ++i) max_d = max(max_d, h[i] - h[i - 1]);

  for (double x; k; --k) {
    cin >> x;
    int g = x * 10 + 0.5;
    if (g > max_d) {
      cout << "-1\n";
      continue;
    }
    for (int i = 0; i <= n; ++i) p[i] = f[i] = make_pair(h[i] - 1ll * g * i, i);
    sort(f, f + n + 1);

    int i = n + 1;
    double ans = 0;
    for (int _ = 0; _ <= n; ++_) {
      int j = f[_].second;
      if (j > i) {
        double ext = 0;
        if (j < n && p[j + 1].first != p[j].first)
          ext = max(ext, fabs(1.0 * (p[j].first - p[i].first) /
                              (p[j + 1].first - p[j].first)));
        if (i > 0 && p[i - 1].first != p[i].first)
          ext = max(ext, fabs(1.0 * (p[j].first - p[i].first) /
                              (p[i].first - p[i - 1].first)));
        if (ext > 1) ext = 1;
        ans = max(ans, j - i + ext);
      }
      i = min(i, j);
    }

    cout << ans << "\n";
  }

  return 0;
}
