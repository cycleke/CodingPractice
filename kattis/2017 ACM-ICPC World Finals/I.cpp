#include <cstdio>
#include <cstring>

bool e[26][26];
char s1[51], s2[51];

int main() {
  int m, n;
  while (scanf("%d %d", &m, &n) != EOF) {
    for (int i = 0; i < 26; ++i) {
      for (int j = 0; j < 26; ++j) {
        e[i][j] = i == j;
      }
    }
    while (m--) {
      char a, b;
      scanf("\n%c %c", &a, &b);
      e[a - 'a'][b - 'a'] = true;
    }
    for (int k = 0; k < 26; ++k) {
      for (int i = 0; i < 26; ++i) {
        for (int j = 0; j < 26; ++j) {
          if (!e[i][j]) {
            e[i][j] = e[i][k] & e[k][j];
          }
        }
      }
    }
    while (n--) {
      scanf("%s %s", s1, s2);
      int l1 = strlen(s1);
      int l2 = strlen(s2);
      if (l1 != l2) {
        puts("no");
      } else {
        bool flag = true;
        for (int i = 0; i < l1; ++i) {
          if (!e[s1[i] - 'a'][s2[i] - 'a']) {
            flag = false;
            break;
          }
        }
        puts(flag ? "yes" : "no");
      }
    }
  }
  return 0;
}

