#include <bits/stdc++.h>
using namespace std;

int f[1001];

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  int T, M;
  cin >> T >> M;
  for (int i = 0; i < M; i++) {
    int t, v;
    cin >> t >> v;
    for (int j = T; j >= t; j--)
      f[j] = max(f[j], f[j - t] + v);
  }
  cout << f[T] << endl;
  return 0;
}
