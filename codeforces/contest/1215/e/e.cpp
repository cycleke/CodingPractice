#include <bits/stdc++.h>
using namespace std;

const int COLOR = 20;

int n;
vector<int> pos[COLOR];
long long cnt[COLOR][COLOR], dp[1 << COLOR];

void cmin(long long &a, long long b) {
  if (a > b) a = b;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  cin >> n;
  for (int i = 0, a; i < n; ++i) {
    cin >> a;
    pos[a - 1].push_back(i);
  }

  for (int i = 0; i < COLOR; ++i) {
    if (pos[i].empty()) continue;
    for (int j = 0; j < COLOR; ++j) {
      if (i == j || pos[j].empty()) continue;
      int p2 = 0;
      for (int p1 = 0; p1 < (int)pos[i].size(); ++p1) {
        for (;; ++p2)
          if (p2 == (int)pos[j].size() - 1 || pos[j][p2 + 1] > pos[i][p1])
            break;
        if (pos[j][p2] < pos[i][p1]) cnt[i][j] += p2 + 1;
      }
      // cerr << i << ' ' << j << ' ' << cnt[i][j] << '\n';
    }
  }

  memset(dp, 0x3f, sizeof(dp));
  dp[0] = 0;

  for (int s = 0, S = 1 << COLOR; s < S; ++s) {
    for (int i = 0; i < COLOR; ++i) {
      if (s >> i & 1) continue;
      long long temp = 0;
      for (int j = 0; j < COLOR; ++j)
        if (s >> j & 1) temp += cnt[i][j];
      cmin(dp[s ^ (1 << i)], dp[s] + temp);
    }
  }
  cout << dp[(1 << COLOR) - 1] << '\n';

  return 0;
}
