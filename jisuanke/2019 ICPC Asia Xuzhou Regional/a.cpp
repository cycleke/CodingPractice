#pragma GCC optimize(2)
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

void solve() {
  static auto gao = [&](ll x) {
    ll y = x, res = 0;
    while (y % 4 != 3 && y > 0) --y;
    for (++y; y <= x; ++y) res ^= y;
    return res;
  };
  ll ans = -1, l, r, s;
  cin >> l >> r >> s;
  ll il = l - 1, ir = min(r - 1, l + 4);
  ll jl = max(l, r - 4), jr = r;
  for (ll i = il; i <= ir; ++i)
    for (ll j = jl; j <= jr; ++j) {
      if (i >= j) continue;
      if ((gao(i) ^ gao(j)) <= s) ans = max(ans, j - i);
    }
  cout << ans << "\n";
}

int main(int argc, char *argv[]) {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int o_o;
  for (cin >> o_o; o_o; --o_o) solve();
  return 0;
}
