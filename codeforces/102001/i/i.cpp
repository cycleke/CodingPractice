#include <bits/stdc++.h>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n;
  cin >> n;
  string s;
  bool ok = true;
  for (int i = 0; i < n; ++i) {
    cin >> s;
    ok ^= s == "LIE";
  }
  cout << (ok ? "TRUTH" : "LIE") << '\n';

  return 0;
}
