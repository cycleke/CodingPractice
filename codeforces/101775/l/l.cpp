#include <bits/stdc++.h>
using namespace std;

const int MAXN = 2e5 + 5;

int n;

void solve(int case_number) {
  cout << "Case #" << case_number << ": ";
  cin >> n;
  if (n & 1) cout << (n < 7 ? "Draw\n" : "Panda\n");
  if (~n & 1) cout << (n < 16 ? "Draw\n" : "Sheep\n");
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int o_o, case_number = 0;
  for (cin >> o_o; o_o; --o_o) solve(++case_number);

  return 0;
}
