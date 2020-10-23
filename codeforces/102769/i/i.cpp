#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

struct Vector {
  ll x, y;
  Vector(ll x = 0, ll y = 0) : x(x), y(y) {}
  Vector operator*(const ll &rate) const { return Vector(x * rate, y * rate); }
  Vector operator-(const Vector &other) const {
    return Vector(x - other.x, y - other.y);
  }
};

void gao(Vector &a, Vector &b) {
  for (ll t; a.x; swap(a, b)) {
    t = b.x / a.x;
    b = b - a * t;
  }
}

void solve() {
  Vector a, b;
  int Q, opt, w;
  long long ans = 0, x, y;
  for (cin >> Q; Q; --Q) {
    cin >> opt >> x >> y;
    if (opt == 1) {
      if (!x && !y) continue;
      Vector c(x, y);
      gao(c, a);
      if (c.y) b.y = __gcd(c.y, b.y);
      if (b.y) a.y %= b.y;
    } else {
      cin >> w;
      if (x) {
        if (a.x == 0 || x % a.x) continue;
        y -= x / a.x * a.y;
      }
      if (y == 0 || (b.y && y % b.y == 0)) ans += w;
    }
  }
  cout << ans << "\n";
}

int main(int argc, char *argv[]) {
  ios::sync_with_stdio(false);
  cin.tie(nullptr), cout.tie(nullptr);

  int T;
  cin >> T;
  for (int step = 1; step <= T; ++step) {
    cout << "Case #" << step << ": ";
    solve();
  }

  return 0;
}
