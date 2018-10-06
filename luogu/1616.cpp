#include <bits/stdc++.h>
using namespace std;

long long f[100001];

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  int t, m;
  cin >> t >> m;
  for (register int i = 0; i < m; i++) {
    int v, p;
    cin >> v >> p;
    for (register int j = v; j <= t; j++)
      f[j] = max(f[j], f[j - v] + p);
  }
  cout << f[t] << endl;
  return 0;
}
