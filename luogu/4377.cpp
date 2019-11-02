#include <bits/stdc++.h>
using namespace std;

const int MAXN = 250;
const int MAXW = 1e3 + 5;

int n, W, w[MAXN], t[MAXN];

bool gao(double x) {
  static double dp[MAXW];
  for (int i = 0; i <= W; ++i) dp[i] = -1e200;
  dp[0] = 0;
  for (int i = 0; i < n; ++i) {
    double val = t[i] - x * w[i];
    for (int j = W; ~j; --j) {
      int _w = min(j + w[i], W);
      dp[_w] = max(dp[_w], dp[j] + val);
    }
  }
  return dp[W] > 0;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  cin >> n >> W;
  for (int i = 0; i < n; ++i) cin >> w[i] >> t[i];

  double l = 0, r = 1e6;
  for (int step = 0; step < 100; ++step) {
    double mid = (l + r) * 0.5;
    (gao(mid) ? l : r) = mid;
  }

  cout << int(l * 1000) << '\n';
  return 0;
}

