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

inline bool check(const ll &x, const ll &p) {
  if (!(x % p) || mod_pow(p % x, x - 1, x) ^ 1) return false;
  ll k = x - 1, t;
  while (~k & 1) {
    if (((t = mod_pow(p % x, k >>= 1, x)) ^ 1) && (t ^ (x - 1))) return false;
    if (!(t ^ (x - 1))) return true;
  }
  return true;
}

inline bool Miller_Rabin(const ll &x) {
  if (x < 2) return false;
  static const int p[12] = {2, 3, 5, 7, 11, 13, 17, 19, 61, 2333, 4567, 24251};
  for (register int i = 0; i < 12; ++i) {
    if (!(x ^ p[i])) return true;
    if (!check(x, p[i])) return false;
  }
  return true;
}

void solve(int case_num) {
  cout << "Case " << case_num << ": ";

  ll n;
  cin >> n;
  if (n < 12) {
    cout << "IMPOSSIBLE\n";
    return;
  }

  if (n & 1) {
    n -= 9;
    cout << "2 2 2 3 ";
  } else {
    n -= 8;
    cout << "2 2 2 2 ";
  }

  for (ll i = n / 2; i; --i)
    if (Miller_Rabin(i) && Miller_Rabin(n - i)) {
      cout << i << ' ' << n - i << '\n';
      break;
    }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int o_o;
  cin >> o_o;
  for (int case_num = 1; case_num <= o_o; ++case_num) solve(case_num);

  return 0;
}
