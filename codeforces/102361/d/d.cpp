#include <bits/stdc++.h>
using namespace std;

void solve() {
  int n;
  cin >> n;
  while (n % 2 == 0) n /= 2;
  while (n % 5 == 0) n /= 5;
  cout << (n != 1 ? "Yes\n" : "No\n");
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int o_o;
  for (cin >> o_o; o_o; --o_o) solve();
  return 0;
}
