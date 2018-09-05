#include <cstdio>

int main() {
  int n, k, next[51] = { -1};
  char s[51];
  scanf("%d%d%s", &n, &k, s);
  for (int i = 1, j = -1; i < n; i++) {
    while ((~j) && s[i] != s[j + 1]) j = next[j];
    next[i] = (s[i] == s[j + 1]) ? ++j : j;
  }
  printf("%s", s);
  char *subs = s + next[n - 1] + 1;
  for (int i = 1; i < k; i++) printf("%s", subs);
  return 0;
}
