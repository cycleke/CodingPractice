#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

inline ll mod_mul(const ll &a, const ll &b, const ll &mod) {
  ll k = (ll)((1.0L * a * b) / (1.0L * mod)), t = a * b - k * mod;
  t -= mod;
  while (t < 0) t += mod;
  return t;
}
inline ll mod_pow(ll a, ll b, const ll &mod) {
  ll res = 1;
  for (; b; b >>= 1, a = mod_mul(a, a, mod))
    (b & 1) && (res = mod_mul(res, a, mod));
  return res;
}

ll exgcd(ll a, ll b, ll &x, ll &y) {
  if (b == 0) return x = 1, y = 0, a;
  ll g = exgcd(b, a % b, y, x);
  y -= a / b * x;
  return g;
}

void solve(int case_num) {
  cout << "Case " << case_num << ": ";

  ll n, c;
  cin >> n >> c;

  ll phi = 1, lim = sqrt(n);
  for (ll p = lim;; ++p)
    if (n % p == 0) {
      phi = (p - 1) * (n / p - 1);
      break;
    }

  static const ll a = (1 << 30) + 3;
  ll x, y;
  exgcd(a, phi, x, y);
  x = (phi + x % phi) % phi;
  cout << mod_pow(c, x, n) << '\n';
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int o_o;
  cin >> o_o;
  for (int case_num = 1; case_num <= o_o; ++case_num) solve(case_num);

  return 0;
}
