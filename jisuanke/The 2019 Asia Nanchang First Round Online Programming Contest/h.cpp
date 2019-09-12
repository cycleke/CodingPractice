#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MAXN = 1e7 + 5;
const int MOD = 998244353;
const int CYCLE = 499122176;

struct Mat {
  int a, b, c, d;
} px;

inline Mat mul(const Mat &a, const Mat &b) {
  static Mat res;
  res.a = (1LL * a.a * b.a + 1LL * a.b * b.c) % MOD,
  res.b = (1LL * a.a * b.b + 1LL * a.b * b.d) % MOD,
  res.c = (1LL * a.c * b.a + 1LL * a.d * b.c) % MOD,
  res.d = (1LL * a.c * b.b + 1LL * a.d * b.d) % MOD;
  return res;
}

inline Mat pow(Mat a, int n) {
  static Mat res;
  for (res = {1, 0, 0, 1}; n; n >>= 1, a = mul(a, a))
    if (n & 1) res = mul(res, a);
  return res;
}

int f[MAXN];

inline int cal(ll n) {
  if (n < MAXN) return f[n];
  n %= CYCLE;
  if (n < MAXN) return f[n];
  static Mat a;
  static ll fa, fb;
  a = pow(px, n / MAXN);
  n %= MAXN;
  fa = f[n];
  fb = n ? f[n - 1] : f[MAXN - 1];
  return (a.a * fa + a.b * fb) % MOD;
}

pair<ll, int> record[MAXN];

int main(int argc, char *argv[]) {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout << fixed << setprecision(10);

  f[0] = 0, f[1] = 1;
  for (register int i = 2; i ^ MAXN; ++i)
    f[i] = (3LL * f[i - 1] + 2LL * f[i - 2]) % MOD;
  px = pow({3, 2, 1, 0}, MAXN);
  ll n;
  int q, ans = 0, fn, cnt = 0, i;
  for (cin >> q >> n; q; --q) {
    ans ^= (fn = cal(n));
    record[cnt++] = make_pair(n, fn);
    n ^= 1LL * fn * fn;
    if (n == record[0].first) break;
  }
  for (--q, i = 0; q > 0; --q, ++i) {
    if (i == cnt) i = 0;
    ans ^= record[i].second;
  }
  cout << ans << '\n';

  return 0;
}
