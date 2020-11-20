#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<int, int> pii;

const int MOD = 1e9 + 7;
const int MAXN = 200 + 3;
// mt19937 rnd(chrono::high_resolution_clock::now().time_since_epoch().count());

void solve() {
  static char maze[MAXN][MAXN];

  int n;
  cin >> n;
  for (int i = 1; i <= n; ++i) cin >> (maze[i] + 1);

  int s = (maze[1][2] == maze[2][1]) ? maze[1][2] - '0' : 3;
  int f = (maze[n - 1][n] == maze[n][n - 1]) ? maze[n - 1][n] - '0' : 3;

  vector<pair<int, int>> ans;
  auto gao = [&](int x, int y, int goal) {
    if (maze[x][y] - '0' == goal) return;
    ans.emplace_back(x, y);
  };
  if (s < 3) {
    int f_ = s ^ 1;
    gao(n - 1, n, f_), gao(n, n - 1, f_);
  } else {
    if (f < 3) {
      int s_ = f ^ 1;
      gao(1, 2, s_), gao(2, 1, s_);
    } else {
      gao(1, 2, 0), gao(2, 1, 0);
      gao(n - 1, n, 1), gao(n, n - 1, 1);
    }
  }

  cout << ans.size() << "\n";
  for (auto p : ans) cout << p.first << " " << p.second << "\n";
}

int main(int argc, char *argv[]) {
  ios::sync_with_stdio(false);
  cin.tie(nullptr), cout.tie(nullptr);
  cout << fixed << setprecision(10);

  int o_o;
  for (cin >> o_o; o_o; --o_o) solve();
  return 0;
}
