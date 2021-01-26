#include <bits/stdc++.h>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr), cout.tie(nullptr);

  int o_o;
  cin >> o_o;
  for (int n, m, step = 1; step <= o_o; ++step) {
    cout << "Case #" << step << ": ";
    cin >> n >> m;
    if (n == 1 && m == 1) {
      cout << "1\n";
    } else if (n == 1 || m == 1) {
      cout << "2\n";
    } else {
      cout << 2 * n + 2 * m - 4 << "\n";
    }
  }

  return 0;
}
