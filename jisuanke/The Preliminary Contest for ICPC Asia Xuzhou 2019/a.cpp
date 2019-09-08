#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

ll exgcd(ll a, ll b, ll &x, ll &y) {
  if (!b) return x = 1, y = 0, a;
  ll g = exgcd(b, a % b, y, x);
  return y -= a / b * x, g;
}

ll excrt(int n, ll *a, ll *r) {
  ll x, y, g, res = 0, M = 1;
  for (int i = 0; i < n; ++i) {
    g = exgcd(M, a[i], x, y);
    if ((r[i] - res) % g) return -1;
    x = (x * (r[i] - res) / g + a[i] / g) % (a[i] / g);
    y = M / g * a[i];
    res = ((x * M + res) % y) % y;
    if (res < 0) res += y;
    M = y;
  }
  return res;
}

ll a[15], r[15];

int main(int argc, char *argv[]) {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n;
  cin >> n;
  for (int i = 0; i < n; ++i) cin >> a[i] >> r[i];
  ll x = excrt(n, a, r);

  if (x == -1 || x > 1e15) {
    cout << "Tankernb!\n";
    return 0;
  }

  auto gao = [&](ll x) {
    if (x == 2 || x == 3) return true;
    ll a = 2, b = 3, c = 5;
    while (c < x) a = b, b = c, c = a + b;
    return c == x;
  };

  cout << (gao(x) ? "Lbnb!\n" : "Zgxnb!\n");

  return 0;
}
