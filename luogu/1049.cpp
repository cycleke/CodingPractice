#include <bits/stdc++.h>
using namespace std;

int f[20001];

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  int V, n;
  cin >> V >> n;
  for (int i = 0; i < n; i++) {
    int v;
    cin >> v;
    for (int j = V; j >= v; j--)
      f[j] = max(f[j], f[j - v] + v);
  }
  cout << V - f[V] << endl;
  return 0;
}
