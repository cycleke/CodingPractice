#include <bits/stdc++.h>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  double lg = log10(2.0);
  int m, case_count = 0;
  while (cin >> m) cout << "Case #" << ++case_count << ": " << int(m * lg) << '\n';
  return 0;
}
