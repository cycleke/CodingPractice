#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <queue>
#include <string>
#define ll long long
using namespace std;
const int maxn = 5050;
int n;
int r, b;
int rl[40], bl[40];
ll w[40][40];
bool vis[40];
ll ans;
void dfs(int lst, ll nowans) {
  ans = max(ans, nowans);
  if (r == n && b == n) {
    return;
  }
  ll tmp;
  if (r < n) {
    rl[++r] = lst;
    tmp = nowans;
    for (int i = 1; i <= b; i++) {
      tmp += w[lst][bl[i]];
    }
    dfs(lst + 1, tmp);
    rl[r] = 0;
    r--;
  }
  if (b < n) {
    bl[++b] = lst;
    tmp = nowans;
    for (int i = 1; i <= r; i++) {
      tmp += w[lst][rl[i]];
    }
    dfs(lst + 1, tmp);
    bl[b] = 0;
    b--;
  }
}
int main() {
  cin >> n;
  for (int i = 1; i <= n + n; i++) {
    for (int j = 1; j <= n + n; j++) {
      cin >> w[i][j];
    }
  }
  dfs(1, 0);
  cout << ans;
  return 0;
}
