#include <bits/stdc++.h>
using namespace std;

long long gao(int a, int b) {
  if (a == b) return 0;
  if (a == 0) return 2 * b - 1 + gao(1, b);

  long long res = 0;

  static auto f =
    [&](int a, int b) {
      int res = 0, zeros = 0;
      for (int i = 1; i <= b; i <<= 1) {
        if (b & i) {
          b ^= i;
          if (!(a & b))
            res += 1 << zeros;
        }
        if (~a & i) ++zeros;
      }
      return res;
    };

  if (a & 1) {
    res += 2 * (f(a, b) - f(a, a));
    ++a;
  }
  if (b & 1) {
    res += 2 * (f(b - 1, b) - f(b - 1, a));
    --b;
  }
  return res + 3 * gao(a / 2, b / 2);
}

void solve() {
  int a, b;
  cin >> a >> b;
  cout << gao(a, b + 1) << '\n';
}

int main() {
  // freopen("in1.txt", "r", stdin);
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int o_o;
  for (cin >> o_o; o_o; --o_o) solve();

  return 0;
}
