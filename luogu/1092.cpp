#include <bits/stdc++.h>
using namespace std;

const int MAXN = 30;

int n, d[MAXN], x[MAXN];
int a[MAXN][MAXN], g[MAXN][MAXN];
bool vis[MAXN];
char s[3][MAXN];

bool dfs(const int &step) {
  if (step == n) {
    bool flag = true;
    memset(vis, 0, sizeof(vis));
    for (int i = 1; i <= n; i++) {
      int &v = x[i] = 0;
      for (int j = 1; j <= n; j++)
        v += g[i][j] * d[j];
      if (v % a[i][i] != 0 || v / a[i][i] < 0 ||
          v / a[i][i] >= n || vis[v / a[i][i]]) {
        flag = false;
        break;
      }
      v /= a[i][i];
      vis[v] = true;
    }
    return flag;
  } else {
    d[step] = 1;
    if (dfs(step + 1)) return true;
    d[step] = 0;
    if (dfs(step + 1)) return true;
    return false;
  }
}

int main() {

  scanf("%d%s%s%s", &n, s[0], s[1], s[2]);

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < 2; j++)
      a[n - i][s[j][i] - 'A' + 1]++;
    a[n - i][s[2][i] - 'A' + 1]--;
  }
  for (int i = 1; i <= n; i++) {
    g[i][i] = n;
    g[i][i - 1] = -1;
  }
  g[1][0] = 0;

  for (int step = 1; step <= n; step++) {
    int maxr = step;
    for (int i = step + 1; i <= n; i++) {
      if (abs(a[i][step]) > abs(a[maxr][step]))
        maxr = i;
    }
    if (maxr != step) {
      swap(a[step], a[maxr]);
      swap(g[step], g[maxr]);
    }
    if (a[step][step] == 0) {
      fprintf(stderr, "Input Data Error\n");
      return -2;
    }
    for (int i = 1; i <= n; i++) {
      if (i != step && a[i][step] != 0) {
        int lcm = a[i][step] / __gcd(a[i][step], a[step][step]) * a[step][step];
        int t1 = lcm / a[i][step];
        int t2 = lcm / a[step][step];
        for (int j = 1; j <= n; j++) {
          a[i][j] = t1 * a[i][j] - t2 * a[step][j];
          g[i][j] = t1 * g[i][j] - t2 * g[step][j];
        }
      }
    }
  }

  if (!dfs(1)) {
    fprintf(stderr, "No Solution\n");
    return -3;
  }
  for (int i = 1; i <= n; i++) {
    printf("%d ", x[i]);
  }

  return 0;
}
