#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1e6 + 6;

int p[MAXN], son[MAXN];

void solve() {
  int n;
  cin >> n;
  memset(son + 1, 0, sizeof(int) * n);
  for (int i = 2; i <= n; ++i) {
    cin >> p[i];
    ++son[p[i]];
  }

  for (int i = 1; i <= n; ++i) {
    if (son[i]) continue;
    int cnt = 0, u = i;
    while (u && son[u] < 2) {
      ++cnt;
      u = p[u];
    }
    if (cnt & 1) {
      cout << "Takeru\n";
      return;
    }
  }
  cout << "Meiya\n";
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int o_o;
  for (cin >> o_o; o_o; --o_o) solve();
  return 0;
}
