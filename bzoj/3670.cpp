#include <cstdio>
#include <cstring>

const int MAXN = 1e6 + 3;
const int MOD = 1e9 + 7;

char s[MAXN];
int f[MAXN], g[MAXN];

inline int ract() {
  int n = strlen(s + 1);
  int ans = 1;
  g[0] = -1;
  for (register int i = 2, j = 0, k = 0; i <= n; i++) {
    while (j && s[i] != s[j + 1])
      j = f[j];
    if (s[i] == s[j + 1])
      j++;
    f[i] = j;
    g[i] = g[j] + 1;
    while (k && (s[i] != s[k + 1] || (k + 1) > (i / 2)))
      k = f[k];
    if (s[i] == s[k + 1])
      k++;
    ans = ans * (g[k] + 2ll) % MOD;
  }
  return ans;
}

int main() {
  // freopen("in", "r", stdin);
  int orz;
  scanf("%d\n", &orz);
  while (orz--) {
    fgets(s + 1, MAXN, stdin);
    printf("%d\n", ract());
  }
  return 0;
}
