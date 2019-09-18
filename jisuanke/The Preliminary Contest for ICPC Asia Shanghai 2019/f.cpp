// by OwenCreeper
#include "bits/stdc++.h"
using namespace std;
typedef unsigned long long ull;
int Case = 0, ans[100];
__int128 dp[100][100];
__int128 getAns(int x, int y) {
  if (dp[x][y]) return dp[x][y];
  if (x == 0) return 1;
  return dp[x][y] = getAns(x - 1, y) * y + getAns(x - 1, y + 1);
}
void work() {
  int n, top = 0;
  __int128 k = 0;
  scanf("%d", &n);
  char ch = getchar();
  while (ch > '9' || ch < '0') ch = getchar();
  while (ch <= '9' && ch >= '0') k *= 10, k += ch - 48, ch = getchar();
  for (int i = 1; i < n; i++) {
    ans[i] = 0;
    for (int j = 1; j <= top; j++)
      if (getAns(n - i, top) < k)
        k -= getAns(n - i, top);
      else {
        ans[i] = j;
        break;
      }
    if (!ans[i]) ans[i] = ++top;
  }
  ans[n] = k;
  Case++;
  printf("Case #%d: ", Case);
  for (int i = 1; i <= n; i++) putchar(ans[i] - 1 + 'A');
  puts("");
}
int main(int argc, char const *argv[]) {
  int T;
  scanf("%d", &T);
  while (T--) work();
  return 0;
}
