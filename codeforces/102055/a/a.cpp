// by sineMora
#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <vector>
#define ll long long
#define ld long double
#define lson rt << 1, l, m
#define pi acos(-1)
#define rson rt << 1 | 1, m + 1, r
#define fo(i, l, r) for (int i = l; i <= r; i++)
#define fd(i, l, r) for (int i = r; i >= l; i--)
#define mem(x) memset(x, 0, sizeof(x))
#define eps 3e-11
using namespace std;
const ll maxn = 100050;
ll read() {
  ll x = 0, f = 1;
  char ch = getchar();
  while (!(ch >= '0' && ch <= '9')) {
    if (ch == '-') f = -1;
    ch = getchar();
  };
  while (ch >= '0' && ch <= '9') {
    x = x * 10 + (ch - '0');
    ch = getchar();
  };
  return x * f;
}
int n;
ll m;
struct dat {
  ll d;
  ll v;
  friend bool operator<(dat a, dat b) { return a.d < b.d; }
} dats[maxn];
int main() {
  int T;
  T = read();
  int tt = 0;
  while (T--) {
    n = read();
    m = read();
    fo(i, 1, n) { dats[i].d = read(); }
    fo(i, 1, n) { dats[i].v = read(); }
    sort(dats + 1, dats + 1 + n);
    int ans = 0;
    fo(i, 1, n) {
      m -= dats[i].v;
      if (m < 0)
        break;
      else
        ans++;
    }
    printf("Case %d: %d\n", ++tt, ans);
  }
  return 0;
}
