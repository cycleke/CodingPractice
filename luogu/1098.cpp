#include <cstdio>

int main() {
  char s[102];
  int p1, p2, p3;
  scanf("%d%d%d%s", &p1, &p2, &p3, s);
  for (char *it = s; *it; it++) {
    char cur = *it;
    char pred = it[-1], succ = it[1];
    if (cur == '-' && pred < succ &&
        ((pred >= '0' && succ <= '9') ||
         (pred >= 'a' && succ <= 'z'))) {
      for (char c = p3==1?pred+1:succ-1; p3==1?c<succ:c>pred; p3==1?c++:c--) {
        char ch = c;
        if (p1 == 2)
          ch = (ch >= 'a') ? ch - 32 : ch;
        else if (p1 == 3)
          ch = '*';
        for (int i = 0; i < p2; i++) putchar(ch);
      }
    } else putchar(cur);
  }
  return 0;
}
