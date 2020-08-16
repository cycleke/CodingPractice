#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef vector<pii> vpii;

const int MOD = 1e9 + 7;
const int MAXV = 2e6 + 3;
mt19937 rnd(chrono::high_resolution_clock::now().time_since_epoch().count());

vi primes;
bitset<MAXV> vis;
int min_factor[MAXV];

void prework() {
  for (int i = 2; i < MAXV; ++i) {
    if (!vis[i]) {
      primes.push_back(i);
      min_factor[i] = i;
    }
    for (int p : primes) {
      int t = i * p;
      if (t >= MAXV) break;
      vis.set(t);
      min_factor[t] = p;
      if (i % p == 0) break;
    }
  }
}

int exgcd(int a, int b, ll &x, ll &y) {
  if (b == 0) return x = 1, y = 0, a;
  int g = exgcd(b, a % b, y, x);
  y -= a / b * x;
  return g;
}

void solve() {
  int a, b;
  cin >> a >> b;
  if (b == 1) {
    cout << "-1 -1 -1 -1\n";
    return;
  }

  int g = __gcd(a, b);
  if (g > 1) {
    a /= g, b /= g;
    cout << a + 1 << " " << b << " " << 1 << " " << b << "\n";
  } else {
    int d = 1, f = b;
    for (int t = min_factor[f]; min_factor[f] == t; f /= t) d *= t;
    if (f == 1) {
      cout << "-1 -1 -1 -1\n";
      return;
    }
    ll x, y;
    exgcd(d, f, x, y);
    if (x > 0) {
      cout << x * a << " " << f << " " << -y * a << " " << d << "\n";
    } else {
      cout << y * a << " " << d << " " << -x * a << " " << f << "\n";
    }
  }
}

int main(int argc, char *argv[]) {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout << fixed << setprecision(10);

  prework();
  int o_o;
  for (cin >> o_o; o_o; --o_o) solve();
  return 0;
}
