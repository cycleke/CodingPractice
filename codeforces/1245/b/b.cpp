#include <bits/stdc++.h>
using namespace std;

void solve() {
  int n, a, b, c;
  string s;
  cin >> n >> a >> b >> c >> s;

  string t(n, '.');
  for (int i = 0; i < n; ++i) {
    if (s[i] == 'S' && a) {
      --a;
      t[i] = 'R';
    } else if (s[i] == 'R' && b) {
      --b;
      t[i] = 'P';
    } else if (s[i] == 'P' && c) {
      --c;
      t[i] = 'S';
    }
  }

  if (n - a - b - c >= (n + 1) / 2) {
    cout << "YES\n";
    for (int i = 0; i < n; ++i) {
      if (t[i] != '.') continue;
      if (a) --a, t[i] = 'R';
      else if (b) --b, t[i] = 'P';
      else t[i] = 'S';
    }
    cout << t << '\n';
    return;
  }
  cout << "NO\n";
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int o_o;
  for (cin >> o_o; o_o; --o_o) solve();
  return 0;
}
