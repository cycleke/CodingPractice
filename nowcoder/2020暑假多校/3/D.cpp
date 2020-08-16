#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef vector<pii> vpii;

void prework() {}

#define NO_SOLUTION                                                            \
  {                                                                            \
    cout << "No\n";                                                            \
    return;                                                                    \
  }

void solve() {
  int n, k;
  cin >> n >> k;
  if (k % 2 || k > 4 * n) NO_SOLUTION;

  int h = 1, w = 1;
  while (h * w < n) (h <= w) ? ++h : ++w;
  if (2 * (h + w) > k) NO_SOLUTION;

  static pii grid[100];
  static int mark[1000][1000], clock;

  ++clock;
  int cnt = 0;
  for (int i = 1; i <= h; ++i)
    for (int j = 1; j <= w; ++j)
      if (cnt < n) {
        mark[i][j] = clock;
        grid[cnt++] = pii(i, j);
      }

  int now_k = 2 * (h + w), y = 1;
  for (--cnt; now_k < k; --cnt) {
    int v = 0;
    v += mark[grid[cnt].first - 1][grid[cnt].second] == clock;
    v += mark[grid[cnt].first][grid[cnt].second - 1] == clock;
    if (now_k + 2 * v <= k) {
      now_k += 2 * v;
      grid[cnt] = pii(20, y);
      y += 2;
    } else {
      now_k += 2;
      grid[cnt] = pii(1, w + 1);
    }
  }

  cout << "Yes\n";
  for (int i = 0; i < n; ++i)
    cout << grid[i].first << " " << grid[i].second << "\n";
}

int main(int argc, char *argv[]) {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout << fixed << setprecision(10);

  prework();
  int o_o;
  for (cin >> o_o; o_o; --o_o) solve();
  return 0;
}
