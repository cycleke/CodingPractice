#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1e6 + 5;

int n, p, bell[MAXN], a[MAXN];

int gao(int n) {
  if (~bell[n]) return bell[n];
  return bell[n] = (gao(n - p) + gao(n + 1 - p)) % p;
}

void solve() {
  cin >> n >> p;
  memset(bell, -1, sizeof(int) * (n + 12));
  a[0] = 1;
  bell[0] = bell[1] = 1;
  for (int i = 2; i < p; ++i) {
    a[i - 1] = bell[i - 1];
    for (int j = i - 2; ~j; --j) a[j] = (a[j] + a[j + 1]) % p;
    bell[i] = a[0];
  }

  cout << gao(n) << '\n';
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int o_o;
  for (cin >> o_o; o_o; --o_o) solve();
  return 0;
}
