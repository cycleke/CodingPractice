#include <bits/stdc++.h>
using namespace std;

void solve(int case_number) {
  cout << "Case #" << case_number << ": ";
  int n;
  cin >> n;
  double s, a, b, ans = 0, max_b = 0;
  for (int i = 0; i <= n; ++i) {
    cin >> s;
    ans += s;
  }
  for (int i = 0; i < n; ++i) {
    cin >> a >> b;
    max_b = max(max_b, b);
  }
  cout << ans + max_b << '\n';
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout << fixed << setprecision(6);

  int o_o, case_number = 0;
  for (cin >> o_o; o_o; --o_o) solve(++case_number);

  return 0;
}
