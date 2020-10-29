#include <bits/stdc++.h>
using namespace std;

const int MAXN = 2e5 + 3;

int mpow(int a, int b, int m) {
  int r = 1;
  for (; b; b >>= 1, a = 1ll * a * a % m)
    (b & 1) && (r = 1ll * r * a % m);
  return r;
}

int inv(int x, int m) { return mpow(x, m - 2, m); }

int a[MAXN], n, p;

void solve() {
  cin >> n >> p;
  for (int i = 0; i < n; ++i) cin >> a[i];
  
  static vector<int> qs;
  static map<int, int> f;
  
  f.clear();
  ++f[1ll * a[1] * inv(a[0], p) % p];
  for (int i = 2; i < n; ++i) {
    ++f[1ll * a[i] * inv(a[i - 1], p) % p];
    ++f[1ll * a[i] * inv(a[i - 2], p) % p];
  }

  int bound = n / 8;
  qs.clear();
  for (auto &p : f)
    if (p.second >= bound) qs.push_back(p.first);

  static auto gao = [&](int q) {
    f.clear();
    int res = 0;
    for (int i = n - 1; ~i; --i) {
      f[a[i]] = max(f[a[i]], f[1ll * a[i] * q % p] + 1);
      res = max(res, f[a[i]]);
    }
    return res;
  };
  
  int ans = 0;
  for (int q : qs) ans = max(ans, gao(q));
  cout << (ans * 2 < n ? -1 : ans) << "\n";
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr), cout.tie(nullptr);

  int o_o;
  for (cin >> o_o; o_o; --o_o) solve();
  
  return 0;
}

