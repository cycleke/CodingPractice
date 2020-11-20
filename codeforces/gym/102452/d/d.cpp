#include <bits/stdc++.h>
using namespace std;

void solve() {
  int k, x;
  cin >> k >> x;
  vector<int> dig;
  for (; x; x /= k) dig.push_back(x % k);
  int n = dig.size();
  for (int i = 0; i < n - 1; ++i) {
    if (dig[i] > 0) continue;
    dig[i] += k, --dig[i + 1];
  }
  while (dig[n - 1] == 0) --n;
  for (int i = n - 1; ~i; --i) cout << dig[i] + 9 - k;
  cout << "\n";
}

int main(int argc, char *argv[]) {
  ios::sync_with_stdio(false);
  cin.tie(nullptr), cout.tie(nullptr);
  cout << fixed << setprecision(10);

  int o_o;
  for (cin >> o_o; o_o; --o_o) solve();
  return 0;
}
