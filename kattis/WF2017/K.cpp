#include <vector>
#include <cstdio>
#include <cstring>
#include <algorithm>

#define MAXN 1000003

int p[MAXN];
char round_string[10][MAXN], s[MAXN];
std::pair < std::vector < int >, int > a[MAXN];

int main() {
  int n, round, len;
  scanf("%d %d", &n, &round);
  for (int i = 0; i < round; ++i) {
    scanf("%s", round_string[i]);
    len = strlen(round_string[i]);
    for (int j = 0; j < len; ++j) {
      s[j + 1] = round_string[i][j];
    }
    //kmp
    int k = 0;
    p[1] = 0;
    for (int j = 2; j <= len; ++j) {
      while (k > 0 && s[j] != s[k + 1]) {
        k = p[k];
      }
      if (s[j] == s[k + 1]) {
        ++k;
      }
      p[j] = k;
    }
    a[i].first.clear();
    for (int j = len; j > 0 && 2 * len - j <= n; j = p[j]) {
      a[i].first.push_back(j);
    }
    a[i].second = i;
  }
  std::sort(a, a + round);
  for (int i = 0; i < round; ++i) {
    printf("%s\n", round_string[a[i].second]);
  }
  return 0;
}
