#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1e5 + 5;

char s[MAXN], gen[4][4][4];
int need[256][3], dp[MAXN][3][3];

inline void init() {
  // Q:0, W:1, E:2
  need['Y'][0] = 3, need['Y'][1] = 0, need['Y'][2] = 0;
  need['V'][0] = 2, need['V'][1] = 1, need['V'][2] = 0;
  need['G'][0] = 2, need['G'][1] = 0, need['G'][2] = 1;
  need['C'][0] = 0, need['C'][1] = 3, need['C'][2] = 0;
  need['X'][0] = 1, need['X'][1] = 2, need['X'][2] = 0;
  need['Z'][0] = 0, need['Z'][1] = 2, need['Z'][2] = 1;
  need['T'][0] = 0, need['T'][1] = 0, need['T'][2] = 3;
  need['F'][0] = 1, need['F'][1] = 0, need['F'][2] = 2;
  need['D'][0] = 0, need['D'][1] = 1, need['D'][2] = 2;
  need['B'][0] = 1, need['B'][1] = 1, need['B'][2] = 1;

  for (int i = 0; i < 256; ++i) {
    if (!need[i][0] && !need[i][1] && !need[i][2]) continue;
    gen[need[i][0]][need[i][1]][need[i][2]] = i;
  }
}

struct Node {
  int idx, v1, v2;
  Node(int idx, int v1, int v2) : idx(idx), v1(v1), v2(v2) {}
};

queue<Node> que;
int c[3], ord[3];
void dfs(int dep) {
  if (dep == 3) {
    dp[0][ord[1]][ord[2]] = 3;
    que.emplace(0, ord[1], ord[2]);
    return;
  }
  for (int i = 0; i < 3; ++i)
    if (c[i]) {
      --c[i];
      ord[dep] = i;
      dfs(dep + 1);
      ++c[i];
    }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  init();
  cin >> s;
  int n = strlen(s);

  memset(dp, 0x3f, sizeof(dp));
  memcpy(c, need[s[0]], sizeof(c));
  dfs(0);

  int ans = INT_MAX;
  while (!que.empty()) {
    int idx = que.front().idx;
    int v1 = que.front().v1;
    int v2 = que.front().v2;
    que.pop();
    if (idx == n - 1) {
      if (ans > dp[idx][v1][v2]) ans = dp[idx][v1][v2];
      continue;
    }

    int c[3] = {0};
    int d = dp[idx][v1][v2] + 1;

    ++c[v1], ++c[v2];
    static auto push = [&](const int &idx, const int &v1, const int &v2) {
      if (dp[idx][v1][v2] <= d) return;
      dp[idx][v1][v2] = d;
      que.emplace(idx, v1, v2);
    };

    if (s[idx] == s[idx + 1]) {
      --d;
      // cerr << "MARK\n";
      push(idx + 1, v1, v2);
      continue;
    }

    for (int i = 0; i < 3; ++i) {
      ++c[i];
      if (gen[c[0]][c[1]][c[2]] == s[idx + 1])
        push(idx + 1, v2, i);
      else
        push(idx, v2, i);
      --c[i];
    }
  }
  // cout << ans << '\n';
  cout << ans + n << '\n';
  return 0;
}
