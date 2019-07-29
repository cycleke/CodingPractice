#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <set>
#include <string>
#define fo(i, l, r) for (int i = l; i <= r; i++)
#define ll long long
using namespace std;
const int maxn = 1050;
ll read() {
  char ch = getchar();
  ll f = 1, x = 0;
  while (!(ch >= '0' && ch <= '9')) {
    if (ch == '-')
      f = -1;
    ch = getchar();
  };
  while (ch >= '0' && ch <= '9') {
    x = x * 10 + (ch - '0');
    ch = getchar();
  };
  return x * f;
}
ll xa, xb, xc, ya, yb, yc;
int main() {
  while (scanf("%lld%lld%lld%lld%lld%lld", &xa, &ya, &xb, &yb, &xc, &yc) !=
         EOF) {
    ll ans = (xa * yb + xb * yc + xc * ya - xa * yc - xb * ya - xc * yb) * 11ll;
    if (ans < 0)
      ans = -ans;
    printf(("%lld\n"), ans);
  }
  return 0;
}
