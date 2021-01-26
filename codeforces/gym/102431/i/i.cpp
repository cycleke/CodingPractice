#include <bits/stdc++.h>
using namespace std;

void solve() {
  int n;
  cin >> n;
  for (int i = 1; i <= n; ++i)
    for (int j = i; j <= n; ++j) {
      cout << i << " " << j << " " << i << " " << j << " 0 " << i << " " << j
           << " 1\n";
    }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr), cout.tie(nullptr);

  int o_o;
  cin >> o_o;
  for (int step = 1; step <= o_o; ++step) {
    cout << "Case #" << step << ":\nYES\n";
    solve();
  }

  return 0;
}
