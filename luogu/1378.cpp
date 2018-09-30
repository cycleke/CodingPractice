#include <bits/stdc++.h>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  int n;
  cin >> n;
  int left, right, up, down;
  cin >> left >> down >> right >> up;
  if (down > up) swap(down, up);
  if (left > right) swap(left, right);

  int x[6], y[6];
  for (int i = 0; i < n; i++) {
    cin >> x[i] >> y[i];
  }

  double d[6][6];
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < i; j++) {
      d[i][j] = d[j][i] = sqrt(pow(x[i] - x[j], 2) + pow(y[i] - y[j], 2));
    }
  }

  int a[6];
  double max_cover = 0.0, r[6], sum_cover;
  for (int i = 0; i < n; i++) a[i] = i;
  do {
    sum_cover = 0.0;
    for (int i = 0; i < n; i++) {
      int u = a[i];
      r[u] = min({x[u] - left, right - x[u], y[u] - down, up - y[u]});
      for (int j = 0; j < i; j++)
        r[u] = min(r[u], d[u][a[j]] - r[a[j]]);
      r[u] = max(r[u], 0.0);
      sum_cover += r[u] * r[u] * M_PI;
    }
    max_cover = max(max_cover, sum_cover);
  } while(next_permutation(a, a + n));
  cout << int((up - down) * (right - left) - max_cover + 0.5) << endl;
  return 0;
}
