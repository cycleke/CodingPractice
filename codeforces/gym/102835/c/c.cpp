#include <bits/stdc++.h>
#define R register
#define inf 1e9

int n, k, sum[4][10010], T;

using namespace std;

int main() {
  scanf("%d", &T);
  while (T--) {
    scanf("%d%d", &n, &k);
    sum[1][1] = k - 1;
    int now = 1;
    for (int i = 2; i <= n; ++i) {
      if (sum[(i & 1) ^ 1][now] & 1) now++;
      for (int j = 1; j <= i; ++j)
        sum[i & 1][j] =
            sum[(i & 1) ^ 1][j - 1] / 2 + (sum[(i & 1) ^ 1][j] + 1) / 2;
      sum[i & 1][i + 1] = sum[i & 1][i + 2] = sum[i & 1][i + 3] = 0;
    }
    printf("%d\n", now - 1);
    memset(sum, 0, sizeof(sum));
  }
}
