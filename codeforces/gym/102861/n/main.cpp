#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1e3 + 3;
using ll = long long;

ll read() {
  ll x = 0; char ch;
  while (!isdigit(ch = getchar())) {}
  while (isdigit(ch)) x = x * 10 + (ch ^ 48), ch = getchar();
  return x;
}

ll c[MAXN], a[MAXN];
vector<int> adj[MAXN];

ll mmul(const ll &a, const ll &b, const ll &mod) {
  ll k = (ll)((1.0L * a * b) / (1.0L * mod)), t = a * b - k * mod;
  for (t -= mod; t < 0;)
    t += mod;
  return t;
}

ll mpow(ll a, ll b, const ll &mod) {
  ll r = 1;
  for (; b; b >>= 1, a = mmul(a, a, mod))
    (b & 1) && (r = mmul(r, a, mod));
  return r;
}

bool check(const ll &x, const ll &p) {
  if (!(x % p) || mpow(p % x, x - 1, x) ^ 1)
    return false;
  for (ll k = x - 1, t; ~k & 1;) {
    if (((t = mpow(p % x, k >>= 1, x)) ^ 1) && (t ^ (x - 1)))
      return false;
    if (!(t ^ (x - 1)))
      return true;
  }
  return true;
}

bool Miller_Rabin(const ll &x) {
  if (x < 2)
    return false;
  static const int p[] = {2, 3, 5, 11, 2333};
  for (int pp : p) {
    if (!(x ^ pp))
      return true;
    if (!check(x, pp))
      return false;
  }
  return true;
}

mt19937_64 rnd(chrono::high_resolution_clock::now().time_since_epoch().count());
ll rnd64(ll x) { return rnd() % x + 1; }

ll Pollard_rho(const ll &x, const int &y) {
  ll v0 = rnd64(x), v = v0, d, s = 1;
  for (int t = 0, k = 1;;) {
    v = (mmul(v, v, x) + y) % x, s = mmul(s, abs(v - v0), x);
    if (!(v ^ v0) || !s)
      return x;
    if (++t == k) {
      if ((d = __gcd(s, x)) ^ 1)
        return d;
      v0 = v, k <<= 1;
    }
  }
}

int fc;
ll factor[MAXN];
void findfac(ll n) {
  if (Miller_Rabin(n)) {
    factor[fc++] = n;
    return;
  }
  ll p = n;
  while (p >= n)
    p = Pollard_rho(p, rnd64(n));
  findfac(p), findfac(n / p);
}

int main() {
  int m = read(), n = read(), k = read();
  for (int i = 1; i <= n; ++i) c[i] = read();
  for (int u, v; k; --k) {
    u = read(), v = read(), read();
    adj[v].push_back(u);
  }

  int cnt = m;

  static int idn[MAXN];
  iota(idn, idn + n, 1);
  sort(idn, idn + n, [&](const int &x, const int &y) { return c[x] < c[y]; });

  for (int idx = 0; idx < n && cnt; ++idx) {
    int i = idn[idx];
    for (int v : adj[i]) {
      if (a[v] == 0) continue;
      while (c[i] % a[v] == 0) c[i] /= a[v];
    }
    if (c[i] == 1) continue;
    fc = 0;
    findfac(c[i]);
    sort(factor, factor + fc);
    sort(adj[i].begin(), adj[i].end());

    fc = unique(factor, factor + fc) - factor;

    int j = 0;
    for (int v : adj[i]) {
      if (a[v]) continue;
      --cnt;
      a[v] = factor[j++];
    }
  }

  for (int i = 1; i <= m; ++i) printf("%lld%c", a[i], " \n"[i == m]);

  return 0;
}
