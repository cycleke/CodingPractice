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
const ll mod = 1e9 + 7;
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
ll n, m;
ll qpow(ll x, ll y) {
  ll ret = 1;
  while (y) {
    if (y & 1) { ret = (ret * x) % mod; }
    x = (x * x) % mod;
    y >>= 1;
  }
  return ret;
}
ll c4 = qpow(4, mod - 2);
ll c6 = qpow(6, mod - 2);
ll c2 = qpow(2, mod - 2);
ll sum(ll n, int mi) {
  if (mi == 3) {
    return n * (n + 1) % mod * n % mod * (n + 1) % mod * c4 % mod;
  }
  if (mi == 2) { return n * (n + 1) % mod * (n + n + 1) % mod * c6 % mod; }
  if (mi == 1) {
    return n * (n + 1) % mod * c2 % mod;
    ;
  }
}
/*
a=n+1
(i-a)(i-2)(i-1)
i^3-(a+3)i^2+(3a+2)i-2a
*/
ll f(ll n, ll a) {
  return (mod - sum(n, 3) + (a + 3) * sum(n, 2) % mod + mod -
          (a * 3 + 2ll) * sum(n, 1) % mod + n * (a)*2ll) %
         mod;
}
ll ans = 0;

int main() {
  // cout<<f(4)<<endl;
  int T;
  T = read();
  int tt = 0;
  while (T--) {
    n = read();
    m = read();
    ans = f(n, n + 1) * f(m, m + 1) % mod * c4 % mod;
    printf("Case %d: %d\n", ++tt, ans);
  }
  return 0;
}
