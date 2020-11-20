#include <bits/stdc++.h>
using namespace std;

const int MAXN = 2e5 + 5;

int n, a[MAXN], d[MAXN];

void solve(int case_number) {
  cout << "Case #" << case_number << ": ";
  cin >> n;
  for (int i = 0; i < n; ++i) cin >> a[i];
  a[n] = 0;
  d[0] = a[0];
  for (int i = 1; i <= n; ++i) d[i] = a[i] - a[i - 1];

  int cur = 0;
  for (int i = 0, j = 3; i <= n; ++i, ++j) {
    if (d[i] > 0) cur += d[i];
    if (j <= n && d[j] < 0) cur += d[j];
    if (cur < 0) return (void)(cout << "No\n");
  }
  cout << (cur ? "No\n" : "Yes\n");
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int o_o, case_number = 0;
  for (cin >> o_o; o_o; --o_o) solve(++case_number);

  return 0;
}
