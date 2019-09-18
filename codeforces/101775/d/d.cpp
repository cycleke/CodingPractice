#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MAXN = 1e5;

vector<ll> a;
ll p10[20] = {1};

inline int gao(ll n) {
  int res = 0;
  while (n) {
    ++res;
    n /= 10;
  }
  return res;
}

void init() {
  for (int i = 1; i < 20; ++i) p10[i] = 10 * p10[i - 1];
  for (int p = 1; p <= MAXN; ++p) {
    for (int q = p + 1; q <= MAXN / p; ++q) {
      if (__gcd(p, q) != 1) continue;
      for (int r = 1; r <= MAXN / p / q; ++r) {
        ll x = 1LL * p * p * r;
        ll y = 1LL * p * q * r;
        ll z = 1LL * q * q * r;
        int nx = gao(x), ny = gao(y), nz = gao(z);
        if (nx + ny + nz > 15) break;
        ll cur = x * p10[ny + nz] + y * p10[nz] + z;
        a.push_back(cur);

        nx += ny + nz;
        int n_x;
        while (z % p == 0) {
          z = z / p * q;
          n_x = gao(z);
          if (nx + n_x > 15) break;
          nx += n_x;
          cur = cur * p10[n_x] + z;
          a.push_back(cur);
        }
      }
    }
  }
  sort(a.begin(), a.end());
  a.erase(unique(a.begin(), a.end()), a.end());
}

inline int sum(const ll &n) {
  return upper_bound(a.begin(), a.end(), n) - a.begin();
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  init();

  int o_o, i = 1;
  ll l, r;
  for (cin >> o_o; i <= o_o; ++i) {
    cin >> l >> r;
    cout << "Case #" << i << ": " << sum(r) - sum(l - 1) << '\n';
  }

  return 0;
}
