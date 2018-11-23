#include <bits/stdc++.h>
using namespace std;

typedef pair<int, int> pii;
typedef long long ll;
typedef vector<int> vi;
typedef vector<long long> vll;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);

  int n;
  cin >> n;
  vi f(n + 1, 0);
  const int MOD = 1e9 + 7;
  static auto Add = [&](int &a, const int &b) {
    a += b;
    if (a >= MOD)
      a -= MOD;
  };
  f[0] = 1;
  for (int i = 0; i < n; i++) {
    int x;
    cin >> x;
    vi g;
    for (int i = 1; i * i <= x; i++) {
      if (x % i != 0)
        continue;
      g.push_back(i);
      if (i * i < x) {
        g.push_back(x / i);
      }
    }
    sort(g.begin(), g.end());
    for (int i = int(g.size() - 1); i >= 0; i--) {
      if (g[i] > n)
        continue;
      Add(f[g[i]], f[g[i] - 1]);
    }
  }
  // for (int x : f) {
  // cout << x << " ";
  //}
  int ans = MOD -1;
  for (int &x : f) {
    Add(ans, x);
  }
  cout << ans << endl;
  return 0;
}
