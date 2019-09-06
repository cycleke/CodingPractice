// by OwenCreeper
#include "bits/stdc++.h"
#define N 200000
using namespace std;
typedef long long ll;
int nx[N + 5], x[N + 5], ny[N + 5], y[N + 5], Case = 0, ctx[N + 5], cty[N + 5],
                                              n;
void work() {
  Case++;
  scanf("%d", &n);
  for (int i = 1; i <= n; i++) {
    scanf("%d%d", x + i, y + i);
    nx[i] = x[i], ny[i] = y[i];
  }
  sort(nx + 1, nx + 1 + n);
  sort(ny + 1, ny + 1 + n);
  int cx, cy;
  cx = unique(nx + 1, nx + 1 + n) - nx - 1;
  cy = unique(ny + 1, ny + 1 + n) - ny - 1;
  int mxx = 0, mxy = 0;
  for (int i = 1; i <= n; i++) {
    x[i] = lower_bound(nx + 1, nx + 1 + cx, x[i]) - nx;
    y[i] = lower_bound(ny + 1, ny + 1 + cy, y[i]) - ny;
    ctx[x[i]]++, cty[y[i]]++;
    mxx = max(mxx, ctx[x[i]]), mxy = max(mxy, cty[y[i]]);
  }
  int lx0 = 0, lx1 = 0, ly0 = 0, ly1 = 0;
  for (int i = 1; i <= cx; i++)
    if (ctx[i] == mxx)
      lx0++;
    else if (ctx[i] == mxx - 1)
      lx1++;
  for (int i = 1; i <= cy; i++)
    if (cty[i] == mxy)
      ly0++;
    else if (cty[i] == mxy - 1)
      ly1++;
  ll ans2 = lx0 * 1ll * ly0;
  // printf("lx = %d ly = %d\n", lx0, ly0);
  for (int i = 1; i <= n; i++)
    if (ctx[x[i]] == mxx && cty[y[i]] == mxy) {
      // printf("%d %d\n", x[i], y[i]);
      ans2--;
    }
  int ans1 = mxx + mxy;
  if (ans2 == 0) {
    ans1--;
    ans2 = lx0 * 1ll * ly0;
    ans2 += lx1 * 1ll * ly0;
    for (int i = 1; i <= n; i++)
      if (ctx[x[i]] == mxx - 1 && cty[y[i]] == mxy) ans2--;
    ans2 += lx0 * 1ll * ly1;
    for (int i = 1; i <= n; i++)
      if (ctx[x[i]] == mxx && cty[y[i]] == mxy - 1) ans2--;
  }
  if (ans1 == 1) ans2 = n;
  if (ans1 == 2) ans2 /= 2;
  printf("Case %d: %d %lld\n", Case, ans1, ans2);
  for (int i = 1; i <= cx; i++) ctx[i] = 0;
  for (int i = 1; i <= cy; i++) cty[i] = 0;
}
int main(int argc, char const *argv[]) {
  int T;
  scanf("%d", &T);
  while (T--) work();
  return 0;
}
