#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<int, int> pii;

const int MOD = 1e9 + 7;
const int MAXN = 1e5 + 3;
// mt19937 rnd(chrono::high_resolution_clock::now().time_since_epoch().count());

long long c[6];
map<pii, int> dir;

const int dx[] = {1, 0, -1, -1, 0, 1};
const int dy[] = {1, 1, 0, -1, -1, 0};

void solve() {
  int x, y;
  cin >> x >> y;
  for (int i = 0; i < 6; ++i) cin >> c[i];

  static auto cmin = [&](long long &a, long long b) {
    if (a > b) a = b;
  };

  for (int step = 0; step < 6; ++step)
    for (int i = 0; i < 6; ++i)
      for (int j = 0; j < 6; ++j) {
        int x = dx[i] + dx[j];
        int y = dy[i] + dy[j];
        if (!dir.count({x, y})) continue;
        cmin(c[dir[{x, y}]], c[i] + c[j]);
      }

  if (x >= 0 && y >= 0) {
    cout << (x >= y ? y * c[0] + (x - y) * c[5] : x * c[0] + (y - x) * c[1])
         << "\n";
  } else if (x <= 0 && y <= 0) {
    x = -x, y = -y;
    cout << (x >= y ? y * c[3] + (x - y) * c[2] : x * c[3] + (y - x) * c[4])
         << "\n";
  } else {
    cout << (x >= 0 ? x * c[5] - y * c[4] : y * c[1] - x * c[2]) << "\n";
  }
}

int main(int argc, char *argv[]) {
  ios::sync_with_stdio(false);
  cin.tie(nullptr), cout.tie(nullptr);
  cout << fixed << setprecision(10);

  for (int i = 0; i < 6; ++i) dir[{dx[i], dy[i]}] = i;

  int o_o;
  for (cin >> o_o; o_o; --o_o) solve();
  return 0;
}
