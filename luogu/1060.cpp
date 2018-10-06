#include <bits/stdc++.h>
using namespace std;

int f[30001];

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  int n, m;
  cin >> n >> m;
  for (int i = 0; i < m; i++) {
    int v, p;
    cin >> v >> p;
    for (int j = n; j >= v; j--)
      f[j] = max(f[j], f[j - v] + v * p);
  }
  cout << f[n];
  return 0;
}
