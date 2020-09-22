#pragma GCC optimize(2)
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

inline ll mmul(ll a, ll b, ll mod) {
  ll k = (ll)((1.0L * a * b) / (1.0L * mod)), t = a * b - k * mod;
  for (t -= mod; t < 0; t += mod) {}
  return t;
}

inline ll mpow(ll a, ll b, ll mod) {
  ll res = 1;
  for (; b; b >>= 1, a = mmul(a, a, mod)) (b & 1) && (res = mmul(res, a, mod));
  return res;
}

inline bool check(ll x, ll p) {
  if (!(x % p) || (mpow(p % x, x - 1, x) ^ 1)) return false;
  ll k = x - 1, t;
  while (~k & 1) {
    if (((t = mpow(p % x, k >>= 1, x)) ^ 1) && (t ^ (x - 1))) return false;
    if (!(t ^ (x - 1))) return true;
  }
  return true;
}

inline bool Miller_Rabin(ll x) {
  if (x < 2) return true;
  static const int p[12] = {2, 3, 5, 7, 11, 13, 17, 19, 61, 2333, 4567, 24251};
  for (int i = 0; i < 12; ++i) {
    if (!(x ^ p[i])) return true;
    if (!check(x, p[i])) return false;
  }
  return true;
}

mt19937_64 rnd(chrono::high_resolution_clock::now().time_since_epoch().count());

inline ll rand64(ll x) { return rnd() % (x - 1) + 1; }

inline ll Pollard_rho(ll x, int y) {
  ll v0 = rand64(x), v = v0, d, s = 1;
  for (int t = 0, k = 1;;) {
    if (v = (mmul(v, v, x) + y) % x, s = mmul(s, abs(v - v0), x),
        !(v ^ v0) || !s)
      return x;
    if (++t == k) {
      if ((d = __gcd(s, x)) ^ 1) return d;
      v0 = v, k <<= 1;
    }
  }
}

vector<ll> factor;
void find_factor(ll n) {
  if (Miller_Rabin(n)) {
    factor.push_back(n);
    return;
  }
  ll p = n;
  while (p >= n) p = Pollard_rho(p, rand64(n));
  find_factor(p), find_factor(n / p);
}

const int MAX_FACTOR = 100;
ll ex[MAX_FACTOR], ey[MAX_FACTOR], ez[MAX_FACTOR];

void gao(ll x, ll *e) {
  for (int i = 0; i < static_cast<int>(factor.size()); ++i) {
    for (ll x_ = x, f = factor[i]; x_; x_ /= f) e[i] += x_ / f;
  }
}

void solve() {
  int n;
  ll x, y, a;
  cin >> n >> x >> y;
  memset(ex, 0, sizeof(ex));
  memset(ey, 0, sizeof(ey));
  memset(ez, 0, sizeof(ez));
  factor.clear();
  find_factor(x);
  sort(factor.begin(), factor.end());
  factor.erase(unique(factor.begin(), factor.end()), factor.end());

  for (int i = 0; i < static_cast<int>(factor.size()); ++i) {
    for (ll x_ = x, f = factor[i]; x_ % f == 0; x_ /= f) ++ex[i];
  }

  gao(y, ey);
  for (int i = 0; i < n; ++i) {
    cin >> a;
    gao(a, ez);
  }

  ll ans = LLONG_MAX;
  for (int i = 0; i < static_cast<int>(factor.size()); ++i)
    ans = min(ans, (ey[i] - ez[i]) / ex[i]);

  cout << ans << "\n";
}

int main(int argc, char *argv[]) {
  ios::sync_with_stdio(false);
  cin.tie(nullptr), cout.tie(nullptr);

  int T;
  for (cin >> T; T; --T) solve();

  return 0;
}
