#include <bits/stdc++.h>
using namespace std;

bitset<2048> s;
int n, m, a[20], ans, chosen;

void dfs(int step, int rest) {
  if (step == n) {
    s.reset();
    s[0] = 1;
    auto getPos = [&](const int &x) {
      for (int i = 0; i < 20; i++) {
        if (x >> i & 1) return i;
      }
      exit(-1);
    };
    for (int i = chosen; i; i &= i - 1)
      s |= s << a[getPos(i)];
    ans = max(ans, int(s.count()) - 1);
  } else {
    if (rest) {
      dfs(step + 1, rest - 1);
    }
    if (n - step - 1 >= rest) {
      chosen ^= 1 << step;
      dfs(step + 1, rest);
      chosen ^= 1 << step;
    }
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  cin >> n >> m;
  for (int i = 0; i < n; i++) {
    cin >> a[i];
  }
  ans = 0;
  dfs(0, m);
  cout << ans << endl;
  return 0;
}
