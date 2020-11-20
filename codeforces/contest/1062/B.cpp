#include <bits/stdc++.h>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  int n;
  cin >> n;
  if (n == 1) {
    cout << "1 0" << endl;
    return 0;
  }
  vector<int> p, fac(n + 2);
  vector<bool> vis(n + 2, false);
  for (int i = 2; i <= n; i++) {
    if (!vis[i]) {
      p.push_back(i);
      fac[i] = i;
    }
    for (int &x : p) {
      if (x * i > n)
        break;
      fac[x * i] = x;
      vis[x * i] = true;
      if (i % x == 0)
        break;
    }
  }
  int x = n, mx = 0;
  int mul = 1, delta = 0;
  while (x > 1) {
    int t = 0, f = fac[x];
    while (fac[x] == f) {
      t++;
      x /= f;
    }
    if (mx && mx != t) {
      delta = 1;
    }
    mx = max(mx, t);
    mul *= f;
  }
  if (fabs(ceil(log2(mx)) - log2(mx)) > 1e-9) {
    delta = 1;
  }
  cout << mul << " " << int(ceil(log2(mx))) + delta << endl;
  return 0;
}
