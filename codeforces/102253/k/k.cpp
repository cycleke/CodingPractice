#include <bits/stdc++.h>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int case_count = 0, n;
  long long k;
  while (cin >> n >> k) {
    cout << "Case #" << ++case_count << ": ";
    if (k <= n) {
      cout << k << '\n';
      continue;
    }
    k -= n;
    k %= 2 * (n - 1);
    if (k == 0) {
      cout << n << '\n';
    } else if (k < n) {
      cout << k << '\n';
    } else {
      cout << k - n + 1 << '\n';
    }
  }

  return 0;
}
