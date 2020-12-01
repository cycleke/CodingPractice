#include <bits/stdc++.h>
using namespace std;

#define debug(...) fprintf(stderr, __VA_ARGS__)

const int MAXN = 3e5 + 3;

int rk[MAXN], pt[MAXN], last[MAXN];
long long sum[MAXN], pre[MAXN], ans[MAXN];

int main(int argc, char *argv[]) {
  ios::sync_with_stdio(false);
  cin.tie(nullptr), cout.tie(nullptr);
  cout << fixed << setprecision(9);

  int n, w;
  cin >> n >> w;
  rk[0] = 1;
  for (int i = 0; i < w; ++i) {
    int k, x, p;
    for (cin >> k; k; --k) {
      cin >> x;
      p = pt[x];
      sum[p] += 1ll * rk[p] * (i - last[p]);
      last[p] = i, ++rk[p];
      ans[x] += sum[p] - pre[x];

      p = ++pt[x];
      sum[p] += 1ll * rk[p] * (i - last[p]);
      last[p] = i;
      if (rk[p] == 0) rk[p] = 1;
      pre[x] = sum[p];
    }
  }

  for (int i = 1; i <= n; ++i) {
    int p = pt[i];
    sum[p] += 1ll * rk[p] * (w - last[p]);
    last[p] = w;
    cout << (ans[i] + sum[p] - pre[i]) * 1.0 / w << "\n";
  }

  return 0;
}
